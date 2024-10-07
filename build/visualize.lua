


---@param start_point string
---@param already_included_list  StringArray | nil
---@return string
  function Generate_amalgamation_recursive(start_point,already_included_list)


    if already_included_list == nil then
    	already_included_list = Created_already_included()
    end

    local start_point_sha = dtw.generate_sha_from_file(start_point)
    if already_included_list.is_included(start_point_sha) then
    	clib.print(ANSI_YELLOW.."file"..start_point.."already included\n")
    	return ""
    end

    already_included_list.append(start_point_sha)


    local content = dtw.load_file(start_point)

    local size = clib.get_str_size(content)
    local inside_string = false
    local waiting_include = false
    local string_buffer = ""
    local final_text = ""
    for i=1,size do
        local is_start_string = Verify_if_is_start_string_char(content,i,inside_string)
        if is_start_string  then
        	inside_string = true
        end

        local is_end_string = Verify_if_is_end_string_char(is_start_string,content,i,inside_string)

       if Include_char_to_string_buffer(is_start_string,is_end_string,inside_string) then
            string_buffer = string_buffer..clib.get_char(content,i)
        end

       if Include_string_buffer_to_final(waiting_include,is_end_string) then
            final_text = final_text..'"'..string_buffer..'"'
        end

        if Is_include_point(content,i,inside_string) then
        	waiting_include = true
        end

        if Anulate_inclusion(waiting_include,content,i) then
            final_text = final_text.."#include "
        	waiting_include = false
        end

        if Include_char_to_final(waiting_include,inside_string) then
        	final_text = final_text..clib.get_char(content,i)
        end



        if Make_recursive_call(waiting_include,is_end_string) then
            local dir = dtw.newPath(start_point).get_dir()
            local full_path = dtw.concat_path(dir,string_buffer)

            local acumulated = Generate_amalgamation_recursive(full_path,already_included_list)
            final_text = final_text.. acumulated.."\n"

        	waiting_include = false
        end

        if is_end_string then
           inside_string = false
           string_buffer = ""
        end

    end

    clib.print(ANSI_GREEN.."amalgamated: "..start_point.."\n")
    return final_text
end


---@param waiting_include boolean
---@param inside_string boolean
 function Include_char_to_final(waiting_include,inside_string)

    if waiting_include then
    	return false
    end
    if inside_string then
    	return false
    end
    return true
end
---@param waiting_include boolean
---@param is_end_string boolean
 function Include_string_buffer_to_final(waiting_include,is_end_string)

    if waiting_include then
    	return false
    end
    if is_end_string then
    	return true
    end

    return false
end
---@param content string
---@param index number
---@param inside_string boolean
 function Is_include_point(content,index,inside_string)

    if inside_string then
    	return false
    end

    local INCLUDE_TEXT  = "#include"
    local content_size = clib.get_str_size(content)
    local include_size = clib.get_str_size(INCLUDE_TEXT)
    if index + include_size >= content_size then
    	return false
    end
    local buffer = ""
    for i=index,index + include_size -1 do
    	buffer = buffer..clib.get_char(content,i)
    end

    return buffer == INCLUDE_TEXT
end

---@param is_start_string boolean
---@param is_end_string boolean
---@param is_inside_string boolean
 function Include_char_to_string_buffer(is_start_string,is_end_string,is_inside_string)
    if is_start_string then
    	return false
    end
    if is_end_string then
    	return false
    end
    if is_inside_string then
    	return true
    end

    return false
end

---@param  waiting_include boolean
---@param is_end_string boolean
 function Make_recursive_call(waiting_include,is_end_string)
	if waiting_include and is_end_string then
		return true
	end
end

---@param waiting_include boolean
---@param content string
---@param index number
 function Anulate_inclusion(waiting_include,content,index)
    if waiting_include == false then
    	return false
    end
    if clib.get_char(content,index) == "<" then
    	return true
    end
    return false
