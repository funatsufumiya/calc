

(function(G){

var retVal;


/* Prototype file of JavaScript parser.
 * Written by MORI Koichiro
 * This file is PUBLIC DOMAIN.
 */

var buffer;
var token;
var toktype;

var YYERRTOK = 256;
var NUM = 257;
var ID = 258;

  
/*
  #define yyclearin (yychar = -1)
  #define yyerrok (yyerrflag = 0)
  #define YYRECOVERING (yyerrflag != 0)
  #define YYERROR  goto yyerrlab
*/


/** Debug mode flag **/
var yydebug = false;

/** lexical element object **/
var yylval = null;

/** Dialog window **/
var yywin = null;
var yydoc = null;

function yydocopen() {
  if (yywin == null) {
    yywin = window.open("", "yaccdiag", "resizable,status,width=600,height=400");
    yydoc = null;
  }
  if (yydoc == null)
    yydoc = yywin.document;
  yydoc.open();
}

function yyprintln(msg)
{
  if (yydoc == null)
    yydocopen();
  yydoc.write(msg + "<br>");
}

function yyflush()
{
  if (yydoc != null) {
    yydoc.close();
    yydoc = null;
    yywin = null;
  }
}



var yytranslate = [
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
  ];

var YYBADCH = 12;
var YYMAXLEX = 259;
var YYTERMS = 12;
var YYNONTERMS = 5;

var yyaction = [
     35,   20,    3,    4,   10,    6,    7,    5,    8,    9,
     10,   32,    6,    7,   37,   11,    0,    0,    2
  ];

var YYLAST = 19;

var yycheck = [
      2,    3,    4,    5,    8,    4,    5,    9,    6,    7,
      8,   10,    4,    5,   10,   11,    0,   -1,    9
  ];

var yybase = [
     -2,    1,   -2,   -2,   -2,   -2,   -2,   -2,   -2,   -2,
     -2,   -2,    8,    8,    8,    2,    2,    2,    2,    4,
      9,   16,   -4,   -4,    0,    2,    0,    0,    0,    0,
      0,    0,    0,    0,    0,    0,    2,    2,    2
  ];

var YY2TBLSTATE = 15;

var yydefault = [
  32767,32767,   14,32767,32767,32767,32767,32767,32767,32767,
  32767,32767,    1,   16,   15,   10,    9,    2,    3,32767,
     12,32767,    4,    5
  ];



var yygoto = [
     13,   15,   16,    1,   17,   18,   22,   23,   30,   14
  ];

var YYGLAST = 10;

var yygcheck = [
      2,    2,    2,    2,    2,    2,    2,    2,    2,    2
  ];

var yygbase = [
      0,    0,   -2,    0,    0
  ];

var yygdefault = [
  -32768,   21,   12,   31,   19
  ];

var yylhs = [
      0,    1,    2,    2,    2,    2,    2,    2,    2,    2,
      2,    2,    2,    3,    4,    4,    4
  ];

var yylen = [
      1,    1,    3,    3,    3,    3,    3,    1,    3,    2,
      2,    1,    1,    4,    0,    3,    1
  ];

var YYSTATES = 29;
var YYNLSTATES = 24;
var YYINTERRTOK = 1;
var YYUNEXPECTED = 32767;
var YYDEFAULT = -32766;

/*
 * Parser entry point
 */

function yyparse()
{
  var yyastk = new Array();
  var yysstk = new Array();

  yystate = 0;
  yychar = -1;

  yysp = 0;
  yysstk[yysp] = 0;
  yyerrflag = 0;
  for (;;) {
    if (yybase[yystate] == 0)
      yyn = yydefault[yystate];
    else {
      if (yychar < 0) {
        if ((yychar = yylex()) <= 0) yychar = 0;
        yychar = yychar < YYMAXLEX ? yytranslate[yychar] : YYBADCH;
      }

      if (((yyn = yybase[yystate] + yychar) >= 0
	    && yyn < YYLAST && yycheck[yyn] == yychar
           || (yystate < YY2TBLSTATE
               && (yyn = yybase[yystate + YYNLSTATES] + yychar) >= 0
               && yyn < YYLAST && yycheck[yyn] == yychar))
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
          yysp++;

          yysstk[yysp] = yystate = yyn;
          yyastk[yysp] = yylval;
          yychar = -1;
          
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
        yyflush();
        return 0;
      }
      else if (yyn != YYUNEXPECTED) {
        /* reduce */
        yyl = yylen[yyn];
        yyval = yyastk[yysp-yyl+1];
        /* Following line will be replaced by reduce actions */
        switch(yyn) {
        case 1:
{ retVal = yyastk[yysp-(1-1)]; } break;
        case 2:
{ yyval = yyastk[yysp-(3-1)] + yyastk[yysp-(3-3)]; } break;
        case 3:
{ yyval = yyastk[yysp-(3-1)] - yyastk[yysp-(3-3)]; } break;
        case 4:
{ yyval = yyastk[yysp-(3-1)] * yyastk[yysp-(3-3)]; } break;
        case 5:
{ yyval = yyastk[yysp-(3-1)] / yyastk[yysp-(3-3)]; } break;
        case 6:
{ yyval = Math.pow(yyastk[yysp-(3-1)],yyastk[yysp-(3-3)]); } break;
        case 7:
{ yyval = yyastk[yysp-(1-1)]; } break;
        case 8:
{ yyval = yyastk[yysp-(3-2)]; } break;
        case 9:
{ yyval = -(yyastk[yysp-(2-2)]); } break;
        case 10:
{ yyval = +(yyastk[yysp-(2-2)]); } break;
        case 11:
{ yyval = yyastk[yysp-(1-1)]; } break;
        case 12:
{ if(isConstExists(yyastk[yysp-(1-1)])){ yyval = getConst(yyastk[yysp-(1-1)]); }else{ yyerror("Constant '"+yyastk[yysp-(1-1)]+"' does not exists"); retVal = NaN; return; }; } break;
        case 13:
{ if(isFuncExists(yyastk[yysp-(4-1)])){ yyval = callDefinedFunc(yyastk[yysp-(4-1)],yyastk[yysp-(4-3)]); }else{ yyerror("Function '"+yyastk[yysp-(4-1)]+"' does not exists"); retVal = NaN; return; };  } break;
        case 14:
{ yyval = []; } break;
        case 15:
{ yyval = yyastk[yysp-(3-1)].concat([yyastk[yysp-(3-3)]]); } break;
        case 16:
{ yyval = [yyastk[yysp-(1-1)]]; } break;
        }
        /* Goto - shift nonterminal */
        yysp -= yyl;
        yyn = yylhs[yyn];
        if ((yyp = yygbase[yyn] + yysstk[yysp]) >= 0 && yyp < YYGLAST
            && yygcheck[yyp] == yyn)
          yystate = yygoto[yyp];
        else
          yystate = yygdefault[yyn];
          
        yysp++;

        yysstk[yysp] = yystate;
        yyastk[yysp] = yyval;
      }
      else {
        /* error */
        switch (yyerrflag) {
        case 0:
          yyerror("syntax error");
        case 1:
        case 2:
          yyerrflag = 3;
          /* Pop until error-expecting state uncovered */

          while (!((yyn = yybase[yystate] + YYINTERRTOK) >= 0
                   && yyn < YYLAST && yycheck[yyn] == YYINTERRTOK
                   || (yystate < YY2TBLSTATE
                       && (yyn = yybase[yystate + YYNLSTATES] + YYINTERRTOK) >= 0
                       && yyn < YYLAST && yycheck[yyn] == YYINTERRTOK))) {
            if (yysp <= 0) {
              yyflush();
              return 1;
            }
            yystate = yysstk[--yysp];
          }
          yyn = yyaction[yyn];
          yysstk[++yysp] = yystate = yyn;
          break;

        case 3:
          if (yychar == 0) {
            yyflush();
            return 1;
          }
          yychar = -1;
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



var pos = 0;
var buffer;
var numRegex = /^(?:0|[1-9][0-9]*|0[.]\d*|[1-9][0-9]*[.]\d*|[.]\d*)$/;
var idRegex = /^[a-zA-Z\d_]+$/;

var definedConsts = {
  PI: Math.PI,
  TWO_PI: 2*Math.PI,
  HALF_PI: 2*Math.PI,
  E: Math.E,
  LN2: Math.LN2,
  LN10: Math.LN10,
  LOG2E: Math.LOG2E,
  LOG10E: Math.LOG10E
};

var definedFuncs = {
  abs: function(n){ return Math.abs(n); },
  sin: function(n){ return Math.sin(n); },
  cos: function(n){ return Math.cos(n); },
  tan: function(n){ return Math.tan(n); },
  asin: function(n){ return Math.asin(n); },
  acos: function(n){ return Math.acos(n); },
  atan: function(n){ return Math.atan(n); },
  atan2: function(a,b){ return Math.atan2(a,b); },
  log: function(n){ return Math.log(n); },
  max: function(){ return Math.max.apply(null, arguments); },
  min: function(){ return Math.min.apply(null, arguments); },
  sq: function(n){ return n*n; },
  sqrt: function(n){ return Math.sqrt(n); },
  cbrt: function(n){ return Math.pow(n, 1/3); },
  pow: function(a,b){ return Math.pow(a,b); },
  floor: function(n){ return Math.floor(n); },
  ceil: function(n){ return Math.ceil(n); },
  round: function(n){ return Math.round(n); },
  random: function(){ return Math.random(); },
  exp: function(n){ return Math.exp(n); },
  log: function(n){ return Math.log(n); },
  log2: function(n){ return Math.log(n)/Math.log(2); },
  log10: function(n){ return Math.log(n)/Math.log(10); },
  logN: function(n,base){ return Math.log(n)/Math.log(base); },
};

function yyerror(msg){
  console.error("[ERROR] "+ msg);
}

function callDefinedFunc(name, args){
  return definedFuncs[name].apply(null, args);
}

function isFuncExists(name){
  return (typeof definedFuncs[name] != 'undefined');
}

function getConst(name){
  return definedConsts[name];
}

function isConstExists(name){
  return (typeof definedConsts[name] != 'undefined');
}

function isNumber(s){
  return numRegex.test(s)
}

function isIdentifier(s){
  return idRegex.test(s);
}

function isBlank(c){
  return (c == ' ' || c == '\n' || c == '\t');
}

function yylex(){
  if(pos == buffer.length){
    return 0;
  }

  var c = buffer[pos];

  if(isBlank(c)){
    while(true){
      if(pos != buffer.length-1 && isBlank(buffer[pos+1])){
        ++pos;
        continue; // skip
      }else{
        ++pos;
        break; // skip
      }
    }

    c = buffer[pos];
  }

  if(pos == buffer.length){
    return 0;
  }

  if(isNumber(c)){
    var numStr = c;
    while(true){
      if(pos != buffer.length-1 && isNumber(numStr + buffer[pos+1])){
        numStr += buffer[pos+1];
        ++pos;
      }else{
        yylval = +(numStr);
        ++pos;
        return NUM;
      }
    }
  }else if(isIdentifier(c)){
    var idStr = c;
    while(true){
      if(pos != buffer.length-1 && isIdentifier(idStr + buffer[pos+1])){
        idStr += buffer[pos+1];
        ++pos;
      }else{
        yylval = idStr;
        ++pos;
        return ID;
      }
    }
  }else{
    return buffer.charCodeAt(pos++);
  }
}

function calc(s){
  pos = 0
  buffer = s;
  yyparse();
  return retVal;
}

G.calc = calc;

})(this); // Global