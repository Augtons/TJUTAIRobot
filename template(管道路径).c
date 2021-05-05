////////////////////////////////////////
//
//	File : ai.c
//	CoSpace Robot
//	Version 1.0.0
//	Jan 1 2016
//	Copyright (C) 2016 CoSpace Robot. All Rights Reserved
//
//////////////////////////////////////
//
// ONLY C Code can be compiled.
//
/////////////////////////////////////

#define CsBot_AI_H//DO NOT delete this line
#ifndef CSBOT_REAL
#include <windows.h>
#include <stdio.h>
#include <math.h>
#define DLL_EXPORT extern __declspec(dllexport)
#define false 0
#define true 1
#endif
//The robot ID : six chars unique CID.
//Find it from your CoSpace Robot label or CoSpace program download GUI.
//Don't write the below line into two lines or more lines.
char AI_MyID[6] = {'1','2','3','4','5','6'};

int Duration = 0;
int SuperDuration = 0;
int bGameEnd = false;
int CurAction = -1;
int CurGame = 0;
int SuperObj_Num = 0;
int SuperObj_X = 0;
int SuperObj_Y = 0;
int Teleport = 0;
int LoadedObjects = 0;
int US_Front = 0;
int US_Left = 0;
int US_Right = 0;
int CSLeft_R = 0;
int CSLeft_G = 0;
int CSLeft_B = 0;
int CSRight_R = 0;
int CSRight_G = 0;
int CSRight_B = 0;
int PositionX = 0;
int PositionY = 0;
int Compass = 0;
int Time = 0;
int WheelLeft = 0;
int WheelRight = 0;
int LED_1 = 0;
int MyState = 0;
int AI_SensorNum = 12;
int AI_TeamID = 1; //Robot Team ID. 1:Blue Ream; 2:Red Team.

#define CsBot_AI_C//DO NOT delete this line
//屏蔽区
#define pingBiQv (between(PositionX, 0, 1) && between(PositionY, 0, 1))


//放宝区
#define LeftisDeposit CSLeft_R >= 224 && CSLeft_R <= 244 \
        && CSLeft_G >= 85 && CSLeft_G <= 105 && CSLeft_B <= 20
#define RightisDeposit CSRight_R >= 224 && CSRight_R <= 244 \
        && CSRight_G >= 85 && CSRight_G <= 105 && CSRight_B <= 20
#define isDeposit (LeftisDeposit && RightisDeposit)


//红石
#define LeftRed CSLeft_R == 255 && CSLeft_G >= 29 && CSLeft_G <=49 \
        && CSLeft_B >= 29 && CSLeft_B <= 49
#define RightRed CSRight_R == 255 && CSRight_G >= 29 && CSRight_G <=49 \
        && CSRight_B >= 29 && CSRight_B <= 49


//钻石
#define LeftQing CSLeft_R >= 29 && CSLeft_R <= 49 && CSLeft_G == 255 && CSLeft_B == 255
#define RightQing CSRight_R >= 29 && CSRight_R <= 49 && CSRight_G == 255 && CSRight_B == 255


//煤炭
#define LeftHei CSLeft_R >= 29 && CSLeft_R <= 49 && CSLeft_G >= 29 && CSLeft_G <=49 \
        && CSLeft_B >= 29 && CSLeft_B <= 49
#define RightHei CSRight_R >= 29 && CSRight_R <= 49 && CSRight_G >= 29 && CSRight_G <=49 \
        && CSRight_B >= 29 && CSRight_B <= 49


//障碍物
#define frontHasBuilding US_Front <= 15
#define leftHasBuilding US_Left <= 15
#define rightHasBuilding US_Right <= 15


//出界
#define leftOut between(PositionX, 0, 10) && between(Compass, 0, 180)
#define rightOut between(PositionX, 350, 1000) && between(Compass, 270, 359)
#define bottomOut between(PositionY, 0, 10) && between(Compass, 90, 270)
#define topOut (between(PositionY, 260, 1000) && (between(Compass, 0, 90) || between(Compass, 270, 359)))


