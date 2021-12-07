#
# Project: IFJ21 imperative language compiler
# 
# Brief:   Makefile for IFJ21 compiler
#  
# Author:  David Chocholaty <xchoch09>
# 
#

PRJ=IFJ21
PROG=$(PRJ)-test

LEX=lex
STX=syntax
SEM=semantic
GEN=gen

MAIN=main
SCAN=scanner
STR=string
ERR=error
PRS=parser
PSA=psa
SYMSTK=symstack
PARAMSTK=paramstack
SYMTBL=symtable
SYMLL=sym_linked_list
CDGEN=code_generator
DLL=dll
IDS=ids_list

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
PROG13=bad_parameter_type_err1
PROG14=bad_parameter_type_err2
PROG15=bad_parameter_type_err3
PROG16=bad_return_type_err1
PROG17=bad_return_type_err2
PROG18=bad_type_variable_err
PROG19=call_too_few_parameter_err1
PROG20=call_too_few_parameter_err2
PROG21=call_too_many_parameter_err1
PROG22=call_too_many_parameter_err2
PROG23=define_too_few_parameter_err
PROG24=define_too_many_parameter_err
PROG25=define_too_many_returns_err
PROG26=function_call_before_declaration_err1
PROG27=function_call_before_declaration_err2
PROG28=function_make_local_variable_err
PROG29=more_returns_than_variables_err
PROG30=no_return_nill_noerr
PROG31=not_defined_function_err
PROG32=same_name_function_err1
PROG33=same_name_function_err2
PROG34=same_name_variable-function_err1
PROG35=same_name_variable-function_err2
PROG36=same_name_variable-function_err3
PROG37=same_name_variable-function_err4
PROG38=same_name_variable-function_err5
PROG39=same_name_variable-function_err6
PROG40=same_name_variable-function_err7
PROG41=same_name_variable-function_err8
PROG42=same_name_variable-function_err9
PROG43=same_name_variable_if_err
PROG44=same_name_variable_main_err
PROG45=same_name_variable_main_if_noerr
PROG46=same_name_variable_main_while_noerr
PROG47=same_name_variable_while_err
PROG48=undeclared_variable_err1
PROG49=undeclared_variable_err2
PROG50=undeclared_variable_err3
PROG51=undeclared_variable_nill_noerr
PROG52=using_undefined_variable_err
PROG53=example1
PROG54=example2
PROG55=example3
PROG56=fun
PROG57=hello
PROG58=multiassign
PROG59=substr
PROG60=visibility
PROG61=whitespaces
DISCTEST=program

CURTEST=_test_cur_
REFTEST=_test_ref_
GENTEST=gen_test_

TESTSDIR=tests
EXPLDIR=example_programs
LEXPATH=$(TESTSDIR)/$(LEX)/
STXPATH=$(TESTSDIR)/$(STX)/
SEMPATH=$(TESTSDIR)/$(SEM)/
GENPATH=$(TESTSDIR)/$(GEN)/
EXPLPATH=$(TESTSDIR)/$(EXPLDIR)/

CC=gcc
# TODO smazat -g
CFLAGS=-Wall -Wextra -Werror -pedantic -std=c11 -g

.PHONY: all $(LEX)-test $(LEX)-clean $(STX)-test $(STX)-clean $(SEM)-test $(SEM)-clean $(GEN)-test $(GEN)-clean

all:
	$(CC) $(CFLAGS) -o compiler $(MAIN).c $(SCAN).c $(SCAN).h $(STR).c $(STR).h $(ERR).c $(ERR).h $(PRS).c $(PRS).h $(PSA).c $(PSA).h $(SYMSTK).c $(SYMSTK).h $(PARAMSTK).c $(PARAMSTK).h $(SYMTBL).c $(SYMTBL).h $(SYMLL).c $(SYMLL).h $(CDGEN).h $(CDGEN).c $(DLL).c $(DLL).h $(IDS).c $(IDS).h

$(LEX)-test:
	$(CC) $(CFLAGS) -o $(LEXPATH)$@ $(SCAN).c $(SCAN).h $(STR).c $(STR).h $(ERR).c $(ERR).h $(LEX)_test.c
