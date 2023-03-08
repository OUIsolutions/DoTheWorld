from jinja2 import Template


with open('template.j2','r') as f:
    template = Template(f.read())

with open('DoTheWorld.h','w') as f:
    f.write(template.render())