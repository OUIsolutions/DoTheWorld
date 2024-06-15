

---@param compiler string
function Create_pre_compiled_version(compiler,declaration_amalgamantion)
    local temp_compilation = "temp_compilation"
    dtw.remove_any(temp_compilation)

    dtw.write_file(dtw.concat_path("temp_compilation",OUTPUT_DECLARATION),declaration_amalgamantion)

    local cjson_comand = compiler.." -c -o ".. dtw.concat_path(temp_compilation,CJSON_NAME).." "..CJSON_LOCATION
    clib.system_with_status(cjson_comand)

    local sha_cmand = compiler.." -c -o ".. dtw.concat_path(temp_compilation,SHA_256_NAME).." "..SHA_256_LOCATION
    clib.system_with_status(sha_cmand)


end