#include <stdio.h>
#include <stdlib.h>

typedef int ListElementType;

typedef struct ListNode *ListPointer;
typedef struct ListNode
{
	ListElementType Data;
    ListPointer Next;
} ListNode;

typedef enum {
    FALSE, TRUE
} boolean;

void CreateList(ListPointer *List);
boolean EmptyList(ListPointer List);
void LinkedInsert(ListPointer *List, ListElementType Item, ListPointer PredPtr);
void LinkedDelete(ListPointer *List, ListPointer PredPtr);
void LinkedTraverse(ListPointer List);
void LinearSearch(ListPointer List, ListElementType Item, ListPointer *PredPtr, boolean *Found);
void OrderedLimearSearch(ListPointer List, ListElementType Item, ListPointer *PredPtr, boolean *Found);
void Intersection_List(ListPointer ListA,ListPointer ListB,ListPointer *FinalList);

int main()
{
    ListPointer List_A,List_B,List_Intersection;
    ListElementType Item;
    int i,n;

    CreateList(&List_A);
    CreateList(&List_B);

    /*Διαβασμα πληθους στοιχειων για την Α Λιστα.*/
    printf("Give the number of integers for List A:");
    scanf("%d",&n);

    /*Διαβαζμα στοιχειων και εισαγωγη.*/
    printf("----List_A----\n");
    for(i = 0; i < n; i++)
    {
        printf("Give an integer:");
        scanf("%d",&Item);
        LinkedInsert(&List_A,Item,NULL);
    }

    /*Διαβασμα πληθους στοιχειων για την Β Λιστα.*/
    printf("\nGive the number of integers for List B:");
    scanf("%d",&n);

    /*Διαβαζμα στοιχειων και εισαγωγη.*/
    printf("----List_B----\n");
    for(i = 0; i < n; i++)
    {
        printf("Give an integer:");
        scanf("%d",&Item);
        LinkedInsert(&List_B,Item,NULL);
    }

    /*Εμφανιση Α Λιστας.*/
    printf("\n----List_A----\n");
    LinkedTraverse(List_A);

    /*Εμφανιση Β Λιστας.*/
    printf("\n----List_B----\n");
    LinkedTraverse(List_B);
    /*Κλήση συναρτησης για ευρεση τομης.*/
    Intersection_List(List_A,List_B,&List_Intersection);

    /*Εμφανιση τελικης λιστας που περιεχει την τομη.*/
    printf("\n----Intersection List----\n");
    LinkedTraverse(List_Intersection);

    return 0;
}

void CreateList(ListPointer *List)
{
	*List = NULL;
}

boolean EmptyList(ListPointer List)
{
	return (List==NULL);
}

void LinkedInsert(ListPointer *List, ListElementType Item, ListPointer PredPtr)
{
	ListPointer TempPtr;

   TempPtr= (ListPointer)malloc(sizeof(struct ListNode));
 /*  printf("Insert &List %p, List %p,  &(*List) %p, (*List) %p, TempPtr %p\n",
   &List, List,  &(*List), (*List), TempPtr); */
   TempPtr->Data = Item;
	if (PredPtr==NULL) {
        TempPtr->Next = *List;
        *List = TempPtr;
    }
    else {
        TempPtr->Next = PredPtr->Next;
        PredPtr->Next = TempPtr;
    }
}

void LinkedDelete(ListPointer *List, ListPointer PredPtr)
{
    ListPointer TempPtr;

    if (EmptyList(*List))
   	    printf("EMPTY LIST\n");
   else
   {
   	    if (PredPtr == NULL)
        {
      	      TempPtr = *List;
              *List = TempPtr->Next;
        }
        else
        {
      	     TempPtr = PredPtr->Next;
             PredPtr->Next = TempPtr->Next;
        }
        free(TempPtr);
    }
}

void LinkedTraverse(ListPointer List)
{
	ListPointer CurrPtr;

   if (EmptyList(List))
   	    printf("EMPTY LIST\n");
   else
   {
   	    CurrPtr = List;
         while ( CurrPtr!=NULL )
        {
             printf("%d ",(*CurrPtr).Data);
             CurrPtr = CurrPtr->Next;
        }
        printf("\n");
   }
}

void LinearSearch(ListPointer List, ListElementType Item, ListPointer *PredPtr, boolean *Found)
{
   ListPointer CurrPtr;
   boolean stop;

   CurrPtr = List;
    *PredPtr=NULL;
   stop= FALSE;
   while (!stop && CurrPtr!=NULL )
    {
         if (CurrPtr->Data==Item )
         	stop = TRUE;
         else
         {
         	*PredPtr = CurrPtr;
            CurrPtr = CurrPtr->Next;
         }
	}
	*Found=stop;
}

void OrderedLimearSearch(ListPointer List, ListElementType Item, ListPointer *PredPtr, boolean *Found)
{
   ListPointer CurrPtr;
   boolean DoneSearching;

   CurrPtr = List;
   *PredPtr = NULL;
   DoneSearching = FALSE;
   *Found = FALSE;
   while (!DoneSearching && CurrPtr!=NULL )
    {
         if (CurrPtr->Data>=Item )
         {
         	DoneSearching = TRUE;
         	*Found = (CurrPtr->Data==Item);
         }
         else
         {
         	*PredPtr = CurrPtr;
            CurrPtr = CurrPtr->Next;
         }
	}
}

void Intersection_List(ListPointer ListA,ListPointer ListB,ListPointer *FinalList)
{
    ListPointer TempPtr1,TempPtr2;

    /*Δημιουργία της τελικής λιστα που θα περιέχει την τομή.*/
    CreateList(FinalList);

    TempPtr1 = ListA;

    while(TempPtr1 != NULL)
    {
        TempPtr2 = ListB;

        while(TempPtr2 != NULL)
        {
            if(TempPtr1->Data == TempPtr2->Data)
            {
                LinkedInsert(FinalList,TempPtr1->Data,NULL);
                break;
            }


            TempPtr2=TempPtr2->Next;
        }

        TempPtr1 = TempPtr1->Next;
    }

}
