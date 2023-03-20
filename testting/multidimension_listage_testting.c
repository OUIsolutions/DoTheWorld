

bool test_multidimension_listage(){
    puts("Testing multidimension listage-------------------------------------");

    puts("Tessting dtw_list_dirs_recursively ");
    
    struct DtwStringArray  *expected = dtw_constructor_string_array();
  
    #ifdef _WIN32
        expected->add_string(expected, "static\\");
        expected->add_string(expected, "static\\a\\");
        expected->add_string(expected, "static\\b\\");
    #else
        expected->add_string(expected, "static/");
        expected->add_string(expected, "static/a/");
        expected->add_string(expected, "static/a/b/");
    #endif
    struct DtwStringArray *list = dtw_list_dirs_recursively("static");

    for(int i = 0; i < list->size; i++){
        int index = expected->find_position(expected,list->strings[i]);
        if(index == -1){
            puts("testing dtw_list_dirs_recursively failed");
            return false;
        }
    }
    
    puts("testing dtw_list_dirs_recursively passed");
     
    
    list->free_string_array(list);
    expected->free_string_array(expected);

    puts("Tessting dtw_list_files_recursively ");

    struct DtwStringArray  *expected2 = dtw_constructor_string_array();
    #ifdef _WIN32
        expected2->add_string(expected2, "static\\deer.jpg");
        expected2->add_string(expected2, "static\\exemple.txt");
        expected2->add_string(expected2, "static\\a\\a.txt");
        expected2->add_string(expected2, "static\\a\\b.txt");
        expected2->add_string(expected2, "static\\b\\a.txt");
        expected2->add_string(expected2, "static\\b\\b.txt");

     
    #else
        expected2->add_string(expected2, "static/deer.jpg");
        expected2->add_string(expected2, "static/exemple.txt");
        expected2->add_string(expected2, "static/a/a.txt");
        expected2->add_string(expected2, "static/a/b.txt");
        expected2->add_string(expected2, "static/b/a.txt");
        expected2->add_string(expected2, "static/b/b.txt");
    #endif
    struct DtwStringArray *list2 = dtw_list_files_recursively("static");
    
    for(int i = 0; i < list2->size; i++){
        int index = expected2->find_position(expected2,list2->strings[i]);
        if(index == -1){
            puts("testing dtw_list_files_recursively failed");
            return false;
        }
    }
    puts("testing dtw_list_files_recursively passed");
    list2->free_string_array(list2);
    expected2->free_string_array(expected2);
    puts("Tessting dtw_list_all_recursively ");
    struct DtwStringArray  *expected3 = dtw_constructor_string_array();
    #ifdef _WIN32
        expected3->add_string(expected3, "static\\");
        expected3->add_string(expected3, "static\\a\\");
        expected3->add_string(expected3, "static\\a\\a.txt");
        expected3->add_string(expected3, "static\\a\\b.txt");
        expected3->add_string(expected3, "static\\b\\");
        expected3->add_string(expected3, "static\\b\\a.txt");
        expected3->add_string(expected3, "static\\b\\b.txt");
        expected3->add_string(expected3, "static\\deer.jpg");
        expected3->add_string(expected3, "static\\exemple.txt");
    #else
        expected3->add_string(expected3, "static/");
        expected3->add_string(expected3, "static/a/");
        expected3->add_string(expected3, "static/a/a.txt");
        expected3->add_string(expected3, "static/a/b.txt");
        expected3->add_string(expected3, "static/b/");
        expected3->add_string(expected3, "static/b/a.txt");
        expected3->add_string(expected3, "static/b/b.txt");
        expected3->add_string(expected3, "static/deer.jpg");
        expected3->add_string(expected3, "static/exemple.txt");
    #endif
    struct DtwStringArray *list3 = dtw_list_all_recursively("static");

    for(int i = 0; i < list3->size; i++){
        int index = expected3->find_position(expected3,list3->strings[i]);
        if(index == -1){
            puts("testing dtw_list_all_recursively failed");
            return false;
        }
    }
    puts("testing dtw_list_all_recursively passed");
    list3->free_string_array(list3);
    expected3->free_string_array(expected3);
    return true;
} 
