

bool  test_io_operations(){
    puts("Testing io operations");
    //testing create dir------------------------------------------------------- 
    dtw_create_dir("test");
    int entity_type = dtw_entity_type("test");
    if(entity_type == DTW_FOLDER_TYPE){
        puts("Created dir passed\n");
    }else{
        puts("Created dir failed\n");
        return false;
    }
    //testing remove any -------------------------------------------------------
    dtw_remove_any("test");
    entity_type = dtw_entity_type("test");
    if(entity_type == DTW_NOT_FOUND){
    puts("Remove any passed\n");
    }else{
    puts("Remove any failed\n");
    return false;
    }
    //testing create dir recursivly---------------------------------------------
    dtw_create_dir_recursively("test/test2/test3/test4");
    entity_type = dtw_entity_type("test/test2/test3/test4");
    if(entity_type == DTW_FOLDER_TYPE){
        puts("Created dir recursivly passed\n");
    }else{
        puts("Created dir recursivly failed\n");
        return false;
    }
    dtw_remove_any("test");
    //testing load any content 
    int size = 0;
    bool is_binary = false;
    unsigned char *first_content = dtw_load_any_content("static/deer.jpg", &size, &is_binary);
    if(first_content != NULL){
        puts("Load any content passed\n");
    }else{
        puts("Load any content failed\n");
        return false;
    }
    free(first_content);
    //testing load string file content 

}