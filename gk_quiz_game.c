/*********************************************************************************************************
This is to certify that this project is my own work, based on my personal efforts in studying and applying 
the concepts learned. I have constructed the functions and their respective algorithms and corresponding code 
by myself. The program was run, tested, and debugged by my own efforts. I further certify that I have not 
copied in part or whole or otherwise plagiarized the work of other students and/or persons.

															CASSANDRA JO TULAGAN SABATER, DLSU ID#12278408
*********************************************************************************************************/

#include <stdio.h>
#include <string.h>
#include <conio.h>	// for getch() function
#include <stdlib.h>	// for random number generation
#include <time.h>	// for random number generation

#define ADMINPASS "Admin-Pass*123"		// Pre-set Admin Password

typedef char String20[21];
typedef char String150[151];
typedef char String30[31];

/* struct to store Quiz questions */
struct quizTag {
	String20 Topic;
	int Number;	
	String150 Question;
	String30 Choice[3];
	String30 Answer;
};

/* struct to store Player information */
struct playerTag {
	String20 Name;
	int Score;
};

/* 	--> void getInput

	This function is used to accept string parameter as input
	
	@param *sentence is the variable that will store the
		string
*/
void 
getInput (char* sentence)
{
	int i = 0;
	char ch;
	
	do {
		scanf("%c", &ch);
		if (ch != '\n')
		{
			sentence[i] = ch;
			i++;
			sentence[i] = '\0';
		}
	} while (i < 151 && ch != '\n'); // longest input will be 150 characters
}

/* 	--> void displayMainMenu

	This function displays the Menu where the user starts and ends the program
*/
void 
displayMainMenu()
{
	printf("\n\t%s%s%s\n", "------------", "------------", "------------");
	printf("\t\t      MAIN MENU\n");
	printf("\t%s%s%s\n", "------------", "------------", "------------");
	
	printf("1) Manage Data\n");
	printf("2) Play\n");
	printf("3) Exit\n");
}

/* 	--> void displayDataMenu 
	
	This function displays the different functions available to the Admin
	entity once their identity has been verified by asking for the password
*/
void 
displayDataMenu()
{
	printf("\n\t%s%s%s\n", "------------", "------------", "------------");
	printf("\t\t    Admin Section\n");
	printf("\t%s%s%s\n", "------------", "------------", "------------");
	
	printf("1) Add a record\n");
	printf("2) Edit a record\n");
	printf("3) Delete a record\n");
	printf("4) Import data\n");
	printf("5) Export data\n");
	printf("6) Go back to MAIN MENU\n");
}

/* 	--> void displayPlayMenu 

	This function displays the different functions available to the Player
	entity
*/
void 
displayPlayMenu()
{
	printf("\n\t%s%s%s\n", "------------", "------------", "------------");
	printf("\t\t    Player Section\n");
	printf("\t%s%s%s\n", "------------", "------------", "------------");
	
	printf("1) Play\n");
	printf("2) View Scores\n");
	printf("3) Go back to Main Menu\n");
}

/* 	--> void displayRecord 

	This function displays the different records stored under the current
	database of quiz questions
	
	@param *questionCount is the address that will refer to the 
		current number of questions in the database	
	@param record[] is the struct array that contains the 
		details of the current questions in the database
*/
void 
displayRecord(int* questionCount, struct quizTag record[])
{
	int i = 0;
	printf("Question Count = %d\n", *questionCount);
	for (i = 0; i < *questionCount; i++)
	{
		printf("Topic: %s\n", record[i].Topic);
		printf("Number %d\n", record[i].Number);
		printf("Question: %s\n", record[i].Question);
		printf("Choice 1: %s\n", record[i].Choice[0]);
		printf("Choice 2: %s\n", record[i].Choice[1]);
		printf("Choice 3: %s\n", record[i].Choice[2]);
		printf("Answer: %s\n", record[i].Answer);	
		
		printf("\n");
	}
}

/*	--> void displayTopics 
	
	This function displays the current unique topics as a numbered list
	
	@param *questionCount is the address that will refer to the 
		current number of questions in the database
	@param topicCount[] is the array that stores the frequency
		of each unique topic
	@param record[] is the struct array that contains the 
		details of the current questions in the database
*/
void 
displayTopics(int* questionCount, int topicCount[], struct quizTag record[])
{
	int i = 0;
	int topicNumber = 1;
	
	printf("\n");
	
	for (i = 0; i < *questionCount; i++)
	{
		if (topicCount[i] != -1) {
			printf("%-d %-3s %-5s\n", topicNumber++ , "Topic:", record[i].Topic);
		}
	}
}