end


---@class StringArray
---@field size number
---@field elements string[]
---@field append fun(element:string)
---@field is_included fun(element:string):boolean

---@return StringArray
function  Created_already_included()
	local self  = {
	    size = 0,
	    elements = {}
	}

	self.append = function (element)
	    self.size = self.size +1
        self.elements[self.size] = element
	end

	self.is_included = function (element)
		for i=1,self.size do
			if self.elements[i] == element then
				return true
			end
		end
		return false
	end
	return self

end

---@param content string
---@param index number
---@param inside_string boolean
 function Verify_if_is_start_string_char(content,index,inside_string)
	if inside_string == true then
		return false
	end
	local last_char = clib.get_char(content,index-1)
    if last_char == '\\' then
    	return false
    end
    local current_char = clib.get_char(content,index)
    if current_char == '"' then
    	return true
    end
    return false
end


 function Verify_if_is_end_string_char(is_start_string_char,content,index,inside_string)
    if is_start_string_char then
    	return false
    end

    if inside_string == false then
    	return false
    end

    local last_last_char = clib.get_char(content,index-2)
    local last_char = clib.get_char(content,index-1)
    local current_char = clib.get_char(content,index)
    local scape = last_char == '\\' and last_last_char ~="\\"
    if current_char == '"' and scape == false  then
    	return true
    end
    return false
end



---@class Clib
---@field load_string fun(path:string):string
---@field get_char fun(path:string,i:number):string
---@field print fun(value:boolean | string | number)
---@field get_str_size fun(value:string): number
---@field get_time fun():number
---@field exit fun(status:number):number
---@field system_with_status fun(comand:string):number
---@field system_with_string fun(comand:string):string
---@field indexof fun(content:string,comparation:string):number
---@field out_extension fun():string
---@field replace fun(content:string,target:string,value_to_replace:string):string
---@field trim fun(content:string):string

---@type Clib
clib = clib

---@param function_name string
---@param resource_path DtwResource
---@param callback fun():string
---@return CacheCallback
local function new_cache_element(function_name,resource_path,callback)

    local self = {
        resource_path  = resource_path,
        callback = callback,
        hasher = dtw.newHasher()
    }
    self.hasher.digest(function_name)

    self.add_dependencie = function (element)
    	   self.hasher.digest(element)
    	   return self
    end

    self.perform = function ()
        local sha = self.hasher.get_value()
        local sha_resource = resource_path.sub_resource(sha)
        local possible_element = sha_resource.get_string()
        if possible_element then
        	return possible_element
        end
        local result = self.callback()
        if result == nil then
        	result = ""
        end
        sha_resource.set_value(result)
        sha_resource.commit()
        return result
    end
    return self;

end

---@param path string
---@return Cache
function NewCache(path)


    local self = {
        resource_path = dtw.newResource(path)
    }

    self.new_element =function (function_name,callback)
        return new_cache_element(function_name,self.resource_path,callback)
    end
    return self;
end


---@class CacheCallback
---@field hasher DtwHasher
---@field callback fun():string or nil
---@field add_dependencie fun(dependencie:string):CacheCallback
---@field perform fun():string


---@class Cache
---@field new_element fun(function_name:string,callback:fun():string | nil):CacheCallbackANSI_RED = "\x1b[31m"
ANSI_GREEN = "\x1b[32m"
ANSI_YELLOW = "\x1b[33m"
ANSI_BLUE = "\x1b[34m"
ANSI_MAGENTA= "\x1b[35m"
ANSI_CYAN= "\x1b[36m"
ANSI_RESET ="\x1b[0m"START_POINT              = "src/one.c"
DECLARATION_POINT        = "src/declaration.h"
DEFINITION_POINT         = "src/definition.c"
LINUX_COMPILER           = "gcc"
WINDOWS_COMPILER         = "x86_64-w64-mingw32-gcc"
RELEASE_FOLDER           = "release"
CJSON_NAME               = "cJSON.o"
CJSON_LOCATION           = "src/dependencies/cJSON/cJSON.c"
SHA_256_NAME             = "sha256.o"
SHA_256_LOCATION         = "src/dependencies/sha256/sha-256.c"
LIB_NAME                 = "doTheWorld.o"

