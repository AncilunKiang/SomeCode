#include<time.h>
#include<windows.h>
#include<conio.h>
#include<iostream>
#include<stdlib.h>
#include<vector>

using namespace std;

inline void gotoxy(int x, int y)//system.h太古老了，只能自己写个gotoxy函数用
{
    COORD pos = {x,y};
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);// 获取标准输出设备句柄
    SetConsoleCursorPosition(hOut, pos);//两个参数分别是指定哪个窗体，具体位置
}

inline void hide()//隐藏光标
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO CursorInfo;
    GetConsoleCursorInfo(handle, &CursorInfo);//获取控制台光标信息
    CursorInfo.bVisible = false; //隐藏控制台光标
    SetConsoleCursorInfo(handle, &CursorInfo);//设置控制台光标状态
}

class Integral//积分类
{
    public:
    int x_i=5;
    int y_i=80;
    int num=0;
    
    void add(){num++;}//加分
}I;

struct S_Node//蛇节点
{
    int x_s;
    int y_s;
    int direction;
    S_Node* next=NULL;
};

class Snake//蛇类
{
    public:
    Snake():head(){//初始化小蛇
        head.x_s=14;head.y_s=24;
        head.direction=2;
        S_Node* a=new S_Node;
        a->x_s=head.x_s;a->y_s=head.y_s+1;
        a->direction=head.direction;
        head.next=a;
    }

    S_Node head;

    bool overlapping(int x,int y);//判断是否重叠
    void grow();//生长
    void move(int d);//移动
}S;

bool Snake::overlapping(int x,int y)//判断是否重叠
{
    if(x==head.x_s&&y==head.y_s)//头部判定
    {
        for(S_Node* p=head.next;p!=NULL;p=p->next)
            if(x==p->x_s&&y==p->y_s) return true;
    }
    else//普通判定
    {
        for(S_Node* p=&head;p!=NULL;p=p->next)
            if(x==p->x_s&&y==p->y_s) return true;
    }
    return false;
}

void Snake::grow()//生长
{
    S_Node* p;
    for(p=&head;p->next!=NULL;p=p->next);
    S_Node* a=new S_Node;
    a->direction=p->direction;
    switch (p->direction)
    {
    case 0 : a->x_s=p->x_s+1;a->y_s=p->y_s;break;
    case 1 : a->x_s=p->x_s-1;a->y_s=p->y_s;break;
    case 2 : a->x_s=p->x_s;a->y_s=p->y_s+1;break;
    case 3 : a->x_s=p->x_s;a->y_s=p->y_s-1;break;
    }
    p->next=a;
}

void Snake::move(int d)//移动
{
    S_Node a,b;//中间节点
    a.direction=head.direction;a.next=head.next;a.x_s=head.x_s;a.y_s=head.y_s;//a存蛇头
    b.direction=head.next->direction;b.next=head.next->next;b.x_s=head.next->x_s;b.y_s=head.next->y_s;//b存第一节蛇身
    if(d==0)//上
    switch (head.direction)
    {
    case 0:head.x_s--;break;
    case 1:return;break;
    default:head.direction=0;head.x_s--;break;
    }
    else if(d==1)//下
    switch (head.direction)
    {
    case 0:return;break;
    case 1:head.x_s++;break;
    default:head.direction=1;head.x_s++;break;
    }
    else if(d==2)//左
    switch (head.direction)
    {
    case 2:head.y_s--;break;
    case 3:return;break;
    default:head.direction=2;head.y_s--;break;
    }
    else if(d==3)//右
    switch (head.direction)
    {
    case 2:return;break;
    case 3:head.y_s++;break;
    default:head.direction=3;head.y_s++;break;
    }

    for(S_Node* p=head.next;p!=NULL;)
    {//先保存后复制
        p->direction=a.direction;p->x_s=a.x_s;p->y_s=a.y_s;
        a.direction=b.direction;a.next=b.next;a.x_s=b.x_s;a.y_s=b.y_s;
        if(b.next!=NULL)//不是最后一个节点
        {
            b.direction=b.next->direction;b.x_s=b.next->x_s;b.y_s=b.next->y_s;b.next=b.next->next;
        }
        p=a.next;
    }
}

class Apple//苹果类
{
    public:
    Apple():x_a(),y_a(){//构造函数,初始化苹果位置
        do
        {
            srand((int)time(NULL));
            x_a=rand()%27+1;
            y_a=rand()%48+1;
        }while(S.overlapping(x_a,y_a));}

    int x_a;
    int y_a;

