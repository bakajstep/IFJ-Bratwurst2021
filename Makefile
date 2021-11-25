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
SYMSTK=symstack

PROG1=fact_iter
PROG2=fact_rec
PROG3=str_func
PROG4=fact_iter_err_1
PROG5=fact_iter_err_2
PROG6=fact_iter_err_3
PROG7=fact_iter_err_4
PROG8=fact_iter_err_5
PROG9=str_func_err_1
PROG10=str_func_err_2
PROG11=fact_iter_no_exp
PROG12=fact_rec_no_err

CURTEST=_test_cur_
REFTEST=_test_ref_

TESTSDIR=tests
EXPLDIR=example_programs
LEXPATH=$(TESTSDIR)/$(LEX)/
STXPATH=$(TESTSDIR)/$(STX)/
EXPLPATH=$(TESTSDIR)/$(EXPLDIR)/

CC=gcc
# TODO smazat
CFLAGS=-Wall -Wextra -Werror -pedantic -std=c11 -g

.PHONY: $(LEX)-test $(LEX)-clean $(STX)-test $(STX)-clean

$(LEX)-test:
	$(CC) $(CFLAGS) -o $(LEXPATH)$@ $(SCAN).c $(SCAN).h $(STR).c $(STR).h $(ERR).c $(ERR).h $(LEX)_test.c

	@echo "\n------------------------------------ 'fact_iter' ------------------------------------\n"
	@./$(LEXPATH)$(LEX)-test < $(EXPLPATH)$(PROG1).tl > $(LEXPATH)$(LEX)$(CURTEST)$(PROG1).output	
	@echo "\nTest case 'fact_iter' output differences:"
	@diff -su $(LEXPATH)$(LEX)$(REFTEST)$(PROG1).output $(LEXPATH)$(LEX)$(CURTEST)$(PROG1).output || exit 0
	
	@echo "\n------------------------------------ 'fact_rec' -------------------------------------\n"
	@./$(LEXPATH)$(LEX)-test < $(EXPLPATH)$(PROG2).tl > $(LEXPATH)$(LEX)$(CURTEST)$(PROG2).output	
	@echo "\nTest case 'fact_rec' output differences:"
	@diff -su $(LEXPATH)$(LEX)$(REFTEST)$(PROG2).output $(LEXPATH)$(LEX)$(CURTEST)$(PROG2).output || exit 0

	@echo "\n------------------------------------ 'str_func' -------------------------------------\n"
	@./$(LEXPATH)$(LEX)-test < $(EXPLPATH)$(PROG3).tl > $(LEXPATH)$(LEX)$(CURTEST)$(PROG3).output	
	@echo "\nTest case 'str_func' output differences:"
	@diff -su $(LEXPATH)$(LEX)$(REFTEST)$(PROG3).output $(LEXPATH)$(LEX)$(CURTEST)$(PROG3).output || exit 0

$(LEX)-clean:
	cd $(LEXPATH) && rm -f $(LEX)$(CURTEST)$(PROG1).output $(LEX)$(CURTEST)$(PROG2).output $(LEX)$(CURTEST)$(PROG3).output $(LEX)-test

