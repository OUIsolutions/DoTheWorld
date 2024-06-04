
local function compile_test(test_resource,cache,src_folder)
    test_resource.each(function (value)
    	local exec_resource = value.sub_resource("exec")
    	local exec = exec_resource.get_string()
    	local exec_path = exec_resource.get_path_string()
    	local value_path = value.get_path_string()
        clib.print("compiling "..value_path.."\n")

        if exec == nil then
            clib.print("file:"..exec_resource.."not found\n")
        	clib.exit()
        end

    	local current_test = cache.new_element(function ()

    	    local comand = "gcc "..exec_path.." -o "..value_path..dtw.concat_path(value_path," exec.out")
            local result = clib.system_with_status(comand)

    	end)

    	.add_side_effect(src_folder)
    	.add_side_effect(exec)
        current_test.perform()
    end)
end

function Execute_compilation(test_resource,cache,src_folder)

    test_resource.each(function (value)
        compile_test(value,cache,src_folder)
    end)
end