

---@param cache Cache
---@param test_dir string
---@param out_path string
function test_side_effect(cache,test_dir,out_path,expected_sha)

    local expected_file_path = dtw.concat_path(test_dir,"expected.txt")
    local expected_content = dtw.load_file(expected_file_path)
    if dtw.isfile(expected_content) == false then
        clib.print(ANSI_RED.."expected file not provided")
        clib.exit(1)
    end
    cache.new_element(function ()
          local output_test = clib.system_with_string("./"..out_path)

          if output_test ~= expected_content then
          	  clib.print(ANSI_RED.."side effect different\n")
          	  Rebase_side_effect()
              clib.exit(1)
          end



    end)
end