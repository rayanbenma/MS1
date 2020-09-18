#pragma hdrstop
#pragma argsused

#ifdef _WIN32
#include <tchar.h>
#else
  typedef char _TCHAR;
  #define _tmain main
#endif

#include <stdio.h>
#include <iostream>
#include <math.h>
#include <sstream>   //pour la class ostrigstream
#include <ctime>
#include <fstream>
#include "SNAfficheur.h"
#include "SNLigne.h"
#include "PortSerieAfficheur.h"
using namespace  std;
int SaisirBinaire()
 {
  char bin[100];

  int nombre = 0;
  cin >> bin;
  cin.get();
  for (int i =0; i < strlen(bin); i++)
  {
	nombre = nombre*2+(bin[i]-'0');
  }
   return nombre;
 }
string EntierVersChaineEnBinaire(int nombre)
 {
   ostringstream oss;
   bool copie = false;
   for (int i=31; i >=0 ; i--)
   {
   if (((nombre >>i)&1) == 1)
   {
   copie = true;
   }
   if (copie == true)
   {
   oss<<((nombre>>i)&1);
	}
  }
   return oss.str();
   }


int _tmain(int argc, _TCHAR* argv[])
{
char phrase [200] ;
int choix,hexa,nb,base;
float valeur1, valeur2, resultat, resultatDeg;
char operateur;
char fonction [10];
char buffer[256];
time_t timestamp = time(NULL);

strftime(buffer, sizeof(buffer), "%A %d %B %Y - %X.", localtime(&timestamp));
printf("%s\n", buffer);


cout << "Calcul (1) , Trigo (2) , Conversion (3) : ";
cin >> choix;
cin.get();

if (choix == 1)
   {

	cout << "Menu Calcul" << endl;

	cout << "saisir l'operation :";
	cin >> valeur1 >> operateur >> valeur2;
	cin.get();

	if (operateur == '+')
   {
	resultat = valeur1 + valeur2;
   }
	else if (operateur == '-')
   {
	resultat = valeur1 - valeur2;
   }
	else if (operateur == '*')
   {
	resultat = valeur1 * valeur2;
   }
	else if (operateur == '/')
   {
	resultat = valeur1 / valeur2;
   }

   sprintf(phrase,"%.3f %c %.3f = %.3f", valeur1, operateur, valeur2, resultat);
 }
	else if (choix == 2)
 {
	cout << "Menu Trigo" << endl;
	cout << "saisir l'operation : ";
	cin >> fonction >> valeur1;
	cin.get();
		if (strcmp(fonction, "cos")==0)
	 {
		resultat = cos ( valeur1 );
	 }
		else if (strcmp(fonction, "sin")==0)
	 {
		resultat = sin ( valeur1 );
	 }
		else if (strcmp(fonction, "tan")==0)
	 {
			resultat = tan ( valeur1 );
	 }

		cout << " Resultat en degres (0) ou radian (1) " <<endl;
		cin >> choix;
		cin.get();
		if (choix ==0) {
		resultat * (3.14/180);
		sprintf(phrase,"%s %.3f = %.3f", fonction ,valeur1, resultat);
  }

 }

else if (choix == 3)
  {
		cout << "Menu conversion" << endl;
		cout << "choix de la base de saisie: Decimal (1),Hexa (2),Binaire(3) ";
		cin>> base ;
		cout<< "Saisir un nombre entier:";
		if (base==1)
		{
		cin>> dec >> nb;
		cin.get();
		}
		if (base==2)
		{
		cin >> hex >>nb;
		cin.get();
		}
		if (base==3)
		{
		 nb=SaisirBinaire();
		}
		cout <<"choix de la base d'affichage: Dec(1) Hexa(2) Bin(3)";
		cin >> base ;
		if (base==1) {
		cout<<"="<< dec <<nb;
		}
		if (base==2)
		{
		cout <<"="<< hex << nb;
		}
		if (base==3)
		{
		cout << EntierVersChaineEnBinaire(nb);
		}


  }
  cout<< buffer ;
  ofstream fichier ;
  fichier.open("calculatrice log");
  fichier << buffer << phrase;
  fichier.close();

  SNAfficheur aff;
  aff.ModifierAdresseIPDuServeurUDP("172.20.182.57");
  aff.ModifierPortDuServeurUDP(4321);
  SNLigne lg;
  lg.ModifierMessage(phrase);
  aff.EnvoyerLigneEnUDP(lg);
  cout << "la  phrase est "<< phrase ;

cin.get(); cin.get(); cin.get();
return 0;

}