/* 	--> void askPassword 

	This function prompts the user to enter the password for access to the
	Admin Section to verify their identity
	
	@param pass20 - string used to store the Access Password that user inputs
*/
void 
askPassword(String20 pass20)
{
	char ch;
	int i;
	
	 do 
	 {
		ch = getch();
		
		// '\r' is the Return character escape sequence (ENTER)
		// '\b' is the Backspace character escape sequence (BACKSPACE)
		if (ch != '\b' && ch != '\r') {		
			printf("*");	// to mask the password
			//printf("%c", ch);					
			pass20[i++] = ch;
		}
		else if (ch == '\r')	// if user hits ENTER button, terminate input sequence
		 	pass20[i] = '\0';		
		 	
		else if (ch == '\b') {	// if user hits BACKSPACE button, delete password input by one character					
			if (i > 0) {	
				printf("\b \b");	// moves cursor one space backwards, prints whitespace to erase character,
										// and moves one space back again for new output to start at old position		
				i--;		// the deleted character is also removed from pass20 array			
			}
		}
	 } while(ch != '\r' && i < 21);	// ask for input while ENTER button is not clicked and input characters are < 20
}

/*	--> int checkPassword 
	
	This function checks if the password that the user entered is equal to
	the pre-set Admin password

	@param pass20 - string used to store the Access Password that user inputs
	@return 1 if Access Password is equal to pre-set Admin Pass and returns 0
	if the two variables are not the same
*/
int 
checkPassword(String20 pass20)
{
	char choice = 0;			// choice to check if User wants to input pass or return to main menu
	int check = 0;
	
	// do while loop to allow user to input password as long as user chooses 'N' choice
	do {
		printf("\nThis feature is limited to Admins only (Enter 0 to exit)\n");
		printf("Enter the Password: ");

		askPassword(pass20);
		// compares Input Password with set Admin Password
		if (strcmp(pass20, ADMINPASS) == 0)
			check = 1;								// user is given access if pass20 and ADMINPASS are same
		else if (strcmp(pass20, "0") == 0) {
			printf("\nYou have chosen to exit.\n");
			choice = 'y';	// so to terminate asking of password
		}
		else {
			printf("\nThe input password is incorrect.\nDo you wish to return to the Main Menu? (y/n): ");
			scanf(" %c", &choice);					// otherwise, given option to return to Main Menu or retry input password
			if (choice == 'y' || choice == 'Y')
				check = 0;
		} 
	} while (choice == 'n' && check != 1);
	
	return check;
}


/*	--> void sortQuestions 
	
	This function sorts questions in Ascending order of Topic name

	@param *questionCount is the address that will refer to the 
		current number of questions in the database
	@param record[] is the struct array that contains the 
		details of the current questions in the database
*/
void 
sortQuestions (int* questionCount, struct quizTag record[])
{
	int i = 0, j = 0;
	struct quizTag temp;
	
	for (i = 0; i < *questionCount; i++)
	{
		for (j = 0; j < *questionCount - 1 - i; j++)
		{
			if (strcmp(record[j].Topic, record[j+1].Topic) > 0) {
				// swaps the records
				temp = record[j];
				record[j] = record[j+1];
				record[j+1] = temp;
			}
		}
	}
}

/*	--> void assignNumber 

	This function is used to automatically assign question number 
	to question once a new record is added. This is to be called after 
	sortQuestions so as to automatically number questions conveniently.
	
	@param *questionCount is the address that will refer to the 
		current number of questions in the database
	@param record[] is the struct array that contains the 
		details of the current questions in the database
*/
void 
assignNumber (int* questionCount, struct quizTag record[])
{
	int i = 0;
	int count = 1;

	for (i = 0; i < *questionCount; i++)
	{
		// if first question, automatically assigns that question the number 1.
		if (i == 0)
			record[i].Number = count;
		else if (strcmp(record[i-1].Topic, record[i].Topic) == 0) {
		// from 2nd loop onwards, if current question's topic is similar to previous one,
		//	increments count and assigns that current count value to the current question.
			count++;
			record[i].Number = count;
		}
		else
		// if current question's topic is not similar to the previous one, restarts 
		//	the count from 1 and assigns the current question that count value.
		{
			count = 1;
			record[i].Number = count;
		}
	}
} 

/* --> void addTopic
	
	This function keeps track of the frequency of unique topics of
	all questions in the database

	@param *questionCount is the address that will refer to the 
		current number of questions in the database
	@param topicCount[] is the array that stores the frequency
		of each unique topic
	@param record[] is the struct array that contains the 
		details of the current questions in the database
*/
void 
addTopic (int* questionCount, int topicCount[], struct quizTag record[])
{
	int i = 0, j = 0;
	int visited = -1;
	int count = 1;
	int fr[50];

	// call sortQuestions to sort array of records 
	sortQuestions(questionCount, record);

	for (i = 0; i < *questionCount; i++)
	{
		count = 1;
		for (j = i + 1; j < *questionCount; j++)
		{
			// if the current and succeeding Topic names are similar
			if (strcmp(record[i].Topic, record[j].Topic) == 0)
			{
				count++;
				fr[j] = visited;	
			}
		}
		if(fr[i] != visited) { // if current topic does not have the value -1, assigns the final accumulated count of that topic
			fr[i] = count;
		}
	}
	
	for (i = 0; i < *questionCount; i++)
	{
		topicCount[i] = fr[i];
	}	
	// call assignNumber to automatically number the questions
	assignNumber(questionCount, record);
	
	// printing out the unique topics and the number of questions under each topic
	for (i = 0; i < *questionCount; i++) 
	{
		if (topicCount[i] != visited)
		{
			printf("Topic: %s\n", record[i].Topic);
			printf("Topic Count = %d\n", topicCount[i]);
		}
	} 

}


