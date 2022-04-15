# IFJ-Bratwurst2021
Implementace překladače imperativního jazyka IFJ21 [VUT-FIT][fit] 2021.


## :bust_in_silhouette: Autoři

Bratwursti

- xbakaj00 - Štěpán Bakaj
- xchoch09 - David Chocholatý
- xkanko00 - Adam Kaňkovský
- xserej00 - Radek Šerejch

## :medal_sports: Finální hodnocení

Procentuální hodnocení modulů překladače:
- Lexikální analýza (detekce chyb): 89 % (155/174)
- Syntaktická analýza (detekce chyb): 90 % (174/192)
- Sémantická analýza (detekce chyb): 93 % (274/294)
- Sémantické/běhové chyby (detekce): 48 % (30/62)
- Interpretace přeloženého kódu (základní): 98 % (300/305)
- Interpretace přeloženého kódu (výrazy, vest. funkce): 72 % (144/198)
- Interpretace přeloženého kódu (komplexní): 14 % (51/343)
- BOOLTHEN 0 % (0/170)
- CYCLES 0 % (0/150)
- FUNEXP 0 % (0/150)
- OPERATORS 0 % (0/50)
- Celkem bez rozšíření: 71 % (1128/1568)

Obdržené body:
- Implementace: 12,37/15
- Dokumentace: 5/5

## :spiral_notepad: Spuštění testů
* Lexikální analýza
```console
  make lex-test; make lex-clean
```

* Syntaktická analýza
```console
  make syntax-test; make syntax-clean
```

* Sémantická analýza
```console
  make semantic-test; make semantic-clean
```

* Generování kódu
```console
  make gen-test; make gen-clean
```


* Testy od studentů FIT VUT BIT
```console    
  make; cd tests/disc_test/; ./ifjtest; cd tmp; rm -rfv *; cd ..; rmdir tmp; cd ..; cd ..
```


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
* [Autoři studentských testů](https://github.com/bakajstep/IFJ-Bratwurst2021/tree/main/tests/disc_test)

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
