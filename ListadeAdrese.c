//Exemplu - Lista de adrese
//Ilustreaza modul de utilizare al listelor dublu inlantuite
//Lista este stocata in memorie in timpul utilizarii
//Lista poate fi stocata intr-un fisier si incarcata de acolo pentru a fi utilizata
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
struct adresa {
       char nume[30];
       char strada[40];
       char oras[20];
       char stat[3];
       char cod_postal[11];
       struct adresa *urm; //pointerul urmatoarei intrari
       struct adresa *preced; //pointerul inregistrarii precedente
       } lista_intrari;
struct adresa *prim; //pointerul primei intrari din lista
struct adresa *ultim; //pointerul ultimei intrari
struct adresa *find(char *);
void enter();
void search();
void save();
void load();
void list();
void sterge(struct adresa **, struct adresa **);
void dls_store(struct adresa *i, struct adresa **prim, struct adresa **ultim);
void inputs(char *, char *, int);
void display(struct adresa *);
int menu_select();
int main() {
    //initializarea pointerilor de inceput si sfarsit
    prim = ultim = NULL;
    for(;;) {
            switch (menu_select()) {
                   case 1 : enter();
                            break;
                   case 2 : sterge(&prim, &ultim);
                            break;
                   case 3 : list();
                            break;
                   case 4 : search(); //gaseste o strada
                            break;
                   case 5 : save(); //salveaza lista in fisier
                            break;
                   case 6 : load(); //citeste lista din fisier
                            break;
                   case 7 : exit(0);
                   }
            }
    getch();
}
//selectarea unei operatii
int menu_select() {
     char s[80];
     int c; 
     printf("1. Introduceti un nume\n");
     printf("2. Stergeti un nume\n");
     printf("3. Afiseaza lista din fisier\n");
     printf("4. Cauta\n");
     printf("5. Salveaza fisierul\n");
     printf("6. Incarca fisierul\n");
     printf("7. Renunta\n");
     do {
         printf("\nIntroduceti optiunea : ");
         gets(s);
         c = atoi(s);
         } while (c < 0 || c > 7);
     return c;
}
//introducere nume si adrese
void enter() {
     struct adresa *info;
     for(;;) {
             info = (struct adresa *)malloc(sizeof(lista_intrari));
             if (!info) {
                        printf("\nmemorie insuficienta");
                        return;
                        }
             inputs("Introduceti numele : ", info->nume, 30);
             if (!info->nume[0]) break; //se opreste introducerea
             inputs("Introduceti strada : ", info->strada, 40);
             inputs("Introduceti orasul : ", info->oras, 20);
             inputs("Introduceti statul : ", info->stat, 3);
             inputs("Introduceti codul postal : ", info->cod_postal, 10);
             dls_store(info, &prim, &ultim);
             }
}
//citeste un sir de lungime maxima egala cu numar si previne depasirea sirului
void inputs(char *mesaj, char *s, int numar) {
     char p[255];
     printf(mesaj);
     gets(p);
     if (strlen(p) > numar) printf("\nSir prea lung\n");
     strcpy(s, p);
}
//creeaza o lista dublu inlantuita sortata
void dls_store(
     struct adresa *i, //element nou
     struct adresa **prim, //primul element din lista
     struct adresa **ultim) { //ultimul element din lista
     struct adresa *vechi, *p;
     if (*ultim == NULL) { //primul element din lista
        i->urm = NULL;
        i->preced = NULL;
        *ultim = i;
        *prim = i;
        return;
     }
     p = *prim; //incepe din varful listei
     vechi = NULL;
     while (p) {
           if (strcmp(p->nume, i->nume) < 0) {
                               vechi = p;
                               p = p->urm;
                               }
           else {
                if (p->preced) {
                               p->preced->urm = i;
                               i->urm = p;
                               i->preced = p->preced;
                               p->preced = i;
                               return;
                               }
                i->urm = p; //noul prim element
                i->preced = NULL;
                p->preced = i;
                *prim = i;
                return;
                }
     }
     vechi->urm = i; //inserare la sfarsit
     i->urm = NULL;
     i->preced = vechi;
     *ultim = i;
}
//elimina un element din lista
void sterge(struct adresa **prim, struct adresa **ultim) {
     struct adresa *info, *find();
     char s[80];
     inputs("Introduceti numele : ", s, 30);
     info = find(s);
     if (info) {
               if (*prim == info) {
                         *prim = info->urm;
                         if (*prim) (*prim)->preced = NULL;
                         else *ultim = NULL;
                         }
               else {
                    info->preced->urm = info->urm;
                    if (info != *ultim)
                       info->urm->preced = info->preced;
                    else *ultim = info->preced;
                    }
               free(info);
               }
}
//gaseste o adresa
struct adresa *find(char *nume) {
       struct adresa *info;
       info = prim;
       while (info) {
             if (!strcmp(nume, info->nume)) return info;
             info = info->urm;
             }
       printf("Numele nu a fost gasit\n");
       return NULL;
}
//afiseaza toata lista
void list() {
     struct adresa *info;
     info = prim;
     if (info == NULL) printf("\nLista este vida\n");
     while (info) {
           printf("\n");
           display(info);
           info = info->urm;
           }
     printf("\n");
}
//afiseaza campurile din fiecare adresa
void display(struct adresa *info) {
     printf("\n");
     printf("%s\n", info->nume);
     printf("%s\n", info->strada);
     printf("%s\n", info->oras);
     printf("%s\n", info->stat);
     printf("%s\n", info->cod_postal);
     printf("\n");
}
//cauta un nume in lista
void search() {
     char nume[40];
     struct adresa *info, *find();
     printf("Introduceti numele : ");
     gets(nume);
     info = find(nume);
     if (!info) printf("Nu a fost gasit\n");
     else display(info);
}
//salveaza fisierul de adrese
void save() {
     struct adresa *info;
     FILE *fp;
     fp = fopen("listadubla", "wb");
     if (!fp) {
              printf("Nu se poate deschide fisierul\n");
              exit(1);
              }
     printf("\nSe salveaza fisierul\n");
     info = prim;
     while (info) {
           fwrite(info, sizeof(struct adresa), 1, fp);
           info = info->urm;
           }
     fclose(fp);
}
//incarca fisierul de adrese
void load() {
     struct adresa *info;
     FILE *fp;
     fp = fopen("listadubla", "rb");
     if (!fp) {
              printf("Nu se poate deschide fisierul\n");
              exit(1);
              }
//elibereaza toata memoria alocata anterior
     while (prim) {
           info = prim->urm;
           free(info);
           prim = info;
           }
//initializeaza pointerii extremi
     prim = ultim = NULL;
     printf("\nSe incarca fisierul\n");
     while (!feof(fp)) {
           info = (struct adresa *)malloc(sizeof(struct adresa));
           if (!info) {
                       printf("\nmemorie insuficienta");
                       return;
                       }
           if (1 != fread(info, sizeof(struct adresa), 1, fp)) break;
           dls_store(info, &prim, &ultim);
           }
     fclose(fp);
}
                      
    
     
     
