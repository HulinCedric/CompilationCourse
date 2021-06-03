/*****************************************************************/
/*   Analyseur syntaxique pour le langage Mulot                  */
/*   I.U.T. de Nice - Departement Informatique - L.Brenac        */
/*   analyseur_inst.c                                            */
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
/* procedure proc_listparam      */
/*********************************/
void proc_listparam()
{
	DEBUGGING ("...ENTREE proc_listparam\n");
	proc_defparam();
	while (us->cl == virg){
		
		verifier (stop, us->cl == virg, 9); 
		prochus();
		/* prod */ PRODUIRE1(", ");
		proc_defparam();
	}
	DEBUGGING ("......SORTIE proc_listparam\n");
}

/*********************************/
/* procedure proc_signature      */
/*********************************/
void proc_signature()
{
	DEBUGGING ("...ENTREE proc_signature\n"); 
	verifier (stop, us->cl == pargau, 13); 
	prochus(); 
	/* prod */ PRODUIRE1("(");
	if (us->cl == sint || us->cl == smulot){
		proc_listparam(); 
		/* prod */ PRODUIRE1(", ");
	}
	verifier (stop, us->cl == pardroi, 14); 
	/* prod */ PRODUIRE1("Graphics g)");
	prochus();
	DEBUGGING ("......SORTIE proc_signature\n");
}

