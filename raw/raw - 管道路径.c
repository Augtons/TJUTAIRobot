void guanDaoLuJing(int direction, int location, int width);

int step = 0;
int debug = 0;
//枚举
enum GuanDao_Directions{
    GuanDao_Horizontal_Left,
    GuanDao_Horizontal_Right,
    GuanDao_Vertical_Up,
    GuanDao_Vertical_Down,
};
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