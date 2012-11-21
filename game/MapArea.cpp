#include "MapArea.h"
int sign[MAP_COL][MAP_ROW][MAX];  //地图搜索定义
int dir[4][2] = {{0,-1},{0,1},{-1,0},{1,0}};
int key[] = {1,2,4,8,16,32,64,128,256,512};  //10把钥匙
MoveState Road[MAP_ROW*MAP_COL*MAX];
CNode st,em;

MapArea::MapArea(QWidget *parent) :
    QWidget(parent)
{
    QPalette p = palette();
    p.setColor(QPalette::Window,Qt::white);
    setPalette(p);
    setAutoFillBackground(true);
    // 小图标20

    img_people = new QImage(":/images/peopleall.png");
    img_wall = new QImage(":/images/wall.png");
    img_tar = new QImage(":/images/tar.png");

    img_key[0] = new QImage(":/images/key0.png");
    img_key[1] = new QImage(":/images/key1.png");
    img_key[2] = new QImage(":/images/key2.png");
    img_key[3] = new QImage(":/images/key3.png");
    img_key[4] = new QImage(":/images/key4.png");

    img_door[0] = new QImage(":/images/door0.png");
    img_door[1] = new QImage(":/images/door1.png");
    img_door[2] = new QImage(":/images/door2.png");
    img_door[3] = new QImage(":/images/door3.png");
    img_door[4] = new QImage(":/images/door4.png");

    //大图标30
/*
    img_people = new QImage(":/images/peopleall3.png");
    img_wall = new QImage(":/images/wall3.png");
    img_tar = new QImage(":/images/tar3.png");

    img_key[0] = new QImage(":/images/key30.png");
    img_key[1] = new QImage(":/images/key31.png");
    img_key[2] = new QImage(":/images/key32.png");
    img_key[3] = new QImage(":/images/key33.png");
    img_key[4] = new QImage(":/images/key34.png");

    img_door[0] = new QImage(":/images/door30.png");
    img_door[1] = new QImage(":/images/door31.png");
    img_door[2] = new QImage(":/images/door32.png");
    img_door[3] = new QImage(":/images/door33.png");
    img_door[4] = new QImage(":/images/door34.png");
*/
    setMinimumSize(MAP_COL*CELL_WIDTH,MAP_ROW*CELL_WIDTH);
    setMaximumSize(MAP_COL*CELL_WIDTH,MAP_ROW*CELL_WIDTH);

    initGame();
    //startGame();
}


void MapArea::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    int i,j;
    QRect cell_rect,img_rect;
    for(i = 0;i < MAP_ROW;i ++)
    {
        for(j = 0;j < MAP_COL;j ++)
        {
            QPoint cell_topleft = QPoint(CELL_WIDTH*j, CELL_WIDTH*i);
            QRect img_rect = QRect(QPoint(0,0),QSize(CELL_WIDTH,CELL_WIDTH));
            if(map[j][i] == WALL)
            {
                p.drawImage(cell_topleft, *img_wall, img_rect);
            }else if(map[j][i] == TAR)
            {
                p.drawImage(cell_topleft, *img_tar, img_rect);
            }else if(map[j][i] >= KEY && map[j][i] <= KEY2)
            {
                p.drawImage(cell_topleft,*img_key[map[j][i]-KEY],img_rect);
            }else if(map[j][i] >= DOOR && map[j][i] <= DOOR2)
            {
                p.drawImage(cell_topleft,*img_door[map[j][i]-DOOR],img_rect);
            }
        }
    }
    drawPeople(*img_people);
}

void MapArea::drawPeople(QImage img)
{
    QRect cell_rect,img_rect;
    QPainter p(this);
    int img_row,img_col;
    MoveState state = tt.getMoveState();
    switch(state)
    {
    case MOVE_UP:
        img_row = 3;
        img_col = people_col%4;
        //img_col = 0;
        break;
    case MOVE_DOWN:
        img_row = 0;
        img_col = people_col%4;
        //img_col = 0;
        break;
    case MOVE_LEFT:
        img_row = 1;
        img_col = people_col%4;
        //img_col = 0;
        break;
    default:
        img_row = 2;
        img_col = people_col%4;
        //img_col = 0;
        break;
    }
    Pos peo_pos = tt.getPeoplePos();
    cell_rect = QRect(QPoint(CELL_WIDTH*peo_pos.x,CELL_WIDTH*peo_pos.y),
                      QSize(CELL_WIDTH,CELL_WIDTH));
    img_rect = QRect(QPoint(CELL_WIDTH*img_col,CELL_WIDTH*img_row),
                     QSize(CELL_WIDTH,CELL_WIDTH));
    p.drawImage(cell_rect,*img_people,img_rect);
}

