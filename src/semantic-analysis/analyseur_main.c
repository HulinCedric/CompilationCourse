/*****************************************************************/
/*   Analyseur syntaxique/semantique pour le langage Mulot       */
/*   I.U.T. de Nice - Departement Informatique - C. Hulin        */
/*   analyseur_main.c                                            */
/*****************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include "mulot_us.h"
#include "mulot_util.h"
#include "mulot_tds.h"

extern int yylex();
unit_synt* us; /* variable globale partagee avec lex */
int compteurligne;

// void proc_listinst();
/* sema */ void proc_listinst(int n);
/* sema */ void proc_defroutine(int n);

// void proc_expr();
/* sema */ description * proc_expr(int n);

/*!sema!*/ pt_identif  tds[10];
/*!sema!*/ int niveau;

/****************************************/
/* procedure principale - main          */
/****************************************/
int main( int argc , char *argv[])
{
	/* prod */ FILE * fic;
	/* prod */ char * nom_fichier;
	/* sema */ int i;
	/*!sema!*/ tds[0] = NULL;
	/* sema */ niveau = 0;
	/*!sema!*/ InitSemantique(); 
	init_mulot();
	us = (unit_synt*) malloc (sizeof(unit_synt));
	if (us == NULL) { fprintf(stderr, "pb alloc mem\n"); exit(1);}
	compteurligne = 1;
	prochus(); 
	verifier (stop, us->cl == smulot,1);
	prochus(); 
	verifier (stop, us->cl == ident,4);
	prochus();
	/* prod */	nom_fichier = copier (us->nom_id);
	/* prod */	if (creer_fichier() == 0)
				{fprintf(stderr, "pb creation fichier\n"); exit(1);}
	/* prod */	produire_entete();
	/* prod */	produire_import();
	/* prod */	produire_debut_applet();
	
	prochus();
	
	while ((us->cl == sproc) || (us->cl == sfonc))
	{
		/* sema */ niveau++;
		// proc_defroutine(); 
		/* sema */ proc_defroutine(niveau--);
	}

	if (us->cl == ident || us->cl == spour || us->cl == stantque || us->cl == ssi || us->cl == sint || us->cl == smulot)
	{
		/* prod */ produire_debut_paint_applet();
		/* sema */ proc_listinst(0);
		/* prod */ produire_fin_paint_applet();
	}

	verifier (stop, us->cl == stolum,2);
	/* prod */ produire_fin_applet();
	/* prod */ fermer_fichier();
	/* sema */ for (i=0; i<=niveau; i++)
	/* sema */ {
	/* sema */		if (i == 0) fprintf (stderr, "\n\n<== DEBUT TABLE DES SYMBOLES MAIN ==>\n");
	/* sema */ else fprintf (stderr, "\n\n<== DEBUT TABLE DES SYMBOLES DE LA ROUTINE N %d ==>\n",i);

	/* sema */	afficher_identif (tds[i]);
	/* sema */	fprintf (stderr, "<== FIN TABLE DES SYMBOLES DE LA ROUTINE N %d ==>\n\n",i);
	/* sema */ }

	printf ("\n\n[[[[[[[[[[ Mulot : Fin normale de compilation ]]]]]]]]]]\n\n");
} 
