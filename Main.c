#include <stdio.h>
#include <String.h>
#include <stdlib.h>

typedef struct{
    int id, experience;
    char applicant[21]; // 20 place for the applicant name as maximum and one place for null charecter
    char education[21];
    char major[6];
    float GPA, points;
    char state[10];

} Applicant;

Applicant *list = NULL;   
int numOfApplicants = 0;
void addApplicant();     // function prototype


int main(){

    addApplicant();
    int i;
    for (i = 0; i < numOfApplicants; i++){ // print all the read applicant info
        printf("id: %d\nname: %s\neducation: %s\nexperience: %d\nmajor: %s\nGPA: %.1f\nstate: %s\npoint: %d\n\n********************\n", (list + i)->id, (list + i)->applicant, (list + i)->education, (list + i)->experience, (list + i)->major, (list + i)->GPA, (list + i)->state, (list + i)->points);
    }

    return 0;
}

void addApplicant(){
    FILE *file = fopen("Applicants.txt", "r");
    fscanf(file, "%*[^\n]\n"); // to get rid of the first line
    fscanf(file, "%*[^\n]\n"); // to get rid of the second line
    int i = 1;
    char ch;
    // while (!feof(file)){
    while ((ch = fgetc(file)) != EOF){
        fseek(file, -1, SEEK_CUR);     // to go back one step 
        list = (Applicant *)realloc(list, sizeof(Applicant) * (i));  // realocate list of applicant each time we read new line
        fscanf(file, "%d %s %s %d %s %f %s", &(list + i - 1)->id, (list + i - 1)->applicant, (list + i - 1)->education, &(list + i - 1)->experience, (list + i - 1)->major, &(list + i - 1)->GPA, (list + i - 1)->state);
        (list + i)->points = 0;
        i++;
    }
    numOfApplicants = i - 2;
}