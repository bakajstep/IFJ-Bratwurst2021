PRJ=IFJ21
PROG=$(PRJ)-test

LEX=lex
STX=syntax

MAIN=main
SCAN=scanner
STR=string
ERR=error
PRS=parser
PSA=psa

PROG1=fact_iter
PROG2=fact_rec
PROG3=str_func

CURTEST=_test_cur_
REFTEST=_test_ref_

TESTSDIR=tests
EXPLDIR=example_programs
LEXPATH=$(TESTSDIR)/$(LEX)/
STXPATH=$(TESTSDIR)/$(STX)/
EXPLPATH=$(TESTSDIR)/$(EXPLDIR)/

CC=gcc
CFLAGS=-Wall -Wextra -Werror -pedantic -std=c11

.PHONY: $(LEX)-test $(LEX)-clean $(STX)-test $(STX)-clean

$(LEX)-test:
	$(CC) $(CFLAGS) -o $(LEXPATH)$@ $(SCAN).c $(SCAN).h $(STR).c $(STR).h $(ERR).c $(ERR).h $(LEX)_test.c

	@echo "\n------------------------------------ 'fact_iter' ------------------------------------\n"
	@./$(LEXPATH)$(LEX)-test < $(EXPLPATH)$(PROG1).tl > $(LEXPATH)$(LEX)$(CURTEST)$(PROG1).output	
	@echo "\nTest case 'fact_iter' output differences:"
	@diff -su $(LEXPATH)$(LEX)$(REFTEST)$(PROG1).output $(LEXPATH)$(LEX)$(CURTEST)$(PROG1).output || exit 0
	
	@echo "\n------------------------------------ 'fact_rec' -------------------------------------\n"
	@./$(LEXPATH)$(LEX)-test < $(EXPLPATH)$(PROG2).tl > $(LEXPATH)$(LEX)$(CURTEST)$(PROG2).output	
	@echo "\nTest case 'fact_iter' output differences:"
	@diff -su $(LEXPATH)$(LEX)$(REFTEST)$(PROG2).output $(LEXPATH)$(LEX)$(CURTEST)$(PROG2).output || exit 0

	@echo "\n------------------------------------ 'str_func' -------------------------------------\n"
	@./$(LEXPATH)$(LEX)-test < $(EXPLPATH)$(PROG3).tl > $(LEXPATH)$(LEX)$(CURTEST)$(PROG3).output	
	@echo "\nTest case 'fact_iter' output differences:"
	@diff -su $(LEXPATH)$(LEX)$(REFTEST)$(PROG3).output $(LEXPATH)$(LEX)$(CURTEST)$(PROG3).output || exit 0

$(LEX)-clean:
	cd $(LEXPATH) && rm -f $(LEX)$(CURTEST)$(PROG1).output $(LEX)$(CURTEST)$(PROG2).output $(LEX)$(CURTEST)$(PROG3).output $(LEX)-test

$(STX)-test:
	$(CC) $(CFLAGS) -o $(STXPATH)$@ $(SCAN).c $(SCAN).h $(STR).c $(STR).h $(ERR).c $(ERR).h $(PRS).c $(PRS).h $(PSA).c $(PSA).h $(STX)_test.c
	
	@echo "\n------------------------------------ 'fact_iter' ------------------------------------\n"
	@./$(STXPATH)$(STX)-test < $(EXPLPATH)$(PROG1).tl > $(STXPATH)$(STX)$(CURTEST)$(PROG1).output
	@echo "\nTest case 'fact_iter' output differences:"
	@diff -su $(STXPATH)$(STX)$(REFTEST)$(PROG1).output $(STXPATH)$(STX)$(CURTEST)$(PROG1).output || exit 0

	@echo "\n------------------------------------ 'fact_rec' -------------------------------------\n"
	@./$(STXPATH)$(STX)-test < $(EXPLPATH)$(PROG2).tl > $(STXPATH)$(STX)$(CURTEST)$(PROG2).output	
	@echo "\nTest case 'fact_iter' output differences:"
	@diff -su $(STXPATH)$(STX)$(REFTEST)$(PROG2).output $(STXPATH)$(STX)$(CURTEST)$(PROG2).output || exit 0

	@echo "\n------------------------------------ 'str_func' -------------------------------------\n"
	@./$(STXPATH)$(STX)-test < $(EXPLPATH)$(PROG3).tl > $(STXPATH)$(STX)$(CURTEST)$(PROG3).output	
	@echo "\nTest case 'fact_iter' output differences:"
	@diff -su $(STXPATH)$(STX)$(REFTEST)$(PROG3).output $(STXPATH)$(STX)$(CURTEST)$(PROG3).output || exit 0

$(STX)-clean:
	cd $(STXPATH) && rm -f $(STX)$(CURTEST)$(PROG1).output $(STX)$(CURTEST)$(PROG2).output $(STX)$(CURTEST)$(PROG3).output $(STX)-test