#	$(CC) $(CFLAGS) -o $(LEXPATH)$@ $(SCAN).c $(SCAN).h $(STR).c $(STR).h $(ERR).c $(ERR).h $(PRS).c $(PRS).h $(PSA).c $(PSA).h  $(LEX)_test.c $(SYMSTK).c $(SYMSTK).h $(SYMTBL).c $(SYMTBL).h $(SYMLL).c $(SYMLL).h	

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
#	$(CC) $(CFLAGS) -o $(STXPATH)$@ $(SCAN).c $(SCAN).h $(STR).c $(STR).h $(ERR).c $(ERR).h $(PRS).c $(PRS).h $(PSA).c $(PSA).h  $(STX)_test.c $(SYMSTK).c $(SYMSTK).h
#	$(CC) $(CFLAGS) -o $(STXPATH)$@ $(SCAN).c $(SCAN).h $(STR).c $(STR).h $(ERR).c $(ERR).h $(PRS).c $(PRS).h $(PSA).c $(PSA).h $(STX)_test.c $(SYMSTK).c $(SYMSTK).h $(SYMTBL).c $(SYMTBL).h $(SYMLL).c $(SYMLL).h
	$(CC) $(CFLAGS) -o $(STXPATH)$@ $(SCAN).c $(SCAN).h $(STR).c $(STR).h $(ERR).c $(ERR).h $(PRS).c $(PRS).h $(PSA).c $(PSA).h $(STX)_test.c $(SYMSTK).c $(SYMSTK).h $(PARAMSTK).c $(PARAMSTK).h $(SYMTBL).c $(SYMTBL).h $(SYMLL).c $(SYMLL).h $(CDGEN).h $(CDGEN).c $(DLL).c $(DLL).h $(IDS).c $(IDS).h
	
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

