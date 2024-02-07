#include "header.h"

int main()
{
    int  type, maxScore, res=0, flag1=0, flag2=0;
    char command;
    userInfo *pHead=NULL, *pTmp;
    userInfo currUser;
    mapInfo currMap;
    currMap.score=0;
    xoy pacMan, ghost1, ghost2;

    pHead = loadUsers();

    //main menu
    while(1)
    {
        mainMenu();
        command = _getch();
        printf(clear);
        switch(command)
        {
            case '1':
                currUser = logIn(pHead);
                if(currUser.password==0)//log in failed 
                    break;//go to main menu
                else
                {
                    //game menu
                    while(1)
                    { 
                        gameMenu();
                        command = _getch();
                        switch(command)
                        {
                            case '1':///game play
                                if(currUser.lastPlayStatus==1)
                                {
                                    printf(clear yellow"Do you want to restore your last play?(enter y for yes and n for no)\n"reset);
                                    command = _getch();
                                    if(command=='n')
                                        currUser.lastPlayStatus=0;
                                    else
                                    {
                                        type = readType(currUser.id);
                                        switch(type)
                                        {
                                            case 1:
                                                currMap=loadUserMap1(currUser.id,&pacMan,&ghost1);
                                                maxScore=1;
                                                res = play1(&pacMan,&ghost1,&currMap,&currUser,maxScore);
                                                if(res==1)
                                                {
                                                    currUser.level+=3;
                                                    currUser.lastPlayStatus=0;
                                                }
                                                if(res==2)
                                                {
                                                    currUser.level --;
                                                    currUser.lastPlayStatus=0;
                                                }
                                                freeMap(currMap);
                                                break;//go to game menu
                                            case 2:
                                                currMap=loadUserMap2(currUser.id,&pacMan,&ghost1,&ghost2);
                                                maxScore=2;
                                                res = play2(&pacMan,&ghost1,&ghost2,&currMap,&currUser,maxScore);
                                                if(res==1)
                                                {
                                                    currUser.level+=3;
                                                    currUser.lastPlayStatus=0;
                                                }
                                                if(res==2)
                                                {
                                                    currUser.level --;
                                                    currUser.lastPlayStatus=0;
                                                }
                                                freeMap(currMap);
                                                break;//go to game menu
                                        }            
                                        flag2=1; //flag2 : not to start a new game while the user has chosen to play his last game
                                    }
                                }
                                if(currUser.lastPlayStatus==0 && flag2==0)
                                {
                                    //play 
                                    playMenu();
                                    scanf("%d",&type);
                                    switch(type)
                                    {
                                        case 1:
                                            currMap = loadMap(1);
                                            pacMan.x = 6;
                                            pacMan.y = 2;
                                            ghost1.x = 2;
                                            ghost1.y = 3;
                                            maxScore=1;
                                            res = play1(&pacMan,&ghost1,&currMap,&currUser,maxScore);
                                            if(res==1)
                                                currUser.level+=3;
                                            if(res==2)
                                                currUser.level --;
                                            freeMap(currMap);
                                            break;
                                        case 2:
                                            currMap = loadMap(2);
                                            pacMan.x = 4;
                                            pacMan.y = 5;
                                            ghost1.x = 1;
                                            ghost1.y = 3;
                                            ghost2.x = 7;
                                            ghost2.y = 3;
                                            maxScore=2;
                                            res = play2(&pacMan,&ghost1,&ghost2,&currMap,&currUser,maxScore);
                                            if(res==1)
                                                currUser.level+=3;
                                            if(res==2)
                                                currUser.level --;
                                            freeMap(currMap);
                                            break;
                                        case 3:
                                            currMap = loadMap(3);
                                            pacMan.x = 1;
                                            pacMan.y = 7;
                                            ghost1.x = 2;
                                            ghost1.y = 1;
                                            ghost2.x = 6;
                                            ghost2.y = 7;
                                            maxScore=3;
                                            res = play2(&pacMan,&ghost1,&ghost2,&currMap,&currUser,maxScore);
                                            if(res==1)
                                                currUser.level+=3;
                                            if(res==2)
                                                currUser.level --;
                                            freeMap(currMap);
                                            break;
                                        default:
                                            error("Please enter a valid number!");
                                    }          
                                }
                                flag2=0;
                                break;//go to game menu
                            case '2':
                                attachToLinkedList(currUser,pHead);
                                flag1=1;
                                break;//go to main menu(with a flag)
                            case '3':
                                attachToLinkedList(currUser,pHead);
                                storeUsers(pHead);
                                return 0;//exit 
                            default:
                                error("Please enter a valid number!");
                                break;//go to game menu
                        }
                        if(flag1==1) //check if the user wants to go to the main menu
                        {
                            flag1=0;
                            break;
                        }
                    }
                }
                break;
            case '2':
                pTmp = signUp(pHead);
                pHead = pTmp;
                break;//go to mainMenu
            case '3':
                pTmp = deleteAccount(pHead);
                pHead = pTmp;
                break;//go to mainMenu
            case '4':
                storeUsers(pHead);
                return 0;
            default:
                error("Please enter a valid number!");
                break;//goto mainMenu
        }
    }
    return 0;
}