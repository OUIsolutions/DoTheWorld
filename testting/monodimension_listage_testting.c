

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
    struct DtwStringArray *list = dtw_list_basic("static",DTW_FILE_TYPE,DTW_CONCAT_PATH);
    

    
    for (int i = 0; i < expected1->size; i++)
    {   
        int index = list->find_position(list,expected1->strings[i]);
        if(index == -1){
            puts("testing dtw_list_basic for files concatting path failed");
            return false;
        }
    }


    puts("Testing dtw_list_basic  for files concatting path passed");
    list->free_string_array(list);
    expected1->free_string_array(expected1);

    struct DtwStringArray *expected_second  = dtw_constructor_string_array();
    
    expected_second->add_string(expected_second, "deer.jpg");
    expected_second->add_string(expected_second, "exemple.txt");

    struct DtwStringArray *list2 = dtw_list_basic("static",DTW_FILE_TYPE,DTW_NOT_CONCAT_PATH);
  
    
    for (int i = 0; i < expected_second->size; i++){   
        int index = list2->find_position(list2,expected_second->strings[i]);
        if(index == -1){
            puts("testing dtw_list_basic for files  not concatting path failed");
            return false;
        }
    }
    puts("Testing dtw_list_basic not for files  concatting path passed");
    list2->free_string_array(list2);
    expected_second->free_string_array(expected_second);
  
    struct DtwStringArray *expected_third  = dtw_constructor_string_array();
    #ifdef _WIN32
    expected_third->add_string(expected_third, "static\\a\\");
    expected_third->add_string(expected_third, "static\\b\\");
    #else
    expected_third->add_string(expected_third, "static/a/");
    expected_third->add_string(expected_third, "static/b/");
    #endif
    struct DtwStringArray *list3 = dtw_list_basic("static",DTW_FOLDER_TYPE,DTW_CONCAT_PATH);
    
    
    for (int i = 0; i < expected_third->size; i++){   
        int index = list3->find_position(list3,expected_third->strings[i]);
        if(index == -1){
            puts("testing dtw_list_basic for folders concatting path failed");
            return false;
        }
    }
    puts("Testing dtw_list_basic for folders concatting path passed");
    
    list3->free_string_array(list3);
    expected_third->free_string_array(expected_third);
    
    struct DtwStringArray *expected_fourth  = dtw_constructor_string_array();
    #ifdef _WIN32
        expected_fourth->add_string(expected_fourth, "a\\");
        expected_fourth->add_string(expected_fourth, "b\\");
    #else
        expected_fourth->add_string(expected_fourth, "a/");
        expected_fourth->add_string(expected_fourth, "b/");
    #endif
    struct DtwStringArray *list4 = dtw_list_basic("static",DTW_FOLDER_TYPE,DTW_NOT_CONCAT_PATH);
    for (int i = 0; i < expected_fourth->size; i++){   
        int index = list4->find_position(list4,expected_fourth->strings[i]);
        if(index == -1){
            puts("testing dtw_list_basic for folders not concatting path failed");
            return false;
        }
    }
    puts("Testing dtw_list_basic for folders not concatting path passed");
    list4->free_string_array(list4);
    expected_fourth->free_string_array(expected_fourth);
    return true;
    
}