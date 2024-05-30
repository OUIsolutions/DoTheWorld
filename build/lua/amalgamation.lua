local function concat_if_not_nul(str,str2)
    if str2 == nil then
    	return str
    end
    return str..str2
end

local function flip_bool(value)
	if value == true then
		return false
	end
	return true

end
local function is_include_at_point(str,point,inside_string)
    if inside_string == true  then
    	return false
    end

    local include_size = clib.get_str_size("#include")
    local buffer = ""
    for i=point,point+include_size-1 do
    	local current_char = clib.get_char(str,i)
        buffer = concat_if_not_nul(buffer,current_char)
    end

    return buffer == "#include"
end


---@param start_point string
---@return string
 function Generate_amalgamation(start_point)
    local content = clib.load_string(start_point)
    local size = clib.get_str_size(content)
    local final  = ""
    local getting_path = false
    local inside_string = false
    local path = ""
    for i=1,size do

       	local char = clib.get_char(content,i)
        local last_char = clib.get_char(content,i-1);

       	if char == '"' and last_char ~= '\\' then
       		inside_string = flip_bool(inside_string)
       	end

        getting_path = is_include_at_point(content,i,inside_string)
        if getting_path == false then
        	final = final..char
        end


    end
    return final
end