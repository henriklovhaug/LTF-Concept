#include<iostream>
#include<vector>
#include"player.h"

class Player
{
private:
    int x = 0;
    int y = 0;
    int* ptrX = &x;
    int* prtY = &y;
public:
    Player(int x){
        setX(x);
    };
    ~Player();
    void setX(int x){
        this->x = x;
    }
    int getX(){
        return x;
    }
};