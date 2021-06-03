/**************************************************************/
/*			pilote.c										  */
/*    I.U.T. de Nice - Departement Informatique - L. Brenac   */
/*                                                            */
/**************************************************************/

extern int yylex();
int nblignes=0;


main()
{
  int r=0;
  do{
		r = yylex(); 
  }while (r != 1);
  printf("Fin de fichier atteinte : %d lignes \n", nblignes);
}