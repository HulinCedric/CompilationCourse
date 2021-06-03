/*****************************************************************/
/*   Analyseur syntaxique/semantique pour le langage Mulot       */
/*   I.U.T. de Nice - Departement Informatique - C. Hulin        */
/*   analyseur_inst.c                                            */
/*****************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include "mulot_us.h"
#include "mulot_util.h"
#include "mulot_tds.h"

extern int yylex();
extern unit_synt* us; /* variable globale partagee avec lex */
extern int compteurligne;

void proc_expr(int n);
void proc_listinst(int n);

extern pt_identif  tds[10];
void proc_inst(int n);
int returnFonc= 0;

/*********************************/
/* procedure proc_creation       */
/*********************************/
void proc_creation(int n)
{
	DEBUGGING  ("...ENTREE proc_creation\n");
	verifier (stop, us->cl == snew, 20);
	prochus(); verifier (stop, us->cl == smulot, 1);
	prochus(); verifier (stop, us->cl == pargau, 5);	
	prochus(); 
	if (us->cl != pardroi)
	{
		proc_expr(n);
		verifier (stop, us->cl == virg, 21); 
		prochus(); 
		proc_expr(n);
		if (us->cl != pardroi)
		{
			/* couleur */
			verifier (stop, us->cl == virg, 21); 
			prochus();
			verifier (stop, us->cl == ident, 4);
			prochus();
			
			if (us->cl != pardroi)
			{
				/* direction */
				verifier (stop, us->cl == virg, 21); 
				prochus(); 
				proc_expr(n);
			}
		}
		verifier (stop, us->cl == pardroi, 6);
	}
	
	prochus();
	DEBUGGING ("......SORTIE proc_creation\n");
}

/*********************************/
/* procedure proc_action         */
/*********************************/
void proc_action(int n)
{
	DEBUGGING  ("...ENTREE proc_action\n");
	prochus(); verifier (stop, us->cl == sleve || us->cl == sbaisse || us->cl == stourne || us->cl == savance, 19);
	switch(us->cl)
	{
		case sleve :
			prochus(); verifier (stop, us->cl == pargau, 5);
			prochus(); verifier (stop, us->cl == pardroi, 6);
			break;
			
		case sbaisse :
			prochus(); verifier (stop, us->cl == pargau, 5);
			prochus(); verifier (stop, us->cl == pardroi, 6);
			break;
			
		case stourne :
			prochus(); verifier (stop, us->cl == pargau, 5);
			prochus();
			proc_expr(n);
			verifier (stop, us->cl == pardroi, 6);
			break;
			
		case savance :
			prochus(); verifier (stop, us->cl == pargau, 5);
			prochus(); 
			proc_expr(n);
			verifier (stop, us->cl == pardroi, 6);
			break;
	}
	prochus();
	DEBUGGING ("......SORTIE proc_action\n");
}

/*********************************/
/* procedure proc_appelrout      */
/*********************************/
void proc_appelrout(int n)
{
	// nom de la routine appelé
	//
	char* nom_routine;
	
	// Identif de la routine
	//
	pt_identif temp = NULL;
	
	// Identif de la routine appelé
	//
	pt_identif temp2 = NULL;
	
	// nom du parametre courrant
	//
	char* nom_param;
	
	// nombre de parametre de la routine
	//
	int nb_param = 0;
	
	// nombre de parametre passé
	//
	int nb_paramAppel = 0;
	
	DEBUGGING  ("...ENTREE proc_appelrout\n");
	nom_routine = copier(us->nom_id);
	prochus();
	if (us->cl != pardroi)
	{
		// On vérifie le premier paramètre
		//
		temp = ChercherIdent(tds[0], nom_routine);
		if(temp != NULL)	temp = temp->descr->acces_params;
		proc_expr(n);
	
		//On récupére le nom du parametre
		//
		nom_param = copier(us->nom_id);
		
		//On récupére les informations sur le premier parametre
		//
		temp2 = ChercherIdent(tds[n], nom_param);
		nb_paramAppel++;
		
		//Calcul le nombre de parametre
		//
		while(temp != NULL)
		{
			temp = temp->suivant;
			nb_param++;
		}
		temp = ChercherIdent(tds[0], nom_routine);
		
		if(temp != NULL)	temp = temp->descr->acces_params;
		
		
		// On vérifie que le type du parametre est valide
		//
		if(temp != NULL)
		{
			verifier(go, temp2->descr->nature == temp->descr->nature, 1009);
			temp = temp->suivant;
		}
		
		while (us->cl == virg)
		{	
			prochus();
			proc_expr(n);
			nom_param = copier(us->nom_id);
			temp2 = ChercherIdent(tds[n], nom_param);
			
			// On vérifie que le type du parametre est valide
			//
			if(temp != NULL)
			{
				verifier(go, temp2->descr->nature == temp->descr->nature, 1009);
				temp = temp->suivant;
			}
			nb_paramAppel++;
		}
		
		verifier (stop, us->cl == pardroi, 6);
		prochus();
		printf("%d -- %d",nb_param, nb_paramAppel);
		verifier(go, nb_param == nb_paramAppel, 1011);
	}
	DEBUGGING ("......SORTIE proc_appelrout\n");
}

