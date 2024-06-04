

START_POINT = "src/one.c"
END_POINT = "doTheWorld.h"
END_TEST_POINT= "tests/doTheWorld_test.h"
TEST_POINT = "tests/main_test"
LIB_FOLDER = "src"
CACHE_POINT  = "cache2"
local function main()

    local src_sha = dtw.generate_sha_from_folder_by_content(LIB_FOLDER)
    local cache = NewCache(CACHE_POINT)

    local amalgamation_cache = cache.new_element(function ()
    	return Generate_amalgamation_recursive(START_POINT)
    end).add_side_effect(src_sha)

    local amalgamation_result = amalgamation_cache.perform()
    dtw.write_file(END_TEST_POINT,amalgamation_result)

    local main_test_resource = dtw.newResource(TEST_POINT)
    Execute_compilation(main_test_resource,cache)



end

main()