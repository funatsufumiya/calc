#line 1 "/usr/local/lib/kmyacc.c.parser"
/* -*-c-*-  Prototype file of KM-yacc parser for C.
 *
 * Written by MORI Koichiro
 *
 * This file is PUBLIC DOMAIN.
 */


#line 3 "calc.y"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <regex.h>
#include <stdarg.h>

// #define DEBUG

#define true 1
#define false 0
#define arrlen(arr) sizeof(arr) / sizeof(arr[0])

int yyparse();

typedef int bool;

typedef struct {
    char *key;
    double value;
} dTuple;

typedef struct {
    char *name;
    double(*func)(double*, size_t);
} fTuple;

double retVal = 0.0;
int argSize = 0;

double* arrcpy(double *to, double *from){
  size_t n = arrlen(from);
  int i;
  for (i = 0; i < n; ++i){
    to[i] = from[i];
  }
  return to;
}

#line 14 "/usr/local/lib/kmyacc.c.parser"

#line 20 "/usr/local/lib/kmyacc.c.parser"

#line 24 "/usr/local/lib/kmyacc.c.parser"

/* declarations */
#line 28 "/usr/local/lib/kmyacc.c.parser"
typedef union
{
  int intval;
  char* strval;
  double dblval;
  double* dblarrval;
}
#line 30 "/usr/local/lib/kmyacc.c.parser"
YYSTYPE;
#line 38 "/usr/local/lib/kmyacc.c.parser"
extern YYSTYPE yylval;

#define YYERRTOK 256
#define NUM 257
#define ID 258
#line 44 "/usr/local/lib/kmyacc.c.parser"

/* -p option */
#line 53 "/usr/local/lib/kmyacc.c.parser"


#ifndef YYMAXDEPTH
# define YYMAXDEPTH 512
#endif /* !YYMAXDEPTH */

#ifndef YYASP
# define YYASP(n) yyasp[n]
#endif /* !YYASP */

#define yyclearin (yychar = -1)
#define yyerrok (yyerrflag = 0)
#define YYRECOVERING (yyerrflag != 0)

#define YYACCEPT  return (0)
#define YYABORT  return (1)
#define YYERROR  goto yyerrlab




#if YYDEBUG
int yydebug;
#endif /* YYDEBUG */

#if 0
int yylex();
int yyerror();
#endif

#if !YYPURE
int yychar;
YYSTYPE yylval;
#endif


/* code after %% in *.y */
#line 100 "calc.y"

// Defined Functions =======================

double __abs(double* a, size_t c){ return abs(a[0]); };
double __sin(double* a, size_t c){ return sin(a[0]); };
double __cos(double* a, size_t c){ return cos(a[0]); };
double __tan(double* a, size_t c){ return tan(a[0]); };
double __asin(double* a, size_t c){ return asin(a[0]); };
double __acos(double* a, size_t c){ return acos(a[0]); };
double __atan(double* a, size_t c){ return atan(a[0]); };
double __atan2(double* a, size_t c){ return atan2(a[0],a[1]); };
double __max(double* a, size_t c){
  int i, v;
  for (i = 0; i < c; ++i){
    if(i == 0){
      v = a[i]; continue;
    }else{
      if(a[i] < a[i-1]){ v = a[i-1];
      }else{ v = a[i]; }
    }
  }
  return v;
};
double __min(double* a, size_t c){
  int v, i;
  for (i = 0; i < c; ++i){
    if(i == 0){
      v = a[i]; continue;
    }else{
      if(a[i] < a[i-1]){ v = a[i];
      }else{ v = a[i-1]; }
    }
  }
  return v;
};
double __sq(double* a, size_t c){ return a[0] * a[0]; };
double __sqrt(double* a, size_t c){ return sqrt(a[0]); };
double __cbrt(double* a, size_t c){ return pow(a[0], 1/3); };
double __pow(double* a, size_t c){ return pow(a[0],a[1]); };
double __floor(double* a, size_t c){ return floor(a[0]); };
double __ceil(double* a, size_t c){ return ceil(a[0]); };
double __round(double* a, size_t c){ return round(a[0]); };
double __random(double* a, size_t c){ return random(); };
double __exp(double* a, size_t c){ return exp(a[0]); };
double __log(double* a, size_t c){ return log(a[0]); };
double __log2(double* a, size_t c){ return log(a[0])/log(2); };
double __log10(double* a, size_t c){ return log(a[0])/log(10); };
double __logN(double* a, size_t c){ return log(a[0])/log(a[1]); };

