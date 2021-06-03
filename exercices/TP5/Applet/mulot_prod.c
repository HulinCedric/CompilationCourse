/*****************************************************************/
/*             UTILITAIRES DE PRODUCTION DE CODE JAVA            */
/*                                                               */
/*   I.U.T. de Nice - Departement Informatique - L. Brenac       */
/*                                                               */
/*                    MODULE D'IMPLEMENTATION                    */
/*****************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "mulot_tds.h"
#include "mulot_prod.h"
extern int nbTab;

/* itoa:  convert n to characters in s */
void itoa(int n, char s[])
{
    int i, sign;
	
    if ((sign = n) < 0)  /* record sign */
        n = -n;          /* make n positive */
    i = 0;
    do {       /* generate digits in reverse order */
        s[i++] = n % 10 + '0';   /* get next digit */
    } while ((n /= 10) > 0);     /* delete it */
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
} 


/* reverse:  reverse string s in place */
void reverse(char s[])
{
    int i, j;
    char c;
	
    for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}


int creer_fichier ()
{
	char * chemin = "../../ExemplesProduitsEnJava/";
	char * nom_complet = (char *) malloc(sizeof(char) * (strlen (chemin)+strlen(nom_fichier)+6));
	strcpy(nom_complet, chemin);
	strcat(nom_complet, nom_fichier);
	strcat(nom_complet, ".java");
	fic = fopen(nom_complet, "w");
	if (!fic) return 0;
	return 1;
}
void produire_entete()
{
	PRODUIRE1("/**\n");
	PRODUIRE2("* %s.java\n", nom_fichier);
	PRODUIRE1("* @author C. Hulin\n");
	PRODUIRE1("*/\n");
	PRODUIRE1("\n");
}

void produire_import()
{
	PRODUIRE1("import java.awt.Graphics;\n");
	PRODUIRE1("import java.applet.Applet;\n");
	PRODUIRE1("\n");
}

void produire_debut_applet ()
{
	PRODUIRE1("public class ");
	PRODUIRE2("%s extends Applet\n", nom_fichier); 
	PRODUIRE1("{\n");
}

void produire_fin_applet()
{
	PRODUIRE1("}\n");
}

void produire_debut_paint_applet()
{
	PRODUIRE1("public void paint(Graphics g) {\n");
}

void produire_fin_paint_applet()
{
	PRODUIRE1("}\n");	
}

void fermer_fichier()
{
	fclose (fic);
}