$(STX)-test:
	$(CC) $(CFLAGS) -o $(STXPATH)$@ $(SCAN).c $(SCAN).h $(STR).c $(STR).h $(ERR).c $(ERR).h $(PRS).c $(PRS).h $(PSA).c $(PSA).h  $(STX)_test.c $(SYMSTK).c $(SYMSTK).h
	
	@echo "\n------------------------------------ 'fact_iter' ------------------------------------\n"
	@./$(STXPATH)$(STX)-test < $(EXPLPATH)$(PROG1).tl > $(STXPATH)$(STX)$(CURTEST)$(PROG1).output
	@echo "\nTest case 'fact_iter' output differences:"
	@diff -su $(STXPATH)$(STX)$(REFTEST)$(PROG1).output $(STXPATH)$(STX)$(CURTEST)$(PROG1).output || exit 0

	@echo "\n------------------------------------ 'fact_rec' -------------------------------------\n"
	@./$(STXPATH)$(STX)-test < $(EXPLPATH)$(PROG2).tl > $(STXPATH)$(STX)$(CURTEST)$(PROG2).output	
	@echo "\nTest case 'fact_rec' output differences:"
	@diff -su $(STXPATH)$(STX)$(REFTEST)$(PROG2).output $(STXPATH)$(STX)$(CURTEST)$(PROG2).output || exit 0

	@echo "\n------------------------------------ 'str_func' -------------------------------------\n"
	@./$(STXPATH)$(STX)-test < $(EXPLPATH)$(PROG3).tl > $(STXPATH)$(STX)$(CURTEST)$(PROG3).output	
	@echo "\nTest case 'str_func' output differences:"
	@diff -su $(STXPATH)$(STX)$(REFTEST)$(PROG3).output $(STXPATH)$(STX)$(CURTEST)$(PROG3).output || exit 0

	@echo "\n------------------------------------ 'fact_iter_err_1' ------------------------------------\n"
	@./$(STXPATH)$(STX)-test < $(EXPLPATH)$(PROG4).tl > $(STXPATH)$(STX)$(CURTEST)$(PROG4).output
	@echo "\nTest case 'fact_iter_err_1' output differences:"
	@diff -su $(STXPATH)$(STX)$(REFTEST)$(PROG4).output $(STXPATH)$(STX)$(CURTEST)$(PROG4).output || exit 0

	@echo "\n------------------------------------ 'fact_iter_err_2' -------------------------------------\n"
	@./$(STXPATH)$(STX)-test < $(EXPLPATH)$(PROG5).tl > $(STXPATH)$(STX)$(CURTEST)$(PROG5).output	
	@echo "\nTest case 'fact_iter_err_2' output differences:"
	@diff -su $(STXPATH)$(STX)$(REFTEST)$(PROG5).output $(STXPATH)$(STX)$(CURTEST)$(PROG5).output || exit 0

	@echo "\n------------------------------------ 'fact_iter_err_3' -------------------------------------\n"
	@./$(STXPATH)$(STX)-test < $(EXPLPATH)$(PROG6).tl > $(STXPATH)$(STX)$(CURTEST)$(PROG6).output	
	@echo "\nTest case 'fact_iter_err_3' output differences:"
	@diff -su $(STXPATH)$(STX)$(REFTEST)$(PROG6).output $(STXPATH)$(STX)$(CURTEST)$(PROG6).output || exit 0

	@echo "\n------------------------------------ 'fact_iter_err_4' ------------------------------------\n"
	@./$(STXPATH)$(STX)-test < $(EXPLPATH)$(PROG7).tl > $(STXPATH)$(STX)$(CURTEST)$(PROG7).output
	@echo "\nTest case 'fact_iter_err_4' output differences:"
	@diff -su $(STXPATH)$(STX)$(REFTEST)$(PROG7).output $(STXPATH)$(STX)$(CURTEST)$(PROG7).output || exit 0

	@echo "\n------------------------------------ 'fact_iter_err_5' -------------------------------------\n"
	@./$(STXPATH)$(STX)-test < $(EXPLPATH)$(PROG8).tl > $(STXPATH)$(STX)$(CURTEST)$(PROG8).output	
	@echo "\nTest case 'fact_iter_err_5' output differences:"
	@diff -su $(STXPATH)$(STX)$(REFTEST)$(PROG8).output $(STXPATH)$(STX)$(CURTEST)$(PROG8).output || exit 0

	@echo "\n------------------------------------ 'str_func_err_1' -------------------------------------\n"
	@./$(STXPATH)$(STX)-test < $(EXPLPATH)$(PROG9).tl > $(STXPATH)$(STX)$(CURTEST)$(PROG9).output	
	@echo "\nTest case 'str_func_err_1' output differences:"
	@diff -su $(STXPATH)$(STX)$(REFTEST)$(PROG9).output $(STXPATH)$(STX)$(CURTEST)$(PROG9).output || exit 0

	@echo "\n------------------------------------ 'str_func_err_2' -------------------------------------\n"
	@./$(STXPATH)$(STX)-test < $(EXPLPATH)$(PROG10).tl > $(STXPATH)$(STX)$(CURTEST)$(PROG10).output	
	@echo "\nTest case 'str_func_err_2' output differences:"
	@diff -su $(STXPATH)$(STX)$(REFTEST)$(PROG10).output $(STXPATH)$(STX)$(CURTEST)$(PROG10).output || exit 0

	@echo "\n------------------------------------ 'str_func_no_exp' -------------------------------------\n"
	@./$(STXPATH)$(STX)-test < $(EXPLPATH)$(PROG11).tl > $(STXPATH)$(STX)$(CURTEST)$(PROG11).output	
	@echo "\nTest case 'str_func_err_2' output differences:"
	@diff -su $(STXPATH)$(STX)$(REFTEST)$(PROG11).output $(STXPATH)$(STX)$(CURTEST)$(PROG11).output || exit 0

	@echo "\n------------------------------------ 'fact_rec_no_err' -------------------------------------\n"
	@./$(STXPATH)$(STX)-test < $(EXPLPATH)$(PROG12).tl > $(STXPATH)$(STX)$(CURTEST)$(PROG12).output	
	@echo "\nTest case 'str_func_err_2' output differences:"
	@diff -su $(STXPATH)$(STX)$(REFTEST)$(PROG12).output $(STXPATH)$(STX)$(CURTEST)$(PROG12).output || exit 0

$(STX)-clean:
	cd $(STXPATH) && rm -f \
	$(STX)$(CURTEST)$(PROG1).output \
	$(STX)$(CURTEST)$(PROG2).output \
	$(STX)$(CURTEST)$(PROG3).output \
	$(STX)$(CURTEST)$(PROG4).output \
	$(STX)$(CURTEST)$(PROG5).output \
	$(STX)$(CURTEST)$(PROG6).output \
	$(STX)$(CURTEST)$(PROG7).output \
	$(STX)$(CURTEST)$(PROG8).output \
	$(STX)$(CURTEST)$(PROG9).output \
	$(STX)$(CURTEST)$(PROG10).output \
	$(STX)$(CURTEST)$(PROG11).output \
	$(STX)$(CURTEST)$(PROG12).output \
	$(STX)-test
