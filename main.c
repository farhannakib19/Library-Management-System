#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
    #define CLEAR() system("cls")
#else
    #define CLEAR() system("clear")
#endif

struct Book {
    int  id;
    char name[50];
    char author[50];
    int  quantity;
    int  rack;
};

struct Member {
    int  id;
    char name[50];
    char type[20];
    char password[20];
};

struct Issue {
    int bookId;
    int memberId;
    int daysUsed;
    int returned;
};

FILE *file, *file2;
struct Book   a;
struct Member m;
int  d = 1;
int  choice;

void heading(void);
void userType(void);
void login(void);
void mainMenu(void);

void addBook(void);
void viewBook(void);
void searchBook(void);
void editBook(void);
void deleteBook(void);

void addMember(void);
void updateDeleteMember(void);

void returnBookFine(void);
void dueDateReport(void);

void pause_screen(void);
void clearInputBuffer(void);


int main()
{
    userType();
    login();
    return 0;
}

void heading(void)
{
    printf("\n\n\t********************************************\n");
    printf("\t*        LIBRARY  MANAGEMENT  SYSTEM      *\n");
    printf("\t********************************************\n");
}

void clearInputBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void pause_screen(void)
{
    printf("\n\n\t\tpress any key...");
    clearInputBuffer();
    getchar();
}

void userType(void)
{
    CLEAR();
    heading();
    printf("\n\tAre you:\n\n");
    printf("\t1. Student\n");
    printf("\t2. Teacher\n");
    printf("\t3. Others\n");
    printf("\n\t********************************************\n");
    printf("\tEnter your choice: ");
    scanf("%d", &choice);

    if (choice < 1 || choice > 3) {
        printf("\n\tInvalid choice!\n");
        pause_screen();
        userType();
    }
}

void login(void)
{
    int  id, found = 0;
    char pass[20];

    CLEAR();
    heading();
    printf("\n\tFor login in Main Menu\n\n");
    printf("\tEnter ID: ");
    scanf("%d", &id);
    printf("\tEnter Password: ");
    scanf("%s", pass);

    if (id == 1 && strcmp(pass, "admin123") == 0) {
        found = 1;
    } else {
        file = fopen("members.dat", "rb");
        if (file != NULL) {
            while (fread(&m, sizeof(m), 1, file) == 1) {
                if (m.id == id && strcmp(m.password, pass) == 0) {
                    found = 1;
                    break;
                }
            }
            fclose(file);
        }
    }

    if (found) {
        printf("\n\n\t\tLogin Successful!\n");
        pause_screen();
        mainMenu();
    } else {
        printf("\n\n\t\tInvalid ID or Password!\n");
        pause_screen();
        login();
    }
}

void mainMenu(void)
{
    CLEAR();
    printf("\t********************** Main Menu **********************\n\n");
    printf("\t1.  Add Book\n");
    printf("\t2.  View Book List\n");
    printf("\t3.  Search Book\n");
    printf("\t4.  Edit Book\n");
    printf("\t5.  Delete Book\n");
    printf("\t6.  Add New Member\n");
    printf("\t7.  Update / Delete Member Record\n");
    printf("\t8.  Return Book and Fine Collection\n");
    printf("\t9.  Due Date Tracking & Overdue Report\n");
    printf("\t10. Exit\n");
    printf("\n\t*********************************************************\n");
    printf("\tEnter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:  addBook();            break;
        case 2:  viewBook();           break;
        case 3:  searchBook();         break;
        case 4:  editBook();           break;
        case 5:  deleteBook();         break;
        case 6:  addMember();          break;
        case 7:  updateDeleteMember(); break;
        case 8:  returnBookFine();     break;
        case 9:  dueDateReport();      break;
        case 10:
            printf("\n\n\t\tThank you for using the Library System!\n\n");
            exit(0);
        default:
            printf("\n\tInvalid choice!\n");
            pause_screen();
            mainMenu();
    }
}

void addBook(void)
{
    CLEAR();
    printf("\n\n\t***************** Book Info *****************\n\n");

    printf("\tID: ");
    scanf("%d", &a.id);
    printf("\tName: ");
    scanf("%s", a.name);
    printf("\tAuthor: ");
    scanf("%s", a.author);
    printf("\tQuantity: ");
    scanf("%d", &a.quantity);
    printf("\tRack No: ");
    scanf("%d", &a.rack);

    file = fopen("books.dat", "ab");
    fwrite(&a, sizeof(a), 1, file);
    fclose(file);

    printf("\n\n\t\tBook Added Successfully!\n");
    pause_screen();
    mainMenu();
}

