/*****************************************************************/
/*   Analyseur pour le langage Mulot                             */
/*   I.U.T. de Nice - Departement Informatique - L.Brenac        */
/*   analyseur_main.c                                            */
/*****************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include "mulot_us.h"
#include "mulot_util.h"
#include "mulot_tds.h"
#include "mulot_prod.h"


extern int yylex();
unit_synt* us; /* variable globale partagee avec lex */
int compteurligne;

/* prod */ FILE * fic;
/* prod */ char * nom_fichier;

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
	
	/* prod */ nom_fichier = copier (us->nom_id);
	/* prod */ if (creer_fichier() == 0) {fprintf(stderr, "pb creation fichier\n"); exit(1);}
	/* prod */ produire_entete();
	/* prod */ produire_import();
	/* prod */ produire_debut_applet();
	
	prochus();
	
	while ((us->cl == sproc) || (us->cl == sfonc))
	{
		proc_defroutine(); 
	}

	if (us->cl == ssi || us->cl == stantque || us->cl == spour || us->cl == sint || us->cl == smulot || us->cl == ident || us->cl == sreturn)
	{
		/* prod */ produire_debut_paint_applet();
		
		proc_listinst();
		
		/* prod */ produire_fin_paint_applet();
	}
	

	verifier (stop, us->cl == stolum,2);
	
	/* prod */ produire_fin_applet();
	/* prod */ fermer_fichier();
	
	printf ("\n\n[[[[[[[[[[ Mulot : Fin normale de compilation ]]]]]]]]]]\n\n");
} 
