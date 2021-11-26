require "ifj21"

global func : function(integer) : string

function func(n : integer) : integer
    return 5
end

function main()
    local a : integer = 1
    local b : string = func(a)
end

main()
