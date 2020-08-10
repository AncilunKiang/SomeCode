#include<time.h>
#include<windows.h>
#include<conio.h>
#include<iostream>
#include<stdlib.h>
#include<vector>

using namespace std;

inline void gotoxy(int x, int y)//system.h̫�����ˣ�ֻ���Լ�д��gotoxy������
{
    COORD pos = {x,y};
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);// ��ȡ��׼����豸���
    SetConsoleCursorPosition(hOut, pos);//���������ֱ���ָ���ĸ����壬����λ��
}

inline void hide()//���ع��
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO CursorInfo;
    GetConsoleCursorInfo(handle, &CursorInfo);//��ȡ����̨�����Ϣ
    CursorInfo.bVisible = false; //���ؿ���̨���
    SetConsoleCursorInfo(handle, &CursorInfo);//���ÿ���̨���״̬
}

class Integral//������
{
    public:
    int x_i=5;
    int y_i=80;
    int num=0;
    
    void add(){num++;}//�ӷ�
}I;

struct S_Node//�߽ڵ�
{
    int x_s;
    int y_s;
    int direction;
    S_Node* next=NULL;
};

class Snake//����
{
    public:
    Snake():head(){//��ʼ��С��
        head.x_s=14;head.y_s=24;
        head.direction=2;
        S_Node* a=new S_Node;
        a->x_s=head.x_s;a->y_s=head.y_s+1;
        a->direction=head.direction;
        head.next=a;
    }

    S_Node head;

    bool overlapping(int x,int y);//�ж��Ƿ��ص�
    void grow();//����
    void move(int d);//�ƶ�
}S;

bool Snake::overlapping(int x,int y)//�ж��Ƿ��ص�
{
    if(x==head.x_s&&y==head.y_s)//ͷ���ж�
    {
        for(S_Node* p=head.next;p!=NULL;p=p->next)
            if(x==p->x_s&&y==p->y_s) return true;
    }
    else//��ͨ�ж�
    {
        for(S_Node* p=&head;p!=NULL;p=p->next)
            if(x==p->x_s&&y==p->y_s) return true;
    }
    return false;
}

void Snake::grow()//����
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

void Snake::move(int d)//�ƶ�
{
    S_Node a,b;//�м�ڵ�
    a.direction=head.direction;a.next=head.next;a.x_s=head.x_s;a.y_s=head.y_s;//a����ͷ
    b.direction=head.next->direction;b.next=head.next->next;b.x_s=head.next->x_s;b.y_s=head.next->y_s;//b���һ������
    if(d==0)//��
    switch (head.direction)
    {
    case 0:head.x_s--;break;
    case 1:return;break;
    default:head.direction=0;head.x_s--;break;
    }
    else if(d==1)//��
    switch (head.direction)
    {
    case 0:return;break;
    case 1:head.x_s++;break;
    default:head.direction=1;head.x_s++;break;
    }
    else if(d==2)//��
    switch (head.direction)
    {
    case 2:head.y_s--;break;
    case 3:return;break;
    default:head.direction=2;head.y_s--;break;
    }
    else if(d==3)//��
    switch (head.direction)
    {
    case 2:return;break;
    case 3:head.y_s++;break;
    default:head.direction=3;head.y_s++;break;
    }

    for(S_Node* p=head.next;p!=NULL;)
    {//�ȱ������
        p->direction=a.direction;p->x_s=a.x_s;p->y_s=a.y_s;
        a.direction=b.direction;a.next=b.next;a.x_s=b.x_s;a.y_s=b.y_s;
        if(b.next!=NULL)//�������һ���ڵ�
        {
            b.direction=b.next->direction;b.x_s=b.next->x_s;b.y_s=b.next->y_s;b.next=b.next->next;
        }
        p=a.next;
    }
}

class Apple//ƻ����
{
    public:
    Apple():x_a(),y_a(){//���캯��,��ʼ��ƻ��λ��
        do
        {
            srand((int)time(NULL));
            x_a=rand()%27+1;
            y_a=rand()%48+1;
        }while(S.overlapping(x_a,y_a));}

    int x_a;
    int y_a;

    void change()//����ı�ƻ��λ��
    {
        do
        {
            srand((int)time(NULL));
            x_a=rand()%27+1;
            y_a=rand()%48+1;
        }while(S.overlapping(x_a,y_a));
    }
}A;

