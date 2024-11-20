#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    int id, experience;
    char applicant[21]; // 20 place for the applicant name as maximum and one place for null charecter
    char education[21];
    char major[6];
    float GPA, points;
    char state[10];

} Applicant;

Applicant *list = NULL;
int numOfApplicants = 0;
void addApplicant(); // function prototypes
void calculatePoints();
void writeAssignedApplicant();
void printList();

int main()
{

   addApplicant();

writeAssignedApplicant();    
    
        /* code */
    
            printf("\nتحياتي واشواقي للجميع\n");//remove later

  //  for (int i = 0; i < numOfApplicants; i++) // print all the read applicant info *only for testing*
       //printf("id: %d\nname: %s\neducation: %s\nexperience: %d\nmajor: %s\nGPA: %.2f\nstate: %s\npoint: %.2f\n\n********************\n", (list + i)->id, (list + i)->applicant, (list + i)->education, (list + i)->experience, (list + i)->major, (list + i)->GPA, (list + i)->state, (list + i)->points);
    calculatePoints();

    printList();//testing yay

    return 0;
}


void addApplicant()
{
    FILE *file = fopen("Applicants.txt", "r");
    fscanf(file, "%*[^\n]\n"); // to get rid of the first line
    fscanf(file, "%*[^\n]\n"); // to get rid of the second line
    int i = 1;
    char ch;
    while ((ch = fgetc(file)) != EOF)
    {
        fseek(file, -1, SEEK_CUR);                                  // to go back one step
        list = (Applicant *)realloc(list, sizeof(Applicant) * (i)); // realocate list of applicant each time we read new line until we reach End of File
        fscanf(file, "%d %s %s %d %s %f %s", &(list + i - 1)->id, (list + i - 1)->applicant, (list + i - 1)->education, &(list + i - 1)->experience, (list + i - 1)->major, &(list + i - 1)->GPA, (list + i - 1)->state);
        (list + i-1)->points = 0;
        i++;
    }
    numOfApplicants = i - 2;
}


void calculatePoints()
{
    for (int i = 0; i < numOfApplicants; i++)
    {
        if (strcmp("MSc", list[i].education) == 0) // checking if this applicant has a masters degree
            list[i].experience += 10;              // add 10 years to the experience
        list[i].points = list[i].GPA + (float) list[i].experience;
        printf(" applicant #%d points are: %.2f \n and was calculated by %.2f + %d\n",i+1,list[i].points, list[i].GPA, list[i].experience); //only for testing
    }
}


void writeAssignedApplicant(){// A func. outputs the file “Output_Applicants.txt”  with 3 lists ( Applicants & Candidates & Assigned ) 

    FILE *file= fopen("Output_Applicants.txt","w+");// create the required file 

fprintf(file,"\nThe applicants are:\n%-6s%-8s%-13s%-14s%-9s%-7s%-9s\n","id","Name","Education","Experience","Major","GPA","State");//print the header & bar of the 1st list "Applicants"

for ( int i = 0; i < numOfApplicants; i++){//Prints all Applicants with the OWL state 
    fprintf(file,"%-6d%-8s%-13s%-14d%-9s%-7.1f%-9s\n",(list+i)->id,(list+i)->applicant,(list+i)->education,(list+i)->experience,(list+i)->major,(list+i)->GPA,"OWL");
}//END OF FIRST LIST

fprintf(file,"\n----------\n");//FORMATING ONLY
fprintf(file,"\nThe Candidates list is:\n%-6s%-8s%-13s%-9s%-10s%-9s\n","id","Name","Education","Major","Points","State");//print the header & bar of the 2nd list "Candidates"


for ( int i = 0; i < numOfApplicants; i++){//Prints all Applicants with the "Candidate" state only
    if(strcmp(list->state,"candidate")== 0)
        fprintf(file,"%-6d%-8s%-13s%-9s%-10.1f%-9s\n",(list+i)->id,(list+i)->applicant,(list+i)->education,(list+i)->major,(list+i)->points,(list+i)->state);
}//END OF SECOND LIST

fprintf(file,"\n----------\n");//FORMATING ONLY
fprintf(file,"\nThe Assigned Applicants:\n");//print the header of the 3rd list "Assigned"

for ( int i = 0; i < numOfApplicants; i++){//Prints the Applicant with the "Assigned" state only
    if(strcmp(list->state,"Assigned")== 0){
        fprintf(file,"%-6d%-8s%-13s%-9s%-7.1f%-9s\n",(list+i)->id,(list+i)->applicant,(list+i)->education,(list+i)->major,(list+i)->points,(list+i)->state);
    }
        fprintf(file,"TEST\n");//remove later
}//END OF THIRD LIST
}//END OF THE FUNC. 

void printList(){// A func. outputs the data of the list as ( Applicants & Candidates & Assigned ) ON SCREEN 

printf("\nThe applicants are:\n%-6s%-8s%-13s%-14s%-9s%-7s%-9s\n","id","Name","Education","Experience","Major","GPA","State");//print the header & bar of the 1st list "Applicants"
    for ( int i = 0; i < numOfApplicants; i++){//Prints all Applicants with the OWL state
             printf("%-6d%-8s%-13s%-14d%-9s%-7.1f%-9s\n",(list+i)->id,(list+i)->applicant,(list+i)->education,(list+i)->experience,(list+i)->major,(list+i)->GPA,"OWL");//State as defaulte "OWL"
    }//END OF FIRST LIST

printf("\n----------\n");//FORMATING ONLY
printf("\nThe Candidates are:\n%-6s%-8s%-13s%-9s%-10s%-9s\n","id","Name","Education","Major","Points","State");//print the header & bar of the 2nd list "Candidates"

    for ( int i = 0; i < numOfApplicants; i++){//Prints all Applicants with the "Candidate" state only
        if(strcmp(list->state,"candidate")== 0)
             printf("%-6d%-8s%-13s%-9s%-10.1f%-9s\n",(list+i)->id,(list+i)->applicant,(list+i)->education,(list+i)->major,(list+i)->points,(list+i)->state);
    }//END OF SECOND LIST  

      printf("\nTEST1\n");//remove later


printf("\n----------\n");//FORMATING ONLY
printf("\nThe Assigned Applicants:\n");//print the header of the 3rd list "Assigned"

    for ( int i = 0; i < numOfApplicants; i++){//Prints the Applicant with the "Assigned" state only
        if(strcmp(list->state,"Assigned")== 0)
            printf("%-6d%-8s%-13s%-9s%-7.1f%-9s\n",(list+i)->id,(list+i)->applicant,(list+i)->education,(list+i)->major,(list+i)->points,(list+i)->state);
    }//END OF THIRD LIST

        printf("\nTEST2\n");//remove later
}