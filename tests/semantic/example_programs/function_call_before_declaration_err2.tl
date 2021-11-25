require "ifj21"

function funcA(n : integer) : number
    return funcB(n)
end

function main()
    local a : integer = 1
    local b : number = funcA(a)
end

main()


function funcB(n : integer) : number
    return n
end
