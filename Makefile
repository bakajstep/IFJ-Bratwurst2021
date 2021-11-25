PRJ=IFJ21
PROG=$(PRJ)-test

LEX=lex
STX=syntax
SEM=semantic

MAIN=main
SCAN=scanner
STR=string
ERR=error
PRS=parser
PSA=psa
SYMSTK=symstack
SYMTBL=symtable
SYMLL=sym_linked_list

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
PROG24=define_too_many_parameter_err1
PROG25=define_too_many_parameter_err2
PROG26=define_too_many_returns_err
PROG27=function_call_before_declaration_err1
PROG28=function_call_before_declaration_err2
PROG29=function_make_local_variable_err
PROG30=more_returns_than_variables_err
PROG31=no_return_nill_noerr
PROG32=not_defined_function_err
PROG33=same_name_function_err1
PROG34=same_name_function_err2
PROG35=same_name_variable-function_err1
PROG36=same_name_variable-function_err2
PROG37=same_name_variable-function_err3
PROG38=same_name_variable-function_err4
PROG39=same_name_variable-function_err5
PROG40=same_name_variable-function_err6
PROG41=same_name_variable-function_err7
PROG42=same_name_variable-function_err8
PROG43=same_name_variable-function_err9
PROG44=same_name_variable_if_err
PROG45=same_name_variable_main_err
PROG46=same_name_variable_main_if_noerr
PROG47=same_name_variable_main_while_noerr
PROG48=same_name_variable_while_err
PROG49=undeclared_variable_err1
PROG50=undeclared_variable_err2
PROG51=undeclared_variable_err3
PROG52=undeclared_variable_nill_noerr
PROG53=using_undefined_variable_err

CURTEST=_test_cur_
REFTEST=_test_ref_

TESTSDIR=tests
EXPLDIR=example_programs
LEXPATH=$(TESTSDIR)/$(LEX)/
STXPATH=$(TESTSDIR)/$(STX)/
SEMPATH=$(TESTSDIR)/$(SEM)/
EXPLPATH=$(TESTSDIR)/$(EXPLDIR)/

CC=gcc
# TODO smazat
CFLAGS=-Wall -Wextra -Werror -pedantic -std=c11 -g

.PHONY: $(LEX)-test $(LEX)-clean $(STX)-test $(STX)-clean $(SEM)-test $(SEM)-clean

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

