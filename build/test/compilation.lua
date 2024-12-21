---@param cache Cache
---@param src_sha string
---@param artifact TestArtifact
function Execute_compilation(cache, src_sha, artifact)
    local compiled = false
    local compile_and_test = function()
        compiled = true
        local comand = "gcc " .. artifact.c_path .. " -DDTW_DEBUG_TIME -o " .. artifact.executable_path
        local result = os.execute(comand)

        if not result then
            os.exit(1)
        end
        print(ANSI_GREEN .. "\tcompilation:passed")
    end
    if not dtw.isfile(artifact.executable_path) then
        compile_and_test()
        return
    end


    cache.new_element("compilation", compile_and_test).
        add_dependencie(src_sha).
        add_dependencie(artifact.c_sha).
        perform()
    if compiled == false then
        print(ANSI_YELLOW .. "\tcompilation:cached")
    end
end