PRECOMPILED_LINUX        = "pre_compiled_linux.zip"
PRECOMPILED_WINDOWS      = "pre_compiled_windows.zip"

OUTPUT_DECLARATION       = "doTheWorldDeclaration.h"
OUTPUT_SINGLE_FILE       = "doTheWorld.h"
OUTPUT_DECLARATION       = "doTheWorld_declaration.h"
OUTPUT_DEFINITION        = "doTheWorld_definition.c"
END_TEST_POINT           = "tests/doTheWorld_test.h"
SIDE_EFFECT              = "tests/target"
TEST_POINT               = "tests/main_test"
LIB_FOLDER               = "src"
CACHE_POINT              = "cache2"
EXAMPLES_FOLDER          = "exemples"
TEST_FILE                = "exec.c"
TEST_INPREDICTBILE_START = "S_"
TEST_PREDICIBLE_START    = "T_"
EXPECTED_NAME            = "expected.txt"
CODEOF_TEXT              = "codeof"
SIDE_EFFECT_COMPARATION  = "side_effect"
LOCKER_FILE_PATH         = "tests/locker_test/locker_test.c"
LOCKER_OUTPUT_PATH       = "tests/locker_test/locker_test.out"
LOCKER_WRITE_FILE        = "append.txt"
RECONSTRUCT              = false
SIDE_EFFECT_COPY = "side_effect_copy"
OUTPUT_TEST ="output_test"
function Create_examples()
    dtw.remove_any(EXAMPLES_FOLDER)
    local test_tree = dtw.newTree_from_hardware(TEST_POINT)
    test_tree.each(function(tree_part)
        local path = tree_part.path

        if path.get_name() ~= "exec.c" then
            return
        end
        local content = tree_part.get_value()
        local formated_content = clib.replace(content, "../", "")
        formated_content = clib.replace(formated_content, "doTheWorld_test.h", OUTPUT_SINGLE_FILE);
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
        clib.print(ANSI_GREEN .. "created example" .. path.get_full_path() .. "\n")
    end)
    test_tree.commit()
end

---@param folder string
---@return string
function Generate_sha_from_folder_not_considering_empty_folders(folder)
	local hasher = dtw.newHasher()
	local files,files_size = dtw.list_files_recursively(folder)
	for i=1,files_size do
	    local current_file = files[i]
	    local file_path = dtw.concat_path(folder,current_file)
	    local content = dtw.load_file(file_path)
		hasher.digest(current_file)
		hasher.digest(content)
	end
	local dirs,dirs_size = dtw.list_dirs_recursively(folder)
	for i=1,dirs_size do
	    local current_dir = dirs[i]
	    local dir_path = dtw.concat_path(folder,current_dir)
		local ignore,size= dtw.list_files_recursively(dir_path,false)
		if size > 0 then
			hasher.digest(current_dir)
		end
	end
	return hasher.get_value()
end

---@param content string
local function  count_break_lines(content)
	local size = clib.get_str_size(content)
	local total =0
	for i=1,size do
		if clib.get_char(content,i) == "\n" then
			total = total+1
		end
	end
	return total
