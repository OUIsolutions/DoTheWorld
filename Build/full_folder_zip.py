from os.path import isdir
from os import listdir
from os import getcwd
from os import makedirs
from shutil import rmtree
def create_full_folder_cleared(folder:str,dest:str):    
    content = listdir(folder)
    for c in content:
        path = f'{folder}/{c}'
        path = path.replace(getcwd() + '/','')
        if c.startswith('.'):
            continue
        if c.startswith('__pycache__'):
            continue

        if c == 'main.c':
            continue

        if c.endswith('.out'):
            continue
        
 
        if isdir(path):
            makedirs(f'{dest}/{path}')
            create_full_folder_cleared(path,dest)
        else:
            print(path)


def zip_folder():
    rmtree('outfolder',ignore_errors=True)
    create_full_folder_cleared(getcwd(),'out_folder')