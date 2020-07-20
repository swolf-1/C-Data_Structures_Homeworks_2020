#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Αλλαγη του τυπου BinTreeElementType
typedef struct
{
    int code;
    int recNo;
} BinTreeElementType;

//Δημιουργια εγγραφης student.
typedef struct
{
    int code;
    char surname[20];
    char name[20];
    char sex;
    int year;
    float grade;

}studentT;

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
void menu(int *choise);
int BuildBST(BinTreePointer *Root);
void InsertNewStudent(BinTreePointer *Root,int *size);
void SearchStudent(BinTreePointer Root);
void PrintStudent(int RecNum);
void PrintStudentsWithGrade();



int main()
{
    //Δηλωση μεταβλητων.
    BinTreePointer ARoot;
    int size,choise;

    //Επαναλαμβανομενη εμφανιση του menou μεχρι να αποφασισει ο χρηστης να σταματησει.
    while(TRUE)
    {
        menu(&choise);
        switch(choise)
        {
            //Στην περιπτωση που η επιλογη ειναι 1 κληση της συνάρτησης για δημιουργια ΔΔΑ(index).
            case 1:
                size = BuildBST(&ARoot);
                break;
            //Στην περιπτωση που η επιλογη ειναι 2 κληση της συνάρτησης για εισαγωγη νεου φοιτητη στο ΔΔΑ και στο αρχειο.
            case 2:
                InsertNewStudent(&ARoot,&size);
                break;
            //Στην περιπτωση που η επιλογη ειναι 3 κληση της συνάρτησης για αναζητηση ενος φοιτητη και εμφανιση τον στοιχειων του.
            case 3:
                SearchStudent(ARoot);
                break;
            //Στην περιπτωση που η επιλογη ειναι 4 κληση της συνάρτησης για εμφανιση ολων των φοιτητων απο το ΔΔΑ.
            case 4:
                printf("\nPrint all students data.\n\n");
                RecBSTInorder(ARoot);
                printf("\n");
                break;
            case 5:
            //Στην περιπτωση που η επιλογη ειναι 5 κληση της συνάρτησης για εμφανιση στοιχειων φοιτητων με βαθμο μεγαλυτερο απο μια τιμη.
                PrintStudentsWithGrade();
                break;
            //Στην περιπτωση που η επιλογη ειναι 6,τελος προγραμματος.
            case 6:
                return 0;
        }
    }
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
        if (Item.code < (*Root)->Data.code)
            RecBSTInsert(&(*Root) ->LChild,Item);
        else if (Item.code > (*Root)->Data.code)
            RecBSTInsert(&(*Root) ->RChild,Item);
        else
            printf("To %d EINAI HDH STO DDA\n", Item.code);
}

void RecBSTSearch(BinTreePointer Root, BinTreeElementType KeyValue,boolean *Found, BinTreePointer *LocPtr)
{
    if (BSTEmpty(Root))
        *Found=FALSE;
    else
        if (KeyValue.code < Root->Data.code)
            RecBSTSearch(Root->LChild, KeyValue, &(*Found), &(*LocPtr));
        else
            if (KeyValue.code > Root->Data.code)
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
        printf("to %d DeN BRE8HKe STO DDA\n", KeyValue.code);
     else
         //* αναζήτησε αναδρομικά τον κόμβο που περιέχει την τιμή KeyValue και διάγραψέ τον
          if (KeyValue.code < (*Root)->Data.code)
             RecBSTDelete(&((*Root)->LChild), KeyValue);       //* ΑΡΙΣΤΕΡΟ ΥΠΟΔΕΝΔΡΟ *
          else
            if (KeyValue.code > (*Root)->Data.code)
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
        RecBSTInorder(Root->LChild);
        printf(" (%d, %d),",Root->Data.code,Root->Data.recNo);
        RecBSTInorder(Root->RChild);
    }

}

void RecBSTPreorder(BinTreePointer Root)
{
    if (Root!=NULL) {
        printf("/%d /",Root->Data.code);
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
        printf("/%d /",Root->Data.code);
    }
    printf("U");
}

