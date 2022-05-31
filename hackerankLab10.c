#include <stdio.h>
#include <stdlib.h>

// Define a structure for save students datas
typedef struct student{
    int batch;
    int regNo;
    char firstName[20];
    char lastName[20];
    float cGPA;
    struct student *next;
}student_t;

// Declare a list for store the datas of student
student_t * head;

// Functions
void insertRecord();
void print_A_record();
void print_all();
void deleteA_Record();
int string_length(char s[]);
int eNum_to_n();
int stringToInt(char str[]);
void deleteNode(int position);

// Student count
int n = 0;

int main(){
    
    int option;

    // Print the instruction
        printf("--------------------------------------------\n");
        printf("A VOLATILE STUDENT RECORD MAINTENANCE SYSTEM\n");
        printf("--------------------------------------------\n");
        printf("0. Quit\n");
        printf("1. Insert a Student Record\n");
        printf("2. Print a Student Record\n");
        printf("3. Print all Student Records\n");
        printf("4. Delete a Student Record\n");

    // Select the function  option 
    while (1)
    {
        printf("------------------\n");
        printf("ENTER OPTION [0-4]\n");
        printf("------------------\n");

        scanf("%d", &option);

        if (option == 0)
        {
            return 0;
        }
        else if (option == 1)
        {
            insertRecord();   
        }
        else if (option == 2)
        {
            print_A_record();
        }
        else if (option == 3)
        {
            print_all();
        }
        else if (option == 4)
        {
            deleteA_Record();
        }
    }
}

// Function for insert a student record 
void insertRecord(){

    student_t * temp = (student_t*)malloc(sizeof(student_t));

    printf("Enter the batch (14/15/16/17): ");
    scanf("%d", &temp->batch);

    printf("Enter the registration number: ");
    scanf("%d", &temp->regNo);

    printf("Enter the first name         : ");
    scanf("%s", temp->firstName);

    printf("Enter the last name          : ");
    scanf("%s", temp->lastName);

    printf("Enter the cumulative GPA     : ");
    scanf("%f", &temp->cGPA);
    printf("\n");
    temp->next = head;
    head = temp;
    
    n++;
} 

// Function for asking E number from user and convert into 
int eNum_to_n(){
    char e_num[10];
    char split_enum[3][10];
    int batchNum, eNumber, n_value = -1;

    printf("Enter the Registration Number: ");
    scanf("%s", e_num);

    int j = 0, ctr = 0;
    // convert Registration number as 2D array
    for(int i = 0; i <= string_length(e_num) ; i++)
    {
        // if sace or NULL found, assign NULL into newString[ctr]
        if(e_num[i] == '/')
        {
            split_enum[ctr][j] = '\0';
            ctr++;  //for next word
            j=0;    //for next word, init index to 0
        }
        else
        {
            split_enum[ctr][j] = e_num[i];//put a word in char aray
            j++;
        }
    }

    batchNum = stringToInt(split_enum[1]);
    eNumber = stringToInt(split_enum[2]);
    student_t *search_temp = head;

    // Loop for find the position of given Reg No
    for (int i = 0 ;i < n ;i++){
        if(batchNum == search_temp->batch && eNumber == search_temp->regNo ){
            n_value = i;
            break;
        }
        search_temp = search_temp->next;
    }
    return n_value;

}

// Function for print a student data by asking E number
void print_A_record(){

    int num = eNum_to_n();
    student_t * printtemp  = head;
    
    if( num == -1) {
        printf("No student with the given Registration Number!\n");
        printf("\n");
    }
    else if(num == 1)
    {
        printf("The student %s %s (E/%d/%d) has a cumulative GPA of %0.2lf\n", head->firstName, head->lastName, head->batch, head->regNo, head->cGPA);
        printf("\n");
    }
    else
    {
        for (int i = 0; i < num; i++)
        {
        printtemp = printtemp->next;
        }
        printf("The student %s %s (E/%d/%d) has a cumulative GPA of %0.2lf\n", printtemp->firstName, printtemp->lastName, printtemp->batch, printtemp->regNo, printtemp->cGPA);
        printf("\n");
    }

}

// Function for print all srudents data at once
void print_all(){
    
    for(student_t * printAllTemp = head; printAllTemp != NULL ;printAllTemp = printAllTemp->next){
        printf("The student %s %s (E/%d/%d) has a cumulative GPA of %0.2lf\n", printAllTemp->firstName, printAllTemp->lastName, printAllTemp->batch, printAllTemp->regNo, printAllTemp->cGPA);
    
    }
    printf("\n");

}

//Function for delete a record
void deleteA_Record(){
    int num = eNum_to_n()+1;
    student_t * deleteTemp  = head;
    student_t * temp1 = NULL;

    //printf("%d\n",num);

    if(num == 0){
        printf("No student with the given Registration Number!\n");
        printf("\n");
    }
    else
    {
        deleteNode(num);
        printf("Delete Successful!\n");
        printf("\n"); 
        n--;
    }  
}

// Function for calculate the string length
int string_length(char s[]){
   int c = 0;
   while (s[c] != '\0')
      c++;

   return c;
}

// Function for convert char into integer
int stringToInt(char str[]){

    int i=0,sum=0;

    while(str[i]!='\0')     //string not equals to null
     {
        sum = sum*10 + (str[i] - 48);
        i++;
    }
    return sum;
}

//Function for delete a given node in a linked list
void deleteNode(int position)
{
    student_t * current = head,*  previous = head;

    // If position is one delete head and assign a new head
    if (position ==1)
    {
        head = current->next;
        free(current);
        current = NULL;
    }
    else
    {
        while (position != 1)
        {
            previous = current;
            current = current->next;
            position--;
        }
        previous->next = current->next;
        free(current);
        current = NULL;  
    }
}