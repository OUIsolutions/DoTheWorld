

START_POINT = "src/one.c"
END_POINT = "doTheWorld.h"


local function main()
   Verify_if_string_at_char_time = New_time("verify_if_string_at_char")
    local amalgamation_result = Generate_amalgamation(START_POINT)
     clib.write_file(END_POINT,amalgamation_result)
     Verify_if_string_at_char_time.represent()
end
main()