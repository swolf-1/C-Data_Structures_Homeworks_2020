#include <stdio.h>
#include <stdlib.h>

#define NumberOfNodes 22

#define NilValue -1

/*Τροποποιείση του τύπου ListElementType ώστε να αποθηκευεί
τον ΑΜ και τον Βαθμό του μαθητή και αναλογες αλλαγές στις
συναρτήσεις InitializeStoragePool,ReleaseNode,Insert,TraverseLinked
για να περνάμε και τα δυο δεδομένα.*/
typedef struct{
    int AM;
    float grade;
} ListElementType;

typedef int ListPointer;

typedef struct {
    ListElementType Data;
    ListPointer  Next;
} NodeType;

typedef enum {
    FALSE, TRUE
} boolean;

void InitializeStoragePool(NodeType Node[], ListPointer *FreePtr);
void CreateLList(ListPointer *List);
boolean EmptyLList(ListPointer List);
boolean FullLList(ListPointer FreePtr);
void GetNode(ListPointer *P, ListPointer *FreePtr, NodeType Node[]);
void ReleaseNode(NodeType Node[NumberOfNodes], ListPointer P, ListPointer *FreePtr);
void Insert(ListPointer *List, NodeType Node[],ListPointer *FreePtr, ListPointer PredPtr, ListElementType Item);
void Delete(ListPointer *List, NodeType Node[], ListPointer *FreePtr, ListPointer PredPtr);
void TraverseLinked(ListPointer List, NodeType Node[]);

int main()
{
    int number_of_students,i,j;
    ListPointer AList;
    NodeType Node[NumberOfNodes];
    ListPointer FreePtr,PredPtr;
    ListElementType Item;

    /*Δημιουεγεία κενής ΣΛ.(Ερώτημα i)*/
    InitializeStoragePool(Node, &FreePtr);
    CreateLList(&AList);

    /*Διάβασμα πλήθους μαθητών και έλεγχος εγκυρότητας.(Ερώτημα ii)*/
    do{
        printf("DWSE ARI8MO MA8ITWN:");
        scanf("%d",&number_of_students);
        if(number_of_students < 0 || number_of_students >20)
            printf("MH EPITREPTOS ARI8MOS.PROSPA8ISTE KSANA.\n");
    }while(number_of_students < 0 || number_of_students >20);

    /*Διάβασμα στοιχείων μαθητών και εμφάνιση ΣΛ με την συνάρτηση
    TraverseLinked.(Ερώτημα iii)*/
    for(i=0; i < number_of_students; i++)
    {
        printf("DWSE ARI8MO MHTRWOU GIA EISAGWGH STH LISTA: ");
        scanf("%d",&Item.AM);

        printf("DWSE BA8MO GIA EISAGWGH STH LISTA: ");
        scanf("%f",&Item.grade);

        printf("DWSE TH 8ESH META THN OPOIA 8A GINEI H EISAGWGH STOIXEIOU: ");
        scanf("%d",&PredPtr);
        printf("\n");

        printf("Plithos stoixeiwn sth lista %d\n",i+1);
        Insert(&AList,Node,&FreePtr,PredPtr,Item);

        TraverseLinked(AList,Node);
    }

    /*Διαγραφή ενος μαθητή και εμφάνιση της ΣΛ.(Ερώτημα iv)*/
    printf("DWSE TH 8ESH TOY PROHGOUMENOY STOIXEIOY GIA DIAGRAFI: ");
    scanf("%d",&PredPtr);
    printf("\n");
    Delete(&AList,Node,&FreePtr,PredPtr);

    printf("Plithos stoixeiwn sth lista %d\n",i-1);
    TraverseLinked(AList,Node);

    /*Διάβασμα στοιχείων δυο νέων μαθητών και εμφάνιση ΣΛ.(Ερώτημα v)*/
    for(j=0; j < 2; j++)
    {
        printf("DWSE ARI8MO MHTRWOU GIA EISAGWGH STH LISTA: ");
        scanf("%d",&Item.AM);

        printf("DWSE BA8MO GIA EISAGWGH STH LISTA: ");
        scanf("%f",&Item.grade);

        printf("DWSE TH 8ESH META THN OPOIA 8A GINEI H EISAGWGH STOIXEIOU: ");
        scanf("%d",&PredPtr);
        printf("\n");

        printf("Plithos stoixeiwn sth lista %d\n",i+j);
        Insert(&AList,Node,&FreePtr,PredPtr,Item);

        TraverseLinked(AList,Node);
    }

    return 0;
}

