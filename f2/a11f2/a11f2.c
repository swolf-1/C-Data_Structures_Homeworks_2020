#include <stdio.h>
#include <stdlib.h>

#define StackLimit 20

typedef int StackElementType;
typedef struct  {
    int Top;
    StackElementType Element[StackLimit];
} StackType;

typedef enum {
    FALSE, TRUE
} boolean;

void CreateStack(StackType *Stack);
boolean FullStack(StackType Stack);
boolean EmptyStack(StackType Stack);
void Push(StackType *Stack, StackElementType Item);
void Pop(StackType *Stack, StackElementType *Item);
void TraverseStack(StackType Stack);
void FilterStack(StackType *Stack,StackElementType Item);

int main()
{
    StackType myStack;
    int plithos,i;
    StackElementType item,deleteItem;
    CreateStack(&myStack);


    /*Ανάγνωση πλήθους στοιχείων (Ερώτημα Α) και
      έλεγχος εγκυρότητας ωστε το πλήθος να ειναι
      θετικός μικρότερος του 20.*/
    do{
        printf("Dwse plithos stixeion:");
        scanf("%d",&plithos);
        if(plithos < 0 || plithos > StackLimit)
            printf("To plithos prepei na einai thetikos mikroteros tou 20.");
    }while(plithos < 0 || plithos > StackLimit);

    /*Ανάγνωση στοιχείων και εισαγωγή τους στην στοίβα(Ερώτημα Β).*/
    for(i=0; i < plithos; i++)
    {
       printf("Dwse to %do stoixeio:",i+1);
       scanf("%d",&item);
       Push(&myStack,item);
    }

    /*Ανάγνωση στοιχείου προς διαγραφή(Ερώτημα Γ).*/
    printf("Dwse to stoixeio pou thes na diagrapseis:");
    scanf("%d",&deleteItem);

    /*Κλησή συνάρτησης FilterStack για την διαγραφή του στοιχείου απο την στοίβα.*/
    FilterStack(&myStack,deleteItem);

    return 0;
}

void CreateStack(StackType *Stack)
{
    Stack -> Top = -1;
}

boolean EmptyStack(StackType Stack)
{
    return (Stack.Top == -1);
}

boolean FullStack(StackType Stack)
{
    return (Stack.Top == (StackLimit - 1));
}

void Push(StackType *Stack, StackElementType Item)
{
    if (!FullStack(*Stack)) {
        Stack -> Top++;
        Stack -> Element[Stack -> Top] = Item;
    } else
        printf("Full Stack...");
}

void TraverseStack(StackType Stack)
{
    int i;
    printf("\nplithos sto stack %d\n",Stack.Top+1);
    for (i=0;i<=Stack.Top;i++) {
        printf("%d, ",Stack.Element[i]);
    }
    printf("\n");
}

void Pop(StackType *Stack, StackElementType *Item)
{
    if (!EmptyStack(*Stack)) {
        *Item = Stack -> Element[Stack -> Top];
        Stack -> Top--;
    } else
        printf("Empty Stack...");
}

void FilterStack(StackType *Stack,StackElementType Item)
{
   int i;
   StackType TempStack;

   /*Δημιουργία βοηθιτικής στοίβας.*/
   CreateStack(&TempStack);

   /*Εμφάνιση της στοίβας χρησιμοποιώντας την συνάρτηση TraverseStack.*/
   TraverseStack(*Stack);

   /*Απώθηση στοιχείων στην βοηθιτική στοίβα μέχρι να βρεθεί το στοιχείο προς διαγραφή και
    "διαγραφεί" κάθε φορα του στοιχείου που βρίσκεται στην κορύφη.*/
   for(i=(*Stack).Top;(*Stack).Element[i] != Item; i--)
   {

      Push(&TempStack,(*Stack).Element[i]);
      Pop(&(*Stack),&(*Stack).Element[i]);

      TraverseStack(*Stack);
      TraverseStack(TempStack);
   }

   /*Διαγραφή του στοιχείου που επέλεξε ο χρήστης.*/
   Pop(&(*Stack),&(*Stack).Element[i]);

   TraverseStack(*Stack);
   TraverseStack(TempStack);

   /*Επιστροφή των στοιχείων της βοηθιτικής στοίβας στην αρχική μας στοίβα.*/
   for(i=TempStack.Top;i >= 0; i--)
   {
       Push(&(*Stack),TempStack.Element[i]);
       Pop(&TempStack,&TempStack.Element[i]);

       TraverseStack(TempStack);
       TraverseStack(*Stack);
   }

}
