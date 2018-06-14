#include <stdio.h>
//initing the board with corresponding integer values for each piece
int board[8][8]={{11, 12, 13, 14, 15, 13, 12, 11},
				 {10, 10, 10, 10, 10, 10, 10, 10},
				 {0 ,  0,  0,  0,  0,  0,  0,  0},
				 {0 ,  0,  0,  0,  0,  0,  0,  0},
				 {0 ,  0,  0,  0,  0,  0,  0,  0},
				 {0 ,  0,  0,  0,  0,  0,  0,  0},
				 {1 ,  1,  1,  1,  1,  1,  1,  1},
				 {2 ,  3,  4,  5,  6,  4,  3,  2},};




//1, White pawn		10, Black pawn
//2, white rook		11, black rook
//3, white knight	12, black knight
//4, white bishop	13, black bishop
//5, white queen	14, black queen
//6, white king		15, black king
//-------------------------------------//archaic.......
//7, whit rook1,	16, black rook1 
//8, white kinght1	17, black knight 1
//9, white bishop 1	18, black bishiop

int abs(int x);

void print_board() //prints the curren board status
{
   int i, j;
   for (i=0; i<8; i++)
   {
      for (j=0; j<8; j++) 
	  {
      	printf("%d ",board[i][j]);		 
      }
      printf("\n");
   }	
}
void print_locale(int i, int j) //prints the value of a single board locale to the console
{
	printf("board value:   ");
    printf("%d ",board[i][j]);
    printf("\n");
}

int contains_white(int ycoord, int xcoord) // returns 1 if a white piecce is present in the queried locale, otw, returns 0
{
	int yes;
	yes=0;
		
	if ((board[ycoord][xcoord] == 1) || (board[ycoord][xcoord] == 2) || (board[ycoord][xcoord] == 3) || 
		(board[ycoord][xcoord] == 4) || (board[ycoord][xcoord] == 5) || (board[ycoord][xcoord] == 6) || 
		(board[ycoord][xcoord] == 7) || (board[ycoord][xcoord] == 8) || (board[ycoord][xcoord] == 9) )
	{
		yes= 1;
	}
	return yes;
}