/*********************************/
/* procedure proc_facteur        */
/*********************************/
void proc_facteur(int n)
{
	char* nom_variable;
	pt_identif temp;
	
	DEBUGGING  ("...ENTREE proc_facteur\n");
	verifier (stop, us->cl == pargau || us->cl == snot || us->cl == cst_ent ||us->cl == ident, 17);
	switch(us->cl)
	{
		case pargau :
			prochus();
			proc_expr(n);
			verifier (stop, us->cl == pardroi, 6);
			prochus();
			break;
			
		case snot : 
			prochus();
			proc_expr(n);
			break;
			
		case cst_ent :
			prochus();
			break;
			
		case ident :
			nom_variable = copier(us->nom_id);
			
			//Vérifie dans la TDS courrante
			//
			temp = ChercherIdent(tds[n], nom_variable);                                                   
			
			// Si on trouve pas dans la TDS courrante, on regarde dans les parametres de la fonction
			//
			if(temp == NULL)
			{
				// n != 0 car le main n'a pas de parametre
				//
				if(tds[n] != NULL && n != 0)
				{
					//Vérifie dans les parametres
					//
					if(tds[n]->descr->acces_params != NULL) temp = ChercherIdent(tds[n]->descr->acces_params, nom_variable);
				}
			}	

			verifier(go, temp != NULL, 1007);
			
			prochus();
			if (us->cl == pargau)	proc_appelrout(n);
			
			break;
	}
	DEBUGGING ("......SORTIE proc_facteur\n");
}

/*********************************/
/* procedure proc_terme          */
/*********************************/
void proc_terme(int n)
{
	DEBUGGING  ("...ENTREE proc_terme\n");
	proc_facteur(n); 
	while (us->cl == mult || us->cl == divi || us->cl == pourcent || us->cl == sand)
	{
		prochus();
		proc_facteur(n); 
	}
	DEBUGGING ("......SORTIE proc_terme\n");
}

/*********************************/
/* procedure proc_exprsimple     */
/*********************************/
void proc_exprsimple(int n)
{
	DEBUGGING  ("...ENTREE proc_exprsimple\n");
	if (us->cl == plus || us->cl == moins)
	{
		prochus();
	}
	proc_terme(n);
	while (us->cl == plus || us->cl == moins || us->cl == sor)
	{
		prochus();
		proc_terme(n);
	}
	DEBUGGING ("......SORTIE proc_exprsimple\n");
}

/*********************************/
/* procedure proc_expr           */
/*********************************/
void proc_expr(int n)
{
	DEBUGGING  ("...ENTREE proc_expr\n");
	proc_exprsimple(n);
	if (us->cl == egalegal || us->cl == notegal || us->cl == oing || us->cl == osug || us->cl == oinf || us->cl == osup)
	{
		prochus();
		proc_exprsimple(n);
	}
	DEBUGGING ("......SORTIE proc_expr\n");
}

