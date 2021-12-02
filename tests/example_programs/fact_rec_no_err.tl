-- Program 2: Vypocet faktorialu (rekurzivne)
require "ifj21"

function factorial(n : integer) : integer
	local a : integer local b : integer local c : integer
	local n1 : integer = n - 1
	if n < 2 then
		return 1
	else
		local tmp : integer = factorial(n1)
		--a,b,c = 1,2,3
		return n1
        a,b,c = 1,2,3
	end
end

function main()
	write("Zadejte cislo pro vypocet faktorialu: ")
	local a : integer = readi()
	if a ~= nil then
		if a < 0 then
			write("Faktorial nejde spocitat!", "\n")
		else
			local vysl : integer = factorial(a)
			write("Vysledek je ", vysl, "\n")
		end
	else
		write("Chyba pri nacitani celeho cisla!\n")
	end
end

main()
