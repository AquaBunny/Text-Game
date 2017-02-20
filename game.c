#include <stdio.h>
#include <string.h>
#define MAXINPUT 50
#define INVENTORYSIZE 100
/* gamestate is simply a number and will indicate what the next loop will say or do */
enum gameStates {EXIT,START,DOCK, BEACH};
/* Only make up to inventory size.  Each item is represented bya  specific slot in inventory. */
enum items{SPOON};
/* enum of directions */
enum directions{NORTH, SOUTH, EAST, WEST, INSIDE, OUTSIDE};

int gameloop(int gameState, int inventory[], char name[]);
void removeNewLine(char inputStr[]);
char * strToLower(char str[]);


int main(void)
{
	int gameState = START;
	char name[MAXINPUT];
	int inventory[INVENTORYSIZE] = {0};
	printf("Welcome to the game!\nPlease enter your character's name:");
	/* recieve input for user name */
	fgets(name,MAXINPUT,stdin);
	/*remove newline*/
	removeNewLine(name);
	printf("\nWelcome %s\n", name);
    /* loop until gamestate is returned as 0 */
	while(gameState)
	{
		gameState = gameloop(gameState, inventory, name);
	}
	return 0;
}

int gameloop(int gameState, int inventory[], char name[])
{
	unsigned int i, j;
	char input[MAXINPUT];
	char firstInput[MAXINPUT];
	char secondInput[MAXINPUT];
	/* given a gamestate determine what to print out. */ 
	switch(gameState)
	{
		case START:
			printf("Usable commands are:\n");
			printf("get [object] : Attempt to put item in inventory.\n");
			printf("use [object] : Attempt to use item in inventory or in area.\n");
			printf("go [direction] : Attempt to go a specific place.\n");
			printf("talk [something] : Attempt to talk to something.\n");
			printf("exit : exits the game\n");
			printf("suicide : kills self, as this world was too much to take.\n");
			printf("\nHit enter to begin adventure...\n");
			break;
		case DOCK:
			if(inventory[SPOON] == 0)
			{
				printf("You are %s. You find yourself on a dock.  The dock leads to land to the NORTH.  By your feet is a SPOON.\n", name);
			}
			else
			{
				printf("You find yourself on a dock.  The dock leads to land to the NORTH.\n");
			}
			
			break;
		case BEACH:
			printf("The beach is peaceful, there is an OLD MAN on the beach.\n");
			break;
	}
	/* get user input */
	printf("Input Command:");
	fgets(input,MAXINPUT,stdin);
	removeNewLine(input);
	strToLower(input);
	/* separate out the first and second half of the commands */
	for(i = 0; i < strlen(input); i++)
	{
		if(input[i] == 0 || input[i] == ' ')
		{
			break;
		}
		firstInput[i] = input[i];
	}
	firstInput[i]=0;
	for(; i < strlen(input); i++)
	{
		if(input[i] != 0 && input[i] != ' ')
		{
			
			break;
		}
	}
	for(j = 0; i < strlen(input); i++, j++)
	{
		secondInput[j] = input[i];	
	}
	secondInput[j] = 0;
	/* if statements to figure out what command occurred */
	if(strcmp(firstInput,"exit") == 0)
	{
		return EXIT;
	}
	else if(strcmp(firstInput,"get") == 0)
	{
		if(strcmp(secondInput, "spoon") == 0)
		{
			
			if(inventory[SPOON] == 1)
			{
				printf("You already have a spoon.\n");
			}
			else
			{
				switch(gameState)
				{
					case DOCK:
						printf("You pick up a spoon.\n");
						inventory[SPOON] = 1;
						break;
					default:
						printf("There is no spoon.\n");
						break;
				}
			}
		}
		else
		{
			printf("\nInvalid get target.\n");
		}
		return gameState;
	}
	else if(strcmp(firstInput,"use") == 0)
	{
		if(strcmp(secondInput, "spoon"))
		{
			if(inventory[SPOON] == 0)
			{
				printf("There is no spoon.\n");
			}
			else
			{
				
			}
		}
		else
		{
			printf("\nInvalid use target.\n");
		}
		return gameState;
	}
	else if(strcmp(firstInput,"go") == 0)
	{
		if(strcmp(secondInput,"north") == 0)
		{
		printf("north enetered\n");
			switch(gameState)
			{
				case DOCK:
					printf("You head NORTH onto the beach.\n");
					gameState = BEACH;
					break;
				default:
					printf("You cannot go north here.\n");
					break;
			}
		}
		else if(strcmp(secondInput, "south") == 0)
		{
			switch(gameState)
			{
				case BEACH:
					printf("You head SOUTH to the dock.\n");
					gameState = DOCK;
					break;
				default:
					printf("You cannot go south here.\n");
					break;
			}
		}
		else
		{
			printf("\nInvalid go target.\n");
		}
		return gameState;
	}
	else if(strcmp(firstInput,"talk") == 0)
	{
		printf("%s\n",secondInput);
		if(strcmp(secondInput, "old man") == 0 )
		{
			switch(gameState)
			{
				case BEACH:
					printf("He scowls at you saying something about bad omens on your arrival.\n");
					break;
				default:
					printf("The old man is not here.\n");
					break;
			}
		}
		else
		{
			printf("\nInvalid talk target.\n");
		}
		return gameState;
	}
	else
	{
		if(gameState == START)
		{
			printf("Dock Reached\n");
			return DOCK;
		}
		printf("\nInvalid Command.\n");
		/*debug line*/
		printf("\n Command was: '%s'\n First Part: '%s'\n Second Part: '%s' \n", input, firstInput, secondInput );
		return gameState;
	}
	/*should never get here only here for setup*/
	return gameState;
}
/*removes newline from line that used fgets*/
void removeNewLine(char inputStr[])
{
	inputStr[strlen(inputStr)-1] = 0;
	return;
}
/* converts all uppercase letters to lowercase */
char * strToLower(char str[])
{
	unsigned int i;
	for( i = 0 ; i < strlen(str) ; i++)
	{
		if(str[i] >= 'A' && str[i] <= 'Z')
		{
			str[i] += 32;
		}
	}
	return str;
}