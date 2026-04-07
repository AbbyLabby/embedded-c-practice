#include <stdio.h>

typedef struct
{
    int rollNumber;
    int studentSemister;
    char studentDOB[15];
    char studentBranch[50];
    char studentName[50];
} StudentRecord;

void init_array(StudentRecord *pStudentRecords);
int find_first_empty_node(StudentRecord *pStudentRecords);
void display_all_records(StudentRecord *studentRecords, int currentRecordsNumber);
void add_new_record(StudentRecord *pStudentRecords, int *pCurrentRecordsNumber);
int check_the_rollNumber(int newRecord, StudentRecord *pStudentRecords, int *pCurrentRecordsNumber);
void delete_record(StudentRecord *pStudentRecords, int *pCurrentRecordsNumber);
void display_menu();

int main()
{
    StudentRecord studentsRecords[10];
    int currentRecordsNumber = 0;
    int *pCurrentRecordsNumber = &currentRecordsNumber;

    init_array(studentsRecords);

    int userInput = 0;
    while(1)
    {
        display_menu();
        scanf("%d", &userInput);

        switch(userInput)
        {
            case 1:
                display_all_records(studentsRecords, currentRecordsNumber);
                break;
            case 2:
                add_new_record(studentsRecords, pCurrentRecordsNumber);
                break;
            case 3:
                delete_record(studentsRecords, pCurrentRecordsNumber);
                break;
            case 4:
                printf("Exiting application...\n");
                return 0;
                break;
        }
    }

    return 0;
}

void init_array(StudentRecord *pStudentRecords)
{
    for(int i = 0; i < 10; i++)
    {
        pStudentRecords[i].rollNumber = 0;
    }
}

void delete_record(StudentRecord *pStudentRecords, int *pCurrentRecordsNumber)
{
    if(*pCurrentRecordsNumber == 0)
    {
        printf("There is no any records\n");
        return;
    }

    int tempRollNumber = 0;

    printf("Delete a record\n");

    printf("Enter the roll number of the student: ");
    scanf("%d", &tempRollNumber);

    int result = check_the_rollNumber(tempRollNumber, pStudentRecords, pCurrentRecordsNumber);

    if(result == -1)
    {
        printf("Record with this rollNumber not found\n");
        return;
    }

    pStudentRecords[result].rollNumber = 0;

    (*pCurrentRecordsNumber)--;
    printf("Record deleted successfully\n");
}

void add_new_record(StudentRecord *pStudentRecords, int *pCurrentRecordsNumber)
{
    if(*pCurrentRecordsNumber == 10)
    {
        printf("Not enough space for new record, try to delete one\n");
        return;
    }

    int tempRollNumber = 0;

    printf("Add a new record\n");

    printf("Enter the rollNumber: ");
    scanf("%d", &tempRollNumber);

    int result = check_the_rollNumber(tempRollNumber, pStudentRecords, pCurrentRecordsNumber);

    if(result != -1)
    {
        printf("Record with this rollNumber already exsist\n");
        return;
    }

    int emptyNodeIndex = find_first_empty_node(pStudentRecords);

    if(emptyNodeIndex == -1)
    {
        printf("Unexpected result for find_first_empty_node\n");
        return;
    }

    pStudentRecords[emptyNodeIndex].rollNumber = tempRollNumber;

    printf("Enter the studentSemister: ");
    scanf("%d", &pStudentRecords[emptyNodeIndex].studentSemister);

    printf("Enter the studentDOB: ");
    scanf(" %[^\n]s", &pStudentRecords[emptyNodeIndex].studentDOB);

    printf("Enter the studentBranch: ");
    scanf(" %[^\n]s", &pStudentRecords[emptyNodeIndex].studentBranch);

    printf("Enter the studentName: ");
    scanf(" %[^\n]s", &pStudentRecords[emptyNodeIndex].studentName);

    (*pCurrentRecordsNumber)++;
    printf("Record added successfully\n");
}

int find_first_empty_node(StudentRecord *pStudentRecords)
{
    for(int i = 0; i < 10; i++)
    {
        if(pStudentRecords[i].rollNumber == 0)
            return i;
    }

    return -1;
}

int check_the_rollNumber(int newRecord, StudentRecord *pStudentRecords, int *pCurrentRecordsNumber)
{
    int result = -1;

    for(int i = 0; i < 10; i++)
    {
        if(newRecord == pStudentRecords[i].rollNumber)
        {
            result = i;
            return result;
        }
    }

    return result;
}

void display_all_records(StudentRecord *pStudentRecords, int currentRecordsNumber)
{
    if(currentRecordsNumber == 0)
    {
        printf("No records to display\n");
        return;
    }

    printf("Displaying all students recors\n");
    for(int i = 0; i < currentRecordsNumber; i++)
    {
        if(pStudentRecords[i].rollNumber == 0)
            continue;

        printf("----------------------------\n");
        printf("rollNumber: %d\n", pStudentRecords[i].rollNumber);
        printf("studentSemister: %d\n", pStudentRecords[i].studentSemister);
        printf("studentDOB: %s\n", pStudentRecords[i].studentDOB);
        printf("studentBranch: %s\n", pStudentRecords[i].studentBranch);
        printf("studentName: %s\n", pStudentRecords[i].studentName);
        printf("----------------------------\n");
    }
}

void display_menu()
{
    printf("Display all records -->1\n");
    printf("Add new record      -->2\n");
    printf("Delete a record     -->3\n");
    printf("Exit application    -->4\n");
    printf("Enter your option here: ");
}
