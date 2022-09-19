//(c) Morozov Artem 2022
/* $b16 */
#include "semantics.h"
using namespace std;
void tSM::init() {
	globals.clear();
	locals.clear();
	scope = 0;
	globals["pi"] = tgName(VAR|DEFINED|BUILT);
	globals["e"] = tgName(VAR|DEFINED|BUILT);
	globals["newline"] = tgName(PROC|DEFINED|BUILT, "", 0);
	globals["display"] = tgName(PROC|DEFINED|BUILT, "", 1);
	globals["abs"] = tgName(PROC|DEFINED|BUILT, "", 1);
	globals["sin"] = tgName(PROC|DEFINED|BUILT, "", 1);
	globals["log"] = tgName(PROC|DEFINED|BUILT, "", 1);
	return;
}
int tSM::p01() { //       S -> PROG
	bool check_error = false;
	for (tGlobal:: iterator iterator = globals.begin(); iterator != globals.end(); ++iterator) {
		if (iterator->second.test(PROC) && iterator->second.test(USED) && !iterator->second.test(DEFINED)) {
			ferror_message += "Error[01-1] in line " + iterator->second.line + ": procedure '" + iterator->first + "' was used, but was not defined!\n";
			//процедура 'x' была использована, но не была определена!
			//procedure 'x' was used, but was not defined!
			check_error = true;
			return 1;
		}
		else if (iterator->second.test(USED) && iterator->second.test(VAR) && !iterator->second.test(DEFINED)) {
			ferror_message += "Error[01-2] in line " + iterator->second.line + ": variable '" + iterator->first + "' was used, but was not defined!\n";
			//переменная 'x' была использована, но не была определена!
			//variable 'x' was used, but was not defined!
			check_error = true;
			return 1;
		}
		else if (iterator->second.test(PROC) && !iterator->second.test(USED) && iterator->second.test(DEFINED) && !iterator->second.test(BUILT)) {
			ferror_message += "Warning[01-3] in line " + iterator->second.line + ": procedure '" + iterator->first + "' was defined, but was not used!\n";
			//процедура 'x' была определена, но не была использована!
			//procedure 'x' was defined, but was not used!
			return 1;
		}
		else if (!iterator->second.test(USED) && iterator->second.test(VAR) && iterator->second.test(DEFINED) && !iterator->second.test(BUILT)) {
			ferror_message += "Warning[01-4] in line " + iterator->second.line + ": variable '" + iterator->first + "' was defined, but was not used!\n";
			//переменная 'x' была определена, но не была использована!
			//variable 'x' was defined, but was not used!
			return 1;
		}
	}
	if (check_error) {
		return 1;
	}
	return 0;
}
int tSM::p02() { //    PROG -> CALCS
	return 0;
}
int tSM::p03() { //    PROG -> DEFS
	return 0;
}
int tSM::p04() { //    PROG -> DEFS CALCS
	return 0;
}
int tSM::p05() { //       E -> $id
	string current_name = S1->name;
	string current_line = S1->line;
	switch (scope) {
		case 1:
			if (locals.count(current_name))
			return 0;
		default:
			tgName &link = globals[current_name];
			if (link.empty()) {
				link = tgName(VAR|USED, current_line);
				return 0;
			}
			else if (link.test(VAR)) {
				link.set(USED);
				return 0;
			}
			else if (link.test(BUILT)) {
				ferror_message += "Error[05-1] in line " + current_line + ": integrated procedure '" + current_name + "' can't be used as a variable!\n";
				//встроенная процедура 'x' не может быть использована как переменная!
				//integrated procedure 'x' can't be used as a variable!
				return 1;
			}
	}
	return 0; 
}
int tSM::p06() { //       E -> $int
	return 0;
}
int tSM::p07() { //       E -> $dec
	return 0;
}
int tSM::p08() { //       E -> AREX
	return 0;
}
int tSM::p09() { //       E -> COND
	return 0;
}
int tSM::p10() { //       E -> EASYLET
	return 0;
}
int tSM::p11() { //       E -> CPROC
	return 0;
}
int tSM::p12() { // EASYLET -> HEASYL E )
	return 0;
}
int tSM::p13() { //  HEASYL -> ( let ( )
	return 0;
}
int tSM::p14() { //  HEASYL -> HEASYL INTER
	return 0;
}
int tSM::p15() { //    AREX -> HAREX E )
	return 0;
}
int tSM::p16() { //   HAREX -> ( AROP
	return 0;
}
int tSM::p17() { //   HAREX -> HAREX E
	return 0;
}
int tSM::p18() { //    AROP -> +
	return 0;
}
int tSM::p19() { //    AROP -> -
	return 0;
}
int tSM::p20() { //    AROP -> *
	return 0;
}
int tSM::p21() { //    AROP -> /
	return 0;
}
int tSM::p22() { //   CPROC -> HCPROC )
	string current_name = S1->name;
	string current_line = S1->line;
	int current_count = S1->count;
	switch (scope) {
		case 1:
			if (locals.count(current_name)) {
				ferror_message += "Error[22-1] in line " + current_line + ": global procedure with parameter name '" + current_name + "' already exists!\n";
				//глобальная процедура с именем 'x' уже существует!
				//global procedure with name 'x' already exists!
				return 1;
			}
		default:
			tgName &link = globals[current_name];
			if (link.empty()) {
				link = tgName(PROC|USED, current_line, current_count);
				return 0;
			}
			if (link.test(VAR)) {
				ferror_message += "Error[22-2] in line " + current_line + ": variable with name '" + current_name + "' is not a procedure!\n";
				//переменная с именем 'x' не является процедурой!
				//variable with name 'x' is not a procedure!
				return 1;
			}
			if (link.arity != current_count) {
				ferror_message += "Error[22-3] in line " + current_line + ": procedure '" + current_name + "' doesn't accept such a number of parameters: " + Uint_to_str(current_count) + ", it takes another number of parameters: " + Uint_to_str(link.arity) + "!\n";
				//процедура не принимает столько параметров, она принимает другое количество параметров!
				//procedure doesn't accept such a number of parameters, it takes another number of parameters!
				return 1;
			}
			link.set(USED);
	}
	return 0; 
}
int tSM::p23() { //  HCPROC -> ( $id
	S1->name = S2->name;
	S1->types = 0;
	S1->count = 0;
	return 0;
}
int tSM::p24() { //  HCPROC -> HCPROC E
	++S1->count;
	return 0; 
}
int tSM::p25() { //    COND -> ( cond BRANCHES )
	return 0;
}
int tSM::p26() { //BRANCHES -> ELSE
	return 0;
}
int tSM::p27() { //BRANCHES -> CLAUS BRANCHES
	return 0;
}
int tSM::p28() { //   CLAUS -> ( BOOL E )
	return 0;
}
int tSM::p29() { //    ELSE -> ( else ELSEB )
	return 0;
}
int tSM::p30() { //   ELSEB -> E
	return 0;
}
int tSM::p31() { //   ELSEB -> INTER ELSEB
	return 0;
}
int tSM::p32() { //     STR -> $str
	return 0;
}
int tSM::p33() { //     STR -> SIF
	return 0;
}
int tSM::p34() { //     SIF -> ( if BOOL STR STR )
	return 0;
}
int tSM::p35() { //    BOOL -> $bool
	return 0;
}
int tSM::p36() { //    BOOL -> $idq
	string current_name = S1->name;
	string current_line = S1->line;
	bool scope_flag = false;
	if ((scope_flag > 1 && locals.count(current_name)) || (scope > 0 && locals.count(current_name))) {
		scope_flag = true;
		return 0;
	}
	if (!scope_flag) {
		ferror_message += "Error[36-1] in line: "+ current_line + ": a variable of the bool type '" + current_name + "' was not declared at this scope!\n";
		//переменная типа bool не была определена!
		//a variable of the bool type was not declared at this scope!
		return 1;
	}
	return 0;
}
int tSM::p37() { //    BOOL -> REL
	return 0;
}
int tSM::p38() { //    BOOL -> ( not BOOL )
	return 0;
}
int tSM::p39() { //    BOOL -> OR
	return 0;
}
int tSM::p40() { //    BOOL -> CPRED
	return 0;
}
int tSM::p41() { //      OR -> ( or ORARGS )
	return 0;
}
int tSM::p42() { //  ORARGS -> BOOL ORARGS
	return 0;
}
int tSM::p43() { //  ORARGS -> BOOL
	return 0;
}
int tSM::p44() { //   CPRED -> ( $idq )
	string current_name = S1->name;
	string current_line = S1->line;
	int current_count = S1->count;
	int current_types = S1->types;
    tgName &link = globals[current_name];
    if (link.empty()) {
        link = tgName(PROC|USED, current_line, current_count);
        return 0;
    }
	link.set(USED);
    return 0;
}
int tSM::p45() { //   CPRED -> ( $idq PDARGS )
	return 0;
}
int tSM::p46() { //  PDARGS -> ARG
	return 0;
}
int tSM::p47() { //  PDARGS -> ARG PDARGS
	return 0;
}
int tSM::p48() { //     ARG -> E
	S1->types = 0;
	return 0;
}
int tSM::p49() { //     ARG -> BOOL
	S1->types = 1;
	return 0; 
}
int tSM::p50() { //     REL -> ( = E E )
	return 0;
}
int tSM::p51() { //     REL -> ( >= E E )
	return 0;
}
int tSM::p52() { // DISPSET -> ( display E )
	return 0;
}
int tSM::p53() { // DISPSET -> ( display BOOL )
	return 0;
}
int tSM::p54() { // DISPSET -> ( display STR )
	return 0;
}
int tSM::p55() { // DISPSET -> ( newline )
	return 0;
}
int tSM::p56() { // DISPSET -> SET
	return 0;
}
int tSM::p57() { //   INTER -> DISPSET
	return 0;
}
int tSM::p58() { //   INTER -> E
	return 0;
}
int tSM::p59() { //   CALCS -> CALC
	return 0;
}
int tSM::p60() { //   CALCS -> CALCS CALC
	return 0;
}
int tSM::p61() { //    CALC -> E
	return 0;
}
int tSM::p62() { //    CALC -> BOOL
	return 0;
}
int tSM::p63() { //    CALC -> STR
	return 0;
}
int tSM::p64() { //    CALC -> DISPSET
	return 0;
}
int tSM::p65() { //    DEFS -> DEF
	return 0;
}
int tSM::p66() { //    DEFS -> DEFS DEF
	return 0;
}
int tSM::p67() { //     DEF -> PRED
	return 0;
}
int tSM::p68() { //     DEF -> VAR
	return 0;
}
int tSM::p69() { //     DEF -> PROC
	return 0;
}
int tSM::p70() { //    PRED -> HPRED BOOL )
	string current_name = S1->name;
	string current_line = S1->line;
	int	current_count = S1->count;
	int current_types = S1->types;
    tgName& link = globals[current_name];
	if (link.empty()) {
		link = tgName(PROC|DEFINED|USED, current_line, current_count, current_types);
		locals.clear();
		scope = 0;
		return 0;
	}
	locals.clear();
	scope = 0;
	link.set(DEFINED);
	return 0;
}
int tSM::p71() { //   HPRED -> PDPAR )
	scope = 1;
	return 0;
}
int tSM::p72() { //   PDPAR -> ( define ( $idq
	S1->name = S4->name;
    S1->count = 0;
	return 0;
}
int tSM::p73() { //   PDPAR -> PDPAR $idq
	++S1->count;
	string current_name = S1->name;
	string current_line = S1->line;
	int	current_count = S1->count;
	int current_types = S1->types;
	string another_name = S2->name;
	string another_line = S2->line;
	tgName& link = globals[current_name];
	if (locals.count(another_name)) {
      	ferror_message += "Error[73-1] in line "+ another_line +": the procedure '" + current_name + "' duplicated the '" + another_name +"' parameter!\n";
		//в процедуре 'x' дублировался параметр 'y'!
		//the procedure 'x duplicated the 'y' parameter!
		return 1;
	}
	if (another_name == current_name) {
    	ferror_message += "Warning[73-2] in line " + another_line + ": in the procedure '" + current_name + "' a parameter of the same name with the procedure has been met!\n";
		//в процедуре встречен одноименный с ней параметр!
		//in the procedure a parameter of the same name with the procedure has been met!
		return 1;
	}
	locals.insert(another_name);
	return 0;
}
int tSM::p74() { //   PDPAR -> PDPAR $id
	string current_name = S1->name;
	string current_line = S1->line;
	int	current_count = S1->count;
	int current_types = S1->types;
	string another_name = S2->name;
	string another_line = S2->line;
	if (locals.count(another_name)) {
        ferror_message += "Error[74-1] in line " + another_line + ": the parameter '" + another_name + "' is duplicated in the predicate '" + current_name + "'!\n";
        // в предикате 'x' дублируется параметр 'y'
        // the parameter 'y' is duplicated in the predicate 'x'
        return 1;
    }
    current_types |= 0 << current_count;
    locals.insert(another_name);
    ++S1->count;
	return 0; 
}
int tSM::p75() { //     SET -> ( set! $id E )
	string another_name = S3->name;
	string current_line = S1->line;
    switch (scope) {
        case 1:
            if (locals.count(another_name)) {
                return 0;
            }
        default:
            tgName &link = globals[another_name];
            if (link.empty()) {
                link = tgName(VAR | USED, current_line);
                return 0;
            }
            if (link.test(VAR) && link.test(BUILT)) {
                ferror_message += "Error[75-1] in line " + current_line + ": the global constant '" + another_name + "' must not be overridden!\n";
                // глобальную константу нельзя переопределять!
                // the global constant cannot be overridden!
                return 1;
            }
    }
    globals[another_name].set(USED);
	return 0;
}
int tSM::p76() { //     VAR -> VARDCL VARINI )
	return 0;
}
int tSM::p77() { //  VARDCL -> ( define $id
	string another_name = S3->name;
	string another_line = S3->line;
    tgName& link = globals[another_name];
    if (link.empty()) {
        link = tgName(VAR|DEFINED, another_line);
        return 0;
    }
    link.set(DEFINED);
	return 0;
}
int tSM::p78() { //  VARINI -> $int
	return 0;
}
int tSM::p79() { //  VARINI -> $dec
	return 0;
}
int tSM::p80() { //    PROC -> HPROC PCBODY )
	string current_name = S1->name;
	string current_line = S1->line;
	int	current_count = S1->count;
	int current_types = S1->types;
    tgName& link = globals[current_name];
    if (link.empty()) {
        link = tgName(PROC|DEFINED, current_line, current_count, current_types);
        scope = 0;
        locals.clear();
        return 0;
    }
    if (link.test(VAR)) {
        ferror_message += "Error[80-1] in line " + current_line + ": the procedure '" + current_name + "' has the same name as the global variable in the following line: " + link.line + "!\n";
        // процедура 'x' имеет то же имя, что и глобальная переменная!
        // the procedure 'x' has the same name as the global variable in the following line!
        return 1;
    }
    if (link.test(DEFINED)) {
        ferror_message += "Error[80-2] in line " + current_line + ": the procedure '" + current_name + "' can't be overridden! (mentioned in line " + link.line + ")!\n";
        // процедура 'x' не может быть переопределена!
        // procedure 'x' can't be overridden!
        return 1;
    }
    if (link.test(USED) && link.arity != current_count) {
        ferror_message += "Error[80-3] in line " + current_line + ": the procedure '" + current_name + "' has been called with such number of parameters: " + Uint_to_str(link.arity) + ", but another number of parameters has been passed: " + Uint_to_str(current_count) + "!\n";
        // процедура 'x' была вызвана с одним количеством параметров, однако другое количество параметров было передано!
        // the procedure 'x' has been called with such number of parameters, but another number of parameters has been passed! 
        return 1;
    }
    link.set(DEFINED);
    scope = 0;
    locals.clear();
    return 0;
}
int tSM::p81() { //   HPROC -> PCPAR )
	scope = 1;
	return 0;
}
int tSM::p82() { //  PCBODY -> E
	return 0;
}
int tSM::p83() { //  PCBODY -> INTER PCBODY
	return 0;
}
int tSM::p84() { //  PCBODY -> VAR PCBODY
	return 0;
}
int tSM::p85() { //   PCPAR -> ( define ( $id
	S1->name = S4->name;
    S1->count = 0;
	return 0;
}
int tSM::p86() { //   PCPAR -> PCPAR $id
	string current_name = S1->name;
	string another_name = S2->name;
	string another_line = S2->line;
	++S1->count;
	if (current_name == another_name) {
		ferror_message += "Warning[86-1] in line " + another_line + ": in the procedure '" + current_name + "' a parameter of the same name with the procedure has been met!\n";
		//в процедуре встречен одноименный с ней параметр!
		//in the procedure a parameter of the same name with the procedure has been met!
		return 1;
	}
	locals.insert(another_name);
	return 0;
}
//_____________________
int tSM::p87(){return 0;} int tSM::p88(){return 0;} 
int tSM::p89(){return 0;} int tSM::p90(){return 0;} 
int tSM::p91(){return 0;} int tSM::p92(){return 0;} 
int tSM::p93(){return 0;} int tSM::p94(){return 0;} 
int tSM::p95(){return 0;} int tSM::p96(){return 0;} 
int tSM::p97(){return 0;} int tSM::p98(){return 0;} 
int tSM::p99(){return 0;} int tSM::p100(){return 0;} 
int tSM::p101(){return 0;} int tSM::p102(){return 0;} 
int tSM::p103(){return 0;} int tSM::p104(){return 0;} 
int tSM::p105(){return 0;} int tSM::p106(){return 0;} 
int tSM::p107(){return 0;} int tSM::p108(){return 0;} 
int tSM::p109(){return 0;} int tSM::p110(){return 0;}