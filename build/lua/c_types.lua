

---@class Clib
---@field load_string fun(path:string):string
---@field get_char fun(path:string,i:number):string
---@field print fun(value:boolean | string | number)
---@field get_str_size fun(value:string): number
---@field concat_path fun(path:string,path_to_concat:string):string
---@field extract_dir fun(path:string):string
---@field write_file fun(filename:string,content:string)
---@field get_time fun():number
---@field list_dirs fun():string[],number

---@type Clib
clib = clib
