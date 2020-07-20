#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char name[20];
    int code;
} BinTreeElementType;

typedef struct BinTreeNode *BinTreePointer;
 struct BinTreeNode {
    BinTreeElementType Data;
    BinTreePointer LChild, RChild;
} ;

typedef enum {
    FALSE, TRUE
} boolean;


void CreateBST(BinTreePointer *Root);
boolean EmptyBST(BinTreePointer Root);
void BSTInsert(BinTreePointer *Root, BinTreeElementType Item);
void BSTSearch(BinTreePointer Root, BinTreeElementType KeyValue, boolean *Found, BinTreePointer *LocPtr);
void BSTSearch2(BinTreePointer Root, BinTreeElementType Item, boolean *Found,BinTreePointer *LocPtr, BinTreePointer *Parent);
void BSTDelete(BinTreePointer *Root, BinTreeElementType KeyValue);
void InorderTraversal(BinTreePointer Root);
void BuildBST(BinTreePointer *Root);
void InorderTraversalPart(BinTreePointer Root, int code);

int main()
{
    BinTreePointer ARoot,LocPtr;
    BinTreeElementType EmpRec;
    boolean found;
    int i;

    //1. Create BST
    BuildBST(&ARoot);

    //2. Insert employees
    for(i = 0; i < 9; i++)
    {
       if(i == 0)
       {
            printf("Give the data for Office Employees.\n");
            printf("-----------------------------------\n");
       }
       else if(i == 3)
       {
            printf("\nGive the data for the Factory Employees.\n");
            printf("----------------------------------------\n");
       }
       else if(i == 6)
       {
            printf("\nGive the data for the Sales Representatives.\n");
            printf("--------------------------------------------\n");
       }

       printf("\nGive the name:");
       fgets(EmpRec.name,20,stdin);
       EmpRec.name[strlen(EmpRec.name)-1]='\0';

       printf("Give the code:");
       scanf("%d",&EmpRec.code);
       getchar();

       BSTInsert(&ARoot,EmpRec);
    }

    //3. Search for an employee by name.
    printf("\n-----------------------\n");
    printf("Give a name for search:");
    fgets(EmpRec.name,20,stdin);
    EmpRec.name[strlen(EmpRec.name)-1]='\0';

    BSTSearch(ARoot,EmpRec,&found,&LocPtr);
    printf("\n-----Search Result-----\n");

    if(found)
    {
        printf("Name:%s\n",LocPtr->Data.name);
        printf("Code:%d\n",LocPtr->Data.code);
    }
    else
        printf("Employee not Found\n");

    //4. List all employees.
    printf("\n----------------------\n");
    printf("List of all Empolyees.\n");
    printf("----------------------\n");
    InorderTraversal(ARoot);

    //5. List office employees.
    printf("\n-------------------------\n");
    printf("List of office Empolyees.\n");
    printf("-------------------------\n");

    InorderTraversalPart(ARoot,1);

    //6. List factory employees.
    printf("\n--------------------------\n");
    printf("List of factory Empolyees.\n");
    printf("--------------------------\n");

    InorderTraversalPart(ARoot,2);

    //7. List sale representatives.
    printf("\n----------------------------\n");
    printf("List of Sale Representatives.\n");
    printf("----------------------------\n");

    InorderTraversalPart(ARoot,3);

    //8. Delete an employee record.
    printf("----------------------\n");
    printf("Give a name to delete:");
    fgets(EmpRec.name,20,stdin);
    EmpRec.name[strlen(EmpRec.name)-1]='\0';

    BSTDelete(&ARoot,EmpRec);

    return 0;
}

void CreateBST(BinTreePointer *Root)
{
    *Root = NULL;
}

boolean EmptyBST(BinTreePointer Root)
{
    return (Root==NULL);
}

void BSTInsert(BinTreePointer *Root, BinTreeElementType Item)
{
    BinTreePointer LocPtr, Parent;
    boolean Found;

    LocPtr = *Root;
    Parent = NULL;
    Found = FALSE;
    while (!Found && LocPtr != NULL) {
        Parent = LocPtr;
        if (strcmp(Item.name,LocPtr->Data.name) < 0)
            LocPtr = LocPtr ->LChild;
        else if (strcmp(Item.name,LocPtr->Data.name) > 0)
            LocPtr = LocPtr ->RChild;
        else
            Found = TRUE;
    }
    if (Found)
        printf("To %s EINAI HDH STO DDA\n", Item.name);
    else {
        LocPtr = (BinTreePointer)malloc(sizeof (struct BinTreeNode));
        LocPtr ->Data = Item;
        LocPtr ->LChild = NULL;
        LocPtr ->RChild = NULL;
        if (Parent == NULL)
            *Root = LocPtr;
        else if (strcmp(Item.name,Parent->Data.name) < 0)
            Parent ->LChild = LocPtr;
        else
            Parent ->RChild = LocPtr;
    }
}

