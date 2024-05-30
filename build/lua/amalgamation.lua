
---@param start_point string
---@return string
 function Generate_amalgamation(start_point)
    local content = clib.load_string(start_point)
    local size = clib.get_str_size(content)
    for i=1,size do
    	clib.print(i)
    	clib.print("\n")
    end
end