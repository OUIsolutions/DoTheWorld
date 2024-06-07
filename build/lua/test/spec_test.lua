
IMPREDITIBLE = 1
PREDICTIBLE = 2

---@class TestSpec
---@field test_type number
---@field test_dir string


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
     return test
end