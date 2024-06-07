

---@class CacheCallback
---@field add_dependencie fun(dependencie:string):CacheCallback
---@field perform fun():string


---@class Cache
---@field new_element fun(callback:fun():string | nil):CacheCallback