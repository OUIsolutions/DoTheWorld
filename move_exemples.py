from os import listdir ,makedirs
from os.path import isdir,isfile
#from shutil import makedirs

content  = listdir('exemples')

for c in content:
    path = f'exemples/{c}'
    for p in listdir(path):
        caminho_do_arquivo = f'{path}/{p}'
        nova_pasta = f'{path.replace("exemples","tests/main_test")}/T_{p.replace(".c","")}'
        novo_caminho = f'{nova_pasta}/exec.c'
        if not  isdir(nova_pasta):
            makedirs(nova_pasta)

        if not isfile(novo_caminho):
            with open(caminho_do_arquivo,'r' ) as arq:
                conteudo = arq.read()
                with open(novo_caminho,'w') as arq:
                    arq.write(conteudo)
        
        