$(SEM)-test:
	$(CC) $(CFLAGS) -o $(SEMPATH)$@ $(SCAN).c $(SCAN).h $(STR).c $(STR).h $(ERR).c $(ERR).h $(PRS).c $(PRS).h $(PSA).c $(PSA).h  $(SEM)_test.c $(SYMSTK).c $(SYMSTK).h $(SYMTBL).c $(SYMTBL).h $(SYMLL).c $(SYMLL).h

	@echo "\n------------------------------------ 'bad_parameter_type_err1' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)$(PROG13).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG13).output
	@echo "\nTest case 'bad_parameter_type_err1' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG13).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG13).output || exit 0

	@echo "\n------------------------------------ 'bad_parameter_type_err2' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)$(PROG14).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG14).output
	@echo "\nTest case 'bad_parameter_type_err2' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG14).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG14).output || exit 0

	@echo "\n------------------------------------ 'bad_parameter_type_err3' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)$(PROG15).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG15).output
	@echo "\nTest case 'bad_parameter_type_err3' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG15).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG15).output || exit 0

	@echo "\n------------------------------------ 'bad_return_type_err1' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)$(PROG16).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG16).output
	@echo "\nTest case 'bad_return_type_err1' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG16).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG16).output || exit 0

	@echo "\n------------------------------------ 'bad_return_type_err2' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)$(PROG17).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG17).output
	@echo "\nTest case 'bad_return_type_err2' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG17).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG17).output || exit 0

	@echo "\n------------------------------------ 'bad_type_variable_err' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)$(PROG18).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG18).output
	@echo "\nTest case 'bad_type_variable_err' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG18).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG18).output || exit 0

	@echo "\n------------------------------------ 'call_too_few_parameter_err1' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)$(PROG19).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG19).output
	@echo "\nTest case 'call_too_few_parameter_err1' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG19).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG19).output || exit 0

	@echo "\n------------------------------------ 'call_too_few_parameter_err2' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)$(PROG20).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG20).output
	@echo "\nTest case 'call_too_few_parameter_err2' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG20).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG20).output || exit 0

	@echo "\n------------------------------------ 'call_too_many_parameter_err1' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)$(PROG21).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG21).output
	@echo "\nTest case 'call_too_few_parameter_err1' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG21).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG21).output || exit 0

	@echo "\n------------------------------------ 'call_too_many_parameter_err2' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)$(PROG22).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG22).output
	@echo "\nTest case 'bad_type_variable_err' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG22).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG22).output || exit 0

	@echo "\n------------------------------------ 'define_too_few_parameter_err' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)$(PROG23).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG23).output
	@echo "\nTest case 'define_too_few_parameter_err' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG23).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG23).output || exit 0

	@echo "\n------------------------------------ 'define_too_many_parameter_err' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)$(PROG24).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG24).output
	@echo "\nTest case 'bad_type_variable_err' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG24).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG24).output || exit 0

	@echo "\n------------------------------------ 'define_too_many_returns_err' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)$(PROG25).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG25).output
	@echo "\nTest case 'define_too_many_returns_err' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG25).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG25).output || exit 0

	@echo "\n------------------------------------ 'function_call_before_declaration_err1' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)$(PROG26).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG26).output
	@echo "\nTest case 'function_call_before_declaration_err1' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG18).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG18).output || exit 0

	@echo "\n------------------------------------ 'function_call_before_declaration_err2' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)$(PROG27).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG27).output
	@echo "\nTest case 'function_call_before_declaration_err2' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG27).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG27).output || exit 0

	@echo "\n------------------------------------ 'function_make_local_variables_err' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)$(PROG28).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG28).output
	@echo "\nTest case 'function_make_local_variables_err' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG28).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG28).output || exit 0

	@echo "\n------------------------------------ 'more_returns_than_variables_err' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)$(PROG29).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG29).output
	@echo "\nTest case 'more_returns_than_variables_err' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG29).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG29).output || exit 0

	@echo "\n------------------------------------ 'no_return_nill_noerr' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)$(PROG30).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG30).output
	@echo "\nTest case 'no_return_nill_noerr' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG30).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG30).output || exit 0

