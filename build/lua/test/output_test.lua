

---@param expected_content string
---@param artifact TestSpec
---@param output_test string
local function handle_side_effect_expected_file(expected_content,artifact,output_test)
      if expected_content == nil or RECONSTRUCT then
           dtw.write_file(artifact.expected_file_path,output_test)
           clib.print(ANSI_CYAN.."\texpected file:created\n")
      else
          if output_test ~= expected_content then
              clib.print(ANSI_RED.."\texpected file: different\n")
              Rebase_side_effect()
               clib.exit(1)
           end
           clib.print(ANSI_GREEN.."\texpected file: passed\n")
      end

end



---@param cache Cache
---@param original_side_effect_sha string
---@param artifact TestSpec
function Test_out_put(cache,original_side_effect_sha,artifact)

    local output_tested = false

    cache.new_element(function ()
          local expected_content = dtw.load_file(artifact.expected_file_path)

          output_tested = true
          local output_test = clib.system_with_string("./"..artifact.expected_file_path)
          handle_side_effect_expected_file(expected_content,artifact,output_test)

          local current_sidde_effect = dtw.generate_sha_from_file(SIDE_EFFECT)
          if current_sidde_effect ~=original_side_effect_sha then
          	 clib.print(ANSI_YELLOW.."\tside effect folder: no changes\n")
          	 return
          end

          local comparation_provided = dtw.isdir(artifact.side_effect_folder_path)
          if comparation_provided == false or RECONSTRUCT then
          	 dtw.move_any_overwriting(SIDE_EFFECT,artifact.side_effect_folder_path)
          	 Rebase_side_effect()
             clib.print(ANSI_MAGENTA.."\tside effect folder: recreated\n")
             return
          end

          local comparation_sha = dtw.generate_sha_from_folder_by_content(artifact.side_effect_folder_path)
          if comparation_sha ~=original_side_effect_sha then
          	   clib.print(ANSI_RED.."\tside effect folder: diffeent\n")
          	   Rebase_side_effect()
               clib.exit(1)
          end

          clib.print(ANSI_GREEN.."\tside effect folder: passed\n")
          Rebase_side_effect()

    end).
    add_dependencie(artifact.executable_sha).
    add_dependencie(original_side_effect_sha).
    perform()

    if output_tested == false then
    	clib.print(ANSI_YELLOW.."output test: cached\n")
    end

end