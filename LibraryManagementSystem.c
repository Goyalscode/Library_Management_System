// Program to implement library management system in c language for geu

// NAME               - PRIYANSHU GOYAL
// UNIVERSITY ROLL NO - 2014787

// Below are the header files required in the program
#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<dos.h>
#include<stdlib.h>
#include<ctype.h>
#include<time.h>

// structure to store the present date
typedef struct date_info
{
    int day,month,year;    // d - to store no of days, m - to store the current month, year - to store the current year
}date;

// structure to store information about a student
typedef struct student_info
{
    char stud_name[50];        // character array, to store the name of student
    long long int unique_id;   // to store the unique id of a student
    int issued;                // to store no of books the student has issued
    long long int b_id[5];     // to store the Book Ids, that the student has issued
}student;

// structure to store information about a book
typedef struct book_info
{
    char book_name[50];       // character array, to store the name of book
    char author_name[50];     // character array, to store author name of book
    long long int book_id;    // to store the Book Id
    double b_price;           // to store the price of the book
    int issue_st;             // to store the status of book issued (1 if issued else 0)
    date issue;               // a structure of type date to store the issue date of book
    date due;                 // a structure of type date to store the due date of book
    char s_name[50];          // character array, to store name of student who issued the book
    long long int s_id;       // to store the unique id of the student who issued the book
}book;

// Below is the prototype of all functions created in the program
void front_menu();
void load_request(int);
int password();
void change_password();
char neg_Check(long long int, int);
void check_choice(char*);
void bookServices();
book check_Id(long long int);
void disp_Book();
void disp_Issued();
void bookAdd();
void remove_Book(long long int);
void check_BookAv(int);
void book_Search();
void studServices();
student check_SId(long long int);
void disp_Stud();
void disp_StudIssued();
void studAdd(long long int);
void remove_Stud(long long int);
void check_StIssued(int);
void book_issue();
void return_book();
int isLeapYear(int);
int isValidDate(date);
int check_LessDate(date, date);
void return_date(date *);
void cal_due(date*);
int cal_Fine(date*, date*);
void check_openFile(FILE *);

int main()   // function from where the execution of program begins
{
    int log_check = 0;    // to store the status of logging in (1 if user has logged in else 0)
    date today;           // structure of type date to store the present date
    return_date(&today);
    printf("\n\n\n\n\n");
    printf("  \t\t\t\t  ________________________________________________");
    printf("\n\t\t\t\t |                                                |");
    printf("\n\t\t\t\t |  ASSIGNMENT TITLE - LIBRARY MANAGEMENT SYSTEM  |");
    printf("\n\t\t\t\t |                                                |");
    printf("\n\t\t\t\t |              PREPARED BY :                     |");
    printf("\n\t\t\t\t |                                                |");
    printf("\n\t\t\t\t |      NAME                - PRIYANSHU GOYAL     |");
    printf("\n\t\t\t\t |      SEMESTER            - 3rd                 |");
    printf("\n\t\t\t\t |      SECTION             - A                   |");
    printf("\n\t\t\t\t |      UNIVERSITY ROLL NO. - 2014787             |");
    printf("\n\t\t\t\t |      ASSIGNMENT DATE     - 09/09/2020          |");
    printf("\n\t\t\t\t |      TODAY'S DATE        - %02d/%02d/%4d          |", today.day, today.month, today.year);
    printf("\n\t\t\t\t |________________________________________________|\n\n");
    printf("\n\nPress any key to continue\n");
    getch();
    system("cls");         // inbuilt function to clear the entire screen
    front_menu(log_check);
    return 0;
}

// Function to display the front menu to the user
void front_menu(int log_check)
{
    int opt;    // to store the choice of the user, from the front menu, serves as the switch variable
    do
    {
        opt = -1;
        system("cls");
        printf("\t\t\t\t --------------------------------------------------\n");
        printf("\t\t\t\t |********LIBRARY MANAGEMENT SYSTEM FOR GEU*******|    \n");
        printf("\t\t\t\t --------------------------------------------------\n\n\n\n\n");
        printf("        FRONT  MENU  \n\n");
        if(log_check == 0)
            printf("0 -> LOGIN FOR THE LIBRARIAN \n\n");
        printf("1 -> BOOKS RELATED SERVICES \n\n");
        printf("2 -> STUDENT RELATED SERVICES \n\n");
        printf("3 -> CHANGE PASSWORD FOR LOGIN \n\n");
        printf("4 -> EXIT FROM THE APPLICATION \n\n");
        printf("Choose any of the given options\n");
        scanf("%d", &opt);
        getchar();
        switch(opt)    // switch block - executes a function based on user's choice from menu that is stored in opt
        {              // switch block contains various case blocks containing different case constants based on menu
            case 0 :
                if(password())
                    log_check=1;
                break;
            case 1 :
                if(log_check == 0)
                    log_check = password();
                if(log_check)
                {
                    load_request(100);    // function to delay execution of the program to bring design and reality
                    bookServices();
                }
                break;
            case 2 :
                if(log_check == 0)
                    log_check = password();
                if(log_check)
                {
                    load_request(100);
                    studServices();
                }
                break;
            case 3 :
                if(log_check == 0)
                    log_check = password();
                if(log_check)
                {
                    load_request(100);
                    system("cls");
                    printf("\t\tEnter New Password :\t");
                    change_password();
                }
                break;
            case 4 :
                printf("\n\nWe will now exit from the application");
                printf("\nHave a nice day,Goodbye\n");
                load_request(100);
                exit(0);           // inbuilt function to exit from the program
                break;
            default:               // default block gets executed if no case block is executed
                printf("\n\nEntered choice is not valid");
                fflush(stdin);
                printf("\nChoose only from the options given\n");
                printf("\nAgain loading the menu\n");
                load_request(250);
        }
    }while(1);
}

