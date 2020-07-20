#include <stdio.h>
#include <stdlib.h>

#define NumberOfNodes 20
#define NilValue -1

typedef int ListElementType;
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
void sort_list(ListPointer *List, NodeType Node[], boolean Ascending);
void swap(ListPointer PrevPtr,ListPointer CurrentPtr,ListPointer NextPtr,NodeType Node[],ListPointer *List);
int Menu();

int main()
{
    ListPointer AList,FreePtr,PredPtr;
    NodeType Node[NumberOfNodes];
    ListElementType AnItem,numb,i;
    boolean asc;

    InitializeStoragePool(Node, &FreePtr);
    CreateLList(&AList);

    /*Δέχεται τον αριθμό των ακεραίων που θελουμε να εισάγουμε
    και κανει τον κατάλληλο έλεγχο εγκυρότητας.*/
    do{
        printf("Enter number of integers: ");
        scanf("%d",&numb);
        if(numb < 0 || numb >20)
            printf("MH EPITREPTOS ARI8MOS.PROSPA8ISTE KSANA.\n");
    }while(numb < 0 || numb >20);

    /*Εισαγωγή των αριθμών στην λίστα.*/
    for(i=0; i < numb; i++)
    {
        printf("Enter an integer: ");
        scanf("%d",&AnItem);
        PredPtr=NilValue;
        Insert(&AList,Node,&FreePtr,PredPtr,AnItem);
    }

    /*Εμφάνιση του Menou και ενημέρωση της λογικής μεταβλητής asc
    ανάλογα με την επιλογή του χρήστη.*/

    asc=TRUE;

    if(Menu()==2)
        asc=FALSE;

    /*Κλήση συνάρτησης ταξινόμησης.*/
    sort_list(&AList,Node,asc);

    /*Εμφάνηση ταξινομημένης λιστας.*/
    TraverseLinked(AList,Node);

    return 0;
}

void InitializeStoragePool(NodeType Node[], ListPointer *FreePtr)
{
   int i;

    for (i=0; i<NumberOfNodes-1;i++)
    {
        Node[i].Next=i+1;
        Node[i].Data=-1;
    }
    Node[NumberOfNodes-1].Next=NilValue;
    Node[NumberOfNodes-1].Data=NilValue;
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
  Node[P].Data = -1;

  *FreePtr =P;
}

void Insert(ListPointer *List, NodeType Node[],ListPointer *FreePtr, ListPointer PredPtr, ListElementType Item)
{
  ListPointer TempPtr;
  GetNode(&TempPtr,FreePtr,Node);
  if (!FullLList(TempPtr)) {
    if (PredPtr==NilValue)
    {
        Node[TempPtr].Data =Item;
        Node[TempPtr].Next =*List;
        *List =TempPtr;
    }
    else
      {
        Node[TempPtr].Data =Item;
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
          printf("%d ",Node[CurrPtr].Data);
          CurrPtr=Node[CurrPtr].Next;
       }
       printf("\n");
   }
  else printf("Empty List ...\n");
}


int Menu()
{
    int answer;

    printf("----------------------- Select -----------------------\n");
    printf("1.Sort Ascending\n");
    printf("2.Sort Descending\n");

    do{
        scanf("%d",&answer);

        if(answer!=1 && answer!=2)
            printf("WRONG!Pleas try again.");

    }while(answer!=1 && answer!=2);

    return answer;

}

//Η συνάρτηση ταξινόμησης οπως άγινε στο μάθημα.
void sort_list(ListPointer *List, NodeType Node[], boolean Ascending)
{
    ListPointer NextPtr,CurrPtr,PrevPtr,OutPtr;
    boolean swi=FALSE;

    if(!EmptyLList(*List))
    {
        OutPtr = *List;

        while(OutPtr != NilValue)
        {
            CurrPtr = *List;
            PrevPtr = NilValue;
            NextPtr = Node[CurrPtr].Next;

            while(NextPtr != NilValue)
            {
                swi = FALSE;

                if(Ascending == TRUE)
                {
                    if(Node[CurrPtr].Data > Node[NextPtr].Data)
                    {
                        swi = TRUE;
                    }
                }
                else
                {
                    if(Node[CurrPtr].Data < Node[NextPtr].Data)
                    {
                        swi = TRUE;
                    }
                }
                if(swi == TRUE)
                {
                    swap(PrevPtr,CurrPtr,NextPtr,Node,&(*List));

                    if(OutPtr==CurrPtr)
                    {
                        OutPtr = NextPtr;
                    }

                }
                PrevPtr=CurrPtr;
                CurrPtr=NextPtr;
                NextPtr=Node[CurrPtr].Next;
            }
            OutPtr--;
        }
    }
    else
    {
        printf("Empty List...\n");
    }
}

//Η συνάρτηση ενναλαγής οπως άγινε στο μάθημα.
void swap(ListPointer PrevPtr,ListPointer CurrentPtr,ListPointer NextPtr,NodeType Node[],ListPointer *List)
{


    if(CurrentPtr == *List )
    {
        *List = NextPtr;
    }

    Node[CurrentPtr].Next= Node[NextPtr].Next;
    Node[NextPtr].Next = CurrentPtr;

    if(PrevPtr != NilValue)
    {
        Node[PrevPtr].Next = NextPtr;
    }
}


