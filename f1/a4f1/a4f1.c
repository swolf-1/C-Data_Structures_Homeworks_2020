#include <stdio.h>
#include <stdlib.h>

#define megisto_plithos 59

typedef enum {
    FALSE, TRUE
} boolean;

typedef boolean typos_synolou[megisto_plithos];
typedef int stoixeio_synolou;

void Katholiko(typos_synolou synolo);
void Dimiourgia(typos_synolou synolo);
void displayset(typos_synolou set);
void Eisagogi(stoixeio_synolou stoixeio, typos_synolou synolo);
boolean Melos(stoixeio_synolou stoixeio, typos_synolou synolo);
boolean isPrime(int numb);
void TomiSynolou(typos_synolou s1, typos_synolou s2, typos_synolou tomi);
void EnosiSynolou(typos_synolou s1, typos_synolou s2, typos_synolou enosi);
void DiaforaSynolou(typos_synolou s1, typos_synolou s2, typos_synolou diafora);
void ComplementSynolou(typos_synolou s1,typos_synolou sympliroma);

int main()
{
    /*Δήλωση συνόλων.*/
    typos_synolou periti,prwti,tomi_peritwn_prwtwn,enosi_peritwn_prwtwn,peritiNOTprwti,sympliroma_prwtwn;

    /*Δημιουργία συνόλου περιττών και εμφάνιση του.(Ερώτημα a)*/
    Dimiourgia(periti);
    for(stoixeio_synolou i=0; i < megisto_plithos; i+=2)
        Eisagogi(i,periti);
    printf("Synolo perittwn arithmwn:");
    displayset(periti);

    /*Δημιουργία συνόλου πρώτων και εμφάνιση του.(Ερώτημα b)*/
    Dimiourgia(prwti);
    for(stoixeio_synolou i=0; i < megisto_plithos; i++)
        if(isPrime(i+1))
            Eisagogi(i,prwti);
    printf("Synolo prwtwn arithmwn:");
    displayset(prwti);

    /*Δημιουργία συνόλου τομής πρώτων και περριτών αριθμών και εμφάνιση του.(Ερώτημα c)*/
    Dimiourgia(tomi_peritwn_prwtwn);
    TomiSynolou(periti,prwti,tomi_peritwn_prwtwn);
    printf("Tomi peritwn kai prwtwn arithmwn:");
    displayset(tomi_peritwn_prwtwn);

    /*Δημιουργία συνόλου ένωησης πρώτων και περριτών αριθμών και εμφάνιση του.(Ερώτημα d)*/
    Dimiourgia(enosi_peritwn_prwtwn);
    EnosiSynolou(periti,prwti,enosi_peritwn_prwtwn);
    printf("Enosi peritwn kai prwtwn arithmwn:");
    displayset(enosi_peritwn_prwtwn);

    /*Δημιουργία συνόλου περριτών αλλα οχι πρώτων αριθμών και εμφάνιση του.(Ερώτημα e)*/
    Dimiourgia(peritiNOTprwti);
    DiaforaSynolou(periti,prwti,peritiNOTprwti);
    printf("Synolo peritwn pou den einai prwti:");
    displayset(peritiNOTprwti);

    /*Δημιουργία συνόλου για συμπλήρωμα πρώτων αριθμών και εμφάνιση του.(Ερώτημα f)*/
    Dimiourgia(sympliroma_prwtwn);
    ComplementSynolou(prwti,sympliroma_prwtwn);
    printf("Symplirwma prwtwn arithmwn:");
    displayset(sympliroma_prwtwn);

    return 0;
}

void Katholiko(typos_synolou synolo)
{
    stoixeio_synolou i;

    for (i = 0; i < megisto_plithos; i++)
        synolo[i] = TRUE;
}

void Dimiourgia(typos_synolou synolo)
{
    stoixeio_synolou i;

    for (i = 0; i < megisto_plithos; i++)
        synolo[i] = FALSE;
}

void Eisagogi(stoixeio_synolou stoixeio, typos_synolou synolo)
{
    synolo[stoixeio] = TRUE;
}

/*Τροποποιημένο displayset για την εμφάνιση που χρειαζόμαστε.(Τριτή κουκκίδα)*/
void displayset(typos_synolou set)
{
	stoixeio_synolou i;
    printf("[");
	for (i=0;i < megisto_plithos;i++)
	{
		if(Melos(i,set))
			printf(" %d",i+1);
	}
	printf("]\n");
}

boolean Melos(stoixeio_synolou stoixeio, typos_synolou synolo)
{
    return synolo[stoixeio];
}

/*Συνάρτηση ελέγχου πρώτων αριθμών.(Πρώτη κουκκίδα)*/
boolean isPrime(int numb)
{
    int counter=0;
    if(numb > 1)
    {
        for(int i=1; i < numb+1; i++)
            if(numb%i==0)
                counter++;

        if(counter == 2)
            return 1;
        else
            return 0;
    }
    else
         return 0;

}

void TomiSynolou(typos_synolou s1, typos_synolou s2, typos_synolou tomi)
{
    stoixeio_synolou i;

    for (i = 0; i < megisto_plithos; i++)
        tomi[i] = Melos(i, s1) && Melos(i, s2);
}

void EnosiSynolou(typos_synolou s1, typos_synolou s2, typos_synolou enosi)
{
    stoixeio_synolou i;

    for (i = 0; i < megisto_plithos; i++)
        enosi[i] = Melos(i, s1) || Melos(i, s2);
}

void DiaforaSynolou(typos_synolou s1, typos_synolou s2, typos_synolou diafora)
{
    stoixeio_synolou i;

    for (i = 0; i < megisto_plithos; i++)
        diafora[i] = Melos(i, s1) && (!Melos(i, s2));
}

/*Συνάρτηση επιστροφής συμπήρώματος.(Δεύτερη κουκκίδα)*/
void ComplementSynolou(typos_synolou s1,typos_synolou sympliroma)
{
    typos_synolou numbers;

    Katholiko(numbers);
    DiaforaSynolou(numbers,s1,sympliroma);
}
