

function is_end_string(allow_loop,content,index,inside_string)
    if allow_loop == false then
    	return false
    end
    if inside_string == false then
    	return false
    end

    local last_last_char = clib.get_char(content,index-2)
    local last_char = clib.get_char(content,index-1)
    local current_char = clib.get_char(content,index)
    local scape = last_char == '\\' and last_last_char ~="\\"
    if current_char == '"' and scape == false  then
    	return true
    end
    return false
end

local function is_string_start(allow_loop,content,index,inside_string)
    if allow_loop == false then
    	return false
    end
	if inside_string == true then
		return false
	end
    local current_char = clib.get_char(content,index)
    if current_char == '"' then
    	return true
    end
    return false
end

local function include_char_to_final(allow_loop,waiting_include,inside_string)
    if allow_loop == false then
    	return false
    end
    if waiting_include then
    	return false
    end
    if inside_string then
    	return false
    end
    return true
end

local function include_string_buffer_to_final(waiting_include,is_end)

    if waiting_include then
    	return false
    end
    if is_end then
    	return true
    end

    return false
end


local function is_include_point(allow_loop,content,index,inside_string)
    if allow_loop == false then
    	return false
    end
    if inside_string then
    	return false
    end
    local INCLUDE_TEXT  = "#include"
    local content_size = clib.get_str_size(content)
    local include_size = clib.get_str_size(INCLUDE_TEXT)
    if index + include_size >= content_size then
    	return false
    end
    local buffer = ""
    for i=index,content_size do
    	buffer = buffer..clib.get_char(content,i)
    end
    return buffer == INCLUDE_TEXT
end
local function include_char_to_string_buffer(allow_loop,inside_string)
    if inside_string == false then
    	return false
    end
    if allow_loop == false then
    	return false
    end
    return true
end
---@param start_point string
---@return string
 function Generate_amalgamation(start_point)

    local content = clib.load_string(start_point)

    local size = clib.get_str_size(content)
    local inside_string = false
    local waiting_include = false
    local string_buffer = ""
    local allow_loop = true
    local final_text = ""
    for i=1,size do
        allow_loop = true

        if  is_string_start(allow_loop,content,i,inside_string) then
        	allow_loop = false
        	inside_string = true
        end

        local end_string = is_end_string(allow_loop,content,i,inside_string)

        if end_string then
           inside_string = false
           string_buffer = ""
        end


        if include_char_to_string_buffer(allow_loop,inside_string) then
        	string_buffer = string_buffer..clib.get_char(content,i)
        end

        if include_string_buffer_to_final(waiting_include,end_string) then
        	final_text = final_text..string_buffer
        end

        if include_char_to_final(allow_loop,waiting_include,inside_string) then
        	final_text = final_text..clib.get_char(content,i)
        end

        if is_include_point(allow_loop,content,i,inside_string) then
        	waiting_include = true
        end





    end
    return final_text
end