void InitializeStoragePool(NodeType Node[], ListPointer *FreePtr)
{
   int i;

    for (i=0; i<NumberOfNodes-1;i++)
    {
        Node[i].Next=i+1;
        Node[i].Data.AM=-1;
        Node[i].Data.grade=-1;

    }
    Node[NumberOfNodes-1].Next=NilValue;
    Node[NumberOfNodes-1].Data.AM=NilValue;
    Node[NumberOfNodes-1].Data.grade=NilValue;
    *FreePtr=0;
}

void CreateLList(ListPointer *List)
{
  *List=NilValue;
}

boolean EmptyLList(ListPointer List)
{
  return (List==NilValue);
}

boolean FullLList(ListPointer FreePtr)
{
  return (FreePtr == NilValue);
}

void GetNode(ListPointer *P, ListPointer *FreePtr, NodeType Node[])
{
  *P = *FreePtr;
  if (!FullLList(*FreePtr))
    *FreePtr =Node[*FreePtr].Next;
}

void ReleaseNode(NodeType Node[], ListPointer P, ListPointer *FreePtr)
{
  Node[P].Next =*FreePtr;
  Node[P].Data.AM = -1;
  Node[P].Data.grade = -1;

  *FreePtr =P;
}

void Insert(ListPointer *List, NodeType Node[],ListPointer *FreePtr, ListPointer PredPtr, ListElementType Item)
{
  ListPointer TempPtr;
  GetNode(&TempPtr,FreePtr,Node);
  if (!FullLList(TempPtr)) {
    if (PredPtr==NilValue)
    {
        Node[TempPtr].Data.AM = Item.AM;
        Node[TempPtr].Data.grade = Item.grade;
        Node[TempPtr].Next =*List;
        *List =TempPtr;
    }
    else
      {
        Node[TempPtr].Data.AM =Item.AM;
        Node[TempPtr].Data.grade=Item.grade;
        Node[TempPtr].Next =Node[PredPtr].Next;
        Node[PredPtr].Next =TempPtr;
      }
}
  else
    printf("Full List ...\n");
}

void Delete(ListPointer *List, NodeType Node[], ListPointer *FreePtr, ListPointer PredPtr)
{
  ListPointer TempPtr ;

  if (!EmptyLList(*List))
    if (PredPtr == NilValue)
    {
        TempPtr =*List;
        *List =Node[TempPtr].Next;
        ReleaseNode(Node,TempPtr,FreePtr);
    }
    else
      {
        TempPtr =Node[PredPtr].Next;
        Node[PredPtr].Next =Node[TempPtr].Next;
        ReleaseNode(Node,TempPtr,FreePtr);
      }
  else
    printf("Empty List ...\n");
}

void TraverseLinked(ListPointer List, NodeType Node[])

{
  ListPointer CurrPtr;

  if (!EmptyLList(List))
  {
      CurrPtr =List;
      while (CurrPtr != NilValue)
      {
          printf("[%d: (%d,%.1f) ->%d] ",CurrPtr,Node[CurrPtr].Data.AM,Node[CurrPtr].Data.grade, Node[CurrPtr].Next);
          CurrPtr=Node[CurrPtr].Next;
       }
       printf("\n");
   }
  else printf("Empty List ...\n");
}
