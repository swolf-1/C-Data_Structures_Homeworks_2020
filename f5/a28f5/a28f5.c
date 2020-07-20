#include <stdio.h>
#include <stdlib.h>


typedef int BinTreeElementType;

typedef struct BinTreeNode *BinTreePointer;

 struct BinTreeNode {
    BinTreeElementType Data;
    BinTreePointer LChild, RChild;
} ;

typedef enum {
    FALSE, TRUE
} boolean;


void CreateBST(BinTreePointer *Root);
boolean BSTEmpty(BinTreePointer Root);
void RecBSTInsert(BinTreePointer *Root, BinTreeElementType Item);
void RecBSTSearch(BinTreePointer Root, BinTreeElementType KeyValue, boolean *Found, BinTreePointer *LocPtr);
void RecBSTDelete(BinTreePointer *Root, BinTreeElementType KeyValue);
void RecBSTInorder(BinTreePointer Root);
void RecBSTPreorder(BinTreePointer Root);
void RecBSTPostorder(BinTreePointer Root);
int Number_Ceiling(BinTreePointer Root, BinTreeElementType Item);
int Number_Floor(BinTreePointer Root, BinTreeElementType Item);

int main()
{
    //Δηλωση μεταβλητων.
    BinTreePointer ARoot;
    BinTreeElementType Insert_Item,Search_Item;
    int Ceiling,Floor;

    //Δημιουργια κενου ΔΔΑ
    CreateBST(&ARoot);

    /*Δομή επαναληψης για εισαγωγη στοιχειων στο ΔΔΑ μεχρι να δοθει αρνητικος αριθμος.*/
    while(TRUE)
    {
        printf("Enter number to insert: ");
        scanf("%d",&Insert_Item);

        if(Insert_Item < 0)
            break;
        else if(Insert_Item == 0)
            printf("Number must be > 0 or < 0(If you want to stop inserting).\n");
        else
            RecBSTInsert(&ARoot,Insert_Item);
    }

    /*Δομη επαναληψης για αναζητηση ενος στοιχειου και ευρεση του Ceiling και Floor του
    μεχρι να δοθει αρνητικος αριθμος.*/
    while(TRUE)
    {
        printf("Enter number to search: ");
        scanf("%d",&Search_Item);

        if(Search_Item < 0)
            break;
        else if(Search_Item == 0)
            printf("Number must be > 0 or < 0(If you want to stop inserting).\n");
        else
        {
            Ceiling = Number_Ceiling(ARoot,Search_Item);
            printf("Ceiling:%d\n",Ceiling);

            Floor = Number_Floor(ARoot,Search_Item);
            printf("Floor:%d\n",Floor);
        }
    }

    return 0;
}

void CreateBST(BinTreePointer *Root)
{
    *Root = NULL;
}

boolean BSTEmpty(BinTreePointer Root)
{
    return (Root==NULL);
}

void RecBSTInsert(BinTreePointer *Root, BinTreeElementType Item)
{
    if (BSTEmpty(*Root)) {
        (*Root) = (BinTreePointer)malloc(sizeof (struct BinTreeNode));
        (*Root) ->Data = Item;
        (*Root) ->LChild = NULL;
        (*Root) ->RChild = NULL;
    }
    else
        if (Item < (*Root) ->Data)
            RecBSTInsert(&(*Root) ->LChild,Item);
        else if (Item > (*Root) ->Data)
            RecBSTInsert(&(*Root) ->RChild,Item);
        else
            printf("To %d EINAI HDH STO DDA\n", Item);
}

void RecBSTSearch(BinTreePointer Root, BinTreeElementType KeyValue, boolean *Found, BinTreePointer *LocPtr)
{

    if (BSTEmpty(Root))
        *Found=FALSE;
    else
        if (KeyValue < Root->Data)
            RecBSTSearch(Root->LChild, KeyValue, &(*Found), &(*LocPtr));
        else
            if (KeyValue > Root->Data)
                RecBSTSearch(Root->RChild, KeyValue, &(*Found), &(*LocPtr));
            else
                {
                    *Found = TRUE;
                    *LocPtr=Root;
                }
}

