function main()
    dtw.remove_any("release")
    os.execute("mkdir -p dependencies")

    if argv.flags_exist({ "install_dependencies" }) then
        os.execute(
            "curl -L https://raw.githubusercontent.com/DaveGamble/cJSON/refs/tags/v1.7.18/cJSON.c -o dependencies/cJSON.c")
        os.execute(
            "curl -L https://raw.githubusercontent.com/DaveGamble/cJSON/refs/tags/v1.7.18/cJSON.h -o dependencies/cJSON.h")

        os.execute(
            "curl -L https://raw.githubusercontent.com/amosnier/sha-2/565f65009bdd98267361b17d50cddd7c9beb3e6c/sha-256.c -o dependencies/sha-256.c  "
        )
        os.execute(
            "curl -L https://raw.githubusercontent.com/amosnier/sha-2/565f65009bdd98267361b17d50cddd7c9beb3e6c/sha-256.h -o dependencies/sha-256.c  "
        )

        os.execute(
            "curl -L https://github.com/OUIsolutions/CHashManipulator/releases/download/0.001/CHashManipulator.h -o dependencies/CHashManipulator.h "
        )
    end
    if argv.flags_exist({ "silverchain_organize" }) then
        silverchain.generate({
            src = "src",
            project_short_cut = "doTHeWorld",
            tags = { "native_imports", "dependency", "consts", "macros", "types", "globals", "fdeclare", "fdefine" }
        })
    end

    if argv.flags_exist({ "amalgamate" }) then
        local amalgamation_result = camalgamator.generate_amalgamation(START_POINT)
        dtw.write_file(RELEASE_FOLDER .. "/" .. OUTPUT_SINGLE_FILE, amalgamation_result)
    end


    if argv.flags_exist({ "test" }) then
        local cache = NewCache(CACHE_POINT)
        local src_sha = Generate_sha_from_folder_not_considering_empty_folders(LIB_FOLDER)
        Execute_full_test(cache, src_sha)
        local locker_content = dtw.load_file("tests/locker_test/locker_test.c")

        cache.new_element("locker", function()
            Execute_locker_test()
        end).
            add_dependencie(locker_content).
            add_dependencie(src_sha).
            perform()
    end
    if argv.flags_exist({ "create_examples" }) then
        Create_examples()
    end

    if argv.flags_exist({ "create_readme" }) then
        local readme = Create_readme()
    end
    print(ANSI_RESET)
end
