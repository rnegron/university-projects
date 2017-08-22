import openpyxl
from collections import defaultdict

column_dict = dict(caja=1, año=2, prod=3, titulo=4,
             autor=5, director=6, escena=7, luz=8,
             vestido=9, notas=10)

problem_columns = ['autor', 'director', 'escena', 'luz', 'vestido']

def parse_names(string):
    split_string = [name.strip() for name in string.split(',')]
    connecting_words = ['del', 'de', 'la', 'y', '-', 'di']

    names = []

    if split_string == ['']: split_string = []

    for name in split_string:
        result = dict()
        name_split = name.split()

        result['primero'] = name_split[0]

        if len(name_split) == 1:
            result['apellido'] = 'N/A'

        elif len(name_split) == 2:
            result['apellido'] = name_split[1]

        else:
            if name_split[1] in connecting_words:
                result['apellido'] = ' '.join(name_split[1:])

            else:
                result['segundo'] = name_split[1]
                result['apellido'] = ' '.join(name_split[2:])

        names.append(result)

    return names


def insert_people(f, l1, l2, l3, entity, table_name, _id):
    template_people = 'INSERT INTO {} (primer_nombre, segundo_nombre, apellido) VALUES {};\n\n'
    template_insert = 'INSERT INTO {} ({}_id, obra_id) VALUES ({}, {});\n\n'

    d_id = 0

    check_list = l1 + l2 + l3
    my_list = []
    for i in range(len(check_list)):
        my_list.append(' '.join(list(list((check_list[i].values()))[0]['parse'].values())))

    D = defaultdict(list)
    for i, item in enumerate(my_list):
        D[item].append(i)

    D = {k: v for k, v in D.items() if len(v) > 1}
    to_do = [v for v in D.values()]

    for k, v in D.items():
        print('{}\'s repeat list (v): {}'.format(k, v))
        bucket = v[0]
        print('The bucket is therefore v[{}]: {}'.format(bucket, check_list[bucket][k]['obras']))

        if bucket < :
            for extension in v[1:]:
                curr = l1[bucket][k]['obras']

                if extension < :
                    pass

                elif extension < :
                    pass

                elif extension < :
                    # print('Adding to bucket the values in {}: {}'.format(extension, l3[extension - len(l2) - len(l1) - 1][k]['obras']))
                    # l1[bucket][k]['obras'] = curr + l3[extension - len(l2) - len(l1) - 1][k]['obras']
                    # del(l3[extension - len(l2) - len(l1) - 1])
                    
        elif bucket < :
            for extension in v[1:]:
                curr = l1[bucket][k]['obras']

                if extension < :
                    pass

                elif extension < :
                    pass

                elif extension < :

        else :
            for extension in v[1:]:
                curr = l1[bucket][k]['obras']

                if extension < :
                    pass

                elif extension < :
                    pass

                elif extension < :

    # for person in l1:
    #     d_id += 1
    #     for val in person.values():
    #         c = val['parse']
    #         primer_nombre = c.get('primero', '')
    #         segundo_nombre = c.get('segundo', '')
    #         apellido = c.get('apellido', '')
    #         obras = (val['obras'])
    #
    #     f.write(template_people.format(entity, (primer_nombre, segundo_nombre, apellido)))
    #
    #     for obra in obras:
    #         pass
    #         f.write(template_insert.format(table_name, _id, d_id, obra))
    #
    # for person in l2:
    #     d_id += 1
    #     for val in person.values():
    #         c = val['parse']
    #         primer_nombre = c.get('primero', '')
    #         segundo_nombre = c.get('segundo', '')
    #         apellido = c.get('apellido', '')
    #         obras = (val['obras'])
    #
    #     f.write(template_people.format(entity, (primer_nombre, segundo_nombre, apellido)))
    #
    #     for obra in obras:
    #         pass
    #         f.write(template_insert.format(table_name, _id, d_id, obra))
    #
    # for person in l3:
    #     d_id += 1
    #     for val in person.values():
    #         c = val['parse']
    #         primer_nombre = c.get('primero', '')
    #         segundo_nombre = c.get('segundo', '')
    #         apellido = c.get('apellido', '')
    #         obras = (val['obras'])
    #
    #     f.write(template_people.format(entity, (primer_nombre, segundo_nombre, apellido)))
    #
    #     for obra in obras:
    #         pass
    #         f.write(template_insert.format(table_name, _id, d_id, obra))

