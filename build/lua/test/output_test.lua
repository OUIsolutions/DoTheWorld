

---@param cache Cache
---@param executable_sha string
---@param side_effect_sha string
---@param test_dir string
---@param out_path string
function Test_out_put(cache,executable_sha,side_effect_sha,test_dir,out_path,expected_sha)

    local expected_file_path = dtw.concat_path(test_dir,"expected.txt")
    local expected_content = dtw.load_file(expected_file_path)
    if dtw.isfile(expected_content) == false then
        clib.print(ANSI_RED.."expected file not provided")
        clib.exit(1)
    end
    local output_tested = false
    cache.new_element(function ()
          output_tested = true
          local output_test = clib.system_with_string("./"..out_path)

          if output_test ~= expected_content then
          	  clib.print(ANSI_RED.."\tside effect different\n")
          	  Rebase_side_effect()
              clib.exit(1)
          end
          clib.print(ANSI_GREEN.."\texpected file: passed\n")

          local local_side_effect_dir_path = dtw.concat_path(test_dir,"side_effect")
          if dtw.isdir(local_side_effect_dir_path) then

          	local local_side_effect_assignature = dtw.generate_sha_from_folder_by_content(local_side_effect_dir_path)
          	if local_side_effect_assignature ~= side_effect_sha then
          		  clib.print(ANSI_RED.."side effect different than expected\n")
                  Rebase_side_effect()
                  clib.exit(1)
          	end
            clib.print(ANSI_GREEN.."\tside effect folder: passed\n")
            Rebase_side_effect()
          else
            clib.print(ANSI_YELLOW.."\tside effect folder: not provided\n")
          end
    end).
    add_dependencie(executable_sha).
    add_dependencie(side_effect_sha).
    perform()

    if output_tested == false then
    	clib.print(ANSI_YELLOW.."output test: cached\n")
    end

end