local function verify_if_is_start_string_char(content,index,inside_string)
	if inside_string == true then
		return false
	end
	local last_char = clib.get_char(content,index-1)
    if last_char == '\\' then
    	return false
    end
    local current_char = clib.get_char(content,index)
    if current_char == '"' then
    	return true
    end
    return false
end


local function verify_if_is_end_string_char(is_start_string_char,content,index,inside_string)
    if is_start_string_char then
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


local function include_char_to_final(waiting_include,inside_string)

    if waiting_include then
    	return false
    end
    if inside_string then
    	return false
    end
    return true
end

local function include_string_buffer_to_final(waiting_include,is_end_string)

    if waiting_include then
    	return false
    end
    if is_end_string then
    	return true
    end

    return false
end


local function is_include_point(content,index,inside_string)

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
    for i=index,index + include_size -1 do
    	buffer = buffer..clib.get_char(content,i)
    end

    return buffer == INCLUDE_TEXT
end

local function include_char_to_string_buffer(is_start_string,is_end_string,is_inside_string)
    if is_start_string then
    	return false
    end
    if is_end_string then
    	return false
    end
    if is_inside_string then
    	return true
    end

    return false
end

local function make_recursive_call(waiting_include,is_end_string)
	if waiting_include and is_end_string then
		return true
	end
end

local function anulate_inclusion(waiting_include,content,index)
    if waiting_include == false then
    	return false
    end
    if clib.get_char(content,index) == "<" then
    	return true
    end
    return false
end
---@param start_point string
---@return string
 function Generate_amalgamation(start_point)

    local stack = {{}}
    local current_stack = stack[1]
    current_stack.start_point = start_point
    current_stack.content = clib.load_string(start_point)
    current_stack.size = clib.get_str_size(current_stack.content)
    current_stack.inside_string = false
    current_stack.waiting_include = false
    current_stack.string_buffer = ""
    current_stack.final_text = ""

    local stack_size = 1

    while true do


            for i=1,current_stack.size do

                local is_start_string = verify_if_is_start_string_char(current_stack.content,i,current_stack.inside_string)
                if is_start_string  then
                    current_stack.inside_string = true
                end

                local is_end_string = verify_if_is_end_string_char(is_start_string,current_stack.content,i,current_stack.inside_string)

               if include_char_to_string_buffer(is_start_string,is_end_string,current_stack.inside_string) then
                    current_stack.string_buffer = current_stack.string_buffer..clib.get_char(current_stack.content,i)
                end

               if include_string_buffer_to_final(current_stack.waiting_include,is_end_string) then
                    current_stack.final_text = current_stack.final_text..'"'..current_stack.string_buffer..'"'
                end

                if is_include_point(current_stack.content,i,current_stack.inside_string) then
                    current_stack.waiting_include = true
                end

                if anulate_inclusion(current_stack.waiting_include,current_stack.content,i) then
                    current_stack.final_text = current_stack.final_text.."#include "
                    current_stack.waiting_include = false
                end

                if include_char_to_final(current_stack.waiting_include,current_stack.inside_string) then
                    current_stack.final_text = current_stack.final_text..clib.get_char(current_stack.content,i)
                end


                if make_recursive_call(current_stack.waiting_include,is_end_string) then
                    local dir = clib.extract_dir(current_stack.start_point)
                    local full_path = clib.concat_path(dir,current_stack.string_buffer)
                    stack_size = stack_size +1
                    current_stack = {}
                    stack[stack_size] = current_stack
                    current_stack.start_point = full_path
                    current_stack.content = clib.load_string(full_path)
                    current_stack.size = clib.get_str_size(current_stack.content)
                    current_stack.inside_string = false
                    current_stack.waiting_include = false
                    current_stack.string_buffer = ""
                    current_stack.final_text = ""
                    clib.print("incremetou\n")
                    break
                end

            end


            if stack_size == 1 then
            	return current_stack.final_text
            end
            local old_stack = stack[stack_size]
            stack_size = stack_size -1
            current_stack = stack[stack_size]

            current_stack.final_text = current_stack.final_text.. old_stack.final_text.."\n"
            current_stack.waiting_include = false
            current_stack.inside_string = false
            current_stack.string_buffer = ""

    end

end
