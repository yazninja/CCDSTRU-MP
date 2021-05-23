#include <stdio.h> 
#include <stdlib.h> 

/* Structure of X,Y positions*/ 
struct position
{ 
    int row,col; 
}; 
typedef struct position Player; 

/* Initializes values of variables in the game */ 
void gameInit(char P[][4], Player Ord[], Player Cha[], Player Free[])
{
    int row,col; int k = 0; 
    
	// set board to have spaces 
    for (row=0; row < 4; row ++) 
        for (col =0; col < 4; col++) 
            P[row][col] = ' '; 
    
	// initialize free 
    for (row = 0; row < 4; row ++) 
        for (col = 0; col < 4; col ++)
        { 
            Free[k].row= row+1; 
            Free[k].col= col+1; 
            k++; 
        } 
    
	// initialize Ord
    for (row = 0; row < 4; row++)
	{
		Ord[row].col = 0; 
		Ord[row].row = 0; 
	}
    
	// initialize Cha   
    for (row = 0; row < 11; row++)
	{
		Cha[row].col = 0; 
		Cha[row].row = 0; 
	}  
} 

/* Displays board, FREE, spaces Cha cannot take, and checks array */ 
void gameDisplay(char P[][4], Player Ord[], Player Cha[], Player Free[], Player H[]) 
{ 
    int row,col; 
    
	// display BOARD 
    printf("\nBOARD:\n\n"); 
    printf("    1   2   3   4  \n"); 
    printf("  _________________\n"); 
    for (row = 0; row < 4; row ++)
    { 
        printf("%d ",row+1); 
        for (col = 0; col < 4; col++)  
            printf("| %c ", P[row][col]);  
        printf("|\n"); 
        printf("  _________________\n"); 
    } 
    
	// display Free Spaces
    printf("\n\nFree Spaces:\n"); 
    for (row = 0; row < 16; row ++) 
    { 
        printf("(%d,%d)",Free[row].row, Free[row].col);
        if ((row+1) % 4 ==0) 
            printf("\n"); 
    }
    
	// Display H (spaces Cha cannot take) 
    printf("\n\nSpaces Cha cannot take: "); 
    for(row=0; row<5;row++) 
        printf("(%d,%d)", H[row].row, H[row].col); 
    printf("\n");
    
	// display Ord Spaces 
    printf("\nOrd:"); 
    for (row = 0; row < 4; row++) 
        printf("(%d,%d)", Ord [row].row, Ord[row].col); 
    printf("\n");
    
	// display Cha Spaces 
    printf("\nCha:"); 
    for (row = 0; row < 11; row++) 
        printf("(%d,%d)", Cha[row].row, Cha[row].col);
    printf("\n"); 
} 
        
/* checks if cha or ord can take up a space */ 
int checkArray(int x, int y, Player Array[], int nElem)
{ 
    int i; 
    for(i=0; i < nElem; i++) 
        if(Array[i].row == x && Array[i].col == y) 
            return 1; 
    return 0; 
} 

/* if cha/ord takes a free slot, it will no longer be free */ 
void removeFree (Player Free[], int row, int col) 
{
    int i; 
    for (i = 0; i < 16; i++)
        if(Free[i].row==row&&Free[i].col==col)
        { 
            Free[i].row = 0; 
            Free[i].col = 0; 
        }  
} 

/* if when ord decides to free up a spot, it will be free */ 
void addFree (Player Free [], int row, int col)
{ 
    int k=0; 
    int i, j;
    Player FreeCopy [16];
    
    //initialize FreeCopy 
    for (i=0; i < 4; i ++) 
        for (j=0; j < 4; j++){
                FreeCopy[k].row= i+1; 
                FreeCopy[k].col= j+1; 
                k++; 
        }
    
    for (i=0; i < 16; i ++){
      if(FreeCopy[i].row==row&&FreeCopy[i].col==col)
        if(Free[i].row==0&&Free[i].col==0){
          Free[i].row=row;
          Free[i].col=col;
        }
    }
}

/* when ord removes a position from his list, it becomes 0,0 */ 
void removePosition(Player nowPlayer[], int row, int col)
{ 
    int i; 
    for(i=0;i<4;i++)
        if(nowPlayer[i].row==row&&nowPlayer[i].col==col)
		{
			nowPlayer[i].row=0; 
			nowPlayer[i].col=0; 
		} 
            
} 

/* when ord takes a free space, it will take the values of the input */ 
void addPosition(Player nowPlayer[], int row, int col)
{ 
    int i, flag=0; 
    for(i=0;i<4;i++)
        if(nowPlayer[i].row==0&&nowPlayer[i].col==0&&flag==0)
        { 
            nowPlayer[i].row=row; nowPlayer[i].col=col; 
            flag++; 
        }  
} 

/* starts and ends turn, assigns positions to cha's list or ord's list */ 
void nextMove(char P[][4], Player H[], Player Free[],int row, int col, Player nowPlayer[], int *nElem, int *turn)
{ 
    if(*turn && !checkArray(row, col, H, 5) && checkArray(row, col, Free, 16))
    { 
        nowPlayer[*nElem].row = row; nowPlayer[*nElem].col = col; 
        removeFree(Free, row, col); P[row-1][col-1]='C'; 
        *turn = 0; 
        (*nElem)++; 
    }
    else if(!(*turn) && checkArray(row,col, Free, 16) && *nElem < 4)
    { 
        addPosition(nowPlayer, row, col); 
        removeFree(Free, row, col); 
        P[row-1][col-1]='O'; 
        *turn = 1; 
        (*nElem)++; 
    } 
    else if (!(*turn) && *nElem == 4 && checkArray(row,col,nowPlayer, 4))
    { 
        removePosition(nowPlayer, row, col); 
		addFree(Free, row, col);
        P[row-1][col-1]=' '; 
        (*nElem)--; 
    }
    else
      printf("\nYour input is invalid.\n");
} 