end
function  Execute_locker_test()

	local compilation_comand = "gcc "..LOCKER_FILE_PATH.." -o "..LOCKER_OUTPUT_PATH
	local status = clib.system_with_status(compilation_comand)

    if status ~= 0 then
          clib.print(ANSI_RED.."locker complation fail")
          clib.exit(1)
    end
    local TOTAL_TESTS = 10
    for i=1,TOTAL_TESTS do
       clib.system_with_string("./"..LOCKER_OUTPUT_PATH)
       local locker_write_path = dtw.concat_path(SIDE_EFFECT,LOCKER_WRITE_FILE)
       local locker_write_content = dtw.load_file(locker_write_path)
       if locker_write_content == nil then
       	    clib.print(ANSI_RED.."locker fail\n")
       	    Rebase_side_effect()
       	    clib.exit(1)
       	    return
       end
       local total_break_lines = count_break_lines(locker_write_content)

       if total_break_lines == 10 then
       	  clib.print(ANSI_GREEN.."locker test "..i.." passed\n")
       else
            clib.print(ANSI_RED.."locker test fail\n")
            Rebase_side_effect()
            clib.exit(1)
       end
    end

    Rebase_side_effect()


  end

---@class DtwTreePart
---@field path DtwPath
---@field get_value fun():string
---@field set_value fun(value:string | number | boolean | DtwTreePart | DtwResource | DtwActionTransaction)
---@field hardware_remove fun(as_transaction:boolean|nil):DtwTreePart
---@field hardware_write fun(as_transaction:boolean|nil):DtwTreePart
---@field hardware_modify fun(as_transaction:boolean|nil):DtwTreePart
---@field get_sha fun():string
---@field is_blob fun():boolean
---@field unload fun():DtwTreePart
---@field load fun():DtwTreePart


---@class DtwTree
---@field newTreePart_empty fun ():DtwTreePart
---@field newTreePart_loading fun ():DtwTreePart
---@field get_tree_part_by_index fun(index:number):DtwTreePart
---@field insecure_hardware_write_tree fun():DtwTree
---@field insecure_hardware_remove fun():DtwTree
---@field commit fun():DtwTree
---@field get_size fun():number
---@field get_tree_part_by_name fun(name:string):DtwTreePart
---@field get_tree_part_by_path fun(name:string):DtwTreePart
---@field find fun(callback: fun(part:DtwTreePart):boolean):DtwTreePart
---@field count fun(callback: fun(part:DtwTreePart):boolean):number
---@field map fun(callback: fun(part:DtwTreePart):any):any[]
---@field each fun(callback: fun(part:DtwTreePart))
---@field dump_to_json_string fun():string
---@field dump_to_json_file fun():DtwTree

---@class DtwPath
---@field path_changed fun():boolean
---@field add_start_dir fun(start_dir:string):DtwPath
---@field add_end_dir_method fun (end_dir:string):DtwPath
---@field changed fun():boolean
---@field get_dir fun():string
---@field get_extension fun():string
---@field get_name fun():string
---@field get_only_name fun():string
---@field get_full_path fun():string
---@field set_name fun(new_name:string) DtwPath
---@field set_only_name fun(new_name:string) DtwPath
---@field set_extension fun(extension:string):DtwPath
---@field set_dir fun(dir:string):DtwPath
---@field set_path fun(path:string):DtwPath
---@field replace_dirs fun(old_dir:string,new_dir:string):DtwPath
---@field get_total_dirs fun():number
---@field get_sub_dirs_from_index fun(start:number,end:number):string
---@field insert_dir_at_index fun(index:number,dir:string):DtwPath
---@field remove_sub_dir_at_index fun(start:number,end:number):DtwPath
---@field insert_dir_after fun(point:string, dir:string):DtwPath
---@field insert_dir_before fun(point:string, dir:string):DtwPath
---@field remove_dir_at fun(point:string):DtwPath
---@field unpack fun():string[],number



---@class DtwHasher
---@field digest fun(value:string | number | boolean | string ):DtwHasher
---@field digest_file fun(source:string):DtwHasher
---@field digest_folder_by_content fun(source:string):DtwHasher
---@field digest_folder_by_last_modification fun(source:string):DtwHasher
---@field get_value fun():string

