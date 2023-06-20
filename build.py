
import CToolKit as ct
from os import remove




STARTER = 'doTheWorld/doTheWorldMain.h'
OUTPUT_TEST = 'doTheWorld_test.h'

ct.generate_amalgamated_code(STARTER,OUTPUT_TEST)

ct.execute_test_for_folder('gcc','exemples/io/')



ct.generate_amalgamated_code(STARTER,'doTheWorld.h')