/* --> void addRecord
	
	This function takes several variables to allow an Admin to
	add a record to the database

	@param *questionCount is the address that will refer to the 
		current number of questions in the database
	@param topicCount[] is the array that stores the frequency
		of each unique topic
	@param record[] is the struct array that contains the 
		details of the current questions in the database
*/
void 
addRecord(int* questionCount, int topicCount[], struct quizTag record[])
{
	String150 cQues;
	String30 cAns;
	String30 cChoice;
	String20 cTopic;
	String20 Exit;
	
	strcpy(Exit, "0");
	
	int i = 0, j = 0;
	int current = *questionCount - 1;
	int found = 0;
	char ch;
	
	if (record[current].Number > 0) // check if there's already a record before
	{
		scanf("%c", &ch);		// TO ACCOUNT FOR THE NEW LINE
		printf("\nEnter the question (Press 0 to exit): ");	
		getInput(cQues);
		
		if ((strcmp(cQues, "0") == 0)) 
		{
			printf("You have chosen to exit.");		
		}
		else
		{
			printf("\nEnter the answer: ");
			getInput(cAns);
			
			// checks if there is already a record with the input question and answer
			for (i = 0; i < *questionCount; i++)
			{
				if (strcmp(record[i].Question, cQues) == 0 && strcmp(record[i].Answer, cAns) == 0)
					found = 1;
			}
			
			// displays notice when user enters a question and answer that is alr listed
			if (found) {
				printf("\n");
				displayRecord(questionCount, record);
				printf("\n");
				printf("\nThis question and answer is already listed.");
			}
			else
			{
				printf("\nEnter the topic: ");
				getInput(cTopic);
				
				for (j = 0; j < 3; j++) 
				{
					printf("\nEnter Choice %d: ", j + 1);
					getInput(cChoice);	
					strcpy(record[*questionCount].Choice[j], cChoice);
				}
				strcpy(record[*questionCount].Topic, cTopic);
				strcpy(record[*questionCount].Question, cQues);
				strcpy(record[*questionCount].Answer, cAns);	
				(*questionCount)++;
			
				// calls addTopic to update frequency of Topics
				addTopic(questionCount, topicCount, record);
				
				printf("\n");
				displayRecord(questionCount, record);
				printf("\n");
				printf("Successfully added record!\n");	
			}				
		}
	}
	else	// if there is currently no existing record, asks for input regularly
	{
		scanf("%c", &ch);		// TO ACCOUNT FOR THE NEW LINE
		printf("\nEnter the question (Press 0 to exit): ");	
		getInput(cQues);

		if ((strcmp(cQues, "0") == 0)) 
		{
			printf("You have chosen to exit.");		
		}
		else 
		{
			printf("\nEnter the answer: ");
			getInput(cAns);
			
			printf("\nEnter the topic: ");
			getInput(cTopic);
		
			for (j = 0; j < 3; j++) {
				printf("\nEnter Choice %d: ", j + 1);
				getInput(cChoice);	
				strcpy(record[*questionCount].Choice[j], cChoice);
			}
			strcpy(record[*questionCount].Topic, cTopic);
			strcpy(record[*questionCount].Question, cQues);
			strcpy(record[*questionCount].Answer, cAns);	
			(*questionCount)++;
			
			// calls addTopic to update frequency of Topics
			addTopic(questionCount, topicCount, record);	
			
			printf("\n");
			displayRecord(questionCount, record);
			printf("\n");
			printf("Successfully added record!\n");		
		}
	}
}

