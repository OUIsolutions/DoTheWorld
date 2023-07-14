from os.path import isdir
from os import listdir
from os import getcwd
from os import makedirs
from shutil import rmtree,make_archive
import zipfile

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
        if c == dest:
            continue
        
 
        if isdir(path):
            makedirs(f'{dest}/{path}')
            create_full_folder_cleared(path,dest)
        else:
            
            with open(path,'rb' ) as arq:
                content = arq.read()
            
            with open(f'{dest}/{path}','wb') as arq:
                arq.write(content)
            

def zip_folder():
    out_name = 'out_name'
    rmtree(out_name,ignore_errors=True)
    makedirs(out_name)
    create_full_folder_cleared(getcwd(),out_name)
    make_archive('DoTheWorld','zip',out_name)