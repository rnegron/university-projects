import openpyxl, string
from openpyxl.utils import get_column_letter, column_index_from_string

def parse_names(string):
    split_string = [name.strip() for name in string.split(',')]
    connecting_words = ['del', 'de', 'la', 'y', '-']
    names = []

    for name in split_string:
        result = dict()
        name_split = name.split()
        result['first'] = name_split[0]

        if len(name_split) == 2:
            result['last'] = name_split[1]

        else:
            if name_split[1] in connecting_words:
                result['last'] = ' '.join(name_split[1:])

            else:
                result['middle'] = name_split[1]
                result['last'] = ' '.join(name_split[2:])

        names.append(result)

    return names


def comedieta_parse():
    START = 7
    # results_dict = dict()
    wb = openpyxl.load_workbook('comedieta.xlsx')
    sh = wb.get_sheet_by_name('Sheet4')



def rodante_parse():
    # results_dict = dict()
    wb = openpyxl.load_workbook('rodante.xlsx')
    sh = wb.get_sheet_by_name('Sheet4')

    # with open('rodante_results.txt', 'w+') as dump:
    #     pass


def universitario_parse():
    # results_dict = dict()
    wb = openpyxl.load_workbook('universitario.xlsx')
    sh = wb.get_sheet_by_name('Sheet4')




if __name__ == '__main__':
    pass
