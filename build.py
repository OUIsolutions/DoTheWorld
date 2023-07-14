
import Build.CToolKit as ct
from Build.exemple_build import create_exemples
from Build.full_folder_zip import zip_folder


STARTER = 'doTheWorld/doTheWorldMain.h'
TEST_NAME  = 'doTheWorld_test.h'

OUTPUT_TEST = 'tests/doTheWorld_test.h'
OUTPUT = 'doTheWorld.h'
ZIP_NAME ='DoTheWorld'


ct.generate_amalgamated_code(STARTER,OUTPUT_TEST)
test = ct.FolderTestPreset(folder='tests/main_test',side_effect_folder='tests/target')
test.generate_ouptut()
test.start_test()
ct.include_code_in_markdown('README.md',save_file=True)
ct.generate_amalgamated_code(STARTER,OUTPUT)

create_exemples(TEST_NAME,OUTPUT)

zip_folder(ZIP_NAME)