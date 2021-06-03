/*****************************************************************/
/*   Analyseur pour le langage Mulot                             */
/*   I.U.T. de Nice - Departement Informatique - L.Brenac        */
/*   analyseur_rout.c                                            */
/*****************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include "mulot_us.h"
#include "mulot_util.h"
#include "mulot_tds.h"
#include "mulot_prod.h"

extern int yylex();
extern unit_synt* us; /* variable globale partagee avec lex */
extern int compteurligne;

/*********************************/
/* procedure proc_defroutine     */
/*********************************/
void proc_defroutine()
{
	DEBUGGING  ("...ENTREE proc_defroutine\n");
	if (us->cl == sproc) {
		proc_defproc();
	}
	else {
		if (us->cl == sfonc) {
			proc_deffonc();
		}
	}
	DEBUGGING ("......SORTIE proc_defroutine\n");
}

/*********************************/
/* procedure proc_deffonc        */
/*********************************/
void proc_deffonc()
{	
	/* prod */ char * nom_routine; 

	DEBUGGING  ("...ENTREE proc_deffonc\n");
	verifier(stop, us->cl == sfonc, 3);
	prochus();
	verifier(stop, us->cl == ident, 4);
	prochus(); 
	/* prod */ PRODUIRE1("\npublic int ");
	/* prod */ nom_routine = copier(us->nom_id); 
	/* prod */ PRODUIRE2("%s ", nom_routine);
	proc_signature();
	/* prod */ PRODUIRE1(" {\n");
	verifier(stop, us->cl == egal, 7);
	prochus(); 
	verifier(stop, us->cl == sint, 8);
	prochus(); 
	if (us->cl == ssi || us->cl == stantque || us->cl == spour || us->cl == sint || us->cl == smulot || us->cl == ident || us->cl == sreturn) proc_listinst();
	verifier (stop, us->cl == scnof, 27);
	/* prod */ PRODUIRE1("}\n");
	prochus();
	DEBUGGING ("......SORTIE proc_deffonc\n");
}

/*********************************/
/* procedure proc_defproc        */
/*********************************/
void proc_defproc()
{
	/* prod */ char * nom_routine; 
	
	DEBUGGING ("...ENTREE proc_defproc\n"); 
	verifier (stop, us->cl == sproc, 3); 
	prochus(); 
	verifier (stop, us->cl == ident, 4); 
	prochus(); 
	/* prod */ PRODUIRE1("\npublic void ");
	/* prod */ nom_routine = copier(us->nom_id); 
	/* prod */ PRODUIRE2("%s ", nom_routine);
	proc_signature();
	/* prod */ PRODUIRE1(" {\n");
	if (us->cl == ssi || us->cl == stantque || us->cl == spour || us->cl == sint || us->cl == smulot || us->cl == ident) proc_listinst();
	verifier (stop, us->cl == scorp, 5); 
	/* prod */ PRODUIRE1("}\n");
	prochus();
	DEBUGGING ("......SORTIE proc_defproc\n");
}

/*********************************/
/* procedure proc_defparam       */
/*********************************/
void proc_defparam()
{
	/* prod */ char* nom_param;
	
	DEBUGGING  ("...ENTREE proc_defparam\n");
	verifier(stop, us->cl == sint || us->cl == smulot, 18);
	/* prod */ if (us->cl == sint) PRODUIRE1("int ");
	/* prod */ else PRODUIRE1("Mulot ");
	prochus();
	verifier(stop, us->cl == ident, 4);
	/* prod */ nom_param= copier(us->nom_id);
	/* prod */ PRODUIRE2("%s", nom_param);
	prochus();
	DEBUGGING ("......SORTIE proc_defparam\n");
}

/*********************************/
/* procedure proc_listinst      */
/********************************/
void proc_listinst()
{
	DEBUGGING  ("...ENTREE proc_listinst\n");
	while (us->cl == ssi || us->cl == stantque || us->cl == spour || us->cl == sint || us->cl == smulot || us->cl == ident || us->cl == sreturn) {
		proc_inst();
	}
	DEBUGGING ("......SORTIE proc_listinst\n");
}

/*********************************/
/* procedure proc_oprel          */
/*********************************/
void proc_oprel()
{
	DEBUGGING  ("...ENTREE proc_oprel\n");
	verifier(stop, us->cl == egalegal || us->cl == notegal || us->cl == oinf || us->cl == osup || us->cl == osug || us->cl == oing, 10);
	switch (us->cl) {
		case egalegal:
			PRODUIRE1("==");
			break;
		case notegal:
			PRODUIRE1("!=");
			break;
		case oing:
			PRODUIRE1("<=");
			break;
		case osug:
			PRODUIRE1(">=");
			break;
		case oinf:
			PRODUIRE1("<");
			break;
		case osup:
			PRODUIRE1(">");
			break;
		default:
			break;
	}
	prochus();
	DEBUGGING ("......SORTIE proc_oprel\n");
}

/*********************************/
/* procedure proc_opadd          */
/*********************************/
void proc_opadd()
{
	DEBUGGING  ("...ENTREE proc_opadd\n");
	verifier(stop, us->cl == plus || us->cl == moins || us->cl == sor, 11);
	switch (us->cl) {
		case plus:
			PRODUIRE1("+");
			break;
		case moins:
			PRODUIRE1("-");
			break;
		case sor:
			PRODUIRE1("||");
			break;
		default:
			break;
	}
	prochus();
	DEBUGGING ("......SORTIE proc_opadd\n");	
}

/*********************************/
/* procedure proc_opmult         */
/*********************************/
void proc_opmult()
{
	DEBUGGING  ("...ENTREE proc_opmult\n");
	verifier(stop, us->cl == mult || us->cl == divi || us->cl == pourcent || us->cl == sand, 12);
	switch (us->cl) {
		case mult:
			PRODUIRE1("*");
			break;
		case divi:
			PRODUIRE1("/");
			break;
		case pourcent:
			PRODUIRE1("%");
			break;
		case sand:
			PRODUIRE1("&&");
			break;
		default:
			break;
	}
	prochus();
	DEBUGGING ("......SORTIE proc_opmult\n");	
}

/*********************************/
/* procedure proc_couleur        */
/*********************************/
void proc_couleur()
{
	/* prod */ char* nom_couleur;
	
	DEBUGGING  ("...ENTREE proc_couleur\n");
	verifier(stop, us->cl == ident, 9); 
	/* prod */ nom_couleur= copier(us->nom_id);
	/* prod */ PRODUIRE2("Mulot.%s", nom_couleur);
	prochus();
	DEBUGGING ("......SORTIE proc_couleur\n");
}