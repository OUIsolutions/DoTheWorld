
import CToolKit as ct
from shutil import copytree,rmtree
from os import remove,makedirs
from os import listdir
from os.path import isdir


STARTER = 'doTheWorld/doTheWorldMain.h'
OUTPUT_TEST = 'doTheWorld_test.h'
OUTPUT = 'doTheWorld.h'


def execute_test_for_folder(folder:str):
    print(f'executing test for {folder}')
    files = listdir(folder)
    for file in files:
        #means its an destructive side effect script
        file_path = f'{folder}/{file}'

        if isdir(file_path):
            execute_test_for_folder(file_path)
            continue

        if '#destructive#' in file:
            rmtree('security',ignore_errors=True)
            copytree('exemple_folder','security')
            try:
                ct.execute_test_for_file('gcc',file_path)
            except Exception as e:
                rmtree('exemple_folder',ignore_errors=True)
                copytree('security','exemple_folder')
                rmtree('security',ignore_errors=True)
                print('failuired: ',file)
                raise e
            rmtree('exemple_folder',ignore_errors=True)
            copytree('security','exemple_folder')
            rmtree('security',ignore_errors=True)
        else:
            try:
                ct.execute_test_for_file('gcc',file_path)
            except Exception as e:
                print('\tfailuired: ',file)
                raise e

        print('\tpassed:',file)








ct.generate_amalgamated_code(STARTER,OUTPUT_TEST)
execute_test_for_folder('exemples')

def modifier(text:str):
    return text.replace(f'../../{OUTPUT_TEST}',OUTPUT)

ct.include_code_in_markdown('README.md',save_file=True,modifier=modifier)
ct.generate_amalgamated_code(STARTER,OUTPUT)






