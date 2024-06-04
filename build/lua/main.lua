

START_POINT = "src/one.c"
END_POINT = "doTheWorld.h"
END_TEST_POINT= "tests/doTheWorld_test.h"
TEST_POINT = "tests/main_test"
LIB_FOLDER = "src"
CACHE_POINT  = "cache"
local function main()

    local cache = dtw.newResource(CACHE_POINT)
    local src_sha = dtw.generate_sha_from_folder_by_content(LIB_FOLDER)
    local amalgamation  = cache.sub_resource("amalgamation")
    local src_of_generation = amalgamation.get_value_from_sub_resource("src_sha")
    local amalgamation_result = nil
    clib.print("gerada"..src_sha.."\n")
    clib.print("nova"..src_of_generation.."\n")

    if src_of_generation == src_sha then
    	clib.print("amalgamation cached\n");
    	amalgamation_result =amalgamation.get_value_from_sub_resource("code")
    else
        clib.print("constructing amalgamation\n")
        amalgamation_result =Generate_amalgamation(START_POINT)
        amalgamation.set_value_in_sub_resource("code",amalgamation_result)
        amalgamation.set_value_in_sub_resource("src_sha",src_sha)
    end
    cache.commit()

end

main()