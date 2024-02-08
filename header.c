#include "header.h"

//menu display
void mainMenu()
{
    printf(clear"\n\n\n\n");
    printInTheCenter("Main Menu");
    printf(red);
    printInTheCenter("________________");
    printf(reset);
    printf("\n");
    printInTheCenter("1.log in");
    printf("\n");
    printInTheCenter("2.sign up");
    printf("\n");
    printInTheCenter("3.delete account");
    printf("\n");
    printInTheCenter("4.exit");
    printf(red);
    printInTheCenter("________________");
    printf(reset);
}
void gameMenu()
{
    printf(clear"\n\n\n\n");
    printInTheCenter("Game Menu");
    printf(red);
    printInTheCenter("________________");
    printf(reset);                        
    printf("\n");
    printInTheCenter("1.play");
    printf("\n");
    printInTheCenter("2.log out");
    printf("\n");
    printInTheCenter("3.exit");
    printf(red);
    printInTheCenter("________________");
    printf(reset);
}
void playMenu()
{
    printf(clear);
    printf(red"\n\n\n\n");
    printInTheCenter("________________");
    printf(reset);
    printInTheCenter("1.easy");
    printf("\n");
    printInTheCenter("2.medium");
    printf("\n");
    printInTheCenter("3.hard");
    printf(red);
    printInTheCenter("________________");
    printf(reset);
}

//message display 
void printInTheCenter(char* str)
{
    int len = strlen(str);
    int space = (200-len)/2;
    int i;
    for(i=0;i<space;i++)
        printf(" ");
    printf("%s\n",str);
}
void printLose()
{
    printf("\n\n\n\n\n\n\n");
    printInTheCenter("****	  *********  ********  ********  ");
    printInTheCenter("****	  *********  ***       ***       ");
    printInTheCenter("****	  ***   ***  ********  ********  ");
    printInTheCenter(" *******  *********       ***  ***     ");
    printInTheCenter(" *******  *********  ********  ********");
}
void printWin()
{
    printf("\n\n\n\n\n");
    printInTheCenter("***      **      *** ********** ******    ***");
    printInTheCenter(" ***    ****    ***     ****    *** ***   ***");
    printInTheCenter("  ***  ******  ***      ****    ***  ***  ***");
    printInTheCenter("   ******  ******       ****    ***   *** ***");
    printInTheCenter("     ***    ***      ********** ***    ******");
}
void error(char*text)
{
    printf(clear"\n\n\n\n"red);
    printInTheCenter(text);
    printf(reset);
    Sleep(3000);
}
void confirmation(char*text)
{
    printf(clear"\n\n\n\n"green);
    printInTheCenter(text);
    printf(reset);
    Sleep(3000);
}
void win()
{
    int i;
    printf(green);
    for(i=0;i<20;i++)
    {
        printf(clear);
        printWin();
        Sleep(100);
        printf(clear"\n\n\n\n\n");
        printWin();
        Sleep(100);
        printf(clear"\n\n\n\n\n\n\n\n\n\n");
        printWin();
        Sleep(100);
    }
    printf(reset);
}
void lose()
{
    int i;
    printf(red);
    for(i=0;i<20;i++)
    {
        printf(clear);
        printLose();
        Sleep(100);
        printf(clear"\n\n\n\n\n");
        printLose();
        Sleep(100);
        printf(clear"\n\n\n\n\n\n\n\n\n\n");
        printLose();
        Sleep(100);
    }
    printf(reset);
}