void viewBook(void)
{
    CLEAR();
    int count = 0;

    printf("\n\n\t******* view Book List *******\n\n");
    printf("\tId\tName\tAuthor\tquantity\tRack\n\n");

    file = fopen("books.dat", "rb");
    if (file != NULL) {
        while (fread(&a, sizeof(a), 1, file) == 1) {
            printf("\t%d", a.id);
            printf("\t%s", a.name);
            printf("\t%s", a.author);
            printf("\t%d", a.quantity);
            printf("\t%d\n", a.rack);
            count = count + 1;
        }
        fclose(file);
    }

    printf("\n\n\t\tTotal Books: %d\n", count);
    pause_screen();
    mainMenu();
}

void searchBook(void)
{
    CLEAR();
    int id, found = 0;

    printf("\n\n\t************** search Book *****************\n\n");
    printf("\tsearching.....\n\n");
    printf("\tEnter ID: ");
    scanf("%d", &id);

    file = fopen("books.dat", "rb");
    if (file != NULL) {
        while (fread(&a, sizeof(a), 1, file) == 1) {
            if (a.id == id) {
                found = 1;
                printf("\n\tBook is Found!\n");
                printf("\tID: %d\n", a.id);
                printf("\tName: %s\n", a.name);
                printf("\tAuthor: %s\n\n", a.author);
                printf("\tquantity: %d\n", a.quantity);
                printf("\tRack: %d\n", a.rack);
                break;
            }
        }
        fclose(file);
    }

    if (found == 0) {
        printf("\n\tBook is not Available!\n");
    }

    pause_screen();
    mainMenu();
}

void editBook(void)
{
    CLEAR();
    int id, found = 0;

    printf("\n\n\t***************** Edit Book *****************\n\n");
    printf("\tEnter Book ID to Edit: ");
    scanf("%d", &id);

    file = fopen("books.dat", "rb+");
    if (file != NULL) {
        while (fread(&a, sizeof(a), 1, file) == 1) {
            if (a.id == id) {
                found = 1;
                printf("\n\n\t***************** New Book info *****************\n\n");
                printf("\tID: ");
                scanf("%d", &a.id);
                printf("\tName: ");
                scanf("%s", a.name);
                printf("\tAuthor: ");
                scanf("%s", a.author);
                printf("\tQuantity: ");
                scanf("%d", &a.quantity);
                printf("\tRack No: ");
                scanf("%d", &a.rack);

                fseek(file, -(long)sizeof(a), SEEK_CUR);
                fwrite(&a, sizeof(a), 1, file);
                break;
            }
        }
        fclose(file);
    }

    if (found)
        printf("\n\n\t\tBook Edited/Updated Successfully!\n");
    else
        printf("\n\n\t\tBook ID not Found!\n");

    pause_screen();
    mainMenu();
}

void deleteBook(void)
{
    CLEAR();
    int id, found = 0;

    printf("\n\n\t***************** delete Book *****************\n\n");
    printf("\tEnter ID for delete Book: ");
    scanf("%d", &id);

    file  = fopen("books.dat", "rb");
    file2 = fopen("temp.dat", "wb");

    if (file != NULL && file2 != NULL) {
        while (fread(&a, sizeof(a), 1, file) == 1) {
            if (id != a.id) {
                fwrite(&a, sizeof(a), 1, file2);
            } else {
                found = 1;
                printf("\n\tBook is Available!\n");
                printf("\tBook Name is: %s\n", a.name);
                printf("\tRack no %d\n", a.rack);
            }
        }
        fclose(file);
        fclose(file2);

        remove("books.dat");
        rename("temp.dat", "books.dat");
    }

    if (!found)
        printf("\n\tBook is not Available!\n");
    else
        printf("\n\tBook Deleted Successfully!\n");

    pause_screen();
    mainMenu();
}

void addMember(void)
{
    CLEAR();
    printf("\n\n\t***************** Add New Member *****************\n\n");

    printf("\tID: ");
    scanf("%d", &m.id);
    printf("\tName: ");
    scanf("%s", m.name);
    printf("\tType (Student/Teacher/Others): ");
    scanf("%s", m.type);
    printf("\tPassword: ");
    scanf("%s", m.password);

    file = fopen("members.dat", "ab");
    fwrite(&m, sizeof(m), 1, file);
    fclose(file);

    printf("\n\n\t\tNew Member Added Successfully!\n");
    pause_screen();
    mainMenu();
}

