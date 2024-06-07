

---@param cache Cache
---@param src_sha string
---@param side_effect_sha string
---@param artifact TestSpec
local function execute_test_artifact(cache,src_sha,side_effect_sha,artifact)

    clib.print(ANSI_BLUE.."testing: "..artifact.c_path.."\n")

    artifact.c_sha = dtw.generate_sha_from_file(artifact.c_path)


    Execute_compilation(cache,src_sha,artifact)
    artifact.executable_sha = dtw.load_file(artifact.executable_path)


    Exec_valgrind_test(cache,side_effect_sha,artifact)

    if artifact.test_type ==IMPREDITIBLE  then
    	clib.print(ANSI_YELLOW.."side effect: not tested\n")
        Reconstruct_output(side_effect_sha,artifact)
        return
    end
    if RECONSTRUCT then
        Reconstruct_output(side_effect_sha,artifact)
    	return
    end

    Test_out_put(cache,executable_sha,side_effect_sha,artifact.test_dir,out_path)


end


---@param cache Cache
---@param src_sha string
function Execute_full_test(cache,src_sha)

    local side_effect_sha =  dtw.generate_sha_from_folder_by_content(SIDE_EFFECT)
    dtw.copy_any_overwriting(SIDE_EFFECT,"side_effect_copy")

    local listage,size =dtw.list_files_recursively(TEST_POINT,true)

    for i=1,size do
    	local possible_test = listage[i]
        local test = Get_test_spec(possible_test)
        if test ~= nil then
            execute_test_artifact(cache,src_sha,side_effect_sha,test)
        end

    end
end