---@class DtwActionTransaction
---@field get_type_code fun():number
---@field get_type fun():string
---@field get_content fun():string
---@field set_content fun()
---@field get_source fun():string
---@field get_dest fun():string
---@field set_dest fun():string




---@class DtwTransaction
---@field write fun(src :string , value:string | number | boolean | string | DtwResource ):DtwTransaction
---@field remove_any fun(src:string):DtwTransaction
---@field copy_any fun(src:string,dest:string):DtwTransaction
---@field move_any fun(src:string,dest:string):DtwTransaction
---@field dump_to_json_string fun():string
---@field dump_to_json_file fun(src:string):DtwTransaction
---@field each fun(callbac: fun(value:DtwActionTransaction))
---@field map fun(callbac: fun(value:DtwActionTransaction):any):any[]
---@field find fun(callbac: fun(value:DtwActionTransaction):boolean):DtwActionTransaction
---@field count fun(callbac: fun(value:DtwActionTransaction):boolean):number
---@field __index fun(index:number):DtwActionTransaction
---@field get_action fun(index:number):DtwActionTransaction
---@field commit fun():DtwTransaction


---@class DtwSchema
---@field add_primary_keys fun(values:string | string[])
---@field sub_schema fun(values:string | string[])

---@class DtwResource
---@field schema_new_insertion fun():DtwResource
---@field dangerous_remove_prop fun(primary_key:string)
---@field dangerous_rename_prop fun(primary_key:string ,new_name:string)
---@field get_resource_matching_primary_key fun(primary_key: string,  value:string | number | boolean | Dtwblobs | DtwResource ):DtwResource
---@field get_resource_by_name_id fun(id_name:string)
---@field schema_list fun(): DtwResource[]
---@field schema_each fun(callback:fun(value:DtwResource))
---@field schema_find fun(callback:fun(value:DtwResource):boolean):DtwResource
---@field schema_map fun(callback:fun(value:DtwResource):any)
---@field schema_count fun(callback:fun(value:DtwResource):boolean):number
---@field sub_resource fun(str:string) :DtwResource
---@field sub_resource_next fun(str:string) :DtwResource
---@field sub_resource_now fun(str:string) :DtwResource
---@field sub_resource_now_in_unix fun(str:string) :DtwResource
---@field __index fun(str:string) : number ,DtwResource
---@field get_value fun():string | number | boolean | nil | string
---@field get_string fun():string | nil
---@field get_number fun(): number | nil
---@field get_bool fun(): boolean | nil
---@field set_value fun(value:string | number | boolean | string | DtwResource )
---@field commit fun()  apply the modifications
---@field lock fun() lock the resource from other process
---@field unlock fun()
---@field unload fun() unload the content
---@field get_path_string fun() :string
---@field each fun(callback :fun(element:DtwResource))
---@field set_extension fun(extension:string)
---@field list fun(): DtwResource[]
---@field destroy fun()
---@field set_value_in_sub_resource fun(key:string ,value:string | number | boolean | string | DtwResource )
---@field get_value_from_sub_resource fun(key:string):string | number | boolean | nil | string
---@field newSchema fun():DtwSchema


