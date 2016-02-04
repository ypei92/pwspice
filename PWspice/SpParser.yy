/************************************************************
             Scanner for SPICE Parser Template

Author:
   Chen, Jiajun
   Shi, Guoyong
   Hu, Hanbin
 
Used for the course project of "Introduction to EDA", 2014

   School of Micro-electronics
   Shanghai Jiaotong University
************************************************************/

%skeleton "lalr1.cc"
%defines
%locations

%define "parser_class_name" "SpParser"

%code requires{
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>

using std::cerr;
using std::endl;
using std::string;

#include "MyClass.h"
	
extern FILE* yyin;
}

/* set the output file name */
%output="./SpParser.cpp"
%verbose

%union
{
	double f;
	int n;
	char* s;
};

/* defining parser input variable type */
%parse-param {MyClass* pObj}

/* assigning data type for tokens and patterns */
%token<f> FLOAT
%token<s> STRING
%token<n> INTEGER
%token<s> RESISTOR CAPACITOR INDUCTOR CURRENTSRC VOLTAGESRC VCCS CCCS CCVS VCVS OPAMP SWITCH DIODE MOS
%token<f> VALUE
%type<s> resistor capacitor inductor currentsrc voltagesrc vccs cccs ccvs vcvs opamp switch_on_off  diode mos node variable
%type<f> value
%token END EOL

%{
extern int yylex(yy::SpParser::semantic_type* yylval,
                 yy::SpParser::location_type* yylloc);
%}

%initial-action {
  // Filename for locations here
  @$.begin.filename = @$.end.filename = new std::string("stdin");
}

%%


spice: netlist end
;

end: end EOL
   | END EOL
;

netlist: netlist line
       | line
;

line: component EOL
	| error EOL
	| EOL
;

component:	  resistor
		| capacitor
		| inductor
		| currentsrc
		| voltagesrc
		| vccs
		| cccs
		| ccvs
		| vcvs
		| opamp
		| switch_on_off
		| diode
		| mos		
;


resistor: RESISTOR node node value
		  {
			 pObj->ParseRes($1, $2, $3, $4);
		  }
;

capacitor: CAPACITOR node node value					
           {
              pObj->ParseCap($1, $2, $3, $4);
		   }
		 | CAPACITOR node node value value
		   {
		   	  pObj->ParseCap($1, $2, $3, $4, $5);
		   }
;		
	
inductor: INDUCTOR node node value  				
		  {
			  pObj->ParseInd($1, $2, $3, $4);
		  }
		| INDUCTOR node node value value
		  {
		  	  pObj->ParseInd($1, $2, $3, $4, $5);
		  }
;


voltagesrc: VOLTAGESRC node node value						
            {
		    	pObj->ParseVsrc($1, $2, $3, $4);
			}
;

currentsrc: CURRENTSRC node node value						
            {
				pObj->ParseIsrc($1, $2, $3, $4);
			}
;

vccs : VCCS node node node node value
		{
			pObj -> ParseVCCS($1, $2, $3, $4, $5, $6 );
			}
;
cccs : CCCS node node node value
		{
			pObj -> ParseCCCS($1, $2, $3, $4, $5 );
			}
/*       CCCS node node value	
		{
			pObj -> ParseCCCS_1($1, $2, $3, $4);
			}*/
;
ccvs : CCVS node node node value
		{
			pObj -> ParseCCVS($1, $2, $3, $4, $5 );
			}
/*       CCVS node node value	
		{
			pObj -> ParseCCVS_1($1, $2, $3, $4);
			}*/
;
vcvs : VCVS node node node node value
		{
			pObj -> ParseVCVS($1, $2, $3, $4, $5, $6 );
			}
;
opamp : OPAMP node node node node
		{
			pObj -> ParseOpamp($1, $2, $3, $4);
			}
;
switch_on_off : SWITCH node node
		{
			pObj -> ParseSwitch($1, $2, $3);
			}
;
diode : DIODE node node value
		{
			pObj -> ParseDiode($1, $2, $3, $4);
			}		
;
mos : MOS node node node node value value
		{
			pObj -> ParseMos($1, $2, $3, $4, $5, $6, $7);
			}
;
node: variable										
      {
	  	  $$ = new char[strlen($1) + 1];
		  strcpy($$, $1); 
		  $$[strlen($1)] = '\0';
	  }

    | INTEGER
	  {
	  	  char s[33];
		  sprintf(s, "%d", $1);
		  $$ = new char[strlen(s) + 1];
		  strcpy($$, s);
		  $$[strlen(s)] = '\0';
	  }
;

variable: STRING				{$$ = new char[strlen($1) + 1]; strcpy($$, $1); $$[strlen($1)] = '\0';}
	    | RESISTOR				{$$ = new char[strlen($1) + 1]; strcpy($$, $1); $$[strlen($1)] = '\0';}
	    | CAPACITOR				{$$ = new char[strlen($1) + 1]; strcpy($$, $1); $$[strlen($1)] = '\0';}
            | INDUCTOR 				{$$ = new char[strlen($1) + 1]; strcpy($$, $1); $$[strlen($1)] = '\0';}
	    | CURRENTSRC  			{$$ = new char[strlen($1) + 1]; strcpy($$, $1); $$[strlen($1)] = '\0';}
	    | VOLTAGESRC			{$$ = new char[strlen($1) + 1]; strcpy($$, $1); $$[strlen($1)] = '\0';}
	    | VCCS				{$$ = new char[strlen($1) + 1]; strcpy($$, $1); $$[strlen($1)] = '\0';}
	    | CCCS				{$$ = new char[strlen($1) + 1]; strcpy($$, $1); $$[strlen($1)] = '\0';}
            | CCVS 				{$$ = new char[strlen($1) + 1]; strcpy($$, $1); $$[strlen($1)] = '\0';}
	    | VCVS  				{$$ = new char[strlen($1) + 1]; strcpy($$, $1); $$[strlen($1)] = '\0';}
	    | OPAMP				{$$ = new char[strlen($1) + 1]; strcpy($$, $1); $$[strlen($1)] = '\0';}
	    | SWITCH 				{$$ = new char[strlen($1) + 1]; strcpy($$, $1); $$[strlen($1)] = '\0';}
	    | DIODE  				{$$ = new char[strlen($1) + 1]; strcpy($$, $1); $$[strlen($1)] = '\0';}
	    | MOS				{$$ = new char[strlen($1) + 1]; strcpy($$, $1); $$[strlen($1)] = '\0';}
;

value: VALUE											{$$ = $1;}
         | FLOAT										{$$ = $1;}
         | INTEGER										{$$ = $1;}
;

%%

void yy::SpParser::error(const location &loc, const string &s) 
{
	cerr << "error at " << loc << ": " << s << endl;
}
