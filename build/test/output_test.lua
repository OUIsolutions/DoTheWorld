---@param expected_content string
---@param artifact TestArtifact
---@param output_test string
local function handle_expected_file(expected_content, artifact, output_test)
    if expected_content == nil then
        dtw.write_file(artifact.expected_file_path, output_test)
        print(ANSI_CYAN .. "\texpected file:created")
        return
    end
    if output_test == expected_content then
        print(ANSI_GREEN .. "\texpected file: passed")
        return
    end

    if RECONSTRUCT then
        dtw.write_file(artifact.expected_file_path, output_test)
        print(ANSI_MAGENTA .. "\texpected file:reconstructed\n")
        return
    end
    if artifact.test_type == PREDICTIBLE then
        print(ANSI_RED .. "\texpected file: different\n")
        Rebase_side_effect()
        os.exit(1)
    end
    if artifact.test_type == IMPREDITIBLE then
        print(ANSI_YELLOW .. "\texpected file: impredictible\n")
    end
end


---@param original_side_effect_sha string
---@param artifact TestArtifact
local function handle_side_effect_folder(original_side_effect_sha, artifact)
    local current_sidde_effect = Generate_sha_from_folder_not_considering_empty_folders(SIDE_EFFECT)

    if current_sidde_effect == original_side_effect_sha then
        print(ANSI_YELLOW .. "\tside effect folder: no changes\n")
        return
    end



    if artifact.side_effect_sha == nil then
        dtw.move_any_overwriting(SIDE_EFFECT, artifact.side_effect_folder_path)
        print(ANSI_CYAN .. "\tside effect folder: created")
        return
    end

    if artifact.test_type == IMPREDITIBLE then
        print(ANSI_YELLOW .. "\tside effect folder: impredictible")
        return
    end

    if RECONSTRUCT then
        dtw.move_any_overwriting(SIDE_EFFECT, artifact.side_effect_folder_path)
        print(ANSI_MAGENTA .. "\tside effect folder: recreated")
        return
    end

    if artifact.side_effect_sha ~= current_sidde_effect then
        print(ANSI_RED .. "\tside effect folder: diffeent")
        Rebase_side_effect()
        os.exit(1)
    end

    print(ANSI_GREEN .. "\tside effect folder: passed")
end

---@param cache Cache
---@param original_side_effect_sha string
---@param artifact TestArtifact
function Test_out_put(cache, src_sha, original_side_effect_sha, artifact)
    local output_tested = false
    local expected_content = dtw.load_file(artifact.expected_file_path)

    local out_cache = cache.new_element("output", function()
        output_tested = true
        local ok = os.execute("./" .. artifact.executable_path .. "> side_effect")
        local output_test = dtw.load_file("side_effect")
        handle_expected_file(expected_content, artifact, output_test)
        handle_side_effect_folder(original_side_effect_sha, artifact)
        Rebase_side_effect()
    end).
    add_dependencie(artifact.executable_sha).
    add_dependencie(src_sha).
    add_dependencie(original_side_effect_sha)


    if dtw.isdir(artifact.side_effect_folder_path) then
        artifact.side_effect_sha = Generate_sha_from_folder_not_considering_empty_folders(artifact
            .side_effect_folder_path)
        out_cache.add_dependencie(artifact.side_effect_sha)
    end

    if expected_content ~= nil and artifact.test_type == PREDICTIBLE then
        out_cache.add_dependencie(expected_content)
    end


    out_cache.perform()


    if output_tested == false then
        print(ANSI_YELLOW .. "\toutput test: cached")
    end
end
