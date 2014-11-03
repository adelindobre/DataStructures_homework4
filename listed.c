#include <stdlib.h>
#include "listed.h"
/*initializare lista vida*/
bool InitializareLista(struct LISTA *pL) {
     pL->inceput = (struct celula *) malloc (sizeof(struct celula));
     if (!(pL->inceput)) return False;
     pL->sfarsit = (struct celula *) malloc (sizeof(struct celula));
     if (!(pL->sfarsit)) return False;
     pL->inceput->urm = pL->sfarsit;
     pL->sfarsit->prec = pL->inceput;
     pL->inceput->prec = NULL;
     pL->sfarsit->urm = NULL;
     pL->lungime = 0;
     pL->curent = pL->sfarsit;
     return True;
}
bool TestListaVida(struct LISTA *pL) {
     return pL->lungime == 0;
}
bool PozitionareInceput(struct LISTA *pL) {
     if (TestListaVida(pL)) return False;
     else {
          pL->curent = pL->inceput->urm;
          return True;
          }
}
bool PozitionareSfarsit(struct LISTA *pL) {
     if (TestListaVida(pL)) return False;
     else {
          pL->curent = pL->sfarsit->prec;
          return True;
          }
}  
bool TestInceput(struct LISTA *pL) {
     return pL->inceput->urm == pL->curent;
}
bool TestSfarsit(struct LISTA *pL) {
     return pL->curent == pL->sfarsit;
} 
bool Urmator(struct LISTA *pL) {
     if (TestListaVida(pL)) return False;
     else {
          if (pL->curent != pL->sfarsit) {
                         pL->curent = pL->curent->urm;
                         return True;
                         }
          else return False;
          }
}
bool Precedent(struct LISTA *pL) {
     if (TestListaVida(pL)) return False;
     else {
          if (pL->curent != pL->inceput) {
                         pL->curent = pL->curent->prec;
                         return True;
                         }
          else return False;
          }
}
bool AdaugaLaSfarsit(struct LISTA *pL, void *x) {
     struct celula *p;
     p = (struct celula *) malloc (sizeof(struct celula));
     if (!p) return False;
     else {
          p->prec = pL->sfarsit->prec;
          p->urm = pL->sfarsit;
          p->pTipElement = x;
          pL->sfarsit->prec->urm = p;
          pL->sfarsit->prec = p;
          pL->lungime += 1;
          return True;
          }
}
bool AdresaInformatie(struct LISTA *pL, void **x) {
     if (TestListaVida(pL)) return False;
     else {
          *x = pL->curent->pTipElement;
          return True;
          }
}
bool ModificaInformatie(struct LISTA *pL, void *x) {
     if (TestListaVida(pL)) return False;
     else {
          pL->curent->pTipElement = x;
          return True;
          }
}   
bool StergeElement(struct LISTA *pL) {
     struct celula *p;
     if (TestListaVida(pL)) return False;
     else {
          p = pL->curent;
          p->prec->urm = p->urm;
          p->urm->prec = p->prec;
          if (p->urm == pL->sfarsit) pL->curent = p->prec;
          else pL->curent = p->urm;
          free (p->pTipElement);
          free(p);
          pL->lungime -= 1;
          return True;
          }
}
bool InsereazaElement(struct LISTA *pL, void *x) {
     struct celula *p;
     p = (struct celula *) malloc (sizeof(struct celula));
     if (!p) return False;
     p->pTipElement = x;
     p->urm = pL->curent;
     p->prec = pL->curent->prec;
     pL->curent->prec->urm = p;
     pL->curent->prec = p;
     pL->curent = p;
     pL->lungime += 1;
     return True;
}
int LungimeLista(struct LISTA *pL) {
    return pL->lungime;
}

