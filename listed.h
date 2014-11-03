#define bool int
#define True 1
#define False 0
#define NULL 0
struct celula {
       void *pTipElement;
       struct celula *prec;
       struct celula *urm;
       };
struct LISTA {
       int lungime;
       struct celula *inceput;
       struct celula *curent;
       struct celula *sfarsit;
       };
bool InitializareLista(struct LISTA *pL);
bool TestListaVida(struct LISTA *pL);
bool PozitionareInceput(struct LISTA *pL);
bool PozitionareSfarsit(struct LISTA *pL);
bool TestInceput(struct LISTA *pL);
bool TestSfarsit(struct LISTA *pL);
bool Urmator(struct LISTA *pL);
bool Precedent(struct LISTA *pL);
bool AdaugaLaSfarsit(struct LISTA *pL, void *x);
bool AdresaInformatie(struct LISTA *pL, void **x);
bool ModificaInformatie(struct LISTA *pL, void *x);
bool StergeElement(struct LISTA *pL);
bool InsereazaElement(struct LISTA *pL, void *x);
int LungimeLista(struct Lista *pL);
