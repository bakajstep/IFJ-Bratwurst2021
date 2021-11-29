require "ifj21"

global func : function(integer, integer) : string

function func(n : integer) : string
    return n
end

function main()
    local a : integer = 1
    local b : integer = func(a)
end

main()
