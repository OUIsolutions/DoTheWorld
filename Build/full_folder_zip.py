from os.path import isdir
from os import listdir

def create_full_folder_cleared(folder:str,dest:str):    
    content = listdir(folder)
    for c in content:
        path = f'{folder}/{c}'
        if c.startswith('.'):
            continue
        if c.startswith('__pycache__'):
            continue
 
        if isdir(path):
            return create_full_folder_cleared(path,dest)

        print(c)


def zip_folder():
    pass 