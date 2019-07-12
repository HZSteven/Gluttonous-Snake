#include<ctime>
#include<cmath>
#include<cstdlib>
#include<cstring>
#include<conio.h>
#include<iostream>
#include<bits/stdc++.h> 
#include<windows.h>

using namespace std;

string Map[22];
int n;
int input, length, direction, newinp;
int flag, flag1;
int speed = 60;
int delay = 9;
int con   = 1;
int applex, appley, ti;
bool wall  = true;
bool ghost = false;

struct Snake {
    int x;
    int y;
    int dir;
}snake[484];//queueWithoutHeadAndTail

void output(void) {//GameMapOutput
	string out;
    system("cls");
    if(ghost == 1 && ti % 5 != 0) {
        srand(time(NULL));
        for(int i = 0; i < 20; ++i) {
            Map[rand() % 21][rand() % 21] = rand() % 127 + 1;
        }
    }
    cout << "-GluttonousSnake-\nScore:" << (length - 3) * 5 << endl;
    for(int i = 0; i < 22; ++i) {
    	out += Map[i] + '\n';
	}
    cout << out;
}

bool gameover(void) {//gameCondition
    if(Map[snake[0].x][snake[0].y] == '-' || Map[snake[0].x][snake[0].y] == '|' || Map[snake[0].x][snake[0].y] == '+' || snake[0].x == 0 || snake[0].x == 21 || snake[0].y == 0 || snake[0].y == 21) {
        system("cls");
        cout << "Game over!\nScore:" << (length - 3) * 5 << endl;
        while(!_kbhit()) {
        	Sleep(10);
		}
        return true;
    }
    return false;
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

void GCS(void) {//gameConditionSet
	system("color 0F");
	srand(time(NULL));
	direction = 1;
	length = 3;
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
    return;
}

int main(void) {
	
	GCS();//gameConditionSet
	
    //startPage
    system("cls");
    string st = "-GluttonousSnake-\nBy KM_YoaMoa & HZSteven\nbeta1.4 Upd:2019/07/09\n-Press space to start the game-";
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
    
    output();//theFirstGameMapOutput
    
    while(1) {//gameLoop
        //keybdEvent
        int END = 110 - speed;
        for(int i = 0; i < END; ++i) {
            if(_kbhit()) {
                newinp = _getch();
                flag1 = 1;
            }
            Sleep(delay);
        }
        
        if(flag1 == 1){//ifAnyKeyDown
        
        	//newDirectionUpd
            if     ((newinp == 68 || newinp == 100) && direction != 3) {
            	direction = 1;
			}
            else if((newinp == 83 || newinp == 115) && direction != 4) {
            	direction=2;
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
                while(1) {
                    system("cls");
                    cout << "-Pause-" << endl;
                    string c[5] = {"Speed:", "Delaytime:", "Wall:", "Ghost:", "Exit"};
                    for(int i = 0; i < 5; i++){
                        if(con - 1 == i) {
                        	cout << "&";
						}
                        else {
                        	cout << " ";
						}
                        cout << c[i];
                        if(i == 0) {
                        	cout << speed;
						}
                        else if(i == 1) {
                        	cout << delay;
						}
                        else if(i == 2) {
                            if(wall == 1) {
                            	cout << "true";
							}
                            else {
                            	cout << "false";
							}
                        }else if(i == 3) {
                            if(ghost == 1) {
                            	cout << "true";
							}
                            else {
                            	cout << "false";
							}
                        }
                        cout << endl; 
                    }
                    while(!_kbhit()) {
                    	Sleep(10);
					} 
                    int in = _getch();
                    if(in == 119 && con > 1) {
                    	--con;
					}
                    else if(in == 115 && con < 5) {
                    	++con;
					}
                    else if(in == 97) {
                        if(con == 1 && speed > 10) {
                        	speed -= 5;
						}
                        else if(con == 2 && delay > 0) {
                        	--delay;
						}
                        else if(con == 3) {
                        	wall = !wall;
						}
                        else if(con == 4) {
                        	ghost = !ghost;
						}
                    }else if(in == 100) {
                        if(con == 1 & speed < 100) {
                        	speed += 5;
						}
                        else if(con == 2 && delay < 15) {
                        	++delay;
						}
                        else if(con == 3) {
                        	wall = !wall;
						}
                        else if(con == 4) {
                        	ghost = !ghost;
						}
                    }
					else if(in == 13) {
                        if(con == 5) {
                            cout << "Thanks for your support!" << endl;
                            Sleep(1000);
                            return 0;
                        }
                    }
					else if(in == 32){
						break;
					}
                }
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
        if(gameover()) {
        	return 0;
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
        clemap();
        Map[applex][appley] = 'a';
        Map[snake[0].x][snake[0].y] = '@';
        for(int i = 1; i < 484; ++i) {
            if(snake[i].x != 0 && snake[i].y != 0) {
            	int IMinusOne = i - 1;
                if(snake[IMinusOne].dir != snake[i].dir) {
                    if(snake[i + 1].dir != 0) {
                    	Map[snake[i].x][snake[i].y] = '+';
					}
                    else if(snake[IMinusOne].dir == 1 || snake[IMinusOne].dir == 3) {
                    	Map[snake[i].x][snake[i].y] = '-';
					}
                    else {
                    	Map[snake[i].x][snake[i].y] = '|';
					}
                }
                else if(snake[IMinusOne].dir == 1 || snake[IMinusOne].dir == 3){
                	Map[snake[i].x][snake[i].y] = '-';
				}
                else {
                	Map[snake[i].x][snake[i].y] = '|';
				}
            }
        }
        if(gameover()) {
        	return 0;
		}
        
        
        output();//gameMapOutput
        ++ti;//gameTimeUpd
        flag1 = 0;//keybdEventUpd
    }
    return 0;
}
