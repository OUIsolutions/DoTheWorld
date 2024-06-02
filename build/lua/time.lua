
DebugTime = true

function New_time(function_name)
	local self = {
        name=function_name,
        acumulation = 0,
        total = 0
	}

	self.start_time = function ()
        if DebugTime == false then
        	return
        end
	    self.total = self.total+1
        self.start_point = clib.get_time()
	end

	self.end_time = function ()
        if DebugTime == false then
            return
        end
		local end_time = clib.get_time();
		local duration =end_time -  self.start_point
		self.acumulation = self.acumulation + duration
	end

	self.get_median = function ()
        if DebugTime == false then
            return
        end
		return self.acumulation / self.total
	end

	self.represent = function ()
        if DebugTime == false then
            return
        end
		clib.print("function:"..self.name.." duration:"..self.get_median().."\n")
	end

    return self
end