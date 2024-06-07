
---@param cache Cache
---@param src_sha string
---@param exec_content string
---@param exec_path string
---@param out_path string
function Execute_compilation(cache,src_sha,exec_content, exec_path,out_path)

    local compiled = false
    cache.new_element(function ()
        compiled = true
        local comand = "gcc "..exec_path.." -o "..out_path
        local result = clib.system_with_status(comand)
        if result ~=0 then
        	clib.exit(1)
        end
        clib.print(ANSI_GREEN.."\tcompilation:passed\n")
    end).
    add_dependencie(src_sha).
    add_dependencie(exec_content).
    perform()

    if compiled == false then
        clib.print(ANSI_YELLOW.."\tcompilation:cached\n")
    end
end

