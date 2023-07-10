
import CToolKit as ct
from shutil import copytree,rmtree
from os import remove,makedirs
from os import listdir
from os.path import isdir


STARTER = 'doTheWorld/doTheWorldMain.h'
OUTPUT_TEST = 'tests/doTheWorld_test.h'
OUTPUT = 'doTheWorld.h'



ct.generate_amalgamated_code(STARTER,OUTPUT_TEST)

test = ct.FolderTestPreset(folder='tests/main_test',side_effect_folder='tests/target')
test.generate_ouptut()
test.start_test()

'''
rmtree('exemples',ignore_errors=True)
elements = listdir('tests/main_test')
for e in elements:
    if isdir(e):
        makedirs(f'exemples/{e}')


def modifier(text:str):
    return text.replace(f'../../{OUTPUT_TEST}',OUTPUT)

ct.include_code_in_markdown('README.md',save_file=True,modifier=modifier)
ct.generate_amalgamated_code(STARTER,OUTPUT)


'''



