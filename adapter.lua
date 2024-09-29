local dtw = require("luaDoTheWorld/luaDoTheWorld")


function remove_all_includes(content)

end

function remove_all_includes_of_dir(dir)
    local elements = dtw.list_files_recursively(dir, true)
    for i = 1, #elements do
        local current = elements[i]
        local content = dtw.loadfile(current)
        local content_formmatted = remove_all_includes(content)
        dtw.write_file(current, content_formmatted)
    end
end
