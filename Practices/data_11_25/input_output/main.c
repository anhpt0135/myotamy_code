#include <stdio.h>
#include <stdlib.h>

#define MAX_DATA 100
typedef enum{
	BLUE, GREEN, BROWN, BLACK, OTHER
}eEyeColour;

char *EyeTable[]={"blue", "green", "brown", "black", "other"};

typedef struct{
	char firstname[MAX_DATA];
	char lastname[MAX_DATA];
	int age;
	eEyeColour eyes;
	float income;
}infor_t;

infor_t *gPeople = NULL;

void print_out(infor_t *iPeople){
	printf("---- RESULTS----\n");
	printf("First Name: %s", iPeople->firstname);
	printf("Last Name: %s", iPeople->lastname);
	printf("Age: %d\n", iPeople->age);
	printf("Eyes: %s\n", EyeTable[iPeople->eyes]);
	printf("Income: %f\n", iPeople->income);
}

int main(int argc, char *argv[]){
	gPeople = (infor_t*)malloc(sizeof(infor_t));
	printf("What's your First Name ?");
	fgets(gPeople->firstname, MAX_DATA - 1, stdin);
	fflush(stdin);
	printf("What's your Last name ?");
	fgets(gPeople->lastname, MAX_DATA - 1, stdin);
	fflush(stdin);
	printf("How old are you ?");
	scanf("%d", &gPeople->age);
	fflush(stdin);
	printf("what color are your eyes: \
		\r\n1) Blue  \
		\r\n2) Green \
		\r\n3) Brown \
		\r\n4) Black \
		\r\n5) Other\n");
	printf(">");
	int tmp;
	scanf("%d", &tmp);
	fflush(stdin);
	gPeople->eyes = tmp - 1;
	printf("\nHow much do you make an hour?");
	scanf("%f", &gPeople->income);
	fflush(stdin);
	print_out(gPeople);
	free(gPeople);

	return 0;
}