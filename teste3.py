


from os import listdir
from os.path import  isdir

import hashlib



def generate_folder_hash(folder:str)->str:

    content = listdir(folder)
    content.sort()
    sha256 = hashlib.sha256()

    for c in content:
        path = f'{folder}/{c}'

        if isdir(path):
            sha256.update(generate_folder_hash(path).encode('utf8'))

        else:
            with open(path,'rb') as arq:
                sha256.update(arq.read())

    return sha256.hexdigest()


def are_folders_equal(folder1,folder2)->bool:
    hash1 =  generate_folder_hash(folder1)
    hash2 = generate_folder_hash(folder2)
    return hash1 == hash2




r = are_folders_equal('tests/target','tests/main_test/extras/T_converting_b64_to_binary/side_effect')
print(r)
