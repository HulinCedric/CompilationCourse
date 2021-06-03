%option noyywrap 
%{
/**************************************************************/
/*           Analyseur lexical pour le langage Mulot          */
/*    I.U.T. de Nice - Departement Informatique - H. Cedric   */
/*                                                            */
/*         VERSION pour le generateur  FLEX/Windows           */
/**************************************************************/
#include <string.h>
/* INCLUSION DES "NORMES" Mulot  */
/*********************************/
#include "mulot_us.h"
/* DEFINITIONS */
/***************/
%}
D      [0-9]
A      [a-zA-Z]
X      ([a-zA-Z]|[0-9]|_)
tsq    [^']
ascii  [^"\n]
dbleq  \\\"
dblsl  \\\\
W      [ \t]

%{
/* Trace sur la sortie standard.*/
#define LEX_DEBUG
#ifdef LEX_DEBUG                    
#define LIST0 printf ("(LEX) %s\n", yytext)
#define LIST1(c) printf ("(LEX) %s\n", c)
#define LIST2(c,d) printf ("(LEX) %s %s\n", c, d)
#define LISTCAR(x,y) printf ("(LEX) %s %c\n", x, y)
#else
#define LIST0
#define LIST1
#define LIST2
#define LISTCAR
#endif
/*********************/
/* VARIABLE GLOBALE  */
/*********************/
extern unit_synt* us;
/*******************************************************************************/
/* Tableau mettant en correspondance les mots-cles et les valeurs de `classus' */
/*******************************************************************************/
#define NB_ELEM 23
mot_cle table [NB_ELEM] =
{
  {"Mulot",smulot},{"Tolum",stolum},{"Proc",sproc},{"Corp",scorp},{"Fonc",sfonc},{"Cnof",scnof},
  {"return", sreturn}, {"int",sint},{"new",snew},
  {"leve",sleve},{"baisse",sbaisse},{"tourne",stourne},{"avance",savance},
  {"Pour",spour},{"a",sa},{"Ruop",sruop},{"Tantque",stantque},{"Tnat",stnat},
  {"Si",ssi},{"Alors",salors},{"Sinon",ssinon},{"Is",sis},
  {NULL, sbidon}
};

int chercher (char* chaine)
{ 
	char * chaineAChercher;
	int  res, i;
	chaineAChercher  =  (char*) malloc(strlen (chaine)+1);
	strcpy(chaineAChercher, chaine);
	i=0;
	while (table[i].chaine != NULL)
	{
		res = strcmp (chaineAChercher, table[i].chaine);
		if (res == 0) 
			return table[i].cl;
		i++;
	}
	return sbidon;
}

/* REGLES */
/**********/
%}
%%
{W}+            {/* ignorer  espaces  */}
\r\n            { LIST1 ("nouvelle_ligne");us->cl = nouvelle_ligne; return (0);} 
<<EOF>>         { LIST0; us->cl = fin_flot; return (0);} /* Ne plus appeler lex apres reception de fin_flot ! */
";"             { LIST1 ("pt_virgule"); us->cl =pvirg; return (0);}
","             { LIST1 ("virgule"); us->cl =virg; return (0);}
"("             { LIST1 ("parenthese_gauche"); us->cl =pargau; return (0);}
")"             { LIST1 ("parenthese_droite"); us->cl =pardroi; return (0);}
"."             { LIST1 ("point"); us->cl =point; return (0);}
"="             { LIST1 ("egal"); us->cl =egal; return (0);}
"!="            { LIST1 ("notegal"); us->cl =notegal; return (0);}
"=="            { LIST1 ("egalegal"); us->cl =egalegal; return (0);}
">"             { LIST1 ("osup"); us->cl =osup; return (0);}
"<"             { LIST1 ("oinf"); us->cl =oinf; return (0);}
">="            { LIST1 ("osug"); us->cl =osug;return (0);}
"<="            { LIST1 ("oing"); us->cl =oing;return (0);}
"+"             { LIST1 ("plus"); us->cl =plus;return (0);}
"-"             { LIST1 ("moins"); us->cl =moins;return (0);}
"/"             { LIST1 ("divi"); us->cl =divi;return (0);}
"*"             { LIST1 ("mult"); us->cl =mult;return (0);}
"%"             { LIST1 ("pourcent"); us->cl =pourcent;return (0);}
"!"             { LIST1 ("snot"); us->cl =snot;return (0);}
"||"            { LIST1 ("sor"); us->cl =sor;return (0);}
"&&"            { LIST1 ("sand"); us->cl =sand;return (0);}
{A}{X}*         { classus res;
                  res = chercher ( (char*) yytext);
                  if (res == sbidon)
                  {
                    LIST2 ("ident", yytext);
                    us->cl = ident; 
                    us->nom_id =  (char*) malloc (yyleng+1);
                    strncpy (us->nom_id, yytext, yyleng);
                    (us->nom_id)[yyleng] = '\0';
                  }
                  else 
                  {
                    LIST2 ("mot-cle", yytext);
                    us->cl = res;
                  }
                  return (0);}
{D}+            { LIST2 ("cst_ent ", yytext); 
                  us->cl = cst_ent; 
                  us->val_ent = (atoi(yytext)); 
                  return (0);}
"--"([^\n]*)    {/* ignorer commentaires*/}
.           	 { printf ("%s %s %c\n", "*** ERREUR LEXICALE ***","Caractere illegal (ignore) ", yytext[0]);}
%%

