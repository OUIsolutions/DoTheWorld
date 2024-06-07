

---@param cache Cache
---@param src_sha string
---@param exec_content string
---@param side_effect_sha string
---@param out_path string
 function Exec_valgrind_test(cache,src_sha,exec_content,side_effect_sha,out_path)
    local memory_tested = false
    cache.new_element(function ()
        memory_tested =true
        local comand = "valgrind --log-file='output_test' ./"..out_path
        clib.system_with_string(comand);

        local result = dtw.load_file("output_test")
        if result == nil then
            rebase_side_effect()
            clib.exit(1)
            return
        end

        local HEAP_CHECK  = "All heap blocks were freed -- no leaks are possible"
        local error =false
        if clib.indexof(result,HEAP_CHECK) == -1 then
        	error = true
        end
        local ERROR_CHECK = "ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)"
        if clib.indexof(result,ERROR_CHECK) == -1 then
          error = true
        end

        rebase_side_effect()
        if error then
            clib.print(ANSI_RED..result)
        	clib.exit(1)
        end
        clib.print(ANSI_GREEN.."\tmemory test:passed\n")
end).
    add_dependencie(src_sha).
    add_dependencie(exec_content).
    add_dependencie(side_effect_sha).
    perform()

    if memory_tested == false then
        clib.print(ANSI_YELLOW.."\tmemory test:cached\n")
    end
end
