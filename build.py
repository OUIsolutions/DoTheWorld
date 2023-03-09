from jinja2 import Template, Environment, FileSystemLoader
from os import system

env = Environment(loader=FileSystemLoader('code'))

template = env.get_template('doTheWorld.j2')

with open('doTheWorld.c','w') as f:
    f.write(template.render())

result  =system('g++ main.c')
if result == 0:
    print('Compilation successful')
  
else:
    print('Compilation failed')

