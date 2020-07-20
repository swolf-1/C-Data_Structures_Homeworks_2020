#include <stdio.h>
#include <stdlib.h>

#define megisto_plithos 100

typedef enum {
    FALSE, TRUE
} boolean;

typedef boolean typos_synolou[megisto_plithos];
typedef int stoixeio_synolou;

void Dimiourgia(typos_synolou synolo);
void Katholiko(typos_synolou synolo);
void Eisagogi(stoixeio_synolou stoixeio, typos_synolou synolo);
void Diagrafi(stoixeio_synolou stoixeio, typos_synolou synolo);
boolean Melos(stoixeio_synolou stoixeio, typos_synolou synolo);
boolean KenoSynolo(typos_synolou synolo);
boolean IsaSynola(typos_synolou s1, typos_synolou s2);
boolean Yposynolo(typos_synolou s1, typos_synolou s2);
void EnosiSynolou(typos_synolou s1, typos_synolou s2, typos_synolou enosi);
void TomiSynolou(typos_synolou s1, typos_synolou s2, typos_synolou tomi);
void DiaforaSynolou(typos_synolou s1, typos_synolou s2, typos_synolou diafora);
boolean isPrime(stoixeio_synolou n);
void createPrimeSet(stoixeio_synolou first,stoixeio_synolou last,typos_synolou syn);
void displaySet(stoixeio_synolou first,stoixeio_synolou last,typos_synolou syn);

int main()
{
    typos_synolou syn;
    int first,last;

    printf("dwse ton first:");
    scanf("%d",&first);

    printf("dwse ton last");
    scanf("%d",&last);

    createPrimeSet(first,last,syn);

    printf("prwtoi...... \n");
    displaySet(first,last,syn);

}
void Dimiourgia(typos_synolou synolo)
{
    stoixeio_synolou i;

    for (i = 0; i < megisto_plithos; i++)
        synolo[i] = FALSE;
}
void Katholiko(typos_synolou synolo)
{
    stoixeio_synolou i;

    for (i = 0; i < megisto_plithos; i++)
        synolo[i] = TRUE;
}
void Eisagogi(stoixeio_synolou stoixeio, typos_synolou synolo)
{
    synolo[stoixeio] = TRUE;
}
void Diagrafi(stoixeio_synolou stoixeio, typos_synolou synolo)
{
    synolo[stoixeio] = FALSE;
}
boolean Melos(stoixeio_synolou stoixeio, typos_synolou synolo)
{
    return synolo[stoixeio];
}
boolean KenoSynolo(typos_synolou synolo)
{
    stoixeio_synolou i;
    boolean keno;

    keno=TRUE;
    i = 0;

    while (i < megisto_plithos  && keno) {
        if (Melos(i, synolo))
            keno = FALSE;
        else
            i++;
    }
    return keno;
}
boolean IsaSynola(typos_synolou s1, typos_synolou s2)
{
    stoixeio_synolou i;
    boolean isa;

    isa = TRUE;
    i=0;
    while (i < megisto_plithos && isa)
        if (Melos(i,s1) != Melos(i,s2))
            isa = FALSE;
        else
            i++;
    return isa;
}
boolean Yposynolo(typos_synolou s1, typos_synolou s2)
{
    stoixeio_synolou i;
    boolean yposyn;

    yposyn = TRUE;
    i=0;
    while (i < megisto_plithos && yposyn)
        if (Melos(i, s1) && !Melos(i, s2))
            yposyn = FALSE;
        else
            i++;
    return yposyn;
}
void EnosiSynolou(typos_synolou s1, typos_synolou s2, typos_synolou enosi)
{
    stoixeio_synolou i;

    for (i = 0; i < megisto_plithos; i++)
        enosi[i] = Melos(i, s1) || Melos(i, s2);
}
void TomiSynolou(typos_synolou s1, typos_synolou s2, typos_synolou tomi)
{
    stoixeio_synolou i;

    for (i = 0; i < megisto_plithos; i++)
        tomi[i] = Melos(i, s1) && Melos(i, s2);
}
void DiaforaSynolou(typos_synolou s1, typos_synolou s2, typos_synolou diafora)
{
    stoixeio_synolou i;

    for (i = 0; i < megisto_plithos; i++)
        diafora[i] = Melos(i, s1) && (!Melos(i, s2));
}
boolean isPrime(int n)
{
    int i,dier=0;

    for(i=1;i<=n;i++)
        if(n % i == 0)
            dier++;

    if(dier==2)
        return TRUE;
    else
        return FALSE;
}
void createPrimeSet(stoixeio_synolou first,stoixeio_synolou last,typos_synolou syn)
{
    Dimiourgia(syn);

    for(int i = first; i <= last; i++)
        if(isPrime(i))
            Eisagogi(i,syn);
}
void displaySet(stoixeio_synolou first,stoixeio_synolou last,typos_synolou syn)
{
    for(int i=first; i <= last; i++)
        if(syn[i])
            printf("%d ",i);
}