#TODO smazat code_generator
$(SEM)-test:
#	$(CC) $(CFLAGS) -o $(SEMPATH)$@ $(SCAN).c $(SCAN).h $(STR).c $(STR).h $(ERR).c $(ERR).h $(PRS).c $(PRS).h $(PSA).c $(PSA).h $(SEM)_test.c $(SYMSTK).c $(SYMSTK).h $(SYMTBL).c $(SYMTBL).h $(SYMLL).c $(SYMLL).h $(CDGEN).h $(CDGEN).c
	$(CC) $(CFLAGS) -o $(SEMPATH)$@ $(SCAN).c $(SCAN).h $(STR).c $(STR).h $(ERR).c $(ERR).h $(PRS).c $(PRS).h $(PSA).c $(PSA).h $(SEM)_test.c $(SYMSTK).c $(SYMSTK).h $(PARAMSTK).c $(PARAMSTK).h $(SYMTBL).c $(SYMTBL).h $(SYMLL).c $(SYMLL).h $(CDGEN).h $(CDGEN).c $(DLL).c $(DLL).h $(IDS).c $(IDS).h

	@echo "\n------------------------------------ 'bad_parameter_type_err1' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)/$(PROG13).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG13).output
	@echo "\nTest case 'bad_parameter_type_err1' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG13).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG13).output || exit 0

	@echo "\n------------------------------------ 'bad_parameter_type_err2' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)/$(PROG14).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG14).output
	@echo "\nTest case 'bad_parameter_type_err2' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG14).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG14).output || exit 0

	@echo "\n------------------------------------ 'bad_parameter_type_err3' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)/$(PROG15).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG15).output
	@echo "\nTest case 'bad_parameter_type_err3' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG15).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG15).output || exit 0

	@echo "\n------------------------------------ 'bad_return_type_err1' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)/$(PROG16).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG16).output
	@echo "\nTest case 'bad_return_type_err1' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG16).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG16).output || exit 0

	@echo "\n------------------------------------ 'bad_return_type_err2' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)/$(PROG17).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG17).output
	@echo "\nTest case 'bad_return_type_err2' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG17).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG17).output || exit 0

	@echo "\n------------------------------------ 'bad_type_variable_err' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)/$(PROG18).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG18).output
	@echo "\nTest case 'bad_type_variable_err' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG18).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG18).output || exit 0

	@echo "\n------------------------------------ 'call_too_few_parameter_err1' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)/$(PROG19).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG19).output
	@echo "\nTest case 'call_too_few_parameter_err1' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG19).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG19).output || exit 0

	@echo "\n------------------------------------ 'call_too_few_parameter_err2' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)/$(PROG20).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG20).output
	@echo "\nTest case 'call_too_few_parameter_err2' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG20).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG20).output || exit 0

	@echo "\n------------------------------------ 'call_too_many_parameter_err1' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)/$(PROG21).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG21).output
	@echo "\nTest case 'call_too_few_parameter_err1' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG21).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG21).output || exit 0

	@echo "\n------------------------------------ 'call_too_many_parameter_err2' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)/$(PROG22).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG22).output
	@echo "\nTest case 'bad_type_variable_err' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG22).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG22).output || exit 0

	@echo "\n------------------------------------ 'define_too_few_parameter_err' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)/$(PROG23).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG23).output
	@echo "\nTest case 'define_too_few_parameter_err' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG23).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG23).output || exit 0

	@echo "\n------------------------------------ 'define_too_many_parameter_err' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)/$(PROG24).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG24).output
	@echo "\nTest case 'bad_type_variable_err' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG24).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG24).output || exit 0

	@echo "\n------------------------------------ 'define_too_many_returns_err' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)/$(PROG25).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG25).output
	@echo "\nTest case 'define_too_many_returns_err' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG25).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG25).output || exit 0

	@echo "\n------------------------------------ 'function_call_before_declaration_err1' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)/$(PROG26).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG26).output
	@echo "\nTest case 'function_call_before_declaration_err1' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG18).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG18).output || exit 0

	@echo "\n------------------------------------ 'function_call_before_declaration_err2' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)/$(PROG27).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG27).output
	@echo "\nTest case 'function_call_before_declaration_err2' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG27).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG27).output || exit 0

	@echo "\n------------------------------------ 'function_make_local_variables_err' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)/$(PROG28).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG28).output
	@echo "\nTest case 'function_make_local_variables_err' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG28).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG28).output || exit 0

	@echo "\n------------------------------------ 'more_returns_than_variables_err' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)/$(PROG29).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG29).output
	@echo "\nTest case 'more_returns_than_variables_err' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG29).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG29).output || exit 0

	@echo "\n------------------------------------ 'no_return_nill_noerr' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)/$(PROG30).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG30).output
	@echo "\nTest case 'no_return_nill_noerr' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG30).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG30).output || exit 0

	@echo "\n------------------------------------ 'not_defined_function_err' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)/$(PROG31).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG31).output
	@echo "\nTest case 'not_defined_function_err' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG31).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG31).output || exit 0

	@echo "\n------------------------------------ 'same_name_function_err1' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)/$(PROG32).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG32).output
	@echo "\nTest case 'same_name_function_err1' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG32).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG32).output || exit 0

	@echo "\n------------------------------------ 'same_name_function_err2' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)/$(PROG33).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG33).output
	@echo "\nTest case 'same_name_function_err2' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG33).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG33).output || exit 0

	@echo "\n------------------------------------ 'same_name_variable-function_err1' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)/$(PROG34).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG34).output
	@echo "\nTest case 'same_name_variable-function_err1' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG34).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG34).output || exit 0

	@echo "\n------------------------------------ 'same_name_variable-function_err2' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)/$(PROG35).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG35).output
	@echo "\nTest case 'same_name_variable-function_err2' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG35).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG35).output || exit 0

	@echo "\n------------------------------------ 'same_name_variable-function_err3' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)/$(PROG36).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG36).output
	@echo "\nTest case 'same_name_variable-function_err3' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG36).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG36).output || exit 0

	@echo "\n------------------------------------ 'same_name_variable-function_err4' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)/$(PROG37).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG37).output
	@echo "\nTest case 'same_name_variable-function_err4' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG37).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG37).output || exit 0

	@echo "\n------------------------------------ 'same_name_variable-function_err5' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)/$(PROG38).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG38).output
	@echo "\nTest case 'same_name_variable-function_err5' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG38).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG38).output || exit 0

	@echo "\n------------------------------------ 'same_name_variable-function_err6' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)/$(PROG39).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG39).output
	@echo "\nTest case 'same_name_variable-function_err6' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG39).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG39).output || exit 0

	@echo "\n------------------------------------ 'same_name_variable-function_err7' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)/$(PROG40).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG40).output
	@echo "\nTest case 'same_name_variable-function_err7' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG40).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG40).output || exit 0

	@echo "\n------------------------------------ 'same_name_variable-function_err8' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)/$(PROG41).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG41).output
	@echo "\nTest case 'same_name_variable-function_err8' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG41).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG41).output || exit 0

	@echo "\n------------------------------------ 'same_name_variable-function_err9' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)/$(PROG42).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG42).output
	@echo "\nTest case 'same_name_variable-function_err9' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG42).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG42).output || exit 0

	@echo "\n------------------------------------ 'same_name_variable_if_err' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)/$(PROG43).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG43).output
	@echo "\nTest case 'same_name_variable_if_err' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG43).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG43).output || exit 0

	@echo "\n------------------------------------ 'same_name_variable_main_err' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)/$(PROG44).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG44).output
	@echo "\nTest case 'same_name_variable_main_err' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG44).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG44).output || exit 0

	@echo "\n------------------------------------ 'same_name_variable_main_if_noerr' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)/$(PROG45).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG45).output
	@echo "\nTest case 'same_name_variable_main_if_noerr' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG45).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG45).output || exit 0

	@echo "\n------------------------------------ 'same_name_variable_main_while_noerr' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)/$(PROG46).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG46).output
	@echo "\nTest case 'same_name_variable_main_while_noerr' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG46).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG46).output || exit 0

	@echo "\n------------------------------------ 'same_name_variable_while_err' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)/$(PROG47).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG47).output
	@echo "\nTest case 'same_name_variable_while_err' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG47).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG47).output || exit 0

	@echo "\n------------------------------------ 'undeclared_variable_err1' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)/$(PROG48).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG48).output
	@echo "\nTest case 'undeclared_variable_err1' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG48).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG48).output || exit 0

	@echo "\n------------------------------------ 'undeclared_variable_err2' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)/$(PROG49).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG49).output
	@echo "\nTest case 'undeclared_variable_err2' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG49).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG49).output || exit 0

	@echo "\n------------------------------------ 'undeclared_variable_err3' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)/$(PROG50).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG50).output
	@echo "\nTest case 'undeclared_variable_err3' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG50).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG50).output || exit 0

	@echo "\n------------------------------------ 'undeclared_variable_nill_noerr' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)/$(PROG51).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG51).output
	@echo "\nTest case 'undeclared_variable_err3' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG51).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG51).output || exit 0

	@echo "\n------------------------------------ 'using_undefined_variable_err' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)/$(PROG52).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG52).output
	@echo "\nTest case 'using_undefined_variable_err' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG52).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG52).output || exit 0

