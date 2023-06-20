
import CToolKit as ct
from shutil import copytree,rmtree
from os import remove,makedirs
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
            rmtree('exemple_folder',ignore_errors=True)
            copytree('security','exemple_folder')
            rmtree('security',ignore_errors=True)
        else:
            try:
                ct.execute_test_for_file('gcc',f'{folder}/{file}')
            except Exception as e:
                print('failuired: ',file)
                raise e

        print('passed:',file)


def  execute_all_tests():
    execute_test_for_folder('exemples/io')
    execute_test_for_folder('exemples/monodimension_listage')
    execute_test_for_folder('exemples/multidimension_listage')
    execute_test_for_folder('exemples/extras')
    execute_test_for_folder('exemples/path')
    execute_test_for_folder('exemples/tree_parts')
    execute_test_for_folder('exemples/trees')



def create_readme_files_of_folder(folder:str):

    files = listdir(folder)
    for file in files:
        with open(f'{folder}/{file}','r') as arq:
            formated = arq.read().replace('../../doTheWorld_test.h','doTheWorld.h')
            with open(f'readme_exemples/{file}','w') as narq:
                narq.write(formated)

def generate_exemple_formated_for_readme():
    rmtree('readme_exemples',ignore_errors=True)
    makedirs('readme_exemples')
    create_readme_files_of_folder('exemples/extras')
    create_readme_files_of_folder('exemples/io')
    create_readme_files_of_folder('exemples/monodimension_listage')
    create_readme_files_of_folder('exemples/multidimension_listage')
    create_readme_files_of_folder('exemples/path')
    create_readme_files_of_folder('exemples/tree_parts')
    create_readme_files_of_folder('exemples/trees')


ct.generate_amalgamated_code(STARTER,OUTPUT_TEST)
execute_all_tests()
generate_exemple_formated_for_readme()
#ct.include_code_in_markdown('README.md',True)
ct.generate_amalgamated_code(STARTER,'doTheWorld.h')






