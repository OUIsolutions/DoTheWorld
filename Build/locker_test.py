
from .CToolKit.comand_line_functions import compile_project
from .CToolKit.ComandLineExecution import ComandLineExecution
from platform import system as osname
from os import remove


def execute_locker_test():
    
    out = compile_project('tests/locker_test/locker_test.c')
    for i in range(0,10):
        r = ComandLineExecution(f'valgrind ./{out}')
        
        try:
            with open('tests/target/append.txt','r') as arq:
                content = arq.read()
                lines = content.split('\n')
                if len(lines) != 11:
                    raise Exception('locker overwritten information')
                try:
                    remove('tests/target/append.txt')
                except:pass     
        except Exception as e:
            try:
                remove('tests/target/append.txt')
                pass 
            except:pass 
            raise e
        
        if 'Rerun with --leak-check' in r.output:
            raise Exception('leaks on loker')
        
        replaced = r.output.replace('ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)','')
        if 'ERROR SUMMARY' in replaced: 
            raise Exception('Errors on locker')
        print(f"test  locker:{i} passed")

    print('passed: locker_tests.c')
        
