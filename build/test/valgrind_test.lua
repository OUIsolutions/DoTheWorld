---@param cache Cache
---@param src_sha string
---@param original_side_effect_sha string
---@param artifact TestArtifact
function Exec_valgrind_test(cache, src_sha, original_side_effect_sha, artifact)
    local memory_tested = false
    cache.new_element("valgrind", function()
        memory_tested = true
        local comand = "valgrind --log-file='" .. OUTPUT_TEST .. "' ./" .. artifact.executable_path
        os.execute(comand);
        Rebase_side_effect()

        local result = dtw.load_file(OUTPUT_TEST)
        if result == nil then
            os.exit(1)
            return
        end

        local HEAP_CHECK = "All heap blocks were freed"
        local error      = false
        if string.find(result, HEAP_CHECK) == nil then
            print("subiu aqui\n")
            error = true
        end
        local ERROR_CHECK = "ERROR SUMMARY: 0 errors from 0 contexts"
        if string.find(result, ERROR_CHECK) == nil then
            error = true
        end

        if error then
            print(ANSI_RED .. result)
            os.exit(1)
        end
        print(ANSI_GREEN .. "\tmemory test:passed\n")
    end).
        add_dependencie(artifact.executable_sha).
        add_dependencie(original_side_effect_sha).
        add_dependencie(src_sha).
        perform()

    if memory_tested == false then
        print(ANSI_YELLOW .. "memory test:cached\n")
    end
end