/* --> void editRecord
	
	This function takes several variables to allow an Admin to
	edit a record from the database

	@param *questionCount is the address that will refer to the 
		current number of questions in the database
	@param topicCount[] is the array that stores the frequency
		of each unique topic
	@param record[] is the struct array that contains the 
		details of the current questions in the database
*/
void 
editRecord(int* questionCount, int topicCount[], struct quizTag record[])
{
	String20 cEdit;
	String20 cTopic;
	String150 cString;
	
	int i = 0, j = 0;
	int nEdit = 0;
	int nChoice;
	int nExit = 0;
	
	char ch;
	
	displayTopics(questionCount, topicCount, record);
	printf("\nChoose one of the above topics (Press 0 to exit): ");
	scanf("%c", &ch);	// to account for new line 
	getInput(cTopic);
	
	do {
		nExit = 0;	// resets nExit to 0 

		if (strcmp(cTopic, record[i].Topic) == 0)
		{
			for (j = i; j < i + topicCount[i]; j++)
			{
				printf("Topic: %s\n", record[j].Topic);
				printf("Number %d\n", record[j].Number);
				printf("Question: %s\n", record[j].Question);
				printf("Choice 1: %s\n", record[j].Choice[0]);
				printf("Choice 2: %s\n", record[j].Choice[1]);
				printf("Choice 3: %s\n", record[j].Choice[2]);
				printf("Answer: %s\n", record[j].Answer);	
				printf("\n");
			}	

			printf("\nEnter the question number of the record you wish to edit: ");
			scanf("%d", &nEdit);
			scanf("%c", &ch);	// to account for new line between integer and character
			
			for (j = i; j < i + topicCount[i]; j++)
			{
				if (record[j].Number == nEdit)
				{
					printf("Topic: %s\n", record[j].Topic);
					printf("Number %d\n", record[j].Number);
					printf("Question: %s\n", record[j].Question);
					printf("Choice 1: %s\n", record[j].Choice[0]);
					printf("Choice 2: %s\n", record[j].Choice[1]);
					printf("Choice 3: %s\n", record[j].Choice[2]);
					printf("Answer: %s\n", record[j].Answer);
					
					printf("\nWhich field would you like to edit? -- topic, question, choices, answer: ");
					getInput(cEdit);
					
					if (strcmp(cEdit, "topic") == 0)
					{
						printf("Topic: ");
						getInput(cString);
						strcpy(record[j].Topic, cString);
						addTopic(questionCount, topicCount, record); 
					}
					else if (strcmp(cEdit, "question") == 0)
					{
						printf("Question: ");
						getInput(cString);
						strcpy(record[j].Question, cString);
					}
					else if (strcmp(cEdit, "choices") == 0)
					{
						printf("Which choice do you wish to edit? -- 1, 2, 3: ");
						scanf("%d", &nChoice);
						scanf("%c", &ch);	// for new line between integer and character
						
						switch (nChoice)
						{
							case 1: printf("Choice 1: "); getInput(cString); strcpy(record[j].Choice[0], cString); break;
							case 2: printf("Choice 2: "); getInput(cString); strcpy(record[j].Choice[1], cString); break;
							case 3: printf("Choice 3: "); getInput(cString); strcpy(record[j].Choice[2], cString); break;
							default: printf("\nInvalid input."); break;
						}
					}
					else if (strcmp(cEdit, "answer") == 0)
					{
						printf("Answer: ");
						getInput(cString);
						strcpy(record[j].Answer, cString);
					}
					else
						printf("\nInvalid input.\n");
				}
				// if already on last record of topic, but number still does not match, displays warning message
				else if (j == i + topicCount[i] - 1 && record[j].Number != nEdit)
				{
					printf("\nThat number does not exist!\n");
				}
			}			
		}
		else if ((strcmp(cTopic, "0") == 0)) // If user inputs 0, then they will stop executing the edit record function
		{
			nExit = 1;
		}
		else if (i == *questionCount - 1)	// if searching last record and the topic is not found, invalid
		{
			nExit = 1;
			printf("\nInvalid input!\n");
		}
		i++;
	} while (i < *questionCount && nEdit == 0 && nExit == 0);	// loop until the user has entered a number to edit and has chosen to not exit
}


/* --> void deleteRecord
	
	This function takes several variables to allow an Admin to
	delete a record from the database

	Pre-condition: nDelete only takes integer parameters

	@param *questionCount is the address that will refer to the 
		current number of questions in the database
	@param topicCount[] is the array that stores the frequency
		of each unique topic
	@param record[] is the struct array that contains the 
		details of the current questions in the database
*/
void
deleteRecord(int* questionCount, int topicCount[], struct quizTag record[])
{
	String20 cTopic;
	
	int i = 0, j = 0, k = 0;
	int nExit = 0;
	int nDelete = 0;
	int found = 0;
		
	char cConfirm;	// RESET CONFIRM VALUE TO NULL EVERY TIME THE FUNCTION STARTS
	char ch;
	
	// displays all the unique topics currently registered
	displayTopics(questionCount, topicCount, record);
	
	printf("\nChoose one of the above topics (Press 0 to exit): ");
	scanf("%c", &ch);	// to account for new line 
	getInput(cTopic);
	
	do	
	{
		// if topic user enters matches one of the topics available..
		if (strcmp(cTopic, record[i].Topic) == 0)
		{
			for (j = i; j < i + topicCount[i]; j++)
			{
				// ..displays the questions from that specific topic
				printf("Topic: %s\n", record[j].Topic);
				printf("Number %d\n", record[j].Number);
				printf("Question: %s\n", record[j].Question);
				printf("Choice 1: %s\n", record[j].Choice[0]);
				printf("Choice 2: %s\n", record[j].Choice[1]);
				printf("Choice 3: %s\n", record[j].Choice[2]);
				printf("Answer: %s\n", record[j].Answer);
				printf("\n");
			}
			
			// asks the Admin which record they wish to delete
			printf("\nEnter the question number of the record you wish to delete: ");
			scanf("%d", &nDelete);	
			scanf("%c", &ch);	// for new line between integer and character
			
			for (j = i; j < i + topicCount[i] && found == 0; j++)
			{
				if (nDelete == record[j].Number)
				{
					printf("Topic: %s\n", record[j].Topic);
					printf("Number %d\n", record[j].Number);
					printf("Question: %s\n", record[j].Question);
					printf("Choice 1: %s\n", record[j].Choice[0]);
					printf("Choice 2: %s\n", record[j].Choice[1]);
					printf("Choice 3: %s\n", record[j].Choice[2]);
					printf("Answer: %s\n", record[j].Answer);
					
					// displays confirmation message to delete the record
					do {
						printf("\nAre you sure you want to delete this record? (y/n): ");
						scanf("%c", &cConfirm);
						scanf("%c", &ch); // for new line 
					} while (cConfirm != 'n' && cConfirm != 'y');

					if (cConfirm == 'y')
					{
					// the deleted record will be overwritten by the ones after it and so on.
						for (k = j; k < *questionCount; k++) 
						{
							record[k] = record[k+1];
							topicCount[k] = topicCount[k+1];	
						}
						(*questionCount)--;	// decrements the number of total questions by one
						addTopic(questionCount, topicCount, record);	// to arrange the records properly after deletion
					}
					found = 1;	
				}
				// if already on last record of topic, but number still does not match, displays warning message
				else if (j == i + topicCount[i] - 1 && record[j].Number != nDelete)
				{
					printf("\nThat number does not exist!\n");
				} 
			} 
		}
		else if ((strcmp(cTopic, "0") == 0))	// If user inputs 0, then they will stop executing the edit record function
		{
			nExit = 1;
		}
		else if (i == *questionCount - 1)	// if searching last record and the topic is not found, invalid
		{
			nExit = 1;
			printf("\nInvalid input!\n");
		}
		i++;
	}  while (i < *questionCount && nDelete == 0  && nExit == 0);	// loop until the user has entered a number to edit
}