// End of Defined Functions =======================

int pos = 0;
char* buffer = NULL;
char* numRegexStr = "^(0|[1-9][0-9]*|0[.][0-9]*|[1-9][0-9]*[.][0-9]*|[.][0-9]*)$";
char* idRegexStr = "^[a-zA-Z0-9_]+$";
regex_t numRegex;
regex_t idRegex;

fTuple definedFuncs[] = {
  {"abs", __abs},
  {"sin", __sin},
  {"cos", __cos},
  {"tan", __tan},
  {"asin", __asin},
  {"acos", __acos},
  {"atan", __atan},
  {"atan2", __atan2},
  {"log", __log},
  {"max", __max},
  {"min", __min},
  {"sq", __sq},
  {"sqrt", __sqrt},
  {"cbrt", __cbrt},
  {"pow", __pow},
  {"floor", __floor},
  {"ceil", __ceil},
  {"round", __round},
  {"random", __random},
  {"exp", __exp},
  {"log", __log},
  {"log2", __log2},
  {"log10", __log10},
  {"logN", __logN}
};

dTuple definedConsts[] = {
  {"PI", 3.141592653589793},
  {"TWO_PI", 6.283185307179586},
  {"HALF_PI", 1.5707963267948966},
  {"E", 2.718281828459045},
  {"LN2", 0.6931471805599453},
  {"LN10", 2.302585092994046},
  {"LOG2E", 1.4426950408889634},
  {"LOG10E", 0.4342944819032518}
};

void yyerror(char *msg){
  char str[200];
  sprintf(str, "[ERROR] %s", msg);
  fputs(str, stderr);
}

int getDefinedFuncId(char *name){
  size_t n = arrlen(definedFuncs);
  int i;
  for (i = 0; i < n; ++i){
    if(strcmp(definedFuncs[i].name, name) == 0){
      return i;
    }
  }
  return -1;
}

double callDefinedFunc(char *name, size_t argc, double *argv){
  int id = getDefinedFuncId(name);
  return definedFuncs[id].func(argv, argc);
}

bool isFuncExists(char *name){
  return getDefinedFuncId(name) > -1;
}

double getConst(char *name){
  size_t n = arrlen(definedConsts);
  int i;
  for (i = 0; i < n; ++i){
    if(strcmp(definedConsts[i].key, name) == 0){
      return definedConsts[i].value;
    }
  }
  return 0xDEADBEEF; // never comes here
}

bool isConstExists(char *name){
  size_t n = arrlen(definedConsts);
  int i;
  for (i = 0; i < n; ++i){
    if(strcmp(definedConsts[i].key, name) == 0){
      return true;
    }
  }
  return false;
}

bool isNumber(char* s){
  regmatch_t match[1];
  return regexec( &numRegex, s, 1, match, 0 ) == 0;
}

bool isIdentifier(char* s){
  regmatch_t match[1];
  return regexec( &idRegex, s, 1, match, 0 ) == 0;
}

bool isBlank(char c){
  return (c == ' ' || c == '\n' || c == '\t');
}

