# IFJ-Bratwurst2021
Implementace překladače imperativního jazyka IFJ21 [VUT-FIT][fit] 2021.


## :bust_in_silhouette: Autoři

Bratwursti

- xbakaj00 - Štěpán Bakaj
- xchoch09 - David Chocholatý
- xkanko00 - Adam Kaňkovský
- xserej00 - Radek Šerejch

## :spiral_notepad: Spuštění testů
* Lexikální analýza
  make lex-test
  make lex-clean

* Syntaktická analýza
  make syntax-test
  make syntax-clean
  
* Sémantická analýza
  make semantic-test
  make semantic-clean
    
* Generování kódu
  make gen-test
  make gen-clean

* Testy od studentů FIT VUT BIT
  make
  cd tests/disc_test/
  ./ifjtest 

## :computer: Technologie
* C - standard C99
* Makefile
* LaTeX

## :package: Repozitář
[https://github.com/bakajstep/IFJ-Bratwurst2021](https://github.com/bakajstep/IFJ-Bratwurst2021)

## :warning: Licence

Program je distribuován s otevřenými zdrojovými texty pod licencí [GNU GPL verze 3][gpl].

## :clap: Poděkování
* [Overleaf](https://www.overleaf.com/)
* [Autoři studentských testů](https://github.com/ondrej-mach/ifjtest?fbclid=IwAR2jtMZJNUb4I3rEZGhuyeYLSoOew-UNi9KxL7KChLGC2llYJJH0kM8SS-o)

## :page_with_curl: Reference
* [Zadání][zadani]

## :writing_hand: Citace
* [Elements of Compiler Design][elements]
* [Průvodce labyrintem algoritmů][pruvodce]

[fit]: https://www.fit.vut.cz/.en "VUT-FIT"
[gpl]: https://github.com/bakajstep/IFJ-Bratwurst2021/blob/main/LICENSE "License"
[zadani]: https://github.com/bakajstep/IFJ-Bratwurst2021/tree/main/doc/zadani/ifj2021.pdf "Zadání"
[elements]: http://pruvodce.ucw.cz/static/pruvodce.pdf "Průvodce labyrintem algoritmů"
[pruvodce]: https://www.fit.vut.cz/research/publication/8538/.cs "Elements of Compiler Design"
