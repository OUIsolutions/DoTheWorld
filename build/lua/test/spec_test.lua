
IMPREDITIBLE = 1
PREDICTIBLE = 2

---@class TestSpec
---@field test_type number
---@field test_dir string | nil
---@field expected_file_path string | nil
---@field executable_path string |nil
---@field c_path string | nil
---@field side_effect_folder_path string | nil
---@field c_sha string
---@field executable_sha string

---@param content string
---@return TestSpec | nil
 function Get_test_spec(content)

     local path = dtw.newPath(content)
     local filename = path.get_name()
     if filename ~= "exec.c" then
     	return nil
     end
     local test = {}
     local dirs,size = path.unpack()
     for i=1,size do
        local current_dir = dirs[i]
        if dtw.starts_with(current_dir,"S_") then
        	test.test_type = IMPREDITIBLE
        end
        if dtw.starts_with(current_dir,"T_") then
        	test.test_type = PREDICTIBLE
        end
     end

     if test.test_type == nil then
     	return nil
     end

     test.test_dir = path.get_dir()
     test.expected_file_path = dtw.concat_path(test.test_dir,"expected.txt")
     test.executable_path = dtw.concat_path(test.test_dir,"exec."..clib.out_extension())
     test.c_path = path.get_full_path()
     test.side_effect_folder_path = dtw.concat_path(test.test_dir,"side_effect")
     return test
end