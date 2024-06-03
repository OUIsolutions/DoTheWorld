

---@class Clib
---@field load_string fun(path:string):string
---@field get_char fun(path:string,i:number):string
---@field print fun(value:boolean | string | number)
---@field get_str_size fun(value:string): number
---@field concat_path fun(path:string,path_to_concat:string):string
---@field extract_dir fun(path:string):string
---@field write_file fun(filename:string,content:string)
---@field get_time fun():number
---@field list_dirs fun(path:string):string[],number
---@field generate_sha_from_string fun(content:string):string
---@field generate_sha_from_folder fun(path:string):string
---@field generate_sha_from_file fun(path:string):string

---@type Clib
clib = clib