void MapArea::initGame()
{
    int i,j;
    people_col = 0;
    Pos s,e;
    s.x = 1;
    s.y = 1;
    e.x = MAP_COL - 2;
    e.y = MAP_ROW - 2;
    map[s.x][s.y] = STAR;
    map[e.x][e.y] = TAR;
    tt.initPeople(s,e);
    gamestart = false;
    QString sn;
    sn = "MAP/map2.map";
    QFile file(sn);
    if(!file.open(QIODevice::ReadWrite))
    {
        for(i = 0;i < MAP_ROW;i ++)
            for(j = 0;j < MAP_COL;j ++)
            {
                if(i == 0 || i == MAP_ROW-1 || j == 0 || j == MAP_COL - 1) map[j][i] = WALL;
                else  map[j][i] = NOTHING;
                back_map[j][i] = map[j][i];
            }
    }else{
        QTextStream stream(&file);
        int row,col;

        stream >> start.x >> start.y;
        stream >> tar.x >> tar.y;
        for(row = 0;row < MAP_ROW;row ++)
            for(col = 0;col < MAP_COL;col ++)
            {
                stream >> map[col][row];
                back_map[col][row] = map[col][row];
            }
        tt.initPeople(start,tar);
        file.close();
    }
}

void MapArea::startGame()
{
    if(gamestart == false)
    {
        gamestart = true;
        gamepause = false;
        gameover = false;
        int i,j;
        for(i = 0;i < MAP_ROW;i ++)
            for(j = 0;j < MAP_COL;j ++)
                map[j][i] = back_map[j][i];
        tt.resetPeoplepos();
        step = 0;
        roadok = bfs();
        if(roadok != -1)
        {
            dfs(em);
            time_no = startTimer(500);
        }else
        {
            gamestart = false;
            QString title,message;
            title = title.fromLocal8Bit("提示");
            message = message.fromLocal8Bit("这个地图没法走到终点");
            killTimer(time_no);
            QMessageBox::information(this,title,message);
        }
    }
}

void MapArea::pauseGame()
{
    if(gamestart)
    {
        if(gamepause)
        {
            gamepause = false;
            time_no = startTimer(500);
        }else
        {
            gamepause = true;
            killTimer(time_no);
        }
    }
}


void MapArea::changeDirect(int key)
{
    Pos new_pos;
    switch(key)
    {
    case Qt::Key_Up:
        tt.changeDirect(MOVE_UP);
        new_pos = tt.getPeoplenewPos();
        if(map[new_pos.y][new_pos.x] != WALL)
            tt.move();
        break;
    case Qt::Key_Down:
        tt.changeDirect(MOVE_DOWN);
        new_pos = tt.getPeoplenewPos();
        if(map[new_pos.y][new_pos.x] != WALL)
            tt.move();
        break;
    case Qt::Key_Left:
        tt.changeDirect(MOVE_LEFT);
        new_pos = tt.getPeoplenewPos();
        if(map[new_pos.y][new_pos.x] != WALL)
            tt.move();
        break;
    case Qt::Key_Right:
        tt.changeDirect(MOVE_RIGHT);
        new_pos = tt.getPeoplenewPos();
        if(map[new_pos.y][new_pos.x] != WALL)
            tt.move();
        break;
    }
    update();
}

bool MapArea::isGameover()
{
    return gameover;
}

void MapArea::getKey(int row, int col)
{
    if(map[row][col] == KEY)
        map[row][col] = NOTHING;
}

void MapArea::openDoor(int row, int col)
{
    if(map[row][col] == DOOR)
        map[row][col] = NOTHING;
}

void MapArea::timerEvent(QTimerEvent *)
{
    if(tt.iswin())
    {
        QString title,message;
        title = title.fromLocal8Bit("提示");
        message = message.fromLocal8Bit("已经到达终点");
        gamestart = false;
        gameover = true;
        killTimer(time_no);
        QMessageBox::information(this,title,message);
    }else
    {
        //tt.move();
        if(step != 0)
        {
            if(Road[step] == Road[step-1]) people_col ++;
            else people_col = 0;
        }
        /*
          增加人物行走动态
        */
        tt.changeDirect(Road[step]);
        tt.move();
        Pos tmp= tt.getPeoplePos();
        map[tmp.x][tmp.y] = NOTHING;
        step ++;
        update();
    }
}
bool MapArea::safe(int x,int y)
{
    if(x >= 0 && x < MAP_COL &&y >= 0 &&  y < MAP_ROW && map[x][y] != WALL)
        return true;
    return false;
}


