
import CToolKit as ct
from shutil import copytree,rmtree
from os import remove
from os import listdir



STARTER = 'doTheWorld/doTheWorldMain.h'
OUTPUT_TEST = 'doTheWorld_test.h'



def execute_test_for_folder(folder:str):
    files = listdir(folder)
    for file in files:
        #means its an destructive side effect script
        if '#destructive#' in file:
            rmtree('security',ignore_errors=True)
            copytree('exemple_folder','security')
            try:
                ct.execute_test_for_file('gcc',f'{folder}/{file}')
            except Exception as e:
                rmtree('exemple_folder',ignore_errors=True)
                copytree('security','exemple_folder')
                rmtree('security',ignore_errors=True)
                print('failuired: ',file)
                raise e
        else:
            try:
                ct.execute_test_for_file('gcc',f'{folder}/{file}')
            except Exception as e:
                print('failuired: ',file)
                raise e

        print('passed:',file)


def  execute_all_tests():
    execute_test_for_folder('exemples/extras')
    execute_test_for_folder('exemples/io')
    execute_test_for_folder('exemples/monodimension_listage')
    execute_test_for_folder('exemples/multidimension_listage')

ct.generate_amalgamated_code(STARTER,OUTPUT_TEST)

execute_all_tests()

ct.generate_amalgamated_code(STARTER,'doTheWorld.h')






