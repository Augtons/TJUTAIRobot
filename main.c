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


//枚举
enum directions{
    DIRECTION_ADVANCE = 0,
    DIRECTION_LEFT = 1,
    DIRECTION_RIGHT = 2,
};
enum behaviors{
    FIND_HONE = 1,
    OUT_HOME,
    FIND_SUPER_OBJ,

    CHU_JIE,
    BI_ZHANG,
    XIAN_JING,
    FIRST_OUT_ZHAO_ZE,
};
enum GuanDao_Directions{
    GuanDao_Horizontal_Left,
    GuanDao_Horizontal_Right,
    GuanDao_Vertical_Up,
    GuanDao_Vertical_Down,
};

//我的变量
int SuperLocationX = 0;
int SuperLocationY = 0;

int red[6][2];
int qing[6][2];
int hei[6][2];

int redCount = 0;
int qingCount = 0;
int heiCount = 0;

int depositState = 0;//1 正在 2 结束
int behavior = FIRST_OUT_ZHAO_ZE;
int step = 0;
int debug = 0;



//函数声明
void mycode();

void guanDaoLuJing(int direction, int location, int width);

void behavior_FindHome();
void behavior_OutHome();
void behavior_FindSuperObj();
void behavior_ChuJie();
void behavior_BiZhang();
void behavior_XianJing();
void behavior_FirstOutZhaoZe();

int between(int val, int start, int end);
int isNear(int px, int py);
void setWheel(int left, int right);
void setWheelWithTurn(int speed, int direction, int turnSpeed);
void deposit();
void getOutOfXianjing();
void bizhang();
void fangchujie();
void getTreasure();
void isThereTreasure();


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

//出界 新
#define leftChuJie (CSLeft_R == 206 && CSLeft_G == 217 && CSLeft_B == 255)
#define rightChuJie (CSRight_R == 206 && CSRight_G == 217 && CSRight_B == 255)
#define chuJie (leftChuJie && rightChuJie)

//空地
#define isEmpty (!(frontHasBuilding)) && (!(leftHasBuilding)) && (!(rightHasBuilding)) && (!(leftXianjing)) && (!(rightXianjing)) && \
        !(topOut) && !(bottomOut) && !(leftOut) && !(rightOut) && !(leftChuJie) && !(rightChuJie)



void Game1()
{
    //出现超级宝藏
    if ((SuperObj_X != 0 || SuperObj_Y != 0) && SuperLocationX == 0 && SuperLocationY == 0){
        SuperLocationX = SuperObj_X;
        SuperLocationY = SuperObj_Y;
        behavior = FIND_SUPER_OBJ;
    }
    if(Duration>0){
        Duration--;
    }
    else {
        if (depositState == 1){ // 正在存宝（但已结束）
            depositState = 2;
            LoadedObjects = 0;

            redCount = 0;
            qingCount = 0;
            heiCount = 0;
            behavior = 0;//将找存包区的1变回0
        }
        if (behavior != 0){
            switch (behavior) {
                case FIRST_OUT_ZHAO_ZE:
                    behavior_FirstOutZhaoZe();//走出开始的沼泽
                    break;
                case FIND_HONE://满载，找存包区
                    behavior_FindHome();
                    break;
                case OUT_HOME://存包结束，离开存包区
                    behavior_OutHome();
                    break;
                case FIND_SUPER_OBJ:
                    behavior_FindSuperObj();
                    break;
                case CHU_JIE:
                    behavior_ChuJie();
                    break;
                case BI_ZHANG:
                    behavior_BiZhang();
                    break;
                case XIAN_JING:
                    behavior_XianJing();
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
            Game1();
            break;
        default:
            break;
    }
}


//todo 我的代码
void mycode(){
//    正常情况下：主行为
    isThereTreasure();
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
    if (leftChuJie || rightChuJie){
        behavior = CHU_JIE;
        return;
    }
    if (frontHasBuilding || leftHasBuilding || rightHasBuilding){
        behavior = BI_ZHANG;
        return;
    }
    if (leftXianjing || rightXianjing){
        behavior = XIAN_JING;
        return;
    }
    if (isEmpty) {
        LED_1 = 0;
        setWheel(60, 60);
    }
}

void behavior_FindHome(){
    


    behavior = 0;
}

void behavior_OutHome(){
    

    behavior = 0;
}

void behavior_FindSuperObj(){
    

    behavior = 0;

}
void behavior_ChuJie(){
    if (topOut){
        setWheel(-100, -100);
    }else{
        behavior = 0;
    }
}
void behavior_BiZhang(){
    

    behavior = 0;

}
void behavior_XianJing(){

    behavior = 0;

}

void behavior_FirstOutZhaoZe(){
    if(leftZhaoZe || rightZhaoZe){
        setWheel(100, 100);
    }else{
        behavior = 0;
    }
}



/**
 * Debug 函数
 */

DLL_EXPORT char* GetDebugInfo()
{
    char info[3000];
    sprintf(info, "WheelLeft=%d;WheelRight=%d;当前行为Behavior=%d;Duration=%d;存宝状态depositState=%d;调试参数Debug=%d;行为步骤step=%d"
            , WheelLeft, WheelRight, behavior, Duration, depositState, debug, step);
    return info;
}

/**
 * 自定义函数
 * 
 */
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

void setWheelWithTurn(int speed, int direction, int turnSpeed){
    if (direction == DIRECTION_ADVANCE){
        WheelLeft = speed;
        WheelRight = speed;
    } else if (direction == DIRECTION_LEFT){
        WheelLeft = speed - turnSpeed / 2;
        WheelRight = speed + turnSpeed / 2;
    } else if (direction == DIRECTION_RIGHT){
        WheelLeft = speed + turnSpeed / 2;
        WheelRight = speed - turnSpeed / 2;
    }
}
void deposit(){
    setWheel(0, 0);
    Duration = 55;
    LED_1 = 2;

    depositState = 1;
}

void getTreasure(){
    setWheel(0, 0);
    Duration = 50;
    LED_1 = 1;
    LoadedObjects++;
}


//预计弃用
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
void isThereTreasure(){//是否有宝藏
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
}

/**
 * ====================================================================================
 * 以下为系统函数 
 * ====================================================================================
 * ====================================================================================
 * ====================================================================================
 * ====================================================================================
 * ====================================================================================
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

#ifndef CSBOT_REAL



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