//陷阱
#define leftXianjing between(CSLeft_R, 204, 255) && between(CSLeft_G, 215, 255) && between(CSLeft_B, 0, 40)
#define rightXianjing between(CSRight_R, 204, 255) && between(CSRight_G, 215, 255) && between(CSRight_B, 0, 40)
#define xianjing (leftXianjing && rightXianjing)


//沼泽
#define leftZhaoZe between(CSLeft_R, 130, 185) && between(CSLeft_G, 135, 186) && between(CSLeft_B, 180, 255)
#define rightZhaoZe between(CSRight_R, 130, 185) && between(CSRight_G, 135, 186) && between(CSRight_B, 180, 255)
#define zhaoze (leftZhaoZe && rightZhaoZe)

//出界 新
#define leftChuJie (CSLeft_R == 206 && CSLeft_G == 217 && CSLeft_B == 255)
#define rightChuJie (CSRight_R == 206 && CSRight_G == 217 && CSRight_B == 255)
#define chuJie (leftChuJie && rightChuJie)

//空地
#define isEmpty (!(frontHasBuilding)) && (!(leftHasBuilding)) && (!(rightHasBuilding)) && (!(leftXianjing)) && (!(rightXianjing)) && \
        !(topOut) && !(bottomOut) && !(leftOut) && !(rightOut) && !(leftChuJie) && !(rightChuJie)

//函数声明
int between(int val, int start, int end);
void guanDaoLuJing(int direction, int location, int width);
void myCode();
//自定义变量
int step = 0;
int debug = 0;
//枚举
enum GuanDao_Directions{
    GuanDao_Horizontal_Left,
    GuanDao_Horizontal_Right,
    GuanDao_Vertical_Up,
    GuanDao_Vertical_Down,
};


#ifndef CSBOT_REAL

DLL_EXPORT char* GetDebugInfo(){
    char info[3000];
    sprintf(info, "step=%d;debug=%d;屏蔽区=%d", step,debug, pingBiQv);
    return info;
}

int between(int val, int start, int end){
    return val >= min(start, end) && val <= max(start, end);
}

void setWheel(int left, int right){
    WheelLeft = left;
    WheelRight = right;
}

void Game1(){
    if(Duration>0){
        Duration--;
    }else{
        myCode();
    }
}

DLL_EXPORT void OnTimer(){
    switch (CurGame)
    {
        case 9:
            break;
        case 10:
            WheelLeft=0;
            WheelRight=0;
            LED_1=0;
            break;
        case 1:
            Game1();
            break;
        default:
            break;
    }
}

void myCode(){
    //static step = 0;
    if (step == 0){
        if (leftXianjing || rightXianjing){
            setWheel(100, 100);
        }else{
            setWheel(60, 60);
        }
        if (between(PositionY, 235, 245)){
            step = 1;
        }
    }else if(step == 1){
        guanDaoLuJing(GuanDao_Horizontal_Left, 240, 10);
        if (between(PositionX, 53, 63)){
            step = 2;
        }
    }else if(step == 2){
        guanDaoLuJing(GuanDao_Vertical_Down, 58, 10);
        if (between(PositionY, 55, 65)){
            step = 3;
        }
    }else if(step == 3){
        guanDaoLuJing(GuanDao_Horizontal_Right, 60, 10);
        if (between(PositionX, 296, 306)){
            step = 4;
        }
    }else if (step == 4){
        guanDaoLuJing(GuanDao_Vertical_Up, 301, 10);
        if (between(PositionY, 235, 245)){
            step = 1;
        }
    }
}

/**
 * 管道路径 
 * 
 */
