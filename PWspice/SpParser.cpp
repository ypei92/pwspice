/* A Bison parser, made by GNU Bison 2.5.  */

/* Skeleton implementation for Bison LALR(1) parsers in C++
   
      Copyright (C) 2002-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* First part of user declarations.  */


/* Line 293 of lalr1.cc  */
#line 39 "./SpParser.cpp"


#include "SpParser.hpp"

/* User implementation prologue.  */

/* Line 299 of lalr1.cc  */
#line 60 "SpParser.yy"

extern int yylex(yy::SpParser::semantic_type* yylval,
                 yy::SpParser::location_type* yylloc);


/* Line 299 of lalr1.cc  */
#line 54 "./SpParser.cpp"

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* FIXME: INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                               \
 do                                                                    \
   if (N)                                                              \
     {                                                                 \
       (Current).begin = YYRHSLOC (Rhs, 1).begin;                      \
       (Current).end   = YYRHSLOC (Rhs, N).end;                        \
     }                                                                 \
   else                                                                \
     {                                                                 \
       (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;        \
     }                                                                 \
 while (false)
#endif

/* Suppress unused-variable warnings by "using" E.  */
#define YYUSE(e) ((void) (e))

/* Enable debugging if requested.  */
#if YYDEBUG

/* A pseudo ostream that takes yydebug_ into account.  */
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)	\
do {							\
  if (yydebug_)						\
    {							\
      *yycdebug_ << Title << ' ';			\
      yy_symbol_print_ ((Type), (Value), (Location));	\
      *yycdebug_ << std::endl;				\
    }							\
} while (false)

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug_)				\
    yy_reduce_print_ (Rule);		\
} while (false)

# define YY_STACK_PRINT()		\
do {					\
  if (yydebug_)				\
    yystack_print_ ();			\
} while (false)

#else /* !YYDEBUG */

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_REDUCE_PRINT(Rule)
# define YY_STACK_PRINT()

#endif /* !YYDEBUG */

#define yyerrok		(yyerrstatus_ = 0)
#define yyclearin	(yychar = yyempty_)

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace yy {

/* Line 382 of lalr1.cc  */
#line 140 "./SpParser.cpp"

  /// Build a parser object.
  SpParser::SpParser (MyClass* pObj_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      pObj (pObj_yyarg)
  {
  }

  SpParser::~SpParser ()
  {
  }

#if YYDEBUG
  /*--------------------------------.
  | Print this symbol on YYOUTPUT.  |
  `--------------------------------*/

  inline void
  SpParser::yy_symbol_value_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yyvaluep);
    switch (yytype)
      {
         default:
	  break;
      }
  }


  void
  SpParser::yy_symbol_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    *yycdebug_ << (yytype < yyntokens_ ? "token" : "nterm")
	       << ' ' << yytname_[yytype] << " ("
	       << *yylocationp << ": ";
    yy_symbol_value_print_ (yytype, yyvaluep, yylocationp);
    *yycdebug_ << ')';
  }