//load functions
userInfo* loadUsers()
{
    userInfo *pHead=NULL, *pNew, *pTmp, tmp;

    //opening the file 
    FILE* fp;
    fp = fopen("userInfo.bin","r");
    if(fp==NULL)
        return NULL;

    //creating the linked list 
    while(fread(&tmp,sizeof(userInfo),1,fp)>0)
    {
        pNew = (userInfo*) malloc(sizeof(userInfo));
        pNew->next=NULL;
        *pNew = tmp; //does it work?
        if(pHead == NULL)
            pHead = pTmp = pNew;
        else
        {
            pTmp->next = pNew;
            pTmp = pTmp->next;
        }
    }

    //closing the file 
    fclose(fp);
    return pHead;
}
mapInfo loadUserMap1(char id[21],xoy*pacMan,xoy*ghost)
{
    int i, tmp;
    mapInfo userMap={};

    char fileName[25];
    strcpy(fileName,id);
    strcat(fileName,".txt");

    FILE* fp;
    fp = fopen(fileName,"r");
    if(fp==NULL)
        return userMap;
    
    fscanf(fp,"%d",&tmp);
    fscanf(fp,"%d %d",&userMap.yWidth,&userMap.xLength); //geting the size 
    userMap.map=(char**)malloc((userMap.yWidth)*sizeof(char*));
    for(i=0;i<userMap.yWidth;i++) //scaning the map
    {
        userMap.map[i]=(char*)malloc(userMap.xLength+1);
        fgets(userMap.map[i],userMap.xLength+1,fp);       
    }
    fscanf(fp,"%d",&userMap.score); //score 
    fscanf(fp,"%d %d",&pacMan->x,&pacMan->y); //pacMan
    fscanf(fp,"%d %d",&ghost->x,&ghost->y); //ghost
    fclose(fp);
    return userMap;
}
mapInfo loadUserMap2(char id[21],xoy*pacMan,xoy*ghost1,xoy*ghost2)
{
    int i,tmp;
    mapInfo userMap={};

    char fileName[25];
    strcpy(fileName,id);
    strcat(fileName,".txt");

    FILE* fp;
    fp = fopen(fileName,"r");
    if(fp==NULL)
        return userMap;
    fscanf(fp,"%d",&tmp);
    fscanf(fp,"%d %d",&userMap.yWidth,&userMap.xLength);
    userMap.map=(char**)malloc((userMap.yWidth)*sizeof(char*));
    for(i=0;i<userMap.yWidth;i++)
    {
        userMap.map[i]=(char*)malloc(userMap.xLength+1);
        fgets(userMap.map[i],userMap.xLength+1,fp);        
    }
    fscanf(fp,"%d",&userMap.score); //score
    fscanf(fp,"%d %d",&pacMan->x,&pacMan->y);
    fscanf(fp,"%d %d",&ghost1->x,&ghost1->y);
    fscanf(fp,"%d %d",&ghost2->x,&ghost2->y);
    fclose(fp);
    return userMap;
}
mapInfo loadMap(int type)
{
    int i;
    char fileName[10];
    switch(type)
    {
        case 1: //easy
            strcpy(fileName,"mapA.txt");
            break;
        case 2:
            strcpy(fileName,"mapB.txt");
            break;
        case 3:
            strcpy(fileName,"mapC.txt");
            break;
    }
    mapInfo Map={};
    FILE* fp;

    fp = fopen(fileName,"r");
    if(fp==NULL)
        return Map;
    fscanf(fp,"%d %d",&Map.yWidth,&Map.xLength);
    Map.map=(char**)malloc((Map.yWidth)*sizeof(char*));
    for(i=0;i<Map.yWidth;i++)
    {
        Map.map[i]=(char*)malloc(Map.xLength+1);
        fscanf(fp,"%s",Map.map[i]);//        
    }
    return Map;
}
int readType(char*id)
{
    char fileName[25];
    FILE* fp;
    int type;

    strcpy(fileName,id);
    strcat(fileName,".txt");
    fp = fopen(fileName,"r");
    fscanf(fp,"%d",&type);
    fclose(fp);
    return type;
}

//store functions 
void storeUsers(userInfo* pHead)
{
    userInfo *pTmp;
    FILE* fp;
    fp = fopen("userInfo.bin","w");
    if(fp==NULL)
        return;
    
    while (pHead)
    {
        fwrite(pHead,sizeof(userInfo),1,fp);
        pTmp = pHead;
        pHead = pHead->next;
        free(pTmp);
    }
    free(pHead);
    fclose(fp);
}
void storeUserMap1(mapInfo userMap, char id[21],xoy pacMan,xoy ghost)
{
    int i;
    char fileName[25];
    strcpy(fileName,id);
    strcat(fileName,".txt");

    FILE* fp;
    fp = fopen(fileName,"w");
    if(fp==NULL)
        return;
    
    fprintf(fp,"%d %d %d",1,userMap.yWidth,userMap.xLength);//printing the size 
    for(i=0;i<userMap.yWidth;i++)//printing the map
    {
        fputs(userMap.map[i],fp);        
        free(userMap.map[i]);
    }
    free(userMap.map);
    fprintf(fp,"%d %d %d %d %d",userMap.score,pacMan.x,pacMan.y,ghost.x,ghost.y);
    fclose(fp);
}
void storeUserMap2(mapInfo userMap, char id[21],xoy pacMan,xoy ghost1,xoy ghost2)
{
    int i;
    char fileName[25];
    strcpy(fileName,id);
    strcat(fileName,".txt");

    FILE* fp;
    fp = fopen(fileName,"w");
    if(fp==NULL)
        return;
    fprintf(fp,"%d %d %d",2,userMap.yWidth,userMap.xLength);
    for(i=0;i<userMap.yWidth;i++)
    {
        fputs(userMap.map[i],fp);        
        free(userMap.map[i]);
    }
    free(userMap.map);
    fprintf(fp,"%d %d %d %d %d %d %d",userMap.score,pacMan.x,pacMan.y,ghost1.x,ghost1.y,ghost2.x,ghost2.y);
    fclose(fp);
}
void attachToLinkedList(userInfo currUser,userInfo*pHead)
{
    userInfo *pi;
    for(pi=pHead;pi!=0;pi=pi->next)
    {
        if(strcmp(pi->id,currUser.id)==0)
        {
            *pi = currUser;
            return;
        }
    }
}

