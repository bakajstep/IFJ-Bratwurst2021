require "ifj21"

global func : function(integer, integer) : string

function func(n : integer) : string
    return 5
end

function main()
    local a : integer = 1
    local b : number = func(a)
end

main()
