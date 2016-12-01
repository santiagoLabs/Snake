// Carlos Santiago Giraldo Pedroza
#include<iostream>     
#include<fstream>                    //include libraries     
#include<string>       
#include<cstdlib>    


#include<windows.h>    
#include<conio.h>                    //include file headers      
#include<stdlib.h>
#include<time.h>


using namespace std;


#define W            119
#define A            97
#define S            115             // Constants
#define D            100
#define PAUSE        112
#define ESC          27

#define UP 72
#define DOWN 80
#define RIGHT 77
#define LEFT 75
#define ENTER 13

HANDLE a = GetStdHandle(STD_OUTPUT_HANDLE);


int body[100][2];     // body
int n = 1;            // Used to increase snake length
int length = 7;       // Length of the body when the game starts
int x = 5;            // Coordinate x of the snake when the game starts
int y = 12;           // Coordinate y of the snake when the game starts      
int dir = 3;          // The direction of the snake when the game starts
int xc = 0;			  // Food cooridinate x
int yc = 0;			  // Food cooridinate y
int speed = 0;        // Speed of the snake
int score = 0;        // Score
//int h = 1;				
int choice= 1;        // Used to save the choice you made
int s_diff;           // Used to save witch difficult you chose
char key;             // Used to save the keyboard input
fstream hs;           // Used for the file
bool pause = false;


void SetWindow(int Width, int Height){          // Set the width and height of the game window
    _COORD coord;
    coord.X = Width;
    coord.Y = Height;

    _SMALL_RECT Rect;
    Rect.Top = 0;
    Rect.Left = 0;
    Rect.Bottom = Height - 1;
    Rect.Right = Width - 1;

    HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);      // Get Handle
    SetConsoleScreenBufferSize(Handle, coord);            // Set Buffer Size
    SetConsoleWindowInfo(Handle, TRUE, &Rect);            // Set Window Size
}


void gotoxy(int x, int y){                     // Move the cursor around the window
        HANDLE hCon;
        COORD dwPos;

        dwPos.X = x;
        dwPos.Y = y;
        hCon = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleCursorPosition(hCon,dwPos);
}

void clrscr(int x1, int y1, int x2, int y2){    // Used to clear the screen
	int i,j;

	for(i= y1; i<y2; i++){
		for(j = x1; j<x2; j++){
			gotoxy(i,j);
			cout<<" ";
		}
	}
}

void uppercase(string& name){                // Uppercase gamer's name
	int i;

	for(i=0; i<name.length(); i++){
		name[i] = toupper(name[i]);
	}
}

