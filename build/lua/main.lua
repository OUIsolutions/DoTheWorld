

START_POINT = "src/one.c"
END_POINT = "doTheWorld.h"
END_TEST_POINT= "tests/doTheWorld_test.h"
TEST_POINT  = "tests/main_test"

local function main()

  local amalgamation_result = Generate_amalgamation(START_POINT)
   clib.write_file(END_TEST_POINT,amalgamation_result)
   clib.write_file(END_POINT,amalgamation_result)



end
main()