



local function main()

        local src_sha = Generate_sha_from_folder_not_considering_empty_folders(LIB_FOLDER)
        local cache = NewCache(CACHE_POINT)

        local amalgamation_cache = cache.new_element("amalgamation",function ()
            return Generate_amalgamation_recursive(START_POINT)
        end).add_dependencie(src_sha)


        local amalgamation_result = amalgamation_cache.perform()
        dtw.write_file(END_TEST_POINT,amalgamation_result)

        Execute_full_test(cache,src_sha)

        local locker_content= dtw.load_file("tests/locker_test/locker_test.c")

       cache.new_element("locker",function ()
            Execute_locker_test()
        end).
        add_dependencie(locker_content).
        add_dependencie(src_sha).
        perform()

        Create_examples()
        dtw.write_file("exemples/locker/locker_test.c",locker_content)

        clib.print(ANSI_RESET)


        local readme = Create_readme()
        if readme ~= nil then
            dtw.write_file("README.md",readme)
        end

        dtw.write_file(OUT_PUT_NAME,amalgamation_result)
end

main()