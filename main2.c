#include<stdio.h>

void swap (int *x, int *y)
{
	int temp;
	
	temp = *x;
	*x = *y;
	*y = temp;
	
}

void sort (int player [4][2]){
	int bSwap, row, nElem = 4;
	
	do{
		bSwap = 0;
		for (row = 0; row < nElem-1; row++){
			if (player[row][0] > player [row+1][0]){
				swap (&player[row][0],& player[row +1][0]);
				swap(&player[row][1],& player[row +1][1]);
				bSwap = 1;
			}
		}
		nElem--;
	}while (bSwap);
}


void setGame(int P[4][4], int Free[16][2], int Cha[4][2], int Ord[4][2]){
  int row,col;
  int k = 0;

  for (row=0; row < 4; row ++)
  	for (col =0; col < 4; col++)
  	  P[row][col] = 0;

  //initialize free spaces
  for (row = 0; row < 4; row ++){
    for (col = 0; col < 4; col ++){
      if (P[row][col]== 0){ 
	  	Free[k][0]= row+1;
        Free[k][1]= col+1;
		k++;
      }
    }
  }
    
  //initialize Cha
  for (row = 0; row < 4; row++){
	Cha[row][0]=0;
	Cha[row][1]=0;
  }
	  
  //initialize Ord
  for (row = 0; row < 4; row++){
	Ord[row][0]=0;
	Ord[row][1]=0;
  }
		
}

void displayGame (int P[4][4], int Free[16][2], int Ord[4][2], int Cha[4][2]){
  int row, col, i;

  //display playing board
   printf("\nBOARD:");
    printf("\n-----------------\n");
    for (row = 0; row < 4; row ++){
    	  for (col = 0; col < 4; col++){
          	printf("| %d ", P[row][col]);
		  }
		  printf("|\n"); 
      printf("-----------------\n"); 
      }


  //display free spaces
    printf("\n\nFree Spaces:\n");
    for (row = 0; row < 16; row ++){
      printf("(%d,%d)",Free[row][0], Free[row][1]);
      
	  if ((row+1) % 4 ==0)
      	printf("\n");
    }

  //display Ord
  printf("\nOrd:\n");
	for (row = 0; row < 4; row++)
  	  printf("(%d,%d)", Ord [row][0], Ord[row][1]);

  //display Cha
  printf("\nCha:\n");
    for (row = 0; row < 4; row++)
      printf("(%d,%d)", Cha[row][0], Ord[row][1]);

}

//returns which row the pos can be found
int checkFree (int Free[16][2], int pos[2]){
	int row;

	for(row = 0; row < 16; row++){
        if (Free[row][0]==pos[0] && Free[row][1]==pos[1]){
        	return row++;
        } 
    }
    
	return 0;
}

//returns 1 if available
int checkPlayer (int player [4][2], int pos[2]){
	int row;
	
	for (row = 0; row < 4; row ++){
		if (player[row]==pos)
		return 1;
	}
	
	return 0;
}

void removeFree (int Free[16][2], int pos[2]){
  int row;
  
  for (row = 0; row < 16; row++){
    if (Free[row]==pos){
    	Free[row][0] = 0;
    	Free[row][1] = 0;
	}  
  }
}

void addFree (int Free [16][2], int pos[2]){
  int row, col;
  int ctr = 0;
  int k = 0;
  int FreeCopy [16][2];
  int PCopy [4][4];
  
  //initialize pCopy
  for (row=0; row < 4; row ++)
  	for (col =0; col < 4; col++)
  	  PCopy[row][col] = 0;
  
  //initialize FreeCopy
  for (row = 0; row < 4; row ++){
    for (col = 0; col < 4; col ++){
      if (PCopy[row][col]== 0){ 
	  	FreeCopy[k][0]= row+1;
		FreeCopy[k][1]= col+1;
        k++;
      }
    }
  }

  ctr = checkFree (FreeCopy,pos);
  if (ctr != 0){
    Free[ctr-1][0]=pos[0];
    Free[ctr-1][1]=pos[1];
  }
    
}

