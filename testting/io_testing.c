
bool verify_if_is_test_equal_to_static(){
    struct DtwStringArray *static_files = dtw_constructor_string_array();
    #ifdef _WIN32
        static_files->add_string(static_files, "test\\");
        static_files->add_string(static_files, "test\\a\\");
        static_files->add_string(static_files, "test\\a\\a.txt");
        static_files->add_string(static_files, "test\\a\\b.txt");
        static_files->add_string(static_files, "test\\b\\");
        static_files->add_string(static_files, "test\\b\\a.txt");
        static_files->add_string(static_files, "test\\b\\b.txt");
        static_files->add_string(static_files, "test\\deer.jpg");
        static_files->add_string(static_files, "test\\exemple.txt");
    #else
        static_files->add_string(static_files, "test/");
        static_files->add_string(static_files, "test/a/");
        static_files->add_string(static_files, "test/a/a.txt");
        static_files->add_string(static_files, "test/a/b.txt");
        static_files->add_string(static_files, "test/b/");
        static_files->add_string(static_files, "test/b/a.txt");
        static_files->add_string(static_files, "test/b/b.txt");
        static_files->add_string(static_files, "test/deer.jpg");
        static_files->add_string(static_files, "test/exemple.txt");
    #endif
    struct DtwStringArray *files = dtw_list_all_recursively("test");

    for(int i = 0; i < files->size; i++){
        if(!static_files->find_position(static_files, files->strings[i])== -1){
            puts("Test is not equal to static");
            return false;
        }
    }
    return true;
}
bool  test_io_operations(){
    puts("Testing io operations--------------------------------------------");
    //testing create dir------------------------------------------------------- 
    dtw_create_dir("test");
    int entity_type1 = dtw_entity_type("test");
    if(entity_type1 == DTW_FOLDER_TYPE){
        puts("Created dir passed");
    }else{
        puts("Created dir failed");
        return false;
    }

    //testing create dir recursivly---------------------------------------------
    dtw_create_dir_recursively("test/test2/test3/test4");
    int entity_type2 = dtw_entity_type("test/test2/test3/test4");
    if(entity_type2 == DTW_FOLDER_TYPE){
        puts("Created dir recursivly passed");
    }else{
        puts("Created dir recursivly failed");
        return false;
    }

    //testing remove any -------------------------------------------------------
    dtw_remove_any("test");
    int entity_type3 = dtw_entity_type("test");
    if(entity_type3 == DTW_NOT_FOUND){
    puts("Remove any passed");
    }else{
    puts("Remove any failed");
    return false;
    }

    //testing load any content -------------------------------------------------
    int size4 = 0;
    bool is_binary4 = false;
    unsigned char *content4 = dtw_load_any_content("static/deer.jpg", &size4, &is_binary4);
    if(content4 != NULL){
        puts("Load any content passed");
    }else{
        puts("Load any content failed");
        return false;
    }
    free(content4);
    //testing load string file content -----------------------------------------

    char *content5 = dtw_load_string_file_content("static/exemple.txt");
    if( strcmp(content5,"Working!") == 0){
        puts("Load string file content passed");
    }else{
        puts("Load string file content failed");
        return false;
    }
    free(content5);
    //testing write any content-------------------------------------------------
    //load the deer.jpg content and write it 
    int size6 = 0;
    bool is_binary6 = false;
    unsigned char *content6 = dtw_load_any_content("static/deer.jpg", &size6, &is_binary6);
    bool result6 = dtw_write_any_content("test/deer.jpg", content6, size6);
    //load test/deer.jpg content and compare it with deer.jpg content
    int size7 = 0;
    bool is_binary7 = false;
    unsigned char *content7 = dtw_load_any_content("test/deer.jpg", &size7, &is_binary7);
    if(result6 && size6 == size7 && is_binary6 == is_binary7){
        puts("Write any content passed");
    }else{
        puts("Write any content failed");
        dtw_remove_any("test");
        return false;
    }
    free(content6);
    free(content7);
    dtw_remove_any("test");

    //testing write string file content-----------------------------------------
    int result8 = dtw_write_string_file_content("test/exemple.txt","Working!");
    char *content8 = dtw_load_string_file_content("test/exemple.txt");
    if(result8 && strcmp(content8,"Working!") == 0){
        puts("Write string file content passed");
    }else{
        puts("Write string file content failed");
        dtw_remove_any("test");
        return false;
    }
    free(content8);
    dtw_remove_any("test");

    //testing loading binary content--------------------------------------------
    int size9 = 0;
    unsigned char *content9 = dtw_load_binary_content("static/deer.jpg", &size9);
    if(content9 != NULL){
        puts("Load binary file content passed");
    }else{
        puts("Load binary file content failed");
        dtw_remove_any("test");
        return false;
    }
    dtw_remove_any("test");
    free(content9);

    //testing copy any----------------------------------------------------------
    //testing for file 
    bool result10 = dtw_copy_any("static/deer.jpg","test/deer.jpg",false);
    int size10 = 0;
    bool is_binary10 = false;
    unsigned char *content10 = dtw_load_any_content("test/deer.jpg", &size10, &is_binary10);
    if(result10 && content10 != NULL){
        puts("Copy any passed with files");
    } else{
        puts("Copy any failed with files");
        dtw_remove_any("test");
        return false;
    }
    free(content10);
    dtw_remove_any("test");

    //testing for folder--------------------------------------------------------
    bool result11 = dtw_copy_any("static","test",false);
    if(result11 && verify_if_is_test_equal_to_static()){
        puts("Copy any passed with folders");
    } else{
        puts("Copy any failed with folders");
        dtw_remove_any("test");
        return false;
    }
    dtw_remove_any("test");
    //testing move any----------------------------------------------------------
    //testing for file
    dtw_copy_any("static/deer.jpg","test/deer.jpg",false);
    dtw_move_any("test/deer.jpg","test2/deer.jpg",DTW_NOT_MERGE);
    //verify if the origin were removed 
    int entity_type12 = dtw_entity_type("test/deer.jpg");
    
    int size12 = 0;
    bool is_binary12 = false;
    unsigned char *content12 = dtw_load_any_content("test2/deer.jpg", &size12, &is_binary12);
    
    if(entity_type12 == DTW_NOT_FOUND && content12 != NULL){
        puts("Move any passed with files");
    } else{
        puts("Move any failed with files");
        dtw_remove_any("test");
        dtw_remove_any("test2");
        return false;
    }

    free(content12);
    dtw_remove_any("test2");
    dtw_remove_any("test");

    //testing for folder--------------------------------------------------------
    dtw_copy_any("static","test2",false);
    dtw_move_any("test2","test",DTW_NOT_MERGE);
    //verify if the origin were removed
    int entity_type13 = dtw_entity_type("test2");

    if(entity_type13 == DTW_NOT_FOUND && verify_if_is_test_equal_to_static()){
        puts("Move any passed with folders");
    } else{
        puts("Move any failed with folders");
        dtw_remove_any("test");
        dtw_remove_any("test2");
        return false;
    }
    dtw_remove_any("test");
    dtw_remove_any("test2");
    return true;
}