// Function to display menu of book related services on the screen
void bookServices()
{
    do
    {
        system("cls");
        printf("\t\tOPTIONS FOR THE BOOK RELATED SERVICES ARE : \n\n\n");
        printf("1 -> DISPLAY ALL BOOKS OF LIBRARY   \t\t  10 -> CHANGE PASSWORD \n");
        printf("2 -> DISPLAY ALL ISSUED BOOKS \n");
        printf("3 -> ADD A NEW BOOK \n");
        printf("4 -> DELETE AN EXISTING BOOK \n");
        printf("5 -> CHECK AVAILABILITY OF A BOOK \n");
        printf("6 -> CHECK WHICH BOOK GIVEN TO WHICH STUDENT \n");
        printf("7 -> SEARCH A BOOK \n");
        printf("8 -> GO BACK TO THE FRONT MENU \n");
        printf("9 -> EXIT FROM THE APPLICATION \n");
        int ch;      // to store the choice of the user, he makes from the books menu
        printf("\n\nEnter your choice from the above menu\n");
        scanf("%d", &ch);
        getchar();
        switch(ch)
        {
            case 1 :
                disp_Book();
                break;
            case 2 :
                disp_Issued();
                break;
            case 3 :
                bookAdd();
                break;
            case 4 :
                remove_Book(-1);
                break;
            case 5 :
                check_BookAv(-1);
                break;
            case 6 :
                check_BookAv(1);
                break;
            case 7 :
                book_Search();
                break;
            case 8 :
                return;
                break;
            case 9 :
                exit(0);
                break;
            case 10 :
                load_request(100);
                system("cls");
                printf("\t\tEnter new password :\t");
                change_password();
                break;
            default :
            printf("Choice is invalid\n");
            printf("Choose only from the options given\n");
            printf("\nAgain loading the book related menu\n");
            load_request(350);
            bookServices();
        }
    }while(1);
}

// Function to delay ecxecution of program for ms milliseconds
void delay(int ms)    // ms - formal parameter - stores no of milliseconds for which program is to delay
{
    ms += clock();    // clock() - inbuilt function that returns milliseconds elapsed since the program began
    while(clock() < ms)
    {

    }
}

// Function to print an asterisk with delay when user selects a choice from the menu
void load_request(int ms)    // ms - formal parameter - stores no of milliseconds for which program is to delay
{
    for(int i = 0; i < 6; i++)    // i - loop variable to print * six times
    {
        printf("*");
        delay(ms);
    }
    printf("\n");
}

// Function to check whether a file is opened successfully or not
void check_openFile(FILE *fp)    // fp - formal parameter, stores address of opened file
{
    if(fp == NULL)
    {
        printf("Some error, Unable to open the required file\n");
        exit(0);
    }
}

// Function to input password from the user for logging in (returns 1 if password correct else 0)
int password()
{
    printf("\n\t\tFulfilling your request\n");
    load_request(100);
    system("cls");
    printf("\nFirst Enter Password For Logging In To Access Services :\t");
    char initial[17],ch;    // initial - character array to store password, ch - to store each character of password
    int i = 0;              // to store and increment the index no of initial array while user eneters the password
    while(((ch = getch()) != '\r') && (i < 16))
    {
        if(ch == '\b')
        {
            i--;           // when backspace is pressed, decrement index by 1
            printf("\b");
            continue;
        }
        printf("*");
        initial[i++] = ch;
    }
    initial[i] = '\0';
    FILE *pass;                           // pass - file pointer to store address returned by fopen()
    pass = fopen("password.txt", "r");    // fopen() - inbuilt function to open a file with different access modes
    check_openFile(pass);
    char check_pass[17];                  // character array to store the correct password that is read from the file
    fscanf(pass, "%s", check_pass);
    fclose(pass);                         // fclose() - inbuilt function that closes file pointed by file pointer (pass)
    if(strcmp(initial, check_pass) == 0)  // comparing the correct and entered password
    {
        printf("\nLOGIN IS SUCCESSFUL, \n");
        return 1;
    }
    else           // executes if password enetered is wrong
    {
        char p;    // to store choice of user whether he wants to re-enter password or go to front menu
        printf("\nPassword enetered is incorrect, \n");
        printf("Do you want to try logging again (Y) ,or will go to front menu (N) \n");
        printf("Enter your choice \n");
        scanf("%c", &p);
        getchar();
        while((toupper(p) != 'N') && (toupper(p) != 'Y'))
        {
            printf("Enetered Choice is invalid\n");
            printf("Please try again\n");
            printf("Enter your choice (Y,N)\n");
            scanf("%c", &p);
            getchar();
        }
        if(toupper(p) == 'N')
        {
            printf("\n\t\tFulfilling your request\n");
            printf("\n");
            load_request(200);
            return 0;
        }
        if(toupper(p) == 'Y')
            password();
    }
}

// function to change the initial password for logging in
void change_password()
{
    char change[17],ch;    // change - character array to store new password, ch - to store each character of password
    int i = 0;             // to store and increment the index no of change array while user eneters the password
    while(((ch = getch()) != '\r') && (i < 16))
    {
        if(ch == '\b')
        {
            i--;
            printf("\b");
            continue;
        }
        printf("*");
        change[i++] = ch;
    }
    change[i] = '\0';
    FILE *pass;                           // pass - file pointer to store address of password file
    pass = fopen("password.txt", "w");    // opening password file in write mode to enter the new password
    check_openFile(pass);
    fprintf(pass, "%s", change);
    printf("\nPassword Reset successfully\n");
    fclose(pass);
    printf("\n\nFor continuing,press any key you want\n");
    getchar();
}

// Function to display information about all books in the library
void disp_Book()
{
    system("cls");
    printf("\t\t All books in Geu Library are :\n\n");
    printf("\t%-25s %-25s %-9s %-9s %-13s\n", "Book Name", "Book Author", "Price", "Book Id", "Book Status");
    FILE *open_bk;                          // open_bk is a file pointer to store address of AllBooks file
    open_bk = fopen("AllBooks.txt", "r");
    check_openFile(open_bk);
    book bk;                                // bk - structure of type book to store info of a book
    int c = 0;                              // to store total no of books in the library
    while(feof(open_bk) == 0)               // feof() returns non-zero value if all data has been read from a file
    {
        // fread() - inbuilt function that reads a block of data from given file stream
        // below fread() - used to read info of a book in structure bk, from file stream specified by open_bk

        if((fread(&bk, sizeof(bk), 1, open_bk)))
        {
            c++;
            printf("%5d.  %-25s %-25s %-9.2lf %-9lld ", c, bk.book_name, bk.author_name, bk.b_price, bk.book_id);
            if(bk.issue_st == 0)
                printf("%-13s\n", "Not Issued");
            else
                printf("%-13s\n", "Issued");
        }
    }
    printf("\nTotal Books In The Library Are : %d", c);
    fclose(open_bk);
    printf("\n\n\nFor continuing,press any key you want\n");
    getchar();
}

