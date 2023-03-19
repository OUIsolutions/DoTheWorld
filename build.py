from sys import argv
from os import system

formated = ''

def format_path(path:str) -> str:
    CHARS_TO_REMOVE = ['"','\n']
    for char in CHARS_TO_REMOVE:
        path = path.replace(char,'')
    return f'doTheWorld/{path}'

with open('doTheWorld/doTheWorldMain.c','r') as f:
    
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

with open('doTheWorld.c','w') as f:
    f.write(formated)

if 'copile' in argv:

    #make an gcc and c++ copilation 
    result_c = system('gcc main.c ')
    if result_c != 0:
        print('gcc failed')

    result_cpp = system('g++ main.c ')
    if result_cpp != 0:
        print('g++ failed')

    print('Compilation finished')