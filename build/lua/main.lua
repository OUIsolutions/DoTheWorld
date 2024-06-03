

START_POINT = "src/one.c"
END_POINT = "doTheWorld.h"
END_TEST_POINT= "tests/doTheWorld_test.h"
TEST_POINT = "tests/main_test"
LIB_FOLDER = "src"
CACHE_POINT  = "cache"
local function main()

  local amalgamation_result = Generate_amalgamation(START_POINT)
   clib.write_file(END_TEST_POINT,amalgamation_result)
   local src_sha = clib.generate_sha_from_folder(LIB_FOLDER)
    Execute_tests_compilaton(src_sha)
   clib.write_file(END_POINT,amalgamation_result)

end
main()