from os import listdir
from os.path import isdir
#from shutil import makedirs

content  = listdir('exemples')

for c in content:
    path = f'exemples/{c}'
    for p in listdir(path):
        caminho_do_arquivo = f'{path}/{p}'
        nova_pasta = f'{path.replace("exemples","tests/main_test")}/T_{p.replace(".c","")}'
        novo_caminho = f'{nova_pasta}/exec.c'
        if isdir(nova_pasta):
            print('ja existe',nova_pasta)
            continue 
        #fazendo alteracoes