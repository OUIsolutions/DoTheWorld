local dtw = require("luaDoTheWorld/luaDoTheWorld")


local var_to_be_replaced = "DtwSchemaUnsafe"
local var_to_replace = "privateDtwSchemaUnsafe"

local all, size = dtw.list_files_recursively("src", true)
for i = 1, size do
    local path = all[i]
    local content = dtw.load_file(path)
    local formmated_content = string.gsub(content, var_to_be_replaced, var_to_replace)
    dtw.write_file(path, formmated_content)
end
