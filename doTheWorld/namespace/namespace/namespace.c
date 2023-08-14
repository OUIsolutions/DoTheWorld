
DtwNamespace newDtwNamespace(){
    DtwNamespace self = {0};
    //io
    self.create_dir_recursively = dtw_create_dir_recursively;
    self.remove_any = dtw_remove_any;
    self.get_current_dir = dtw_get_current_dir;
    self.load_any_content = dtw_load_any_content;
    self.load_string_file_content = dtw_load_string_file_content;
    self.load_binary_content = dtw_load_binary_content;
    self.write_any_content = dtw_write_any_content;
    self.write_string_file_content =dtw_write_string_file_content;
    self.entity_type = dtw_entity_type;
    self.complex_entity_type = dtw_complex_entity_type;
    self.convert_entity  = dtw_convert_entity;
    self.copy_any = dtw_copy_any;
    self.move_any = dtw_move_any;

    //listage
    self.list_files = dtw_list_files;
    self.list_dirs = dtw_list_dirs;
    self.list_all = dtw_list_all;

    self.list_files_recursively = dtw_list_files_recursively;
    self.list_dirs_recursively = dtw_list_dirs_recursively;
    self.list_all_recursively = dtw_list_all_recursively;

    //extras
    self.generate_sha_from_file = dtw_generate_sha_from_file;
    self.generate_sha_from_string = dtw_generate_sha_from_string;
    self.generate_sha_from_any = dtw_generate_sha_from_any;
    self.get_file_last_motification_in_unix = dtw_get_file_last_motification_in_unix;
    self.get_file_last_motification_in_string = dtw_get_file_last_motification_in_string;
    self.concat_path = dtw_concat_path;
    //bas64
    self.base64_encode = dtw_base64_encode;
    self.base64_decode  = dtw_base64_decode;
    self.convert_binary_file_to_base64 = dtw_convert_binary_file_to_base64;

    self.string_array = newDtwStringArrayModule();
    self.path = newDtwPathModule();
    #ifdef __linux__
        self.locker = newDtwLockerModule();
    #endif

    self.tree = newDtwTreeModule();
    self.transaction = newDtwTransactionModule();
    self.resource = newDtwResourceModule();


    return self;
}