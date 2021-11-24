require "ifj21"

global func : function(integer, integer) : number, number

function func(n : integer, m : integer) : number
    return n
end

function main()
    local a : integer = 1
    local b : integer = func(a, a)
end

main()
