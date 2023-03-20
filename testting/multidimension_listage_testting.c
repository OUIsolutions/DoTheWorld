

bool test_multidimension_listage(){
    puts("Testing multidimension listage-------------------------------------");

    puts("Tessting dtw_list_dirs_recursively ");
    
    struct DtwStringArray  *expected = dtw_constructor_string_array();
    expected->add_string(expected, "static/");
    #ifdef _WIN32
        expected->add_string(expected, "static\\a/");
        expected->add_string(expected, "static\\b/");
    #else
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
    list->represent(list);    
    
    list->free_string_array(list);
    expected->free_string_array(expected);

    puts("Tessting dtw_list_files_recursively ");

    struct DtwStringArray  *expected2 = dtw_constructor_string_array();
    expected2->add_string(expected2, "static/deer.jpg");
    expected2->add_string(expected2, "static/deer.jpg");
    expected2->add_string(expected2, "static/exemple.txt");

    struct DtwStringArray *list2 = dtw_list_files_recursively("static");
    list2->represent(list2);
    
} 