/*****************************************************************/
/*   Analyseur syntaxique/semantique pour le langage Mulot       */
/*   I.U.T. de Nice - Departement Informatique - C. Hulin        */
/*   analyseur_rout.c                                            */
/*****************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include "mulot_us.h"
#include "mulot_util.h"
#include "mulot_tds.h"

extern int yylex();
extern unit_synt* us; /* variable globale partagee avec lex */
extern int compteurligne;
/* sema */ extern pt_identif  tds[10];
/* sema */ extern int returnFonc;
/* sema */ void proc_inst(int n);

/*********************************/
/* procedure proc_listinst      */
/********************************/
void proc_listinst(int n)
{
	DEBUGGING2  ("...ENTREE proc_listinst routine %d\n",n);
	while (us->cl == ident || us->cl == spour || us->cl == stantque || us->cl == ssi 
		|| us->cl == sint || us->cl == smulot || us->cl == sreturn)
	{
		proc_inst(n);
	}
	DEBUGGING ("......SORTIE proc_listinst\n");
}

/*********************************/
/* procedure proc_defparam       */
/*********************************/
description* proc_defparam(int n, description* descr)
{
	description* descr2;
	char* nom_param;
	pt_identif temp;
	
	DEBUGGING  ("...ENTREE proc_defparam\n");
	verifier (stop, us->cl == sint || us->cl == smulot, 8);
	
	// Recupere le type du parametre
	//
	if (us->cl == sint) descr= pt_ent;
	else descr= pt_mulot;
	
	prochus(); 
	verifier (stop, us->cl == ident, 4);
	
	// Recupere le nom du parametre
	//
	nom_param= copier(us->nom_id);
	
	// Verifie qu'il existe pas encore dans la liste des parametres
	//
	temp= ChercherIdent(descr->acces_params, nom_param);
	verifier(go, temp == NULL, 1004);
	
	// Insere le paramètre dans la liste
	//
	if (temp == NULL) InsererIdent(&(descr->acces_params), nom_param, parametre, descr2);
	prochus();
	DEBUGGING ("......SORTIE proc_defparam\n");
	return descr;
}

/*********************************/
/* procedure proc_listparam      */
/*********************************/
description* proc_listparam(int n)
{
	//Initialise la liste des parametres
	//
	description* descr= (description*)malloc(sizeof(description));
	descr->acces_params= NULL;
	DEBUGGING  ("...ENTREE proc_listparam\n");
	descr= proc_defparam(n, descr);
	while (us->cl == virg)
	{
		prochus();
		descr= proc_defparam(n, descr);
	}
	DEBUGGING ("......SORTIE proc_listparam\n");
	return descr;
}

/*********************************/
/* procedure proc_signature      */
/*********************************/
description* proc_signature(int n)
{
	description* descr;
	DEBUGGING  ("...ENTREE proc_signature\n");
	verifier (stop, us->cl == pargau, 5);
	prochus();
	if (us->cl == sint || us->cl == smulot)	descr= proc_listparam(n);
	verifier (stop, us->cl == pardroi, 6);
	prochus(); 
	DEBUGGING ("......SORTIE proc_signature\n");
	return descr;
}

/*********************************/
/* procedure proc_deffonc        */
/*********************************/
void proc_deffonc(int n)
{
	char * nom_routine; 
	description * descr; 
	pt_identif temp; 
	DEBUGGING  ("...ENTREE proc_deffonc\n");
	verifier (stop, us->cl == sfonc, 3);
	prochus(); 
	verifier (stop, us->cl == ident, 4);
	prochus();
	
	// Recupere le nom de la fonction
	//
	nom_routine = copier(us->nom_id); 
	
	// Recupere la description de la fonction
	//
	descr= proc_signature(n);
	
	// Initialiser le retour de la fonction en entier
	//
	descr->resultat = pt_ent;
	
	// Verifier que la fonction n'existe pas deja
	//
	temp = ChercherIdent ( tds[0], nom_routine );
	verifier (go, temp == NULL, 1009);
	
	//Insere la description de la fonction
	//
	if (temp == NULL)	InsererIdent(&(tds[0]),nom_routine,routine,descr);

	verifier (stop, us->cl == egal, 10);
	prochus(); 
	verifier (stop, us->cl == sint, 24);
	prochus();
	if (us->cl == ident || us->cl == spour || us->cl == stantque || us->cl == ssi || us->cl == sint || us->cl == smulot || us->cl == sreturn)
		proc_listinst(n);
	
	// Verifier que la fonction retourne bien un resultat
	// a la fin de celle-ci
	//
	verifier (go, returnFonc == 1, 1010);
	returnFonc= 0;
	
	verifier (stop, us->cl == scnof, 25);
	
	prochus();
	DEBUGGING ("......SORTIE proc_deffonc\n");
}

/*********************************/
/* procedure proc_defproc        */
/*********************************/
void proc_defproc(int n) 
{	
	char * nom_routine; 
	description * descr; 
	pt_identif temp; 
	DEBUGGING ("...ENTREE proc_defproc\n"); 
	verifier (stop, us->cl == sproc, 3); 
	prochus();
	verifier (stop, us->cl == ident, 4); 
	prochus(); 
	
	// Recupere le nom de la procedure
	//
	nom_routine = copier(us->nom_id); 
	
	// Recupere la description de la procedure
	//
	descr = proc_signature(n);
	
	// Pas de retour sur les procedures
	//
	descr->resultat = NULL;
	
	// Verifier que la procedure n'existe pas deja
	//
	temp = ChercherIdent ( tds[0], nom_routine );
	verifier (go, temp == NULL, 1008);
	
	// Insere la description de la procedure
	//
	if (temp == NULL)	InsererIdent(&(tds[0]),nom_routine,routine,descr);

	
	if (us->cl == ident || us->cl == spour || us->cl == stantque || us->cl == ssi || us->cl == sint || us->cl == smulot)
	{
		proc_listinst(n);
	}
	verifier (stop, us->cl == scorp, 7);
	prochus();
	DEBUGGING ("......SORTIE proc_defproc\n");
}

/*********************************/
/* procedure proc_defroutine     */
/*********************************/
void proc_defroutine(int n)
{
	DEBUGGING  ("...ENTREE proc_defroutine\n");
	tds[n] = NULL;
	if (us->cl == sproc) proc_defproc(n);
	else proc_deffonc(n);
	DEBUGGING ("......SORTIE proc_defroutine\n");
}