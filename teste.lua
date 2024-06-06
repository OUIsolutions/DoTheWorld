

local function qualquer_coisa()
    
    local variavel = "aaa"

    local tabela = {
        nome="mateus",
        v = variavel
    }
    return tabela
end
function teste()
   local  v = qualquer_coisa()    
   return "auqalque coisa"
end

local x = teste()

