function main()
    local src_sha = Generate_sha_from_folder_not_considering_empty_folders(LIB_FOLDER)
    local cache = NewCache(CACHE_POINT)

    local amalgamation_cache = cache.new_element("one_amalgamation", function()
        return camalgamator.generate_amalgamation(START_POINT)
    end).add_dependencie(src_sha)



    local amalgamation_result = amalgamation_cache.perform()
    dtw.write_file(END_TEST_POINT, amalgamation_result)

    Execute_full_test(cache, src_sha)
    if true then
        return
    end
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


    local readme = Create_readme()
    if readme ~= nil then
        dtw.write_file("README.md", readme)
    end
    dtw.write_file(RELEASE_FOLDER .. "/" .. OUTPUT_SINGLE_FILE, amalgamation_result)

    local declaration_amalgamation = cache
        .new_element("declaration_amalgamation", function()
            return Generate_amalgamation_recursive(DECLARATION_POINT)
        end
        ).add_dependencie(src_sha)
        .perform()

    dtw.write_file(RELEASE_FOLDER .. "/" .. OUTPUT_DECLARATION, declaration_amalgamation)

    local implementation_amalgamation = cache.new_element("implementation_amalgamation", function()
        return Generate_amalgamation_recursive(DEFINITION_POINT)
    end).add_dependencie(src_sha).perform()

    local index = clib.indexof(implementation_amalgamation, "//doTheWorldDeclarationEnd");


    local formmated = string.sub(implementation_amalgamation, index, #implementation_amalgamation);
    formmated = '#include  "doTheWorld_declaration.h"\n' .. formmated
    dtw.write_file(RELEASE_FOLDER .. "/" .. OUTPUT_DEFINITION, formmated)
end

main()
