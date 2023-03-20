

bool test_monodimension_listage(){

    puts("Testing monodimension listage-------------------------------------");
    puts("Testing dtw_list_basic");
    struct DtwStringArray *expected1  = dtw_constructor_string_array();
    #ifdef _WIN32
    expected1->add_string(expected1, "static\\deer.jpg");
    expected1->add_string(expected1, "static\\exemple.txt");
    #else
    expected1->add_string(expected1, "static/deer.jpg");
    expected1->add_string(expected1, "static/exemple.txt");
    #endif
    struct DtwStringArray *list1 = dtw_list_basic("static",DTW_FILE_TYPE,DTW_CONCAT_PATH);
    

    
    for (int i = 0; i < expected1->size; i++)
    {   
        int index1 = list1->find_position(list1,expected1->strings[i]);
        if(index1 == -1){
            puts("testing dtw_list_basic for files concatting path failed");
            return false;
        }
    }


    puts("Testing dtw_list_basic  for files concatting path passed");
    list1->free_string_array(list1);
    expected1->free_string_array(expected1);

    struct DtwStringArray *expected2  = dtw_constructor_string_array();
    
    expected2->add_string(expected2, "deer.jpg");
    expected2->add_string(expected2, "exemple.txt");

    struct DtwStringArray *list2 = dtw_list_basic("static",DTW_FILE_TYPE,DTW_NOT_CONCAT_PATH);
  
    
    for (int i = 0; i < expected2->size; i++){   
        int index = list2->find_position(list2,expected2->strings[i]);
        if(index == -1){
            puts("testing dtw_list_basic for files  not concatting path failed");
            return false;
        }
    }
    puts("Testing dtw_list_basic not for files  concatting path passed");
    list2->free_string_array(list2);
    expected2->free_string_array(expected2);
  
    struct DtwStringArray *expected3  = dtw_constructor_string_array();
    #ifdef _WIN32
    expected3->add_string(expected3, "static\\a\\");
    expected3->add_string(expected3, "static\\b\\");
    #else
    expected3->add_string(expected3, "static/a/");
    expected3->add_string(expected3, "static/b/");
    #endif
    struct DtwStringArray *list3 = dtw_list_basic("static",DTW_FOLDER_TYPE,DTW_CONCAT_PATH);
    
    
    for (int i = 0; i < expected3->size; i++){   
        int index = list3->find_position(list3,expected3->strings[i]);
        if(index == -1){
            puts("testing dtw_list_basic for folders concatting path failed");
            return false;
        }
    }
    puts("Testing dtw_list_basic for folders concatting path passed");
    
    list3->free_string_array(list3);
    expected3->free_string_array(expected3);
    
    struct DtwStringArray *expected4  = dtw_constructor_string_array();
    #ifdef _WIN32
        expected4->add_string(expected4, "a\\");
        expected4->add_string(expected4, "b\\");
    #else
        expected4->add_string(expected4, "a/");
        expected4->add_string(expected4, "b/");
    #endif
    struct DtwStringArray *list4 = dtw_list_basic("static",DTW_FOLDER_TYPE,DTW_NOT_CONCAT_PATH);
    for (int i = 0; i < expected4->size; i++){   
        int index = list4->find_position(list4,expected4->strings[i]);
        if(index == -1){
            puts("testing dtw_list_basic for folders not concatting path failed");
            return false;
        }
    }
    puts("Testing dtw_list_basic for folders not concatting path passed");
    list4->free_string_array(list4);
    expected4->free_string_array(expected4);
    return true;
    
}