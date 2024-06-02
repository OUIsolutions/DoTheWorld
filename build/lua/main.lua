

START_POINT = "src/one.c"
END_POINT = "doTheWorld.h"


local function main()

  local amalgamation_result = Generate_amalgamation(START_POINT)
   clib.write_file(END_POINT,amalgamation_result)



end
main()