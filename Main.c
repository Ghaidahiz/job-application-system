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

int main()
{

    addApplicant();
    
    for (int i = 0; i < numOfApplicants; i++) // print all the read applicant info *only for testing*
       printf("id: %d\nname: %s\neducation: %s\nexperience: %d\nmajor: %s\nGPA: %.2f\nstate: %s\npoint: %.2f\n\n********************\n", (list + i)->id, (list + i)->applicant, (list + i)->education, (list + i)->experience, (list + i)->major, (list + i)->GPA, (list + i)->state, (list + i)->points);
    
    calculatePoints();
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