int yylex(){
  #ifdef DEBUG
  printf("lex: (buffer:\"%s\", pos:%d)\n",buffer,pos);
  #endif

  if(pos == strlen(buffer)){
    #ifdef DEBUG
    printf("  EOF\n\n");
    #endif
    return 0;
  }

  char c = buffer[pos];

  if(isBlank(c)){
    while(true){
      #ifdef DEBUG
      printf("  BLANK\n");
      #endif

      if(pos != strlen(buffer)-1 && isBlank(buffer[pos+1])){
        ++pos;
        continue; // skip
      }else{
        ++pos;
        break; // skip
      }
    }

    c = buffer[pos];
  }

  if(pos == strlen(buffer)){
    #ifdef DEBUG
    printf("  EOF\n\n");
    #endif
    return 0;
  }

  char s[2] = {c,0};

  #ifdef DEBUG
  printf("  c = %c\n",c);
  #endif

  if(isNumber(s)){
    #ifdef DEBUG
    printf("  isNumber:\n");
    #endif

    char numStr[100] = {c,0};
    char tmp[100];
    while(true){
      #ifdef DEBUG
      printf("  numStr = %s\n",numStr);
      #endif
      if(pos != strlen(buffer)-1){
        s[0] = buffer[pos+1];
        s[1] = 0;
        sprintf(tmp, "%s%s", numStr, s);
      }
      if(pos != strlen(buffer)-1 && isNumber(tmp)){
        strcpy(numStr, tmp);
        ++pos;
      }else{
        yylval.intval = atoi(numStr);
        ++pos;

        #ifdef DEBUG
        printf("  return NUM %s\n",numStr);
        #endif

        return NUM;
      }
    }
  }else if(isIdentifier(s)){
    #ifdef DEBUG
    printf("  isIdentifier:\n");
    #endif

    char idStr[100] = {c,0};
    char tmp[100];
    while(true){
      if(pos != strlen(buffer)-1){
        s[0] = buffer[pos+1];
        s[1] = 0;
        sprintf(tmp, "%s%s", idStr, s);
      }

      if(pos != strlen(buffer)-1 && isIdentifier(tmp)){
        strcpy(idStr, tmp);
        ++pos;
      }else{
        yylval.strval = strdup(idStr);
        ++pos;

        #ifdef DEBUG
        printf("  return ID %c\n",c);
        #endif

        return ID;
      }
    }
  }else{

    #ifdef DEBUG
    printf("  return ELSE %c\n",buffer[pos]);
    #endif

    return buffer[pos++];
  }
}

double calc(char* s){
  #ifdef DEBUG
  printf("\nparse(\"%s\")\n\n", s);
  #endif

  regcomp( &numRegex, numRegexStr, REG_EXTENDED );
  regcomp( &idRegex, idRegexStr, REG_EXTENDED );

  pos = 0;
  buffer = s;
  yyparse();

  regfree( &numRegex );
  regfree( &idRegex );

  return retVal;
}


int main(int argc, char const *argv[])
{
  if(argc == 1){
    printf("\nusage: calc [expression]\n\n");
    exit(1);
  }else{
    double val = calc(argv[1]);
    printf("%f\n",val);
  }
  return 0;
}
#line 91 "/usr/local/lib/kmyacc.c.parser"


#if !YYDEBUG

#define YYTRACE_DCL
#define YYTRACE_NEWSTATE(st, tok)
#define YYTRACE_READ(tok)
#define YYTRACE_SHIFT(tok)
#define YYTRACE_ACCEPT()
#define YYTRACE_REDUCE(n)
#define YYTRACE_POP(st)
#define YYTRACE_DISCARD(tok)

#endif /* !YYDEBUG */


#if YYDEBUG

#ifndef EOF
#include <stdio.h>
#endif

#ifndef YYTRACEF
#define YYTRACEF stderr
#endif /* !YYTRACEF */

static char *yyterminals[] = {
  "$EOF",
  "error",
  "NUM",
  "ID",
  "'+'",
  "'-'",
  "'*'",
  "'/'",
  "'^'",
  "'('",
  "')'",
  "','"
#line 119 "/usr/local/lib/kmyacc.c.parser"
  , "???"
};

