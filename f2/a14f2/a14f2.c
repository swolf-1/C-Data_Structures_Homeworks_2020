#include <stdio.h>
#include <stdlib.h>

#define StackLimit 50

typedef int StackElementType;

typedef struct  {
    int Top;
    StackElementType Element[StackLimit];
} StackType;

typedef enum {
    FALSE, TRUE
} boolean;

void CreateStack(StackType *Stack);
void Push(StackType *Stack, StackElementType Item);
void Pop(StackType *Stack, StackElementType *Item);
boolean EmptyStack(StackType Stack);
boolean FullStack(StackType Stack);

int main()
{
    StackType myStack;
    StackElementType M,item,currentMemory;
    CreateStack(&myStack);

    /*Μέγιστη διεύθυνση μνήμης(πρωτη κουκιδα).*/
    printf("Please enter maximum memory address:");
    scanf("%d",&M);

    /*Εισαγωγή διευθύνσεων μνήμης μεχρι να δοθεί η τιμή 0(δευτερη κουκιδα).*/
    do{
        printf("Please enter the next relative memory address:");
        scanf("%d",&item);

        Push(&myStack,item);
    }while(item != 0);

    /*"Διαγραφή" του στοιχείου 0 απο την στοίβα το οποιο χρησιμοποιήθηκε ως
    τιμή τερματισμού και δεν θέλουμε να ελεγχθεί.*/
    Pop(&myStack,&myStack.Element[myStack.Top]);

    /*Τρέχουσα διεύθυνση μνήμης (τριτη κουκίδα).*/
    printf("Please enter the current memory address:");
    scanf("%d",&currentMemory);

    /*Εκτέλεση εντολών μια-μια μεχρι να τελειώσουν ολες ή μεχρι
    η διεύθυνση μνήμης να ξεπεράσει τα επιτρεπτά όρια.*/
    while(myStack.Top != -1)
    {
        currentMemory+=myStack.Element[myStack.Top];
        Pop(&myStack,&myStack.Element[myStack.Top]);

        /*(Τέταρτη κουκίδα)*/
        if((currentMemory >= 0) && (currentMemory <= M))
            printf("Executing instruction: %d\n",currentMemory);
        /*(Πέμπτη κουκίδα)*/
        else
        {
            printf("Access Violation Exception at address:%d\n",currentMemory);
            break;
        }
    }

    return 0;
}

void CreateStack(StackType *Stack)
{
    Stack -> Top = -1;
   // (*Stack).Top = -1;
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

void Pop(StackType *Stack, StackElementType *Item)
{
    if (!EmptyStack(*Stack)) {
        *Item = Stack -> Element[Stack -> Top];
        Stack -> Top--;
    } else
        printf("Empty Stack...");
}
