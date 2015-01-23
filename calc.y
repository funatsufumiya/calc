/* kmyacc file (C) */

%{

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

%}

%union {
  int intval;
  char* strval;
  double dblval;
  double* dblarrval;
}

%token NUM
%token ID

%type <intval> NUM
%type <strval> ID
%type <dblval> expr
%type <dblval> funcall
%type <dblarrval> args


%left '+' '-'
%left '*' '/'
%left '^'

%start line

%%

line
  : expr { retVal = $1; }
  ;

expr
  : expr '+' expr { $$ = $1 + $3; }
  | expr '-' expr { $$ = $1 - $3; }
  | expr '*' expr { $$ = $1 * $3; }
  | expr '/' expr { $$ = $1 / $3; }
  | expr '^' expr { $$ = pow($1,$3); }
  | funcall { $$ = $1; }
  | '(' expr ')' { $$ = $2; }
  | '-' expr { $$ = -($2); }
  | '+' expr { $$ = +($2); }
  | NUM { $$ = $1; }
  | ID { if(isConstExists($1)){ $$ = getConst($1); }else{ char str[100]; sprintf(str,"Constant '%s' does not exists",$1); yyerror(str); retVal = 0; return 1; }; }
  ;

funcall
  : ID '(' args ')' { if(isFuncExists($1)){ $$ = callDefinedFunc($1,argSize,$3); free($3); }else{ char str[100]; sprintf(str,"Function '%s' does not exists",$1); yyerror(str); retVal = 0; free($3); return 1; };  }
  ;

args
  : /* empty */ { double arr[] = {}; $$ = arr; }
  | args ',' expr { argSize += 1; double* args = (double*)realloc($1, argSize * sizeof(double)); args[argSize-1] = $3; $$ = args; }
  | expr { double* args = (double*)malloc(sizeof(double)); args[0] = $1; argSize = 1; $$ = args; }
  ;

%%

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