// Function to check whether an ID eneterd by user is valid or not
char neg_Check(long long int id, int b_or_s)
{
    // id     - formal parameter that stores the enetered id by the user
    // b_or_s - to check whether entered id is of a student or  book (1 for book, 2 for student)

    char ch = '1';    // to store choice of user whether he wants to eneter id again or not
    if(id < 0)
    {
        if(b_or_s == 1)
            printf("\nBOOK ID CANNOT BE NEGATIVE, TRY AGAIN (Press 'Y' for trying again else 'N')\n");
        else
            printf("\nSTUDENT ID CANNOT BE NEGATIVE, TRY AGAIN (Press 'Y' for trying again else 'N')\n");
        scanf("%c", &ch);
        getchar();
        check_choice(&ch);
    }
    return ch;
}

// function to check if choice enetered by user is valid or not
void check_choice(char *ch)    // ch is char pointer, stores address of choice entered by user
{
    char c = *ch;              // char variable to store choice pointed by ch
    while((toupper(c) != 'Y') && (toupper(c) != 'N'))
    {
        printf("\nEntered choice is invalid, Press only 'Y' or 'N'\n");
        scanf("%c", ch);
        getchar();
        c = *ch;
    }
}

// function to display all the issued books of library
void disp_Issued()
{
    system("cls");
    printf("\n\t\t\t All Issued Books In Geu Library Are :\n\n");
    printf("\t%-25s %-25s %-11s %-11s %-25s %-12s %-12s %-12s\n\n", "Book Name", "Book Author", "Price", "Book Id", "Student Name", "Student ID", "ISSUE DATE", "DUE DATE");
    FILE *open_bk;                          // open_bk - file pointer, to store address of AllBooks file
    open_bk = fopen("AllBooks.txt", "r");
    check_openFile(open_bk);
    book bk;                                // structure of type book to store info of a book
    int c = 0;                              // to store total no of issued books
    while(feof(open_bk) == 0)
    {
        if((fread(&bk, sizeof(bk), 1, open_bk)))
        {
            if(bk.issue_st == 1)
            {
                c++;
                printf("%5d.  %-25s %-25s %-11.2lf %-11lld %-25s %-12lld ", c, bk.book_name, bk.author_name, bk.b_price, bk.book_id, bk.s_name, bk.s_id);
                printf("%02d/%02d/%d   ", bk.issue.day, bk.issue.month, bk.issue.year);
                printf("%02d/%02d/%d\n\n", bk.due.day, bk.due.month, bk.due.year);
            }
        }
    }
    printf("\nTotal Issued Books Are : %d", c);
    fclose(open_bk);
    printf("\n\n\nFor continuing,press any key you want\n");
    getchar();
}

// function to input Id of a book and also invokes neg_Check() to check its validity
char input_Bookid(book *bk)    // bk - pointer to a structure of type book used to store input book Id in the structure
{
    char ch;                  // to store character returned by neg_Check()
    printf("\tEnter the following information:\n\n");
    bk->book_id = -1;
    printf("Book Id: \t");
    scanf("%lld", &(bk->book_id));
    getchar();
    ch = neg_Check(bk->book_id, 1);
    return ch;
}

// function to check whether entered Book id by user exists in library database (returns a book type structure)
book check_Id(long long int id)    // id - formal parameter, stores the Id of a book user has entered
{
    FILE *open_bk;                 // file pointer to store address of AllBooks file
    open_bk = fopen("AllBooks.txt", "r");
    check_openFile(open_bk);
    book b;                        // a book type structure, stores info of the book if Id found
    while(feof(open_bk) == 0)
    {
        if(fread(&b, sizeof(book), 1, open_bk) == 1)
        {
            if(b.book_id == id)
            {
                fclose(open_bk);
                return b;
            }
        }
    }
    fclose(open_bk);
    b.book_name[0] = '\0';
    return b;
}

// function to check availability of a book and also see to which student a book is given
void check_BookAv(int check)    // check -> stores -1 if user wants to see availabilty, 1 to see given to which student
{
    char ch;             // to store choioce of user if he wants to continue check availabilty a book
    do
    {
        book bk;         // a book type structure to store info of a book
        system("cls");
        if(check == -1)
            printf("\t\t\t FOR CHECKING AVAILABILITY OF A BOOK : \n");
        else
            printf("\t\t\t FOR CHECKING WHICH BOOK IS GIVEN TO WHICH STUDENT : \n");
        ch = input_Bookid(&bk);
        if(ch != '1')
            continue;
        book s_check = check_Id(bk.book_id);    // s_check - book type structure to store book info returned by check_Id()
        if(s_check.book_name[0] == '\0')
            printf("\nA book with this Id does not exist\n");
        else
        {
            printf("\n_______________________________________________________________________________________________");
            bk = s_check;
            if(s_check.issue_st == 1)
            {
                if(check == -1)
                    printf("\nThis Book Is Not Available At This Moment\n");
                printf("\n\nThis Book Is Issued To   : %-25s %-14s %-14s %-14s\n", "Student Name", "Student ID", "Issue Date", "Due Date");
                printf("\t\t\t   %-25s %-14lld %02d/%02d/%d     %02d/%02d/%d", bk.s_name, bk.s_id, bk.issue.day, bk.issue.month, bk.issue.year, bk.due.day, bk.due.month, bk.due.year);
            }
            else
            {
                if(check == -1)
                    printf("\nBook is available\n");   // printing according to value of check
                else
                    printf("\nThis Book Is Not Issued To Any Student\n");
                printf("\nBook Details Are:\n");
                printf("%-25s %-25s %-11s %-9s \n", "Book Name", "Book Author", "Price", "Book Id");
                printf("%-25s %-25s %-11.2lf %-11lld ", bk.book_name, bk.author_name, bk.b_price, bk.book_id);
            }
            printf("\n_______________________________________________________________________________________________\n");
        }
        if(check == -1)
            printf("\n\nDo you want to check availability of any other book('Y' ,'N')\n");
        else
            printf("\n\nDo you want to check for any other book to find out to which student it is given('Y' ,'N')\n");
        scanf("%c", &ch);
        getchar();
        check_choice(&ch);
    }while(toupper(ch) == 'Y');
    printf("\n\nFor continuing,press any key you want\n");
    getchar();
}