class Picture//������
{
    public:
    int width_p=100;//������
    int height_p=29;//����߶�
    int width_w=50;//ǽ��
    int height_w=29;//ǽ��
    vector<vector<int>> CSYS{vector<vector<int>>(height_p,vector<int>(width_p,0))};//��������ϵ
    vector<int> restore;//����������

    void init() {//��ʼ������
        //��������ѭ������ǽ��
        for(int i=0;i<width_w;i++)
            CSYS[0][i]=CSYS[height_w-1][i]=1;
        for(int i=0;i<height_w;i++)
            CSYS[i][0]=CSYS[i][width_w-1]=1;
        CSYS[I.x_i][I.y_i]=2;//��ʼ��������ʾλ��
        CSYS[A.x_a][A.y_a]=3;//��ʼ��ƻ��λ��
        CSYS[S.head.x_s][S.head.y_s]=4;//��ʼ����ͷλ��
        CSYS[S.head.next->x_s][S.head.next->y_s]=5;//��ʼ������
        restore.push_back(A.x_a);//��ƻ��������������vector
        restore.push_back(A.y_a);
        //���߸��ڵ�������������vector
        restore.push_back(S.head.x_s);
        restore.push_back(S.head.y_s);
        restore.push_back(S.head.next->x_s);
        restore.push_back(S.head.next->y_s);
    }
    void print();//�����������
    void refresh();//����ˢ��
}P;

void Picture::print()//�����������
{
    for(vector<int> a: CSYS)
        {
            for(int i : a)
                switch (i)
                {
                case 0 : cout<<" ";break;
                case 1 : cout<<"#";break;//ǽ��
                case 2 : cout<<"���Ļ���Ϊ��"<<I.num;break;//����
                case 3 : cout<<"*";break;//ƻ��
                case 4 : cout<<"@";break;//��ͷ
                case 5 : cout<<"*";break;//����
                }
            cout<<endl;
        }
}

void Picture::refresh()//����ˢ��
{
    for(auto i=restore.begin();i<=restore.end()-2;i+=2)//��ͼ��ԭ
        CSYS[*i][*(i+1)]=0;
    restore.clear();
    //system("cls");//̫����
    gotoxy(0,0);//����
    CSYS[A.x_a][A.y_a]=3;//��ʼ��ƻ��λ��
    CSYS[S.head.x_s][S.head.y_s]=4;//��ʼ����ͷλ��
    for(S_Node* p=S.head.next;p!=NULL;p=p->next)//��ʼ������
        CSYS[p->x_s][p->y_s]=5;
    //��ƻ��������������vector
    restore.push_back(A.x_a);
    restore.push_back(A.y_a);
    //���߸��ڵ�������������vector
    for(S_Node* p=&S.head;p!=NULL;p=p->next)
    {restore.push_back(p->x_s);restore.push_back(p->y_s);}
}

class game//��Ϸ�ж���
{
    public:
    bool die()//�����ж�
    {
        if(S.head.x_s==0 || S.head.x_s==P.height_w-1 || S.head.y_s==0||S.head.y_s==P.width_w-1)//ײǽ
            return true;
        else if(S.overlapping(S.head.x_s,S.head.y_s))//ײ�Լ�
            return true;
        return false;
    }
    bool eat()//��ƻ���ж�
    {
        if(S.head.x_s==A.x_a&&S.head.y_s==A.y_a) return true;
        return false;
    }
}G;

int main()
{
    hide();//���ؿ���̨���
    char key;//���������ַ�
    int opt;//�����������
    P.init();//��ʼ������
    P.print();//�����ʼ������
    while(1)//��ѭ��
    {
        if(G.die()) break;//�����ж�
        if(G.eat())//��ƻ���ж�
        {
            I.add();//�ӷ�
            A.change();//������ƻ��
            S.grow();//�߳���
        }
        if(kbhit())//�Ƿ��û�����
        {
            key=getch();//��ȡ�ַ�
            switch (key)//ת��������
            {
            case 'w': opt=0;break;//��
            case 's': opt=1;break;//��
            case 'a': opt=2;break;//��
            case 'd': opt=3;break;//��
            case 27: key=getch(); break;//��ͣ
            }
            S.move(opt);//�ƶ�
            P.refresh();//ˢ�»���
            P.print();//�������
        }
        else
        {
            S.move(S.head.direction);//���������ƶ�
            P.refresh();//ˢ�»���
            P.print();//�������
        }
        
    }
    cout<<"you are dead!!!"<<endl;
    system("pause");
    return 1;
}