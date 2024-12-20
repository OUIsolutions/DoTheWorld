function main()
    local src_sha = Generate_sha_from_folder_not_considering_empty_folders(LIB_FOLDER)
    local cache = NewCache(CACHE_POINT)

    local amalgamation_cache = cache.new_element("one_amalgamation", function()
        return camalgamator.generate_amalgamation(START_POINT)
    end).add_dependencie(src_sha)

    local amalgamation_result = amalgamation_cache.perform()
    dtw.write_file(RELEASE_FOLDER .. "/" .. OUTPUT_DECLARATION, amalgamation_result)

    if true then
        return
    end


    Execute_full_test(cache, src_sha)

    local locker_content = dtw.load_file("tests/locker_test/locker_test.c")

    cache.new_element("locker", function()
        Execute_locker_test()
    end).
        add_dependencie(locker_content).
        add_dependencie(src_sha).
        perform()

    Create_examples()
    dtw.write_file("exemples/locker/locker_test.c", locker_content)

    clib.print(ANSI_RESET)
end

main()
