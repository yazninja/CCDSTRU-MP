#include <stdio.h>
#include <stdlib.h>

struct position{
    int row,col;
};

typedef struct position Player;

void gameInit(char P[][4], Player Ord[], Player Cha[], Player Free[])
{
    int row,col;
    int k = 0;
    // set board to 0
    for (row=0; row < 4; row ++)
  	    for (col =0; col < 4; col++)
  	        P[row][col] = '*';
    // init free
    for (row = 0; row < 4; row ++)
        for (col = 0; col < 4; col ++){
            Free[k].row= row+1;
            Free[k].col= col+1;
		    k++;
        } 
    // init Ord and Cha to 0
    for (row = 0; row < 4; row++){
    Ord[row].col = 0;
    Ord[row].row = 0;
    }
    for (row = 0; row < 7; row++){
    Cha[row].col = 0;
    Cha[row].row = 0;
    }
}

void gameDisplay(char P[][4], Player Ord[], Player Cha[], Player Free[], Player H[]){

    int row,col;
  //  gameUpdate(P,Ord,Cha,Free);
    printf("\nBOARD:\n");
    printf("    1   2   3   4  \n");
    printf("  _________________\n");
    for (row = 0; row < 4; row ++){
        printf("%d ",row+1);
        for (col = 0; col < 4; col++){
            printf("| %c ", P[row][col]);
	    }
		printf("|\n"); 
        printf("  _________________\n");
  }

  printf("\n\nFree Spaces:\n");
    for (row = 0; row < 16; row ++){
      printf("(%d,%d)",Free[row].row, Free[row].col);
      
	    if ((row+1) % 4 ==0)
      	printf("\n");
    }
  
  printf("\n\nSpaces Cha cannot take: ");
  for(row=0; row<5;row++)
    printf("(%d,%d)", H[row].row, H[row].col);

  printf("\nOrd:\n");
	for (row = 0; row < 4; row++)
  	printf("(%d,%d)", Ord [row].row, Ord[row].col);

  printf("\nCha:\n");
  for (row = 0; row < 7; row++)
    printf("(%d,%d)", Cha[row].row, Cha[row].col);
}

int checkArray(int x, int y, Player Array[], int nElem){
    int i;
    for(i=0; i < nElem; i++)
        if(Array[i].row == x && Array[i].col == y)
            return 1;
    return 0;
}  

void removeFree (Player Free[], int row, int col){
  int i;

  for (i = 0; i < 16; i++){
    if (Free[i].row==row&&Free[i].col==col){
    	Free[i].row = 0;
    	Free[i].col = 0;
	  }  
  }
}

void addFree (Player Free [], Player pos){
  int row, col;
  int ctr = 0;
  int k = 0;
  Player FreeCopy [16];
  int PCopy [4][4];
  
  //initialize pCopy
  for (row=0; row < 4; row ++)
  	for (col=0; col < 4; col++)
  	  PCopy[row][col] = 0;
  
  //initialize FreeCopy
  for (row = 0; row < 4; row ++){
    for (col = 0; col < 4; col ++){
      if (PCopy[row][col]==0){ 
	  	  FreeCopy[k].row= row+1;
		    FreeCopy[k].col= col+1;
        k++;
      }
    }
  }

  ctr = checkArray(pos.row, pos.col, FreeCopy, 16);
  if (ctr){
    Free[ctr-1].row=pos.row;
    Free[ctr-1].col=pos.col;
  }
    
}

void nextMove(char P[][4], Player H[], Player Free[],int row, int col, Player nowPlayer[], int *nElem, int *turn){

    if(*turn && !checkArray(row, col, H, 5) && checkArray(row, col, Free, 16))
    {
        nowPlayer[*nElem].row = row;
        nowPlayer[*nElem].col = col;
        removeFree(Free, row, col);
        P[row-1][col-1]='1';
        *turn = 0;
        (*nElem)++;
    }
    else if(!(*turn) && checkArray(row,col, Free, 16) && *nElem < 4)
    {
        nowPlayer[*nElem].row = row;
        nowPlayer[*nElem].col = col;
        removeFree(Free, row, col);
        P[row-1][col-1]='0';
        *turn = 1;
        (*nElem)++;
    }
    else if (!(*turn) && *nElem == 4 && checkArray(row,col,nowPlayer, 4))
    {
        nowPlayer[*nElem].row = 0;
        nowPlayer[*nElem].col = 0;
        Free[(col-1)*4+(row-1)].row=row;
        Free[(col-1)*4+(row-1)].col=col;        
        P[row-1][col-1]='*';
        (*nElem)--;
    }
}