---@class DtwModule
---@field copy_any_overwriting fun(src:string,dest:string):boolean returns true if the operation were ok otherwise false
---@field copy_any_merging   fun(src:string,dest:string):boolean returns true if the operation were ok otherwise false
---@field move_any_overwriting fun(src:string,dest:string):boolean returns true if the operation were ok otherwise false
---@field move_any_merging fun(src:string,dest:string):boolean returns true if the operation were ok otherwise false
---@field remove_any fun(src:string):boolean returns true if the operation were ok otherwise false
---@field base64_encode_file fun(src:string):string transform file into base64
---@field base64_encode fun(value:string | number | boolean | string):string transform content into base64
---@field base64_decode fun(value:string): string | string retransform base64 into normal value
---@field list_files fun(src:string,concat_path:boolean|nil):string[],number
---@field list_dirs fun(src:string,concat_path:boolean|nil):string[],number
---@field list_all fun(src:string,concat_path:boolean|nil):string[],number
---@field list_files_recursively fun(src:string,concat_path:boolean|nil):string[],number
---@field list_dirs_recursively fun(src:string,concat_path:boolean|nil):string[],number
---@field list_all_recursively fun(src:string,concat_path:boolean|nil):string[],number
---@field load_file fun(src:string):string | string
---@field write_file fun(src:string,value:string | number | boolean | DtwTreePart | DtwResource | DtwActionTransaction)
---@field is_blob fun(value:any):boolean returns if a value is a blob
---@field newResource fun(src:string):DtwResource
---@field generate_sha fun(value:string | number | boolean | string):string
---@field generate_sha_from_file fun(src:string):string
---@field generate_sha_from_folder_by_content fun(src:string):string
---@field generate_sha_from_folder_by_last_modification fun(src:string):string
---@field newHasher fun():DtwHasher
---@field isdir fun(path:string):boolean
---@field isfile fun(path:string):boolean
---@field isfile_blob fun(path:string):boolean
---@field newTransaction fun():DtwTransaction
---@field newTransaction_from_file fun():DtwTransaction
---@field newTransaction_from_json_string fun():DtwTransaction
---@field newPath fun(path:string):DtwPath
---@field newTree fun():DtwTree
---@field newTree_from_hardware fun(path:string):DtwTree
---@field concat_path fun(path1:string,path2:string):string
---@field starts_with fun(comparation:string,prefix:string):boolean
---@field ends_with fun(comparation:string,sulfix:string):boolean



---@type DtwModule
dtw = dtw

---@param content string
---@param index number
local function is_codeof_at_point(content,index)
    local codeof_size = clib.get_str_size(CODEOF_TEXT)
    local content_size = clib.get_str_size(content)
    if index + codeof_size >= content_size then
    	return false
    end

    local buffer = ""
    for i=index,index + codeof_size -1 do
    	buffer = buffer..clib.get_char(content,i)
    end

    return buffer == CODEOF_TEXT

end


---@return string |nil
function Create_readme()
    local content = dtw.load_file("build/INTERNAL.md")
    if content == nil then
    	clib.print("intenal readme not found\n")
    	clib.exit(1)
        return
    end

    local i = 1
    local size = clib.get_str_size(content)
    local codeof_size = clib.get_str_size(CODEOF_TEXT)

    local colecting = false
    local final_text = ""
    local path = ""
    while i < size do

        if is_codeof_at_point(content,i) then
            colecting = true
            i = i + codeof_size+1
        end
        local is_end_char = clib.get_char(content,i) == "\n"

        if colecting and not  is_end_char   then
            path = path..clib.get_char(content,i)
        end

        if colecting ==false then
        	final_text = final_text..clib.get_char(content,i)
        end

        if colecting and is_end_char then
            path = clib.trim(path)
        	local file_content = dtw.load_file(path)
        	if file_content == nil then

        		clib.print(ANSI_RED.."file ("..path..") not found\n")
        		clib.exit(1)
        	end

            local extension = dtw.newPath(path).get_extension()
            final_text = final_text.."\n~~~"..extension.."\n"..file_content.."\n~~~\n"
            colecting = false
            path =""
        end




    	i = i + 1
    end
    return final_text

end
IMPREDITIBLE = 1
PREDICTIBLE = 2

