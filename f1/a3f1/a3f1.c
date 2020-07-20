#include <stdio.h>
#include <stdlib.h>

#define megisto_plithos 26

typedef enum {
    FALSE, TRUE
} boolean;

typedef boolean typos_synolou[megisto_plithos];
typedef int stoixeio_synolou;

void Katholiko(typos_synolou synolo);
void EmfanisiSynolou(typos_synolou set);
boolean Melos(stoixeio_synolou stoixeio, typos_synolou synolo);
void Dimiourgia(typos_synolou synolo);
void Eisagogi(stoixeio_synolou stoixeio, typos_synolou synolo);
boolean IsaSynola(typos_synolou s1, typos_synolou s2);
boolean Yposynolo(typos_synolou s1, typos_synolou s2);
void EnosiSynolou(typos_synolou s1, typos_synolou s2, typos_synolou enosi);
void TomiSynolou(typos_synolou s1, typos_synolou s2, typos_synolou tomi);
void DiaforaSynolou(typos_synolou s1, typos_synolou s2, typos_synolou diafora);

int main()
{
    //Δηλωση συνολων
    typos_synolou Kath,S,T,Union,Intersection,Difference;

    /*Δημιουργια καθολολικου συνολου Kath με τα κεφαλαια
    γραμματα του αγγλικου αλφαβητου και η εμφανιση του.
    (Ερωτημα a)
    */
    Katholiko(Kath);
    printf("Synolo Kefalaiwn Agglikwn Grammatwn = ");
    EmfanisiSynolou(Kath);

    /*Δημιουργια κενου συνολου S,εισαγωγη των γραμματων A B
    C D και εμφανιση του.(Ερωτημα b)*/
    Dimiourgia(S);
    printf("S=");
    for(stoixeio_synolou i=0;i < 4; i++)
        Eisagogi(i,S);
    EmfanisiSynolou(S);

    /*Δημιουργια κενου συνολου T,εισαγωγη των γραμματων A C
    E G I και εμφανιση του.(Ερωτημα b)*/
    Dimiourgia(T);
    printf("T=");
    for(stoixeio_synolou i=0; i < 9; i+=2)
        Eisagogi(i,T);
    EmfanisiSynolou(T);

    /*Ελεχγος αν τα συνολα S και Τ ειναι ισα ή υποσυνολα το
    ενα με το αλλο.(Ερωτημα c)
    */
    if(IsaSynola(S,T))
        printf("ISA SYNOLA.\n");
    if(Yposynolo(S,T))
        printf("S YPOSYNOLO T.\n");
    if(Yposynolo(T,S))
        printf("T YPOSYNOLO S.\n");

    /*Μεσα απο τη συναρτηση στης ενωσης περναμε την ενωση των
    συνολων S και T στο συνολο Union και το εμφανιζουμε.(Ερωτημα d)*/
    EnosiSynolou(S,T,Union);
    printf("ENWSI SYNOLWN S KAI T =");
    EmfanisiSynolou(Union);

    /*Μεσα απο τη συναρτηση στης τομης περναμε την τομη των
    συνολων S και T στο συνολο Intersection και το εμφανιζουμε.(Ερωτημα e)*/
    TomiSynolou(S,T,Intersection);
    printf("TOMH SYNOLWN S KAI T =");
    EmfanisiSynolou(Intersection);

    /*Μεσα απο τη συναρτηση στης διαφορας περναμε την διαφορα των
    συνολων S-T στο συνολο Difference και το εμφανιζουμε.(Ερωτημα f)*/
    DiaforaSynolou(S,T,Difference);
    printf("DIAFORA SYNOLWN S-T=");
    EmfanisiSynolou(Difference);

    return 0;
}

void Katholiko(typos_synolou synolo)
{
    stoixeio_synolou i;

    for (i = 0; i < megisto_plithos; i++)
        synolo[i] = TRUE;
}
/*Συναρτηση για την αντιστοίχιση ενος πινακα με τα γραμματα με τα συνολα
που δημιουργισαμε και εμφανιση των γραμματων οπου χρειαζετε.*/
void EmfanisiSynolou(typos_synolou set)
{
	stoixeio_synolou i;
	char alphabet[]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    printf("{");
	for (i=0;i < megisto_plithos;i++)
		if(Melos(i,set))
           printf("%c ",alphabet[i]);

	printf("}\n");
}

boolean Melos(stoixeio_synolou stoixeio, typos_synolou synolo)
{
    return synolo[stoixeio];
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
