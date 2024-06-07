
---@param folder string
---@return string
function Generate_sha_from_folder_not_considering_empty_folders(folder)
	local hasher = dtw.newHasher()
	local files,files_size = dtw.list_files_recursively(folder,true)
	for i=1,files_size do
	    local current_file = files[i]
	    local content = dtw.load_file(current_file)
		hasher.digest(content)
	end
	local dirs,dirs_size = dtw.list_dirs_recursively(folder,false)
	for i=1,dirs_size do
	    local current_dir = dirs[i]
		local ignore,size= dtw.list_files_recursively(current_dir,false)
		if size > 0 then
			hasher.digest(current_dir)
		end
	end
	return hasher.get_value()
end
