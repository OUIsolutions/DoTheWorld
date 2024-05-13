from platform import system as osname
import Build.CToolKit as ct
from Build.exemple_build import create_exemples
from Build.locker_test import execute_locker_test

STARTER = 'src/one.c'
TEST_NAME = 'doTheWorld_test.h'


OUTPUT_TEST = 'tests/doTheWorld_test.h'
OUTPUT_FULL = 'doTheWorld.h'




ct.generate_amalgamated_code(STARTER,OUTPUT_TEST)
use_valgrind = True

if osname() == 'Windows':
    use_valgrind = False


test = ct.FolderTestPreset(
    folder='tests/main_test',
    side_effect_folder='tests/target',
    use_valgrind=use_valgrind,
    compilation_flags=["DDTW_DEBUG_TIME"]
    )

test.generate_ouptut(reconstruct=True)
test.start_test()
execute_locker_test()
create_exemples(TEST_NAME,OUTPUT_FULL)

ct.include_code_in_markdown('README.md',save_file=True)
ct.generate_amalgamated_code(STARTER,OUTPUT_FULL)

