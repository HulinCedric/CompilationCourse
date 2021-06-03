
/*****************************************************************/
/*             UNE TABLE DES SYMBOLES POUR MULOT                 */
/*                    MODULE DE DEFINITION                       */
/*   I.U.T. de Nice - Departement Informatique - L.Brenac        */
/*****************************************************************/
typedef enum { variable, parametre, routine } genres;

typedef struct IDENTIF
{ 
	char * nom;     
	genres genre;
	struct DESCRIPTION * descr;
	struct IDENTIF * suivant;
}identif;

typedef enum { entier, mulot, proc_fonc, erreur_semantique } natures;

typedef struct DESCRIPTION
{ 
	natures nature;
    /* SI procedure ou fonction */
 	struct IDENTIF * acces_params;
	/* si fonction : type du retour = entier */
    struct DESCRIPTION * resultat;
} description;

typedef identif * pt_identif;
typedef pt_identif * pt_pt_identif;

struct DESCRIPTION *pt_ent, *pt_mulot, *pt_erreur; 

extern void InitSemantique ( );
/* role : initialisation des descripteurs globaux */
/*        pt_ent, pt_mulot et pt_erreur*/

extern void InsererIdent ( pt_pt_identif tete, char* nom, genres genre, struct DESCRIPTION *descr);
/* role : insere un element complet dans la table des symboles. 
Suppose que l'element n'est pas deja present                     
*/

extern pt_identif ChercherIdent ( pt_identif tete, char* nom );
/* role : cherche le nom indique dans la table des symboles pointee par tete. 
rend (dans pointeur) l'adresse (si trouve), ou null (si non trouve)
*/

extern void afficher_identif (pt_identif elem);
/* role : affiche (recursivement) sur la sortie d'erreur    */
/* une version textuelle de l'element  */ 

extern void afficher_descr ( struct DESCRIPTION * descripteur);
/* role : affiche (recursivement) sur la sortie d'erreur    */
/* une version textuelle du descripteur  */ 

char * copier (char * source) ;
/* allouer et copier la source */