int gameOver(Player Cha[],Player W[][3],Player Free[],Player H[]){
  int i,j,k;
  int count=0;

	Player FreeCopy[16];

    for(i=0;i<4;i++){
      count=0;
      for(j=0;j<3;j++){
        k=0;
        while(k<3){
          if(W[i][j].row==Cha[k].row&&W[i][j].col==Cha[k].col){
            count++;
          }
          k++;
        } 
      }
    }
    if(count==3){
      return 1;
    }
    
	for(i=0; i<16; i++)// copy Free to FreeCopy
	{
		FreeCopy[i].row = Free[i].row;
		FreeCopy[i].col = Free[i].col;
	}
	for (i=0; i < 16; i++) // remove H from FreeCopy
		for (i=0; i < 5; i++)
			if(FreeCopy[i].row == H[j].row && FreeCopy[i].col == H[j].col)
			{
				FreeCopy[i].row = 0;
				FreeCopy[i].col = 0;
			}
	for (i=0; i < 16; i++) // check if there is a value in FreeCopy
		if(FreeCopy[i].row != 0 && FreeCopy[i].col != 0)
			return -1;
	return 0;
                
}

int main(){
    Player W[][3] = {{{1, 4},{2, 4},{3, 4}}, 
					           {{2, 2},{3, 3},{4, 4}}, 
					           {{2, 3},{3, 2},{4, 1}}, 
					           {{4, 2},{4, 3},{4, 4}}};
    Player H[] = {{1, 1},{1, 2},{1, 3},{2, 1},{3, 1}};

    char P[4][4];
    Player Ord[4], Cha[7], Free[16];
    int turn =1, over = 0;
    int ordCtr=0, chaCtr = 0;
    int row,col;
    char input, dump;

    printf("Tic-Tac-Toe but on drugs\n");
    gameInit(P, Ord, Cha, Free);
    gameDisplay(P, Ord, Cha, Free, H);

    while(!over){
      row=0; col=0; 
      switch(turn){
        case 1:
          printf("\n\n(1) Cha's Turn\n");	
          do{
        	  printf("Enter row position: ");
            scanf("%c%c",&input,&dump);
            if(input>='1'&&input<='4')
			        row = atoi(&input);
            else
              printf("\nInput is invalid.\n");
          }while(row==0);
          do{
            printf("Enter col position: ");
            scanf("%c%c",&input,&dump); 
            if(input>='1'&&input<='4')
			        col = atoi(&input);
            else
              printf("\nInput is invalid.\n"); 
          }while(col<1&&col>4);
          
          nextMove(P, H, Free, row, col, Cha, &chaCtr, &turn);
          gameDisplay(P,Ord,Cha,Free, H);
          break;
        case 0:
          printf("\n\n(2)Ord's Turn\n");
          do{
        	  printf("Enter row position: ");
            scanf("%c%c",&input,&dump);
            if(input>='1'&&input<='4')
			        row = atoi(&input);
            else
              printf("\nInput is invalid.\n");
          }while(row==0);
          
          do{
            printf("Enter col position: ");
            scanf("%c%c",&input,&dump); 
            if(input>='1'&&input<='4')
			        col = atoi(&input);
            else
              printf("\nInput is invalid.\n"); 
          }while(col<1&&col>4);
          nextMove(P, H, Free, row, col, Ord, &ordCtr, &turn);
          gameDisplay(P,Ord,Cha,Free, H);
          break;	        
        }
      
      if(chaCtr==3){
        over = gameOver(Cha , W, Free, H);
			if(over)
			{
				printf("\nCHA WINS!\n");
				return 0;
			}	
			else if (!over)
			{
				printf("\nORD WINS!\n");
				return 0;
			}
      }
    }
}