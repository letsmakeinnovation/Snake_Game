
#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include "Snake.h"
#include "Snake_config.h"

#define height 24
#define width  80

using namespace std;

static int snake_speed = 300;
int gobal_flag = 0;

int snake_food_x;
int snake_food_y;

int snake_special_food_x;
int snake_special_food_y;
bool snake_special_flag = 0;
bool snake_special_flag_expire = 0;
int snake_special_expire = 0;

static char version[10] = "0.001V";
string direction = "none";
bool Pause_Button = 0;
string Mode  = "Normal";
string Player_Name;

int snake_body[100][3] = {0}; // Total size 25, 0 - X position ; 1 - y position;
static int counter = 0;
int len = sizeof(snake_body)-12;

int level = 0;
int counter_1 = 0;
int Game_start = 0;
int score = 0;
int Speed[3] = {25,50,200};
char mode_selection = 0;
char snake_head = '0';

snake snake1({24/2,80/2},1,'n');

void Start_Gaming()
{
    cout<<"\t\t\t\t Start Gaming";

    for(int i=0; i<5; i++)
    {
        cout<<".";
        Sleep(500);
    }

    system("cls");

}
void Initial_Config()
{

    bool Invalid_key = 0;
    bool Invalid_Config = 0;
    char mode_selection_user[10];
    char Config_Selection = 0;
    char Game_Configuration[10];

    cout<<"***********************************SANKE GAME***********************************"<<endl;

    cout<< "Enter Player Name : "<<endl;
    cin>>Player_Name;
    cout<<"Do you want to re-configure your setting? (yes/no)"<<endl;
    while(!Invalid_key)
    {
        cin>> Game_Configuration;
        if(strcmp(Game_Configuration,"yes")==0)
        {
            cout<<"Enter into Config window ....."<<endl;

            cout<< "\n\n*********************************CONFIG WINDOW*********************************"<<endl;

            while(!Invalid_Config)
            {
                cout<<"\n1. Mode \t 2. Sanke Head \t\t 3. About \t 4. Quit"<<endl;
                cin>>Config_Selection;

                switch(Config_Selection)
                {
                    case '1':
                            cout<<"Select the Mode (speed) of the Game (easy/normal/hard)"<<endl;
                            re:
                            cout<<"Enter mode selection : ";
                            cin>>mode_selection_user;

                            if(strcmp(mode_selection_user,"easy")==0)
                            {
                                Mode = "Easy";
                                mode_selection = 0;
                            }
                            else if(strcmp(mode_selection_user,"normal")==0)
                            {
                                Mode = "Normal";
                                mode_selection = 1;
                            }
                            else if(strcmp(mode_selection_user,"hard")==0)
                            {
                                Mode = "Hard";
                                mode_selection = 2;
                            }
                            else
                            {
                                cout<<"Invalid mode selection"<<endl;
                                goto re;
                            }
                            break;

                    case '2':

                             cout<<"Enter Key to Configure the Snake Head : ";
                             cin>>snake_head;
                             break;
                    case '3':
                              cout<<"\nabout :"<<endl;
                              cout<<"version :"<<version<<endl;
                              cout<<"Developer : Prasanth A \n"<<endl;
                              break;

                    case '4': cout<<"quit"<<endl; Invalid_Config=1; Invalid_key = 1; break;

                    default:
                        cout<<"Invalid key"<<endl;
                        break;
                }
            }
        }
        else
        {
            if(strcmp(Game_Configuration,"no")==0)
            {
                Invalid_key = 1;
            }
            else
            {
                cout<<"Invalid key"<<endl;
            }
        }
    }

}

void GamePlay_window()
{
    cout<<"***********************************SANKE GAME***********************************"<<endl;
    Game_start = 1;
    while(Game_start)
    {
        hidecursor();
        level_updation();
        game_keys();

    cout<<"\n";

    cout<<"Player : "<<Player_Name<<"                                                                           "<<endl;
    if(!snake_special_flag)
    {
        cout<<"\t\t\t\t\t\t\t Score : "<<score<<"              "<<endl;
    }
    else
    {
         cout<<"\t\t\t\t\t\t\t Score : "<<score<<"    /Booter\\"<<endl;
    }

    cout<<"\t\t\t\t   LEVEL - "<<level<<endl;
    cout<<"Mode : "<<Mode<<"\t\t\t\t\t\t  Move : "<<direction <<endl;

        board();

        if(Pause_Button==1)
        {
            system("cls");
            cout<<"***********************************SANKE GAME***********************************"<<endl;
            cout<<"1.New Game                    2.Resume the game(Esc button)              3.Quit"<<endl;
            while(Pause_Button)
            {
                if(kbhit())
                {
                    switch(getch())
                    {
                        case '1': system("cls"); Pause_Button = 0; restore_default(); Start_Gaming(); GamePlay_window(); break;
                        case 2:
                        case 27: Pause_Button = 0; break;
                        case '3':  Pause_Button = 0; Game_start = 0; break;
                        default:
                        break;

                }
        }
            }

        }
    }
    cout<< "\n\n***********************************GAME OVER***********************************"<<endl;

}