def table_parse(f):
    results = dict()
    seen_names = dict()
    for key in column_dict.keys():
        results[key] = []

    for item in problem_columns:
        seen_names[item] = []

    wb = openpyxl.load_workbook(f)
    sh = wb.get_sheet_by_name('Sheet4')

    for i in range(1, sh.max_row + 1):
        for key in results.keys():
            v = sh.cell(row=i, column=column_dict[key]).value

            if key not in problem_columns:
                if v is not None and type(v) != int and v.isdigit():
                    v = int(v)

                results[key].append(v if v is not None else '')

            else:
                v = parse_names(v) if v is not None else ''
                if v != '':
                    for name in v:
                        full_name = ' '.join(list(name.values()))
                        if full_name not in seen_names[key]:
                            seen_names[key].append(full_name)
                            results[key].append({full_name: {'parse':name, 'obras':[i]}})

                        else:
                            for item in results[key]:
                                if full_name in item.keys():
                                    item[full_name]['obras'].append(i)
    return results


def make_database(t1, t2, t3):

    caja1 = t1['caja']
    prod1 = t1['prod']
    titulo1 = t1['titulo']
    year1 = t1['año']
    notas1 = t1['notas']
    teatro1 = [1] * len(caja1)
    directors1 = t1['director']
    autores1 = t1['autor']

    caja2 = t2['caja']
    prod2 = [i + prod1[-1] for i in range(1, len(t2['prod']))]
    titulo2 = t2['titulo']
    year2 = t2['año']
    notas2 = t2['notas']
    teatro2 = [2] * len(caja2)
    directors2 = t2['director']
    autores2 = t2['autor']


    caja3 = t3['caja']
    prod3 = [i + prod2[-1] for i in range(1, len(t2['prod']))]
    titulo3 = t3['titulo']
    year3 = t3['año']
    notas3 = t3['notas']
    teatro3 = [3] * len(caja3)
    directors3 = t3['director']
    autores3 = t3['autor']

    # Insert into Obras
    template_obras = 'INSERT INTO {} (teatro_id, caja, num_de_prod, titulo, año, notas) VALUES {};\n\n'

    payload1 = zip(teatro1, caja1, prod1, titulo1, year1, notas1)
    payload2 = zip(teatro2, caja2, prod2, titulo2, year2, notas2)
    payload3 = zip(teatro3, caja3, prod3, titulo3, year3, notas3)

    with open('query.sql', 'w') as f:
        f.write('INSERT INTO Teatros (teatro_id, nombre_teatro) VALUES (1, \'Teatro Comedieta\');\n\n')
        f.write('INSERT INTO Teatros (teatro_id, nombre_teatro) VALUES (2, \'Teatro Universitario\');\n\n')
        f.write('INSERT INTO Teatros (teatro_id, nombre_teatro) VALUES (3, \'Teatro Rodante\');\n\n')

        for query in list(payload1):
            f.write(template_obras.format('Obras', query))

        for query in list(payload2):
            f.write(template_obras.format('Obras', query))

        for query in list(payload3):
            f.write(template_obras.format('Obras', query))

        insert_people(f, directors1, directors2, directors3, 'Directores', 'Directores_de_Obras', 'director')
        # insert_people(autores1, autores2, autores3)


if __name__ == '__main__':
    comedieta = table_parse('comedieta.xlsx')
    universitario = table_parse('universitario.xlsx')
    rodante = table_parse('rodante.xlsx')

    make_database(comedieta, universitario, rodante)

    print("Parse complete\n")
