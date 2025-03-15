#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#include <unistd.h>
#include <windows.h>
#include <time.h>
					
void SetColorAndBackground(int ForgC, int BackC) // Background color |||  cor de letra  | cor de background
{
     WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);;
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
     return;
}

void gotoxy(int x, int y)	// Gotoxy(x, y)
{
  static HANDLE h = NULL;  
  if(!h)
    h = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD c = { x, y };  
  SetConsoleCursorPosition(h,c);
}

main(){
		
	int a, b, c, i, x_tail[599], y_tail[599], score, size, direction, x_food, y_food, food, end; 
	setlocale(LC_ALL, "portuguese");
	
	end = 0;
	food = 1;
	direction = 0;
	score = 0;
	a = -1;   //Size of snake 
	b = 0;	  //food place
	//**Size and original position of the snake (int a) บบ 
	for (i = 12; i >=10; i--){
		a++;
		x_tail[a] = i;
		y_tail[a] = 12;
	}
	//**Size and original position of the snake บบ	
	gotoxy(32, 12);
	printf("The Snake Game");
	gotoxy(32, 15);
	printf("ENTER To Start");
	getchar();
	system("cls");
	sleep(2);
	//THE GAME STARTS +++
	for ( ; ; ){
		
		size = score +2;
		
		//***************BOARD******************************
		SetColorAndBackground(7, 0);
		gotoxy(2, 5);
		printf("________________________________________");
		for ( i = 6 ; i<= 20 ; i++){
			gotoxy(2, i);
			printf("|");
		}	
		for ( i = 6; i<= 20; i++){
			gotoxy(42, i);
			printf("|");
		}
		gotoxy(2, 20);
		printf("________________________________________");
		
		
		//**********Food place**************** int c;
		
		if ( food == 1 ){
			c = 0;
			for ( ;  ; ){
				c++;
				srand(time(NULL));
				x_food = (rand() % 39) + 3;
				srand(time(NULL));
				y_food = ( rand() % 13) + 6 ;
				for ( i = size ; i >= 0 ; i--){
					
					if ( x_food == x_tail[i] || y_food ==  y_tail[i]  )
						b = 1;						 
				}
				
				if ( b != 1 || c == 3)
					break;
			}
			
		}
			
		//****************Printf Food****************************
		gotoxy(x_food , y_food);
		SetColorAndBackground(12, 0);
		printf("+");
		if ( food == 1 ) // 1 = eated , 0 = existing
			food = 0;
		//*****Eating the food && Updating food, size and score****
		if ( x_tail[0] == x_food && y_tail[0] == y_food){
			food = 1;
			score = score +1;
		}
		size = score + 2;		
		//***************Printf Snake********************************
		for ( i = 0 ; i <= size ; i++ ){
			gotoxy(x_tail[i], y_tail[i]);
			SetColorAndBackground(2, 0);
			printf("0");
		}
		//*************Updating the tail*********************
		for ( i = size ; i > 0 ; i--){
			x_tail[i] = x_tail[(i-1)];
			y_tail[i] = y_tail[(i-1)];
		}
		//**************Direction*Update***************************  (0x25 could be any other number)
		if (GetAsyncKeyState(VK_RIGHT) &0x25 && direction != 1)
			direction = 0;
		else if (GetAsyncKeyState(VK_LEFT) &0x25 && direction != 0)
				direction = 1;
		else if (GetAsyncKeyState(VK_UP) &0x25 && direction != 3 )
				direction = 2;
		else if (GetAsyncKeyState(VK_DOWN) &0x25 && direction != 2)
				direction = 3;
				
		if (direction == 0)
			x_tail[0]++;
		else if (direction == 1)
			x_tail[0]--;
		else if  ( direction == 2)
			y_tail[0]--;
		else if ( direction == 3)
			y_tail[0]++;
						 
		//**************Dying 8^) *************************** int c;
		
		if ( x_tail[0] < 3 || x_tail[0] > 41 || y_tail[0] < 6 || y_tail[0] > 20 ){
			end = 2;
			break;
		}
			
		c = 0;
		for ( i = size ; i >= 1; i--){
			if ( x_tail[i] == x_tail[0] && y_tail[i] == y_tail[0] )
				c = 1;	
		}
		if ( c == 1){
			end = 2;
			break;
		}
							
		
		if ( size == 599){
			end = 1;
			break;
		}

	
		usleep(65000); //65 milliseconds -> 1000 = 1 millisecond ->1 = 1 microsecond
		system("cls");
	
	}  // GAME END
	
	
	SetColorAndBackground(7, 0);
	system("cls");
	if ( end == 2){
		
		gotoxy(32, 12);
		printf("You Lost :(");
		gotoxy(32, 13);
		printf("Score : %d", score);
	}
	else {
		
		gotoxy(32, 12);
		printf("You Won : )");
		gotoxy(32, 13);
		printf("score : %d", score);
	}
	fflush(stdin);
	getchar();
}