//    cout<<"dir "<<snake1.dir<<"\t\t\t\t\t\t\tPlayer : "<<Player_Name<<endl;
//    cout<<"pos_x "<<snake1.pos.x<<"       LEVEL - "<<level<<endl;
//    cout<<"pos_y "<<snake1.pos.y<<endl;

void board()
{
    bool flag = 0;
    bool food_place = 0;
    bool special_food_place = 0;
    bool member_flag = 0;

    if(gobal_flag==0)
    {
        c:
        snake_food_x = rand()%(23);
        snake_food_y = rand()%(78);

        if((snake_special_flag==1 && counter%4==0) || counter==0 )
        {
            snake_special_food_x = rand()%(23);
            snake_special_food_y = rand()%(78);
            snake_special_flag = 0;
            snake_special_flag_expire = 0;
        }

        if(snake_food_x==0 || snake_food_y==0)
        {
            goto c;
        }
        else if(snake_special_food_x==0 || snake_special_food_y==0)
        {
            goto c;
        }

        gobal_flag = 1;
    }

    memcpy(snake_body+1,snake_body,len);

    snake_body[0][0]= snake1.pos.x ;
    snake_body[0][1]= snake1.pos.y ;

    for(int i=0; i<99; i++)
    {
        if(i>counter)
        {
            for(int j=0; j<3; j++)
            {
                snake_body[i][j]=0;
            }
        }
    }

    for(int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++)
        {
            if((i==snake1.pos.x) && (j==snake1.pos.y))
            {
                flag = 1;
                cout<<snake_head;
            }

            if((i==snake_special_food_x) && (j==snake_special_food_y)&&(snake_special_flag==0)&&(snake_special_flag_expire==0))
            {
                special_food_place = 1;

                if(flag==1)
                {
                    snake_special_flag = 1;

                    snake_body[counter][2] = 1;
                    counter++;
                    score += 5;
                }
                else
                {
                    cout<<"*";
                }
            }
            else
            {
                special_food_place = 0;
            }

            if((i==snake_food_x) && (j==snake_food_y))
            {
                food_place = 1;
                if(flag==0)
                {
                    cout<<"1";
                }
                else
                {
                    snake_special_flag = 0;
                    gobal_flag = 0;

                    snake_body[counter][2] = 1;
                    counter++;
                    score++;
                }
            }
            else
            {
                food_place = 0;
            }

            if((i==0) || (i== height-1) || (j==0) || (j==width-1))
            {
                if(flag==1)
                {
                    Game_start = 0;
                }
                else
                {
                    cout<<"#";
                }
            }
            else
            {

                if(flag==1)
                {
                    flag = 0;

                     for(int k=1; k<99; k++)
                    {
                        if(snake_body[k][2] == 1)
                        {
                            if(snake_body[k][0]==i && snake_body[k][1]==j)
                            {
                                Game_start = 0;
                            }
                        }
                    }

                }
                else if((food_place==0) && (special_food_place==0))
                {
                    member_flag = 0;
                    for(int k=0; k<99; k++)
                    {
                        if(snake_body[k][2] == 1)
                        {
                            if(snake_body[k][0]==i && snake_body[k][1]==j)
                            {

                               cout<<"0";
                                member_flag = 1;
                                goto c1;
                            }
                        }
                    }
                    c1:
                    if(!member_flag)
                    {
                       cout<<" ";
                    }
                }

            }

        }
        cout<<"\n";

    }

}

void level_updation()
{
    if(snake_speed>0)
    {
        if((counter>counter_1) || (!counter_1))
        {
            if(counter_1>0)
            {
                level++;
            }
            else
            {
                snake_speed -= Speed[mode_selection];
            }

            snake_speed -= 2;

            counter_1 += 2;
        }
    }

    if(snake_special_flag==0)
    {
        if(snake_special_expire++>20)
        {
            //snake_special_flag_expire = 1;
            snake_special_expire = 0;
        }
    }

    Sleep(snake_speed);  // Control the speed of the snake

}


void restore_default()
{
    memset(snake_body, 0, sizeof(snake_body));
    score = 0;
    counter = 0;
    counter_1 = 0;
    gobal_flag = 0;
}

void game_keys()
{
        snake1.move_snake(snake1.dir);
        if(kbhit())
        {
            switch(getch())
            {
                case '4': snake1.dir = '4'; direction = "Left   "; break;
                case '6': snake1.dir = '6'; direction = "Right  "; break;
                case '8': snake1.dir = '8'; direction = "UP     "; break;
                case '2': snake1.dir = '2'; direction = "Down   "; break;
                case 27: Pause_Button = 1; break;

                default:
                break;

            }
        }

        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),{0,0}); // AVOID FLUXERING IN CONCLE
}

void hidecursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle,&info);
}