//主要找路程序，状态压缩 + bfs，
int MapArea::bfs()
{
    int i,x,y,index;

    memset(sign,-1,sizeof(sign));

    CNode mq,tm;
    Pos tar;
    tar = tt.getPeoplePos();
    st.x = tar.x; st.y = tar.y;
    sign[st.x][st.y][0] = 0;
    tar = tt.getPeopletar();

    QQueue<CNode> q;
    st.key = st.ncount = 0;

    q.push_back(st);
    while(!q.empty())
    {
        tm = q.front();q.pop_front();
        //if(tm.ncount >= t) break;
        if(tm.x == tar.x && tm.y == tar.y)
        {
            //printf("%d\n",tm.ncount);
            em = tm;
            return tm.ncount;
        }
        for(i = 0;i < 4;i ++)
        {
            x = tm.x+dir[i][0];
            y = tm.y+dir[i][1];
            if(safe(x,y)&&(sign[x][y][tm.key] == -1))
            {
                if(map[x][y] >= DOOR && map[x][y]  <= DOOR2)
                {
                    index = map[x][y] - DOOR;
                    if((tm.key&key[index]) != 0)
                    {
                        mq.x = x; mq.y = y; mq.key = tm.key; mq.ncount = tm.ncount+1;
                        q.push_back(mq);
                        sign[x][y][mq.key] = mq.ncount;
                    }
                }else if(map[x][y] >= KEY && map[x][y] <= KEY2)
                {
                    index = map[x][y] - KEY;
                    if(!(tm.key&key[index])) mq.key = tm.key+key[index];
                    else mq.key = tm.key;
                    mq.x = x; mq.y = y; mq.ncount = tm.ncount+1;
                    if(sign[x][y][mq.key] == -1)
                    {
                        sign[x][y][mq.key] = mq.ncount;
                        q.push_back(mq);
                    }
                }else
                {
                    mq.x = x;mq.y = y;mq.key = tm.key;mq.ncount = tm.ncount+1;
                    q.push_back(mq);
                    sign[x][y][mq.key] = mq.ncount;
                }
            }
        }
    }
    return -1;  //无法到达目的地
}

MoveState MapArea::DirZ(int dir)
{
    if(dir == 0) return MOVE_DOWN;
    else if(dir == 1) return MOVE_UP;
    else if(dir == 2) return MOVE_RIGHT;
    else if(dir == 3) return MOVE_LEFT;
}

//根据bfs寻找到路径，dfs从终点找起点的最短路径。
void MapArea::dfs(CNode tm)
{
    int i,x,y,ckey = 0;
    bool f;
    f = false;
    CNode qm;
    if(tm.ncount == 0) return ;
    if(back_map[tm.x][tm.y] >= KEY && back_map[tm.x][tm.y] <= KEY2)
    {
        if(tm.key&key[back_map[tm.x][tm.y]-KEY])
            ckey = tm.key - key[back_map[tm.x][tm.y]-KEY];
    }
    for(i = 0;i < 4;i ++)
    {
        x = tm.x+dir[i][0];
        y = tm.y+dir[i][1];
        if(safe(x,y))
        {
            if(sign[x][y][tm.key] == tm.ncount - 1)
            {
                qm.key = tm.key;  qm.x = x; qm.y = y; qm.ncount = tm.ncount - 1;
                Road[tm.ncount-1] = DirZ(i);
                f = true;
                dfs(qm);
                break;
            }
        }
    }
    if(!f)
    {
        for(i = 0;i < 4;i ++)
        {
            x = tm.x+dir[i][0];
            y = tm.y+dir[i][1];
            if(safe(x,y))
            {
                if(sign[x][y][ckey] == tm.ncount - 1)
                {
                    qm.key = ckey;  qm.x = x; qm.y = y; qm.ncount = tm.ncount - 1;
                    Road[tm.ncount-1] = DirZ(i);
                    f = true;
                    dfs(qm);
                    break;
                }
            }
        }
    }
}

void MapArea::ReadMap()
{
    QString s = QFileDialog::getOpenFileName(
                this,
                "open GameMap",
                "/",
                "all(*.*);;Map files(*.map);;txt files(*.txt)"
                );
    QFile file(s);
    if(!file.open(QIODevice::ReadWrite))
    {
        return ;
    }
    QTextStream stream(&file);
    QString line;
    int row,col;

    stream >> start.x >> start.y;
    stream >> tar.x >> tar.y;
    for(row = 0;row < MAP_ROW;row ++)
        for(col = 0;col < MAP_COL;col ++)
        {
            stream >> map[col][row];
            back_map[col][row] = map[col][row];
        }
    if(gamestart == true)
    {
        gamestart = false;
        killTimer(time_no);
    }
    tt.initPeople(start,tar);
    file.close();
    update();
}