static char *yyproduction[] = {
  "$start : line",
  "line : expr",
  "expr : expr '+' expr",
  "expr : expr '-' expr",
  "expr : expr '*' expr",
  "expr : expr '/' expr",
  "expr : expr '^' expr",
  "expr : funcall",
  "expr : '(' expr ')'",
  "expr : '-' expr",
  "expr : '+' expr",
  "expr : NUM",
  "expr : ID",
  "funcall : ID '(' args ')'",
  "args : /* empty */",
  "args : args ',' expr",
  "args : expr"
#line 124 "/usr/local/lib/kmyacc.c.parser"
};

/* Traditional Debug Mode */

#define YYTRACE_DCL /* empty */

#define YYTRACE_NEWSTATE(st, tok) \
    if (yydebug) \
	fprintf(YYTRACEF, "%%%% State %d, Lookahead %s\n", \
		st, tok < 0 ? "--none--" : yyterminals[tok])

#define YYTRACE_READ(tok) \
    if (yydebug) \
	fprintf(YYTRACEF, "%%%% Reading %s\n", yyterminals[tok])

#define YYTRACE_SHIFT(tok) \
    if (yydebug) \
	fprintf(YYTRACEF, "%%%% Shift %s\n", yyterminals[tok])

#define YYTRACE_ACCEPT() \
    if (yydebug) fprintf(YYTRACEF, "%%%% Accepted.\n")

#define YYTRACE_REDUCE(n) \
    if (yydebug) \
	fprintf(YYTRACEF, "%%%% Reduce by (%d) %s\n", \
		n, yyproduction[n])

#define YYTRACE_POP(st) \
    if (yydebug) \
	fprintf(YYTRACEF, "%%%% Recovering, uncovers state %d\n", \
		st)

#define YYTRACE_DISCARD(tok) \
    if (yydebug) fprintf(YYTRACEF, "%%%% Discard %s\n", yyterminals[tok])

#endif /* YYDEBUG */



static char yytranslate[] = {
    0,   12,   12,   12,   12,   12,   12,   12,   12,   12,
   12,   12,   12,   12,   12,   12,   12,   12,   12,   12,
   12,   12,   12,   12,   12,   12,   12,   12,   12,   12,
   12,   12,   12,   12,   12,   12,   12,   12,   12,   12,
    9,   10,    6,    4,   11,    5,   12,    7,   12,   12,
   12,   12,   12,   12,   12,   12,   12,   12,   12,   12,
   12,   12,   12,   12,   12,   12,   12,   12,   12,   12,
   12,   12,   12,   12,   12,   12,   12,   12,   12,   12,
   12,   12,   12,   12,   12,   12,   12,   12,   12,   12,
   12,   12,   12,   12,    8,   12,   12,   12,   12,   12,
   12,   12,   12,   12,   12,   12,   12,   12,   12,   12,
   12,   12,   12,   12,   12,   12,   12,   12,   12,   12,
   12,   12,   12,   12,   12,   12,   12,   12,   12,   12,
   12,   12,   12,   12,   12,   12,   12,   12,   12,   12,
   12,   12,   12,   12,   12,   12,   12,   12,   12,   12,
   12,   12,   12,   12,   12,   12,   12,   12,   12,   12,
   12,   12,   12,   12,   12,   12,   12,   12,   12,   12,
   12,   12,   12,   12,   12,   12,   12,   12,   12,   12,
   12,   12,   12,   12,   12,   12,   12,   12,   12,   12,
   12,   12,   12,   12,   12,   12,   12,   12,   12,   12,
   12,   12,   12,   12,   12,   12,   12,   12,   12,   12,
   12,   12,   12,   12,   12,   12,   12,   12,   12,   12,
   12,   12,   12,   12,   12,   12,   12,   12,   12,   12,
   12,   12,   12,   12,   12,   12,   12,   12,   12,   12,
   12,   12,   12,   12,   12,   12,   12,   12,   12,   12,
   12,   12,   12,   12,   12,   12,    1,    2,    3
#line 165 "/usr/local/lib/kmyacc.c.parser"
};

