

from os import listdir
from os.path import  isdir


def count_elements(content:str or bytes):
    result  = {}
    for x in content:
        try:
            result[x]+=1
        except KeyError:
            result[x]=1
    return result


def convert_to_positive(element:int)->int:
    if element == 0:
        return 0
    
    if element < 0:
        return element * -1 
    
    return element

def get_content_similarity(content:str or bytes , content2:str or bytes)->str:
    
    value1 = count_elements(content)
    value2 = count_elements(content2)
    
    diference = 0
    counted = []
    for element in value1:
        
        counted.append(element)

        total1  = value1[element]
        try:
            total2 = value2[element]
            diference+= convert_to_positive(total1 -total2)
        
        except KeyError:
            diference += total1

    for element in value2:
        if element in counted:
            continue 
        total2 = value2[element]
        try:
            total1 = value1[element]
            diference+= convert_to_positive(total1 -total2)
        except KeyError:
            diference+=total2


    median_size = int((len(content) + len(content2)) / 2) 
    equals = median_size - diference
    similarity = (equals / median_size) * 100
    return similarity

    
def get_files_similarity(path1:str,path2:str)->int:
    with open(path1,'rb') as arq:
        content1 = arq.read()


    with open(path2,'rb') as arq:
        content2 = arq.read()
    
    return get_content_similarity(content1,content2)


def are_folders_equal(folder1:str,folder2:str,bytes_tolerance=0.99,string_tolerance=1)->bool:
    x = get_files_similarity(f'{folder1}/blob.png',f'{folder2}/blob2.png')
    print(x)

r = are_folders_equal('tests/target','tests/main_test/extras/T_converting_b64_to_binary/side_effect')

