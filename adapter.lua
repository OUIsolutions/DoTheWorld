local dtw = require("luaDoTheWorld/luaDoTheWorld")


function remove_all_includes(content)
    local includeIndex = content:find("#include")
    if not includeIndex then
        return content
    end 
    local newIndex = content:find("\n", includeIndex)
    if newIndex then
        content = content:sub(1, includeIndex - 1) .. content:sub(newIndex)
    end
    return remove_all_includes(content)
end


function remove_all_includes_of_dir(dir)
    local elements = dtw.list_files_recursively(dir, true)
    for i = 1, #elements do
        local current = elements[i]
        local content = dtw.load_file(current)
        local content_formmatted = remove_all_includes(content)
        print(content_formmatted)
        -- dtw.write_file(current, content_formmatted)
    end
end

remove_all_includes_of_dir("src/functions")
