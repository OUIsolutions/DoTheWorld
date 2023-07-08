
import CToolKit as ct
from shutil import copytree,rmtree
from os import remove,makedirs
from os import listdir
from os.path import isdir


STARTER = 'doTheWorld/doTheWorldMain.h'
OUTPUT_TEST = 'tests/doTheWorld_test.h'
OUTPUT = 'doTheWorld.h'



def execute_test_for_folder():
    ct.execute_test_for_folder('tests/readonly')


ct.generate_amalgamated_code(STARTER,OUTPUT_TEST)
test = ct.FolderTestPresset(folder='tests/main_test')
test.start_test()



'''
def modifier(text:str):
    return text.replace(f'../../{OUTPUT_TEST}',OUTPUT)

ct.include_code_in_markdown('README.md',save_file=True,modifier=modifier)
ct.generate_amalgamated_code(STARTER,OUTPUT)


'''



