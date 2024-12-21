function Create_examples()
    dtw.remove_any(EXAMPLES_FOLDER)
    local test_tree = dtw.newTree_from_hardware(TEST_POINT)
    test_tree.each(function(tree_part)
        local path = tree_part.path

        if path.get_name() ~= "exec.c" then
            return
        end
        local content = tree_part.get_value()
        formated_content = string.gsub(content, '../../../../release/doTheWorld.h', OUTPUT_SINGLE_FILE);
        tree_part.set_value(formated_content)
        path.insert_dir_at_index(0, EXAMPLES_FOLDER)
        path.remove_sub_dirs_at(TEST_POINT)
        local final_name = path.get_sub_dirs_from_index(-1, -1)
        final_name = string.gsub(final_name, "T_", "")
        final_name = string.gsub(final_name, "S_", "")
        final_name = string.gsub(final_name, "/", ".c")
        path.remove_sub_dir_at_index(-1, -1)
        path.set_name(final_name)

        tree_part.hardware_write()
        print(ANSI_GREEN .. "created example" .. path.get_full_path())
    end)
    test_tree.commit()


    local locker = dtw.load_file("tests/locker_test/locker_test.c")
    locker = string.gsub(locker,"../../release/doTheWorld.h","doTheWorld.h")
    dtw.write_file("exemples/locker/locker_test.c",locker)
end
