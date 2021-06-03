/*****************************************************************/
/*   Analyseur pour le langage Mulot                             */
/*   I.U.T. de Nice - Departement Informatique - L.Brenac        */
/*   analyseur_rout.c                                            */
/*****************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include "mulot_us.h"
#include "mulot_util.h"
/*sema*/ #include "mulot_tds.h"

extern int yylex();
extern unit_synt* us; /* variable globale partagee avec lex */
extern int compteurligne;
/*sema*/ extern pt_identif  tds[10];
/* sema */ void proc_inst(int n);

/*********************************/
/* procedure proc_listinst      */
/********************************/
// void proc_listinst()
/* sema */ void proc_listinst(int n)
{
	// DEBUGGING  ("...ENTREE proc_listinst\n");
	/* sema */ DEBUGGING2  ("...ENTREE proc_listinst routine %d\n",n);
	while (us->cl == ident || us->cl == spour || us->cl == stantque || us->cl == ssi 
		|| us->cl == sint || us->cl == smulot || us->cl == sreturn)
	{
		// proc_inst();
		/* sema */ proc_inst(n);
	}
	DEBUGGING ("......SORTIE proc_listinst\n");
}

//...

/*********************************/
/* procedure proc_defroutine     */
/*********************************/
// void proc_defroutine()
/* sema */ void proc_defroutine(int n)
{
	DEBUGGING  ("...ENTREE proc_defroutine\n");
	// if (us->cl == sproc) proc_defproc();
	// else proc_deffonc();
	/* sema */ tds[n] = NULL;
	/* sema */ if (us->cl == sproc) proc_defproc(n);
	/* sema */ else proc_deffonc(n);
	/* sema */ fprintf (stderr, "<== DEBUT TABLE DES SYMBOLES DE LA ROUTINE N %d ==>\n",n);
	/* sema */ afficher_identif (tds[n]);
	/* sema */ fprintf (stderr, "<== FIN TABLE DES SYMBOLES DE LA ROUTINE N %d ==>\n",n);
	DEBUGGING ("......SORTIE proc_defroutine\n");
}

