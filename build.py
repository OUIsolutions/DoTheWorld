
import CToolKit as ct
from shutil import copytree,rmtree
from os import remove,makedirs
from os import listdir
from os.path import isdir


STARTER = 'doTheWorld/doTheWorldMain.h'
OUTPUT_TEST = 'tests/doTheWorld_test.h'
OUTPUT = 'doTheWorld.h'



ct.generate_amalgamated_code(STARTER,OUTPUT_TEST)

#test = ct.FolderTestPreset(folder='tests/main_test',side_effect_folder='tests/target')
#test.generate_ouptut()
#test.start_test()


rmtree('exemples',ignore_errors=True)
elements = listdir('tests/main_test')

def move_all_c(destination:str,current_path:str):
    elements = listdir(current_path)
    for e in elements:
        path = f'{current_path}/{e}'

        if isdir(path):
            move_all_c(path,path)
            continue

        if e.endswith('.c') or e.endswith('.cpp'):
            print(path)
            with open(path,'r') as arq:
                content = arq.read()
                content = content.replace(f'../../{OUTPUT_TEST}',OUTPUT)
                content = content.replace(f'../../../{OUTPUT_TEST}',OUTPUT)


for e in elements:
    path = f'tests/main_test/{e}'
    if isdir(path):
        makedirs(f'exemples/{e}')
        move_all_c(path,path)


'''
def modifier(text:str):
    return text.replace(f'../../{OUTPUT_TEST}',OUTPUT).replace(f'../../../{OUTPUT_TEST}',OUTPUT)

ct.include_code_in_markdown('README.md',save_file=True,modifier=modifier)
ct.generate_amalgamated_code(STARTER,OUTPUT)


'''



