/*****************************************************************/
/*   Analyseur pour le langage Mulot                             */
/*   I.U.T. de Nice - Departement Informatique - L.Brenac        */
/*   analyseur_main.c                                            */
/*****************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include "mulot_us.h"
#include "mulot_util.h"

extern int yylex();
unit_synt* us; /* variable globale partagee avec lex */
int compteurligne;

void proc_listinst();
void proc_expr();

/****************************************/
/* procedure principale - main          */
/****************************************/
int main( int argc , char *argv[])
{
	init_mulot();
	us = (unit_synt*) malloc (sizeof(unit_synt));
	if (us == NULL) { fprintf(stderr, "pb alloc mem\n"); exit(1);}
	compteurligne = 1;
	prochus() ; verifier (stop, us->cl == smulot,1);
	prochus() ; verifier (stop, us->cl == ident,4);
	prochus();
	
	while ((us->cl == sproc) || (us->cl == sfonc))
	{
		proc_defroutine(); 
		prochus();
	}

	if (us->cl == ident || us->cl == spour || us->cl == stantque || us->cl == ssi || us->cl == sint || us->cl == smulot)
	{
		proc_listinst();
		prochus();
	}

	verifier (stop, us->cl == stolum,2);
	printf ("\n\n[[[[[[[[[[ Mulot : Fin normale de compilation ]]]]]]]]]]\n\n");
} 
