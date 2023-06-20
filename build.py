
import CToolKit as ct
from shutil import copytree,rmtree
from os import remove




STARTER = 'doTheWorld/doTheWorldMain.h'
OUTPUT_TEST = 'doTheWorld_test.h'

ct.generate_amalgamated_code(STARTER,OUTPUT_TEST)

try:
    ct.execute_test_for_folder('gcc','exemples/io/')
    ct.generate_amalgamated_code(STARTER,'doTheWorld.h')
except Exception as e:
    print(e)





