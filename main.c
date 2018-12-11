#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "movie.h"
#include "linkedList.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	
	FILE *fp; //FILE pointer for reading movie data 
	char name[200]; //movie name
	char country[10]; //movie country
	int runTime; //movie runtime
	float score; //movie score
	
	int exit_flag = 0; //flag variable for while loop
	int option; //user input option
	void *list, *mvInfo; //pointers for linked list and a specific structure instance for a movie data
	void *ndPtr; //void pointer for linked list node
	int cnt=0; // count the number of data
	
	//1. reading the movie.dat-----------------------------
	printf("Reading the data files...\n");
	//1.1 FILE open
	fp = fopen("movie.dat", "r");
	
	if(fp == NULL){
		printf("ERROR : File does not exist.\n");
	 return 0;
	}
	
	//1.2 list generation (use function list_genList() )
	list = list_genList();
	
	//1.3 read each movie data from the file and add it to the linked list
	while (		fscanf(fp, "%s %s %i %f", name, country, &runTime, &score) == 4)
	{	
		//generate a movie info instance(mvInfo) with function mv_genMvInfo()
		mvInfo = mv_genMvInfo(name, score, runTime, country);
		
		list_addTail(mvInfo, list);
		
	}
	
	printf("Read done! %i items are read!",	list_len(list));
	
	//1.4 FILE close
	fclose(fp);
	
	//2. program start
	while(exit_flag == 0) 
	{
		//2.1 print menu message and get input option
		printf("\n\n----------------------------Menu----------------------------\n");
		printf("1. Print all the movies.\n");
		printf("2. Search for specific country movies.\n");
		printf("3. Search for specific runtime movies.\n");
		printf("4. Search for specific score movies.\n");
		printf("5. exit.\n");
		printf("----------------------------Menu----------------------------\n");
		printf("-- Select an option : ");
		scanf("%i", &option);
		
		switch(option)
		{
			case 1: //print all the movies
				printf("\n printing all the movies in the list.....\n");
				
				ndPtr = list;
				while (list_isEndNode(ndPtr) != 1)
				{
					//2.2 print a movie data : use functions of movie.c and linkedList.c
					//ndPtr = the next node of the ndPtr;
					ndPtr = list_getNextNd(ndPtr);
					//get object of ndPtr to mvInfo void pointer
					mvInfo=list_getNdObj(ndPtr);
					//print the contents of the mvInfo
					mv_print(mvInfo);
					
				}
				printf("-----------------------------------------------------\n\n");
				printf("Totally %i movies are listed!\n",	list_len(list));
				
				break;
				
			case 2: //print movies of specific country
				//2.3.1 get country name to search for
				printf("Select a country : ");
				scanf("%s", &country);
				
				cnt=0; //Initialize Value 
				
				ndPtr = list;
					while (list_isEndNode(ndPtr) != 1)
				{
					//2.3.2 print a movie data : use functions of movie.c and linkedList.c
					//ndPtr = the next node of the ndPtr;
					ndPtr = list_getNextNd(ndPtr);
					//get object of ndPtr to mvInfo void pointer
					mvInfo=list_getNdObj(ndPtr);
					//if the input country matches to the country of the movie, 
					//then print the contents of the mvInfo
					if(strcmp(country, mv_getCountry(mvInfo))==0){
						mv_print(mvInfo);
						cnt++;
					}
				}
				/*When there is a value that meets the criteria*/
				if(cnt != 0){
					printf("-----------------------------------------------------\n\n");
					printf("Totally %i movies are listed!\n", cnt);				
				}
				/*If no value meets the criteria*/
				else
					printf("\nNo data with that information\n");
				
				break;
				
			case 3:
				//2.4.1 get minimal runtime value to search for
				printf("Select a runtime : ");
				scanf("%i", &runTime);
				
				cnt=0; //Initialize Value 
				
				ndPtr = list;
					while (list_isEndNode(ndPtr) != 1)
				{
					//2.4.2 print a movie data : use functions of movie.c and linkedList.c
					//ndPtr = the next node of the ndPtr;
					ndPtr = list_getNextNd(ndPtr);
					//get object of ndPtr to mvInfo void pointer
					mvInfo=list_getNdObj(ndPtr);
					//if the input runtime is lower than the runtime of the movie,
					//then print the contents of the mvInfo
					if(mv_getRunTime(mvInfo) < runTime){
						mv_print(mvInfo);
						cnt++;
					}					
				}
				/*When there is a value that meets the criteria*/
				if(cnt != 0){
					printf("-----------------------------------------------------\n\n");
					printf("Totally %i movies are listed!\n", cnt);				
				}
				/*If no value meets the criteria*/
				else
					printf("\nNo data with that information\n");
					
				break;
				
			case 4:
				//2.5.1 get minimal score value to search for
				printf("Select a score : ");
				scanf("%f", &score);
				
				cnt=0; //Initialize Value
				
				ndPtr = list;
					while (list_isEndNode(ndPtr) != 1)
				{
					//2.5.2 print a movie data : use functions of movie.c and linkedList.c
					//ndPtr = the next node of the ndPtr;
					ndPtr = list_getNextNd(ndPtr);
					//get object of ndPtr to mvInfo void pointer
					mvInfo=list_getNdObj(ndPtr);
					//if the input score is lower than the score of the movie,
					//then print the contents of the mvInfo
					if(score < mv_getScore(mvInfo)){
						mv_print(mvInfo);
						cnt++;
					}
				}
				/*When there is a value that meets the criteria*/
				if(cnt != 0){
					printf("-----------------------------------------------------\n\n");
					printf("Totally %i movies are listed!\n", cnt);				
				}
				/*If no value meets the criteria*/
				else
					printf("\nNo data with that information\n");
				
				break;
				
			case 5:
				printf("\nBye!\n\n");
				exit_flag = 1;
				break;
				
			default:
				printf("wrong command! input again\n");
				break;
		}
	}
	
	return 0;
}
