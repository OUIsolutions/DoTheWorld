
---@param cache Cache
---@param src_sha string
---@param artifact TestArtifact
function Execute_compilation(cache,src_sha,artifact)

    local compiled = false
    cache.new_element("compilation",function ()
        compiled = true
        local comand = "gcc "..artifact.c_path.." -DDTW_DEBUG_TIME -o "..artifact.executable_path
        local result = clib.system_with_status(comand)
        if result ~=0 then
        	clib.exit(1)
        end
        clib.print(ANSI_GREEN.."\tcompilation:passed\n")
    end).
    add_dependencie(src_sha).
    add_dependencie(artifact.c_sha).
    perform()

    if compiled == false then
        clib.print(ANSI_YELLOW.."\tcompilation:cached\n")
    end
end