void removePlayer (int player [4][2], int pos[2]){
	int row;
	for (row = 0; row < 4; row++)
	{
		if (player [row]==pos){
			player [row][0] = 0;
			player [row][1] = 0;
		}
		
	}
}

void nextPlayerMove (int P[4][4], int Free [16][2], int player[4][2], int *turnCount, int flag){
  int pos[2];
  int getPos=0;

  while(getPos==0){
    if (*turnCount == 4)
    	printf("You have reached the maximum number of markers.\n Re-enter a position to remove.");
    printf("Enter positon row:");
    scanf("%d", &pos[0]);
    printf("Enter positon column:");
    scanf("%d", &pos[1]);

    if (checkFree(Free, pos) && *turnCount < 4){
      player[*turnCount][0] = pos[0];
      player[*turnCount][1] = pos[1];
      P[pos[0]][pos[1]] = flag;
      removeFree(Free, pos);
      *turnCount++;
      getPos++;
	}
	
	else if (checkPlayer(player, pos) && *turnCount == 4){
    	printf("Removed position (%d,%d).\n", pos[0], pos[1]);
    	removePlayer(player,pos);
      	addFree(Free, pos);
    	P[pos[0]][pos[1]] = 0;
    	*turnCount = 0;
    	getPos++;
    }
    
    else if (!checkFree(Free, pos))
    printf("Position already taken.\n");
    printf("%d", checkFree(Free, pos));
  }
}

int gameOver(int W [4][3][2], int player [4][2]){
	int row, col,ctr;
	int win =0;
	
	sort(player);
  
	if (player[1][0] != 2 && player[1][1] != 2)
	return 0;
	
	for (row = 0; row < 4; row++){
		//for(col=0; col<3; col++){
			if (W[row][0][0]==player[0][0] && W[row][0][1]==player[0][1])
		  	if(W[row][2][0]==player[2][0] && W[row][2][1]==player[2][1])
		  	return 1;
		//}	
		
	}
	return 0;
}


int main(){
	int W[][3][2]={{{1, 4},{2, 4},{3, 4}}, 
					{{2, 2},{3, 3},{4, 4}}, 
					{{2, 3},{3, 2},{4, 1}}, 
					{{4, 2},{4, 3},{4, 4}}};
					
	int H[][2]={{1, 1},{1, 2},{1, 3},{2, 1},{3, 1}};
	  
	int  P[4][4], Ord[4][2], Cha[4][2], Free[16][2];
	int turn=1; 
	int over=0;
	                   
    int row, col;
    int ordCtr = 0;
    int chaCtr = 0;

	printf("CCDSTRU\n");
	setGame(P, Free, Cha, Ord);
	displayGame (P,Free,Ord,Cha);
	
	while (!over){ //meaning !(0) so true 
	  if (turn==1){
	      printf("\n\n(1) Cha's Turn\n");	
	     
		 nextPlayerMove(P,Free, Cha, &chaCtr, 1);
	     displayGame (P,Free, Ord, Cha);
	     if (chaCtr == 4){ 
	         if (gameOver(W,Cha)){
			  	 printf("\n*************Player Cha Wins!*************");
	      	  	 over++;
	      	   }
		   }
	     turn =0;
	    }
	    
	  else if (!turn){
		 printf("\n\n(2)Ord's Turn\n");	
		 nextPlayerMove(P,Free, Ord, &ordCtr,2);
	     displayGame (P,Free, Ord, Cha);
	     if (ordCtr == 4){
	        if (gameOver(W,Ord)){
			  	 printf("\n*************Player Ord Wins!*************");
	      	  	 over+=1;
	      	}
		 }
	     turn =1;
	  }
		
	}
	    
		return 0;
}