//free function 
void freeMap(mapInfo Map)
{
    int i, j;
    for(i=0;i<Map.yWidth;i++)
        free(Map.map[i]);
    free(Map.map);
}

//authentation
userInfo logIn(userInfo* pHead) 
{
    userInfo *pi, user;

    printf(yellow"\n\n\n\nUsername:"reset);
    scanf(" %s",user.id);
    printf(yellow"Password"underlinedYellow"(less than 8 digits):"reset);
    scanf(" %d",&user.password);
    printf(clear);
    if(pHead==NULL) //no account saved
    {
        error("The id was not found! Please sign up first!");
        user.password=0;
        return user;   
    }
    for(pi=pHead;pi!=0;pi=pi->next)
    {
        if(strcmp(pi->id,user.id)==0)
        {
            if(pi->password==user.password)
                return *pi;
            error("WRING PASSWORD!");
            user.password=0;
            return user;
        }
    }
    error("The id was not found! Please sign up first!");
    user.password=0;
    return user;
}
userInfo* signUp(userInfo* pHead) 
{
    userInfo *pNew, *pi;

    pNew = (userInfo*)malloc(sizeof(userInfo));
    pNew->next=NULL;
    printf(clear yellow"\n\n\n\nPlease choose a usernamer"underlinedYellow"(less than 20 characters\\letters A-Z\\digits 0-9\\without space):"reset);
    scanf("%s",pNew->id);
    for(pi=pHead;pi!=0;pi=pi->next)
    {
        if(strcmp(pi->id,pNew->id)==0)
        {
            error("This id has been used before!");
            free(pNew);
            return pHead;
        }
    }
    printf(yellow"Please enter a password"underlinedYellow"(less than 8 digits):"reset);
    scanf("%d",&pNew->password);
    pNew->lastPlayStatus=0;
    pNew->level=0;
    if(pHead!=NULL)
        pNew->next = pHead;
    confirmation("You are sucessfully signed in! To start a game please log in!");
    return pNew; //as the new pHead 
}
userInfo* deleteAccount(userInfo* pHead) 
{
    userInfo *pi, *pBefore;
    char id[21];
    int password;
    printf(yellow"Username:"reset);
    scanf("%s",id);
    printf(yellow"Password:"reset);
    scanf("%d",&password);
    if(pHead==NULL)
        return NULL;
    for(pi=pHead;pi!=0;pi=pi->next)
    {
        if(strcmp(pi->id,id)==0)
        {
            if(pi->password==password)
            {
                if(pi==pHead)
                {
                    pHead = pHead->next;
                    free(pi->next);
                    confirmation("The account is successfully deleted!");
                    return pHead;
                }
                pBefore->next = pi->next;
                free(pi);
                confirmation("The account is successfully deleted!");
                return pHead;
            }
            error("WRONG PASSWORD!");
            return pHead;
        }
        pBefore = pi;
    }
    error("The id wasn't found!");
    return pHead;
}

