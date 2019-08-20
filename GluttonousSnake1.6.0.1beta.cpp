#include<ctime>
#include<cmath>
#include<cstdlib>
#include<cstring>
#include<conio.h>
#include<iostream>
#include<windows.h>

using namespace std;

const string version = "beta1.6.0.1";
const string upd = "2019/08/12";

string Map[22];
int n;
int flag, flag1;
int speed, delay, con;
int applex, appley, ti;
int input, length, direction, newinp;
bool wall  = true;
bool ghost = false;

struct Snake {//snakeQueue
    int x;
    int y;
    int dir;
}snake[484];

void gotoxy(int x, int y) {//outputFunc
    COORD pos = {x,y};
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOut, pos);
}

void output(int x, int y, char c) {//gotoxyOutput
	gotoxy(y, x+2);
	putchar(c);
}

void clemap(void) {//clearTheMap
    Map[ 0] = "######################";
    Map[ 1] = "#                    #";
    Map[ 2] = "#                    #";
    Map[ 3] = "#                    #";
    Map[ 4] = "#                    #";
    Map[ 5] = "#                    #";
    Map[ 6] = "#                    #";
    Map[ 7] = "#                    #";
    Map[ 8] = "#                    #";
    Map[ 9] = "#                    #";
    Map[10] = "#                    #";
    Map[11] = "#                    #";
    Map[12] = "#                    #";
    Map[13] = "#                    #";
    Map[14] = "#                    #";
    Map[15] = "#                    #";
    Map[16] = "#                    #";
    Map[17] = "#                    #";
    Map[18] = "#                    #";
    Map[19] = "#                    #";
    Map[20] = "#                    #";
    Map[21] = "######################";
} 

void createmap(void) {//firstMapOutput 
	system("cls");
	printf("-GluttonousSnake-\nScore:%d\n", (length - 3) * 5);
	for(int i = 0; i < 22; ++i) {
		for(int j = 0; j < 22; ++j){
			putchar(Map[i][j]);
		}
		putchar('\n');
	}
}

void GCS(void) {//gameConditionSet
	memset(snake,0,sizeof(snake));
	srand(time(NULL));
	flag1 = false;
	ghost = false;
	wall = true;
	direction = 1;
	length = 3;
	speed = 60;
	delay = 9;
    clemap();
    ti = 0;
    snake[0].x   = 1;
    snake[1].x   = 1;
    snake[2].x   = 1;
    snake[0].y   = 3;
    snake[1].y   = 2;
    snake[2].y   = 1;
    snake[0].dir = 1;
    snake[1].dir = 1;
    snake[2].dir = 1;
    srand(time(NULL));
    applex = rand() % 20 + 1;
    appley = rand() % 20 + 1;
    while(applex <= 1 && appley <= 3){
        srand(time(NULL));
        applex = rand() % 20 + 1;
        appley = rand() % 20 + 1;
    }
    Map[applex][appley] = 'a';
    Map[snake[0].x][snake[0].y] = '@';
    for(int i = 1; i < 484; ++i) {
    	if(snake[i].x != 0 && snake[i].y != 0) {
    		Map[snake[i].x][snake[i].y] = '-';
		}
	}
	createmap();
    return;
}

int gameover(void) { // gameCondition
    if(Map[snake[0].x][snake[0].y] == '-' || Map[snake[0].x][snake[0].y] == '|' || Map[snake[0].x][snake[0].y] == '+' || snake[0].x == 0 || snake[0].x == 21 || snake[0].y == 0 || snake[0].y == 21) {
        system("cls");
        cout << "Game over!\nScore:" << (length - 3) * 5 << endl;
        cout << "Press space to keep playing or others to exit the game \n";
		while(!_kbhit()) {
        	Sleep(10);
		}
		char operation = _getch();
		if(operation == ' ') {
			return 2;
		}
        return 1;
    }
    return 0;
} 

int judge() { // 0 for exit, 1 for restart, 2 for continue
	int isGameOver = gameover();
    if(isGameOver == 1) {
       	return 0;
	}
	else if(isGameOver == 2) {
		return 1;
	}
	return 2;
}

void startGame() {
	//startPage
    system("cls");
    system("color 0f");
    string st = "-GluttonousSnake-\nBy KM_YoaMoa & HZSteven\n"+version+" Upd:"+upd+"\n-Press space to start the game-";
    for(int i = 0; i < st.length(); ++i){
        cout << st[i];
        Sleep(50);
    } 
    while(1) {
    	while(!_kbhit()) {
    		Sleep(10);
		}
		int startkey = _getch();
		if(startkey == 32) {
			break;
		}
	}
	return;
}

