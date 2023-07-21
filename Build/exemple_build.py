

from shutil import copytree
from shutil import rmtree
from os import remove,makedirs
from os import listdir
from os.path import isdir,dirname



def move_all_c(destination:str,current_path:str,test_name:str,output:str):
    elements = listdir(current_path)
    for e in elements:
        path = f'{current_path}/{e}'

        if isdir(path):
            move_all_c(destination,path,test_name,output)
            continue

        if e.endswith('.c') or e.endswith('.cpp'):
            with open(path,'r') as arq:
                content = arq.read()

                content = content.replace(f'../../../{test_name}',output)
                content = content.replace(f'../../{test_name}',output)
                content = content.replace(f'../{test_name}',output)


            name =dirname(path).split('/')[-1].replace('T_','')
            with open(f'{destination}/{name}.c','w') as arq2:
                arq2.write(content)



def create_exemples(test_name:str,output:str):
    rmtree('exemples',ignore_errors=True)
    elements = listdir('tests/main_test')
    for e in elements:
        path = f'tests/main_test/{e}'
        if isdir(path):
            dest = f'exemples/{e}'
            makedirs(dest)
            move_all_c(dest,path,test_name,output)
    makedirs('exemples/locker')        
    move_all_c('exemples/locker','tests/locker_test',test_name,output)
