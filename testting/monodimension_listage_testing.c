

bool test_monodimension_listage(){

    puts("Testing monodimension listage-------------------------------------");
    puts("Testing dtw_list_basic");
    struct DtwStringArray *expected_first  = dtw_constructor_string_array();
    expected_first->add_string(expected_first, "static\\deer.jpg");
    expected_first->add_string(expected_first, "static\\exemple.txt");
    
    struct DtwStringArray *list = dtw_list_basic("static",DTW_FILE_TYPE,DTW_CONCAT_PATH);
  
    
    for (int i = 0; i < expected_first->size; i++)
    {   
        int index = list->find_position(list,expected_first->strings[i]);
        if(index == -1){
            puts("testing dtw_list_basic for files concatting path failed");
            return false;
        }
    }
    puts("Testing dtw_list_basic  for files concatting path passed");
    list->free_string_array(list);
    expected_first->free_string_array(expected_first);

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
    expected_third->add_string(expected_third, "static\\a/");
    expected_third->add_string(expected_third, "static\\b/");

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
    
    return true;
}