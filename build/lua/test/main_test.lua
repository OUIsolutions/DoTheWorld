
IMPREDITIBLE = 1
PREDICTIBLE = 2

---@class TestSpec
---@field test_type number
---@field test_dir string


---@param content string
---@return TestSpec | nil
local function get_test_spec(content)

     local path = dtw.newPath(content)
     local filename = path.get_name()
     if filename ~= "exec.c" then
     	return nil
     end
     local test = {}
     local dirs,size = path.unpack()
     for i=1,size do
        local current_dir = dirs[i]
        if dtw.starts_with(current_dir,"S_") then
        	test.test_type = IMPREDITIBLE
        end
        if dtw.starts_with(current_dir,"T_") then
        	test.test_type = PREDICTIBLE
        end
     end

     if test.test_type == nil then
     	return nil
     end

     test.test_dir = path.get_dir()
     return test
end

local function rebase_side_effect()
	        dtw.copy_any_overwriting("side_effect_copy",SIDE_EFFECT)

end

---@param cache Cache
---@param src_sha string
---@param side_effect_sha string
---@param artifact TestSpec
local function execute_test_artifact(cache,src_sha,side_effect_sha,artifact)

    local exec_path = dtw.concat_path(artifact.test_dir,"exec.c")
    local out_path = dtw.concat_path(artifact.test_dir,"exec.out")
    local exec_content = dtw.load_file(exec_path)


    cache.new_element(function ()
    	clib.print("compiled "..exec_path.."\n");
        local comand = "gcc "..exec_path.." -o "..out_path
        local result = clib.system_with_status(comand)
        if result ~=0 then
        	clib.exit(1)
        end
    end).
    add_dependencie(src_sha).
    add_dependencie(exec_content).
    perform()


    cache.new_element(function ()
        clib.print("testing "..out_path.."\n");
        local comand = "valgrind ./"..out_path
        local result = clib.system_with_string(comand);
        --clib.print(result)
        rebase_side_effect()

end).
    add_dependencie(src_sha).
    add_dependencie(exec_content).
    add_dependencie(side_effect_sha).
    perform()


end


---@param cache Cache
---@param src_sha string
function Execute_full_test(cache,src_sha)

    local side_effect_sha =  dtw.generate_sha_from_folder_by_content(SIDE_EFFECT)
    dtw.copy_any_overwriting(SIDE_EFFECT,"side_effect_copy")

    local listage,size =dtw.list_files_recursively(TEST_POINT,true)

    for i=1,size do
    	local possible_test = listage[i]
        local test = get_test_spec(possible_test)
        if test ~= nil then
            execute_test_artifact(cache,src_sha,side_effect_sha,test)
        end

    end
end