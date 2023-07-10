from os import listdir


content  = listdir('exemples')

for c in content:
    path = f'exemples/{c}'
    for p in listdir(path):
        pasta  = f'{path.replace("exemples","tests/main_test")}/T_{p.replace(".c","")}'
        
        print(pasta)