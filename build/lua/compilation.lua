
local function compile_projects_of_folder(src_sha,folder)
        local listage,size = clib.list_dirs(folder)
        for i=1, size do
            local current_path = listage[i]
            local current_file = current_path.."exec.c"
            local current_sha = clib.generate_sha_from_file(current_file)
            local final_sha = clib.generate_sha_from_string(src_sha..current_sha)
            local output = CACHE_POINT.."/"..final_sha
            clib.print("compiling: "..output.."\n")

        end
end

function Execute_tests_compilaton(src_sha)
    local listage,size = clib.list_dirs(TEST_POINT)
    clib.print("compiling==========================================\n")
    for i=1,size do
        local current = listage[i]
        compile_projects_of_folder(src_sha,current)
    end
end