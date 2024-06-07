
---@param content string
local function  count_break_lines(content)
	local size = clib.get_str_size(content)
	local total =0
	for i=1,size do
		if clib.get_char(content,i) == "\n" then
			total = total+1
		end
	end
	return total
end
function  Execute_locker_test()
	local locker_file = "tests/locker_test/locker_test.c"
	local locker_output = "tests/locker_test/locker_test.out"
	local compilation_comand = "gcc "..locker_file.." -o "..locker_output
	local status = clib.system_with_status(compilation_comand)

    if status ~= 0 then
          clib.print(ANSI_RED.."locker complation fail")
          clib.exit(1)
    end
    local TOTAL_TESTS = 10
    for i=1,TOTAL_TESTS do
       clib.system_with_string("./"..locker_output)
       local locker_write_path = dtw.concat_path(SIDE_EFFECT,"append.txt")
       local locker_write_content = dtw.load_file(locker_write_path)
       if locker_write_content == nil then
       	    clib.print(ANSI_RED.."locker fail\n")
       	    Rebase_side_effect()
       	    clib.exit(1)
       	    return
       end
       local total_break_lines = count_break_lines(locker_write_content)

       if total_break_lines == 10 then
       	  clib.print(ANSI_GREEN.."locker test "..i.." passed\n")
       else
            clib.print(ANSI_RED.."locker test fail\n")
            Rebase_side_effect()
            clib.exit(1)
       end
    end

    Rebase_side_effect()


  end