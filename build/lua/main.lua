

START_POINT = "src/one.c"
END_POINT = "doTheWorld.h"
END_TEST_POINT= "tests/doTheWorld_test.h"
SIDE_EFFECT = "tests/target"
TEST_POINT = "tests/main_test"
LIB_FOLDER = "src"
CACHE_POINT  = "cache2"

local function main()


    local result = clib.system_with_string("valgrind  ./a.out --log-file='teste'")
    clib.print("result was: "..result.."\n")

    if false then
        local src_sha = dtw.generate_sha_from_folder_by_content(LIB_FOLDER)
        local cache = NewCache(CACHE_POINT)

        local amalgamation_cache = cache.new_element(function ()
            clib.print("amalgamated \n");
            return Generate_amalgamation_recursive(START_POINT)
        end).add_dependencie(src_sha)

        local amalgamation_result = amalgamation_cache.perform()
        dtw.write_file(END_TEST_POINT,amalgamation_result)

        Execute_full_test(cache,src_sha)

    end



end

main()