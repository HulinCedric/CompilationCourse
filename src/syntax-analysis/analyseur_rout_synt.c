/*****************************************************************/
/*   Analyseur pour le langage Mulot                             */
/*   I.U.T. de Nice - Departement Informatique - C. Hulin        */
/*   analyseur_rout.c                                            */
/*****************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include "mulot_us.h"
#include "mulot_util.h"

extern int yylex();
extern unit_synt* us; /* variable globale partagee avec lex */
extern int compteurligne;

/*********************************/
/* procedure proc_listinst      */
/********************************/
void proc_listinst()
{
	DEBUGGING  ("...ENTREE proc_listinst\n");
	while (us->cl == smulot || us->cl == ident || us->cl == sint || us->cl == spour || us->cl == stantque || us->cl == ssi || us->cl == sreturn)
		proc_inst();
	DEBUGGING ("......SORTIE proc_listinst\n");
}

/*********************************/
/* procedure proc_defparam       */
/*********************************/
void proc_defparam()
{
	DEBUGGING  ("...ENTREE proc_defparam\n");
	verifier (stop, us->cl == sint || us->cl == smulot, 8); prochus(); 
	verifier (stop, us->cl == ident, 4); prochus();
	DEBUGGING ("......SORTIE proc_defparam\n");
}

/*********************************/
/* procedure proc_listparam      */
/*********************************/
void proc_listparam()
{
	DEBUGGING  ("...ENTREE proc_listparam\n");
	proc_defparam();
	while (us->cl == virg) {
		prochus();
		proc_defparam();
	}
	DEBUGGING ("......SORTIE proc_listparam\n");
}

/*********************************/
/* procedure proc_signature      */
/*********************************/
void proc_signature()
{
	DEBUGGING  ("...ENTREE proc_signature\n");
	verifier (stop, us->cl == pargau, 5); prochus();
	if (us->cl == sint || us->cl == smulot)
		proc_listparam();
	verifier (stop, us->cl == pardroi, 6); prochus(); 
	DEBUGGING ("......SORTIE proc_signature\n");
}

/*********************************/
/* procedure proc_deffonc        */
/*********************************/
void proc_deffonc()
{
	DEBUGGING  ("...ENTREE proc_deffonc\n");
	verifier (stop, us->cl == sfonc, 3); prochus(); 
	verifier (stop, us->cl == ident, 4); prochus();
	proc_signature();
	verifier (stop, us->cl == egal, 10); prochus(); 
	verifier (stop, us->cl == sint, 24); prochus();
	if (us->cl == smulot || us->cl == ident || us->cl == sint || us->cl == spour || us->cl == stantque || us->cl == ssi || us->cl == sreturn)
		proc_listinst();
	verifier (stop, us->cl == scnof, 25); prochus();
	DEBUGGING ("......SORTIE proc_deffonc\n");
}
/*********************************/
/* procedure proc_defproc        */
/*********************************/
void proc_defproc()
{
	DEBUGGING  ("...ENTREE proc_defproc\n");
	verifier (stop, us->cl == sproc, 3); prochus(); 
	verifier (stop, us->cl == ident, 4); prochus();
	proc_signature();
	if (us->cl == smulot || us->cl == ident || us->cl == sint || us->cl == spour || us->cl == stantque || us->cl == ssi || us->cl == sreturn)
		proc_listinst();
	verifier (stop, us->cl == scorp, 7); prochus();
	DEBUGGING ("......SORTIE proc_defproc\n");
}

/*********************************/
/* procedure proc_defroutine     */
/*********************************/
void proc_defroutine()
{
	DEBUGGING  ("...ENTREE proc_defroutine\n");
	if (us->cl == sproc) proc_defproc();
	else proc_deffonc();
	DEBUGGING ("......SORTIE proc_defroutine\n");
}

