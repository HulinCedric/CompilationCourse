/*****************************************************************/
/*   us_mulot.h : Definitions standards pour un compilateur      */
/*   I.U.T. de Nice - Departement Informatique - L. Brenac       */
/*****************************************************************/

typedef enum {
	smulot, stolum, sproc, scorp, sfonc, scnof, sreturn, sint, snew, sleve, sbaisse, stourne, savance, 
	spour, sa, sruop, stantque, stnat, ssi, salors, ssinon, sis, 
	cst_ent, ident, nouvelle_ligne, fin_flot, point, sbidon,
	snot, sor, sand, pvirg, virg, pargau, pardroi, egal, notegal, egalegal,
	osup, oinf, osug, oing, plus, moins, divi, mult, pourcent 
}classus;

typedef struct{ 
	classus  cl;
	union {
		char * nomid;     /* cas `ident' : identificateur */
		int valent;      /* cas `cst_ent' : valeur entiere */
		}cas;
}unit_synt;

typedef struct {
	char * chaine; 
	classus cl;
}mot_cle;

# define nom_id cas.nomid
# define val_ent cas.valent
