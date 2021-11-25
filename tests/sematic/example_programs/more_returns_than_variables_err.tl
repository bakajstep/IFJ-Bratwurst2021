require "ifj21"

global func : function(integer) : number, number

function func(n : integer) : number, number
    return 5, 5
end

function main()
    local a : integer = 1
    local b : number = func(a)
end

main()
