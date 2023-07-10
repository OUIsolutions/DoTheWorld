from os import listdir


content  = listdir('exemples')

for c in content:
    path = f'exemples/{c}'
    for p in listdir(path):
        novo_path = f'{path}/{p}'
        print(novo_path)