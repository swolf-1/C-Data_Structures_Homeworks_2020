#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define HMax 10

#define VMax 100
#define EndOfList -1

typedef char ListElementType;

typedef struct {
	char RecKey[8];
	ListElementType Password[6];
	int Link;
} ListElm;

typedef struct  {
	int HashTable[HMax];
    int Size;
	int SubListPtr;
    int StackPtr;
	ListElm List[VMax];
} HashListType;

typedef enum {
    FALSE, TRUE
} boolean;

void CreateHashList(HashListType *HList);
int HashKey(char Key[]);
boolean FullHashList(HashListType HList);
void SearchSynonymList(HashListType HList,char KeyArg[],int *Loc,int *Pred);
void SearchHashList(HashListType HList,char KeyArg[],int *Loc,int *Pred);
void AddRec(HashListType *HList,ListElm InRec);
void DeleteRec(HashListType *HList,char DelKey[]);


int findAverage(char username[]);
void BuildHashList(HashListType *HList);
/*ΕΧΟΥΝ ΓΙΝΕΙ ΟΙ ΑΠΑΡΑΙΤΗΤΕΣ ΑΛΛΑΓΕΣ ΩΣΤΕ ΓΙΝΕΤΕ ΕΙΑΣΑΓΩΓΗ ΚΑΙ ΣΥΓΚΡΙΣΗ ΑΛΦΑΡΙΘΜΗΤΙΚΏΝ ΣΤΙΣ ΣΥΝΑΡΤΗΣΕΙΣ (SearchSynonymList , SearchHashList, CreateHashList)*/
int main()
{
    //Δηλωση μεταβλητων.
    HashListType HList;
    ListElm AnItem;
    int Loc,Pred;
    char newEntry;

    //Κληση συναρτησης για δημιουργια HashList.
    BuildHashList(&HList);

    //Επαναλιπτικη δομη εισαγωγης στοιχειων μεχρι να την τερματισει ο χρηστης.
    while(TRUE)
    {
        //Διαβασμα στοιχειων USERNAME και PASSWORD.
        printf("USERNAME: ");
        scanf("%s",AnItem.RecKey);
        AnItem.RecKey[strlen(AnItem.RecKey)] = '\0';
        printf("PASSWORD: ");
        scanf("%s",AnItem.Password);
        AnItem.Password[strlen(AnItem.Password)] = '\0';

        //Αναζητση των στοιχειων που δοθηκαν.
        SearchHashList(HList,AnItem.RecKey,&Loc,&Pred);

        //Αν βρεθηκε το USERNAME.
        if( Loc != -1)
            //Ελεγχος του PASSWORD που αντιστοιχει στο USERNAME που βρεθηκε , με το PASSWORD που δοθηκε απο το πληκρολογιο.
            //Αν ειναι ιδια.
            if(strcmp(HList.List[Loc].Password,AnItem.Password) == 0)
                //Εμφανιση μηνυματος επιτυχεις εισασαγωγης στο συστημα.
                printf("You have logged in to the system.\n");
            //Αν δεν ειναι ιδια.
            else
                //Εμφανιση μηνυματος ανεπιτυχεις εισασαγωγης στο συστημα και οτι ο κωδικος δν ταιριαζει.
                printf("Access is forbidden: Wrong password.\n");
        //Αν δεν βρεθηκε το USERNAME.
        else
            //Ενημερωτικο μηνυμα.
            printf("Access is forbidden: Wrong user ID.\n");

        //Μηνυμα αν θελει να συνεχισει ο χρηστης να εισαγει και αλλα στοιχεια.
        printf("New entry Y/N (Y=Yes, N=No)?");

        do{
            scanf(" %c", &newEntry);

            if(newEntry != 'Y' && newEntry != 'N')
                printf("The answer must be Y(Yes) or N(No).Try again:");

        }while(newEntry != 'Y' && newEntry != 'N');

        //Αν επιλεξει 'Ν'.Τελοσ επαναληπτικης διαδικασιας.
        if(newEntry == 'N')
            break;
    }
    return 0;
}

/*Τροποποίηση της συναρτησης HashKey ωστε να ειναι αναλογη με τηνσυναρτηση κατακερματισμου που χρειαζομαστε.*/
int HashKey(char Key[])
{
	return findAverage(Key)%HMax;
}

void CreateHashList(HashListType *HList)

{
	int index;

	HList->Size=0;
	HList->StackPtr=0;

    index=0;
	while (index<HMax)
	{
		HList->HashTable[index]=EndOfList;
		index=index+1;
    }


    index=0;
	while(index < VMax-1)
	{
		HList->List[index].Link=index+1;
		strcpy(HList->List[index].Password,"0");
		index=index+1;
	}
	HList->List[index].Link=EndOfList;
}