inline int startPlaying() {
	while(1) { //gameLoop
        //keybdEvent
        int END = 110 - speed;
        for(int i = 0; i < END; ++i) {
            if(_kbhit()) {
                newinp = _getch();
                flag1 = 1;
            }
            Sleep(delay);
        }
        
        if(flag1 == 1) { // ifAnyKeyDown
        
        	//newDirectionUpd
            if     ((newinp == 68 || newinp == 100) && direction != 3) {
            	direction = 1;
			}
            else if((newinp == 83 || newinp == 115) && direction != 4) {
            	direction = 2;
			}
            else if((newinp == 65 || newinp ==  97) && direction != 1) {
            	direction = 3;
			}
            else if((newinp == 87 || newinp == 119) && direction != 2) {
            	direction = 4;
			}
			else if(newinp == 32){
				//controlPageOutput
                con = 1;
				system("cls");
                printf("-Pause-\n");
                string c[5] = {"Speed:", "Delaytime:", "Wall:", "Ghost:", "Exit"};
                for(int i = 0; i < 5; ++i){
                    if(i == 0) {
                    	putchar('&');
					}
                    else {
                    	putchar(' ');
					}
					for(int j = 0; j < c[i].length(); ++j) {
						putchar(c[i][j]);
					}
                    if(i == 0) {
                    	printf("%d", speed);
					}
                    else if(i == 1) {
                    	printf("%d", delay);
					}
                    else if(i == 2) {
                        if(wall) {
                        	printf("true");
						}
                        else {
                        	printf("false");
						}
                    }else if(i == 3) {
                        if(ghost) {
                        	printf("true");
						}
                        else {
                        	printf("false");
						}
                    }
                    putchar('\n');
                }
                while(1) {
                    
                    while(!_kbhit()) {
                    	Sleep(10);
					} 
                    int in = _getch();
                    if(in == 119 && con > 1) {
                    	gotoxy(0, con);
                    	putchar(' ');
                    	--con;
                    	gotoxy(0, con);
                    	putchar('&');
                    	gotoxy(0, con);
					}
                    else if(in == 115 && con < 5) {
                    	gotoxy(0, con);
                    	putchar(' ');
                    	++con;
                    	gotoxy(0, con);
                    	putchar('&');
                    	gotoxy(0, con);
					}
                    else if(in == 97) {
                        if(con == 1 && speed > 10) {
                        	speed -= 5;
                        	gotoxy(7, con);
                        	printf("%d ", speed);
						}
                        else if(con == 2 && delay > 0) {
                        	--delay;
                        	gotoxy(11, con);
                        	printf("%d ", delay);
						}
                        else if(con == 3) {
                        	wall = !wall;
                        	gotoxy(6, con);
                        	if(wall) {
                        		printf("true ");
							}
							else {
								printf("false");
							}
						}
                        else if(con == 4) {
                        	ghost = !ghost;
                        	gotoxy(7, con);
                        	if(ghost) {
                        		printf("true ");
							}
							else {
								printf("false");
							}
						}
						gotoxy(0, con);
                    }
					else if(in == 100) {
                        if(con == 1 & speed < 100) {
                        	speed += 5;
                        	gotoxy(7, con);
                        	printf("%d ", speed);
						}
                        else if(con == 2 && delay < 15) {
                        	++delay;
                        	gotoxy(11, con);
                        	printf("%d ", delay);
						}
                        else if(con == 3) {
                        	wall = !wall;
                        	gotoxy(6, con);
                        	if(wall) {
                        		printf("true ");
							}
							else {
								printf("false");
							}
						}
                        else if(con == 4) {
                        	ghost = !ghost;
                        	gotoxy(7, con);
                        	if(ghost) {
                        		printf("true ");
							}
							else {
								printf("false");
							}
						}
						gotoxy(0, con);
                    }
					else if(in == 13) {
                        if(con == 5) {
                        	gotoxy(0, con);
                        	printf("Thanks for your support!\n");
                            Sleep(1000);
                            return false;
                        }
                    }
					else if(in == 32){
						break;
					}
                }
                createmap();
            }
        }
        
        //snakeUpd
        int LenMinusOne = length - 1;
        for(int i = LenMinusOne; i > 0; --i) {
            if(i == LenMinusOne && flag == 1) {
                snake[length].x   = snake[LenMinusOne].x;
                snake[length].y   = snake[LenMinusOne].y;
                snake[length].dir = snake[LenMinusOne].dir;
            }
            int IMinusOne = i - 1;
            snake[i].x   = snake[IMinusOne].x;
            snake[i].y   = snake[IMinusOne].y;
            snake[i].dir = snake[IMinusOne].dir;
        }
        if(flag == 1) {
        	++length;
		}
        if(direction == 1) {
            snake[0].dir = 1;
            ++snake[0].y;
        }
        else if(direction == 2){
            snake[0].dir = 2;
            ++snake[0].x; 
        }
        else if(direction == 3){
            snake[0].dir = 3;
            --snake[0].y;
        }
        else {
            snake[0].dir = 4;
            --snake[0].x;
        }
        if(wall == 0){
            if(direction == 1 && snake[0].y == 21) {
            	snake[0].y = 1;
			}
            else if(direction == 2 && snake[0].x == 21) {
            	snake[0].x = 1;
			}
            else if(direction == 3 && snake[0].y == 0) {
            	snake[0].y = 20;
			}
            else if(direction == 4 && snake[0].x == 0) {
            	snake[0].x = 20;
			}
        }
        
        int Choice = judge();
        if(Choice == 0) {
        	return false;
		}
		else if(Choice == 1) {
			return true;
		}
		
        if(snake[0].x == applex && snake[0].y == appley) {
            srand(time(NULL));
            applex = rand() % 20 + 1;
            appley = rand() % 20 + 1;
            flag = 1;
            while(Map[applex][appley] == '@' || Map[applex][appley] == '|' || Map[applex][appley] == '-' || Map[applex][appley] == '+') {
                applex = rand() % 20 + 1;
                appley = rand() % 20 + 1;
            }
        }
		else {
			flag = 0;
		}
        
        //newGameMapUpd
        for(int i = 0; i < 22; ++i){
        	for(int j = 0; j < 22; ++j){
        		if(Map[i][j] != ' ' && Map[i][j] != '#'){
        			gotoxy(j, i+2);
        			putchar(' ');
				}
			}
		}
		clemap();
        Map[applex][appley] = 'a';
        output(applex, appley, 'a');
        Map[snake[0].x][snake[0].y] = '@';
        output(snake[0].x, snake[0].y, '@');
        for(int i = 1; i < 484; ++i) {
            if(snake[i].x != 0 && snake[i].y != 0) {
            	int IMinusOne = i - 1;
                if(snake[IMinusOne].dir != snake[i].dir) {
                    if(snake[i + 1].dir != 0 && Map[snake[i].x][snake[i].y] != '+') {
                    	output(snake[i].x, snake[i].y,'+');
                    	Map[snake[i].x][snake[i].y] = '+';
					}
                    else if((snake[IMinusOne].dir == 1 || snake[IMinusOne].dir == 3) && Map[snake[i].x][snake[i].y] != '-') {
                    	output(snake[i].x, snake[i].y,'-');
						Map[snake[i].x][snake[i].y] = '-';
					}
                    else if((snake[IMinusOne].dir == 2 || snake[IMinusOne].dir == 4) && Map[snake[i].x][snake[i].y] != '|'){
                    	output(snake[i].x, snake[i].y,'|');
						Map[snake[i].x][snake[i].y] = '|';
					}
                }
                else if(snake[IMinusOne].dir == 1 || snake[IMinusOne].dir == 3){
                	output(snake[i].x, snake[i].y,'-');
                	Map[snake[i].x][snake[i].y] = '-';
				}
                else {
                	output(snake[i].x, snake[i].y,'|');
                	Map[snake[i].x][snake[i].y] = '|';
				}
            }
        }
		if(ghost && ti % 5 == 0) {
	        srand(time(NULL));
	        for(int i = 0; i < 20; i++){
	            output(rand() % 21, rand() % 21, (char)(rand() % 127 + 1));
	        }
	    }
	    else if(ghost && ti % 5 == 3) {
	    	createmap();
		}
        gotoxy(6,1);
        printf("%d", (length - 3) * 5);
        
        int Choi = judge();
        if(Choi == 0) {
        	return false;
		}
		else if(Choice == 1) {
			return true;
		}
    	
        ++ti;//gameTimeUpd
        flag1 = 0;//keybdEventUpd
    }
}

int main(void) {
	
    startGame();    //loadTheStartPage
    
	GCS();          //gameConditionSet
	
    bool choice = startPlaying(); //startTheGame
    
    while(choice) {
    	GCS();
    	choice = startPlaying();
	}
	
    Sleep(1000);
    
    return 0;
}