// function to search for a book in library
void book_Search()
{
    char ch;    // to store choice of user if he wants to continue search for any other book
    do
    {
        system("cls");
        printf("\t\t\t SEARCHING A BOOK IN GEU LIBRARY : \n");
        book bk;
        ch = input_Bookid(&bk);
        if(ch != '1')
            continue;
        book s_check = check_Id(bk.book_id);    // calling check_Id() to check if entered id exists in library
        if(s_check.book_name[0] == '\0')
            printf("\nA book with this Id does not exist\n");
        else
        {
            printf("\nSearch Results Are:\n\n");
            printf("________________________________________________________________________\n\n");
            printf("%-25s %-25s %-9s %-9s \n", "Book Name", "Book Author", "Price", "Book Id");
            printf("%-25s %-25s %-11.2lf %-11lld ", s_check.book_name, s_check.author_name, s_check.b_price, s_check.book_id);
            if(s_check.issue_st == 0)    // checking if book is issued or not
                printf("\n\nThis book is not issued");
            else
            {
                printf("\n\nThis book is issued :\n\n");
                printf("%-25s %-14s %-14s %-14s \n", "Student Name", "Student ID", "Issue Date", "Due Date");
                printf("%-25s %-14lld %02d/%02d/%d     %02d/%02d/%d", s_check.s_name, s_check.s_id, s_check.issue.day, s_check.issue.month, s_check.issue.year, s_check.due.day, s_check.due.month, s_check.due.year);
            }
            printf("\n________________________________________________________________________\n");
        }
        printf("\nDo you want to search for any other book ('Y' ,'N')\n");
        scanf("%c", &ch);
        getchar();
        check_choice(&ch);
    }while(toupper(ch) == 'Y');
    printf("\n\nFor continuing,press any key you want\n");
    getchar();
}

// function to add a book to the library
void bookAdd()
{
    char ch;    // to store choice of user if he wants to continue adding any other book
    do
    {
        system("cls");
        printf("\t\t\t FOR ADDING BOOK : \n");
        book bk;    // book type structure to store book details entered by the user
        ch = input_Bookid(&bk);
        if(ch != '1')
            continue;
        book check = check_Id(bk.book_id);    // check - book type structure to store book info returned by check_Id()
        if(check.book_name[0] != '\0')
        {
            printf("\nA book with this Id already exists\n");
        }
        else
        {
            FILE *open_bk;    // file pointer to store address of AllBooks file
            open_bk=fopen("AllBooks.txt", "a");    // opening AllBooks file in append mode
            check_openFile(open_bk);
            printf("Book Name: \t");
            scanf("%[^\n]s", bk.book_name);
            getchar();
            printf("Author Name: \t");
            scanf("%[^\n]s", bk.author_name);
            getchar();
            printf("Book Price: \t");
            scanf("%lf", &bk.b_price);
            getchar();
            bk.issue_st = 0;
            bk.issue.day = 0;
            bk.issue.month = 0;
            bk.issue.year = 0;
            bk.due = bk.issue;
            fwrite(&bk, sizeof(book), 1, open_bk);    // writing info of a book to file pointed by open_bk
            printf("Book has been added successfully\n");
            fclose(open_bk);
        }
        printf("\n\nDo you want to add any other book('Y' ,'N')\n");
        scanf("%c", &ch);
        getchar();
        check_choice(&ch);
    }while(toupper(ch) == 'Y');
    printf("\n\nFor continuing,press any key you want\n");
    getchar();
}

// function to remove a book from the library
void remove_Book(long long int check)
{
    // check stores -1 if user wants to delete book himself otherwise stores Id of book to be deleted

    char ch;    // character variable to store choice of user if he wants to continue remove any other book
    do
    {
        int flag = 1;    // integer variable - stores 1 if a book with Id enetered by user exists in library else 0
        book bk;         // book type structure to store info of book to be deleted
        if(check == -1)
        {
            system("cls");
            printf("\t\t\t For Deleting a book:\n");
            ch = input_Bookid(&bk);
            if(ch != '1')
                continue;
            book b_check = check_Id(bk.book_id);
            if(b_check.book_name[0] == '\0')
            {
                flag = 0;
                printf("\nA book with this ID does not exist");
            }
        }
        else
            bk.book_id = check;
        if(flag == 1)
        {
            long long int del_Id = bk.book_id;    // del_Id - long type variable to store Id of book to be deleted
            FILE *copy = fopen("Copy.txt", "w");  // copy - file pointer to store address of Copy file
            check_openFile(copy);
            FILE *open_bk = fopen("AllBooks.txt", "r");
            check_openFile(open_bk);
            while(feof(open_bk) == 0)
            {
                if(fread(&bk, sizeof(book), 1, open_bk))
                {
                    if(bk.book_id != del_Id)
                        fwrite(&bk, sizeof(book), 1, copy);    // writing records of all books to Copy file except
                }                                              // that to be deleted
            }
            fclose(open_bk);
            fclose(copy);
            remove("AllBooks.txt");                // deleting AllBooks file
            rename("Copy.txt", "AllBooks.txt");    // to rename Copy file to AllBooks file
            if(check != -1)
                return;
            printf("Book has been deleted successfully\n");
        }
        printf("\n\nDo you want to delete any other book('Y' ,'N')\n");
        scanf("%c", &ch);
        getchar();
        check_choice(&ch);
    }while(toupper(ch) == 'Y');
    printf("\n\nFor continuing,press any key you want\n");
    getchar();
}

// function to print student related menu on the screen
void studServices()
{
    do
    {
        system("cls");
        printf("\t\tOPTIONS FOR THE STUDENT RELATED SERVICES ARE : \n\n\n");
        printf("1 -> DISPLAY ALL STUDENTS ADDED TO LIBRARY DATABASE   \t\t  11 -> CHANGE PASSWORD \n");
        printf("2 -> DISPLAY ALL STUDENTS WHICH HAVE ISSUED BOOKS \n");
        printf("3 -> ADD A NEW STUDENT \n");
        printf("4 -> DELETE AN EXISTING STUDENT \n");
        printf("5 -> ISSUE A BOOK \n");
        printf("6 -> RETURN A BOOK \n");
        printf("7 -> CHECK WHICH STUDENT HAS ISSUED HOW MANY BOOKS \n");
        printf("8 -> SEARCH FOR A STUDENT \n");
        printf("9 -> GO BACK TO THE FRONT MENU \n");
        printf("10 -> EXIT FROM THE APPLICATION \n");
        int ch;    // to store choice of the user he makes from the student menu, serves as the switch variable
        printf("\n\nEnter your choice from the above menu\n");
        scanf("%d", &ch);
        getchar();
        switch(ch)
        {
            case 1 :
                disp_Stud();
                break;
            case 2 :
                disp_StudIssued();
                break;
            case 3 :
                studAdd(-1);
                break;
            case 4 :
                remove_Stud(-1);
                break;
            case 5 :
                book_issue();
                break;
            case 6 :
                return_book();
                break;
            case 7 :
                check_StIssued(-1);
                break;
            case 8 :
                check_StIssued(1);
                break;
            case 9 :
                return;
                break;
            case 10 :
                exit(0);
                break;
            case 11 :
                load_request(100);
                system("cls");
                printf("\t\tEnter new password :\t");
                change_password();
                break;
            default :
            printf("Choice is invalid\n");
            printf("Choose only from the options given\n");
            printf("\n\nAgain loading the student related menu\n");
            load_request(350);
            studServices();
        }
    }while(1);
}

