/*****************************************************************/
/*   Analyseur syntaxique pour le langage Mulot                  */
/*   I.U.T. de Nice - Departement Informatique - C. Hulin        */
/*   analyseur_inst.c                                            */
/*****************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include "mulot_us.h"
#include "mulot_util.h"
 
extern int yylex();
extern unit_synt* us; /* variable globale partagee avec lex */
extern int compteurligne;

/*********************************/
/* procedure proc_creation       */
/*********************************/
void proc_creation()
{
	DEBUGGING  ("...ENTREE proc_creation\n");
	verifier (stop, us->cl == smulot, 1); prochus();
	verifier (stop, us->cl == pargau, 2); prochus(); 
	if (us->cl != pardroi) {
		proc_expr();
		verifier (stop, us->cl == virg, 21); prochus(); 
		proc_expr();
		if (us->cl != pardroi) {
			verifier (stop, us->cl == virg, 21); prochus(); 
			verifier (stop, us->cl == ident, 4); prochus();
			if (us->cl != pardroi) {
				verifier (stop, us->cl == virg, 21); prochus(); 
				proc_expr();
			}
		}
	}
	verifier (stop, us->cl == pardroi, 3); prochus();
	DEBUGGING ("......SORTIE proc_creation\n");
}

/*********************************/
/* procedure proc_action         */
/*********************************/
void proc_action()
{
	DEBUGGING  ("...ENTREE proc_action\n");
	verifier (stop, us->cl == sleve || us->cl == sbaisse || us->cl == stourne || us->cl == savance, 19);
	switch(us->cl) {
		case sleve :
			prochus(); 
			verifier (stop, us->cl == pargau, 2); prochus(); 
			verifier (stop, us->cl == pardroi, 3);
			break;

		case sbaisse :
			prochus(); 
			verifier (stop, us->cl == pargau, 2); prochus(); 
			verifier (stop, us->cl == pardroi, 3);
			break;

		case stourne :
			prochus(); 
			verifier (stop, us->cl == pargau, 2); prochus();
			proc_expr();
			verifier (stop, us->cl == pardroi, 3);
			break;
			
		case savance :
			prochus(); 
			verifier (stop, us->cl == pargau, 2); prochus(); 
			proc_expr();
			verifier (stop, us->cl == pardroi, 3);
			break;
	}
	prochus();
	DEBUGGING ("......SORTIE proc_action\n");
}

/*********************************/
/* procedure proc_facteur        */
/*********************************/
void proc_facteur()
{
	DEBUGGING  ("...ENTREE proc_facteur\n");
	verifier (stop, us->cl == ident || us->cl == cst_ent || us->cl == snot || us->cl == pargau, 17);
	switch(us->cl) {
		case ident :
			prochus();
			if (us->cl == pargau) {
				prochus();
				if (us->cl != pardroi) {
					proc_expr();
					while (us->cl == virg) {
						prochus();
						proc_expr();
					}
				}
				verifier (stop, us->cl == pardroi, 3); prochus();
			}
			break;
			
		case cst_ent :
			prochus();
			break;
			
		case snot : 
			prochus();
			verifier (stop, us->cl == pargau, 2); prochus();
			proc_expr();
			verifier (stop, us->cl == pardroi, 3); prochus();
			break;
			
		case pargau :
			prochus();
			proc_expr();
			verifier (stop, us->cl == pardroi, 3); prochus();
			break;
	}
	DEBUGGING ("......SORTIE proc_facteur\n");
}

/*********************************/
/* procedure proc_terme          */
/*********************************/
void proc_terme()
{
	DEBUGGING  ("...ENTREE proc_terme\n");
	proc_facteur(); 
	while (us->cl == mult || us->cl == divi || us->cl == pourcent || us->cl == sand) {
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
		prochus();
	proc_terme();
	while (us->cl == plus || us->cl == moins || us->cl == sor) {
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
	while (us->cl == egalegal || us->cl == notegal || us->cl == oing || us->cl == osug || us->cl == oinf || us->cl == osup) {
		prochus();
		proc_exprsimple();
	}
	DEBUGGING ("......SORTIE proc_expr\n");
}

/*********************************/
/* procedure proc_inst           */
/*********************************/
void proc_inst()
{
	DEBUGGING  ("...ENTREE proc_inst\n");
	verifier (stop, us->cl == smulot || us->cl == ident || us->cl == sint || us->cl == spour || us->cl == stantque || us->cl == ssi || us->cl == sreturn, 9);
	switch (us->cl)
	{
		case smulot :
			prochus(); 
			verifier (stop, us->cl == ident, 4); prochus();
			verifier (stop, us->cl == pvirg || us->cl == egal, 27);
			if (us->cl == egal) {
				prochus(); 
				verifier (stop, us->cl == snew, 20); prochus();
				proc_creation();
			}
			verifier (stop, us->cl == pvirg, 22); prochus();
			break;

		case ident :
			prochus(); 
			verifier (stop, us->cl == egal || us->cl == point || us->cl == pargau, 18);
			switch(us->cl) {
				case egal :
					prochus(); 
					if (us->cl == snew)
					{
						prochus();
						proc_creation();
					}
					else 
					{
						proc_expr();
					}
					break;

				case point : 
					prochus();
					proc_action();
					break;
					
				case pargau :
					prochus();
					if (us->cl != pardroi) {
						proc_expr();
						while (us->cl == virg) {
							prochus();
							proc_expr();
						}
					}
					verifier (stop, us->cl == pardroi, 3); prochus();
					break;
			}
			verifier (stop, us->cl == pvirg, 22); prochus();
			break;

		case sint :
			prochus(); 
			verifier (stop, us->cl == ident, 4); prochus();
			verifier (stop, us->cl == pvirg || us->cl == egal, 27);
			if (us->cl == egal) {
				prochus();
				proc_expr();
			}
			verifier (stop, us->cl == pvirg, 22); prochus();
			break;
			
		case spour :
			prochus(); 
			verifier (stop, us->cl == ident || us->cl == sint, 28);
			if (us->cl == sint)
				prochus(); 
			prochus(); 
			verifier (stop, us->cl == egal, 10); prochus(); 
			proc_expr();
			verifier (stop, us->cl == sa, 11); prochus(); 
			proc_expr();
			proc_listinst();
			verifier (stop, us->cl == sruop, 12); prochus();
			break;

		case stantque :
			prochus(); 
			verifier (stop, us->cl == pargau, 5); prochus(); 
			proc_expr();
			verifier (stop, us->cl == pardroi, 6); prochus(); 
			proc_listinst();
			verifier (stop, us->cl == stnat, 13); prochus();
			break;

		case ssi :
			prochus(); 
			verifier (stop, us->cl == pargau, 5); prochus(); 
			proc_expr();
			verifier (stop, us->cl == pardroi, 6); prochus(); 
			verifier (stop, us->cl == salors, 14); prochus(); 
			proc_listinst();
			verifier (stop, us->cl == ssinon || us-> cl == sis, 15);
			if (us->cl == ssinon) {
				prochus(); 
				proc_listinst();
			}
			verifier (stop, us->cl == sis, 16); prochus();
			break;

		case sreturn :
			prochus(); 
			proc_expr();
			verifier (stop, us->cl == pvirg, 22); prochus();
			break;

	}
	DEBUGGING ("......SORTIE proc_inst\n");
}