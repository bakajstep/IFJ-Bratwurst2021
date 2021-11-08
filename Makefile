PRJ=IFJ21
PROG=$(PRJ)-test

LEX=lex

MAIN=main
SCAN=scanner
STR=string
ERR=error

PROG1=fact_iter
PROG2=fact_rec
PROG3=str_func

CURTEST=_test_cur_
REFTEST=_test_ref_

TESTSDIR=tests
EXPLDIR=example_programs
LEXPATH=$(TESTSDIR)/$(LEX)/
EXPLPATH=$(TESTSDIR)/$(EXPLDIR)/

CC=gcc
CFLAGS=-Wall -Wextra -Werror -pedantic -std=c11

.PHONY: $(LEX)-test $(LEX)-clean

$(LEX)-test:
	$(CC) $(CFLAGS) -o $(LEXPATH)$@ $(SCAN).c $(SCAN).h $(STR).c $(STR).h $(ERR).c $(ERR).h $(LEX)_test.c

	@echo "\n------------------------------------ 'fact_iter' ------------------------------------\n"
	@./$(LEXPATH)$(LEX)-test < $(EXPLPATH)$(PROG1).tl > $(LEXPATH)$(LEX)$(CURTEST)$(PROG1).output	
	@echo "\nTest case 'fact_iter' output differences:"
	@diff -su $(LEXPATH)$(LEX)$(REFTEST)$(PROG1).output $(LEXPATH)$(LEX)$(CURTEST)$(PROG1).output; [ $$? -eq 1 ]
	
	@echo "\n------------------------------------ 'fact_rec' -------------------------------------\n"
	@./$(LEXPATH)$(LEX)-test < $(EXPLPATH)$(PROG2).tl > $(LEXPATH)$(LEX)$(CURTEST)$(PROG2).output	
	@echo "\nTest case 'fact_iter' output differences:"
	@diff -su $(LEXPATH)$(LEX)$(REFTEST)$(PROG2).output $(LEXPATH)$(LEX)$(CURTEST)$(PROG2).output; [ $$? -eq 1 ]

	@echo "\n------------------------------------ 'str_func' -------------------------------------\n"
	@./$(LEXPATH)$(LEX)-test < $(EXPLPATH)$(PROG3).tl > $(LEXPATH)$(LEX)$(CURTEST)$(PROG3).output	
	@echo "\nTest case 'fact_iter' output differences:"
	@diff -su $(LEXPATH)$(LEX)$(REFTEST)$(PROG3).output $(LEXPATH)$(LEX)$(CURTEST)$(PROG3).output; [ $$? -eq 1 ]

$(LEX)-clean:
	cd $(LEXPATH) && rm -f $(LEX)$(CURTEST)$(PROG1).output $(LEX)$(CURTEST)$(PROG2).output $(LEX)$(CURTEST)$(PROG3).output $(LEX)-test