// function to display record of all students added to library database
void disp_Stud()
{
    system("cls");
    printf("\t\t All Students in Geu Library Database are :\n\n");
    printf("\t%-25s %-12s %-14s\n", "Student Name", "Student Id", "Issued Books");
    FILE *open_st = fopen("Students.txt", "r");   // file pointer to store address of Students file, opened in read mode
    check_openFile(open_st);
    student st;   // student type structure to store info of a student
    int c = 0;    // to count total no of students in the library
    while(feof(open_st) == 0)
    {
        if((fread(&st, sizeof(student), 1, open_st)))
        {
            c++;
            printf("%5d.  %-25s %-12lld %-14d\n", c, st.stud_name, st.unique_id, st.issued);
        }
    }
    printf("\nTotal Students Added To The Library Are : %d", c);
    fclose(open_st);
    printf("\n\n\nFor continuing,press any key you want\n");
    getchar();
}

// function to display students which have issued any book
void disp_StudIssued()
{
    system("cls");
    printf("\t\t\t All Students Which Have Issued Books Are :\n\n");
    printf("\t%-25s %-12s %-14s \n\n", "Student Name", "Student Id", "Issued Books");
    FILE *open_st = fopen("Students.txt", "r");
    check_openFile(open_st);
    student st;    // student type structure to store info of a student
    int c = 0;     // to store total no of students who have issued books
    while(feof(open_st) == 0)
    {
        if((fread(&st, sizeof(student), 1, open_st)))
        {
            if(st.issued > 0)    // checking if student has issued any book
            {
                c++;
                printf("\n%5d.  %-25s %-12lld %-14d \n\n", c, st.stud_name, st.unique_id, st.issued);
                printf("\t\t%-25s %-25s %-11s %-11s %-12s %-12s\n", "Book Name", "Book Author", "Price", "Book Id", "ISSUE DATE", "DUE DATE");
                for(int i = 0; i < st.issued; i++)
                {
                    book b_det = check_Id(st.b_id[i]);
                    printf("\t%5c.  %-25s %-25s %-11.2lf %-11lld ", (char)i+97, b_det.book_name, b_det.author_name, b_det.b_price, b_det.book_id);
                    printf("%02d/%02d/%d   ", b_det.issue.day, b_det.issue.month, b_det.issue.year);
                    printf("%02d/%02d/%d\n", b_det.due.day, b_det.due.month, b_det.due.year);
                    if(i == (st.issued-1))
                        printf("\t______________________________________________________________________________________________________________\n\n\n");
                }
            }
        }
    }
    printf("\nTotal Students Which Have Issued Books Are : %d", c);
    fclose(open_st);
    printf("\n\n\nFor continuing,press any key you want\n");
    getchar();
}

// function to input Id of a student and also invokes neg_Check() to check its validity
char input_Studid(student *st)    // st - pointer to student type structure used to store input id in the structure
{
    char ch;                      // character variable to store character returned by neg_Check()
    printf("\tEnter the following information:\n\n");
    st->unique_id = -1;
    printf("Student Unique Id: \t");
    scanf("%lld", &(st->unique_id));
    getchar();
    ch = neg_Check(st->unique_id, 2);
    return ch;
}

// function to see no of books issued by a student, and also to search for a student
void check_StIssued(int check)    // check - stores -1 if want to see books issued by a stud, 1 to search for a student
{
    char ch;    // to store choice of user if want to continue searching or see no of books issued by  a student
    student st; // student type structure to store student info of entered Id if it exists in library
    do
    {
        system("cls");
        if(check == -1)
            printf("\t\t\t FOR CHECKING WHICH STUDENT HAS ISSUED HOW MANY BOOKS : \n");
        else
            printf("\t\t\t TO SEARCH FOR A STUDENT : \n");
        ch = input_Studid(&st);
        if(ch != '1')
        continue;
        student s_check = check_SId(st.unique_id);
        if(s_check.stud_name[0] == '\0')    // checking if entered Id is found in the database
            printf("\nA Student With This Id Does Not Exist\n");
        else
        {
            if(check == 1)    // printing according to the value of check
                printf("\nSearch Results Are :\n\n");
            st = s_check;
            printf("\n______________________________________________________________________________________________________________\n");
            printf("\nStudent Name : %-25s  Student ID : %-12lld\n", st.stud_name, st.unique_id);
            if(s_check.issued == 0)
                printf("\nThis Student Has Not Issued Any Book\n");
            else
            {
                printf("\nNo Of Books Issued By This Student : %d\n", st.issued);
                printf("\nIssued Books Details Are :\n\n");
                printf("\t%-25s %-25s %-11s %-11s %-12s %-12s\n", "Book Name", "Book Author", "Price", "Book Id", "ISSUE DATE", "DUE DATE");
                for(int i = 0; i < st.issued; i++)    // i - loop variable used to display issued books by a student
                {
                    book b_det = check_Id(st.b_id[i]);
                    printf("%5c.  %-25s %-25s %-11.2lf %-11lld ", (char)i+97, b_det.book_name, b_det.author_name, b_det.b_price, b_det.book_id);
                    printf("%02d/%02d/%d   ", b_det.issue.day, b_det.issue.month, b_det.issue.year);
                    printf("%02d/%02d/%d\n", b_det.due.day, b_det.due.month, b_det.due.year);
                }
            }
            printf("______________________________________________________________________________________________________________\n");
        }
        if(check == -1)
            printf("\n\n\nDo You Want To Check For Any Other Student- How Many Books Issued ('Y', 'N')\n");
        else
            printf("\n\n\nDo You Want To Search For Any Other Student ('Y', 'N')  : \n");
        scanf("%c", &ch);
        getchar();
        check_choice(&ch);
    }while(toupper(ch) == 'Y');
    printf("\n\nFor continuing,press any key you want\n");
    getchar();
}

