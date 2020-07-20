#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define megisto_plithos 256

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
boolean isValidInteger (char str[]);
boolean isValidIdentifier (char str[]);

int main()
{
    typos_synolou CharacterSet,DigitSet,LetterSet;
    char answer = 'y',str[30];


    Dimiourgia(CharacterSet);
    Dimiourgia(DigitSet);
    Dimiourgia(LetterSet);

    Eisagogi(43,CharacterSet);
    Eisagogi(45,CharacterSet);

    for(int i=48; i < 58; i++)
        Eisagogi(i,DigitSet);

    for(int i=65; i < 91; i++)
        Eisagogi(i,LetterSet);

    for(int i=97; i < 123; i++)
        Eisagogi(i,LetterSet);

    while(answer == 'y')
    {
        printf("Give an integer to check if it is valid:");
        scanf(" %s",&str);

        if(isValidInteger(str))
            printf("Is Valid\n");
        else
            printf("Not Valid\n");

        printf("Do you want more y/n:");
        scanf(" %c",&answer);

    }


    /*Μια ιδια λουπα κια για το αλλο*/



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

boolean isValidInteger (char str[])
{
    boolean valid = TRUE;

    if(str[0] == 43 || str[0] == 45)
        for (int i=1; str[i] != '\0'; i++)
                if(str[i] >= 48 && str[i] < 58)
                    valid = TRUE;
                else
                {
                    valid = FALSE;
                    break;
                }

    else
        valid = FALSE;

    return valid;

}

boolean isValidIdentifier (char str[])
{



    /*Με τον ιδιο τροπο και για λεξη ,απλα στο if μεσα στην for θα ελεγχουμε
    (>= 65 && < 91) || (>= 97 && < 123)*/


}