---@class TestArtifact
---@field test_type number
---@field test_dir string | nil
---@field expected_file_path string | nil
---@field executable_path string |nil
---@field c_path string | nil
---@field side_effect_folder_path string | nil
---@field c_sha string
---@field executable_sha string
---@field side_effect_sha string | nil
---@param content string
---@return TestArtifact | nil
 function Get_test_spec(content)

     local path = dtw.newPath(content)
     local filename = path.get_name()
     if filename ~= TEST_FILE then
     	return nil
     end
     local test = {}
     local dirs,size = path.unpack()
     for i=1,size do
        local current_dir = dirs[i]
        if dtw.starts_with(current_dir,TEST_INPREDICTBILE_START) then
        	test.test_type = IMPREDITIBLE
        end
        if dtw.starts_with(current_dir,TEST_PREDICIBLE_START) then
        	test.test_type = PREDICTIBLE
        end
     end

     if test.test_type == nil then
     	return nil
     end

     test.test_dir = path.get_dir()
     test.expected_file_path = dtw.concat_path(test.test_dir,EXPECTED_NAME)
     test.executable_path = dtw.concat_path(test.test_dir,"exec."..clib.out_extension())
     test.c_path = path.get_full_path()
     test.side_effect_folder_path = dtw.concat_path(test.test_dir,SIDE_EFFECT_COMPARATION)
     return test
end
---@param cache Cache
---@param src_sha string
---@param artifact TestArtifact
function Execute_compilation(cache,src_sha,artifact)

    local compiled = false
    cache.new_element("compilation",function ()
        compiled = true
        local comand = "gcc "..artifact.c_path.." -DDTW_DEBUG_TIME -o "..artifact.executable_path
        local result = clib.system_with_status(comand)
        if result ~=0 then
        	clib.exit(1)
        end
        clib.print(ANSI_GREEN.."\tcompilation:passed\n")
    end).
    add_dependencie(src_sha).
    add_dependencie(artifact.c_sha).
    perform()

    if compiled == false then
        clib.print(ANSI_YELLOW.."\tcompilation:cached\n")
    end
end


 function Rebase_side_effect()
	        dtw.copy_any_overwriting(SIDE_EFFECT_COPY,SIDE_EFFECT)

end


---@param cache Cache
---@param src_sha string
---@param original_side_effect_sha string
---@param artifact TestArtifact
local function execute_test_artifact(cache,src_sha,original_side_effect_sha,artifact)

    clib.print(ANSI_BLUE.."testing: "..artifact.c_path.."\n")

    artifact.c_sha = dtw.generate_sha_from_file(artifact.c_path)

    Execute_compilation(cache,src_sha,artifact)
    artifact.executable_sha = dtw.generate_sha_from_file(artifact.executable_path)


    Exec_valgrind_test(cache,original_side_effect_sha,artifact)

    Test_out_put(cache,original_side_effect_sha,artifact)


end


---@param cache Cache
---@param src_sha string
function Execute_full_test(cache,src_sha)

    local original_side_effect_sha =  Generate_sha_from_folder_not_considering_empty_folders(SIDE_EFFECT)
    dtw.copy_any_overwriting(SIDE_EFFECT,SIDE_EFFECT_COPY)

    local listage,size =dtw.list_files_recursively(TEST_POINT,true)

    for i=1,size do
    	local possible_test = listage[i]
        local test = Get_test_spec(possible_test)
        if test ~= nil then
            execute_test_artifact(cache,src_sha,original_side_effect_sha,test)
        end

    end
end

---@param expected_content string
---@param artifact TestArtifact
---@param output_test string
local function handle_expected_file(expected_content,artifact,output_test)


      if expected_content == nil  then
           dtw.write_file(artifact.expected_file_path,output_test)
           clib.print(ANSI_CYAN.."\texpected file:created\n")
            return
      end
      if output_test == expected_content then
           clib.print(ANSI_GREEN.."\texpected file: passed\n")
           return
      end

      if RECONSTRUCT then
        dtw.write_file(artifact.expected_file_path,output_test)
        clib.print(ANSI_MAGENTA.."\texpected file:reconstructed\n")
        return
      end
      if artifact.test_type == PREDICTIBLE then
      	      clib.print(ANSI_RED.."\texpected file: different\n")
              Rebase_side_effect()
              clib.exit(1)
      end
      if artifact.test_type== IMPREDITIBLE then
      	 clib.print(ANSI_YELLOW.."\texpected file: impredictible\n")
      end



