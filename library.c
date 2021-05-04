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
//我的变量
int SuperLocationX = 0;
int SuperLocationY = 0;

int red[6][2];
int qing[6][2];
int hei[6][2];

int neededX = 0;
int neededY = 0;

int redCount = 0;
int qingCount = 0;
int heiCount = 0;


int depositState = 0;//1 正在 2 结束

int behavior = 0;
enum behaviors{
    FIND_HONE = 1,
    OUT_HOME = 2,
    FIND_SUPER_OBJ = 3,
};

void mycode();
void gotoLocation(int x, int y);
void behavior_FindHome();
void behavior_OutHome();
void behavior_FindSuperObj();


int between(int val, int start, int end);

//屏蔽区
#define pingBiQv between(PositionX, 0, 1) && between(PositionY, 0, 1)


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

#define leftChuJie (CSLeft_R == 206 && CSLeft_G == 217 && CSLeft_B == 255)
#define rightChuJie (CSRight_R == 206 && CSRight_G == 217 && CSRight_B == 255)
#define chuJie (leftChuJie && rightChuJie)

//空地
#define isEmpty (!(frontHasBuilding)) && (!(leftHasBuilding)) && (!(rightHasBuilding)) && (!(leftXianjing)) && (!(rightXianjing)) && \
        !(topOut) && !(bottomOut) && !(leftOut) && !(rightOut)


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

#ifndef CSBOT_REAL

