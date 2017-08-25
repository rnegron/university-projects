<?php
    header('Content-Type: text/html; charset=utf-8');

    // Using error reporting for debug
    error_reporting(E_ALL);

    // Retrieve MySQL login info
    $config = parse_ini_file('login.ini');

    // Connect to MySQL database
    $conn = new mysqli($config['hn'], $config['un'], $config['pw'], $config['db']);

    // Check for connection errors
    if ($conn->connect_error) die($conn->connect_error);
    $conn->set_charset('utf8mb4');

    // Check for search term entry
    if (!isset($_POST["term"]) or $_POST["term"] == "")
        exit("Favor de entrar algún termino en la búsqueda.");

    else $term = sanitizeSQL($conn, $_POST["term"]);

    // Check for radio button search option
    if (isset($_POST["searchOptions"])) $search = sanitizeSQL($conn, $_POST["searchOptions"]);

    // Check for checkbox show options
    if (!isset($_POST["showOptions"]))
        exit("Favor de escoger al menos una columna para mostrar resultados.");

    else $showOptions = $_POST["showOptions"];

    $template = "SELECT ";
    $markup = "<table style=\"border: 1px solid black; border-spacing: 10px;\"><tr>";

    // Sanitize each column name and parse
    for ($j = 0; $j < count($showOptions); ++$j) {
        $marked = false;
        $show[$j] = sanitizeSQL($conn, $showOptions[$j]);

        if ($show[$j] == "director") {
            $show[$j] = "CONCAT(Directores.primer_nombre, ' ', Directores.apellido) AS director";
            $markup = $markup . "<th>Director</th>";
            $marked = true;
        }
        else if ($show[$j] == "autor") {
            $show[$j] = "CONCAT(Autores.primer_nombre, ' ', Autores.apellido) AS autor";
            $markup = $markup . "<th>Autor</th>";
            $marked = true;
        }

        if ($j == count($showOptions) - 1) {
            $template = $template . $show[$j];

            if (!$marked) $markup = $markup . "<th>$show[$j]</th></tr>" ;
        }

        else {
            $template = $template . $show[$j] . ", ";
            if (!$marked) $markup = $markup . "<th>$show[$j]</th>";
        }

    }


    $tables = " FROM Obras O
        NATURAL JOIN `Teatros` T
        LEFT JOIN (SELECT obra_id, D.primer_nombre, D.segundo_nombre, D.apellido FROM `Directores_de_Obras` NATURAL JOIN `Directores` D) AS Directores ON O.obra_id = Directores.obra_id
        LEFT JOIN (SELECT obra_id, A.primer_nombre, A.segundo_nombre, A.apellido FROM `Autores_de_Obras` NATURAL JOIN `Autores` A) AS Autores ON O.obra_id = Autores.obra_id
        LEFT JOIN (SELECT obra_id, L.primer_nombre, L.segundo_nombre, L.apellido FROM `Diseño_de_Luces` NATURAL JOIN `Diseñadores_de_Luces` L) AS Luces ON O.obra_id = Luces.obra_id
        LEFT JOIN (SELECT obra_id, E.primer_nombre, E.segundo_nombre, E.apellido FROM `Diseño_de_Escenografia` NATURAL JOIN `Diseñadores_de_Escenografia` E) AS Escena ON O.obra_id = Escena.obra_id
        LEFT JOIN (SELECT obra_id, V.primer_nombre, V.segundo_nombre, V.apellido FROM `Diseño_de_Vestuario` NATURAL JOIN `Diseñadores_de_Vestuario` V) AS Vestido ON O.obra_id = Vestido.obra_id";


    if ($search == "titulo") $query = $template . $tables . " WHERE O.titulo LIKE \"%$term%\";";
    else if ($search == "director") $query = $template . $tables . " WHERE (Directores.primer_nombre LIKE \"%$term%\") OR (Directores.apellido LIKE \"%$term%\");";
    else if ($search == "autor") $query = $template . $tables . " WHERE (Autores.primer_nombre LIKE \"%$term%\") OR (Autores.apellido LIKE \"%$term%\");";

    $result = $conn->query($query);

    $rows = $result->num_rows;

    if (!$result or $result->num_rows == 0) die($conn->error);

    echo $markup;

    for ($j = 0; $j < $rows; ++$j) {
        $result->data_seek($j);
        $row = $result->fetch_array(MYSQLI_ASSOC);

        echo "<tr>";
        foreach($showOptions as $show) {echo "<td>" . $row[$show] . "</td>";}
        echo "</tr>";

    }

    echo "</table>";

    $conn->close();


    function sanitizeString($var) {
        if (get_magic_quotes_gpc()) $var = stripslashes($var);
        $var = strip_tags($var);
        $var = htmlentities($var);
        return $var;
    }

    function sanitizeSQL($conn, $var) {
        $var = $conn->real_escape_string($var);
        $var = sanitizeString($var);
        return $var;
    }
?>
