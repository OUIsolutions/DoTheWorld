
import json 

with open("teste.json","r") as arq:
    content = json.load(arq)


print( content['age'])
print(content['name'])

for i in content['elements']:
    if isinstance(i,dict):
        print(i['categories'])
    else:
        print(i)