$(SEM)-clean:
	cd $(SEMPATH) && rm -f \
    $(SEM)$(CURTEST)$(PROG13).output \
    $(SEM)$(CURTEST)$(PROG14).output \
	$(SEM)$(CURTEST)$(PROG15).output \
	$(SEM)$(CURTEST)$(PROG16).output \
	$(SEM)$(CURTEST)$(PROG17).output \
	$(SEM)$(CURTEST)$(PROG18).output \
	$(SEM)$(CURTEST)$(PROG19).output \
	$(SEM)$(CURTEST)$(PROG20).output \
	$(SEM)$(CURTEST)$(PROG21).output \
	$(SEM)$(CURTEST)$(PROG22).output \
	$(SEM)$(CURTEST)$(PROG23).output \
	$(SEM)$(CURTEST)$(PROG24).output \
	$(SEM)$(CURTEST)$(PROG25).output \
	$(SEM)$(CURTEST)$(PROG26).output \
	$(SEM)$(CURTEST)$(PROG27).output \
	$(SEM)$(CURTEST)$(PROG28).output \
	$(SEM)$(CURTEST)$(PROG29).output \
	$(SEM)$(CURTEST)$(PROG30).output \
	$(SEM)$(CURTEST)$(PROG31).output \
	$(SEM)$(CURTEST)$(PROG32).output \
	$(SEM)$(CURTEST)$(PROG33).output \
	$(SEM)$(CURTEST)$(PROG34).output \
	$(SEM)$(CURTEST)$(PROG35).output \
	$(SEM)$(CURTEST)$(PROG36).output \
	$(SEM)$(CURTEST)$(PROG37).output \
	$(SEM)$(CURTEST)$(PROG38).output \
	$(SEM)$(CURTEST)$(PROG39).output \
	$(SEM)$(CURTEST)$(PROG40).output \
	$(SEM)$(CURTEST)$(PROG41).output \
	$(SEM)$(CURTEST)$(PROG42).output \
	$(SEM)$(CURTEST)$(PROG43).output \
	$(SEM)$(CURTEST)$(PROG44).output \
	$(SEM)$(CURTEST)$(PROG45).output \
	$(SEM)$(CURTEST)$(PROG46).output \
	$(SEM)$(CURTEST)$(PROG47).output \
	$(SEM)$(CURTEST)$(PROG48).output \
	$(SEM)$(CURTEST)$(PROG49).output \
	$(SEM)$(CURTEST)$(PROG50).output \
	$(SEM)$(CURTEST)$(PROG51).output \
	$(SEM)$(CURTEST)$(PROG52).output \
	$(SEM)-test