void updateDeleteMember(void)
{
    CLEAR();
    int id, ch, found = 0;

    printf("\n\n\t********** Update / Delete Member Record **********\n\n");
    printf("\tEnter Member ID: ");
    scanf("%d", &id);

    printf("\n\t1. Update Record\n");
    printf("\t2. Delete Record\n");
    printf("\tEnter your choice: ");
    scanf("%d", &ch);

    if (ch == 1) {
        file = fopen("members.dat", "rb+");
        if (file != NULL) {
            while (fread(&m, sizeof(m), 1, file) == 1) {
                if (m.id == id) {
                    found = 1;
                    printf("\n\tName: ");
                    scanf("%s", m.name);
                    printf("\tType: ");
                    scanf("%s", m.type);
                    printf("\tPassword: ");
                    scanf("%s", m.password);

                    fseek(file, -(long)sizeof(m), SEEK_CUR);
                    fwrite(&m, sizeof(m), 1, file);
                    break;
                }
            }
            fclose(file);
        }
    } else if (ch == 2) {
        file  = fopen("members.dat", "rb");
        file2 = fopen("temp2.dat", "wb");
        if (file != NULL && file2 != NULL) {
            while (fread(&m, sizeof(m), 1, file) == 1) {
                if (id != m.id) {
                    fwrite(&m, sizeof(m), 1, file2);
                } else {
                    found = 1;
                }
            }
            fclose(file);
            fclose(file2);
            remove("members.dat");
            rename("temp2.dat", "members.dat");
        }
    }

    if (found)
        printf("\n\n\t\tOperation Successful!\n");
    else
        printf("\n\n\t\tMember ID not Found!\n");

    pause_screen();
    mainMenu();
}

void returnBookFine(void)
{
    CLEAR();
    int subChoice;

    printf("\n\n\t***** Return Book and Fine Collection *****\n\n");
    printf("\t1. Issue a Book\n");
    printf("\t2. Return a Book & Collect Fine\n");
    printf("\tEnter choice: ");
    scanf("%d", &subChoice);

    if (subChoice == 1) {
        struct Issue iss;
        printf("\n\tEnter Book ID: ");
        scanf("%d", &iss.bookId);
        printf("\tEnter Member ID: ");
        scanf("%d", &iss.memberId);
        iss.daysUsed = 0;
        iss.returned = 0;

        file = fopen("issues.dat", "ab");
        fwrite(&iss, sizeof(iss), 1, file);
        fclose(file);

        printf("\n\tBook Issued Successfully!\n");
    }
    else if (subChoice == 2) {
        int bookId, memberId, daysUsed, found = 0;
        float fine = 0;
        struct Issue iss;

        printf("\n\tEnter Book ID: ");
        scanf("%d", &bookId);
        printf("\tEnter Member ID: ");
        scanf("%d", &memberId);
        printf("\tEnter Total Days Book was Kept: ");
        scanf("%d", &daysUsed);

        file = fopen("issues.dat", "rb+");
        if (file != NULL) {
            while (fread(&iss, sizeof(iss), 1, file) == 1) {
                if (iss.bookId == bookId && iss.memberId == memberId && iss.returned == 0) {
                    found = 1;
                    iss.daysUsed = daysUsed;
                    iss.returned = 1;

                    if (daysUsed > 14) {
                        fine = (daysUsed - 14) * 5.0f;
                    }

                    fseek(file, -(long)sizeof(iss), SEEK_CUR);
                    fwrite(&iss, sizeof(iss), 1, file);
                    break;
                }
            }
            fclose(file);
        }

        if (found) {
            printf("\n\tBook Returned Successfully!\n");
            if (fine > 0)
                printf("\tFine Amount: %.2f Taka (Overdue by %d days)\n", fine, daysUsed - 14);
            else
                printf("\tNo Fine. Returned on Time.\n");
        } else {
            printf("\n\tNo Matching Active Issue Record Found!\n");
        }
    }
    else {
        printf("\n\tInvalid choice!\n");
    }

    pause_screen();
    mainMenu();
}

void dueDateReport(void)
{
    CLEAR();
    struct Issue iss;
    int count = 0;
    int allowedDays = 14;

    printf("\n\n\t***** Due Date Tracking & Overdue Report *****\n\n");
    printf("\tBookID\tMemberID\tStatus\n\n");

    file = fopen("issues.dat", "rb");
    if (file != NULL) {
        while (fread(&iss, sizeof(iss), 1, file) == 1) {
            if (iss.returned == 0) {
                printf("\t%d\t%d\t\tActive (not yet returned)\n", iss.bookId, iss.memberId);
                count++;
            }
        }
        fclose(file);
    }

    if (count == 0) {
        printf("\n\tNo Active Issued Books Found.\n");
    }

    printf("\n\tAllowed borrowing period : %d days.\n", allowedDays);
    printf("\tFine Rate : 5 Taka / day after due date.\n");
    printf("\tUse option 8 (Return Book) to settle a book and calculate fine.\n");

    pause_screen();
    mainMenu();
}