/*Συναρτηση menu που εμφανιζει τις επιλογες που εχει ο χρηστης και επιστρεφει
την επιλογη αυτη μεσω της μεταβλητησ δεικτη choise.Αν η τιμη που θα δοθει δεν
ειναι μεταξυ 1-6 ,εμφανιση μηνυματος λαθους.*/
void menu(int *choise)
{
    printf("\n                       MENOY                     \n");
    printf("-------------------------------------------------\n");
    printf("1. Build BST\n");
    printf("2. Insert new student\n");
    printf("3. Search for a student\n");
    printf("4. Print all students (Traverse Inorder)\n");
    printf("5. Print students with a >= given grade\n");
    printf("6. Quit\n");

    do{
        printf("\nEpilogh: ");
        scanf("%d",&(*choise));

        if(*choise < 1 || *choise > 6)
            printf("Number must be between 1-6.Try again.\n");
    }while(*choise < 1 || *choise > 6);
}

int BuildBST(BinTreePointer *Root)
{
    //Δήλωση μεταβλητών
    FILE *infile;
    studentT student;
    BinTreeElementType indexRec;
    int size,nscan;

    //Δημιουργια ΔΔΑ.
    CreateBST(&(*Root));

    //Ανοιγμα του αρχειου για αναγνωση.
    infile = fopen("foitites.dat","r");

    //Αρχικοποίηση του μετρητη εγγραφών
    size = 0;

    //Αν ανοιξει σωστα το αρχειο.
    if(infile != NULL)
        while(TRUE)
        {
            //Διαβασμα του αρχειου γραμμη-γραμμη και περασμα των δεδομενων στα αναλογα πεδία της εγγραφης Student.
            nscan = fscanf(infile,"%d, %20[^,], %20[^,], %c, %d, %f\n",&student.code, student.surname, student.name, &student.sex, &student.year, &student.grade);
            if(nscan == EOF) break;
            if(nscan != 6)
            {
                printf("Improper file format.\n");
                break;
            }
            //Περασμα του ΑΜ και του αριθμου σειρας που διβαστηκε η εγγραφη στο επξεηήξην(index).
            indexRec.code = student.code;
            indexRec.recNo = size;

            //Εισαγωγη στο ΔΔΑ.
            RecBSTInsert(&(*Root),indexRec);

            //Αυξηση του μετρτη κατα 1.
            size++;
        }
    //Κλεισιμο τυο αρχειου.
    fclose(infile);

    //Επιστροφη του μετρητη.
    return size;
}

void InsertNewStudent(BinTreePointer *Root,int *size)
{
    //Δηλωση μεταβλητων.
    FILE *infile;
    studentT student;
    BinTreeElementType indexRec;
    boolean found;
    BinTreePointer LocPtr;

    //Ανοιγμα του αρχειου για προσάρτηση.
    infile = fopen("foitites.dat","a");

    //Διαβασμα του ΑΜ προς αναζητηση.
    printf("Give students AM: ");
    scanf("%d",&indexRec.code);

    //Αναζητση στο ΔΔΑ.
    RecBSTSearch(*Root,indexRec,&found,&LocPtr);

    //Αν δεν υπαρχει
    if(!found)
    {
        //Περναμε τα δεδομενα στην εγγραφη.
        student.code = indexRec.code;

        printf("Give student surname: ");
        scanf("%s",student.surname);

        printf("Give student name: ");
        scanf("%s",student.name);

        printf("Give student's registration year: ");
        scanf("%d",&student.year);

        printf("Give student's grade: ");
        scanf("%f",&student.grade);

        printf("Give student sex F/M: ");
        scanf(" %c",&student.sex);

        indexRec.recNo = *size;

        //Εισαγωγη στο ΔΔΑ.
        RecBSTInsert(&(*Root),indexRec);

        //Εισαγωγη στο αρχειο.
        fprintf(infile,"%d, %s, %s, %c, %d, %.1f\n", student.code, student.surname, student.name, student.sex, student.year, student.grade);

        //Αυξηση του μετρτη κατα 1.
        size++;
    }
    //Αν δεν υπαρχει εμφανιση αναλογου μηνυματος.
    else
        printf("Afto to AM yparxei hdh.\n");

    //Κλεισιμο τυο αρχειου.
    fclose(infile);
}

