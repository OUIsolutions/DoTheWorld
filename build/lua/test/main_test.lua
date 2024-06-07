

---@param cache Cache
---@param src_sha string
---@param original_side_effect_sha string
---@param artifact TestArtifact
local function execute_test_artifact(cache,src_sha,original_side_effect_sha,artifact)

    clib.print(ANSI_BLUE.."testing: "..artifact.c_path.."\n")

    artifact.c_sha = dtw.generate_sha_from_file(artifact.c_path)

    Execute_compilation(cache,src_sha,artifact)
    artifact.executable_sha = dtw.generate_sha_from_file(artifact.executable_path)


    Exec_valgrind_test(cache,original_side_effect_sha,artifact)

    Test_out_put(cache,original_side_effect_sha,artifact)


end


---@param cache Cache
---@param src_sha string
function Execute_full_test(cache,src_sha)

    local original_side_effect_sha =  Generate_sha_from_folder_not_considering_empty_folders(SIDE_EFFECT)
    dtw.copy_any_overwriting(SIDE_EFFECT,SIDE_EFFECT_COPY)

    local listage,size =dtw.list_files_recursively(TEST_POINT,true)

    for i=1,size do
    	local possible_test = listage[i]
        local test = Get_test_spec(possible_test)
        if test ~= nil then
            execute_test_artifact(cache,src_sha,original_side_effect_sha,test)
        end

    end
end