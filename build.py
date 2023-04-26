from jinja2 import Environment, FileSystemLoader


def main():

    env = Environment(loader=FileSystemLoader('doTheWorld'))
    template = env.get_template('doTheWorldMain.j2')

    complete = template.render(lite=False)
    with open('doTheWorld.h', 'w') as f:
        f.write(complete)
    lite_version = template.render(lite=True)
    with open('doTheWorldLite.h', 'w') as f:
        f.write(lite_version)
main()


