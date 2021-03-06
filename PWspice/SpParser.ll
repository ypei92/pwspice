/************************************************************
             Lexer for SPICE Parser Template

Author:
   Chen, Jiajun
   Shi, Guoyong
   Hu, Hanbin
 
Used for the course project of "Introduction to EDA", 2014

   School of Micro-electronics
   Shanghai Jiaotong University
************************************************************/

%option noyywrap case-insensitive
%option yylineno

%{

#include "SpParser.hpp"

#define YY_DECL int yylex(yy::SpParser::semantic_type *yylval, yy::SpParser::location_type *yylloc)

/*#define YY_USER_ACTION yylloc->columns (yyleng);*/

namespace yy {
	int column = 1;
}

/*int column = 0;*/

#define YY_USER_ACTION {if(yylineno != yylloc->begin.line) yy::column = 0; \
						yylloc->begin.line = yylineno; \ 
						yylloc->begin.column = yy::column; \
						yy::column = yy::column+yyleng; \
						yylloc->end.column = yy::column; \
						yylloc->end.line = yylineno;}

/*#define YY_USER_ACTION {column = (yylloc->begin.line != yylineno) ? 0 : column; \
						yylloc->begin.line = yylineno; \ 
						yylloc->begin.column = column; \
						column = column+yyleng; \
						yylloc->end.column = column; \
						yylloc->end.line = yylineno;}*/

typedef yy::SpParser::token token;
%}

/* Defining output file name */
%option outfile="SpScanner.cpp"	

/* Defining Regular Expressions of the patterns */
ALPHA			[A-Za-z_]
DIGIT			[0-9]
ALPHANUM		[A-Za-z_0-9]
STRING			{ALPHANUM}+
INTEGER			{DIGIT}+
FLOAT			[\-]?{DIGIT}+"."{DIGIT}+([Ee][\+\-]?{DIGIT}+)?

RESISTOR		[Rr]{ALPHANUM}+
CAPACITOR		[Cc]{ALPHANUM}+
INDUCTOR		[Ll]{ALPHANUM}+
CURRENTSRC		[Ii]{ALPHANUM}+
VOLTAGESRC		[Vv]{ALPHANUM}+

VCCS			[Gg]{ALPHANUM}+
CCCS			[Ff]{ALPHANUM}+
CCVS			[Hh]{ALPHANUM}+
VCVS			[Ee]{ALPHANUM}+
OPAMP			[Oo]{ALPHANUM}+
SWITCH			[Ss]{ALPHANUM}+
DIODE			[Dd]{ALPHANUM}+
MOS			[Mm]{ALPHANUM}+

EOL				[\n]
DELIMITER		[ \t]+
UNIT			[Ff]|[Pp]|[Nn]|[Uu]|[Mm]|[Kk]|[Mm][Ee][Gg]|[Gg]|[Tt]
VALUE			({FLOAT}|[-]?{INTEGER}){UNIT}
COMMENT			[\*][^\n]+
END				[\.][Ee][Nn][Dd]

%%

%{
   // start where previous token ended
   yylloc->step ();
%}