//game functions
void mapDisplay(mapInfo Map)
{
    int i, j,k;
    for(i=0;i<Map.yWidth;i++)
    {
        for(k=0;k<(200-(Map.xLength*3))/2;k++)
            printf(" ");
        for(j=0;j<Map.xLength;j++)
        {
            switch(Map.map[i][j])
            {
                case '|':
                case '-':
                    printf(gray"\u2588\u2588\u2588"reset);
                    break;
                case '@':
                    printf("\U0001F440 ");
                    break;
                case 'P':
                    printf("\U0001F352 ");
                    break;
                case 'G':
                    printf("\U0001F47E ");
                    break;
                case '.':
                case ' ':
                    printf("   ");
                    break;
            }
        }
        printf("\n");
    }
        
}
int play1(xoy*pacMan,xoy*ghost,mapInfo*Map,userInfo*currUser,int maxScore)
{
    int input,i;
    xoy pPacMan, pGhost;
    int move, flag=0, command;
    
    while(1)
    {
        printf(clear"\n\n\n\n");
        printf(clear yellow"\n\n\n\nusername : "reset"%s\n"yellow "level : "reset "%d\n" yellow "score : " reset,currUser->id,currUser->level);
        for(i=0;i<Map->score;i++)
            printf("\u2764");
        printf("\n");
        
        printf(yellow);
        printInTheCenter("If you want to QUIT, please enter q!");
        printf(reset);
        printf("\n");

        mapDisplay(*Map);
        pGhost=*ghost;
        pPacMan=*pacMan;
        if(kbhit())
        {
            //move input from the user 
            input = _getch(); //handle arrow keys
            if(input==0 || input==224) //fetch the actual key
            {
                input=_getch();
                switch(input)
                {
                    case up:
                        pPacMan.y++;
                        flag=1;
                        break;
                    case down:
                        pPacMan.y--;
                        flag=1;
                        break;
                    case left:
                        pPacMan.x--;
                        flag=1;
                        break;
                    case right:
                        pPacMan.x++;
                        flag=1;
                        break;
                }
                if((*Map).map[pPacMan.y][pPacMan.x]=='|' || (*Map).map[pPacMan.y][pPacMan.x]=='-')
                    pPacMan = *pacMan;//pacman doesn't move 
            }
            else
                if(input=='q')
                {
                    printf(clear yellow"Do you want to save your game for later?1.Yes2.No\n"reset);
                    scanf("%d",&command);
                    if(command==1)
                    {
                        storeUserMap1(*Map,currUser->id,*pacMan,*ghost); 
                        currUser->lastPlayStatus=1;
                    }
                    return 3;
                }

            //check if the pacman eats the pill
            if((*Map).map[pPacMan.y][pPacMan.x]=='P')
                (*Map).score++;
            //check the result 
            if((*Map).score==maxScore)
            {
                win();
                freeMap(*Map);
                return 1; //win
            }
            //updating the map & pacMan position
            (*Map).map[pPacMan.y][pPacMan.x]='@';
            (*Map).map[pacMan->y][pacMan->x]=' ';
            pacMan->x=pPacMan.x;
            pacMan->y=pPacMan.y;
        }
        //move ghosts
        move = ghostMove(*Map,pGhost);
        switch(move)
        {
            case 1: //up
                pGhost.y++;
                break;
            case 2: //down
                pGhost.y--;
                break;
            case 3: //right
                pGhost.x++;
                break;
            case 4: //left
                pGhost.x--;
                break;
            default:
                pGhost = *ghost; //when the ghost can't move
        }
        if(pPacMan.x==pGhost.x && pPacMan.y==pGhost.y)
        {
            lose();
            freeMap(*Map);
            return 2; //means lose
        } 
        (*Map).map[pGhost.y][pGhost.x]='G';
        if((*Map).map[ghost->y][ghost->x] != '@')
            (*Map).map[ghost->y][ghost->x]=' ';
        ghost->x=pGhost.x;
        ghost->y=pGhost.y;
        Sleep(600);
    }
}
int play2(xoy*pacMan,xoy*ghost1,xoy*ghost2,mapInfo*Map,userInfo*currUser,int maxScore)
{
    int input,i;
    xoy pPacMan, pGhost1, pGhost2;
    int move, flag=0, command;
    
    while(1)
    {
        printf(clear"\n\n\n\n");
        printf(clear yellow"\n\n\n\nusername : "reset"%s\n"yellow "level : "reset "%d\n" yellow "score : " reset,currUser->id,currUser->level);
        for(i=0;i<Map->score;i++)
            printf("\u2764");
        printf("\n");

        printf(yellow);
        printInTheCenter("If you want to QUIT, please enter q!");
        printf(reset);
        printf("\n");

        mapDisplay(*Map);
        pGhost1=*ghost1;
        pGhost2=*ghost2;
        pPacMan=*pacMan;
        if(kbhit())
        {
            //move input from the user 
            input = _getch(); //handle arrow keys
            if(input==0 || input==224) //fetch the actual key
            {
                input=_getch();
                switch(input)
                {
                    case up:
                        pPacMan.y++;
                        flag=1;
                        break;
                    case down:
                        pPacMan.y--;
                        flag=1;
                        break;
                    case left:
                        pPacMan.x--;
                        flag=1;
                        break;
                    case right:
                        pPacMan.x++;
                        flag=1;
                        break;
                }
                if((*Map).map[pPacMan.y][pPacMan.x]=='|' || (*Map).map[pPacMan.y][pPacMan.x]=='-')
                    pPacMan = *pacMan;//pacman doesn't move 
            }
            else
                if(input=='q')
                {
                    printf(clear yellow"Do you want to save your game for later?1.Yes2.No\n"reset);
                    scanf("%d",&command);
                    if(command==1)
                    {
                        storeUserMap2(*Map,currUser->id,*pacMan,*ghost1,*ghost2); 
                        currUser->lastPlayStatus=1;
                    }
                    return 3;
                }
            
            //check if the pacman eats the pill
            if((*Map).map[pPacMan.y][pPacMan.x]=='P')
                (*Map).score++;
            //check the result 
            if((*Map).score==maxScore)
            {
                win();
                freeMap(*Map);
                return 1; //win
            }
            //updating the map & pacMan position
            if(pPacMan.x != pacMan->x || pPacMan.y != pacMan->y)
            {
                (*Map).map[pPacMan.y][pPacMan.x]='@';
                (*Map).map[pacMan->y][pacMan->x]=' ';
                pacMan->x=pPacMan.x;
                pacMan->y=pPacMan.y;
            }
        }
        //move ghosts
        move = ghostMove(*Map,pGhost1);
        switch(move)
        {
            case 1: //up
                pGhost1.y++;
                break;
            case 2: //down
                pGhost1.y--;
                break;
            case 3: //right
                pGhost1.x++;
                break;
            case 4: //left
                pGhost1.x--;
                break;
            default:
                pGhost1 = *ghost1; //when the ghost can't move
        }
        if(pPacMan.x==pGhost1.x && pPacMan.y==pGhost1.y)
        {
            lose();
            freeMap(*Map);
            return 2; //means lose
        } 
        (*Map).map[pGhost1.y][pGhost1.x]='G';
        if((*Map).map[ghost1->y][ghost1->x] != '@')
            (*Map).map[ghost1->y][ghost1->x]=' ';
        ghost1->x=pGhost1.x;
        ghost1->y=pGhost1.y;
        
        move = ghostMove(*Map,pGhost2);
        switch(move)
        {
            case 1: //up
                pGhost2.y++;
                break;
            case 2: //down
                pGhost2.y--;
                break;
            case 3: //right
                pGhost2.x++;
                break;
            case 4: //left
                pGhost2.x--;
                break;
            default:
                pGhost2 = *ghost2; //when the ghost can't move
        }
        if(pPacMan.x==pGhost2.x && pPacMan.y==pGhost2.y)
        {
            lose();
            freeMap(*Map);
            return 2; //means lose
        } 
        (*Map).map[pGhost2.y][pGhost2.x]='G';
        if((*Map).map[ghost2->y][ghost2->x] != '@')
            (*Map).map[ghost2->y][ghost2->x]=' ';
        ghost2->x=pGhost2.x;
        ghost2->y=pGhost2.y;
        Sleep(600);
    }
}
int ghostMove(mapInfo Map,xoy ghost)
{
    int arr[4] = {1,2,3,4}, count=0,i=0,j=0;
    if(Map.map[ghost.y+1][ghost.x]=='|' || Map.map[ghost.y+1][ghost.x]=='-' || Map.map[ghost.y+1][ghost.x]=='P' || Map.map[ghost.y+1][ghost.x]=='G')
    {
        count++;
        arr[0]=0;
    }
    if(Map.map[ghost.y-1][ghost.x]=='|' || Map.map[ghost.y-1][ghost.x]=='-' || Map.map[ghost.y-1][ghost.x]=='P' || Map.map[ghost.y-1][ghost.x]=='G')
    {
        count++;
        arr[1]=0;
    }
    if(Map.map[ghost.y][ghost.x+1]=='|' || Map.map[ghost.y][ghost.x+1]=='-' || Map.map[ghost.y][ghost.x+1]=='P' || Map.map[ghost.y][ghost.x+1]=='G')
    {
        count++;
        arr[2]=0;
    }
    if(Map.map[ghost.y][ghost.x-1]=='|' || Map.map[ghost.y][ghost.x-1]=='-' || Map.map[ghost.y][ghost.x-1]=='P' || Map.map[ghost.y][ghost.x-1]=='G')
    {
        count++;
        arr[3]=0;
    }
    srand(time(0));
    if(count==4)
        return 0;
    count = rand()%(4-count)+1;
    for(i=0;i<4;i++)
    {
        if(arr[i]!=0)
            j++;
        if(j==count)
            break;
    }
    return arr[i];
}
