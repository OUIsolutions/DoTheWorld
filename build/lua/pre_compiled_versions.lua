

---@param compiler string
---@param declaration_amalgamantion string
---@param lib_name string
function Create_pre_compiled_version(compiler,declaration_amalgamantion,lib_name)
    local temp_compilation = "temp_compilation"
    dtw.remove_any(temp_compilation)

    dtw.write_file(dtw.concat_path("temp_compilation",OUTPUT_DECLARATION),declaration_amalgamantion)

    local lib_comand = compiler.." -c -o "..dtw.concat_path(temp_compilation,LIB_NAME).." "..DEFINITION_POINT
    clib.system_with_status(lib_comand)

    local cjson_comand = compiler.." -c -o ".. dtw.concat_path(temp_compilation,CJSON_NAME).." "..CJSON_LOCATION
    clib.system_with_status(cjson_comand)

    local sha_cmand = compiler.." -c -o ".. dtw.concat_path(temp_compilation,SHA_256_NAME).." "..SHA_256_LOCATION
    clib.system_with_status(sha_cmand)
    local temp_lib = "temp_lib"

    clib.system_with_status("zip -r --junk-paths "..temp_lib.." "..temp_compilation)

    local zip_name = temp_lib..".zip"
    dtw.move_any_overwriting(zip_name,dtw.concat_path(RELEASE_FOLDER,lib_name))

end