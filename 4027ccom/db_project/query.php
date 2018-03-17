<?php
    header('Content-Type: text/html; charset=utf-8');

    // Using error reporting for debug
    // error_reporting(E_ALL);

    // Retrieve MySQL login info
    $config = parse_ini_file('login.ini');

    // Connect to MySQL database
    $conn = new mysqli($config['hn'], $config['un'], $config['pw'], $config['db']);

    // Check for connection errors
    if ($conn->connect_error) exit("");

    // Working with the utf8mb4 charset
    $conn->set_charset('utf8mb4');

    // Obtain parameters and sanitize them
    $term = sanitizeSQL($conn, $_POST["term"]);
    $search = sanitizeSQL($conn, $_POST["search"]);

    // $showOptions array has elements sanitized later
    $showOptions = $_POST["show"];

    // Start building a MySQL query template
    $template = "SELECT DISTINCT ";

    // Start building an HTML results table
    $markup = "<table id=\"result_table\" class=\"table table-bordered table-hover\"><thead class=\"thead-default\"><tr>";

    // Sanitize each column name ($showOptions element) and parse results
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

        else if ($show[$j] == "year") {
            $show[$j] = "O.año";
            $markup = $markup . "<th>Año</th>";
            $marked = true;
        }

        else if ($show[$j] == "titulo") {
            $markup = $markup . "<th>Título</th>";
            $marked = true;
        }

        else if ($show[$j] == "num_de_prod") {
            $markup = $markup . "<th>Número</th>";
            $marked = true;
        }

        else if ($show[$j] == "nombre_teatro") {
            $markup = $markup . "<th>Teatro</th>";
            $marked = true;
        }

        else if ($show[$j] == "luces") {
            $show[$j] = "CONCAT(Luces.primer_nombre, ' ', Luces.apellido) AS luces";
            $markup = $markup . "<th>Diseñador de Luces</th>";
            $marked = true;
        }

        else if ($show[$j] == "escena") {
            $show[$j] = "CONCAT(Escena.primer_nombre, ' ', Escena.apellido) AS escena";
            $markup = $markup . "<th>Diseñador de Escenografía</th>";
            $marked = true;
        }

        else if ($show[$j] == "vestido") {
            $show[$j] = "CONCAT(Vestido.primer_nombre, ' ', Vestido.apellido) AS vestido";
            $markup = $markup . "<th>Diseñador de Vestuario</th>";
            $marked = true;
        }

        // Last element should close tags
        if ($j == count($showOptions) - 1) {
            $template = $template . $show[$j];

            if (!$marked) $markup = $markup . "<th>". ucwords($show[$j]) . "</th></tr>" ;
        }

        // Otherwise keep the table row open
        else {
            $template = $template . $show[$j] . ", ";
            if (!$marked) $markup = $markup ."<th>". ucwords($show[$j]) . "</th>";
        }

    }

    // Finish the table header section and start table body
    $markup = $markup . "</thead><tbody>";


    // MySQL query for retrieving all the necessary data in a big table join
    $tables = " FROM Obras O
        NATURAL JOIN `Teatros` T
        LEFT JOIN (SELECT obra_id, D.primer_nombre, D.segundo_nombre, D.apellido FROM `Directores_de_Obras` NATURAL JOIN `Directores` D) AS Directores ON O.obra_id = Directores.obra_id
        LEFT JOIN (SELECT obra_id, A.primer_nombre, A.segundo_nombre, A.apellido FROM `Autores_de_Obras` NATURAL JOIN `Autores` A) AS Autores ON O.obra_id = Autores.obra_id
        LEFT JOIN (SELECT obra_id, L.primer_nombre, L.segundo_nombre, L.apellido FROM `Diseño_de_Luces` NATURAL JOIN `Diseñadores_de_Luces` L) AS Luces ON O.obra_id = Luces.obra_id
        LEFT JOIN (SELECT obra_id, E.primer_nombre, E.segundo_nombre, E.apellido FROM `Diseño_de_Escenografia` NATURAL JOIN `Diseñadores_de_Escenografia` E) AS Escena ON O.obra_id = Escena.obra_id
        LEFT JOIN (SELECT obra_id, V.primer_nombre, V.segundo_nombre, V.apellido FROM `Diseño_de_Vestuario` NATURAL JOIN `Diseñadores_de_Vestuario` V) AS Vestido ON O.obra_id = Vestido.obra_id";


    // Parse search options
    if ($search == "titulo") $query = $template . $tables . " WHERE O.titulo LIKE \"%$term%\";";
    else if ($search == "director") $query = $template . $tables . " WHERE CONCAT(Directores.primer_nombre, ' ', Directores.apellido) LIKE \"%$term%\";";
    else if ($search == "autor")    $query = $template . $tables . " WHERE CONCAT(Autores.primer_nombre, ' ', Autores.apellido) LIKE \"%$term%\";";
    else if ($search == "year")     $query = $template . $tables . " WHERE O.año = $term;";
    else if ($search == "luces")    $query = $template . $tables . " WHERE CONCAT(Luces.primer_nombre, ' ', Luces.apellido) LIKE \"%$term%\";";
    else if ($search == "escena")   $query = $template . $tables . " WHERE CONCAT(Escena.primer_nombre, ' ', Escena.apellido) LIKE \"%$term%\";";
    else if ($search == "vestido")  $query = $template . $tables . " WHERE CONCAT(Vestido.primer_nombre, ' ', Vestido.apellido) LIKE \"%$term%\";";

    // Retrieve results from database
    $result = $conn->query($query);

    // Get the number of received rows
    $rows = $result->num_rows;

    // Check if no rows received, exit
    if (!$result or $result->num_rows == 0) exit("");

    // Display the HTML markup table built so far
    echo $markup;

    // For every row received, display the row's results
    for ($j = 0; $j < $rows; ++$j) {
        $result->data_seek($j);
        $row = $result->fetch_array(MYSQLI_ASSOC);

        echo "<tr>";
        foreach($showOptions as $show) {

            // Year display fix
            if ($show == "year") $show = "año";

            // Fill data for row, column in table
            if ($show == "" or $show == " " or is_null($show)) echo "<td>" . "" . "</td>";
            else echo "<td>" . $row[$show] . "</td>";
        }
        echo "</tr>";
    }

    // Close the entire table
    echo "</tbody></table>";

    // Close the database connection
    $conn->close();

    // Helper functions for removing dangerous tags and sanitizing input strings
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
