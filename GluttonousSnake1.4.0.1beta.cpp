#include<ctime>
#include<cmath>
#include<cstdlib>
#include<cstring>
#include<conio.h>
#include<iostream>
#include<windows.h>

using namespace std;

string map[22];
int n = 0, input, length, direction, newinp, flag, flag1;
int speed = 60,delay = 9, con = 1, applex, appley, ti;
bool wall = 1, ghost = 0;

struct sna {
    int x;
    int y;
    int dir;
}snake[484];//queueWithoutHeadAndTail

void output(void) {//GameMapOutput
	string out;
    system("cls");
    if(ghost == 1 && ti % 5 != 0) {
        srand(time(NULL));
        for(int i = 0; i < 20; i++){
            map[rand() % 21][rand() % 21] = rand() % 127 + 1;
        }
    }
    cout << "-GluttonousSnake-\nScore:" << (length - 3) * 5 << endl;
    for(int i = 0; i < 22; ++i) {
    	out += map[i] + '\n';
	}
    cout << out;
}

bool gameover(void) {//gameCondition
    if(map[snake[0].x][snake[0].y] == '-' || map[snake[0].x][snake[0].y] == '|' || map[snake[0].x][snake[0].y] == '+' || snake[0].x == 0 || snake[0].x == 21 || snake[0].y == 0 || snake[0].y == 21) {
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
    map[ 0] = "######################";
    map[ 1] = "#                    #";
    map[ 2] = "#                    #";
    map[ 3] = "#                    #";
    map[ 4] = "#                    #";
    map[ 5] = "#                    #";
    map[ 6] = "#                    #";
    map[ 7] = "#                    #";
    map[ 8] = "#                    #";
    map[ 9] = "#                    #";
    map[10] = "#                    #";
    map[11] = "#                    #";
    map[12] = "#                    #";
    map[13] = "#                    #";
    map[14] = "#                    #";
    map[15] = "#                    #";
    map[16] = "#                    #";
    map[17] = "#                    #";
    map[18] = "#                    #";
    map[19] = "#                    #";
    map[20] = "#                    #";
    map[21] = "######################";
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
    map[applex][appley] = 'a';
    map[snake[0].x][snake[0].y] = '@';
    for(int i = 1; i < 484; ++i) {
    	if(snake[i].x != 0 && snake[i].y != 0) {
    		map[snake[i].x][snake[i].y] = '-';
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
        for(int i = 0; i < 110 - speed; i++) {
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
                        	delay++;
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
        for(int i = length - 1; i > 0; --i){
            if(i == length - 1 && flag == 1){
                snake[length].x   = snake[length - 1].x;
                snake[length].y   = snake[length - 1].y;
                snake[length].dir = snake[length - 1].dir;
            }
            snake[i].x   = snake[i - 1].x;
            snake[i].y   = snake[i - 1].y;
            snake[i].dir = snake[i - 1].dir;
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
            	snake[0].x=1;
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
            while(map[applex][appley] == '@' || map[applex][appley] == '|' || map[applex][appley] == '-' || map[applex][appley] == '+') {
                applex = rand() % 20 + 1;
                appley = rand() % 20 + 1;
            }
        }
		else {
			flag = 0;
		}
        
        //newGameMapUpd
        clemap();
        map[applex][appley] = 'a';
        map[snake[0].x][snake[0].y] = '@';
        for(int i = 1; i < 484; i++) {
            if(snake[i].x != 0 && snake[i].y != 0) {
                if(snake[i - 1].dir != snake[i].dir) {
                    if(snake[i + 1].dir != 0) {
                    	map[snake[i].x][snake[i].y] = '+';
					}
                    else if(snake[i - 1].dir == 1 || snake[i-1].dir == 3) {
                    	map[snake[i].x][snake[i].y] = '-';
					}
                    else {
                    	map[snake[i].x][snake[i].y] = '|';
					}
                }
                else if(snake[i - 1].dir == 1 || snake[i - 1].dir == 3){
                	map[snake[i].x][snake[i].y] = '-';
				}
                else {
                	map[snake[i].x][snake[i].y] = '|';
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