{INTEGER}		{yylval->n = atoi(yytext); return token::INTEGER;}
{FLOAT}			{yylval->f = atof(yytext); return token::FLOAT;}
{RESISTOR}		{yylval->s = (char*)malloc((strlen(yytext) + 1) * sizeof(char)); 
				 strcpy(yylval->s, yytext);
				 yylval->s[strlen(yytext)] = '\0';
                 return token::RESISTOR;
				}
{CAPACITOR}		{yylval->s = (char*)malloc((strlen(yytext) + 1) * sizeof(char)); 
				 strcpy(yylval->s, yytext);
				 yylval->s[strlen(yytext)] = '\0';
                 return token::CAPACITOR;
				}
{INDUCTOR}		{yylval->s = (char*)malloc((strlen(yytext) + 1) * sizeof(char)); 
				 strcpy(yylval->s, yytext);
				 yylval->s[strlen(yytext)] = '\0';
                 return token::INDUCTOR;
				}
{CURRENTSRC}		{yylval->s = (char*)malloc((strlen(yytext) + 1) * sizeof(char)); 
				 strcpy(yylval->s, yytext);
				 yylval->s[strlen(yytext)] = '\0';
                 return token::CURRENTSRC;				
				}
{VOLTAGESRC}		{yylval->s = (char*)malloc((strlen(yytext) + 1) * sizeof(char)); 
				 strcpy(yylval->s, yytext);
				 yylval->s[strlen(yytext)] = '\0';
                 return token::VOLTAGESRC;
				}
{VCCS}			{yylval->s = (char*)malloc((strlen(yytext) + 1) * sizeof(char)); 
				 strcpy(yylval->s, yytext);
				 yylval->s[strlen(yytext)] = '\0';
                 return token::VCCS;
				}
{CCCS}			{yylval->s = (char*)malloc((strlen(yytext) + 1) * sizeof(char)); 
				 strcpy(yylval->s, yytext);
				 yylval->s[strlen(yytext)] = '\0';
                 return token::CCCS;
				}
{CCVS}			{yylval->s = (char*)malloc((strlen(yytext) + 1) * sizeof(char)); 
				 strcpy(yylval->s, yytext);
				 yylval->s[strlen(yytext)] = '\0';
                 return token::CCVS;
				}
{VCVS}			{yylval->s = (char*)malloc((strlen(yytext) + 1) * sizeof(char)); 
				 strcpy(yylval->s, yytext);
				 yylval->s[strlen(yytext)] = '\0';
                 return token::VCVS;				
				}
{OPAMP}			{yylval->s = (char*)malloc((strlen(yytext) + 1) * sizeof(char)); 
				 strcpy(yylval->s, yytext);
				 yylval->s[strlen(yytext)] = '\0';
                 return token::OPAMP;
				}
{SWITCH}		{yylval->s = (char*)malloc((strlen(yytext) + 1) * sizeof(char)); 
				 strcpy(yylval->s, yytext);
				 yylval->s[strlen(yytext)] = '\0';
                 return token::SWITCH;
				}
{DIODE}			{yylval->s = (char*)malloc((strlen(yytext) + 1) * sizeof(char)); 
				 strcpy(yylval->s, yytext);
				 yylval->s[strlen(yytext)] = '\0';
                 return token::DIODE;				
				}
{MOS}			{yylval->s = (char*)malloc((strlen(yytext) + 1) * sizeof(char)); 
				 strcpy(yylval->s, yytext);
				 yylval->s[strlen(yytext)] = '\0';
                 return token::MOS;
				}

{VALUE}			{double value;
				 value = atof(yytext);
				 int len = strlen(yytext);
				 char u = yytext[len - 1];
				 if (u == 'F' || u == 'f')
					yylval->f = value * 1e-15;
                 else if (u == 'P' || u == 'p')
					yylval->f = value * 1e-12;
				 else if (u == 'N' || u == 'n')
					yylval->f = value * 1e-9;
				 else if (u == 'U' || u == 'u')
					yylval->f = value * 1e-6;
				 else if (u == 'M' || u == 'm')
					yylval->f = value * 1e-3;
				 else if (u == 'K' || u == 'k')
					yylval->f = value * 1e3;
				 else if (u == 'G' || u == 'g')
			     {
					if (yytext[len - 2] == 'E' | yytext[len - 2] == 'e')
						yylval->f = value * 1e6;
					else
						yylval->f = value * 1e9;
				 }
				 else if (u == 'T' | u == 't')
					yylval->f = value * 1e12;
				 else
					yylval->f = value;
				 return token::VALUE;
				}
{STRING}		{yylval->s = (char*)malloc((strlen(yytext) + 1) * sizeof(char)); 
				 strcpy(yylval->s, yytext);
				 yylval->s[strlen(yytext)] = '\0';
                 return token::STRING;
			    }
{EOL}		    {return token::EOL;}
<<EOF>>			{yyterminate();}
{DELIMITER}		{yylloc->step();}
{COMMENT}		{yylloc->step();}
{END}			{return token::END;}

%%