/* --> void importData
	
	This function takes several variables to allow an Admin to
	import records from a .txt file

	@param *questionCount is the address that will refer to the 
		current number of questions in the database
	@param topicCount[] is the array that stores the frequency
		of each unique topic
	@param record[] is the struct array that contains the 
		details of the current questions in the database
*/
void
importData (int *questionCount, int topicCount[], struct quizTag record[])
{
	FILE *inputFile;
	String30 FILENAME;
	int nExit = 0;
	
	do {
		printf("\nEnter the filename of the text file e.g. 'filename.txt' ");
		printf("\n(Press 0 to exit): ");
		scanf("%s", FILENAME);
		
		inputFile = fopen(FILENAME, "r");
		
		if (strcmp(FILENAME, "0") == 0)
		{
			nExit = 1;
			printf("\nYou have chosen to exit.\n");
		}
		else if (inputFile == NULL)
			printf("\nThe file does not exists, please input the file name again.");
		else 
		{
			printf("\nFile is successfully opened! Importing...\n");
			nExit = 1;	
			
			while ((fscanf(inputFile, "%s\n%d\n%[^\n]%*c\n%s\n%s\n%s\n%s\n\n",
					record[*questionCount].Topic,
					&record[*questionCount].Number,
					record[*questionCount].Question,
					record[*questionCount].Choice[0],
					record[*questionCount].Choice[1],
					record[*questionCount].Choice[2],
					record[*questionCount].Answer)) == 7)
			{
				(*questionCount)++;	
			}  	
			
			printf("\n");
			addTopic(questionCount, topicCount, record);
			printf("\n");
			displayRecord(questionCount, record);
						
			printf("File is successfully imported!\n");		
		}
		fclose(inputFile);
		
	} while (nExit == 0);
}

/* --> void exportData
	
	This function takes several variables to allow an Admin to
	export records to a .txt file

	@param *questionCount is the address that will refer to the 
		current number of questions in the database
	@param record[] is the struct array that contains the 
		details of the current questions in the database
*/
void
exportData (int *questionCount, struct quizTag record[])
{
	FILE *outputFile;
	String30 FILENAME;
	
	int i = 0;
	int nExit = 0;

	do {
		printf("\nEnter the filename of the text file e.g. 'filename.txt' ");
		printf("\n(Press 0 to exit): ");
		scanf("%s", FILENAME);
		
		if (strcmp(FILENAME, "0") == 0)
		{
			nExit = 1;
			printf("\nYou have chosen to exit.\n");	 
		}
		else
		{
			nExit = 1;
			printf("\nExporting File...\n");

			// opens the file in write mode. It will overwrite the file if it exists
			outputFile = fopen(FILENAME, "w");

			// writes the information in the current run to the file
			for (i = 0; i < *questionCount; i++) {
				fprintf(outputFile,"%s\n%d\n%s\n%s\n%s\n%s\n%s\n\n",
							record[i].Topic,
							record[i].Number,
							record[i].Question,
							record[i].Choice[0],
							record[i].Choice[1],
							record[i].Choice[2],
							record[i].Answer);
			}
			printf("File is successfully exported!\n");
			
			fclose(outputFile);
		}
	} while (nExit == 0);
}


/* --> int isNewPlayer
	
	This function checks if the Player has played the game or not.
		
	Precondition: Players are allowed to play only once

	@param *playerCount is the address that will refer to the current
		number of registered players
	@param player[] is the struct array that contains the player
		details
	@param *playerName is the string that will store name that
		the Player has input
	@return 1 if the player is a New Player, otherwise return 0
*/
int
isNewPlayer (int* playerCount, struct playerTag player[], char* playerName)
{
	int i = 0;
	int check = 1;
	
	for (i = 0; i < *playerCount; i++)
	{
		// returns 0 if Player entered a name that has already been registered
		if (strcmp(playerName, player[i].Name) == 0)
			check = 0;
	}	
	return check;
}


