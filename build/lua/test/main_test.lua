
IMPREDITIBLE = 1
PREDICTIBLE = 2

function get_test_spec(content)

     local path = dtw.newPath(content)
     local filename = path.get_name()
     if filename ~= "exec.c" and  filename ~= "exec.cpp" then
     	return nil
     end
     local test = {}
     local dirs,size = path.unpack()
     for i=1,size do
        local current_dir = dirs[i]
     end

     if test.test_type == nil then
     	return nil
     end
      clib.print(test.test_type.."\n");

     test.test_dir = path.get_dir()
     return test
end

function Execute_full_test(cache,src_sha)
    local side_effect_sha =  dtw.generate_sha_from_folder_by_content(SIDE_EFFECT)
    local listage,size =dtw.list_files_recursively(TEST_POINT)
    for i=1,size do
    	local possible_test = listage[i]
        local test = get_test_spec(possible_test)
        if test ~= nil then
        end

    end
end