
import Build.CToolKit as ct
from shutil import copytree,rmtree
from os import remove,makedirs
from os import listdir
from os.path import isdir,dirname

STARTER = 'doTheWorld/doTheWorldMain.h'
TEST_NAME  = 'doTheWorld_test.h'

OUTPUT_TEST = 'tests/doTheWorld_test.h'
OUTPUT = 'doTheWorld.h'





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



def create_exemples():
    rmtree('exemples',ignore_errors=True)
    elements = listdir('tests/main_test')
    for e in elements:
        path = f'tests/main_test/{e}'
        if isdir(path):
            dest = f'exemples/{e}'
            makedirs(dest)
            move_all_c(dest,path)



def create_full_folder_file_to_zip(folder:str = None):    
    content = listdir(folder)
    for c in content:
        if c.startswith('.'):
            continue



ct.generate_amalgamated_code(STARTER,OUTPUT_TEST)
test = ct.FolderTestPreset(folder='tests/main_test',side_effect_folder='tests/target')
test.generate_ouptut()
test.start_test()
ct.include_code_in_markdown('README.md',save_file=True)
ct.generate_amalgamated_code(STARTER,OUTPUT)

create_exemples()