/* --> void sortRanking
	
	This function is used to sort the scores of the registered Players
	in descending order, from first to last
	
	@param *playerCount is the address that will refer to the current
		number of registered players
	@param player[] is the struct array that contains the player
		details
*/
void 
sortRanking (int* playerCount, struct playerTag player[])
{
	int i, j, max;
	struct playerTag temp;
	
	for (i = 0; i < *playerCount; i++)
	{
		max = i;	// assumes the first index is the highest number
		
		for (j = i + 1; j < *playerCount; j++)
			if (player[max].Score < player[j].Score)
				max = j;
		
		// swaps the two records
		if(i != max) {
			temp = player[i];
			player[i] = player[max];
			player[max] = temp;
		}
	}	
}

/* --> void updatePlayerInfo
	
	This function is used to update the list of Players by taking 
	two parameters, i.e. the player name and score. It updates "score.txt"
	only if a player has successfully played and ended a Quiz Game.
	
	@param *name is an address that will refer to the name of the
		player that is currently playing
	@param score is the final score of the player that will be
		recorded
*/
void 
updatePlayerInfo (char* name, int score)
{
	FILE *fp;
	
	fp = fopen("score.txt", "a");
	
	fprintf(fp, "%s\n", name);
	fprintf(fp, "%d\n\n", score);
	
	fclose(fp);
}

/* --> void readPlayerInfo
	
	This function reads the list of Player records from a .txt file, 
	namely "score.txt" and overwrites it with the scores arranged from
	highest to lowest.
	
	@param *playerCount is the address that will refer to the current
		number of registered players
	@param player[] is the struct array that contains the player
		details
*/
void
readPlayerInfo (int* playerCount, struct playerTag player[])
{
	FILE *fp;
	int i = 0;
	
	fp = fopen("score.txt", "r");
	
	while ((fscanf(fp, "%s\n%d\n\n", player[i].Name, &player[i].Score) == 2))	// read data from file
	{	
		i++;
	}
	
	*playerCount = i;

	fclose(fp);	
	
	// SORTS THE CURRENT SCORES 
	sortRanking(playerCount, player);
	
	fp = fopen("score.txt", "w");
	
	// OVERWRITES score.txt with the sorted scores
	for (i = 0; i < *playerCount; i++)
	{
		updatePlayerInfo(player[i].Name, player[i].Score);
	}
	
	fclose(fp);
}

/* --> int initPlayer
	
	This function takes in several variables to initialize a Player 
	record. If a player has already played, they will not be able to 
	play again.
		
	Precondition: Players are allowed to play only once

	@param *playerCount is the address that will refer to the current
		number of registered players
	@param player[] is the struct array that contains the player
		details
	@param *questionCount is the address that will refer to the 
		current number of questions in the database
	@param isAnswered[] is the array that will keep track of which
		questions have been answered and which ones have not
		
	@returns 1 if a new player has entered their name so the new player 
		record can be initialized. Otherwise, returns 0 if user decides
		to opt out of the Play option
*/
int
initPlayer (int *playerCount, struct playerTag playerRecord[], int *questionCount, int isAnswered[])
{
	String20 playerName;
	int check;
	int nInitialize = 1;
	int i = 0;
	
	char ch;

	scanf("%c", &ch); // for new line	
	
	do {
		printf("\nPlease enter your name (Press 0 to exit): ");
		getInput(playerName);
		
 		readPlayerInfo(playerCount, playerRecord);				
 		check = isNewPlayer(playerCount, playerRecord, playerName);
 		
		if (strcmp(playerName, "0") == 0)	// if player chooses to exit
		{
			printf("\nYou have chosen to exit.\n");	 
			nInitialize = 0;
		}
		else if (!check)	// if an Old player enters their name
		{
			printf("This player has already played! Give other players a chance.\n");
		}
		else // if a New player enters their name
		{
			// Registers the input name in the database and initializes score to 0
			strcpy(playerRecord[*playerCount].Name, playerName);
			playerRecord[*playerCount].Score = 0;
			
			// Initializes isAnswered to 0 for all questions
			for (i = 0; i < *questionCount; i++)
				isAnswered[i] = 0;
				
			// increments player count
			(*playerCount)++;
		}
	} while (check != 1 && nInitialize == 1);
	
	return nInitialize;
}

