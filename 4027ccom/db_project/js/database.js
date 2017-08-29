//

$('#dbform').submit(function(){
    event.preventDefault();
    $('#results').empty();

    var showOptions = [];

    $('#checkboxes input:checked').each(function() {
        showOptions.push($(this).val());
    });

    if (showOptions.length == 0) {
        alert("Favor de escoger al menos una opción para mostrar resultados.");
        return false;
    };

    var searchOptions = $('#radios input:checked').val();
    var term = $('#term').val();

    if (searchOptions == 'year' && ($.isNumeric(term) == false || Math.floor(term) != term)) {
        alert("Favor de entrar solo números enteros cuando intente buscar por año.");
        return false;
    }

    if (term.length == 0) {
        alert("Favor de entrar algún termino en la búsqueda.");
        return false;
    }

    $.post('query.php', {search: searchOptions, term: term, show: showOptions},
                        function(data)
        {
            if (data) {
                $('#results').append(data)
                $('#result_table').DataTable({searching: false});
                $('.pagination').css("margin-bottom", "50px");
            }

            else {
                alert("No hay resultados! Favor de intentar con otras opciones.");
                $('#results').empty();
            }
        });
});