#define YYBADCH 12
#define YYMAXLEX 259
#define YYTERMS 12
#define YYNONTERMS 5

static short yyaction[] = {
   35,   20,    3,    4,   10,    6,    7,    5,    8,    9,
   10,   32,    6,    7,   37,   11,    0,    0,    2
#line 174 "/usr/local/lib/kmyacc.c.parser"
};
#define YYLAST 19

static char yycheck[] = {
    2,    3,    4,    5,    8,    4,    5,    9,    6,    7,
    8,   10,    4,    5,   10,   11,    0,   -1,    9
#line 179 "/usr/local/lib/kmyacc.c.parser"
};

static short yybase[] = {
   -2,    1,   -2,   -2,   -2,   -2,   -2,   -2,   -2,   -2,
   -2,   -2,    8,    8,    8,    2,    2,    2,    2,    4,
    9,   16,   -4,   -4,    0,    2,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    2,    2,    2
#line 183 "/usr/local/lib/kmyacc.c.parser"
};
#define YY2TBLSTATE 15

static short yydefault[] = {
32767,32767,   14,32767,32767,32767,32767,32767,32767,32767,
32767,32767,    1,   16,   15,   10,    9,    2,    3,32767,
   12,32767,    4,    5
#line 188 "/usr/local/lib/kmyacc.c.parser"
};

static short yygoto[] = {
   13,   15,   16,    1,   17,   18,   22,   23,   30,   14
#line 192 "/usr/local/lib/kmyacc.c.parser"
};
#define YYGLAST 10

static char yygcheck[] = {
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1
#line 197 "/usr/local/lib/kmyacc.c.parser"
};

static short yygbase[] = {
    0,   -2,    0,    0,    0
#line 201 "/usr/local/lib/kmyacc.c.parser"
};

static short yygdefault[] = {
-32768,   12,   31,   19,   21
#line 205 "/usr/local/lib/kmyacc.c.parser"
};

static char yylhs[] = {
    0,    4,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    2,    3,    3,    3
#line 209 "/usr/local/lib/kmyacc.c.parser"
};

static char yylen[] = {
    1,    1,    3,    3,    3,    3,    3,    1,    3,    2,
    2,    1,    1,    4,    0,    3,    1
#line 213 "/usr/local/lib/kmyacc.c.parser"
};

#line 235 "/usr/local/lib/kmyacc.c.parser"

#define YYSTATES 29
#define YYNLSTATES 24
#define YYINTERRTOK 1
#define YYUNEXPECTED 32767
#define YYDEFAULT -32766


/*
 * Seek (st,ch) in action table, return true if found.
 * param n position in yyaction
 * param st current state
 * param ch input token
 */
#if YYPROBEONCE
#define found_in_action(n, st, ch) \
  ((unsigned)(n = yybase[st] + (ch)) < YYLAST && yycheck[n] == (ch))
#endif /* YYPROBEONCE */

#if !YYPROBEONCE
#define found_in_action(n, st, ch) \
  (((unsigned)(n = yybase[st] + (ch)) < YYLAST && yycheck[n] == (ch)) \
   || ((st) < YY2TBLSTATE \
       && (unsigned)(n = yybase[(st) + YYNLSTATES] + (ch)) < YYLAST \
       && yycheck[n] == (ch)))
#endif /* !YYPROBEONCE */

#define found_in_goto(n, st, ch) \
  ((unsigned)(n = yygbase[ch] + (st)) < YYGLAST && yygcheck[n] == (ch))


/*
 * Lexical analyzer interface
 */