#endif

  void
  SpParser::yydestruct_ (const char* yymsg,
			   int yytype, semantic_type* yyvaluep, location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yymsg);
    YYUSE (yyvaluep);

    YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

    switch (yytype)
      {
  
	default:
	  break;
      }
  }

  void
  SpParser::yypop_ (unsigned int n)
  {
    yystate_stack_.pop (n);
    yysemantic_stack_.pop (n);
    yylocation_stack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  SpParser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  SpParser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  SpParser::debug_level_type
  SpParser::debug_level () const
  {
    return yydebug_;
  }

  void
  SpParser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif

  inline bool
  SpParser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  SpParser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  SpParser::parse ()
  {
    /// Lookahead and lookahead in internal form.
    int yychar = yyempty_;
    int yytoken = 0;

    /* State.  */
    int yyn;
    int yylen = 0;
    int yystate = 0;

    /* Error handling.  */
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// Semantic value of the lookahead.
    semantic_type yylval;
    /// Location of the lookahead.
    location_type yylloc;
    /// The locations where the error started and ended.
    location_type yyerror_range[3];

    /// $$.
    semantic_type yyval;
    /// @$.
    location_type yyloc;

    int yyresult;

    YYCDEBUG << "Starting parse" << std::endl;


    /* User initialization code.  */
    
/* Line 565 of lalr1.cc  */
#line 65 "SpParser.yy"
{
  // Filename for locations here
  yylloc.begin.filename = yylloc.end.filename = new std::string("stdin");
}

/* Line 565 of lalr1.cc  */
#line 296 "./SpParser.cpp"

    /* Initialize the stacks.  The initial state will be pushed in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystate_stack_ = state_stack_type (0);
    yysemantic_stack_ = semantic_stack_type (0);
    yylocation_stack_ = location_stack_type (0);
    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yylloc);

    /* New state.  */
  yynewstate:
    yystate_stack_.push (yystate);
    YYCDEBUG << "Entering state " << yystate << std::endl;

    /* Accept?  */
    if (yystate == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    /* Backup.  */
  yybackup:

    /* Try to take a decision without lookahead.  */
    yyn = yypact_[yystate];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    /* Read a lookahead token.  */
    if (yychar == yyempty_)
      {
	YYCDEBUG << "Reading a token: ";
	yychar = yylex (&yylval, &yylloc);
      }


    /* Convert token to internal form.  */
    if (yychar <= yyeof_)
      {
	yychar = yytoken = yyeof_;
	YYCDEBUG << "Now at end of input." << std::endl;
      }
    else
      {
	yytoken = yytranslate_ (yychar);
	YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
      }

    /* If the proper action on seeing token YYTOKEN is to reduce or to
       detect an error, take that action.  */
    yyn += yytoken;
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yytoken)
      goto yydefault;

    /* Reduce or error.  */
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
	if (yy_table_value_is_error_ (yyn))
	  goto yyerrlab;
	yyn = -yyn;
	goto yyreduce;
      }

    /* Shift the lookahead token.  */
    YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

    /* Discard the token being shifted.  */
    yychar = yyempty_;

    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yylloc);

    /* Count tokens shifted since error; after three, turn off error
       status.  */
    if (yyerrstatus_)
      --yyerrstatus_;

    yystate = yyn;
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystate];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    /* If YYLEN is nonzero, implement the default value of the action:
       `$$ = $1'.  Otherwise, use the top of the stack.

       Otherwise, the following line sets YYVAL to garbage.
       This behavior is undocumented and Bison
       users should not rely upon it.  */
    if (yylen)
      yyval = yysemantic_stack_[yylen - 1];
    else
      yyval = yysemantic_stack_[0];

    {
      slice<location_type, location_stack_type> slice (yylocation_stack_, yylen);
      YYLLOC_DEFAULT (yyloc, slice, yylen);
    }
    YY_REDUCE_PRINT (yyn);
    switch (yyn)
      {
	  case 23:

/* Line 690 of lalr1.cc  */
#line 106 "SpParser.yy"
    {
			 pObj->ParseRes((yysemantic_stack_[(4) - (1)].s), (yysemantic_stack_[(4) - (2)].s), (yysemantic_stack_[(4) - (3)].s), (yysemantic_stack_[(4) - (4)].f));
		  }
    break;

  case 24:

/* Line 690 of lalr1.cc  */
#line 112 "SpParser.yy"
    {
              pObj->ParseCap((yysemantic_stack_[(4) - (1)].s), (yysemantic_stack_[(4) - (2)].s), (yysemantic_stack_[(4) - (3)].s), (yysemantic_stack_[(4) - (4)].f));
		   }
    break;

  case 25:

/* Line 690 of lalr1.cc  */
#line 116 "SpParser.yy"
    {
		   	  pObj->ParseCap((yysemantic_stack_[(5) - (1)].s), (yysemantic_stack_[(5) - (2)].s), (yysemantic_stack_[(5) - (3)].s), (yysemantic_stack_[(5) - (4)].f), (yysemantic_stack_[(5) - (5)].f));
		   }
    break;

  case 26:

/* Line 690 of lalr1.cc  */
#line 122 "SpParser.yy"
    {
			  pObj->ParseInd((yysemantic_stack_[(4) - (1)].s), (yysemantic_stack_[(4) - (2)].s), (yysemantic_stack_[(4) - (3)].s), (yysemantic_stack_[(4) - (4)].f));
		  }
    break;

  case 27:

/* Line 690 of lalr1.cc  */
#line 126 "SpParser.yy"
    {
		  	  pObj->ParseInd((yysemantic_stack_[(5) - (1)].s), (yysemantic_stack_[(5) - (2)].s), (yysemantic_stack_[(5) - (3)].s), (yysemantic_stack_[(5) - (4)].f), (yysemantic_stack_[(5) - (5)].f));
		  }
    break;

  case 28:

/* Line 690 of lalr1.cc  */
#line 133 "SpParser.yy"
    {
		    	pObj->ParseVsrc((yysemantic_stack_[(4) - (1)].s), (yysemantic_stack_[(4) - (2)].s), (yysemantic_stack_[(4) - (3)].s), (yysemantic_stack_[(4) - (4)].f));
			}
    break;

  case 29:

/* Line 690 of lalr1.cc  */
#line 139 "SpParser.yy"
    {
				pObj->ParseIsrc((yysemantic_stack_[(4) - (1)].s), (yysemantic_stack_[(4) - (2)].s), (yysemantic_stack_[(4) - (3)].s), (yysemantic_stack_[(4) - (4)].f));
			}
    break;

  case 30:

/* Line 690 of lalr1.cc  */
#line 145 "SpParser.yy"
    {
			pObj -> ParseVCCS((yysemantic_stack_[(6) - (1)].s), (yysemantic_stack_[(6) - (2)].s), (yysemantic_stack_[(6) - (3)].s), (yysemantic_stack_[(6) - (4)].s), (yysemantic_stack_[(6) - (5)].s), (yysemantic_stack_[(6) - (6)].f) );
			}
    break;

  case 31:

/* Line 690 of lalr1.cc  */
#line 150 "SpParser.yy"
    {
			pObj -> ParseCCCS((yysemantic_stack_[(5) - (1)].s), (yysemantic_stack_[(5) - (2)].s), (yysemantic_stack_[(5) - (3)].s), (yysemantic_stack_[(5) - (4)].s), (yysemantic_stack_[(5) - (5)].f) );
			}
    break;

  case 32:

/* Line 690 of lalr1.cc  */
#line 159 "SpParser.yy"
    {
			pObj -> ParseCCVS((yysemantic_stack_[(5) - (1)].s), (yysemantic_stack_[(5) - (2)].s), (yysemantic_stack_[(5) - (3)].s), (yysemantic_stack_[(5) - (4)].s), (yysemantic_stack_[(5) - (5)].f) );
			}
    break;

  case 33:

/* Line 690 of lalr1.cc  */
#line 168 "SpParser.yy"
    {
			pObj -> ParseVCVS((yysemantic_stack_[(6) - (1)].s), (yysemantic_stack_[(6) - (2)].s), (yysemantic_stack_[(6) - (3)].s), (yysemantic_stack_[(6) - (4)].s), (yysemantic_stack_[(6) - (5)].s), (yysemantic_stack_[(6) - (6)].f) );
			}
    break;

  case 34:

/* Line 690 of lalr1.cc  */
#line 173 "SpParser.yy"
    {
			pObj -> ParseOpamp((yysemantic_stack_[(5) - (1)].s), (yysemantic_stack_[(5) - (2)].s), (yysemantic_stack_[(5) - (3)].s), (yysemantic_stack_[(5) - (4)].s));
			}
    break;

  case 35:

/* Line 690 of lalr1.cc  */
#line 178 "SpParser.yy"
    {
			pObj -> ParseSwitch((yysemantic_stack_[(3) - (1)].s), (yysemantic_stack_[(3) - (2)].s), (yysemantic_stack_[(3) - (3)].s));
			}
    break;

  case 36:

/* Line 690 of lalr1.cc  */
#line 183 "SpParser.yy"
    {
			pObj -> ParseDiode((yysemantic_stack_[(4) - (1)].s), (yysemantic_stack_[(4) - (2)].s), (yysemantic_stack_[(4) - (3)].s), (yysemantic_stack_[(4) - (4)].f));
			}
    break;

  case 37:

/* Line 690 of lalr1.cc  */
#line 188 "SpParser.yy"
    {
			pObj -> ParseMos((yysemantic_stack_[(7) - (1)].s), (yysemantic_stack_[(7) - (2)].s), (yysemantic_stack_[(7) - (3)].s), (yysemantic_stack_[(7) - (4)].s), (yysemantic_stack_[(7) - (5)].s), (yysemantic_stack_[(7) - (6)].f), (yysemantic_stack_[(7) - (7)].f));
			}
    break;

  case 38:

/* Line 690 of lalr1.cc  */
#line 193 "SpParser.yy"
    {
	  	  (yyval.s) = new char[strlen((yysemantic_stack_[(1) - (1)].s)) + 1];
		  strcpy((yyval.s), (yysemantic_stack_[(1) - (1)].s)); 
		  (yyval.s)[strlen((yysemantic_stack_[(1) - (1)].s))] = '\0';
	  }
    break;

  case 39:

/* Line 690 of lalr1.cc  */
#line 200 "SpParser.yy"
    {
	  	  char s[33];
		  sprintf(s, "%d", (yysemantic_stack_[(1) - (1)].n));
		  (yyval.s) = new char[strlen(s) + 1];
		  strcpy((yyval.s), s);
		  (yyval.s)[strlen(s)] = '\0';
	  }
    break;

  case 40:

/* Line 690 of lalr1.cc  */
#line 209 "SpParser.yy"
    {(yyval.s) = new char[strlen((yysemantic_stack_[(1) - (1)].s)) + 1]; strcpy((yyval.s), (yysemantic_stack_[(1) - (1)].s)); (yyval.s)[strlen((yysemantic_stack_[(1) - (1)].s))] = '\0';}
    break;

  case 41:

/* Line 690 of lalr1.cc  */
#line 210 "SpParser.yy"
    {(yyval.s) = new char[strlen((yysemantic_stack_[(1) - (1)].s)) + 1]; strcpy((yyval.s), (yysemantic_stack_[(1) - (1)].s)); (yyval.s)[strlen((yysemantic_stack_[(1) - (1)].s))] = '\0';}
    break;

  case 42:

/* Line 690 of lalr1.cc  */
#line 211 "SpParser.yy"
    {(yyval.s) = new char[strlen((yysemantic_stack_[(1) - (1)].s)) + 1]; strcpy((yyval.s), (yysemantic_stack_[(1) - (1)].s)); (yyval.s)[strlen((yysemantic_stack_[(1) - (1)].s))] = '\0';}
    break;

  case 43:

/* Line 690 of lalr1.cc  */
#line 212 "SpParser.yy"
    {(yyval.s) = new char[strlen((yysemantic_stack_[(1) - (1)].s)) + 1]; strcpy((yyval.s), (yysemantic_stack_[(1) - (1)].s)); (yyval.s)[strlen((yysemantic_stack_[(1) - (1)].s))] = '\0';}
    break;

  case 44:

/* Line 690 of lalr1.cc  */
#line 213 "SpParser.yy"
    {(yyval.s) = new char[strlen((yysemantic_stack_[(1) - (1)].s)) + 1]; strcpy((yyval.s), (yysemantic_stack_[(1) - (1)].s)); (yyval.s)[strlen((yysemantic_stack_[(1) - (1)].s))] = '\0';}
    break;

  case 45:

/* Line 690 of lalr1.cc  */
#line 214 "SpParser.yy"
    {(yyval.s) = new char[strlen((yysemantic_stack_[(1) - (1)].s)) + 1]; strcpy((yyval.s), (yysemantic_stack_[(1) - (1)].s)); (yyval.s)[strlen((yysemantic_stack_[(1) - (1)].s))] = '\0';}
    break;

  case 46:

/* Line 690 of lalr1.cc  */
#line 215 "SpParser.yy"
    {(yyval.s) = new char[strlen((yysemantic_stack_[(1) - (1)].s)) + 1]; strcpy((yyval.s), (yysemantic_stack_[(1) - (1)].s)); (yyval.s)[strlen((yysemantic_stack_[(1) - (1)].s))] = '\0';}
    break;

  case 47:

/* Line 690 of lalr1.cc  */
#line 216 "SpParser.yy"
    {(yyval.s) = new char[strlen((yysemantic_stack_[(1) - (1)].s)) + 1]; strcpy((yyval.s), (yysemantic_stack_[(1) - (1)].s)); (yyval.s)[strlen((yysemantic_stack_[(1) - (1)].s))] = '\0';}
    break;

  case 48:

/* Line 690 of lalr1.cc  */
#line 217 "SpParser.yy"
    {(yyval.s) = new char[strlen((yysemantic_stack_[(1) - (1)].s)) + 1]; strcpy((yyval.s), (yysemantic_stack_[(1) - (1)].s)); (yyval.s)[strlen((yysemantic_stack_[(1) - (1)].s))] = '\0';}
    break;

  case 49:

/* Line 690 of lalr1.cc  */
#line 218 "SpParser.yy"
    {(yyval.s) = new char[strlen((yysemantic_stack_[(1) - (1)].s)) + 1]; strcpy((yyval.s), (yysemantic_stack_[(1) - (1)].s)); (yyval.s)[strlen((yysemantic_stack_[(1) - (1)].s))] = '\0';}
    break;

  case 50:

/* Line 690 of lalr1.cc  */
#line 219 "SpParser.yy"
    {(yyval.s) = new char[strlen((yysemantic_stack_[(1) - (1)].s)) + 1]; strcpy((yyval.s), (yysemantic_stack_[(1) - (1)].s)); (yyval.s)[strlen((yysemantic_stack_[(1) - (1)].s))] = '\0';}
    break;

  case 51:

/* Line 690 of lalr1.cc  */
#line 220 "SpParser.yy"
    {(yyval.s) = new char[strlen((yysemantic_stack_[(1) - (1)].s)) + 1]; strcpy((yyval.s), (yysemantic_stack_[(1) - (1)].s)); (yyval.s)[strlen((yysemantic_stack_[(1) - (1)].s))] = '\0';}
    break;

  case 52:

/* Line 690 of lalr1.cc  */
#line 221 "SpParser.yy"
    {(yyval.s) = new char[strlen((yysemantic_stack_[(1) - (1)].s)) + 1]; strcpy((yyval.s), (yysemantic_stack_[(1) - (1)].s)); (yyval.s)[strlen((yysemantic_stack_[(1) - (1)].s))] = '\0';}
    break;

  case 53:

/* Line 690 of lalr1.cc  */
#line 222 "SpParser.yy"
    {(yyval.s) = new char[strlen((yysemantic_stack_[(1) - (1)].s)) + 1]; strcpy((yyval.s), (yysemantic_stack_[(1) - (1)].s)); (yyval.s)[strlen((yysemantic_stack_[(1) - (1)].s))] = '\0';}
    break;

  case 54:

/* Line 690 of lalr1.cc  */
#line 225 "SpParser.yy"
    {(yyval.f) = (yysemantic_stack_[(1) - (1)].f);}
    break;

  case 55:

/* Line 690 of lalr1.cc  */
#line 226 "SpParser.yy"
    {(yyval.f) = (yysemantic_stack_[(1) - (1)].f);}
    break;

  case 56:

/* Line 690 of lalr1.cc  */
#line 227 "SpParser.yy"
    {(yyval.f) = (yysemantic_stack_[(1) - (1)].n);}
    break;



/* Line 690 of lalr1.cc  */
#line 693 "./SpParser.cpp"
	default:
          break;
      }
    /* User semantic actions sometimes alter yychar, and that requires
       that yytoken be updated with the new translation.  We take the
       approach of translating immediately before every use of yytoken.
       One alternative is translating here after every semantic action,
       but that translation would be missed if the semantic action
       invokes YYABORT, YYACCEPT, or YYERROR immediately after altering
       yychar.  In the case of YYABORT or YYACCEPT, an incorrect
       destructor might then be invoked immediately.  In the case of
       YYERROR, subsequent parser actions might lead to an incorrect
       destructor call or verbose syntax error message before the
       lookahead is translated.  */
    YY_SYMBOL_PRINT ("-> $$ =", yyr1_[yyn], &yyval, &yyloc);

    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();

    yysemantic_stack_.push (yyval);
    yylocation_stack_.push (yyloc);

    /* Shift the result of the reduction.  */
    yyn = yyr1_[yyn];
    yystate = yypgoto_[yyn - yyntokens_] + yystate_stack_[0];
    if (0 <= yystate && yystate <= yylast_
	&& yycheck_[yystate] == yystate_stack_[0])
      yystate = yytable_[yystate];
    else
      yystate = yydefgoto_[yyn - yyntokens_];
    goto yynewstate;

  /*------------------------------------.
  | yyerrlab -- here on detecting error |
  `------------------------------------*/
  yyerrlab:
    /* Make sure we have latest lookahead translation.  See comments at
       user semantic actions for why this is necessary.  */
    yytoken = yytranslate_ (yychar);

    /* If not already recovering from an error, report this error.  */
    if (!yyerrstatus_)
      {
	++yynerrs_;
	if (yychar == yyempty_)
	  yytoken = yyempty_;
	error (yylloc, yysyntax_error_ (yystate, yytoken));
      }

    yyerror_range[1] = yylloc;
    if (yyerrstatus_ == 3)
      {
	/* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

	if (yychar <= yyeof_)
	  {
	  /* Return failure if at end of input.  */
	  if (yychar == yyeof_)
	    YYABORT;
	  }
	else
	  {
	    yydestruct_ ("Error: discarding", yytoken, &yylval, &yylloc);
	    yychar = yyempty_;
	  }
      }

    /* Else will try to reuse lookahead token after shifting the error
       token.  */
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;

    yyerror_range[1] = yylocation_stack_[yylen - 1];
    /* Do not reclaim the symbols of the rule which action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    yystate = yystate_stack_[0];
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;	/* Each real token shifted decrements this.  */

    for (;;)
      {
	yyn = yypact_[yystate];
	if (!yy_pact_value_is_default_ (yyn))
	{
	  yyn += yyterror_;
	  if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
	    {
	      yyn = yytable_[yyn];
	      if (0 < yyn)
		break;
	    }
	}

	/* Pop the current state because it cannot handle the error token.  */
	if (yystate_stack_.height () == 1)
	YYABORT;

	yyerror_range[1] = yylocation_stack_[0];
	yydestruct_ ("Error: popping",
		     yystos_[yystate],
		     &yysemantic_stack_[0], &yylocation_stack_[0]);
	yypop_ ();
	yystate = yystate_stack_[0];
	YY_STACK_PRINT ();
      }

    yyerror_range[2] = yylloc;
    // Using YYLLOC is tempting, but would change the location of
    // the lookahead.  YYLOC is available though.
    YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yyloc);

    /* Shift the error token.  */
    YY_SYMBOL_PRINT ("Shifting", yystos_[yyn],
		     &yysemantic_stack_[0], &yylocation_stack_[0]);

    yystate = yyn;
    goto yynewstate;

    /* Accept.  */
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    /* Abort.  */
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (yychar != yyempty_)
      {
        /* Make sure we have latest lookahead translation.  See comments
           at user semantic actions for why this is necessary.  */
        yytoken = yytranslate_ (yychar);
        yydestruct_ ("Cleanup: discarding lookahead", yytoken, &yylval,
                     &yylloc);
      }

    /* Do not reclaim the symbols of the rule which action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (yystate_stack_.height () != 1)
      {
	yydestruct_ ("Cleanup: popping",
		   yystos_[yystate_stack_[0]],
		   &yysemantic_stack_[0],
		   &yylocation_stack_[0]);
	yypop_ ();
      }

    return yyresult;
  }

  // Generate an error message.
  std::string
  SpParser::yysyntax_error_ (int, int)
  {
    return YY_("syntax error");
  }


  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
  const signed char SpParser::yypact_ninf_ = -9;
  const short int
  SpParser::yypact_[] =
  {
       113,    -8,   131,   131,   131,   131,   131,   131,   131,   131,
     131,   131,   131,   131,   131,    -9,    14,    11,    -9,    -6,
      -9,    -9,    -9,    -9,    -9,    -9,    -9,    -9,    -9,    -9,
      -9,    -9,    -9,    -9,    -9,    -9,    -9,    -9,    -9,    -9,
      -9,    -9,    -9,    -9,    -9,    -9,    -9,    -9,    -9,   131,
      -9,   131,   131,   131,   131,   131,   131,   131,   131,   131,
     131,   131,   131,    -9,    -5,     9,    -9,    -9,    42,    42,
      42,    42,    42,   131,   131,   131,   131,   131,    -9,    42,
     131,    -9,    -9,    -9,    -9,    -9,    -9,    42,    42,    -9,
      -9,   131,    42,    42,   131,   131,    -9,   131,    -9,    -9,
      42,    -9,    -9,    42,    -9,    42,    -9,    -9,    42,    -9
  };

  /* YYDEFACT[S] -- default reduction number in state S.  Performed when
     YYTABLE doesn't specify something else to do.  Zero means the
     default is an error.  */
  const unsigned char
  SpParser::yydefact_[] =
  {
         0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     9,     0,     0,     6,     0,
      10,    11,    12,    14,    13,    15,    16,    17,    18,    19,
      20,    21,    22,     8,    40,    39,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,     0,
      38,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     1,     0,     2,     5,     7,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    35,     0,
       0,     4,     3,    55,    56,    54,    23,    24,    26,    29,
      28,     0,     0,     0,     0,     0,    36,     0,    25,    27,
       0,    31,    32,     0,    34,     0,    30,    33,     0,    37
  };

  /* YYPGOTO[NTERM-NUM].  */
  const signed char
  SpParser::yypgoto_[] =
  {
        -9,    -9,    -9,    -9,    16,    -9,    -9,    -9,    -9,    -9,
      -9,    -9,    -9,    -9,    -9,    -9,    -9,    -9,    -9,    -3,
      -9,    10
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const signed char
  SpParser::yydefgoto_[] =
  {
        -1,    16,    65,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    49,
      50,    86
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If YYTABLE_NINF_, syntax error.  */
  const signed char SpParser::yytable_ninf_ = -1;
  const unsigned char
  SpParser::yytable_[] =
  {
        51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,     1,    33,    63,    67,    81,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      82,    64,    15,    66,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    83,    68,    84,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
       0,    85,     0,     0,     0,     0,     0,     0,     0,     0,
      91,    92,    93,    94,    95,     0,     0,    97,     0,    87,
      88,    89,    90,     0,     0,     0,     0,     0,   100,    96,
       0,   103,   104,     0,   105,     0,     0,    98,    99,     0,
       0,     0,   101,   102,     0,     0,     0,     0,     0,     0,
     106,     0,     0,   107,     1,   108,     0,     0,   109,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,     0,     0,    15,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48
  };

  /* YYCHECK.  */
  const signed char
  SpParser::yycheck_[] =
  {
         3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,     1,    21,     0,    21,    21,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      21,    20,    21,    17,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     3,    49,     5,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      -1,    19,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      73,    74,    75,    76,    77,    -1,    -1,    80,    -1,    69,
      70,    71,    72,    -1,    -1,    -1,    -1,    -1,    91,    79,
      -1,    94,    95,    -1,    97,    -1,    -1,    87,    88,    -1,
      -1,    -1,    92,    93,    -1,    -1,    -1,    -1,    -1,    -1,
     100,    -1,    -1,   103,     1,   105,    -1,    -1,   108,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    -1,    -1,    21,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  SpParser::yystos_[] =
  {
         0,     1,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    21,    23,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    21,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    41,
      42,    41,    41,    41,    41,    41,    41,    41,    41,    41,
      41,    41,    41,     0,    20,    24,    26,    21,    41,    41,
      41,    41,    41,    41,    41,    41,    41,    41,    41,    41,
      41,    21,    21,     3,     5,    19,    43,    43,    43,    43,
      43,    41,    41,    41,    41,    41,    43,    41,    43,    43,
      41,    43,    43,    41,    41,    41,    43,    43,    43,    43
  };

#if YYDEBUG
  /* TOKEN_NUMBER_[YYLEX-NUM] -- Internal symbol number corresponding
     to YYLEX-NUM.  */
  const unsigned short int
  SpParser::yytoken_number_[] =
  {
         0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  const unsigned char
  SpParser::yyr1_[] =
  {
         0,    22,    23,    24,    24,    25,    25,    26,    26,    26,
      27,    27,    27,    27,    27,    27,    27,    27,    27,    27,
      27,    27,    27,    28,    29,    29,    30,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    41,
      42,    42,    42,    42,    42,    42,    42,    42,    42,    42,
      42,    42,    42,    42,    43,    43,    43
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  SpParser::yyr2_[] =
  {
         0,     2,     2,     2,     2,     2,     1,     2,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     4,     4,     5,     4,     5,     4,     4,
       6,     5,     5,     6,     5,     3,     4,     7,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1
  };

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
  /* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
     First, the terminals, then, starting at \a yyntokens_, nonterminals.  */
  const char*
  const SpParser::yytname_[] =
  {
    "$end", "error", "$undefined", "FLOAT", "STRING", "INTEGER", "RESISTOR",
  "CAPACITOR", "INDUCTOR", "CURRENTSRC", "VOLTAGESRC", "VCCS", "CCCS",
  "CCVS", "VCVS", "OPAMP", "SWITCH", "DIODE", "MOS", "VALUE", "END", "EOL",
  "$accept", "spice", "end", "netlist", "line", "component", "resistor",
  "capacitor", "inductor", "voltagesrc", "currentsrc", "vccs", "cccs",
  "ccvs", "vcvs", "opamp", "switch_on_off", "diode", "mos", "node",
  "variable", "value", 0
  };
#endif

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const SpParser::rhs_number_type
  SpParser::yyrhs_[] =
  {
        23,     0,    -1,    25,    24,    -1,    24,    21,    -1,    20,
      21,    -1,    25,    26,    -1,    26,    -1,    27,    21,    -1,
       1,    21,    -1,    21,    -1,    28,    -1,    29,    -1,    30,
      -1,    32,    -1,    31,    -1,    33,    -1,    34,    -1,    35,
      -1,    36,    -1,    37,    -1,    38,    -1,    39,    -1,    40,
      -1,     6,    41,    41,    43,    -1,     7,    41,    41,    43,
      -1,     7,    41,    41,    43,    43,    -1,     8,    41,    41,
      43,    -1,     8,    41,    41,    43,    43,    -1,    10,    41,
      41,    43,    -1,     9,    41,    41,    43,    -1,    11,    41,
      41,    41,    41,    43,    -1,    12,    41,    41,    41,    43,
      -1,    13,    41,    41,    41,    43,    -1,    14,    41,    41,
      41,    41,    43,    -1,    15,    41,    41,    41,    41,    -1,
      16,    41,    41,    -1,    17,    41,    41,    43,    -1,    18,
      41,    41,    41,    41,    43,    43,    -1,    42,    -1,     5,
      -1,     4,    -1,     6,    -1,     7,    -1,     8,    -1,     9,
      -1,    10,    -1,    11,    -1,    12,    -1,    13,    -1,    14,
      -1,    15,    -1,    16,    -1,    17,    -1,    18,    -1,    19,
      -1,     3,    -1,     5,    -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned char
  SpParser::yyprhs_[] =
  {
         0,     0,     3,     6,     9,    12,    15,    17,    20,    23,
      25,    27,    29,    31,    33,    35,    37,    39,    41,    43,
      45,    47,    49,    51,    56,    61,    67,    72,    78,    83,
      88,    95,   101,   107,   114,   120,   124,   129,   137,   139,
     141,   143,   145,   147,   149,   151,   153,   155,   157,   159,
     161,   163,   165,   167,   169,   171,   173
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned char
  SpParser::yyrline_[] =
  {
         0,    73,    73,    76,    77,    80,    81,    84,    85,    86,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   105,   111,   115,   121,   125,   132,   138,
     144,   149,   158,   167,   172,   177,   182,   187,   192,   199,
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   225,   226,   227
  };

  // Print the state stack on the debug stream.
  void
  SpParser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (state_stack_type::const_iterator i = yystate_stack_.begin ();
	 i != yystate_stack_.end (); ++i)
      *yycdebug_ << ' ' << *i;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  SpParser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    /* Print the symbols being reduced, and their result.  */
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
	       << " (line " << yylno << "):" << std::endl;
    /* The symbols being reduced.  */
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
		       yyrhs_[yyprhs_[yyrule] + yyi],
		       &(yysemantic_stack_[(yynrhs) - (yyi + 1)]),
		       &(yylocation_stack_[(yynrhs) - (yyi + 1)]));
  }
#endif // YYDEBUG

  /* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
  SpParser::token_number_type
  SpParser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
           0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21
    };
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int SpParser::yyeof_ = 0;
  const int SpParser::yylast_ = 149;
  const int SpParser::yynnts_ = 22;
  const int SpParser::yyempty_ = -2;
  const int SpParser::yyfinal_ = 63;
  const int SpParser::yyterror_ = 1;
  const int SpParser::yyerrcode_ = 256;
  const int SpParser::yyntokens_ = 22;

  const unsigned int SpParser::yyuser_token_number_max_ = 276;
  const SpParser::token_number_type SpParser::yyundef_token_ = 2;


} // yy

/* Line 1136 of lalr1.cc  */
#line 1186 "./SpParser.cpp"


/* Line 1138 of lalr1.cc  */
#line 230 "SpParser.yy"


void yy::SpParser::error(const location &loc, const string &s) 
{
	cerr << "error at " << loc << ": " << s << endl;
}

