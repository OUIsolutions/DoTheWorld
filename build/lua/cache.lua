
local function new_cache_element(resource_path,callback)

    local self = {
        resource_path  = resource_path,
        callback = callback,
        hasher = dtw.newHasher()
    }

    self.add_side_effect = function (element)
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


function NewCache(path)

    local self = {
        resource_path = dtw.newResource(path)
    }

    self.new_element =function (callback)
        return new_cache_element(self.resource_path,callback)
    end
    return self;
end