void guanDaoLuJing(int direction, int location, int width){
    if (direction == GuanDao_Horizontal_Left){
        if(!between(Compass, 70, 110)){
            if(between(Compass, 90, 270)){
                setWheel(30, -30);
            }else{
                setWheel(-30, 30);
            }
        }else{
            if (PositionY > (location + width/2) && !pingBiQv){
                setWheel(50, 65);
            }else if (PositionY < (location - width/2) && !pingBiQv){
                setWheel(65, 50);
            }else{
                setWheel(60, 60);
            }
        }
    }
    else if(direction == GuanDao_Horizontal_Right){
        if(!between(Compass, 250, 290)){
            if(between(Compass, 90, 270)){
                setWheel(-30, 30);
            }else{
                setWheel(30, -30);
            }
        }else{
            if (PositionY > (location + width/2) && !pingBiQv){
                setWheel(65, 50);
            }else if (PositionY < (location - width/2) && !pingBiQv){
                setWheel(50, 65);
            }else{
                setWheel(60, 60);
            }
        }
    }
    else if (direction == GuanDao_Vertical_Up){
        if(between(Compass, 20, 340)){
            if(Compass < 180){
                setWheel(30, -30);
            }else {
                setWheel(-30, 30);
            }
        }else{
            if (PositionX > (location + width/2) && !pingBiQv){
                setWheel(50, 65);
            }else if (PositionX < (location - width/2) && !pingBiQv){
                setWheel(65, 50);
            }else{
                setWheel(60, 60);
            }
        }
    }
    else if(direction == GuanDao_Vertical_Down){
        if(!between(Compass, 160, 200)){
            if(Compass < 180){
                setWheel(-30, 30);
            }else {
                setWheel(30, -30);
            }
        }else{
            if ((PositionX > (location + width/2)) && !pingBiQv){
                setWheel(65, 50);
            }else if (PositionX < (location - width/2) && !pingBiQv){
                setWheel(50, 65);
            }else{
                setWheel(60, 60);
            }
        }
    }
}


/**
 * 以下为系统函数
 * 
 * 
 */


DLL_EXPORT void SetGameID(int GameID)
{
    CurGame = GameID;
    bGameEnd = 0;
}


DLL_EXPORT void SetTeamID(int TeamID)
{
    AI_TeamID = TeamID;
}

DLL_EXPORT int GetGameID()
{
    return CurGame;
}

//Only Used by CsBot Dance Platform
DLL_EXPORT int IsGameEnd()
{
    return bGameEnd;
}


 
DLL_EXPORT char* GetTeamName()
{
     return "test";
}

DLL_EXPORT int GetCurAction()
{
    return CurAction;
}

//Only Used by CsBot Rescue Platform
DLL_EXPORT int GetTeleport()
{
    return Teleport;
}

//Only Used by CsBot Rescue Platform
DLL_EXPORT void SetSuperObj(int X, int Y, int num)
{
    SuperObj_X = X;
    SuperObj_Y = Y;
    SuperObj_Num = num;
}
//Only Used by CsBot Rescue Platform
DLL_EXPORT void GetSuperObj(int *X, int *Y, int *num)
{
    *X = SuperObj_X;
    *Y = SuperObj_Y;
    *num = SuperObj_Num;
}

#endif ////CSBOT_REAL

DLL_EXPORT void SetDataAI(volatile int* packet, volatile int *AI_IN)
{

    int sum = 0;

    US_Front = AI_IN[0]; packet[0] = US_Front; sum += US_Front;
    US_Left = AI_IN[1]; packet[1] = US_Left; sum += US_Left;
    US_Right = AI_IN[2]; packet[2] = US_Right; sum += US_Right;
    CSLeft_R = AI_IN[3]; packet[3] = CSLeft_R; sum += CSLeft_R;
    CSLeft_G = AI_IN[4]; packet[4] = CSLeft_G; sum += CSLeft_G;
    CSLeft_B = AI_IN[5]; packet[5] = CSLeft_B; sum += CSLeft_B;
    CSRight_R = AI_IN[6]; packet[6] = CSRight_R; sum += CSRight_R;
    CSRight_G = AI_IN[7]; packet[7] = CSRight_G; sum += CSRight_G;
    CSRight_B = AI_IN[8]; packet[8] = CSRight_B; sum += CSRight_B;
    PositionX = AI_IN[9]; packet[9] = PositionX; sum += PositionX;
    PositionY = AI_IN[10]; packet[10] = PositionY; sum += PositionY;
    Compass = AI_IN[11]; packet[11] = Compass; sum += Compass;
    Time = AI_IN[12]; packet[12] = Time; sum += Time;
    packet[13] = sum;

}
DLL_EXPORT void GetCommand(int *AI_OUT)
{
    AI_OUT[0] = WheelLeft;
    AI_OUT[1] = WheelRight;
    AI_OUT[2] = LED_1;
}