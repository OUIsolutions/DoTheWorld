
import CToolKit as ct
from shutil import copytree,rmtree
from os import remove,makedirs
from os import listdir
from os.path import isdir,dirname

STARTER = 'doTheWorld/doTheWorldMain.h'
TEST_NAME  = 'doTheWorld_test.h'

OUTPUT_TEST = 'tests/doTheWorld_test.h'
OUTPUT = 'doTheWorld.h'



ct.generate_amalgamated_code(STARTER,OUTPUT_TEST)

test = ct.FolderTestPreset(folder='tests/main_test',side_effect_folder='tests/target')
test.generate_ouptut()
test.start_test()


rmtree('exemples',ignore_errors=True)
elements = listdir('tests/main_test')

def move_all_c(destination:str,current_path:str):
    elements = listdir(current_path)
    for e in elements:
        path = f'{current_path}/{e}'

        if isdir(path):
            move_all_c(destination,path)
            continue

        if e.endswith('.c') or e.endswith('.cpp'):
            with open(path,'r') as arq:
                content = arq.read()

                content = content.replace(f'../../../{TEST_NAME}',OUTPUT)
                content = content.replace(f'../../{TEST_NAME}',OUTPUT)

            name =dirname(path).split('/')[-1].replace('T_','')
            with open(f'{destination}/{name}.c','w') as arq2:
                arq2.write(content)


for e in elements:
    path = f'tests/main_test/{e}'
    if isdir(path):
        dest = f'exemples/{e}'
        makedirs(dest)
        move_all_c(dest,path)



ct.include_code_in_markdown('README.md',save_file=True)
ct.generate_amalgamated_code(STARTER,OUTPUT)





