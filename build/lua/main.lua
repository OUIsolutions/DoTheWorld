

START_POINT = "src/one.c"
END_POINT = "doTheWorld.h"
END_TEST_POINT= "tests/doTheWorld_test.h"
TEST_POINT = "tests/main_test"
LIB_FOLDER = "src"
CACHE_POINT  = "cache2"
local function main()

    local cache = dtw.newResource(CACHE_POINT)
    local src_sha = dtw.generate_sha_from_folder_by_content(LIB_FOLDER)
    local amalgamation = Generate_amalgamation(cache,src_sha)
    dtw.write_file(END_TEST_POINT,amalgamation)
    cache.commit()

end

main()