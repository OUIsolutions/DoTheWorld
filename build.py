
import CToolKit as ct
from shutil import copytree,rmtree
from os import remove




STARTER = 'doTheWorld/doTheWorldMain.h'
OUTPUT_TEST = 'doTheWorld_test.h'



def execute_test_for_folder():
    pass
def  execute_all_tests():
    pass

ct.generate_amalgamated_code(STARTER,OUTPUT_TEST)

execute_all_tests()
except Exception as e:
    print(e)