$(GEN)-test:
	$(CC) $(CFLAGS) -o $(GENPATH)$@ $(MAIN).c $(SCAN).c $(SCAN).h $(STR).c $(STR).h $(ERR).c $(ERR).h $(PRS).c $(PRS).h $(PSA).c $(PSA).h $(SYMSTK).c $(SYMSTK).h $(PARAMSTK).c $(PARAMSTK).h $(SYMTBL).c $(SYMTBL).h $(SYMLL).c $(SYMLL).h $(CDGEN).h $(CDGEN).c $(DLL).c $(DLL).h $(IDS).c $(IDS).h

	@echo "\n------------------------------------ 'example1' ------------------------------------\n"
	@./$(GENPATH)$(GEN)-test < $(GENPATH)$(EXPLDIR)/$(PROG53).tl > $(GENPATH)$(GENTEST)$(PROG53).code
	@$(GENPATH)ic21int $(GENPATH)$(GENTEST)$(PROG53).code < $(GENPATH)$(PROG53).in > $(GENPATH)$(GENTEST)$(PROG53).out
	@echo "\nTest case 'example1' output differences:"
	@diff -su $(GENPATH)$(GENTEST)$(PROG53).out $(GENPATH)$(PROG53).out || exit 0

	@echo "\n------------------------------------ 'example2' ------------------------------------\n"
	@./$(GENPATH)$(GEN)-test < $(GENPATH)$(EXPLDIR)/$(PROG54).tl > $(GENPATH)$(GENTEST)$(PROG54).code
	@$(GENPATH)ic21int $(GENPATH)$(GENTEST)$(PROG54).code < $(GENPATH)$(PROG54).in > $(GENPATH)$(GENTEST)$(PROG54).out
	@echo "\nTest case 'example2' output differences:"
	@diff -su $(GENPATH)$(GENTEST)$(PROG54).out $(GENPATH)$(PROG54).out || exit 0

	@echo "\n------------------------------------ 'example3' ------------------------------------\n"
	@./$(GENPATH)$(GEN)-test < $(GENPATH)$(EXPLDIR)/$(PROG55).tl > $(GENPATH)$(GENTEST)$(PROG55).code
	@$(GENPATH)ic21int $(GENPATH)$(GENTEST)$(PROG55).code < $(GENPATH)$(PROG55).in > $(GENPATH)$(GENTEST)$(PROG55).out
	@echo "\nTest case 'example3' output differences:"
	@diff -su $(GENPATH)$(GENTEST)$(PROG55).out $(GENPATH)$(PROG55).out || exit 0

	@echo "\n------------------------------------ 'fun' ------------------------------------\n"
	@./$(GENPATH)$(GEN)-test < $(GENPATH)$(EXPLDIR)/$(PROG56).tl > $(GENPATH)$(GENTEST)$(PROG56).code
	@$(GENPATH)ic21int $(GENPATH)$(GENTEST)$(PROG56).code < $(GENPATH)$(PROG56).in > $(GENPATH)$(GENTEST)$(PROG56).out
	@echo "\nTest case 'fun' output differences:"
	@diff -su $(GENPATH)$(GENTEST)$(PROG56).out $(GENPATH)$(PROG56).out || exit 0

	@echo "\n------------------------------------ 'hello' ------------------------------------\n"
	@./$(GENPATH)$(GEN)-test < $(GENPATH)$(EXPLDIR)/$(PROG57).tl > $(GENPATH)$(GENTEST)$(PROG57).code
	@$(GENPATH)ic21int $(GENPATH)$(GENTEST)$(PROG57).code < $(GENPATH)$(PROG57).in > $(GENPATH)$(GENTEST)$(PROG57).out
	@echo "\nTest case 'hello' output differences:"
	@diff -su $(GENPATH)$(GENTEST)$(PROG57).out $(GENPATH)$(PROG57).out || exit 0

	@echo "\n------------------------------------ 'multiassign' ------------------------------------\n"
	@./$(GENPATH)$(GEN)-test < $(GENPATH)$(EXPLDIR)/$(PROG58).tl > $(GENPATH)$(GENTEST)$(PROG58).code
	@$(GENPATH)ic21int $(GENPATH)$(GENTEST)$(PROG58).code < $(GENPATH)$(PROG58).in > $(GENPATH)$(GENTEST)$(PROG58).out
	@echo "\nTest case 'multiassign' output differences:"
	@diff -su $(GENPATH)$(GENTEST)$(PROG58).out $(GENPATH)$(PROG58).out || exit 0

	@echo "\n------------------------------------ 'substr' ------------------------------------\n"
	@./$(GENPATH)$(GEN)-test < $(GENPATH)$(EXPLDIR)/$(PROG59).tl > $(GENPATH)$(GENTEST)$(PROG59).code
	@$(GENPATH)ic21int $(GENPATH)$(GENTEST)$(PROG59).code < $(GENPATH)$(PROG59).in > $(GENPATH)$(GENTEST)$(PROG59).out
	@echo "\nTest case 'substr' output differences:"
	@diff -su $(GENPATH)$(GENTEST)$(PROG59).out $(GENPATH)$(PROG59).out || exit 0

	@echo "\n------------------------------------ 'visibility' ------------------------------------\n"
	@./$(GENPATH)$(GEN)-test < $(GENPATH)$(EXPLDIR)/$(PROG60).tl > $(GENPATH)$(GENTEST)$(PROG60).code
	@$(GENPATH)ic21int $(GENPATH)$(GENTEST)$(PROG60).code < $(GENPATH)$(PROG60).in > $(GENPATH)$(GENTEST)$(PROG60).out
	@echo "\nTest case 'visibility' output differences:"
	@diff -su $(GENPATH)$(GENTEST)$(PROG60).out $(GENPATH)$(PROG60).out || exit 0

	@echo "\n------------------------------------ 'whitespaces' ------------------------------------\n"
	@./$(GENPATH)$(GEN)-test < $(GENPATH)$(EXPLDIR)/$(PROG61).tl > $(GENPATH)$(GENTEST)$(PROG61).code
	@$(GENPATH)ic21int $(GENPATH)$(GENTEST)$(PROG61).code < $(GENPATH)$(PROG61).in > $(GENPATH)$(GENTEST)$(PROG61).out
	@echo "\nTest case 'whitespaces' output differences:"
	@diff -su $(GENPATH)$(GENTEST)$(PROG61).out $(GENPATH)$(PROG61).out || exit 0

	@echo "\n------------------------------------ 'disc_test' ------------------------------------\n"
	./$(GENPATH)$(GEN)-test < $(GENPATH)$(DISCTEST).tl > $(GENPATH)$(GENTEST)$(DISCTEST).code
	@$(GENPATH)ic21int $(GENPATH)$(GENTEST)$(DISCTEST).code < $(GENPATH)input > $(GENPATH)$(GENTEST)$(DISCTEST).out
	@echo "\nTest case 'whitespaces' output differences:"
	@diff -su $(GENPATH)$(GENTEST)$(DISCTEST).out $(GENPATH)output || exit 0

	
$(GEN)-clean:
	cd $(GENPATH) && rm -f \
	$(GENTEST)$(PROG53).code \
	$(GENTEST)$(PROG54).code \
	$(GENTEST)$(PROG55).code \
	$(GENTEST)$(PROG56).code \
	$(GENTEST)$(PROG57).code \
	$(GENTEST)$(PROG58).code \
	$(GENTEST)$(PROG59).code \
	$(GENTEST)$(PROG60).code \
	$(GENTEST)$(PROG61).code \
	$(GENTEST)$(PROG53).out \
	$(GENTEST)$(PROG54).out \
	$(GENTEST)$(PROG55).out \
	$(GENTEST)$(PROG56).out \
	$(GENTEST)$(PROG57).out \
	$(GENTEST)$(PROG58).out \
	$(GENTEST)$(PROG59).out \
	$(GENTEST)$(PROG60).out \
	$(GENTEST)$(PROG61).out \
	$(GENTEST)$(DISCTEST).out \
	$(GENTEST)$(DISCTEST).code \
	input \
	output \
	program.tl \
	$(GEN)-test	
