#include <stdio.h>
#include <stdlib.h>

typedef int QueueElementType;

typedef struct QueueNode *QueuePointer;

typedef struct QueueNode
{
	QueueElementType Data;
    QueuePointer Next;
} QueueNode;

typedef struct
{
    QueuePointer Front;
    QueuePointer Rear;
} QueueType;

typedef enum {
    FALSE, TRUE
} boolean;


void CreateQ(QueueType *Queue);
boolean EmptyQ(QueueType Queue);
void AddQ(QueueType *Queue, QueueElementType Item);
void RemoveQ(QueueType *Queue, QueueElementType *Item);

/*ΥΠΑΡΧΕΙ ΑΛλΑΓΗ ΣΤΗΝ ΣΥΝΑΡΤΗΣΗ AddQ ΩΣΤΕ ΝΑ ΓΙΝΕΙ ΚΥΚΛΙΚΗ Η ΟΥΡΑ.*/
int main()
{

    /*Δήλωση μεταβλητών.*/
    QueueType AQueue;
    QueuePointer TempPtr;
    int i,N,M;

    /*Δημιουργία ουρας.*/
    CreateQ(&AQueue);

    /*Έλεγχος εγκυρότητας και διάβασμα πλήθους φυλακισμένων.*/
    do{
        printf("DWSE TO PLITHOS TWN FYLAKISMENWN:");
        scanf("%d",&N);

        if(N < 1 )
            printf("Try again,the number must me >=1.\n");

    }while(N < 1);

    /*Περνάμε στην ουρα αριθμούς όσοι και το πλήθος των φυλακισμένων.*/
    for(i=1; i <= N; i++)
        AddQ(&AQueue,i);

    /*Έλεγχος εγκυρότητας και διάβασμα αριθμού εκτέλεσης.*/
    do{
        printf("DWSE TON ARITHMO TOU KYKLOU EKTELESIS:");
        scanf("%d",&M);

        if(M < 1 )
            printf("Try again,the number must me >=1.\n");

    }while(M < 1);


    /*Δομή επανάληψης μέχρι να μείνει μονο ενας φυλακισμένος.*/
    while(AQueue.Front != AQueue.Front->Next)
    {

        for(i=1; i < M; i++)
        {
            printf("%d, ",AQueue.Front->Data);

            /*Αν ειναι ο προτελευταιος κρατουμενος (συμφωνα με τον αριθμο του κυκλου εκτελεσης)
            τοτε κανουμε το Next του να δειχνει στο μεθεπομενο στοιχειο,γιατι το επομενο θα
            "εκτελεστει".
            Αν δεν ειναι το προτελευταιο ,παει κανονικα στο επομενο.*/

            if(i == M-1)
            {
            TempPtr = AQueue.Front;
            AQueue.Front = AQueue.Front->Next;
            TempPtr->Next = AQueue.Front->Next;
            }
            else
            {
               AQueue.Front = AQueue.Front->Next;
            }
        }

        /*Εμφανιση του τελευταιου φυλακισμενου, ο οποιος θα εκτελεστει κιολας.*/
        printf("%d, ",AQueue.Front->Data);
        printf("EXECUTION %d\n",AQueue.Front->Data);

        /*Προχωραει στον επομενο κρατουμενο.*/
        AQueue.Front = AQueue.Front->Next;


    }
    /*Εμαφνιση του κρατουμενου που σωθηκε.*/
    printf("SURVIVAL %d",AQueue.Front->Data);

    return 0;
}


void CreateQ(QueueType *Queue)
{
	Queue->Front = NULL;
	Queue->Rear = NULL;
}

boolean EmptyQ(QueueType Queue)
{
	return (Queue.Front==NULL);
}

void AddQ(QueueType *Queue, QueueElementType Item)
{
	QueuePointer TempPtr;

    TempPtr= (QueuePointer)malloc(sizeof(struct QueueNode));
    TempPtr->Data = Item;
    /*Το NEXT του τελευταιου κομβου θα διχνει στον πρωτο κομβο.*/
    TempPtr->Next = Queue->Front;
    if (Queue->Front==NULL)
    {
        Queue->Front=TempPtr;
    }
    else
        Queue->Rear->Next = TempPtr;
    Queue->Rear=TempPtr;
}

void RemoveQ(QueueType *Queue, QueueElementType *Item)
{
    QueuePointer TempPtr;

    if (EmptyQ(*Queue)) {
   	    printf("EMPTY Queue\n");
    }
   else
   {
        TempPtr = Queue->Front;
        *Item=TempPtr->Data;
        Queue->Front = Queue->Front->Next;
        free(TempPtr);
        if (Queue->Front==NULL) Queue->Rear=NULL;
    }
}



