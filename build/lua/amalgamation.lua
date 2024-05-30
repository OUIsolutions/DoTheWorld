

local function start_stack(state_machine)

    if state_machine.pending_stack_start  == false then
        return
    end

    state_machine.currrent_stack = state_machine.currrent_stack +1
    state_machine.stack[state_machine.currrent_stack] = {
                content = clib.load_string(state_machine.start_point),
                current_char = nil,
                index = 1
    }
    state_machine.pending_stack_start = false

end

local function get_current_char(state_machine)
    local current_stack = state_machine.state_machine[state_machine.current_stack]
    current_stack.current_char = clib.get_char(current_stack.content,current_stack.index)
end

local function terminate_machine(state_machine)
    if state_machine.current_stack == 0 then
    	state_machine.terminate = true
    end
end

---@param start_point string
---@return string
 function Generate_amalgamation(start_point)
    local state_machine = {
        terminate = false,
        start_point = start_point,
        stack = {},
        pending_stack_start = true,
        current_stack = 0;
    }
    start_stack(state_machine)
    get_current_char(state_machine)

end
