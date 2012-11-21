#include "People.h"

People::People()
{
}

// 初始化位置和目标位置
void People::initPeople(Pos pos,Pos tar)
{
    people_pos.x = pos.x;
    people_pos.y = pos.y;

    people_start = people_pos;

    people_tar.x = tar.x;
    people_tar.y = tar.y;

    people_dir = MOVE_DOWN;

    win = false;
}

Pos People::getPeoplenewPos()
{
    Pos new_pos;
    //new_pos = people_pos;
    switch(people_dir)
    {
    case MOVE_UP:
        new_pos.x = people_pos.x;
        new_pos.y = people_pos.y - 1;
        break;
    case MOVE_DOWN:
        new_pos.x = people_pos.x;
        new_pos.y = people_pos.y + 1;
        break;
    case MOVE_LEFT:
        new_pos.x = people_pos.x - 1;
        new_pos.y = people_pos.y;
        break;
    case MOVE_RIGHT:
        new_pos.x = people_pos.x + 1;
        new_pos.y = people_pos.y;
        break;
    }
    return new_pos;
}

void People::move()
{
    people_pos = getPeoplenewPos();
}

void People::changeDirect(MoveState dir)
{
    people_dir = dir;
}

MoveState People::getMoveState()
{
    return people_dir;
}

bool People::iswin()
{
    if(people_pos.x == people_tar.x && people_pos.y == people_tar.y)
        return true;
    return false;
}