/*********************************/
/* procedure proc_inst           */
/*********************************/
void proc_inst()
{
	/* prod */ char* nom_variable;
	
	DEBUGGING ("...ENTREE proc_inst\n");
	verifier (stop, us->cl == ssi || us->cl == stantque || us->cl == spour || us->cl == sint || us->cl == smulot || us->cl == ident || us->cl == sreturn, 15);
	switch (us->cl) {
			
		case ssi:
			/* prod */ PRODUIRE1("if ");
			prochus();
			verifier (stop, us->cl == pargau, 13); 
			/* prod */ PRODUIRE1(" (");
			prochus();
			proc_expr();
			verifier (stop, us->cl == pardroi, 14);
			/* prod */ PRODUIRE1(")");
			prochus();
			verifier (stop, us->cl == salors, 16);
			/* prod */ PRODUIRE1(" {\n");
			prochus();
			proc_listinst();
			if (us->cl == ssinon) {
				verifier (stop, us->cl == ssinon, 17);
				/* prod */ PRODUIRE1("}\nelse {\n");
				prochus();
				proc_listinst();
			}
			verifier (stop, us->cl == sis, 19);
			/* prod */ PRODUIRE1("}\n");
			prochus();
			break;
			
		case stantque:
			/* prod */ PRODUIRE1("while ");
			prochus();
			verifier (stop, us->cl == pargau, 13); 
			/* prod */ PRODUIRE1("(");
			prochus();
			proc_expr();
			verifier (stop, us->cl == pardroi, 14);
			/* prod */ PRODUIRE1(") {\n");
			prochus();
			proc_listinst();
			verifier (stop, us->cl == stnat, 20); 
			/* prod */ PRODUIRE1("}\n");
			prochus();
			break;

		case spour:
			/* prod */ PRODUIRE1("for (");
			prochus();
			if (us->cl == sint) 
			{
				verifier (stop, us->cl == sint, 8);
				/* prod */ PRODUIRE1("int ");
				prochus();
			}
			verifier (stop, us->cl == ident, 4);
			/* prod */ nom_variable = copier(us->nom_id);
			/* prod */ PRODUIRE2("%s",nom_variable);
			prochus();
			verifier (stop, us->cl == egal, 7);
			/* prod */ PRODUIRE1(" = ");
			prochus();
			proc_expr();
			/* prod */ PRODUIRE1(" ; ");
			verifier (stop, us->cl == sa, 21);
			/* prod */ PRODUIRE2("%s <= ", nom_variable);
			prochus();
			proc_expr();
			/* prod */ PRODUIRE2(" ; %s++) {\n", nom_variable);
			proc_listinst();
			verifier (stop, us->cl == sruop, 22);
			/* prod */ PRODUIRE1("}\n");
			prochus();
			break;
			
		case sint:
			/* prod */ PRODUIRE1("int ");
			prochus();
			verifier (stop, us->cl == ident, 4);
			/* prod */ nom_variable = copier(us->nom_id);
			/* prod */ PRODUIRE2("%s",nom_variable);
			prochus();
			if (us->cl == egal) 
			{
				verifier (stop, us->cl == egal, 7);
				/* prod */ PRODUIRE1("= ");
				prochus();
				proc_expr();
			}
			verifier (stop, us->cl == pvirg, 23);
			/* prod */ PRODUIRE1(";\n");
			prochus();
			break;
		
		case smulot:
			/* prod */ PRODUIRE1("Mulot ");
			prochus();
			verifier (stop, us->cl == ident, 4);
			/* prod */ nom_variable = copier(us->nom_id);
			/* prod */ PRODUIRE2("%s",nom_variable);
			prochus();
			if (us->cl == egal) 
			{			
				verifier (stop, us->cl == egal, 7);
				/* prod */ PRODUIRE1("= ");
				prochus();
				verifier (stop, us->cl == snew, 24);
				/* prod */ PRODUIRE1("new ");
				prochus();
				verifier (stop, us->cl == smulot, 1);
				/* prod */ PRODUIRE1("Mulot");
				prochus();
				verifier (stop, us->cl == pargau, 13);
				/* prod */ PRODUIRE1("(");
				prochus();
				if (us->cl == plus || us->cl == moins || us->cl == ident || us->cl == cst_ent || us->cl == snot || us->cl == pargau) 
				{
					proc_expr();
					verifier (stop, us->cl == virg, 9);
					/* prod */ PRODUIRE1(", ");
					prochus();
					proc_expr();
					/* prod */ PRODUIRE1(", ");
					if (us->cl == virg)
					{
						verifier (stop, us->cl == virg, 9);
						prochus();
						proc_couleur();
						/* prod */ PRODUIRE1(", ");
						if (us->cl == virg) 
						{
							verifier (stop, us->cl == virg, 9);
							prochus();
							proc_expr();
							/* prod */ PRODUIRE1(", ");
						}
					}
				}
				verifier (stop, us->cl == pardroi, 14);
				/* prod */ PRODUIRE1("g)");
				prochus();
			}
			verifier (stop, us->cl == pvirg, 23);
			/* prod */ PRODUIRE1(";\n");
			prochus();
			break;
			
		case ident:
			/* prod */ nom_variable = copier(us->nom_id);	
			/* prod */ PRODUIRE2("%s", nom_variable);
			prochus();
			verifier (stop, us->cl == point || us->cl == egal || us->cl == pargau || us->cl == pvirg, 13);
			if (us->cl == point) 
			{
				/* prod */ PRODUIRE1(".");
				prochus();
				verifier (stop, us->cl == sleve || us->cl == sbaisse || us->cl == stourne || us->cl == savance, 25);
				if (us->cl == sleve || us->cl == sbaisse) 
				{
					if (us->cl == sleve) 
					/* prod */ PRODUIRE1("leve");
					else 
					/* prod */ PRODUIRE1("baisse");
					prochus();
					verifier (stop, us->cl == pargau, 13);
					/* prod */ PRODUIRE1("(");
					prochus();
					verifier (stop, us->cl == pardroi, 14);
					/* prod */ PRODUIRE1("g)");
					prochus();
				}
				else 
				{
					if (us->cl == stourne || us->cl == savance)
					{
						if (us->cl == stourne) 
						/* prod */ PRODUIRE1("tourne");
						else 
						/* prod */ PRODUIRE1("avance");
						prochus();
						verifier (stop, us->cl == pargau, 13);
						/* prod */ PRODUIRE1("(");
						prochus();
						proc_expr();
						verifier (stop, us->cl == pardroi, 14);
						/* prod */ PRODUIRE1(", g)");
						prochus();
					}
				}
			}
			else 
			{
				if (us->cl == egal) 
				{
					/* prod */ PRODUIRE1("= ");
					prochus();
					verifier (stop, us->cl == snew || us->cl == plus || us->cl == moins || us->cl == ident || us->cl == cst_ent || us->cl == snot || us->cl == pargau, 0);
					if (us->cl == snew) 
					{
						/* prod */ PRODUIRE1("new ");
						prochus();
						verifier (stop, us->cl == smulot, 1);
						/* prod */ PRODUIRE1("Mulot");
						prochus();
						verifier (stop, us->cl == pargau, 13);
						/* prod */ PRODUIRE1("(");
						prochus();
						if (us->cl == plus || us->cl == moins || us->cl == ident || us->cl == cst_ent || us->cl == snot || us->cl == pargau) 
						{
							proc_expr();
							verifier (stop, us->cl == virg, 9);
							/* prod */ PRODUIRE1(", ");
							prochus();
							proc_expr();
							/* prod */ PRODUIRE1(", ");
							if (us->cl == virg)
							{
								verifier (stop, us->cl == virg, 9);
								prochus();
								proc_couleur();
								/* prod */ PRODUIRE1(", ");
								if (us->cl == virg) 
								{
									verifier (stop, us->cl == virg, 9);
									prochus();
									proc_expr();
									/* prod */ PRODUIRE1(", ");
								}
							}
						}
						verifier (stop, us->cl == pardroi, 13);
						/* prod */ PRODUIRE1("g)");
						prochus();
					}
					else 
					{
						if (us->cl == plus || us->cl == moins || us->cl == ident || us->cl == cst_ent || us->cl == snot || us->cl == pargau) 
						{
							proc_expr();
						}
					}
				}
				else
				{
					if (us->cl == pargau) 
					{
						/* prod */ PRODUIRE1("(");
						prochus();
						proc_expr();
						while (us->cl == virg)
						{
							verifier (stop, us->cl == virg, 9);
							/* prod */ PRODUIRE1(", ");
							prochus();
							proc_expr();
						}
						verifier (stop, us->cl == pardroi, 14);
						/* prod */ PRODUIRE1(", g)");
						prochus();
					}
				}
			}
			verifier (stop, us->cl == pvirg, 23);
			/* prod */ PRODUIRE1(";\n");
			prochus();
			break;
			
		case sreturn:
			/* prod */ PRODUIRE1("return ");
			prochus();
			proc_expr();
			verifier (stop, us->cl == pvirg, 23);
			/* prod */ PRODUIRE1(";\n");
			prochus();
			break;
			
		default:
			break;
	}
	DEBUGGING ("......SORTIE proc_inst\n");
}