#if YYPURE
#  ifdef YYLEX_PARAM
#    define YYLEX() yylex(&yylval, YYLEX_PARAM)
#  else
#    define YYLEX() yylex(&yylval)
#  endif /* YYLEX_PARAM */
#else
#  define YYLEX() yylex()
#endif /* YYPURE */


/*
 * Parser entry point
 */
#ifdef YYPARSE_PARAM
#  if __STDC__
#    define YYPARSE_ARG void *YYPARSE_PARAM
#    define YYPARSE_DECL
#  else
#    define YYPARSE_ARG YYPARSE_PARAM
#    define YYPARSE_DECL void *YYPARSE_PARAM;
#  endif /* __STDC__ */
#else
# define YYPARSE_ARG
# define YYPARSE_DECL
#endif /* YYPARSE_PARAM */

int yyparse(YYPARSE_ARG)
  YYPARSE_DECL
{
  YYSTYPE yyastk[YYMAXDEPTH];
  short yysstk[YYMAXDEPTH];
  short *yyssp;
  int yystate;
  int yyn;
  int yyp;
  int yyl;
  int yychar1;
#if YYPURE
  int yychar;
  YYSTYPE yylval;
#endif /* YYPURE */
  int yyerrflag;
  YYSTYPE *yyasp;
#ifndef YYACTFUN
  YYSTYPE yyval;
#endif /* !YYACTFUN */
  YYTRACE_DCL

  yyssp = yysstk;
  yyasp = yyastk - 1;
  *yyssp = yystate = 0;
  yychar1 = yychar = -1;
  yyerrflag = 0;
  for (;;) {
    YYTRACE_NEWSTATE(yystate, yychar1);

    if (yybase[yystate] == 0)
      yyn = yydefault[yystate];
    else {
      if (yychar < 0) {
        if ((yychar = YYLEX()) <= 0) yychar = 0;
        yychar1 = yychar < YYMAXLEX ? yytranslate[yychar] : YYBADCH;
        YYTRACE_READ(yychar1);
      }
      
      if (found_in_action(yyn, yystate, yychar1)
          && (yyn = yyaction[yyn]) != YYDEFAULT) {
        /*
         * >= YYNLSTATE: shift and reduce
         * > 0: shift
         * = 0: accept
         * < 0: reduce
         * = -YYUNEXPECTED: error
         */
        if (yyn > 0) {
          /* shift */
          YYTRACE_SHIFT(yychar1);
          if (yyssp >= yysstk + YYMAXDEPTH) {
            yyerror("parser stack overflow");
            YYABORT;
          }
          *++yyssp = yystate = yyn;
          *++yyasp = yylval;
          yychar1 = yychar = -1;

          if (yyerrflag > 0)
            yyerrflag--;
          if (yyn < YYNLSTATES)
            continue;

          /* yyn >= YYNLSTATES means shift-and-reduce */
          yyn -= YYNLSTATES;
        } else
          yyn = -yyn;
      } else
        yyn = yydefault[yystate];
    }

    for (;;) {
      /* reduce/error */
      if (yyn == 0) {
        /* accept */
        YYTRACE_ACCEPT();
        YYACCEPT;
      }
      else if (yyn != YYUNEXPECTED) {
        /* reduce */
        yyl = yylen[yyn];
        yyval = yyasp[1-yyl];
        YYTRACE_REDUCE(yyn);
#line 384 "/usr/local/lib/kmyacc.c.parser"
        switch(yyn) {
        case 1:
#line 72 "calc.y"
{ retVal = YYASP(1-1).dblval; } break;
        case 2:
#line 76 "calc.y"
{ yyval.dblval = YYASP(1-3).dblval + YYASP(3-3).dblval; } break;
        case 3:
#line 77 "calc.y"
{ yyval.dblval = YYASP(1-3).dblval - YYASP(3-3).dblval; } break;
        case 4:
#line 78 "calc.y"
{ yyval.dblval = YYASP(1-3).dblval * YYASP(3-3).dblval; } break;
        case 5:
#line 79 "calc.y"
{ yyval.dblval = YYASP(1-3).dblval / YYASP(3-3).dblval; } break;
        case 6:
#line 80 "calc.y"
{ yyval.dblval = pow(YYASP(1-3).dblval,YYASP(3-3).dblval); } break;
        case 7:
#line 81 "calc.y"
{ yyval.dblval = YYASP(1-1).dblval; } break;
        case 8:
#line 82 "calc.y"
{ yyval.dblval = YYASP(2-3).dblval; } break;
        case 9:
#line 83 "calc.y"
{ yyval.dblval = -(YYASP(2-2).dblval); } break;
        case 10:
#line 84 "calc.y"
{ yyval.dblval = +(YYASP(2-2).dblval); } break;
        case 11:
#line 85 "calc.y"
{ yyval.dblval = YYASP(1-1).intval; } break;
        case 12:
#line 86 "calc.y"
{ if(isConstExists(YYASP(1-1).strval)){ yyval.dblval = getConst(YYASP(1-1).strval); }else{ char str[100]; sprintf(str,"Constant '%s' does not exists",YYASP(1-1).strval); yyerror(str); retVal = 0; return 1; }; } break;
        case 13:
#line 90 "calc.y"
{ if(isFuncExists(YYASP(1-4).strval)){ yyval.dblval = callDefinedFunc(YYASP(1-4).strval,argSize,YYASP(3-4).dblarrval); free(YYASP(3-4).dblarrval); }else{ char str[100]; sprintf(str,"Function '%s' does not exists",YYASP(1-4).strval); yyerror(str); retVal = 0; free(YYASP(3-4).dblarrval); return 1; };  } break;
        case 14:
#line 94 "calc.y"
{ double arr[] = {}; yyval.dblarrval = arr; } break;
        case 15:
#line 95 "calc.y"
{ argSize += 1; double* args = (double*)realloc(YYASP(1-3).dblarrval, argSize * sizeof(double)); args[argSize-1] = YYASP(3-3).dblval; yyval.dblarrval = args; } break;
        case 16:
#line 96 "calc.y"
{ double* args = (double*)malloc(sizeof(double)); args[0] = YYASP(1-1).dblval; argSize = 1; yyval.dblarrval = args; } break;
#line 389 "/usr/local/lib/kmyacc.c.parser"
        }
#line 391 "/usr/local/lib/kmyacc.c.parser"

        /* Goto - shift nonterminal */
        yyasp -= yyl;
        yyssp -= yyl;
        yyn = yylhs[yyn];
        if (found_in_goto(yyp, *yyssp, yyn))
          yystate = yygoto[yyp];
        else
          yystate = yygdefault[yyn];

        if (yyssp >= yysstk + YYMAXDEPTH) {
          yyerror("parser stack overflow");
          YYABORT;
        }
        *++yyssp = yystate;
        *++yyasp = yyval;

      }
      else {
        /* error */
        switch (yyerrflag) {
        case 0:
        yyerrlab:
          yyerror("syntax error");
        case 1:
        case 2:
          yyerrflag = 3;
          /* Pop until error-expecting state uncovered */
          while (!found_in_action(yyn, yystate, YYINTERRTOK)) {
            if (yyssp <= yysstk)
              YYABORT;
            yystate = *--yyssp;
            yyasp--;
            YYTRACE_POP(yystate);
          }
          yyn = yyaction[yyn];
          YYTRACE_SHIFT(YYINTERRTOK);
          *++yyssp = yystate = yyn;
          ++yyasp;
          break;

        case 3:
          YYTRACE_DISCARD(yychar1);
          if (yychar == 0)
            YYABORT;
          yychar1 = yychar = -1;
          break;
        }
      }

      if (yystate < YYNLSTATES)
        break;
      /* >= YYNLSTATES means shift-and-reduce */
      yyn = yystate - YYNLSTATES;
    }
  }
}
