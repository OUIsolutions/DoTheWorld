

bool  test_io_operations(){
    puts("Testing io operations");
    //testing create dir------------------------------------------------------- 
    dtw_create_dir("test");
    int entity_type = dtw_entity_type("test");
    if(entity_type == DTW_FOLDER_TYPE){
        puts("Created dir passed");
    }else{
        puts("Created dir failed");
        return false;
    }
    //testing create dir recursivly---------------------------------------------
    dtw_create_dir_recursively("test/test2/test3/test4");
    entity_type = dtw_entity_type("test/test2/test3/test4");
    if(entity_type == DTW_FOLDER_TYPE){
        puts("Created dir recursivly passed");
    }else{
        puts("Created dir recursivly failed");
        return false;
    }

    //testing remove any -------------------------------------------------------
    dtw_remove_any("test");
    entity_type = dtw_entity_type("test");
    if(entity_type == DTW_NOT_FOUND){
    puts("Remove any passed");
    }else{
    puts("Remove any failed");
    return false;
    }

    //testing load any content -------------------------------------------------
    int size = 0;
    bool is_binary = false;
    unsigned char *first_content = dtw_load_any_content("static/deer.jpg", &size, &is_binary);
    if(first_content != NULL){
        puts("Load any content passed");
    }else{
        puts("Load any content failed");
        return false;
    }
    free(first_content);
    //testing load string file content -----------------------------------------

    char *first_string_content = dtw_load_string_file_content("static/exemple.txt");
    if( strcmp(first_string_content,"Working!") == 0){
        puts("Load string file content passed");
    }else{
        puts("Load string file content failed");
        return false;
    }
    free(first_string_content);
    //testing write any content-------------------------------------------------
    //load the deer.jpg content and write it 
    unsigned char *second_content = dtw_load_any_content("static/deer.jpg", &size, &is_binary);
    bool result = dtw_write_any_content("test/deer.jpg", second_content, size);
    if(result){
        puts("Write any content passed");
    }else{
        puts("Write any content failed");
        dtw_remove_any("test");
        return false;
    }
    free(second_content);
    dtw_remove_any("test");

    //testing write string file content-----------------------------------------
    result = dtw_write_string_file_content("test/exemple.txt","Working!");
    if(result){
        puts("Write string file content passed");
    }else{
        puts("Write string file content failed");
        dtw_remove_any("test");
        return false;
    }
    //testing loading binary content--------------------------------------------
    unsigned char *third_content = dtw_load_binary_content("static/deer.jpg", &size);
    if(third_content != NULL){
        puts("Load binary file content passed");
    }else{
        puts("Load binary file content failed");
        dtw_remove_any("test");
        return false;
    }
    dtw_remove_any("test");
    free(third_content);
    //testing copy any----------------------------------------------------------
    //testing for file 
    result = dtw_copy_any("static/deer.jpg","test/deer.jpg",false);
    if(result){
        puts("Copy any passed with files");
    }else{
        puts("Copy any failed with files");
        dtw_remove_any("test");
        return false;
    }
    dtw_remove_any("test");
    //testing for folder
    result = dtw_copy_any("static","test",false);
    if(result){
        puts("Copy any passed with folders");
    } else{
        puts("Copy any failed with folders");
        dtw_remove_any("test");
        return false;
    }
    dtw_remove_any("test");
    //testing move any----------------------------------------------------------
    dtw_copy_any("static","test",false);
    //testing for files 
    dtw_move_any("test/deer.jpg","test/deer2.jpg",false);
    entity_type = dtw_entity_type("test/deer.jpg");
    if(entity_type == DTW_NOT_FOUND){
        puts("Move any passed with files");
    }else{
        puts("Move any failed with files");
        dtw_remove_any("test");
        return false;
    }
    dtw_remove_any("test");
    //testing for folders
    dtw_move_any("test","test2",false);
    entity_type = dtw_entity_type("test");
    if(entity_type == DTW_NOT_FOUND){
        puts("Move any passed with folders");
    }else{
        puts("Move any failed with folders");
        dtw_remove_any("test2");
        return false;
    }
    dtw_remove_any("test2");
}