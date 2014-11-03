#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include "listed.h"
enum Tip_Comanda {Inscriere, Modificare, Retragere, Note, Ordonare, Afisare, Terminare};
typedef struct Tip_Candidat {
        char nume[30];
        char numar[10];
        int note[3];
        float medie;
        } *pTip_Candidat;
int comanda;
struct LISTA Lista_Candidati, Lista_Ordonata;
bool Trecut_Note = False;
//Defines gotoxy() for ANSI C compilers.
void gotoxy(short x, short y) {
     COORD pos = {x, y};
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void clreol() {
     COORD coord;
     DWORD written;
     CONSOLE_SCREEN_BUFFER_INFO info;
     GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
     coord.X = info.dwCursorPosition.X;
     coord.Y = info.dwCursorPosition.Y;
     FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ',info.dwSize.X - info.dwCursorPosition.X, coord, &written);
     gotoxy(coord.X, coord.Y);
}
//Initializari
void Initializari() { 
     InitializareLista(&Lista_Candidati);
     InitializareLista(&Lista_Ordonata);
}
//Afisare Meniu
void Afisare_Meniu() {
     system("cls");
     gotoxy(10,5);
     printf("1. Inscriere");
     gotoxy(10,7);
     printf("2. Modificare");
     gotoxy(10,9);
     printf("3. Retragere");
     gotoxy(10,11);
     printf("4. Trecere Note");
     gotoxy(10,13);
     printf("5. Ordonare");
     gotoxy(10,15);
     printf("6. Afisare");
     gotoxy(10,17);
     printf("7. Terminare");
     gotoxy(10,20);
     printf("Introduceti numarul comenzii selectate 1..7");
}
//Citire comanda si verificare corectitudine in contextul dat
void Selectie_Validare_Comanda() {
     char sircom[3];
     int nc;
     bool corect;
     corect = False;
     do {
         gotoxy(56,20);
         gets(sircom);
         nc = sircom[0]-'0';
         switch (nc) {
                case 1 :
                     corect = !Trecut_Note;
                     break;
                case 2 :
                case 3 :
                case 4 :
                     corect = !Trecut_Note && !TestListaVida(&Lista_Candidati);
                     break;
                case 5 :
                case 6 :
                     corect = Trecut_Note && !TestListaVida(&Lista_Candidati);
                     break;
                case 7 :
                     corect = True;
                     break;
                default :
                        corect = False;
                        break;
                        };
         if (corect) {
                     comanda = nc - 1;
                     system("cls");
                     }
         else if (nc >= 1 && nc <= 7) {
              printf("Se poate folosi una dintre comenzile:\n");
              switch (2 * Trecut_Note + TestListaVida(&Lista_Candidati)) {
                     case 0 :
                          printf("1 (inscriere) 2 (modificare) 3 (retragere) \n");
                          printf("4 (trecere note) 7(terminare) \n"); 
                          break;
                     case 1 :
                          printf("1 (inscriere) 7(terminare) \n");
                          break;
                     case 2 :
                          printf("5 (ordonare) 6 (afisare) 7(terminare) \n"); 
                          break;
                     case 3 :
                          printf("7(terminare) \n"); 
                          break;
                          };
                     }
              else {
                   clreol();
                   gotoxy(10,24);
                   printf("Comanda inexistenta ! Reluati !");
                   }
     } while (!corect);
}
bool Prezent(struct LISTA *pL, char nume[]) {
//numele dat ca paramentru este cautat in lista L
//daca este gasit, elementul corespunzator din lista devine 
//elementul curent si functia intoarce rezultatul true
bool gasit;
void *x;
if (PozitionareInceput(pL)) {
                            gasit = False;
                            while (!TestSfarsit(pL) && !gasit) {
                                  AdresaInformatie(pL, &x);
                                  gasit = !strcmp(nume, ((pTip_Candidat)x)->nume);
                                  if (!gasit) Urmator(pL);
                                  }
                            return gasit;
                            }
else return False;
}
//1 - Comanda de creare a listei candidatilor
//Datele se introduc de la consola si se termina printr-o linie vida
//Un candidat poate fi inscris o singura data
void Functie_Inscriere() {
     bool b;
     char nume[30];
     char numar[10];
     pTip_Candidat p;
     void *x;
     printf("Lista inscrisi :\n");
     do {
         printf("Nume Prenume : ");
         gets(nume);
         b = True;
         if (nume[0] != '\0') //test terminare introducere
            if (Prezent(&Lista_Candidati, nume))
               printf("Candidat deja inscris !\n");
            else {
                 printf("Numar legitimatie : ");
                 gets(numar);
                 p = (struct Tip_Candidat *) malloc(sizeof(struct Tip_Candidat));
                 strcpy(p->nume, nume);
                 strcpy(p->numar, numar);
                 x = p;
                 b = AdaugaLaSfarsit(&Lista_Candidati, x);
                 }
         } while (nume[0] != '\0' && b);
}
//2 - Comanda de modificare a datelor unui candidat inscris
void Functie_Modificare() {
     pTip_Candidat p;
     void *x;
     char nume[30];
     printf("Introduceti numele si prenumele candidatului \n");
     printf("pentru care se doreste modificarea datelor : ");
     gets(nume);
     if (Prezent(&Lista_Candidati, nume)) {
        printf("Modificari : \n");
        p = (struct Tip_Candidat *) malloc(sizeof(struct Tip_Candidat));
        printf("Nume si prenume : ");
        gets(p->nume);
        printf("Numar legitimatie : ");
        gets(p->numar);
        x = p;
        ModificaInformatie(&Lista_Candidati, x);
        }
     else {
        printf("Candidatul %s nu figureaza in lista\n", nume);
        printf("Introduceti <ENTER> pentru continuare\n");
        getch();
        }
}
//3 - Comanda de stergere a unui candidat inscris in lista
void Functie_Retragere() {
     char nume[30];
     printf("Introduceti numele si prenumele candidatului care se retrage : \n");
     gets(nume);
     if (Prezent(&Lista_Candidati, nume)) StergeElement(&Lista_Candidati);
     else {
          printf("Candidatul %s nu figureaza in lista\n", nume);
          printf("Introduceti <ENTER> pentru continuare\n");
          getch();
          }
}
//4 - Comanda de trecere a notelor candidatilor inscrisi
void Functie_Note() {
     int i;
     bool b;
     void *x;
     char buf[30];
     if (!Trecut_Note) {
        Trecut_Note = True;
        printf("Trecerea notelor candidatilor\n");
        printf("Dupa fiecare nume afisat se introduc notele sub forma :\n");
        printf(" nota1 nota2 nota3 <ENTER> \n");
        i = 0;
        if (PozitionareInceput(&Lista_Candidati))
           while (!TestSfarsit(&Lista_Candidati)) {
                 if (AdresaInformatie(&Lista_Candidati, &x)) {
                    i++;
                    printf("%d %s %s ", i, ((pTip_Candidat)x)->nume, ((pTip_Candidat)x)->numar);
                    gets(buf);
                    sscanf(buf, "%d %d %d ", &(((pTip_Candidat)x)->note[0]),
                    &(((pTip_Candidat)x)->note[1]), &(((pTip_Candidat)x)->note[2]));
                    ((pTip_Candidat)x)->medie = (((pTip_Candidat)x)->note[0] +
                    ((pTip_Candidat)x)->note[1] + ((pTip_Candidat)x)->note[2])/3.0;
                    ModificaInformatie(&Lista_Candidati, x);
                    printf("\n");
                    }
           Urmator(&Lista_Candidati);
           }
     }
}
//5 - Comanda de creare a listei candidatilor, ordonata dupa medie
void Functie_Ordonare(struct LISTA *pL1, struct LISTA *pL2) {
     pTip_Candidat p;
     void *x, *y;
     bool b, gasit;
     InitializareLista(pL2);
     PozitionareInceput(pL1);
     while (!TestSfarsit(pL1)) {
           if (AdresaInformatie(pL1, &x)) {
              p = (struct Tip_Candidat *) malloc(sizeof(struct Tip_Candidat));
              *p = *(pTip_Candidat)(x);
              gasit = False;
              if (PozitionareInceput(pL2))
                 while (!TestSfarsit(pL2) && !gasit)
                    if (AdresaInformatie(pL2, &y))
                       if (p->medie < ((pTip_Candidat)y)->medie)
                           Urmator(pL2);
                       else gasit = True;
              y = p;
              if (!gasit) AdaugaLaSfarsit(pL2, y);
              else InsereazaElement(pL2, y);
              Urmator(pL1);
              }
     }
}           
//6 - Comanda de afisare a listei candidatilor
void Functie_Afisare(struct LISTA *pL) {
     bool b;
     void *x;
     int i, j;
     printf("Afisare rezultate :\n");
     i = 0;
     if (PozitionareInceput(pL))
        while (!TestSfarsit(pL)) {
           if (AdresaInformatie(pL, &x)) {
              i++;
              printf("%3d %-30s %-10s ", i, ((pTip_Candidat)x)->nume, ((pTip_Candidat)x)->numar);
              for (j = 0; j <= 2; j++)
                  printf("%-3d", ((pTip_Candidat)x)->note[j]);
              printf("%5.2f\n", ((pTip_Candidat)x)->medie);
              Urmator(pL);
              }
           }
     else printf ("Lista este vida\n");
     getch();
}
int main() {
    Initializari();
    do {
        Afisare_Meniu();
        Selectie_Validare_Comanda();
        switch (comanda) {
               case Inscriere :
                    Functie_Inscriere();
                    break;
               case Modificare :
                    Functie_Modificare();
                    break; 
               case Retragere :
                    Functie_Retragere();
                    break;
               case Note :
                    Functie_Note();
                    break;  
               case Ordonare :
                    Functie_Ordonare(&Lista_Candidati, &Lista_Ordonata);
                    break;
               case Afisare :
                    Functie_Afisare(&Lista_Ordonata);
                    break;
               }
        } while (comanda != Terminare);
}
