

function Reconstruct_output(test_dir,out_path,side_effect_sha)
    local execution_result = clib.system_with_string("../"..out_path)
    
    local expected_file_path = dtw.concat_path(test_dir,"expected.txt")
    dtw.write_file(expected_file_path,execution_result)
    clib.print(ANSI_BLUE.."created:"..expected_file_path.."\n")
    local local_side_effect_dir_path = dtw.concat_path(test_dir,"side_effect")
    local current_side_effect_sha = dtw.generate_sha_from_folder_by_content(SIDE_EFFECT)

    if current_side_effect_sha ~= side_effect_sha then
        dtw.copy_any_overwriting(SIDE_EFFECT,local_side_effect_dir_path)
        clib.print(ANSI_BLUE.."side effect "..local_side_effect_dir_path.." recreated \n")
    else
        if dtw.isdir(local_side_effect_dir_path) then
            clib.print(ANSI_BLUE.."side effect "..local_side_effect_dir_path.." removed \n")
            dtw.remove_any(local_side_effect_dir_path)
        else
            clib.print(ANSI_BLUE.."test not generated a side effect \n")
        end
    end

end