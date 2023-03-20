from sys import argv
from os import system

formated = ''

def format_path(path:str) -> str:
    CHARS_TO_REMOVE = ['"','\n']
    for char in CHARS_TO_REMOVE:
        path = path.replace(char,'')
    return f'doTheWorld/{path}'


def copile_lib(main_file:str,out_name:str):
    formated = ''
    with open(f'doTheWorld/{main_file}','r') as f:
        
        lines = f.readlines()
        for line in lines:
            separated = line.split(' ')
            if len(separated) > 1:
                #verify if is #include 
                if separated[0] == '#include':
                
                    formated_path = format_path(separated[1])
                    with open(formated_path,'r') as inc:
                        formated += inc.read() + '\n'
                        continue
            formated += line

    with open(out_name,'w') as f:
        f.write(formated)


copile_lib('doTheWorldMain.c','doTheWorld.c')