end


---@param original_side_effect_sha string
---@param artifact TestArtifact
local function handle_side_effect_folder(original_side_effect_sha,artifact)

      local current_sidde_effect =Generate_sha_from_folder_not_considering_empty_folders(SIDE_EFFECT)

      if current_sidde_effect == original_side_effect_sha then
         clib.print(ANSI_YELLOW.."\tside effect folder: no changes\n")
         return
      end



      if artifact.side_effect_sha == nil  then
         dtw.move_any_overwriting(SIDE_EFFECT,artifact.side_effect_folder_path)
         clib.print(ANSI_CYAN.."\tside effect folder: created\n")
         return
      end

      if artifact.test_type == IMPREDITIBLE then
      	  clib.print(ANSI_YELLOW.."\tside effect folder: impredictible\n")
          return
      end

      if RECONSTRUCT then
         dtw.move_any_overwriting(SIDE_EFFECT,artifact.side_effect_folder_path)
         clib.print(ANSI_MAGENTA.."\tside effect folder: recreated\n")
         return
      end

      if artifact.side_effect_sha ~=current_sidde_effect then
           clib.print(ANSI_RED.."\tside effect folder: diffeent\n")
           Rebase_side_effect()
           clib.exit(1)
      end

      clib.print(ANSI_GREEN.."\tside effect folder: passed\n")
end

---@param cache Cache
---@param original_side_effect_sha string
---@param artifact TestArtifact
function Test_out_put(cache,original_side_effect_sha,artifact)

    local output_tested = false
    local expected_content = dtw.load_file(artifact.expected_file_path)

    local out_cache = cache.new_element("output",function ()

          output_tested = true
          local output_test = clib.system_with_string("./"..artifact.executable_path)
          handle_expected_file(expected_content,artifact,output_test)
          handle_side_effect_folder(original_side_effect_sha,artifact)
          Rebase_side_effect()

    end).
    add_dependencie(artifact.executable_sha).
    add_dependencie(original_side_effect_sha)


    if dtw.isdir(artifact.side_effect_folder_path) then
       artifact.side_effect_sha = Generate_sha_from_folder_not_considering_empty_folders(artifact.side_effect_folder_path)
        out_cache.add_dependencie(artifact.side_effect_sha)
    end

    if expected_content ~=nil and artifact.test_type == PREDICTIBLE then
    	out_cache.add_dependencie(expected_content)
    end


    out_cache.perform()


    if output_tested == false then
    	clib.print(ANSI_YELLOW.."\toutput test: cached\n")
    end

end

---@param cache Cache
---@param original_side_effect_sha string
---@param artifact TestArtifact
 function Exec_valgrind_test(cache,original_side_effect_sha,artifact)
    local memory_tested = false
    cache.new_element("valgrind",function ()
        memory_tested =true
        local comand = "valgrind --log-file='"..OUTPUT_TEST.."' ./"..artifact.executable_path
        clib.system_with_string(comand);
        Rebase_side_effect()

        local result = dtw.load_file(OUTPUT_TEST)
        if result == nil then
            clib.exit(1)
            return
        end

        local HEAP_CHECK  = "All heap blocks were freed -- no leaks are possible"
        local error =false
        if clib.indexof(result,HEAP_CHECK) == -1 then
        	error = true
        end
        local ERROR_CHECK = "ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)"
        if clib.indexof(result,ERROR_CHECK) == -1 then
          error = true
        end

        if error then
            clib.print(ANSI_RED..result)
        	clib.exit(1)
        end
        clib.print(ANSI_GREEN.."\tmemory test:passed\n")
end).
    add_dependencie(artifact.executable_sha).
    add_dependencie(original_side_effect_sha).
    perform()

    if memory_tested == false then
        clib.print(ANSI_YELLOW.."\tmemory test:cached\n")
    end
end