/* determine's cha or ord's winning condition */ 
int gameOver(Player Cha[],Player W[][3],Player Free[],Player H[], int turn)
{ 
    int i,j,k; 
    int count1=0, flag=0, count2=0; 
    Player FreeCopy[16]; 
    if(turn==1)
    { 
        for(i=0;i<4;i++)
        { 
            count1=0; 
            for(j=0;j<3;j++)
            { 
                k=0; 
                while(k<3)
                { 
                    if(W[i][j].row==Cha[k].row&&W[i][j].col==Cha[k].col)
                    { 
                        count1++; 
                        if(count1==3) 
                            flag=1; 
                    } 
                    k++; 
                } 
            } 
        } 
        if(flag==1) 
            return 1; 
    } 
    else
    { 
        for(i=0; i<16; i++) // copy Free to FreeCopy  
            FreeCopy[i] = Free[i]; 
        for (i=0; i < 16; i++) // remove H from FreeCopy 
            for (j=0; j < 5; j++) 
                if(FreeCopy[i].row == H[j].row && FreeCopy[i].col == H[j].col)
                { 
                    FreeCopy[i].row = 0; 
                    FreeCopy[i].col = 0; 
                } 
        for (i=0; i < 16; i++) // check if there is a value in FreeCopy 
            if(FreeCopy[i].row == 0 && FreeCopy[i].col == 0) 
                count2++; 

        if(count2==16) 
            return -1; 
    } 
    return 0; 
}

int main()
{ 
    Player W[][3] = {{{1, 4},{2, 4},{3, 4}}, 
                     {{2, 2},{3, 3},{4, 4}}, 
                     {{2, 3},{3, 2},{4, 1}}, 
                     {{4, 2},{4, 3},{4, 4}}}; 
    Player H[] = {{1, 1},{1, 2},{1, 3},{2, 1},{3, 1}}; 
    Player Ord[4], Cha[11], Free[16]; 
    char input, dump, P[4][4]; 
    int row, col, turn =1, over = 0, result=0; 
    int ordCtr=0, chaCtr = 0; 
    
    printf("Tic-Tac-Toe with extra rules! \n"); 
    gameInit(P, Ord, Cha, Free); 
    gameDisplay(P, Ord, Cha, Free, H); 
    while(over == 0)
    { 
        row=0; 
        col=0; 
        switch(turn)
        { 
            case 1: 
                printf("\n\n(1) Cha's Turn\n"); 
                do
                { 
                    printf("Enter row position: "); 
                    fflush(stdin); 
                    scanf("%c%c",&input,&dump); 
                    if(input!='1'&&input!='2'&&input!='3'&&input!='4')
                        printf("\nInput is invalid.\n\n");  
                    row = atoi(&input); 
                } while(input!='1'&&input!='2'&&input!='3'&&input!='4');
                do
                { 
                    printf("Enter col position: "); 
                    fflush(stdin); 
                    scanf("%c%c",&input,&dump); 
                    if(input!='1'&&input!='2'&&input!='3'&&input!='4')
                        printf("\nInput is invalid.\n\n"); 
                    col = atoi(&input); 
                } while(input!='1'&&input!='2'&&input!='3'&&input!='4');
                nextMove(P, H, Free, row, col, Cha, &chaCtr, &turn); 
                if(chaCtr==3)
					result = gameOver(Cha , W, Free, H, 1); 
                else
                  	result=gameOver(Ord, W, Free, H, 0);
                if(result!=0)
                  	over=1;
                gameDisplay(P,Ord,Cha,Free, H); 
                break; 
            
            case 0: 
                printf("\n\n(2)Ord's Turn\n"); 
                do
                {   if(ordCtr==4)
						printf("\nRemove a position\n\n");
                    printf("Enter row position: "); 
                    fflush(stdin); 
                    scanf("%c%c",&input,&dump); 
                    if(input!='1'&&input!='2'&&input!='3'&&input!='4')
                        printf("\nInput is invalid.\n\n"); 
                    row = atoi(&input); 
                } while(input!='1'&&input!='2'&&input!='3'&&input!='4'); 
                do
                { 
                    printf("Enter col position: "); 
                    fflush(stdin); 
                    scanf("%c%c",&input,&dump); 
                    if(input!='1'&&input!='2'&&input!='3'&&input!='4')
                        printf("\nInput is invalid.\n\n");
                    col = atoi(&input); 
                } while(input!='1'&&input!='2'&&input!='3'&&input!='4'); 
                nextMove(P, H, Free, row, col, Ord, &ordCtr, &turn); 
                result=gameOver(Ord, W, Free, H, 0);
                if(result!=0)
                  	over=1;
                gameDisplay(P,Ord,Cha,Free, H); 
                break; 
        } 
    }
    
    if(over == 1)
	{
		if(result==1)
      		printf("\nCHA WINS!\n");
    	else
      		printf("\nORD WINS!\n");  
	}
    return 0; 
}