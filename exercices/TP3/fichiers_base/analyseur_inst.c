/*****************************************************************/
/*   Analyseur syntaxique pour le langage Mulot                  */
/*   I.U.T. de Nice - Departement Informatique - L.Brenac        */
/*   analyseur_inst.c                                            */
/*****************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include "mulot_us.h"
#include "mulot_util.h"
 
extern int yylex();
extern unit_synt* us; /* variable globale partagee avec lex */
extern int compteurligne;

void proc_expr();


/*********************************/
/* procedure proc_facteur        */
/*********************************/
void proc_facteur()

{
	DEBUGGING  ("...ENTREE proc_facteur\n");
	// A COMPLETER
	DEBUGGING ("......SORTIE proc_facteur\n");
}

/*********************************/
/* procedure proc_terme          */
/*********************************/
void proc_terme()
{
	DEBUGGING  ("...ENTREE proc_terme\n");
	proc_facteur(); 
	while (us->cl == mult || us->cl == divi || us->cl == pourcent || us->cl == sand)
	{
		prochus();
		proc_facteur(); 
	}
	DEBUGGING ("......SORTIE proc_terme\n");
}

/*********************************/
/* procedure proc_exprsimple     */
/*********************************/
void proc_exprsimple()
{
	DEBUGGING  ("...ENTREE proc_exprsimple\n");
	if (us->cl == plus || us->cl == moins)
	{
		prochus();
	}
	proc_terme();
	while (us->cl == plus || us->cl == moins || us->cl == sor)
	{
		prochus();
		proc_terme();
	}
	DEBUGGING ("......SORTIE proc_exprsimple\n");
}

/*********************************/
/* procedure proc_expr           */
/*********************************/
void proc_expr()
{
	DEBUGGING  ("...ENTREE proc_expr\n");
	proc_exprsimple();
	if (us->cl == egalegal || us->cl == notegal || us->cl == oing || us->cl == osug || us->cl == oinf || us->cl == osup)
	{
		prochus();
		proc_exprsimple();
	}
	DEBUGGING ("......SORTIE proc_expr\n");
}