    void change()//随机改变苹果位置
    {
        do
        {
            srand((int)time(NULL));
            x_a=rand()%27+1;
            y_a=rand()%48+1;
        }while(S.overlapping(x_a,y_a));
    }
}A;

class Picture//画面类
{
    public:
    int width_p=100;//画面宽度
    int height_p=29;//画面高度
    int width_w=50;//墙宽
    int height_w=29;//墙高
    vector<vector<int>> CSYS{vector<vector<int>>(height_p,vector<int>(width_p,0))};//画面坐标系
    vector<int> restore;//待归零坐标

    void init() {//初始化函数
        //以下两个循环绘制墙壁
        for(int i=0;i<width_w;i++)
            CSYS[0][i]=CSYS[height_w-1][i]=1;
        for(int i=0;i<height_w;i++)
            CSYS[i][0]=CSYS[i][width_w-1]=1;
        CSYS[I.x_i][I.y_i]=2;//初始化积分显示位置
        CSYS[A.x_a][A.y_a]=3;//初始化苹果位置
        CSYS[S.head.x_s][S.head.y_s]=4;//初始化蛇头位置
        CSYS[S.head.next->x_s][S.head.next->y_s]=5;//初始化蛇身
        restore.push_back(A.x_a);//将苹果坐标加入待归零vector
        restore.push_back(A.y_a);
        //将蛇各节点坐标加入待归零vector
        restore.push_back(S.head.x_s);
        restore.push_back(S.head.y_s);
        restore.push_back(S.head.next->x_s);
        restore.push_back(S.head.next->y_s);
    }
    void print();//画面输出函数
    void refresh();//画面刷新
}P;

void Picture::print()//画面输出函数
{
    for(vector<int> a: CSYS)
        {
            for(int i : a)
                switch (i)
                {
                case 0 : cout<<" ";break;
                case 1 : cout<<"#";break;//墙壁
                case 2 : cout<<"您的积分为："<<I.num;break;//积分
                case 3 : cout<<"*";break;//苹果
                case 4 : cout<<"@";break;//蛇头
                case 5 : cout<<"*";break;//蛇身
                }
            cout<<endl;
        }
}

void Picture::refresh()//画面刷新
{
    for(auto i=restore.begin();i<=restore.end()-2;i+=2)//地图复原
        CSYS[*i][*(i+1)]=0;
    restore.clear();
    //system("cls");//太闪了
    gotoxy(0,0);//清屏
    CSYS[A.x_a][A.y_a]=3;//初始化苹果位置
    CSYS[S.head.x_s][S.head.y_s]=4;//初始化蛇头位置
    for(S_Node* p=S.head.next;p!=NULL;p=p->next)//初始化蛇身
        CSYS[p->x_s][p->y_s]=5;
    //将苹果坐标加入待归零vector
    restore.push_back(A.x_a);
    restore.push_back(A.y_a);
    //将蛇各节点坐标加入待归零vector
    for(S_Node* p=&S.head;p!=NULL;p=p->next)
    {restore.push_back(p->x_s);restore.push_back(p->y_s);}
}

class game//游戏判定类
{
    public:
    bool die()//死亡判定
    {
        if(S.head.x_s==0 || S.head.x_s==P.height_w-1 || S.head.y_s==0||S.head.y_s==P.width_w-1)//撞墙
            return true;
        else if(S.overlapping(S.head.x_s,S.head.y_s))//撞自己
            return true;
        return false;
    }
    bool eat()//吃苹果判定
    {
        if(S.head.x_s==A.x_a&&S.head.y_s==A.y_a) return true;
        return false;
    }
}G;

int main()
{
    hide();//隐藏控制台光标
    char key;//保存输入字符
    int opt;//保存输入操作
    P.init();//初始化画面
    P.print();//输出初始化界面
    while(1)//主循环
    {
        if(G.die()) break;//死亡判定
        if(G.eat())//吃苹果判定
        {
            I.add();//加分
            A.change();//生成新苹果
            S.grow();//蛇长长
        }
        if(kbhit())//是否敲击键盘
        {
            key=getch();//获取字符
            switch (key)//转换操作码
            {
            case 'w': opt=0;break;//上
            case 's': opt=1;break;//下
            case 'a': opt=2;break;//左
            case 'd': opt=3;break;//右
            case 27: key=getch(); break;//暂停
            }
            S.move(opt);//移动
            P.refresh();//刷新画面
            P.print();//输出画面
        }
        else
        {
            S.move(S.head.direction);//保持自由移动
            P.refresh();//刷新画面
            P.print();//输出画面
        }
        
    }
    cout<<"you are dead!!!"<<endl;
    system("pause");
    return 1;
}