void RecBSTDelete(BinTreePointer *Root, BinTreeElementType KeyValue)
{

   BinTreePointer TempPtr;          //* true AN TO STOIXEIO KeyValue EINAI STOIXEIO TOY DDA *)

    if (BSTEmpty(*Root))          //* ΑΔΕΙΟ ΔΕΝΔΡΟ ΤΟ KeyValue ΔΕ ΘΑ ΒΡΕΘΕΙ *)
        printf("to %d DeN BRE8HKe STO DDA\n", KeyValue);
     else
         //* αναζήτησε αναδρομικά τον κόμβο που περιέχει την τιμή KeyValue και διάγραψέ τον
          if (KeyValue < (*Root)->Data)
             RecBSTDelete(&((*Root)->LChild), KeyValue);       //* ΑΡΙΣΤΕΡΟ ΥΠΟΔΕΝΔΡΟ *
          else
            if (KeyValue > (*Root)->Data)
                  RecBSTDelete(&((*Root)->RChild), KeyValue);   //* ΔΕΞΙ  ΥΠΟΔΕΝΔΡΟ *
            else                                       //* TO KeyValue ΒΡΕΘΗΚΕ ΔΙΑΓΡΑΦΗ ΤΟΥ ΚΟΜΒΟΥ *)
                if ((*Root)->LChild ==NULL)
                 {
                      TempPtr = *Root;
                      *Root = (*Root)->RChild;      //* ΔΕΝ ΕΧΕΙ ΑΡΙΣΤΕΡΟ ΠΑΙΔΙ *)
                      free(TempPtr);
                 }
                else if ((*Root)->RChild == NULL)
                   {
                        TempPtr = *Root;
                        *Root = (*Root)->LChild;      //* ΕΧΕΙ ΑΡΙΣΤΕΡΟ ΠΑΙΔΙ, ΑΛΛΑ ΟΧΙ ΔΕΞΙ *)
                        free(TempPtr);
                   }
                   else                               //* ΕΧΕΙ 2 ΠΑΙΔΙΑ *)
                   {
                        //* ΕΥΡΕΣΗ ΤΟΥ INORDER ΑΠΟΓΟΝΟΥ ΤΟΥ *)
                        TempPtr = (*Root)->RChild;
                        while (TempPtr->LChild != NULL)
                              TempPtr = TempPtr->LChild;
                        /* ΜΕΤΑΚΙΝΗΣΗ ΤΟΥ ΑΠΟΓΟΝΟΥ ΤΗς ΡΙΖΑΣ ΤΟΥ ΥΠΟΔΕΝΔΡΟΥ
                        ΠΟΥ ΕΞΕΤΑΖΕΤΑΙ ΚΑΙ ΔΙΑΓΡΑΦΗ ΤΟΥ ΑΠΟΓΟΝΟΥ ΚΟΜΒΟΥ */
                        (*Root)->Data = TempPtr->Data;
                        RecBSTDelete(&((*Root)->RChild), (*Root)->Data);
                   }
}

void RecBSTInorder(BinTreePointer Root)
{
    if (Root!=NULL) {
        printf("L");
        RecBSTInorder(Root->LChild);
        printf("/%d/",Root->Data);
        printf("R");
        RecBSTInorder(Root->RChild);
    }
    printf("U");
}

void RecBSTPreorder(BinTreePointer Root)
{
    if (Root!=NULL) {
        printf("/%d /",Root->Data);
        printf("L");
        RecBSTPreorder(Root->LChild);
        printf("R");
        RecBSTPreorder(Root->RChild);
    }
    printf("U");
}

void RecBSTPostorder(BinTreePointer Root)
{
    if (Root!=NULL) {
        printf("L");
        RecBSTPostorder(Root->LChild);
        printf("R");
        RecBSTPostorder(Root->RChild);
        printf("/%d /",Root->Data);
    }
    printf("U");
}


int Number_Ceiling(BinTreePointer Root, BinTreeElementType Item)
{
    int ceil;

    if(BSTEmpty(Root))
        return -1;
    else if (Root->Data == Item)
        return Item;
    else if (Item > Root->Data)
        return Number_Ceiling(Root->RChild,Item);
    else
        ceil = Number_Ceiling(Root->LChild,Item);

    if(ceil == -1)
        return Root->Data;

    return ceil;

}

int Number_Floor(BinTreePointer Root, BinTreeElementType Item)
{
    int floor;

    if(BSTEmpty(Root))
        return -1;
    else if(Root->Data == Item)
        return Item;
    else if(Item < Root->Data)
        return Number_Floor(Root->LChild,Item);
    else
        floor = Number_Floor(Root->RChild,Item);

    if(floor == -1)
        return Root->Data;

    return floor;
}