void logo(){  //print the game logo and menu
	SetConsoleTextAttribute(a,FOREGROUND_GREEN | FOREGROUND_BLUE| FOREGROUND_INTENSITY);  //used to change color letter
	
	 gotoxy(14,0); 
	 cout<<" ____________  "<<endl; gotoxy(14,1);
	 cout<<"|            | "<<endl; gotoxy(14,2);
	 cout<<"|    ________| "<<endl; gotoxy(14,3);
	 cout<<"|   |          "<<endl; gotoxy(14,4);
	 cout<<"|   |________  "<<endl; gotoxy(14,5);           
	 cout<<"|            |"<<endl;	gotoxy(14,6);
	 cout<<"|________    | "<<endl; gotoxy(14,7);
     cout<<"         |   |"<<endl;  gotoxy(14,8);
	 cout<<" ________|   | "<<endl; gotoxy(14,9);
	 cout<<"|            | "<<endl; gotoxy(14,10);
	 cout<<"|____________| "<<endl; gotoxy(14,11);
	
	 gotoxy(29,0);
	 SetConsoleTextAttribute(a,FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);   //used to change color letter
	 cout<<" __      ___"<<endl;gotoxy(29,1);
     cout<<"|  \\    |   |"<<endl;gotoxy(29,2);
     cout<<"|   \\   |   |"<<endl;gotoxy(29,3);
     cout<<"|    \\  |   |"<<endl;gotoxy(29,4);
     cout<<"|     \\ |   |"<<endl;gotoxy(29,5);
     cout<<"|      \\|   |"<<endl;gotoxy(29,6);
     cout<<"|   |\\      |"<<endl;gotoxy(29,7);
     cout<<"|   | \\     |"<<endl;gotoxy(29,8);
     cout<<"|   |  \\    |"<<endl;gotoxy(29,9);
     cout<<"|   |   \\   |"<<endl;gotoxy(29,10);
     cout<<"|___|    \\__|"<<endl;gotoxy(29,11);

	 gotoxy(43,0);
	  SetConsoleTextAttribute(a,  FOREGROUND_BLUE | FOREGROUND_INTENSITY);  //used to change color letter
	 cout<<" ____________ "<<endl;gotoxy(43,1);
     cout<<"|            |"<<endl;gotoxy(43,2);
     cout<<"|    ____    |"<<endl;gotoxy(43,3);
     cout<<"|   |    |   |"<<endl;gotoxy(43,4);
     cout<<"|   |____|   |"<<endl;gotoxy(43,5);
     cout<<"|            |"<<endl;gotoxy(43,6);
     cout<<"|            |"<<endl;gotoxy(43,7);
     cout<<"|    ____    |"<<endl;gotoxy(43,8);
     cout<<"|   |    |   |"<<endl;gotoxy(43,9);
     cout<<"|   |    |   |"<<endl;gotoxy(43,10);
     cout<<"|___|    |___|"<<endl;gotoxy(43,11);

	 gotoxy(58,0);
	 SetConsoleTextAttribute(a, FOREGROUND_RED | FOREGROUND_INTENSITY);  //used to change color letter
	 cout<<" ___     ____ "<<endl; gotoxy(58,1);
     cout<<"|   |   /   /"<<endl; gotoxy(58,2); 
     cout<<"|   |  /   / "<<endl; gotoxy(58,3);  
     cout<<"|   | /   /  "<<endl; gotoxy(58,4); 
     cout<<"|   |/   /	 "<<endl; gotoxy(58,5); 
     cout<<"|       /    "<<endl; gotoxy(58,6); 
     cout<<"|       \\    "<<endl; gotoxy(58,7); 
     cout<<"|   |\\   \\   "<<endl; gotoxy(58,8); 
     cout<<"|   | \\   \\  "<<endl; gotoxy(58,9); 
     cout<<"|   |  \\   \\ "<<endl; gotoxy(58,10); 
     cout<<"|___|   \\___\\ "<<endl; gotoxy(58,11);
    
	 gotoxy(72,0);
	SetConsoleTextAttribute (a, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);  //used to change color letter
	 cout<<" ____________"<<endl; gotoxy(72,1);
     cout<<"|            |"<<endl; gotoxy(72,2);
     cout<<"|    ________|"<<endl; gotoxy(72,3);
     cout<<"|   |	       "<<endl; gotoxy(72,4);  
     cout<<"|   |______      "<<endl; gotoxy(72,5);   
     cout<<"|          |    "<<endl; gotoxy(72,6);
     cout<<"|    ______|    "<<endl; gotoxy(72,7);
     cout<<"|   |        "<<endl; gotoxy(72,8);
     cout<<"|   |________"<<endl; gotoxy(72,9);
     cout<<"|            |"<<endl; gotoxy(72,10);
     cout<<"|____________|"<<endl; gotoxy(72,11);
     
	 SetConsoleTextAttribute(a,FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);  //used to change color letter
	 for(int i=7; i<13; i++){
		gotoxy(11,i);
		cout<<(char) 186;
		gotoxy(88,i);
		cout<<(char) 186;
	 }
	 for(int i=11; i<14; i++){
		gotoxy(i,6);
		cout<<(char) 205;
	 }
	 for(int i = 11; i<89; i++){
		gotoxy(i,13);
		cout<<(char) 205;
	 }
	 for(int i=84; i<89; i++){
		gotoxy(i,6);
		cout<<(char) 205;
	 }
	 gotoxy(11,6);
	 cout<<(char) 201;
	 gotoxy(88,6);
	 cout<<(char) 187;
	 gotoxy(11,13);
	 cout<<(char) 200;
	 gotoxy(88,13);
	 cout<<(char) 188;

	SetConsoleTextAttribute (a, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
	gotoxy(43,15);
	cout<<" _       _      "<<endl; gotoxy(43,16);
    cout<<"|_| |   |_| \\ /    "<<endl; gotoxy(43,17);
    cout<<"|   |__ | |  |    "<<endl; gotoxy(43,18);
    
    SetConsoleTextAttribute(a,FOREGROUND_RED | FOREGROUND_INTENSITY);
	gotoxy(44,19);
	cout<<" _        ___ "<<endl; gotoxy(44,20);
    cout<<"|_  \\/  |  |  "<<endl; gotoxy(44,21);
    cout<<"|_  /\\  |  |  "<<endl; gotoxy(44,22);

	gotoxy(72,28);
	cout<<"DEVELOPER: SANTIAGO GIRALDO";
}

int menu(){                                            
	if(_kbhit()){                                      
			key = _getch();                             
			switch(key){                                
				case UP:                               
					if(choice == 2)	choice = 1;
			        break;
				case DOWN:
					if(choice == 1) choice = 2;
					break;
			}
	}
	
	switch(choice){
		case 1:
			gotoxy(41,20);
			cout<<" ";
			gotoxy(41,16);
			cout<<(char) 16;
			return(1);
	        break;

		case 2:
		     gotoxy(41,16);
			 cout<<" ";
			 gotoxy(41,20);
			 cout<<(char) 16;
			 return(2);
			 break;
	}


}

int menu_choice(){                 
	int choice_1;
	choice_1 = menu();

	if(choice_1 == 1 ){
		if(_kbhit())
			key = _getch();
			switch(key){
				case ENTER:
					return (1);
			}
	    
	}
	
	if(choice_1 == 2 ){
		if(_kbhit())
			key = _getch();
			switch(key){
				case ENTER:
					system("cls");
					exit(0);
			}
	    
	}
}

int difficult(){      // Print the various difficulties and move the select cursor to choose the difficult
	gotoxy(44,6);
	cout<<"SELECT DIFFICULT: (PRESS TWICE)";
	gotoxy(50,10);
	cout<<"NOOB";
	gotoxy(50,12);
	cout<<"EASY";
	gotoxy(49,14);
	cout<<"NORMAL";
	gotoxy(49,16);
	cout<<"EXPERT";
	gotoxy(46,18);
	cout<<"MASTER RACE! ";
	
	if(_kbhit()){             
			key = _getch();
			switch(key){
				case UP:
					if(choice == 2){ 
							gotoxy(48,12);
							cout<<" ";
							gotoxy(48,10);
							cout<<(char) 16;
							choice = 1;
					}
					if(choice == 3){
							gotoxy(48,10);
							cout<<" ";
							gotoxy(47,14);
							cout<<" ";
							gotoxy(48,12);
							cout<<(char) 30;
							choice = 2;
					}
					if(choice == 4){
							gotoxy(48,12);
							cout<<" ";
							gotoxy(47,16);
							cout<<" ";
							gotoxy(47,14);
							cout<<(char) 30;
							choice = 3;
					}
					if(choice == 5){
							gotoxy(47,14);
							cout<<" ";
							gotoxy(44,18);
							cout<<" ";
							gotoxy(47,16);
							cout<<(char) 30;
							choice = 4;
					}
					break;
				case DOWN:
					switch(choice){
						case 1:
							gotoxy(48,10);
							cout<<" ";
							gotoxy(47,14);
							cout<<" ";
							gotoxy(48,12);
							cout<<(char) 30;
							choice = 2;
							break;
						case 2:
							gotoxy(48,12);
							cout<<" ";
							gotoxy(47,16);
							cout<<" ";
							gotoxy(47,14);
							cout<<(char) 30;
							choice = 3;
							break;
						case 3:
							gotoxy(47,14);
							cout<<" ";
							gotoxy(44,18);
							cout<<" ";
							gotoxy(47,16);
							cout<<(char) 30;
							choice = 4;
							break;
						case 4:
							gotoxy(47,16);
							cout<<" ";
							gotoxy(44,18);
							cout<<(char) 30;
							choice = 5;
							break ;
 					}
					break;
			}
	}
	return choice;
}

bool select_difficult(){             // Select the difficult of the game 
	int choice = difficult();

	switch(choice){
		case 1:
		   if(_kbhit())
		   _getch();
		   key = _getch();
		   
		   switch(key){
		   		case ENTER:
					s_diff = 1;
		    		return true;
		    		break;
				
			
		   }
		   break;
		case 2:
			if(_kbhit())
				_getch();
			key = _getch();
			switch(key){
				case ENTER:
					s_diff = 2;
		    		return true;
					break;
		    }
			break;
		case  3:
			if(_kbhit())
				_getch();
			key = _getch();
			switch(key){
				case ENTER:
					s_diff = 3;
		    		return true;
					break;
		    }
			break;
		case 4:
			if(_kbhit())
				_getch();
			key = _getch();
			switch(key){
				case ENTER:
					s_diff = 4;
		    		return true;
					break;
		    }
			break;
		case 5:
			if(_kbhit())
				_getch();
			key = _getch();
			switch(key){
				case ENTER:
					s_diff = 5;
		    		return true;
					break;
		    }
			break;
		
	}
	return false;
}

void f_speed(){        // Set the speed of the game depending of the choice of the difficult
	switch(s_diff){
		case 1:
			speed = 100;
			break;
		case 2:
			speed= 60;
			break;
		case 3:
			speed = 50;
			break;
		case 4:
			speed = 25;
			break;
		case 5:
			speed = 17;
			break;
	}
}

void tutorial(){         //print game tutorial
	gotoxy(43,10);
	cout<<"MOVE: W A S D";
	gotoxy(45,15);
	cout<<"PAUSE: P";
}

void moveset(){          // It allows the snake to move if you type the keys to move the snake ( W A S D )
          if(_kbhit()){
                         key = _getch();
                         switch(key){
                                case W:
                                        if(dir != 2) dir = 1; 
										
                                        break;
                                case S:
                                        if(dir != 1) dir = 2;
										
                                        break;
                                case D:
                                        if(dir != 4) dir = 3;
											
                                        break;
                                case A:
                                        if(dir != 3) dir = 4;
										
                                        break;
                                case PAUSE:
                                        if(!pause){
                                                gotoxy(60,24); cout<<"PAUSE";
                                                gotoxy(65,24); cout<<" ";
                                                _getch();
                                                for(int i=60; i<66; i++){
                                                        gotoxy(i,24); cout<<" ";
                                                }
                                        }
                                        break;
                        }
        }
		switch(dir){
			case 1: 
				y--;
				break;
			case 2:
				y++;
				break;
			case 3:
				x++;
				break;
			case 4: 
				x--;
				break;
		}
}

void draw_game_field(){      //print the game field
        
	    SetConsoleTextAttribute(a,FOREGROUND_RED | FOREGROUND_INTENSITY);
        //horizontal lines
        for(int i=0; i<66; i++){
        
                gotoxy(i,0); cout<<(char)205 ;
                gotoxy(i,23); cout<<(char) 205 ;
                gotoxy(i,29); cout<<(char) 205;

        }
        //vertical lines
        for(int i = 0; i<29; i++){
                gotoxy(0,i); cout<<(char) 186;
                gotoxy(66,i); cout<<(char) 186;
                gotoxy(0,i); cout<<(char) 186;
                gotoxy(98,i); cout<<(char) 186;
        }
        //horizontal lines second square
        for(int i=66; i<98; i++){
                gotoxy(i,0); cout<<(char) 205;
                gotoxy(i,29); cout<<(char) 205;
        }
        //edges
        gotoxy(0,0); cout<<(char) 201;
        gotoxy(98,0); cout<<(char) 187;
        gotoxy(98,29) ; cout<<(char) 188;
        //gotoxy(0,23); cout<<(char) 200;
        gotoxy(66,0); cout<<(char) 187;
        //gotoxy(66,23); cout<<(char) 188;
        gotoxy(0,29); cout<<(char)200;
        gotoxy(66,29); cout<<(char) 188;
        
}

void read_highscore(){        //print the highscores in the game field

	 int x = 68;
	 int y = 4;
	 int i = 1;
	 string line,score_line;

	 gotoxy(78,1);
	 cout<<"HIGHSCORES";
	 hs.open("record.txt", ios::in);
	 while(!hs.eof()){
		 
		 gotoxy(x,y);
	     getline(hs,line);
		 getline(hs,score_line);
		 cout<<i<<")"<<" "<<line;
		 gotoxy(93,y);
		 cout<<score_line<<endl;
		 y += 2;
		 i++;
	 }
     hs.close();
	 for(i=68; i<97; i++){
		gotoxy(i,20);
		cout<<" ";
	 }
	 
}

void write_highscore(){        // Print the highscores into a file and do all the operations to save the highscore in the right way
	
	int cn,c;
	int i,points[10];
	string data[20];
	string name;
	string points_2[10];
	
    hs.open("record.txt", ios::in);
	i=0;
	while(!hs.eof()){
		getline(hs,data[i]);
		getline(hs,points_2[i]);
		points[i] = atoi(points_2[i].c_str());
		i++;
    }
	hs.close();
	if(score >= points[7]){
		do{
		
			for(cn = 40; cn<99; cn++){
				gotoxy(cn,8);
				cout<<" ";
			}
			gotoxy(40,6);
			cout<<"INSERT YOUR NAME!(MAX 10)";
				gotoxy(40,8);
				getline(cin,name);
				uppercase(name);
		}
		while(name.length() >= 15);
	
		if(score >= points[0]){
			
			c=6;
			for(i=7; i>=1; i--){ 
				points[i] = points[c];
				data[i] = data[c];
				c--;
			}
			points[0] = score;
			data[0] = name;
		
		} 
		if(score >= points[1] && score < points[0]){
			
			c=6;
			for(i=7; i>=2; i--){ 
				points[i] = points[c];
				data[i] = data[c];
				c--;
		    }
			points[1] = score;
			data[1] = name;
		} 
		if(score >= points[2] && score < points[1]){
			
			c=6;
			for(i=7; i>=3; i--){ 
				points[i] = points[c];
				data[i] = data[c];
				c--;
			}
			points[2] = score;
			data[2] = name;
		} 
		if(score >= points[3] && score < points[2]){
			
			c=6;
			for(i=7; i>=4; i--){ 
				points[i] = points[c];
				data[i] = data[c];
				c--;
			}
			points[3] = score;
			data[3] = name;
		} 
		if(score >= points[4] && score < points[3]){
			
			c=6;
			for(i=7; i>=5; i--){ 
				points[i] = points[c];
				data[i] = data[c];
			    c--;
			}
			points[4] = score;
			data[4] = name;
		} 
		if(score >= points[5] && score < points[4]){
			
			c=6;
			for(i=7; i>=6; i--){ 
				points[i] = points[c];
				data[i] = data[c];
				c--;
			}
			points[5] = score;
			data[5] = name;
		} 
		if(score >= points[6] && score < points[5]){
			
			c=6;
			for(i=7; i>=7; i--){ 
				points[i] = points[c];
				data[i] = data[c];
				c--;
			}
			points[6] = score;
			data[6] = name;
		} 
		if(score >= points[7] && score < points[6]){
			points[7] = score;
			data[7] = name;
		} 
			
		hs.open("record.txt", ios::out);
		for(i=0; i<8; i++){
			hs<< data[i]<<endl;
			hs<< points[i]<<endl;
		}
		hs.close();
	}			
}

void initialization(){             // Initialization of the game

        draw_game_field();

        srand((unsigned)time(NULL));
        xc = (rand() %62) +4;
        yc = (rand() %19) +4;
        gotoxy(xc,yc);
        cout<<(char) 184;
}

void erase_body(){              // Erases snake body

        gotoxy(body[n][0], body[n][1]) ;
        cout<<" ";

}
 
void save_position(){          // Saves snake coordinates
        body[n][0] = x;
        body[n][1] = y;
        n++;
        if(n == length) n=1;
}

void draw_body(){            // Draws snake body


   for(int i =1 ; i<length; i++){
	   SetConsoleTextAttribute(a, FOREGROUND_GREEN | FOREGROUND_BLUE);
        gotoxy(body[i][0], body[i][1]) ;
        cout<<(char) 254;
        
   }
  
}

void food(){              // Prints snake food in a random postion

        if(x == xc && y == yc){
                srand((unsigned)time(NULL));
                xc = (rand()%62)+4 ;
                yc = (rand()%19)+4 ;

                length++;
                score+=10;
                gotoxy(xc,yc);
                cout<<(char) 184;
             
        }
        
}

bool game_over(){          // If you collide with the game field or with yourself the game over
        
		if(y == 0 || y == 23 || x == 0 || x== 66) return(false);
        for(int j = length-1; j>0; j--){
                if(body[j][0] == x && body[j][1] == y)
                        return(false);
        }

        return(true);
}

void print_score(){        // Prints the score in the game field
        gotoxy(1,24);
        cout<<"SCORE:"<<score;
}

int main(){
   
	do{
		logo();
		menu();
		menu_choice();
	}
	while(menu_choice() != 1);
	clrscr(0,0,60,200);
	gotoxy(48,10);
	cout<<(char) 16;
	do{
		
		difficult();
		select_difficult();
	}
	while(select_difficult() == false); 
	clrscr(0,0,60,200);
	tutorial();
	Sleep(4000);
	clrscr(0,0,60,200);
	initialization();
	read_highscore();
	f_speed();
    do{
				
				    erase_body();
					save_position();
					draw_body();
					food();
					print_score();
				    moveset();
					Sleep(speed);
					if(!game_over()){
							clrscr(0,90,60,200);
							gotoxy(45,4);
							cout<<"YOU LOSE!";
							write_highscore();
							
						
					}
			
		
	}
	while(key != ESC && game_over());
    _getch();
	return(0);
}