/* Function that will calculate the present date and store it in a structure, whose address
   this function takes as a parameter in a pointer of type date*/
void return_date(date* d)    // d is a date pointer - used to store current date in structure to which it points
{
    time_t present;
    time(&present);
    struct tm *point = localtime(&present);    // using inbuilt function to store
    d->day = point->tm_mday;
    d->month = point->tm_mon + 1;
    d->year = point->tm_year + 1900;
}

// function to add a student to the library database
void studAdd(long long int check)
{
    // check stores -1 if user adds a student from student menu
    // if user while issuing finds the Id not existing in library and wants to add, then check stores student Id

    char ch;    // variable to store choice of user if he wants to continue adding a student or not
    do
    {
        student st;      // student type structure to store info of student to be added to library
        int flag = 1;    // integer variable that stores 1 if entered id does not exist in library else stores 0
        if(check == -1)
        {
            system("cls");
            printf("\t\t\t FOR ADDING A STUDENT INTO THE DATABASE : \n");
            ch = input_Studid(&st);
            if(ch != '1')
                continue;
            student s_check = check_SId(st.unique_id);    // s_check - to store student info returned by check_SId()
            if(s_check.stud_name[0] != '\0')
            {
                flag = 0;
                printf("\nA student with this Id already exists\n");
            }
        }
        else
            st.unique_id = check;
        if(flag == 1)
        {
            FILE *open_st;    // open_st - file pointer, to store address of Students file
            open_st=fopen("Students.txt", "a");    // opening Students file in append mode for adding a new student
            check_openFile(open_st);
            printf("\nEnter Student Name: \t");
            scanf("%[^\n]s", st.stud_name);
            getchar();
            st.issued = 0;
            fwrite(&st, sizeof(student), 1, open_st);    // storing info of student in file pointed by open_st
            fclose(open_st);
            printf("Student has been added successfully\n");
        }
        if(check != -1)
            return;
        printf("\n\nDo you want to add any other student('Y' ,'N')\n");
        scanf("%c", &ch);
        getchar();
        check_choice(&ch);
    }while(toupper(ch) == 'Y');
    printf("\n\nFor continuing,press any key you want\n");
    getchar();
}

// function to check whether entered student id exists in library database
student check_SId(long long int id)    // id - formal parameter, stores student Id that is input from user
{
    FILE *open_st;    // open_st is file pointer to store address of Students file
    open_st=fopen("Students.txt", "r");
    check_openFile(open_st);
    student s;
    while(feof(open_st) == 0)
    {
        if(fread(&s, sizeof(student), 1, open_st))
        {
            if(s.unique_id == id)    // checking if any student id in database is equal to input Id
            {
                fclose(open_st);
                return s;
            }
        }
    }
    fclose(open_st);
    s.stud_name[0] = '\0';
    return s;
}

// function to remove a student from the library
void remove_Stud(long long int check)
{
    // checks stores -1 if user himself wants to remove a student from library
    // for performing student remove operation in other functions, check stores Student Id

    char ch;    // to store choice of user if he wants to continue removing another book
    do
    {
        int flag = 1;    // to check if entered Student Id exists in library (stores 1 if exists else 0)
        student st;      // student structure to store info of a student used for reading info from file
        if(check == -1)
        {
            system("cls");
            printf("\t\t\t For Deleting an existing student:\n");
            ch = input_Studid(&st);
            if(ch != '1')
                continue;
            student s_check = check_SId(st.unique_id);
            if(s_check.stud_name[0] == '\0')
            {
                flag = 0;
                printf("\nA Student with this ID does not exist");
            }
        }
        else
            st.unique_id = check;
        if(flag == 1)
        {
            long long int del_Id = st.unique_id;
            // del_Id - to store Id of student to be deleted, as st is used further for reading another students info

            FILE *copy = fopen("SCopy.txt", "w");
            check_openFile(copy);
            FILE *open_st = fopen("Students.txt", "r");
            check_openFile(open_st);
            while(feof(open_st) == 0)
            {
                // to copy all students info in Scopy file except that to be deleted

                if(fread(&st, sizeof(student), 1, open_st))
                {
                    if(st.unique_id != del_Id)
                        fwrite(&st, sizeof(student), 1, copy);
                }
            }
            fclose(open_st);
            fclose(copy);
            remove("Students.txt");                 // deleting Students file
            rename("SCopy.txt", "Students.txt");    // to rename Scopy file to Students file
            if(check != -1)
                return;
            printf("Student has been deleted successfully\n");
        }
        printf("\n\nDo you want to delete any other student('Y' ,'N')\n");
        scanf("%c", &ch);
        getchar();
        check_choice(&ch);
    }while(toupper(ch) == 'Y');
    printf("\n\nFor continuing,press any key you want\n");
    getchar();
}

