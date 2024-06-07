
---@param cache Cache
---@param src_sha string
---@param artifact TestSpec
function Execute_compilation(cache,src_sha,artifact)

    local compiled = false
    cache.new_element(function ()
        compiled = true
        local comand = "gcc "..artifact.exec_path.." -o "..artifact.executable_output
        local result = clib.system_with_status(comand)
        if result ~=0 then
        	clib.exit(1)
        end
        clib.print(ANSI_GREEN.."\tcompilation:passed\n")
    end).
    add_dependencie(src_sha).
    add_dependencie(artifact.exec_content).
    perform()

    if compiled == false then
        clib.print(ANSI_YELLOW.."\tcompilation:cached\n")
    end
end