void BSTSearch(BinTreePointer Root, BinTreeElementType KeyValue, boolean *Found, BinTreePointer *LocPtr)

{

    (*LocPtr) = Root;
    (*Found) = FALSE;
    while (!(*Found) && (*LocPtr) != NULL)
    {
        if (strcmp(KeyValue.name,(*LocPtr)->Data.name) < 0)
            (*LocPtr) = (*LocPtr)->LChild;
        else
            if (strcmp(KeyValue.name,(*LocPtr)->Data.name) > 0)
                (*LocPtr) = (*LocPtr)->RChild;
            else (*Found) = TRUE;
    }
}

void BSTSearch2(BinTreePointer Root, BinTreeElementType KeyValue, boolean *Found, BinTreePointer *LocPtr, BinTreePointer *Parent)
{
    *LocPtr = Root;
    *Parent=NULL;
    *Found = FALSE;
    while (!(*Found) && *LocPtr != NULL)
    {
        if (strcmp(KeyValue.name,(*LocPtr)->Data.name) < 0)
        {
            *Parent=*LocPtr;
            *LocPtr = (*LocPtr)->LChild;
        }
        else
            if (strcmp(KeyValue.name,(*LocPtr)->Data.name) > 0)
            {
                *Parent=*LocPtr;
                *LocPtr = (*LocPtr)->RChild;
            }
            else *Found = TRUE;
    }

}

void BSTDelete(BinTreePointer *Root, BinTreeElementType KeyValue)
{

   BinTreePointer
   n,                   //δείχνει στον κόμβο που περιέχει την τιμή KeyValue *)
   Parent,              // πατέρας του n ή του nNext
   nNext,               // ενδοδιατεταγμένος επόμενος του n
   SubTree;             // δείκτης προς υποδέντρο του n
   boolean Found;       // TRUE AN TO ΣΤΟΙΧΕΙΟ KeyValue EINAI ΣΤΟΙΧΕΟ ΤΟΥ ΔΔΑ *)

     BSTSearch2(*Root, KeyValue, &Found , &n, &Parent);
     if (!Found)
        printf("TO STOIXEIO %s DEN EINAI STO DDA\n", KeyValue.name);
     else {
          if (n->LChild != NULL && n->RChild != NULL)
          {  // κόμβος προς διαγραφή με δύο παιδιά
                 //Βρες τον ενδοδιατεταγμένο επόμενο και τον πατέρα του
                 nNext = n->RChild;
                 Parent = n;
                 while (nNext->LChild !=NULL)  //* DIASXISH PROS TA ARISTERA *)
                 {
                      Parent = nNext;
                      nNext = nNext->LChild;
                 }
                /* Αντιγραφή των περιεχομένων του nNext στον n και
                αλλαγή του n ώστε να δείχνει στον επόμενο */
                n->Data = nNext->Data;
                n = nNext;
          } //Συνεχίζουμε με την περίπτωση που ο κόμβος έχει το πολύ 1 παιδί
          SubTree = n->LChild;
          if (SubTree == NULL)
             SubTree = n->RChild;
          if (Parent == NULL)                 //* 8A DIAGRAFEI H RIZA *)
             *Root = SubTree;
          else if (Parent->LChild == n)
                  Parent->LChild = SubTree;
               else
                   Parent->RChild = SubTree;
          free(n);
     }
}

void InorderTraversal(BinTreePointer Root)
{
    if (Root!=NULL) {
        InorderTraversal(Root->LChild);
        printf("%s \n",Root->Data.name);
        InorderTraversal(Root->RChild);
    }
}

void BuildBST(BinTreePointer *Root)
{
    FILE *input;
    int nscan;
    BinTreeElementType EmpRec;


    CreateBST(&(*Root));
    input = fopen("I12F5.TXT","r");

    if(input == NULL)
    {
        printf("Problem opening file.\n");
    }
    else
        while(TRUE)
        {
            nscan = fscanf(input,"%20[^,],%d\n",EmpRec.name,&EmpRec.code);
            if(nscan == EOF) break;
            if(nscan != 2) printf("Error\n");


            BSTInsert(&(*Root),EmpRec);
        }

    fclose(input);
}

void InorderTraversalPart(BinTreePointer Root, int code)
{
    if(!EmptyBST(Root))
    {
        InorderTraversalPart(Root->LChild,code);

        if(Root->Data.code == code)
        {
            printf("Name:%s\n",Root->Data.name);
            printf("Code:%d\n\n",Root->Data.code);
        }

        InorderTraversalPart(Root->RChild,code);
    }
}