/* --> void randomizeQuestion
	
	This function is used to generate a random question from the 
	database

	@param *number is the address that will be referred to
		as the number of the random question that will be asked
	@param *topic is an address that refers to the topic that 
		the player has chosen to test themselves on
	@param *questionCount is the address that will refer to the 
		current number of questions in the database
	@param record[] is the struct array that contains the 
		details of the current questions in the database
	@param topicCount[] is the array that stores the frequency
		of each unique topic
	@param isAnswered[] is the array that will keep track of which
		questions have been answered and which ones have not
*/
void 
randomizeQuestion (int* random, char* topic, int* questionCount, struct quizTag record[], int topicCount[], int isAnswered[])
{
	int i = 0, j = 0, k = 0;
	int upper, lower, range;
	int found = 0;
	
	int uniqueRandom[50];
	int unique;
	int newRandom = 0;
	
	// initialize array of unique random numbers
	for (i = 0; i < *questionCount; i++)
	{
		uniqueRandom[i] = 0;
	}
	
	i = 0;
	
	do
	{
		// if topic user enters matches one of the topics available..
		if (strcmp(topic, record[i].Topic) == 0)
		{		
			upper = topicCount[i]; // highest possible random number is the last question's number from that topic
			lower = 1;	// lowest possible random number is 1
			range = upper - lower + 1;	
	
			srand(time(NULL)); 	// initialize random number algo, initialized with no. of sec elapsed				
		
			// randomizes numbers by assigning unique random numbers to a separate array
			for (j = i; j < i + topicCount[i]; j++)
			{
				do {
					newRandom = (rand() % range) + lower;
					// assumes number is unique at first
					unique = 1;
					for (k = i; k < j; k++)
						if (uniqueRandom[k] == newRandom)
							unique = 0;	// if a random number similar to previous numbers is generated, not unique
				} while (!unique); // continues until the randomly generated number is unique	
				uniqueRandom[j] = newRandom;
			}

			for (k = i; k < i + topicCount[i]; k++)
			{
				for (j = i; j < i + topicCount[i] && found != 1; j++)
				{			
					// if question number matches a number in the unique random no. array and question 
					//		has not been answered, displays it and updates random number 
					if (uniqueRandom[k] == record[j].Number && isAnswered[j] == 0)
					{
						printf("Number %d\n", record[j].Number);
						printf("Question: %s\n", record[j].Question);
						printf("Choice 1: %s\n", record[j].Choice[0]);
						printf("Choice 2: %s\n", record[j].Choice[1]);
						printf("Choice 3: %s\n", record[j].Choice[2]);
						found = 1;	// to end searching of questions in topic
						isAnswered[j] = 1;	// so that the same question will not appear for player again
						*random = uniqueRandom[k];
					}
				}
			}	
			// if no new question is found, assigns number the value -1
			if (found == 0)
				*random = -1;	
		}
		i++;
	} while (i < *questionCount && found != 1);
} 

/* --> void playGame
	
	This function takes several variables to allow a Player to 
	play the game

	Pre-condition: playerAns accepts only integer input
	
	@param *questionCount is the address that will refer to the 
		current number of questions in the database
	@param record[] is the struct array that contains the 
		details of the current questions in the database
	@param topicCount[] is the array that stores the frequency
		of each unique topic
	@param *playerCount is the address that will refer to the current
		number of registered players
	@param player[] is the struct array that contains the player
		details	
	@param isAnswered[] is the array that will keep track of which
		questions have been answered and which ones have not
*/
void 
playGame(int* questionCount, struct quizTag record[], int topicCount[], 
			int* playerCount, struct playerTag player[], int isAnswered[])
{
	
	String30 CorrectAnswer;
	String20 topic;
	
	int i = 0, j = 0, k = 0;
	int random = 0;
	int playerAns = 0;
	int CorrectChoice = 0;
	
	char ch;
	
	strcpy(topic, "");
		
	displayTopics(questionCount, topicCount, record);
	printf("\nEnter the topic you would like to be tested on: ");
	getInput(topic);
	
	// generates a random question
	randomizeQuestion (&random, topic, questionCount, record, topicCount, isAnswered);
	
	for (i = 0; i < *questionCount; i++)
	{
		// if the topic that player enters matches record's topic
		if (strcmp(topic, record[i].Topic) == 0) {
			for (j = i; j < i + topicCount[i]; j++)
			{

				if (random == record[j].Number) {
					
					do {
						printf("\nWhat is the correct answer? (1, 2, 3): ");
						scanf("%d", &playerAns);
					} while (playerAns != 1 && playerAns != 2 && playerAns != 3);
					
					scanf("%c", &ch);	
					
					// Copies the correct Choice number and answer to separate variables 
					for (k = 0; k < 3; k++)
					{
						if (strcmp(record[j].Answer, record[j].Choice[k]) == 0)
							CorrectChoice = k + 1;					
					}
					strcpy(CorrectAnswer, record[j].Answer);
					
					// checks if the choice that the player chose is correct (same as answer string)
					if (strcmp(record[j].Choice[playerAns-1], record[j].Answer) == 0) 
					{
						printf("\nCorrect! You got it right.");
						(player[(*playerCount) - 1].Score)++;	// increments player score	
						printf("\nCurrent Score: %d\n", player[(*playerCount) - 1].Score);		
					}
					else 
					{
						printf("\nSorry! That's not the right answer.");
						printf("\nThe correct answer is Choice %d: %s", CorrectChoice, CorrectAnswer);
						printf("\nCurrent Score: %d\n", player[(*playerCount) - 1].Score);
					}
					// marks question as already answered by current player, so as to avoid repetition
					isAnswered[j] = 1;
				}
			}	
		}
	}
	
	// if random number passed from randomizeQuestion() is -1, all questions in selected topic has been asked
	if (random == -1)
	{
		printf("\nAll of the questions in this topic have been exhausted!\n");
	} 
}