DLL_EXPORT char* GetDebugInfo()
{
    char info[3000];
    sprintf(info, "WheelLeft=%d;WheelRight=%d;Behavior=%d;Duration=%d;depositState=%d;"
            , WheelLeft, WheelRight, behavior, Duration, depositState);
    return info;
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

void Game1()
{
    //出现超级宝藏
    if ((SuperObj_X != 0 || SuperObj_Y != 0) && SuperLocationX == 0 && SuperLocationY == 0){
        SuperLocationX = SuperObj_X;
        SuperLocationY = SuperObj_Y;
    }

    if(Duration>0)
    {
        Duration--;
    }
    else{
        if (depositState == 1){
            depositState = 2;
            LoadedObjects = 0;
            behavior = 0;//将找存包区的1变回0
        }
        if (behavior != 0){
            switch (behavior) {
                case FIND_HONE://满载，找存包区
                    behavior_FindHome();
                    break;
                case OUT_HOME://存包结束，离开存包区
                    behavior_OutHome();
                    break;
            }
        } else{
            mycode();
        }
    }

}


DLL_EXPORT void OnTimer()
{
    switch (CurGame)
    {
        case 9:
            break;
        case 10:
            WheelLeft=0;
            WheelRight=0;
            //LED_1=0;
            break;
        case 1:
            //gotoLocation(56, 178);
            Game1();
            break;
        default:
            break;
    }
}

int between(int val, int start, int end){
    return val >= min(start, end) && val <= max(start, end);
}

int isNear(int px, int py){
    return abs(PositionY - py) <= 5 || abs(PositionX - px) <= 5;
}

void setWheel(int left, int right){
    WheelLeft = left;
    WheelRight = right;
}
void deposit(){
    setWheel(0, 0);
    Duration = 55;
    LED_1 = 2;

    redCount = 0;
    qingCount = 0;
    heiCount = 0;
    depositState = 1;
}
void getTreasure(){
    setWheel(0, 0);
    Duration = 50;
    LED_1 = 1;
    LoadedObjects++;
}
//todo 重写，范围太小，改成管道路径，或者弃用
void turnTo270(){
    if (Compass > 267 && Compass < 273)
    {
        WheelLeft = 0;
        WheelRight = 0;
        Duration = 0;
    } else if (between(Compass, 90, 270)){
        if (between(abs(Compass - 270), 180, 120)){
            setWheel(-30, 30);
        } else if (between(abs(Compass - 270), 120, 60)){
            setWheel(-20, 20);
        } else if (between(abs(Compass - 270), 60, 20)){
            setWheel(-8, 8);
        } else{
            setWheel(-3, 3);
        }
    } else{
        if (between(Compass, 90, 30)){
            setWheel(30, -30);
        } else if (Compass > 330 || Compass < 30){
            setWheel(20, -20);
        } else if (between(Compass, 330, 290)){
            setWheel(8, -8);
        } else{
            setWheel(3, -3);
        }
    }
}
void turnTo90(){
    if (Compass > 87 && Compass < 93)
    {
        WheelLeft = 0;
        WheelRight = 0;
        Duration = 0;
    } else if (between(Compass, 90, 270)){
        if (between(abs(Compass - 90), 180, 120)){
            setWheel(30, -30);
        } else if (between(abs(Compass - 90), 120, 60)){
            setWheel(20, -20);
        } else if (between(abs(Compass - 90), 60, 20)){
            setWheel(8, -8);
        } else{
            setWheel(3, -3);
        }
    } else{
        if (between(Compass, 270, 330)){
            setWheel(-30, 30);
        } else if (Compass > 330 || Compass < 30){
            setWheel(-20, 20);
        } else if (between(Compass, 30, 70)){
            setWheel(-8, 8);
        } else{
            setWheel(-3, 3);
        }
    }
}
void turnTo180(){
    if (Compass > 177 && Compass < 183)
    {
        WheelLeft = 0;
        WheelRight = 0;
        Duration = 0;
    } else if (Compass > 180){
        if (between(abs(180 - Compass), 180, 120)){
            setWheel(30, -30);
        } else if (between(abs(180 - Compass), 120, 60)){
            setWheel(20, -20);
        } else if (between(abs(180 - Compass), 60, 20)){
            setWheel(8, -8);
        } else{
            setWheel(3, -3);
        }
    } else{
        if (between(abs(180 - Compass), 180, 120)){
            setWheel(-30, 30);
        } else if (between(abs(180 - Compass), 120, 60)){
            setWheel(-20, 20);
        } else if (between(abs(180 - Compass), 60, 20)){
            setWheel(-8, 8);
        } else{
            setWheel(-3, 3);
        }
    }
}
void turnTo0(){
    if (Compass < 3 || Compass>357)
    {
        WheelLeft = 0;
        WheelRight = 0;
        Duration = 0;
    } else if (Compass > 180){
        if (between(abs(360 - Compass), 180, 120)){
            setWheel(-30, 30);
        } else if (between(abs(360 - Compass), 120, 60)){
            setWheel(-20, 20);
        } else if (between(abs(360 - Compass), 60, 20)){
            setWheel(-8, 8);
        } else{
            setWheel(-3, 3);
        }
    } else {
        if (between(Compass, 180, 120)){
            setWheel(30, -30);
        } else if (between(Compass, 120, 60)){
            setWheel(20, -20);
        } else if (between(Compass, 60, 20)){
            setWheel(8, -8);
        } else{
            setWheel(3, -3);
        }
    }
}

//todo 重写goto方法
void gotoPositionX(int x){
    if (abs(x - PositionX) > 5){
        if (PositionX < x){
            if (!between(Compass, 267, 273)){
                turnTo270();
            } else {
                setWheel(60, 60);
            }
        } else {
            if (!between(Compass, 93, 87)){
                turnTo90();
            } else{
                setWheel(60, 60);
            }
        }
    } else{
        setWheel(0, 0);
    }
}
void gotoPositionY(int y){
    if (abs(y - PositionX) > 5){
        if (PositionY < y){
            if (!(Compass >= 357 || Compass <= 3)){
                turnTo0();
            } else{
                setWheel(60, 60);
            }
        } else{
            if (!between(Compass, 183, 177)){
                turnTo180();
            } else setWheel(60, 60);
        }
    } else{
        setWheel(0, 0);
    }
}
void gotoLocation(int x, int y){
    if (abs(y - PositionY) > 5){
        gotoPositionY(y);
    } else if (abs(x - PositionX) > 5){
        gotoPositionX(x);
    }
}

void getOutOfXianjing(){
    if (xianjing){
        setWheel(-60, 60);
    } else if (leftXianjing){
        setWheel(60, -60);
    } else if (rightXianjing){
        setWheel(-60, 60);
    }
}
void bizhang(){
    if (frontHasBuilding){//前边有
        if (leftHasBuilding && rightHasBuilding){
            setWheel(-60, 60);
        } else if (leftHasBuilding){
            setWheel(60, -60);
        } else {
            setWheel(-60, 60);
        }
    } else if (leftHasBuilding && rightHasBuilding){
        if (US_Left < US_Right){ //障碍物在左边近
            setWheel(55, 50);
        } else if (US_Left > US_Right){ //障碍物在右边近
            setWheel(50, 55);
        } else{
            setWheel(55, 55);
        }
    } else if (leftHasBuilding){
        setWheel(60, 45);
    } else if (rightHasBuilding){
        setWheel(45, 60);
    }
}

void fangchujie(){
    if (leftChuJie){
        setWheel(30, -30);
    }
    if (rightChuJie){
        setWheel(-30, 30);
    } else{
        if (PositionX < 178){
            if (PositionY > 126){
                setWheel(-60, 60);
            } else{
                setWheel(60, -60);
            }

        } else{
            if (PositionY > 126){
                setWheel(60, -60);
            } else{
                setWheel(-60, 60);
            }
        }
    }
}

//todo 我的代码
void mycode(){
//    正常情况下：寻宝，捡宝，避障，躲陷阱
    if ((LeftRed || RightRed) && LoadedObjects < 6){
        getTreasure();
        redCount += 1;
        if (LoadedObjects >= 6){
            //todo 满载后，启动找存包区behavior
            behavior = FIND_HONE;
        }
        return;
    } else if ((LeftQing || RightQing) && LoadedObjects < 6){
        getTreasure();
        qingCount += 1;
        if (LoadedObjects >= 6){
            //todo 满载后，启动找存包区behavior
            behavior = FIND_HONE;
        }
        return;
    } else if ((LeftHei || RightHei) && LoadedObjects < 6){
        getTreasure();
        heiCount += 1;
        if (LoadedObjects >= 6){
            //todo 满载后，启动找存包区behavior
            behavior = FIND_HONE;
        }
        return;
    }
    if (isDeposit && LoadedObjects >= 6){
        if (depositState == 0){
            depositState = 1;
            deposit();
        } else if (depositState == 2){
            behavior = OUT_HOME;
            //todo behavior_离开存包区
            depositState = 0;
        }
    }
    if (!(pingBiQv)){
        fangchujie();
    }
    if (isEmpty) {
        LED_1 = 0;
        setWheel(60, 60);
    } else {
        if (frontHasBuilding || leftHasBuilding || rightHasBuilding){
            bizhang();
        }
        if (leftXianjing || rightXianjing){
            getOutOfXianjing();
        }
    }
}

void behavior_FindHome(){
    static int flag = 0;
    static int px = 0;
    static int py = 0;
    if (!(pingBiQv)){

    } else{
        mycode();
    }
}

void behavior_OutHome(){

}

void behavior_FindSuperObj(){

}