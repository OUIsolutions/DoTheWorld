

START_POINT = "src/one.c"
END_POINT = "doTheWorld.h"
END_TEST_POINT= "tests/doTheWorld_test.h"
TEST_POINT = "tests/main_test"
LIB_FOLDER = "src"
CACHE_POINT  = "cache"
local function main()

    local listage = dtw.list_files_recursively("src")
    local i = 1
    while true  do
    	local current = listage[i]
        clib.print(current.."\n")
    	if current == nil then
    		break
    	end
    	i = i + 1
    end
end

main()