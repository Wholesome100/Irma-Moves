#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "IrmaMoves.h"


char **createMapBoard(void)//Allocates memory for the board;
{
 char **board = malloc(sizeof(char*)*8);//Allocate 8 rows of *char arrays

  if(board == NULL)//Make sure board isn't null
    {
    printf("Board creation failed\n");//return NULL if malloc call fails
    return NULL;
    }

 for(unsigned int i=0;i<8;i++)
 {
     board[i] = malloc(sizeof(char)*8);//Allocate memory for columns

     if(board[i] == NULL)
     {
         return NULL;//Return NULL and break if any malloc calls fail
         break;
     }
 }


    //All of this is hard coded positions
    strncpy(board[0], "FF      ", 8);
    strncpy(board[1], " F      ", 8);
    strncpy(board[2], " FF     ", 8);
    strncpy(board[3], "  F     ", 8);
    strncpy(board[4], "  K     ", 8);
    strncpy(board[5], "C  B    ", 8);
    strncpy(board[6], " CC D   ", 8);
    strncpy(board[7], "  C  DD ", 8);

    return board;//Return the pointer to the board
    }




char **destroyMapBoard(char **board)//Gets rid of the current board
{
  for(unsigned int i=0;i<8;i++)
  {
      free(board[i]);//Clear all arrays board points to
  }
  free(board);//Clear the board variable itself

  return NULL;//Return null to make sure everything clears
}




void printMapBoard(char **board)
{
  printf("========\n");//Header = signs
  for(int i=0;i<8;i++)//Uses an i/j method to access and print board contents
    {
        for(int j=0;j<8;j++)
        {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
  printf("========\n\n");//Footer = signs
}




void parseNotationString(char *str, Move *Irma)
{
int i;
for(i=3;;i++)//For loop to get windspeed
{
    int temp;//Int to store int values of characters
    static int ws=0;//Static int to record ws, stays safe in for loop
	char c = str[i];
	if(c>='0' && c<='9') //Check if character is an int
	{
	    //Get the int value from a char, and add it to ws*10
		temp = c - '0';
		ws = ws*10 + temp;
	}
	else
	{
     //once whitespace is encountered, break and assign ws to irma struct
     Irma->irma.ws=ws;
     break;
	}

}

for(i+=1;;i++)//For loop to get windgust, very similar to ws
{
    int temp;
    static int wg=0;
	char c = str[i];
	if(c>='0' && c<='9')
	{
		temp = c - '0';
		wg = wg*10 + temp;
	}
	else
	{
     Irma->irma.wg=wg;
     break;
	}

}

//The first and second elements of board will always be column-row
Irma->from_loc.col = str[0];
Irma->from_loc.row = str[1] - '0';//The - '0' subtracts the ascii code, giving the digit


//The last and second to last elements of board will always be column-row
Irma->to_loc.col = str[strlen(str)-2];
Irma->to_loc.row = str[strlen(str)-1]-'0';

}




char **predictIrmaChange (char* str, Move *irmaMove)
{
char **board=createMapBoard();//Make the board

parseNotationString(str, irmaMove);//Read the string contents and assign values

char OG = board[irmaMove->from_loc.row][irmaMove->from_loc.col-'a'];//Store the character for the starting position
board[irmaMove->from_loc.row][irmaMove->from_loc.col-'a']='I';//Put Irma in the starting position

printMapBoard(board);//Print the initial board

int moveto, movefrom;//Variables to make working with windspeed and gusts concise
movefrom=irmaMove->from_loc.col-'a';
moveto=irmaMove->to_loc.col-'a';


while(movefrom != moveto)//While loop that predicts horizontal movement
{
    if(movefrom < moveto)//Gradually add/subtract movefrom till it's equal to target column
    {
        movefrom+=1;
        if(board[irmaMove->from_loc.row][movefrom] == ' ')//If whitespace (ocean) is encountered increase speeds
        {
            irmaMove->irma.ws+=10;
            irmaMove->irma.wg+=5;
        }
        else
        {
            irmaMove->irma.ws-=15;
            irmaMove->irma.wg-=10;
        }
    }
    else
    {
        movefrom-=1;
        if(board[irmaMove->from_loc.row][movefrom] == ' ')
        {
            irmaMove->irma.ws+=10;
            irmaMove->irma.wg+=5;
        }
        else
        {
            irmaMove->irma.ws-=15;
            irmaMove->irma.wg-=10;
        }
    }
}

movefrom=irmaMove->from_loc.row;//Assign values for rows to movefrom and moveto
moveto=irmaMove->to_loc.row;
while(movefrom != moveto)//While loop very similar to one above, this one calculates vertical movement
{
    if(movefrom < moveto)
    {
        movefrom+=1;
        if(board[movefrom][irmaMove->to_loc.col-'a'] == ' ')
        {
            irmaMove->irma.ws+=10;
            irmaMove->irma.wg+=5;
        }
        else
        {
            irmaMove->irma.ws-=15;
            irmaMove->irma.wg-=10;
        }
    }
    else
    {
        movefrom-=1;
        if(board[movefrom][irmaMove->to_loc.col-'a'] == ' ')
        {
            irmaMove->irma.ws+=6;
            irmaMove->irma.wg+=3;
        }
        else
        {
            irmaMove->irma.ws-=2;
            irmaMove->irma.wg-=1;
        }
    }
}
board[irmaMove->from_loc.row][irmaMove->from_loc.col-'a']=OG;//Put the original character back when moving I
board[irmaMove->to_loc.row][irmaMove->to_loc.col-'a']='I';//Assign I to it's final position

printMapBoard(board);//Print the board with final location of I


return board;//Return the board pointer after everything is done
}


double difficultyRating(void)
{
    double hard=3.5;
    return hard;//This project looked daunting and I had difficulty starting, after getting some help I finished it up easy
}


double hoursSpent(void)
{
    double hours=6.5;
    return hours;//6.5 hours sounds right for the time I spent on the project
}