int contains_black(int ycoord, int xcoord) // returns 1 if a black piece is present in the queried locale, otw returns 0
{

	if ((board[ycoord][xcoord] == 10) || (board[ycoord][xcoord] == 11) || (board[ycoord][xcoord] == 12) || 
		(board[ycoord][xcoord] == 13) || (board[ycoord][xcoord] == 14) || (board[ycoord][xcoord] == 15) || 
		(board[ycoord][xcoord] == 16) || (board[ycoord][xcoord] == 17) || (board[ycoord][xcoord] == 18) )
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int is_legal(int ycoord0, int xcoord0, int ycoord1, int xcoord1) //checks to see if queried move is legal
{
	int piece_type;
	int i;
	int is_legal, inbtw_x, inbtw_y;
	is_legal=0;
	piece_type= board[ycoord0][xcoord0]; // determining piece type
	printf("moving piece type ... \n");
	printf("%d ",piece_type);
	printf("fuck... \n");		
	if (piece_type == 0)
	{
		is_legal= 0; //players cannot move empty space
		goto legal_end;
	}
	if ((xcoord0==xcoord1) && (ycoord0==ycoord1))
	{
		is_legal= 0; //players cannot move empty space
		goto legal_end;
	}
	if ((ycoord1 > 7) || (ycoord1 < 0) || (xcoord1 >7) || (xcoord1<0)) // check if out of bounds move
	{
		is_legal=0;	//out of bounds moves are forbidden
		goto legal_end;
	}	
	switch (piece_type) {
		case 1: // white pawn legal check
		{

			if (((ycoord0 == 6) && (ycoord1 == 4)) && (xcoord0==xcoord1) && (contains_white(ycoord1, xcoord1)==0)) //opening move forward for white pawn
			{			
				is_legal=1; 
			}
			else if ((ycoord1 > 7) || (ycoord1 < 0) || (xcoord1 >7) || (xcoord1<0)) // check if out of bounds move
			{
				is_legal=0;	
			}
			else if ((ycoord1 == (ycoord0-1))&& (contains_white(ycoord1, xcoord1)==0)&&(xcoord0==xcoord1)&&
				(contains_black(xcoord1, ycoord1)==0)) // moving one square forward, into empty space
			{
				is_legal=1;
			}
			else if ((ycoord1 == (ycoord0-1)) && ( (xcoord1 == (xcoord0-1)) || (xcoord1 == (xcoord0+1 )) ) && (contains_black(xcoord1, ycoord1) == 1))
			{ 
				//moving diagonally to take a piece
				is_legal=1;	
			}
			for (i=1; i<10; i++) 
			{
				if (board[ycoord1][xcoord1] == i){
					is_legal=0; // cannot move into a space occupied by a current player peice
				}
			}
		}
		case 2: { //white rook legal check
			for (i=1; i<abs(ycoord1-ycoord0); i++) {
				if ((ycoord1<ycoord0) && (board[ycoord0-i][xcoord0]!=0)) {
					is_legal=0;
					printf("piece inbetween y - \n");
					goto legal_end; 
				}
				if ((ycoord1>ycoord0) && (board[ycoord0+i][xcoord0]!=0)) {
					is_legal=0;
					printf("piece inbetween y + \n");
					goto legal_end; 
				}
			}
			for (i=1; i<abs(xcoord1-xcoord0); i++) {
				if ((xcoord1<xcoord0) && (board[ycoord0][xcoord0-i]!=0)) {
					is_legal=0;
					printf("piece inbetween x - \n");
					goto legal_end; 
				}
				if ((xcoord1<xcoord0) && (board[ycoord0][xcoord0-i]!=0)) {
					is_legal=0;
					printf("piece inbetween x + \n");
					goto legal_end; 
				}								
			}
			for (i=1; i<10; i++) 
			{
				if (board[ycoord1][xcoord1] == i){
					is_legal=0; // cannot move into a space occupied by a current player peice
					printf("friendly fire!!! \n");
					goto legal_end;
				}
			}
			if (((ycoord1==ycoord0) && (xcoord1!=xcoord0)) || ((ycoord1!=ycoord0)&&(xcoord1==xcoord0)))
			{
				is_legal=1;	
			}
	
		}		
			
		case 3: // white horse legal check
		{
			for (i=1; i<10; i++) 
			{
				if (board[ycoord1][xcoord1] == i){
					is_legal=0; // cannot move into a space occupied by a current player peice
					printf("friendly fire!!! \n");
					goto legal_end;
				}
			}		
			if ((abs(ycoord1 - ycoord0) ==2) && (abs(xcoord1 - xcoord0) ==1))
			{
				is_legal=1;	
			}
			if ((ycoord1 > 7) || (ycoord1 < 0) || (xcoord1 >7) || (xcoord1<0)) { // check if out of bounds move 
				is_legal=0;	
				goto legal_end;
			}
			for (i=1; i<10; i++) 
			{
				if (board[ycoord1][xcoord1] == i){
					is_legal=0; // cannot move into a space occupied by a current player peice
					goto legal_end;
				}
			}
		}
			
		case 4: //white bishop legal check
		{		
			printf("the bishop can suck my balls!\n");
			for (i=1; i<10; i++) 
			{
				if (board[ycoord1][xcoord1] == i){
					is_legal=0; // cannot move into a space occupied by a current player peice
					printf("friendly fire!!! \n");
					goto legal_end;
				}
			}				
			for (i=1; i<abs(ycoord1-ycoord0); i++) {
				//up and to the right sweep
				if (((ycoord1<ycoord0) && (xcoord1>xcoord0)) && (board[ycoord0-i][xcoord0+i]!=0)) {
					is_legal=0;
					printf("piece inbetween upper right - \n");
					goto legal_end; 
				}
				//up and to the left
				if (((ycoord1<ycoord0) && (xcoord1<xcoord0)) && (board[ycoord0-i][xcoord0-i]!=0)) {
					is_legal=0;
					printf("piece inbetween upper left - \n");
					goto legal_end; 
				}
				//down and to the left
				if (((ycoord1>ycoord0) && (xcoord1<xcoord0)) && (board[ycoord0+i][xcoord0-i]!=0)) {
					is_legal=0;
					printf("piece inbetween lower left - \n");
					goto legal_end; 
				}
				if (((ycoord1>ycoord0) && (xcoord1>xcoord0)) && (board[ycoord0+i][xcoord0+i]!=0)) {
					is_legal=0;
					printf("piece inbetween lower right - \n");
					goto legal_end; 
				}							
			}
			if ((ycoord1 != ycoord0) && (xcoord1 != xcoord0) && (abs(ycoord1-ycoord0)==abs(xcoord1-xcoord0)))
			{
				is_legal=1;	
			}
				
		}
		case 5: //white queen legal check
		{
			for (i=1; i<10; i++) 
			{
				if (board[ycoord1][xcoord1] == i){
					is_legal=0; // cannot move into a space occupied by a current player peice
					printf("friendly fire!!! \n");
					goto legal_end;
				}
			}			
			for (i=1; i<abs(ycoord1-ycoord0); i++) {
				//up and to the right sweep
				if (((ycoord1<ycoord0) && (xcoord1>xcoord0)) && (board[ycoord0-i][xcoord0+i]!=0)) {
					is_legal=0;
					printf("piece inbetween upper right - \n");
					goto legal_end; 
				}
				//up and to the left
				if (((ycoord1<ycoord0) && (xcoord1<xcoord0)) && (board[ycoord0-i][xcoord0-i]!=0)) {
					is_legal=0;
					printf("piece inbetween upper left - \n");
					goto legal_end; 
				}
				//down and to the left
				if (((ycoord1>ycoord0) && (xcoord1<xcoord0)) && (board[ycoord0+i][xcoord0-i]!=0)) {
					is_legal=0;
					printf("piece inbetween lower left - \n");
					goto legal_end; 
				}
				if (((ycoord1>ycoord0) && (xcoord1>xcoord0)) && (board[ycoord0+i][xcoord0+i]!=0)) {
					is_legal=0;
					printf("piece inbetween lower right - \n");
					goto legal_end; 
				}							
			}
			for (i=1; i<abs(ycoord1-ycoord0); i++) {
				if ((ycoord1<ycoord0) && (board[ycoord0-i][xcoord0]!=0)) {
					is_legal=0;
					printf("piece inbetween y - \n");
					goto legal_end; 
				}
				if ((ycoord1>ycoord0) && (board[ycoord0+i][xcoord0]!=0)) {
					is_legal=0;
					printf("piece inbetween y + \n");
					goto legal_end; 
				}
			}
			for (i=1; i<abs(xcoord1-xcoord0); i++) {
				if ((xcoord1<xcoord0) && (board[ycoord0][xcoord0-i]!=0)) {
					is_legal=0;
					printf("piece inbetween x - \n");
					goto legal_end; 
				}
				if ((xcoord1<xcoord0) && (board[ycoord0][xcoord0-i]!=0)) {
					is_legal=0;
					printf("piece inbetween x + \n");
					goto legal_end; 
				}								
			}
			if ((ycoord1 != ycoord0) && (xcoord1 != xcoord0) && (abs(ycoord1-ycoord0)==abs(xcoord1-xcoord0)))
			{
				is_legal=1;	
			}
			if (((ycoord1==ycoord0) && (xcoord1!=xcoord0)) || ((ycoord1!=ycoord0)&&(xcoord1==xcoord0)))
			{
				is_legal=1;	
			}
			
		}
		
	} // end bracket for parent switch case 
legal_end: return is_legal; 	
}

void move(int ycoord0, int xcoord0, int ycoord1, int xcoord1) //moves a piece on the board
{
	if (is_legal(ycoord0, xcoord0, ycoord1, xcoord1)==1) //checking if the move is legal
	{
		board[ycoord1][xcoord1] = board[ycoord0][xcoord0];	//reassigning values
		board[ycoord0][xcoord0] = 0; //setting original pos empty
	}
	else 
	{
		printf("illegal move suggested \n");
	}
}



int main()
{
   int i,j;
   // printf() displays the string inside quotation
   board[6][3]=0;
   board[4][5]=1;
   printf("Hello, World!\n");
   printf("init board status:\n");
   print_board();
   printf("moving \n");
   move(7,2 ,3, 6 );
   print_board();
}