/*********************************/
/* procedure proc_expr           */
/*********************************/
void proc_expr()
{
	DEBUGGING  ("...ENTREE proc_expr\n");
	proc_exprsimple();
	while (us->cl == egalegal || us->cl == notegal || us->cl == oing || us->cl == osug || us->cl == oinf || us->cl == osup)
	{
		proc_oprel();
		proc_exprsimple();
	}
	DEBUGGING ("......SORTIE proc_expr\n");
}

/*********************************/
/* procedure proc_exprsimple     */
/*********************************/
void proc_exprsimple()
{
	DEBUGGING  ("...ENTREE proc_exprsimple\n");
	if (us->cl == plus || us->cl == moins)
	{
		verifier(stop, us->cl == plus || us->cl == moins , 26);
		if (us->cl == plus) 
		/* prod */ PRODUIRE1("+");
		else
		/* prod */ PRODUIRE1("-");
		prochus();
	}
	proc_terme();
	while (us->cl == plus || us->cl == moins || us->cl == sor)
	{
		proc_opadd();
		proc_terme();
	}
	DEBUGGING ("......SORTIE proc_exprsimple\n");
}

/*********************************/
/* procedure proc_terme          */
/*********************************/
void proc_terme()
{
	DEBUGGING  ("...ENTREE proc_terme\n");
	proc_facteur(); 
	while (us->cl == mult || us->cl == divi || us->cl == pourcent || us->cl == sand)
	{
		proc_opmult();
		proc_facteur(); 
	}
	DEBUGGING ("......SORTIE proc_terme\n");
}

/*********************************/
/* procedure proc_facteur        */
/*********************************/
void proc_facteur()
{
	/* prod */ char* nom_variable;
	
	DEBUGGING  ("...ENTREE proc_facteur\n");
	verifier(stop, us->cl == cst_ent || us->cl == ident || us->cl == pargau || us->cl == snot , 26);
	if (us->cl == pargau || us->cl == snot) 
	{
		if (us->cl == snot) 
		{
			prochus();
			/* prod */ PRODUIRE1("!");
			verifier(stop, us->cl == pargau, 13);
		}
		prochus();
		/* prod */ PRODUIRE1("(");
		proc_expr();
		verifier(stop, us->cl == pardroi, 14);
		/* prod */ PRODUIRE1(")");
		prochus();
	}
	else 
	{	
		if (us->cl == cst_ent)
		{
			/* prod */ nom_variable= (char*) malloc(sizeof (char)*10);
			/* prod */ itoa(us->val_ent, nom_variable);
			/* prod */ PRODUIRE2("%s", nom_variable);
			prochus();
		}
		else
		{
			if (us->cl == ident) 
			{
				/* prod */ nom_variable = copier(us->nom_id);
				/* prod */ PRODUIRE2("%s",nom_variable);
				prochus();
				if (us->cl == pargau) 
				{
					verifier(stop, us->cl == pargau, 13);
					/* prod */ PRODUIRE1("(");
					prochus();
					if (us->cl == plus || us->cl == moins || us->cl == ident || us->cl == cst_ent || us->cl == snot || us->cl == pargau) 
					{
						proc_expr();
						while (us->cl == virg)
						{
							verifier (stop, us->cl == virg, 9);
							/* prod */ PRODUIRE1(", ");
							prochus();
							proc_expr();
						}
					}
					verifier (stop, us->cl == pardroi, 14);
					/* prod */ PRODUIRE1(")");
					prochus();
				}
			}
		}
	}
	DEBUGGING ("......SORTIE proc_facteur\n");
}