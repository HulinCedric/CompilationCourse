/*****************************************************************/
/*         Analyseur syntaxique pour le langage Mulot            */
/*   I.U.T. de Nice - Departement Informatique - L. Brenac       */
/*                                                               */
/*      Prototype qui boucle sur le flot d'unites syntaxiques    */
/*           VERSION pour le generateur  FLEX/Windows            */
/*****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "mulot_us.h"

extern int yylex();
unit_synt * us;				/* variable globale partagee avec lex */

int main()
{
	printf("Debut Analyse ...\n");
	us = (unit_synt *) malloc(sizeof (unit_synt));
	/* boucle sur le flot */
	yylex(); 
	while (us->cl != fin_flot)
	{
		/*printf ("   Scalaire = %d", us->cl);
		switch (us->cl) 
		{
			case ident :      
				{ printf (" , Nom d'identificateur : %s", us->nom_id); break; }
			case cst_ent :    
				{ printf (" , Constante entiere : %d", us->val_ent); break; }
		}
		printf ("\n");*/
		yylex();
  }  
  printf("... Fin Analyse\n");
}

