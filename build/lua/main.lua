


local function main()
    local amalgamation_result = Generate_amalgamation("src/one.c")
    clib.print(amalgamation_result)
end
main()