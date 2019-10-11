#include <stdio.h>
#include <stdlib.h>

struct node{
	int data;
	struct node *next;
};

struct node *start = NULL;
void append();
void addbegin();
void addspecific();
void delete();
void display();

int main(void){
	int ch;
	while(1){
		printf("**CHOSE THE FOLLOWING OPTIONS:\n");
		printf("1. add at end\n");
		printf("2. add at begin\n");
		printf("3. add a specific node\n");
		printf("4. delete a node\n");
		printf("5. dislay\n");
		printf("6. exit\n");
		scanf("%d", &ch);
		switch(ch){
			case 1:
				append();
				break;
			case 2:
				addbegin();
				break;
			case 3:
				addspecific();
				break;
			case 4:
				delete();
				break;
			case 5:
				display();
				break;
			case 6:
				return 0;
			default:
				printf("Invalid input \n");
		}
	}
	
	return 0;
}

void append(){
	int data;
	struct node *tmp;
	tmp = (struct node *)malloc(sizeof(struct node));
	printf("append func, type in the number you want to add: \n");
	scanf("%d", &data);
	tmp->data=data;
	tmp->next=NULL;
	if(start == NULL){
		start = tmp;
	}else{
		struct node *tmploop;
		tmploop = start;
		while(tmploop->next != NULL){
			tmploop = tmploop->next;
		}
		tmploop->next = tmp;
	}
}
void addbegin(){
	int data;
	printf("addbegin func, type in the number you want to add: \n");
	scanf("%d", &data);
	struct node *tmp;
	tmp = (struct node*)malloc(sizeof(struct node));
	tmp->data = data;
	tmp->next = NULL;
	if(start == NULL){
		start = tmp;
	}else{
		tmp->next = start;
		start = tmp;
	}
}
void addspecific(){
	int data;
	printf("addspecific func, type in the number you want to add: \n");
	scanf("%d", &data);
}
void delete(){
	int op;
	printf("delete func, chose one of the following options\n");
	printf("1.Delete a specified node\n");
	printf("2.Delete all the list\n");
	printf("3.Delete at the beginning list\n");
	printf("4.Delete at the end of the list\n");
	scanf("%d", &op);
}
void display(){
	printf("*************display func***************\n");
	struct node *tmploop;
	tmploop = start;
	while(tmploop != NULL){
		printf("%d  ", tmploop->data);
		tmploop=tmploop->next;
	}
	printf("\n****************************************\n");
}