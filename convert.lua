local src = dtw.list_files_recursively("src", true)
---removendo lixo
for i = 1, #src do
    local current = src[i]
    local name = dtw.newPath(current).get_name()
    if name == "declaration.h" or name == "definition.c" or name == "unique.declaration_requirements.h" or
        name == "unique.declaration_requirements.h" or name == "all.h" then
        dtw.remove_any(current)
    end
end
src = dtw.list_files_recursively("src", true)

for i = 1, #src do
    local current = src[i]
    local content = dtw.load_file(current)
    local new_content = string.gsub(content, '#include "../unique.definition_requirements.h"', "")
    new_content = string.gsub(new_content, '#include "../unique.declaration_requirements.h"', "")
    dtw.write_file(current, new_content)
end

local functions = dtw.list_files_recursively("src/functions", true)
for i = 1, #functions do
    local current = functions[i]
    local path_obj = dtw.newPath(current)
    local extension = path_obj.get_extension()

    if extension == "c" then
        local new_name = "fdefine." .. path_obj.get_name()
        path_obj.set_name(new_name)
    end

    if extension == "h" then
        local new_name = "fdeclare" .. path_obj.get_name()
        path_obj.set_name(new_name)
    end

    dtw.move_any_overwriting(current, path_obj.get_full_path())
end
