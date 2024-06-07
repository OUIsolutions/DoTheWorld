
---@param side_effect_sha string
---@param artifact TestSpec
function Reconstruct_output(side_effect_sha,artifact)

    local execution_result = clib.system_with_string("./"..artifact.executable_path)
    dtw.write_file(artifact.expected_file_path,execution_result)
    clib.print(ANSI_MAGENTA.."\tcreated:"..artifact.expected_file_path.."\n")


    local current_side_effect_sha = dtw.generate_sha_from_folder_by_content(SIDE_EFFECT)

    if current_side_effect_sha ~= side_effect_sha then
        dtw.copy_any_overwriting(SIDE_EFFECT,artifact.side_effect_folder_path)
        clib.print(ANSI_MAGENTA.."\tside effect "..artifact.side_effect_folder_path.." recreated \n")
    end
    if current_side_effect_sha == side_effect_sha then
           if dtw.isdir(artifact.side_effect_folder_path) then
               dtw.remove_any(artifact.side_effect_folder_path)
               clib.print(ANSI_MAGENTA.."\tside effect "..artifact.side_effect_folder_path.." removed \n")
           end
           clib.print(ANSI_MAGENTA.."\ttest not generated a side effect \n")
    end


end