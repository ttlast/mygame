#ifndef PEOPLE_H
#define PEOPLE_H

enum MoveState{
    MOVE_UP,MOVE_DOWN,MOVE_LEFT,MOVE_RIGHT
};

typedef struct Pos
{
    int x,y;
}Pos;

class People
{
public:
    People();

    void initPeople(Pos pos,Pos tar);
    void move();
    void changeDirect(MoveState dir);
    MoveState getMoveState();
    Pos getPeoplenewPos();
    void resetPeoplepos()
    {
        people_pos = people_start;
    }

    Pos getPeoplePos()
    {
        return people_pos;
    }
    Pos getPeopletar()
    {
        return people_tar;
    }

    bool iswin();

private:
    Pos people_start,people_tar;
    Pos people_pos;
    MoveState people_dir;

    bool win;
};

#endif // PEOPLE_H
