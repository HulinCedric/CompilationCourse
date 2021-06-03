/*****************************************************************/
/*             UTILITAIRES DE PRODUCTION DE CODE JAVA            */
/*                                                               */
/*   I.U.T. de Nice - Departement Informatique - L. Brenac       */
/*                                                               */
/*                    MODULE DE DEFINITION                       */
/*****************************************************************/

#include <string.h>
#include <stdio.h>

#define PRODUIRE1(x)  fprintf(fic, x)
#define PRODUIRE2(x,y)  fprintf(fic, x, y)
#define PRODUIRE3(x,y,z)  fprintf(fic, x, y, z)
#define COPIER(str,string)  strcpy (str, string)
#define CONCAT_S(str,string)  sprintf (str,"%s%s", str, string)
#define CONCAT_I(str,entier)  sprintf (str,"%s%d", str, entier)
#define CONCAT_C(str,caract)  sprintf (str,"%s%c", str, caract)


extern FILE * fic;
extern char * nom_fichier;

int creer_fichier ();
void produire_entete();
void produire_import();
void produire_debut_applet ();
void produire_fin_applet ();
void fermer_fichier();
void produire_debut_paint_applet();
void produire_fin_paint_applet();
void reverse(char s[]);
void itoa(int n, char s[]);