// function to issue a book to a student
void book_issue()
{
    char ch;    // to store choice of user if he wants to continue issue another book
    do
    {
        student st;    // student type structure to store info of student who wants to issue book
        system("cls");
        printf("\t\t\t FOR ISSUING A BOOK :\n");
        ch = input_Studid(&st);
        if(ch != '1')
            continue;
        else
        {
            int flag = 1;    // to store status if entered Id exists in database (stores 1 if exists else 0)
            student check = check_SId(st.unique_id);
            if(check.stud_name[0] == '\0')
            {
                flag = 0;
                char press;    // to store choice of user if he wants to add an Id to database that does not exist
                printf("\nA Student with this id does not exist\n");
                printf("\n\nFirst add the student into the database, press (Y) for adding else press (N)\n");
                scanf("%c", &press);
                getchar();
                check_choice(&press);
                if(toupper(press) == 'Y')
                {
                    flag = 1;
                    studAdd(st.unique_id);
                }
            }
            if(flag == 1)
            {
                st = check;
                if(st.issued < 5)        // checking if student has issued max no of books
                {
                    long long int id;    // to store book id of book to be issued
                    printf("\nEnter the book id of the book : \t");
                    scanf("%lld", &id);
                    getchar();
                    book bcheck = check_Id(id);    // bcheck - book structure to store book info returned by check_Id()
                    if(bcheck.book_name[0] == '\0')
                        printf("\nA book with this id does not exist");
                    else if(bcheck.issue_st == 1)
                        printf("\nThis Book already issued to some student");
                    else
                    {
                        return_date(&(bcheck.issue));           // storing current date in issue field of book
                        bcheck.due = bcheck.issue;
                        cal_due(&(bcheck.due));                 // calculating and storing due date of book
                        bcheck.issue_st = 1;
                        bcheck.s_id = st.unique_id;
                        strcpy(bcheck.s_name, st.stud_name);
                        st.b_id[st.issued] = bcheck.book_id;
                        st.issued++;                  // incrementing no of issued books by student
                        remove_Stud(st.unique_id);    // remove student with entered Id, again add after increasing issued field
                        printf("\nBook is issued successfully, Details: ");
                        printf("\nStudent Name:  %-30s  Student Id:  %-10lld", st.stud_name, st.unique_id);
                        printf("\n   Book Name:  %-30s     Book Id:  %-10lld", bcheck.book_name, bcheck.book_id);
                        printf("\n\nDate of issue is  : %02d/%02d/%d", bcheck.issue.day, bcheck.issue.month, bcheck.issue.year);
                        printf("\nDue Date of Book is : %02d/%02d/%d", bcheck.due.day, bcheck.due.month, bcheck.due.year);
                        printf("\n A fine of Rs.2 per day will be charged for late return\n");
                        FILE* st_open = fopen("Students.txt", "a");
                        check_openFile(st_open);
                        fwrite(&st, sizeof(student), 1, st_open);    // adding student after issued field is increased
                        fclose(st_open);
                        remove_Book(bcheck.book_id);    // book removed, will be added after changing its issue status
                        FILE* bk_open = fopen("AllBooks.txt", "a");
                        check_openFile(bk_open);
                        fwrite(&bcheck, sizeof(book), 1, bk_open);    // book added after making issue status 0
                        fclose(bk_open);
                    }
                }
                else
                {
                    printf("\n%s : You Have Issued Maximum No Of Books(5)\n", st.stud_name);
                }
            }
        }
        printf("\n\n\t DO YOU WANT TO ISSUE ANY OTHER BOOK (Y,N)\n");
        scanf("%c", &ch);
        getchar();
        check_choice(&ch);
    }while(toupper(ch) == 'Y');
    printf("\n\nFor continuing,press any key you want\n");
    getchar();
}

// function to return a book to the library which is issued by a student
void return_book()
{
    char ch;    // to store choice of user if he wants to continue return a book
    do
    {
        student st;    // student type structure to access details of student who wants to return book
        system("cls");
        printf("\t\t\t FOR RETURNING A BOOK :\n");
        ch = input_Studid(&st);
        if(ch != '1')
            continue;
        else
        {
            student check = check_SId(st.unique_id);
            if(check.stud_name[0] == '\0')
                printf("\nInvalid ID, A Student with this id does not exist\n");
            else
            {
                st = check;
                if(st.issued > 0)
                {
                    long long int id;
                    printf("\nEnter the book id of the book : \t");
                    scanf("%lld", &id);
                    getchar();
                    int flag = -1;
                    book bcheck = check_Id(id);
                    if(bcheck.book_name[0] == '\0')
                        printf("\nA book with this id does not exist");
                    else if(bcheck.issue_st == 0)
                        printf("\nThis Book is not issued to any student");
                    else
                    {
                        for(int i = 0; i < st.issued; i++)
                        {
                            if(st.b_id[i] == bcheck.book_id)
                            {
                                flag = i;
                                break;
                            }
                        }
                    }
                    if(flag != -1)
                    {
                        date b_return;    // to check if student has paid fine on late return
                        char press = 'A';
                        do
                        {
                            printf("\nEnter the date of book return in day/month/year format:\n");
                            printf("\nDay   : \t");
                            scanf("%d", &(b_return.day));
                            getchar();
                            printf("\nMonth : \t");
                            scanf("%d", &(b_return.month));
                            getchar();
                            printf("\nYear  : \t");
                            scanf("%d", &(b_return.year));
                            getchar();
                            if(isValidDate(b_return) == 0)
                                printf("\nEntered Date is Invalid\n");
                            else if(check_LessDate(b_return, bcheck.issue) == 0)
                                printf("\nReturned Date cannot be less than the issued date\n");
                            if((check_LessDate(b_return, bcheck.issue) == 0) || (isValidDate(b_return) == 0))
                            {
                                printf("\nDo you want to enter return date again ('Y', 'N')\n");
                                scanf("%c", &press);
                                getchar();
                                check_choice(&press);
                            }
                        }while(toupper(press) == 'Y');
                        if(toupper(press) == 'N')
                            break;
                        //return_date(&(b_return));
                        int days = cal_Fine(&(b_return), &(bcheck.due));
                        int fine = days * 4;
                        if(fine > ((int)bcheck.b_price + 500))
                            fine = (int)bcheck.b_price + 500;
                        bcheck.issue_st = 0;
                        for(int i = flag; i < (st.issued - 1); i++)
                            st.b_id[i] = st.b_id[i+1];
                        st.issued--;
                        printf("\nBook is returned successfully to the library, Details: ");
                        printf("\nStudent Name:  %-30s  Student Id:  %-10lld", st.stud_name, st.unique_id);
                        printf("\n   Book Name:  %-30s     Book Id:  %-10lld", bcheck.book_name, bcheck.book_id);
                        printf("\nDue Date of Book is           : %02d/%02d/%d", bcheck.due.day, bcheck.due.month, bcheck.due.year);
                        printf("\nDay on which book is returned : %02d/%02d/%d", b_return.day, b_return.month, b_return.year);
                        if(fine > 0)
                        {
                            char f_paid = 'N';
                            printf("\nThe book is returned %d days after the returned date\n", days);
                            printf("So you have to pay a fine of Rs. %d\n", fine);
                            while(toupper(f_paid) != 'Y')
                            {
                                printf("\nPress 'Y' if you have paid the fine else 'N'\n");
                                scanf("%c", &f_paid);
                                getchar();
                                if(toupper(f_paid) == 'N')
                                    printf("\nIt is mandatory to pay the fine, so pay it\n");
                                check_choice(&f_paid);
                            }
                        }
                        else
                            printf("\nThe book is returned on time\n");
                        remove_Stud(st.unique_id);
                        FILE* st_open = fopen("Students.txt", "a");
                        check_openFile(st_open);
                        fwrite(&st, sizeof(student), 1, st_open);
                        fclose(st_open);
                        remove_Book(bcheck.book_id);
                        FILE* bk_open = fopen("AllBooks.txt", "a");
                        check_openFile(bk_open);
                        fwrite(&bcheck, sizeof(book), 1, bk_open);
                        fclose(bk_open);
                    }
                    else if(bcheck.issue_st == 1)
                        printf("\n%s : This book is not issued to you", st.stud_name);
                }
                else
                    printf("\n%s : You Have Not Issued Any Book\n", st.stud_name);
            }
        }
        printf("\n\n\t DO YOU WANT TO RETURN ANY OTHER BOOK (Y,N)\n");
        scanf("%c", &ch);
        getchar();
        check_choice(&ch);
    }while(toupper(ch) == 'Y');
    printf("\n\nFor continuing,press any key you want\n");
    getchar();
}

