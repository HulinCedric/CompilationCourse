%option noyywrap 
%{
/**************************************************************/
/*                       exolex.lex                           */
/*    I.U.T. de Nice - Departement Informatique - C. Hulin    */
/*                                                            */
/**************************************************************/
#include <stdio.h>
extern int nblignes;
int nberr=0;
%}

%{
/***************/
/* DEFINITIONS */
/***************/
%}

chiffre 		[0-9]
sep     		[ \t]
signe   		[+-]
lettre  		[a-zA-Z]
chaine 			\"({ascii}+)\"
chainevide 		\"\"	
ident			{lettre}({let_chi_tiret}*)
let_chi_tiret	([a-zA-Z]|[0-9]|_)
entier			{signe}?{chiffre}+
decimal 		{signe}?{chiffre}+[.,]{chiffre}+
reel			{signe}?({chiffre}+)[.,]({chiffre}+)[e]{signe}?({chiffre}+)
nombre  		({chiffre}+)
ascii   		[^"\n]
finligne 		[\n]
retourligne		[\r\n]
%%

%{
/* Trace sur la sortie standard.                      */
#define LEX_DEBUG
#ifdef LEX_DEBUG
#define LIST0 printf ("(LEX) %s\n", yytext)
#define LIST1(c) printf ("(LEX) %s\n", c)
#define LIST2(c,d) printf ("(LEX) %s %s\n", c, d)
#define LIST3(x,y) printf ("(LEX) %s %c\n", x, y)
#define LISTERR(x,y) printf("ERREUR ligne %d : %s\n", x, y)
#else
#define LIST0
#define LIST1
#define LIST2
#define LIST3
#define LISTERR
#endif

/***************/
/* REGLES      */
/***************/
%}
<<EOF>>      { LIST1("fin de fichier"); return 1;}

{sep}        /* ignorer separateur */

{finligne}   { nblignes++; return 0;}

{retourligne} /* ignorer separateur */

{chiffre}    { LIST2("CHIFFRE :", yytext); return 0;}

{nombre}	 { LIST2("NOMBRE  :", yytext); return 0;}

({signe}+)   { LISTERR(nblignes, "nombre manquant"); nberr++; return -1;}

{entier}	 { LIST2("ENTIER RELATIF :", yytext); return 0;}

{decimal} 	 { LIST2("NOMBRE DECIMAL :", yytext); return 0;}

{signe}?({chiffre}+)[.,] {  LISTERR(nblignes, "partie decimale manquante"); nberr++; return -1;}

{signe}?[.,]({chiffre}+) { LISTERR(nblignes, "partie entiere manquante"); nberr++; return -1;}

{signe}?[.,] { LISTERR(nblignes, "ni partie entiere ni partie decimale"); nberr++; return -1;}

{reel} 		 { LIST2("REEL :", yytext); return 0;}

{signe}?({chiffre}+)[.,]({chiffre}+)[e]{signe}? { LISTERR(nblignes, "exposant manquant"); nberr++; return -1;}

{ident} 	 { LIST2("IDENTIFICATEUR :", yytext); return 0;}

{chaine}	 { LIST2("CHAINE :", yytext); return 0;} 

{chainevide} { LIST1("CHAINE : vide"); return 0;}

\"           { LISTERR(nblignes, "fin de chaine attendu"); nberr++; return -1;}

.            { LIST3("caractere ignore :", yytext[0]); return 0;}
%%
