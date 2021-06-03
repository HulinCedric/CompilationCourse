/*****************************************************************/
/*             UNE TABLE DES SYMBOLES POUR MULOT                 */
/*                                                               */
/*   I.U.T. de Nice - Departement Informatique - L. Brenac       */
/*                                                               */
/*                    MODULE D'IMPLEMENTATION                    */
/*****************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "mulot_tds.h"

void InitSemantique ()
{
     pt_ent  = (description*) malloc (sizeof(description));
	 if (pt_ent == NULL) { printf("pb alloc mem\n"); exit(1);}
     pt_ent->nature = entier;
     
	 pt_mulot  = (description*) malloc (sizeof(description));
	 if (pt_mulot == NULL) { printf("pb alloc mem\n"); exit(1);}
     pt_mulot->nature = mulot;
     
	 pt_erreur = (description*) malloc (sizeof(description));
	 if (pt_erreur == NULL) { printf("pb alloc mem\n"); exit(1);}
     pt_erreur->nature = erreur_semantique;
} 

void InsererIdent ( pt_pt_identif tete, char* nom, genres genre, struct DESCRIPTION *descr)
{
	pt_pt_identif adr_elem_courant; 
	adr_elem_courant = tete;
	while ( *adr_elem_courant != NULL)
		adr_elem_courant = &((*adr_elem_courant)->suivant);
	*adr_elem_courant =  ( identif *) malloc (sizeof(identif));
	if (*adr_elem_courant == NULL) { printf("pb alloc mem\n"); exit(1);}
	(*adr_elem_courant)->nom=copier(nom);
	(*adr_elem_courant)->genre = genre;
	(*adr_elem_courant)->descr = descr;
	(*adr_elem_courant)->suivant = NULL;
}

pt_identif ChercherIdent ( pt_identif tete, char* nom )
{ 
  pt_identif adr_elem_courant; 
  int r;
  adr_elem_courant = tete;
  while (adr_elem_courant != NULL)
  {
	  r = strcmp(nom, adr_elem_courant->nom);
	  if (r == 0) return adr_elem_courant;
	  else adr_elem_courant = adr_elem_courant->suivant;
  }
  return NULL;
}
  
void afficher_identif (pt_identif elem)
{
	if (elem != NULL) 
    {
		if (elem->genre == parametre)
		{
			fprintf (stderr, "==> PARTIE IDENTIFICATION ( %d ) PARAM. %s ", elem, elem->nom);
		}
		else
		{
			fprintf (stderr, "==> PARTIE IDENTIFICATION ( %d ) ", elem);
			switch (elem->genre)
			{
				case variable : { fprintf (stderr, "VARIABLE %s DESCR. |-->...\n", elem->nom); break;}
				case routine : { fprintf (stderr, "ROUT. %s DESCR. |-->...\n", elem->nom); break;}
			}
		}
		afficher_descr (elem->descr);
		afficher_identif (elem->suivant);
   }
}

void afficher_descr  (struct DESCRIPTION * descripteur)
{
   char *fleche;
   fleche = (char*) malloc (40);
   if (descripteur != NULL)
   {
	   strcpy (fleche, "...---> ");
	   switch (descripteur->nature)
	   {
		   case erreur_semantique :
				fprintf (stderr, "%s( %d ) ERREUR SEMANTIQUE\n", fleche, descripteur);
				break;
		   case entier :
				fprintf (stderr, "%s( %d ) entier\n", fleche, descripteur);
				break;
		   case mulot :
				fprintf (stderr, "%s( %d ) mulot\n", fleche, descripteur);
				break;
		   case proc_fonc :
			   if (descripteur->resultat != NULL)
				{
					fprintf (stderr, "%s( %d ) FONCTION\n\tType du resultat DESCR. |-- ", fleche, descripteur);
					afficher_descr(descripteur->resultat);
				}
				else /*procedure */
				{
					fprintf (stderr, "%s( %d ) PROCEDURE\n", fleche, descripteur);
				}
				afficher_identif(descripteur->acces_params);
				fprintf (stderr, "                    FIN DE PROC/FONCT\n");
				break;
	   }
	}
}  

char * copier (char * source)
{
	char * dest;
	dest = (char *) malloc ((strlen(source) + 1)*sizeof(char));
	if (dest == NULL) { printf("pb alloc mem\n"); exit(1);}
	dest[0] = '\0';
	strcpy(dest, source);
	return dest;
}