/* --> void viewScores
	
	This function takes in several variables to display the scores of 
	all registered players (from previous and current program runs). It
	displays the scores in descending order, with their respective ranks
	
	@param *playerCount is the address that will refer to the current
		number of registered players
	@param player[] is the struct array that contains the player
		details
*/
void
viewScores (int* playerCount, struct playerTag player[])
{
	int i = 0;		

	printf("Number of Players = %d\n", *playerCount);
	printf("\nRank\tName\tScore\n");
	printf("-------------------------------\n");
	
	for (i = 0; i < *playerCount; i++)
	{
		printf("%d\t%s\t%d\n", i + 1, player[i].Name, player[i].Score);
	}
}


int 
main ()
{
	int topicCount[50];		// keeps track of the current number of unique topics
	int isAnswered[50];		// keeps track of already answered questions
	int initializePlayer;
	int questionCount = 0;
	int playerCount = 0;

	struct quizTag record[50];
	struct playerTag player[50];
	
	char nMainChoice, nAdminChoice, nPlayerChoice;	// variables to navigate through the menus
	char cContinue, cEdit, cDelete;	
	char ch; // for trailing new lines
	
	String20 AccessPass;	// variable to store the password that the user inputs to access "Manage Data" feature
	
	do {
		displayMainMenu();
		printf("Press the corresponding number to navigate through the menu: ");	
		scanf(" %c", &nMainChoice);
		
		switch (nMainChoice)
		{
			case '1': 
				if(checkPassword(AccessPass))	// asks for Admin Pass to limit access to collection of records
				{
					do {
						displayDataMenu();	// grants access to Admin Section once Admin's identity has been verified
						
						printf("Press the corresponding number to navigate through the menu: ");	
						scanf(" %c", &nAdminChoice);
						
						if (nAdminChoice == '1') {
							addRecord (&questionCount, topicCount, record);
						}
						else if (nAdminChoice == '2') {	
							cEdit = '\0';	
							if (questionCount == 0)		
							{
								printf("\nThere are currently no questions in the database!\n");
							}		
							else {
								do {
									editRecord (&questionCount, topicCount, record);
									printf("Do you wish to continue editing? (y/n): ");
									scanf("%c", &cEdit);
								} while (cEdit != 'n' && questionCount > 0); 							
							}	
						}
						else if (nAdminChoice == '3') {
							cDelete = '\0'; 
							if (questionCount == 0)		
							{
								printf("\nThere are currently no questions in the database!\n");
							}		
							else {
								do {
									deleteRecord (&questionCount, topicCount, record);
									printf("Do you wish to continue deleting? (y/n): ");
									scanf("%c", &cDelete);
								} while (cDelete != 'n' && questionCount > 0);	
							}
						}
						else if (nAdminChoice == '4') {
							importData(&questionCount, topicCount, record);					
						}	
						else if (nAdminChoice == '5') {
							
							if (questionCount == 0)
							{
								printf("\nThere are currently no questions in the database!\n");
							}
							else
								exportData(&questionCount, record);					
						}
						else if (nAdminChoice == '6') {
							printf("\nYou are being redirected to the Main Menu...\n");
						}
						else {
							printf("\nINVALID INPUT. Please select one of the choices above.\n");
						}
						
					} while (nAdminChoice != '6');
				}
				break;
				
			case '2':
			{
				do {
					displayPlayMenu();
					printf("Press the corresponding number to navigate through the menu: ");	
					scanf(" %c", &nPlayerChoice);

					if (nPlayerChoice == '1') 
					{
						// if there are currently no questions, displays a notice message
						if (questionCount == 0) {
							printf("\nThere are currently no questions in the database!\n");
						}
						else {
							initializePlayer = initPlayer(&playerCount, player, &questionCount, isAnswered);	
							cContinue = '\0';
						
							while (initializePlayer == 1 && cContinue !='n')
							{	
								playGame(&questionCount, record, topicCount, &playerCount, player, isAnswered);
								printf("\nContinue playing? (y/n): ");
								scanf("%c", &cContinue);
								scanf("%c", &ch);	// to account for new line 
								if (cContinue == 'n')
								{
									printf("\nYou have ended the game, thank you for playing!");
									printf("\n%s's final score: %d", player[playerCount - 1].Name, player[playerCount - 1].Score);
									// updates the player information in a separate .txt file by calling updatePlayerInfo	
									updatePlayerInfo(player[playerCount - 1].Name, player[playerCount - 1].Score);
								}
							}
						}
					}
					else if (nPlayerChoice == '2')
					{
						readPlayerInfo(&playerCount, player);
						viewScores(&playerCount, player);
					}
					else if (nPlayerChoice == '3') {
						printf("\nYou are being redirected to the Main Menu...\n");
					}
					else
					{
						printf("\nINVALID INPUT. Please select one of the choices above.\n");
					}
					
				} while (nPlayerChoice != '3');
			}
			break;
				
			case '3':
				printf("\nYou have exited the program. Have a nice day!"); break;
				
			default: 
				printf("\nINVALID INPUT. Please select one of the choices above.\n"); break;
		}
	} while (nMainChoice != '3');
	
	return 0;
}
