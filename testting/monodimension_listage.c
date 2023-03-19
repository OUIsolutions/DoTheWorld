

bool test_monodimension_listage(){

    puts("Testing monodimension listage-------------------------------------");
    puts("Testing dtw_list_basic");
    struct DtWStringArry *expected  = dtw_constructor_string_array();
    dtw_add_string_to_array(expected,"static/deer.jpg");
    dtw_add_string_to_array(expected,"static/exemple.txt");
    
    struct DtwStringArray *list = dtw_list_basic("static",DTW_FILE_TYPE,DTW_NOT_CONCAT_PATH);
    



    return true;
}