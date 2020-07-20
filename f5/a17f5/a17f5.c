#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//Αλλαγή στον τυπο του BinTreeElementType.
typedef struct
{
    char data[20];
    char dummy;
} BinTreeElementType;

typedef struct BinTreeNode *BinTreePointer;
 struct BinTreeNode {
    BinTreeElementType Data;
    BinTreePointer LChild, RChild;
} ;

typedef enum {
    FALSE, TRUE
} boolean;

//Συναρτησεις απο το HuffmanDecoding.c .
void BuildDecodingTree(BinTreePointer *Root,   FILE  *CodeFile);
void AddToTree(char ch[], char code[], int codelen, BinTreePointer *Root);
void Decode(BinTreePointer Root, FILE* MessageFile);

int main()
{
    //Δηλωση μεταβλητων.
    FILE *CodeFile,*MessageFile;
    BinTreePointer ARoot;

    //Ανοιγμα του αρχειου.
    CodeFile = fopen("codesRW.txt","r");

    //Αν υπαρχει σφαλμα κατα το ανοιγμα,εμφανιση ενημερωτικου μηνυματος.
    if(CodeFile == NULL)
        printf("Can't open codesRW.txt\n");
    else
    {
        //αλλιως κληση της συναρτησης BuildDecodingTree για την δημιουργια
        //του ΔΔΑ.
        BuildDecodingTree(&ARoot, CodeFile);

        //Ανοιγμα του αρχειου με το κωδικοποιημενο μηνυμα.
        MessageFile = fopen("program.txt","r");

        //Αν υπαρχει θεμα στο ανοιγμα,εμφανιση ενημερωτικου μηνυματος.
        if(MessageFile == NULL)
            printf("Can't oped program.txt\n");
        else
        //αλλιως κληση συναρτησης Decode για αποκωδικοποιηση του μηνυματος.
            Decode(ARoot,MessageFile);
    }

    //Κλείσιμο αρχειου.
    fclose(CodeFile);
    fclose(MessageFile);

    system("PAUSE");
}


/*Ολες οι συναρτησεις υλοποιήθηκαν με βαση το HuffmanDecoding.c,
εχουν γινει οι απαραιτητες αλλαγες ωστε να αποθηκευει μια ολοκληρη λεξη
αντι για εναν χαρακτηρα που ηταν πριν.*/
void BuildDecodingTree(BinTreePointer *Root,   FILE  *CodeFile)
{
    //Αλλαγη ωστε αντι για εναν χαρακτηρα να διαβαζει μια ολοκληρη λεξη.
    char ch[20],code[10],termch;
    int nscan;

    (*Root) = (BinTreePointer)malloc(sizeof (struct BinTreeNode));
    (*Root)->Data.dummy = '*';
    (*Root)->LChild=NULL;
    (*Root)->RChild=NULL;

    while(TRUE)
    {
        /*Αλλαγη ωστε να διαβαζει την λεξη και την κωδικοποιηση της(η οποια
         βρισκεται στην απο κατω σειρα) και αποθηκευση στις αναλογες μεταβλητες.*/
        nscan = fscanf(CodeFile, "%20[^\n]%c\n%10[^\n]\n",ch,&termch,code);

        if(nscan == EOF ) break;
        if(nscan != 3 || termch != '\n')
        {
            printf("Improper file format.\n");
            break;
        }
        else
            AddToTree(ch,code,strlen(code),&(*Root));

    }

}
 //Αλλαγη ωστε αντι για εναν χαρακτηρα να δεχεται μια ολοκληρη λεξη.
void AddToTree(char ch[], char code[], int codelen, BinTreePointer *Root)
{
    int i = 0;
    BinTreePointer TempPtr,p = *Root;

    while(i < codelen)
        if(code[i] == '0')
        {
            if(p->LChild == NULL)
            {
                TempPtr = (BinTreePointer)malloc(sizeof (struct BinTreeNode));
                strcpy(TempPtr->Data.data,"*");
                TempPtr->Data.dummy = '*';
                TempPtr->LChild=NULL;
                TempPtr->RChild=NULL;
                p->LChild=TempPtr;
            }
            i++;
            p = p->LChild;
        }
        else
            if(code[i] == '1')
            {
                if(p->RChild == NULL)
                {
                    TempPtr = (BinTreePointer)malloc(sizeof (struct BinTreeNode));
                    strcpy(TempPtr->Data.data,"*");
                    TempPtr->Data.dummy = '*';
                    TempPtr->LChild=NULL;
                    TempPtr->RChild=NULL;
                    p->RChild = TempPtr;
                }
                i++;
                p = p->RChild;
            }
            //Αλλαγη ωστε να περναει μια λεξη αντι για γραμμα.
            strcpy(p->Data.data,ch);
}

void Decode(BinTreePointer Root, FILE* MessageFile)
{
    char bit;
    BinTreePointer p;

    while(TRUE)
    {
        p = Root;

        while(p->LChild != NULL || p->RChild != NULL)
        {
            bit = fgetc(MessageFile);

            if(bit != EOF)
            {
                printf("%c",bit);

                if(bit == '0')
                    p = p->LChild;
                else
                    if(bit == '1')
                        p=p->RChild;
                    else
                        if(bit != '\n')
                            printf("MH APODEKTO bit:%c \n",bit);

            }
            else break;
        }
        if(bit != EOF ) printf("----%s\n",p->Data.data);
        else break;
    }
}
