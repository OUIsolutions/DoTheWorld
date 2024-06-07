
function  Execute_locker_test()
	local locker_file = "tests/locker_test.c"
	local locker_output = "tests/locker_test.out"
	local compilation_comand = "gcc "..locker_file.."-o"..locker_output
	local status = clib.system_with_status(compilation_comand)

    if status ~= 0 then
          clib.print(ANSI_RED.."locker complation fail")
          clib.exit(1)
    end
    local TOTAL_TESTS = 10
    for i=1,TOTAL_TESTS do
       local content = clib.system_with_string("./"..locker_output)
       clib.print(content)

    end
    Rebase_side_effect()


  end