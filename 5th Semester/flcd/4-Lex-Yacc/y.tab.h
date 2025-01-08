/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INTEGER_CONSTANT = 258,
     FLOAT_CONSTANT = 259,
     STRING_CONSTANT = 260,
     IDENTIFIER = 261,
     IF = 262,
     ELSE = 263,
     WHILE = 264,
     READ = 265,
     WRITE = 266,
     INT = 267,
     FLOAT = 268,
     STRING = 269,
     CHAR = 270,
     ARRAY = 271,
     OF = 272,
     LPAREN = 273,
     RPAREN = 274,
     LBRACE = 275,
     RBRACE = 276,
     LBRACKET = 277,
     RBRACKET = 278,
     SEMICOLON = 279,
     COMMA = 280,
     ASSIGN = 281,
     PLUS = 282,
     MINUS = 283,
     MULTIPLY = 284,
     DIVIDE = 285,
     MODULO = 286,
     EQUALS = 287,
     NOTEQUAL = 288,
     LT = 289,
     GT = 290,
     LTE = 291,
     GTE = 292,
     AND = 293,
     OR = 294
   };
#endif
/* Tokens.  */
#define INTEGER_CONSTANT 258
#define FLOAT_CONSTANT 259
#define STRING_CONSTANT 260
#define IDENTIFIER 261
#define IF 262
#define ELSE 263
#define WHILE 264
#define READ 265
#define WRITE 266
#define INT 267
#define FLOAT 268
#define STRING 269
#define CHAR 270
#define ARRAY 271
#define OF 272
#define LPAREN 273
#define RPAREN 274
#define LBRACE 275
#define RBRACE 276
#define LBRACKET 277
#define RBRACKET 278
#define SEMICOLON 279
#define COMMA 280
#define ASSIGN 281
#define PLUS 282
#define MINUS 283
#define MULTIPLY 284
#define DIVIDE 285
#define MODULO 286
#define EQUALS 287
#define NOTEQUAL 288
#define LT 289
#define GT 290
#define LTE 291
#define GTE 292
#define AND 293
#define OR 294




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 49 "lang.y"
{
    struct row_entry* row;
    int int_val;
    float float_val;
    char* str_val;
}
/* Line 1529 of yacc.c.  */
#line 134 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