/*********************************/
/* procedure proc_inst           */
/*********************************/
void proc_inst(int n)
{
	DEBUGGING  ("...ENTREE proc_inst\n");
	verifier (stop, us->cl == ident || us->cl == spour || us->cl == stantque || us->cl == ssi || us->cl == sint
			  || us->cl == smulot || us->cl == sreturn, 9);
	
	switch (us->cl)
	{
			char* nom_variable;
			pt_identif temp;
			
		case sint :
			prochus(); 
			verifier (stop, us->cl == ident, 4);
			
			nom_variable = copier(us->nom_id);
			
			// Vérifie dans la TDS
			//
			temp = ChercherIdent(tds[n], nom_variable);
			if(temp == NULL)
			{
				if(tds[n] != NULL && n != 0)
				{
					// Vérifie dans les parametres
					//
					if(tds[n]->descr->acces_params != NULL)	temp = ChercherIdent(tds[n]->descr->acces_params, nom_variable);
				}
			}
			verifier(go, temp == NULL, 1003);
			if(temp == NULL)
			InsererIdent(&(tds[n]), nom_variable, variable, pt_ent);
			
			prochus(); 
			verifier (stop, us->cl == pvirg || us->cl == egal, 27);
			if (us->cl == egal)
			{
				prochus();
				proc_expr(n);
			}
			
			verifier (stop, us->cl == pvirg, 22);
			prochus();
			break;
			
		case smulot :
			prochus(); 
			verifier (stop, us->cl == ident, 4);
			
			nom_variable = copier(us->nom_id);
			temp = ChercherIdent(tds[n], nom_variable);                            /* Vérifie dans la TDS */
			if(temp == NULL)
			{
				if(tds[n] != NULL && n != 0)
				{
					// Vérifie dans les parametres
					//
					if(tds[n]->descr->acces_params != NULL)	temp = ChercherIdent(tds[n]->descr->acces_params, nom_variable);
				}
			}
			verifier(go, temp == NULL, 1003);
			if(temp == NULL)	InsererIdent(&(tds[n]), nom_variable, variable, pt_mulot);
			
			prochus(); 
			verifier (stop, us->cl == pvirg || us->cl == egal, 27);
			if (us->cl == egal)
			{
				prochus(); verifier (stop, us->cl == snew, 20);
				proc_creation(n);
			}
			
			verifier (stop, us->cl == pvirg, 22);
			prochus();
			break;
			
		case ident :	
			nom_variable = copier(us->nom_id);	
			prochus(); 
			verifier (stop, us->cl == egal || us->cl == point || us->cl == pargau, 18);
			
		   	if(us->cl != pargau)
			{
				// Vérifie dans la TDS
				//
				temp = ChercherIdent(tds[n], nom_variable);
			
				// si on trouve pas dans la TDS courrante, on regarde dans les parametres de la fonction
				//
				if(temp == NULL)
				{
						// n != 0 car le main n'a pas de parametre
						//
						if(tds[n] != NULL && n != 0)
						{
							// Vérifie dans les parametres
							// 
							if(tds[n]->descr->acces_params != NULL)	temp = ChercherIdent(tds[n]->descr->acces_params, nom_variable);	
						}
				}
				printf("nom var : %s niveau : %d", nom_variable, n);

				verifier(go, temp != NULL, 1007);
			}
			
			switch(us->cl)
			{
				case egal :
					prochus(); 
					if (us->cl == snew)proc_creation(n);
					else proc_expr(n);
					break;
				
				case point : 
					proc_action(n);
					break;
				
				case pargau :
					
					// Vérifie dans la TDS global 
					//
					temp = ChercherIdent(tds[0], nom_variable);
					verifier(go, temp != NULL, 1008);
					proc_appelrout(n);
					break;
			}
			
			verifier (stop, us->cl == pvirg, 22);
			prochus();
			break;
			
		case spour :
			prochus(); 
			verifier (stop, us->cl == ident || us->cl == sint, 28);
			if (us->cl == sint)
			{
				prochus();
				nom_variable = copier(us->nom_id);
				
				// Vérifie dans la TDS
				//
				temp = ChercherIdent(tds[n], nom_variable);
				if(temp == NULL)
				{
					if(tds[n] != NULL && n != 0)
					{
						//Vérifie dans les parametres
						//
						if(tds[n]->descr->acces_params != NULL)	temp = ChercherIdent(tds[n]->descr->acces_params, nom_variable);
					}
				}
				verifier(go, temp == NULL, 1003);
				if(temp == NULL)	InsererIdent(&(tds[n]), nom_variable, variable, pt_ent);
			}
			else
			{
				nom_variable = copier(us->nom_id);
				
				//Vérifie dans la TDS
				//
				temp = ChercherIdent(tds[n], nom_variable);
				
				// si on trouve pas dans la TDS courrante, on regarde dans les parametres de la fonction */
				//
				if(temp == NULL)
				{
					// n != 0 car le main n'a pas de parametre
					//
					if(tds[n] != NULL && n != 0)
					{
						// Vérifie dans les parametres
						//
						if(tds[n]->descr->acces_params != NULL) temp = ChercherIdent(tds[n]->descr->acces_params, nom_variable);
					}
				}
				printf("nom var : %s niveau : %d", nom_variable, n);

				verifier(go, temp != NULL, 1007);
			}
			
			prochus(); 
			verifier (stop, us->cl == egal, 10);
			prochus(); 
			proc_expr(n);
			verifier (stop, us->cl == sa, 11);
			prochus(); 
			proc_expr(n);
			
			proc_listinst(n);
			verifier (stop, us->cl == sruop, 12);
			prochus();
			break;
			
		case stantque :
			prochus(); verifier (stop, us->cl == pargau, 5);
			prochus(); 
			proc_expr(n);
			verifier (stop, us->cl == pardroi, 6);
			prochus(); 
			proc_listinst(n);
			verifier (stop, us->cl == stnat, 13);
			prochus();
			break;
			
		case ssi :
			prochus(); verifier (stop, us->cl == pargau, 5);
			prochus(); 
			proc_expr(n);
			verifier (stop, us->cl == pardroi, 6);
			prochus(); verifier (stop, us->cl == salors, 14);
			prochus(); 
			proc_listinst(n);
			verifier (stop, us->cl == ssinon || us-> cl == sis, 15);
			if (us->cl == ssinon)
			{
				prochus(); 
				proc_listinst(n);
			}
			verifier (stop, us->cl == sis, 16);
			prochus();
			break;
			
		case sreturn :
			prochus(); 
			proc_expr(n);
			verifier (stop, us->cl == pvirg, 22);
			prochus();
			returnFonc = 1;
			break;
	}
	DEBUGGING ("......SORTIE proc_inst\n");
}
