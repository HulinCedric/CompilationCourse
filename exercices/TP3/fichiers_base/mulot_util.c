/*****************************************************************/
/*   mulot_util.c : Procedures utilitaires pour un compilateur  */
/*   I.U.T. de Nice - Departement Informatique - L. Brenac       */
/*                 - MODULE D'IMPLEMENTATION                     */
/*****************************************************************/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include "mulot_us.h"
#include "mulot_util.h"

#ifdef LINE
	#define DEBUG_LINE(x,y)  fprintf(stderr, x,y)
#else
	#define DEBUG_LINE(x,y)
#endif

typedef struct{
	int num; 
	char lib[80];
}mess_item;

static mess_item lib_mess[100];
char chaine[80];
int nb_mess;

/******************************/
/* procedure init_mulot       */
/******************************/
void  init_mulot ()
{
	FILE *messages; 
	char c; 
	int i, j; 
	char* nomfichier; 
	char* str_numero;

	DEBUGGING  ("\n MESSAGES D'ERREUR PREVUS\n\n");
	
	/* Recuperation du fichier des messages d'erreurs */
	nomfichier = (char*) malloc(200 * sizeof(char));
	strcpy(nomfichier, "..\\..\\MESSAGES.TXT");
	fopen_s(&messages, nomfichier, "r");
	if (messages == NULL)
	{
		fprintf (stderr, "%s %s\n", "ERREUR FATALE : Fichier de messages d'erreur", "`MESSAGES.TXT' absent ou illisible."); 
		exit (1);
	}
	else
	{ 
		str_numero = (char*) malloc (80*sizeof(char));
		i = 0; 
		c = fgetc(messages); 
		while ( c != EOF)
		{ 
			/* Recuperation d'une ligne */
			j=0;
			while (c != '\n')
			{ 
				chaine[j]= c; j++;
				c = fgetc(messages); 
			}
			chaine[j] = '\0';
			/* Traitement de la ligne */
			if ( chaine[0] != '#' ) 
			{
				/* Si la ligne n'est pas un commentaire */
				sscanf (chaine, "%s", str_numero);
				lib_mess[i].num = atoi(str_numero);  
				strcpy (lib_mess[i].lib, chaine+strlen(str_numero));
				DEBUGGING3  ("(%d) - %s\n", lib_mess[i].num, lib_mess[i].lib);
				i++;
			}
			/* Lecture 1er car ligne suivante */
			c = fgetc(messages); 
		}
	}
	nb_mess = i;
	DEBUGGING2  ("\n FIN DES MESSAGES D'ERREURS (%d messages)\n\n", nb_mess);
}

/******************************/
/* procedure verifier         */
/******************************/
void  verifier (fonctionnement apres_erreur, int predicat, int nomess)
{
	int i = 0; 
	int sortie = 0, ok = 0;
	if ( !predicat )
	{ 
		while (!sortie)
		{
			 if (lib_mess[i].num == nomess)
			 { ok = 1; sortie = 1;}
			 else i++;
			 if (i == nb_mess) sortie = 1;
		}
		if (ok) 
		  /* Si message trouve' */
		  fprintf (stderr, "*** Ligne %d :%s (No %d) ***\n", compteurligne, lib_mess[i].lib, lib_mess[i].num);
		else 
		  /* Si message non trouve' */
			fprintf (stderr, "*** Ligne %d : ERREUR - PREVOIR UN MESSAGE POUR No %d ***\n", compteurligne, nomess);
		
		if (apres_erreur == stop) 
			exit(1);
	}  
}

/*********************************/
/* procedure prochus             */
/*********************************/
void  prochus ()
{
	do
	{
		yylex();
		if (us->cl == nouvelle_ligne)
		{
			compteurligne = compteurligne + 1;
			DEBUGGING2 ("\n LIGNE NUMERO %d\n\n", compteurligne);
			DEBUG_LINE ("\t\t\t\t/* LIGNE %d */\n", compteurligne);
		}
	}while (us->cl == nouvelle_ligne);

	/* interception de la fin de fichier detectee par yylex */
	verifier  (stop, us->cl != fin_flot, 999);
}

