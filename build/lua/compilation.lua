
local function compile_segment(test_resource,cache,src_folder)
    test_resource.each(function (value)
    	local value_path = value.get_path_string()
    	local exec_resource = value.sub_resource("exec.c")
    	local exec_path = exec_resource.get_path_string()
    	local exec = exec_resource.get_string()
        clib.print("compiling "..value_path.."\n")

        if exec == nil then
            clib.print("file:'"..exec_path.."'not found\n")
        	clib.exit(1)
        end
        local command = "gcc "..exec_path.." -o "..dtw.concat_path(value_path,"exec.o ")
        cache.new_element(function ()
             local status = clib.system_with_status(command)
             if status ~= 0 then
             	clib.print("compilation fail\n")
             	clib.exit(1)
             end
        end)
        .add_side_effect(exec)
        .add_side_effect(src_folder)
        .add_side_effect(command)
        .perform()
    end)
end

function Execute_compilation(test_resource,cache,src_folder)

    test_resource.each(function (value)
        compile_segment(value,cache,src_folder)
    end)
end