boolean FullHashList(HashListType HList)
{
	return(HList.Size==VMax);
}

void SearchSynonymList(HashListType HList,char KeyArg[],int *Loc,int *Pred)
{
	int Next;
	Next=HList.SubListPtr;
	*Loc=-1;
	*Pred=-1;
	while(Next!=EndOfList)
	{
		if (strcmp(HList.List[Next].RecKey,KeyArg)==0)
		{
			*Loc=Next;
			Next=EndOfList;
		}
		else
		{
			*Pred=Next;
			Next=HList.List[Next].Link;
		}
	}
}
void SearchHashList(HashListType HList,char KeyArg[],int *Loc,int *Pred)
{
	int HVal;
	HVal=HashKey(KeyArg);
    if (HList.HashTable[HVal]==EndOfList)
	{
		*Pred=-1;
		*Loc=-1;
	}
	else
	{
		HList.SubListPtr=HList.HashTable[HVal];
		SearchSynonymList(HList,KeyArg,Loc,Pred);
	}
}

void AddRec(HashListType *HList,ListElm InRec)
{
	int Loc, Pred, New, HVal;


	if(!(FullHashList(*HList)))
	{
		Loc=-1;
		Pred=-1;
		SearchHashList(*HList,InRec.RecKey,&Loc,&Pred);
		if(Loc==-1)
		{
			HList->Size=HList->Size +1;
			New=HList->StackPtr;
			HList->StackPtr=HList->List[New].Link;
			HList->List[New]=InRec;
			if (Pred==-1)
			{
			    HVal=HashKey(InRec.RecKey);
                HList->HashTable[HVal]=New;
				HList->List[New].Link=EndOfList;
			}
			else
			{
                HList->List[New].Link=HList->List[Pred].Link;
				HList->List[Pred].Link=New;
			}
		}

		else
		{
			printf("YPARXEI HDH EGGRAFH ME TO IDIO KLEIDI \n");
		}
	}
	else
	{
		printf("Full list...");
	}
}
void DeleteRec(HashListType *HList,char DelKey[])
{
	int Loc, Pred, HVal;

	SearchHashList(*HList,DelKey,&Loc,&Pred);
	if(Loc!=-1)
	{
		if(Pred!=-1)
		{
			HList->List[Pred].Link=HList->List[Loc].Link;
		}
		else
		{
			HVal=HashKey(DelKey);
		    HList->HashTable[HVal]=HList->List[Loc].Link;
		}
		HList->List[Loc].Link=HList->StackPtr;
		HList->StackPtr=Loc;
		HList->Size=HList->Size -1;
	}
	else
	{
		printf("DEN YPARXEI  EGGRAFH ME KLEIDI %s \n",DelKey);
	}
}

/*Συναρτηση ευρεσης της τιμης average απο την συναρτηση κατακερματισμου.*/
int findAverage(char username[])

{   //Δηλωση μεταβλητων.
    //Εισαγουμε στην μεταβλητη average τον κωδικο ASCII του πρωτου χαρακτηρα του USERNAME.
    int average=username[0],i;

    for(i=0; username[i] != '\0'; i++)
        if(username[i+1] == '\0')
            //Προσφετουμε στην μεταβλητη average τον κωδικο ASCII του τελευταιου χαρακτηρα του USERNAME.
            average += username[i];
    //Επιστρεφουμε το average δια του 2.
    return average / 2;

}

//Συναρτηση δημιουριας HashList.
void BuildHashList(HashListType *HList)
{
    //Δηλωση μεταβλητων.
    ListElm AnItem;
    FILE *input;
    int nscan;

    //Δημιουρια HashList.
    CreateHashList(&(*HList));

    //Ανοιγμα αρχειου για αναγνωση.
    input = fopen("I5F6.txt","r");

    //Αν δεν ανοιξει,εμφανιση αναλογου μηνυματος.
    if(input == NULL)
        printf("Can't open file.\n");
    //Αν ανοιξει επιτυχως
    else
        while(TRUE)
        {
            //Διαβαζουμε σε ζευγαρια USERNAME και PASSWORD.
            nscan = fscanf(input, "%s %s",AnItem.RecKey,AnItem.Password);

            //Οταν τελειωσει η αναγνωσει του αρχειου ,τελος επαναληψης.
            if(nscan == EOF) break;
            //Αν υπαρχει προβλημα στην αναγνωση, εμφανησει ενημερωτικου μηνυματος και εξοδος απο την επαναληπτικη διαδικασια.
            if(nscan != 2 )
            {
                printf("Improper file format.\n");
                break;
            }
            //Αν ειναι ολα καλα
            else
                //Εισαγωγει των στοιχειων που διαβαστικαν στο HashList.
                AddRec(&(*HList),AnItem);
        }
}
