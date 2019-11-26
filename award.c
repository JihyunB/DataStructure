#include <stdio.h>
#include <stdlib.h>
#include <cType.h>
#include <stdbool.h>
#include "P5-16.h"
#include "linkListADT.h"

void printInstr (void);
LIST* buildList (void);
void process (LIST* list);
char getChoice (void);
void printList (LIST* list);
void search (LIST* list);
int cmpYear(void* pYear1, void* pYear2);

int main (void)
	{
		LIST* list;

		printInstr();
		list = buildList();
		process(list);
		printf( "End Best Pictures\n"
				"Hope you found your favorite!\n");
		return 0;
	}
void printInstr(void)
	{
		printf("This program prints the Academy Awards \n"
			   "Best picture of the Year and its director.\n"
			   "Your job is to enter the year; we will do\n"
			   "the rest. Enjoy.\n");
		return;
	}
LIST* buildList (void)
{
	FILE* fpData;
	LIST* list;

	short yearIn;
	int addResult;
	char c;
	PICTURE* pPic;

	list = createList(cmpYear);

	if(!list)
		printf("\aCannot create list\n"),
			exit(100);

	fpData = fopen("pictures.dat", "r");

	if(!fpData)
		printf("\aError opening input file\n"),
			exit(110);

	while(fscanf(fpData," %hd",&yearIn) == 1)
	{
		pPic = (PICTURE*) malloc(sizeof(PICTURE));
		if(!(pPic))
			printf("\aOut of Memory in build list\n"),
				exit(100);
		pPic->year = yearIn;

		while((fgetc(fpData)) != ' ');
		while((fgetc(fpData)) != '"');
		fscanf(fpData," %40[^\"], %*c",pPic->picture);
		while((fgetc(fpData)) != ' ');
		while((fgetc(fpData)) != '"');
		fscanf(fpData," %40[^\"], %*c",pPic->director);
		addResult = addNode (list, pPic);
		if(addResult != 0)
			if(addResult == -1)
				printf("Memory overflow adding movie\a\n"),
					exit(120);
			else
				printf("Duplicate year %hd not added\n\a",pPic->year);
		while ((c=fgetc(fpData)) != '\n'&&c != EOF);

	}
	fclose(fpData);
	return list;
}
void process(LIST* list)
{
	char choice;

	do
	{
		choice = getChoice();

		switch (choice)
		{
			case 'P' : printList(list);
					   break;
			case 'S' : search (list);
			case 'Q' : break;
		}
	}while(choice != 'Q');
	return;
}
void printList(LIST* list)
{
	PICTURE* pPic;

	if(listCount(list) == 0 )
		printf("Sorry, nothing in list\n\a");
	else
	{
		printf("\nBest Pictures List\n");
		traverse(list, 0,(void**)&pPic);
		do
		{
			printf("%hd %-40s %s\n",pPic->year,pPic->picture,pPic->director);
		}while(traverse(list,1,(void**)&pPic));
	}
	printf("End of Best Pictures List\n\n");
}
char getChoice(void)
{
	char choice;
	bool valid;

	printf("======= MENU ======\n"
		   "Here are your choices:\n"
		   " S: Search for a year\n"
		   " P: Printf all years\n"
		   " Q: Quit\n\n"
		   "Enter your choice: ");

	do
	{
		scanf(" %c", &choice);
		choice = toupper(choice);
		switch (choice)
		{
			case 'S' :
			case 'P' :
			case 'Q' : valid = true;
					   break;

			default: valid = false;
					 printf("\aInvalid choice\n"
					 		"Please try again: ");
					 break;
		}
	}while(!valid);
	return choice;
}
void search (LIST* list)
{
	short year;
	bool found;

	PICTURE pSrchArgu;
	PICTURE* pPic;

	printf("Enter a four digit year: ");
	scanf("%hd", &year);
	pSrchArgu.year = year;

	found = searchList(list, &pSrchArgu, (void**)&pPic);

	if(found)
		printf("%hd %-40s %s\n",pPic->year, pPic->picture,pPic->director);
	else
		printf("Sorry, but %d is not available.\n",year);

	return;
}
int cmpYear (void* pYear1, void* pYear2)
{
	int result;
	short year1;
	short year2;

	year1 = ((PICTURE*)pYear1)->year;
	year2 = ((PICTURE*)pYear2)->year;

	if(year1<year2)
		result = -1;
	else if(year1>year2)
		result = +1;
	else
		result = 0;

	return result;
}