void SearchStudent(BinTreePointer Root)
{
    //Δηλωση μεταβλητων.
    BinTreeElementType indexRec;
    BinTreePointer LocPtr;
    boolean found;

    //Διαβασμα του ΑΜ προς αναζητηση.
    printf("\nGive student's code: ");
    scanf("%d",&indexRec.code);
    printf("\n");

    //Αναζητση στο ΔΔΑ.
    RecBSTSearch(Root,indexRec,&found,&LocPtr);

    //Αν υπαρχει εμφανιση στοιχειων με την βοηθεια τησ συναρτησης PrintStudent.
    if(found)
        PrintStudent(LocPtr->Data.recNo);
    //Αν δεν υπαρχει εμφανιση αναλογου μηνυματος.
    else
        printf("Student NOT found.\n");
}

void PrintStudent(int RecNum)
{
    //Δηλωση μεταβλητων.
    FILE *infile;
    int nscan,lines;
    studentT student;

    //Ανοιγμα του αρχειου για αναγνωση.
    infile = fopen("foitites.dat","r");

    //Αρχικοποιηση της μεταβλητης που μετρα τις γραμμες που διαβαστηκαν
    lines = 0;

    //Αν ανοιξει σωστα το αρχειο.
    if(infile != NULL)
    {

        while(lines <= RecNum)
        {
            //Διαβασμα του αρχειου γραμμη-γραμμη και περασμα των δεδομενων στα αναλογα πεδία της εγγραφης Student.
            nscan = fscanf(infile,"%d, %20[^,], %20[^,], %c, %d, %f\n",&student.code, student.surname, student.name, &student.sex, &student.year, &student.grade);
            if(nscan == EOF) break;
            if(nscan != 6)
            {
                printf("Improper file format.\n");
                break;
            }
            //Αυξηση του μετρητη κατα.
            lines++;
        }
        //Μολις φτασει στην γραμμη που θελουμε εμφανιση και εχουν διαβαστει γραμμες εμφανιση των στοιχειων του φοιτητη.
        if(lines)
            printf("%d,%s,%s,%c,%d,%.1f\n",student.code,student.name,student.surname,student.sex,student.year,student.grade);
    }
    //Κλεισιμο τυο αρχειου.
    fclose(infile);
}
void PrintStudentsWithGrade()
{
    //Δηλωση μεταβλητων.
    FILE *infile;
    int nscan;
    studentT student;
    float theGrade;

    //Διαβασμα του βαθμου με τον οποιο θελουμε να συγκρινουμε.
    printf("Give the grade: ");
    scanf("%f",&theGrade);

    //Ανοιγμα του αρχειου για αναγνωση.
    infile = fopen("foitites.dat","r");

    //Ενημερωτικο μηνυμα.
    printf("Student's with grade >= %.1f\n\n",theGrade);

    //Αν ανοιξει σωστα το αρχειο.
    if(infile != NULL)
        while(TRUE)
        {
            //Διαβασμα του αρχειου γραμμη-γραμμη και περασμα των δεδομενων στα αναλογα πεδία της εγγραφης Student.
            nscan = fscanf(infile,"%d, %20[^,], %20[^,], %c, %d, %f\n",&student.code, student.surname, student.name, &student.sex, &student.year, &student.grade);
            if(nscan == EOF) break;
            if(nscan != 6)
            {
                printf("Improper file format.\n");
                break;
            }
            //Αν ο φοιτητς που διαβαστικε εχει >= βαθμο απο αυτον που δοθηκε να εμφανιστουν τα στοιχεια του.
            if(student.grade >= theGrade)
                printf("%d,%s,%s,%c,%d,%.1f\n",student.code,student.name,student.surname,student.sex,student.year,student.grade);
        }
        printf("\n");

        //Κλεισιμο τυο αρχειου.
        fclose(infile);
}