# dodelano

	@echo "\n------------------------------------ 'function_call_before_declaration_err2' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)$(PROG27).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG27).output
	@echo "\nTest case 'function_call_before_declaration_err2' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG27).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG27).output || exit 0

	@echo "\n------------------------------------ 'function_call_before_declaration_err2' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)$(PROG27).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG27).output
	@echo "\nTest case 'function_call_before_declaration_err2' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG27).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG27).output || exit 0

	@echo "\n------------------------------------ 'function_call_before_declaration_err2' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)$(PROG27).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG27).output
	@echo "\nTest case 'function_call_before_declaration_err2' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG27).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG27).output || exit 0

	@echo "\n------------------------------------ 'function_call_before_declaration_err2' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)$(PROG27).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG27).output
	@echo "\nTest case 'function_call_before_declaration_err2' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG27).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG27).output || exit 0

	@echo "\n------------------------------------ 'function_call_before_declaration_err2' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)$(PROG27).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG27).output
	@echo "\nTest case 'function_call_before_declaration_err2' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG27).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG27).output || exit 0

	@echo "\n------------------------------------ 'function_call_before_declaration_err2' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)$(PROG27).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG27).output
	@echo "\nTest case 'function_call_before_declaration_err2' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG27).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG27).output || exit 0

	@echo "\n------------------------------------ 'function_call_before_declaration_err2' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)$(PROG27).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG27).output
	@echo "\nTest case 'function_call_before_declaration_err2' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG27).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG27).output || exit 0

	@echo "\n------------------------------------ 'function_call_before_declaration_err2' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)$(PROG27).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG27).output
	@echo "\nTest case 'function_call_before_declaration_err2' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG27).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG27).output || exit 0

	@echo "\n------------------------------------ 'function_call_before_declaration_err2' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)$(PROG27).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG27).output
	@echo "\nTest case 'function_call_before_declaration_err2' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG27).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG27).output || exit 0

	@echo "\n------------------------------------ 'function_call_before_declaration_err2' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)$(PROG27).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG27).output
	@echo "\nTest case 'function_call_before_declaration_err2' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG27).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG27).output || exit 0

	@echo "\n------------------------------------ 'function_call_before_declaration_err2' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)$(PROG27).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG27).output
	@echo "\nTest case 'function_call_before_declaration_err2' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG27).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG27).output || exit 0

	@echo "\n------------------------------------ 'function_call_before_declaration_err2' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)$(PROG27).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG27).output
	@echo "\nTest case 'function_call_before_declaration_err2' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG27).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG27).output || exit 0

	@echo "\n------------------------------------ 'function_call_before_declaration_err2' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)$(PROG27).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG27).output
	@echo "\nTest case 'function_call_before_declaration_err2' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG27).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG27).output || exit 0

	@echo "\n------------------------------------ 'function_call_before_declaration_err2' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)$(PROG27).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG27).output
	@echo "\nTest case 'function_call_before_declaration_err2' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG27).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG27).output || exit 0

	@echo "\n------------------------------------ 'function_call_before_declaration_err2' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)$(PROG27).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG27).output
	@echo "\nTest case 'function_call_before_declaration_err2' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG27).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG27).output || exit 0

	@echo "\n------------------------------------ 'function_call_before_declaration_err2' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)$(PROG27).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG27).output
	@echo "\nTest case 'function_call_before_declaration_err2' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG27).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG27).output || exit 0

	@echo "\n------------------------------------ 'function_call_before_declaration_err2' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)$(PROG27).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG27).output
	@echo "\nTest case 'function_call_before_declaration_err2' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG27).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG27).output || exit 0

	@echo "\n------------------------------------ 'function_call_before_declaration_err2' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)$(PROG27).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG27).output
	@echo "\nTest case 'function_call_before_declaration_err2' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG27).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG27).output || exit 0

	@echo "\n------------------------------------ 'function_call_before_declaration_err2' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)$(PROG27).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG27).output
	@echo "\nTest case 'function_call_before_declaration_err2' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG27).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG27).output || exit 0

	@echo "\n------------------------------------ 'function_call_before_declaration_err2' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)$(PROG27).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG27).output
	@echo "\nTest case 'function_call_before_declaration_err2' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG27).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG27).output || exit 0

	@echo "\n------------------------------------ 'function_call_before_declaration_err2' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)$(PROG27).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG27).output
	@echo "\nTest case 'function_call_before_declaration_err2' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG27).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG27).output || exit 0

	@echo "\n------------------------------------ 'function_call_before_declaration_err2' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)$(PROG27).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG27).output
	@echo "\nTest case 'function_call_before_declaration_err2' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG27).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG27).output || exit 0

	@echo "\n------------------------------------ 'function_call_before_declaration_err2' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)$(PROG27).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG27).output
	@echo "\nTest case 'function_call_before_declaration_err2' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG27).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG27).output || exit 0

	@echo "\n------------------------------------ 'function_call_before_declaration_err2' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)$(PROG27).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG27).output
	@echo "\nTest case 'function_call_before_declaration_err2' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG27).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG27).output || exit 0

	@echo "\n------------------------------------ 'function_call_before_declaration_err2' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)$(PROG27).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG27).output
	@echo "\nTest case 'function_call_before_declaration_err2' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG27).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG27).output || exit 0

	@echo "\n------------------------------------ 'function_call_before_declaration_err2' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)$(PROG27).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG27).output
	@echo "\nTest case 'function_call_before_declaration_err2' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG27).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG27).output || exit 0

	@echo "\n------------------------------------ 'function_call_before_declaration_err2' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)$(PROG27).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG27).output
	@echo "\nTest case 'function_call_before_declaration_err2' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG27).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG27).output || exit 0

	@echo "\n------------------------------------ 'function_call_before_declaration_err2' ------------------------------------\n"
	@./$(SEMPATH)$(SEM)-test < $(SEMPATH)$(EXPLDIR)$(PROG27).tl > $(SEMPATH)$(SEM)$(CURTEST)$(PROG27).output
	@echo "\nTest case 'function_call_before_declaration_err2' output differences:"
	@diff -su $(SEMPATH)$(SEM)$(REFTEST)$(PROG27).output $(SEMPATH)$(SEM)$(CURTEST)$(PROG27).output || exit 0

$(SEM)-clean:
	cd $(SEMPATH) && rm -f \
    $(SEM)$(CURTEST)$(PROG13).output \
    $(SEM)$(CURTEST)$(PROG14).output \
