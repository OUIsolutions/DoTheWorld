

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

---@type Clib
clib = clib
