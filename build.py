
import CToolKit as ct
from os import remove
from testing.test_io import  test_io_operations



from testing.test_io import test_io_operations
STARTER = 'doTheWorld/doTheWorldMain.h'
OUTPUT_TEST = 'doTheWorld_test.h'

ct.generate_amalgamated_code(STARTER,OUTPUT_TEST)
try:
    test_io_operations()
    ct.generate_amalgamated_code(STARTER,'doTheWorld.h')
except Exception as e:
    print(e)
    remove(OUTPUT_TEST)

try:
    remove(OUTPUT_TEST)
except:pass