// function to check if a year is leap year or not (returns 1 if leap year else 0)
int isLeapYear(int y)    // y - formal parameter, stores the year to be checked for leap year
{
    if(y % 400 == 0)
        return 1;
    if((y % 100 != 0) && (y % 4 == 0))
        return 1;
    return 0;
}

// function to check if entered date by the user is valid or not (returns 1 if valid else 0)
int isValidDate(date dt)    // dt contains the date that is input from the user
{
    if((dt.day > 31) || (dt.day < 1) || (dt.month < 1) || (dt.month > 12))    // checking if days are less than 0 or >31
        return 0;
    int d = dt.day, m = dt.month, y = dt.year;
    if(m == 4 || m == 6 || m == 9 || m == 11)
    {
        if(d > 30)
            return 0;
    }
    if(m == 2)
    {
        if(isLeapYear(y))
        {
            if(d > 29)    // checking if in leap year, feb contains more than 29 days
                return 0;
        }
        else
        {
            if(d > 28)    // checking if feb contains more than 28 days if not a leap year
                return 0;
        }
    }
    return 1;
}

// function to check if the return date entered by user is less than the issue date of book
int check_LessDate(date ret, date iss)    // ret stores return date, iss stores issued date of a book
{                                         // both ret and iss are date type structures
    if(ret.year < iss.year)               // checking if year of return is less than year of issued
        return 0;
    if((ret.year == iss.year) && (ret.month < iss.month))    // checking if return month is less than issue month
        return 0;
    if((ret.year == iss.year) && (ret.month == iss.month) && (ret.day < iss.day))
        return 0;
    return 1;
}

// function to calculate fine to be paid for an issued book returned late to the library
int cal_Fine(date *re, date *du)
{
    // re points to return date of book, du points to due date of a book (both are date pointers)

    date ret = *re, due = *du;      // ret stores date pointed by re (return date), due - date pointed bu du (due date)
    int days = 0;                   // to store number of days, the book is returned late
    int flag = 0;                   // if return month or year is more than due month or year(stores 1) else 0
    if(due.year > ret.year)
        return 0;
    if((ret.month > due.month) || (ret.year > due.year))
    {
        flag = 1;                   // flag stores 1 if return month or year is greater than due month or year, else 0
        days += ret.day;            // adding days of the return month
        if(ret.month == 1)
            ret.year--;
        ret.month--;                // decrease return month as its days are added
    }
    while(ret.year > due.year)      // runs until the due year is reached
    {
        if(ret.month == 0)
        {
            if(isLeapYear(ret.year))
                days += 366;
            else
                days += 365;
            continue;
        }
        while(ret.month > 0)
        {
            int mon = ret.month;
            if(mon == 1 || mon == 3 || mon == 5 || mon == 7 || mon == 8 || mon == 10 || mon == 12)
                days += 31;
            else if(mon == 4 || mon == 6 || mon == 9 || mon == 11)
                days += 30;
            else
            {
                if(isLeapYear(ret.year))
                    days += 29;
                else
                    days += 28;
            }
            ret.month--;
        }
        ret.year--;
    }
    int mon = ret.month;           //  mon stores return month
    if(mon == 0)
    {
        mon = 12;
    }
    while(mon > due.month)
    {
        if(mon == 1 || mon == 3 || mon == 5 || mon == 7 || mon == 8 || mon == 10 || mon == 12)
            days += 31;
        else if(mon == 4 || mon == 6 || mon == 9 || mon == 11)
            days += 30;
        else
        {
            if(isLeapYear(ret.year))
                days += 29;
            else
                days += 28;
        }
        mon--;
    }
    if(flag == 1)
    {
        // executes if return month was initially greater than due month
        // then we subtract due days from total days of due month

        if(mon == 1 || mon == 3 || mon == 5 || mon == 7 || mon == 8 || mon == 10 || mon == 12)
                days += (31 - due.day);
        else if(mon == 4 || mon == 6 || mon == 9 || mon == 11)
            days += (30 - due.day);
        else
        {
            if(isLeapYear(ret.year))
                days += (29 - due.day);
            else
                days += (28 - due.day);
        }
    }
    else if(mon == due.month)               // if return and due month are equal and return and due year also
        days += (ret.day - due.day);        // simply subtract due days from return days
    return days;
}

// function to calculate the due date of a book which is issued
void cal_due(date* d)    // d is date type pointer, points to a structure in which due date has to be stored
{                                        // initially due date contains issue date of book
    date temp = *d;                      // temp is used to store issue date that due date stores initially
    int flag = isLeapYear(temp.year);    // flag checks if year of issue is leap year (1 if leap else 0)
    d->day += 30;                        // adding 30 days to issue day
    d->month += 1;
    int mon = temp.month;
    if(mon == 1 || mon == 3 || mon == 5 || mon == 7 || mon == 8 || mon == 10 || mon == 12)
    {
        if(temp.day == 1)
            d->month -= 1;               // decrease due month if issue month has 31 days and issue day is 1
    }
    if(d->month > 12)
    {
        d->month = 1;
        d->year++;                       // incrementing due year if issue month is 12  and issue day is more than 1
    }
    if(d->month != temp.month)           // to subtract days of issue month from total due days to get due day
    {

        //  below if is for months having 31 days except jan
        if(mon == 3 || mon == 5 || mon == 7 || mon == 8 || mon == 10 || mon == 12)
            d->day -= 31;
        else if(mon == 4 || mon == 6 || mon == 9 || mon == 11)    // for months having 30 days
            d->day -= 30;
        else if(mon == 2)
        {
            if(flag)
                d->day -= 29;
            else
                d->day -= 28;
        }
        else                          // executes if issued month is 1 (january)
        {
            d->day -= 31;

            // below if else statement is to check case when issue month is 1 and issue day is 31
            if(flag)
            {
                if((d->day) > 29)
                {
                    d->month++;
                    d->day -= 29;
                }
            }
            else
            {
                if((d->day) > 28)
                {
                    d->month++;
                    d->day -= 28;
                }
            }
        }
    }
}
