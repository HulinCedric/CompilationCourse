/*****************************************************************/
/*   mulot_util.h : Procedures utilitaires pour un compilateur   */
/*   I.U.T. de Nice - Departement Informatique - L. Brenac       */
/*                 - MODULE DE DEFINITION -                      */
/*****************************************************************/

#ifdef DEBUG
#define DEBUGGING(x)  printf(x)
#define DEBUGGING2(x,y)  printf(x,y)
#define DEBUGGING3(x,y,z)  printf(x,y,z)
#else
#define DEBUGGING(x)
#define DEBUGGING2(x,y)
#define DEBUGGING3(x,y,z)
#endif

typedef enum { go, stop } fonctionnement; /* fonctionnement de `verifier' */ 

extern int yylex();
extern unit_synt* us;     /* variable globale partagee avec lex et synt */
extern int compteurligne; /* variable globale partagee avec synt */

/******************************/
/* procedure init_mulot      */
/******************************/
void  init_mulot ();
	  /* A appeler en debut de la fonction principale. Initialise la liste des messages d'erreurs 
		a partir du fichier MESSAGES.TXT.
        Format du fichier : Voir modele MESSAGES.TXT.
        Affiche les messages prevus (en mode DEBUG)*/

/******************************/
/* procedure verifier         */
/******************************/
void  verifier (fonctionnement apres_erreur, int predicat, int nomess);
	  /* Si le predicat est faux, affiche le message d'erreur de numero 
        `nomess'.   Pour ajouter un nouveau message, ajouter une ligne au 
        fichier `MESSAGES.TXT'.
        Si fonctionnement = stop -> arret du programme 
        Si fonctionnement = go   -> retour a l'appelant                   */

/*********************************/
/* procedure prochus             */
/*********************************/
void prochus ();
	  /* Place dans la variable globale us, la description de la nouvelle */
	  /* unite syntaxique reconnue en entree. Gere le comptage de ligne.  */
	  /* Intercepte la fin du fichier d'entree.                           */

/*********************************/
/* procedure proc_defroutine     */
/*********************************/
void proc_defroutine();

/*********************************/
/* procedure proc_deffonc		 */
/*********************************/
void proc_deffonc();

/*********************************/
/* procedure proc_defproc        */
/*********************************/
void proc_defproc();

/*********************************/
/* procedure proc_facteur        */
/*********************************/
void proc_facteur();

/*********************************/
/* procedure proc_terme			 */
/*********************************/
void proc_terme();

/*********************************/
/* procedure proc_exprsimple     */
/*********************************/
void proc_exprsimple();

/*********************************/
/* procedure proc_expr			 */
/*********************************/
void proc_expr();

/*********************************/
/* procedure proc_signature      */
/*********************************/
void proc_signature();

/*********************************/
/* procedure proc_listparam      */
/*********************************/
void proc_listparam();

/*********************************/
/* procedure proc_listinst       */
/*********************************/
void proc_listinst();

/*********************************/
/* procedure proc_defparam       */
/*********************************/
void proc_defparam();

/*********************************/
/* procedure proc_oprel          */
/*********************************/
void proc_oprel();

/*********************************/
/* procedure proc_opadd			 */
/*********************************/
void proc_opadd();

/*********************************/
/* procedure proc_opmult         */
/*********************************/
void proc_opmult();

/*********************************/
/* procedure proc_couleur        */
/*********************************/
void proc_couleur();

/*********************************/
/* procedure proc_inst           */
/*********************************/
void proc_inst();