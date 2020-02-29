#include<iostream>
#include<string>
#include<map>
using namespace std;

struct Determinant
{//����ʽ
    int n;
    int d[9][9];
};

map<string,int> m;
Determinant D[20];
int num=0;

void OutputDeterminant(Determinant D)
{//�������ʽ
    for(int i=0;i<D.n;i++)
    for(int j=0;j<D.n;j++)
    {
        printf("%3d",D.d[i][j]);
        if(j==D.n-1) {cout<<endl;break;}
    }
}
void Transpose(Determinant &D)
{//ת������ʽ
    int TD[D.n][D.n];
    for(int i=0;i<D.n;i++)
    for(int j=0;j<D.n;j++)
        TD[i][j]=D.d[j][i];
    for(int i=0;i<D.n;i++)
    for(int j=0;j<D.n;j++)
        D.d[i][j]=TD[i][j];
}
void Swap(Determinant &D,int i,int j,bool l)
{//��/�л���(l�����з����У�i��jΪ������/��)
    if(l)
    {
        int a;
        for(int k=0;k<D.n;k++)
        {
            a=D.d[i][k];
            D.d[i][k]=D.d[j][k];
            D.d[j][k]=a;
        }
    }
    else
    {
        int a;
        for(int k=0;k<D.n;k++)
        {
            a=D.d[k][i];
            D.d[k][i]=D.d[k][j];
            D.d[k][j]=a;
        }
    }
}
void Add(Determinant &D,int i,int j,bool l,int k)
{//��/�����/��(l�����з����У�kΪ����)
    if(l)
    {
        for(int a=0;a<D.n;a++)
            D.d[i][a]+=k*D.d[j][a];
    }
    else
    {
        for(int a=0;a<D.n;a++)
            D.d[a][i]+=k*D.d[a][j];
    }
    
}
void Cofactor(Determinant D,int i,int j,Determinant &A)
{//��aij������ʽ
    A.n=D.n-1;
    int a=0,b=0;
    for(int x=0;x<D.n;x++)
    {
        if(x==i) continue;
        for(int y=0;y<D.n;y++)
        {
            if(y==j) continue;
            A.d[a][b]=D.d[x][y];
            b++;
        }
        a++;
        b=0;
    }
}
int Evaluation(Determinant D)
{//����ʽ��ֵ
    int e=0;
    if(D.n==2)
    {
        e=D.d[0][0]*D.d[1][1]-D.d[0][1]*D.d[1][0];
        return e;
    }
    else if(D.n==3)
    {
        e+=D.d[0][0]*D.d[1][1]*D.d[2][2];
        e+=D.d[0][1]*D.d[1][2]*D.d[2][0];
        e+=D.d[0][2]*D.d[1][0]*D.d[2][1];
        e-=D.d[0][2]*D.d[1][1]*D.d[2][0];
        e-=D.d[0][1]*D.d[1][0]*D.d[2][2];
        e-=D.d[0][0]*D.d[1][2]*D.d[2][1];
        return e;
    }
    else
    {
        int A[D.n];
        for(int i=0;i<D.n;i++)
        {
            Determinant DA;
            Cofactor(D,0,i,DA);
            A[i]=Evaluation(DA)*D.d[0][i];
            if((i+2)%2!=0) A[i]=0-A[i];
        }
        for(int i=0;i<D.n;i++) e+=A[i];
        return e;
    }
}
void GetHelp()
{//��ȡ��������
    cout<<"q/Q       :�˳�"<<endl;
    cout<<"H/h    :�鿴��������"<<endl;
    cout<<"=       :������ʽ��ֵ"<<endl;
    cout<<"Mij     :��aij������ʽ"<<endl;
    cout<<"T       :���ת������ʽ"<<endl;
    cout<<"li<->lj :��i�к͵�j�л���"<<endl;
    cout<<"ci<->cj :��i�к͵�j�л���"<<endl;
    cout<<"li+klj  :��i�м���k���ĵ�j��"<<endl;
    cout<<"ci+kcj  :��i�м���k���ĵ�j��"<<endl;
    cout<<"li-klj  :��i�м�ȥk���ĵ�j��"<<endl;
    cout<<"ci-kcj  :��i�м�ȥk���ĵ�j��"<<endl;
}
bool fun()
{//��������
    string O,ob;
    cout<<"�����������";
    cin>>O;
    if(O[0]=='T')
    {//ת��
        cout<<"�������������";
        cin>>ob;
        Transpose(D[m[ob]]);
        cout<<ob<<"��"<<endl;
        OutputDeterminant(D[m[ob]]);
    }
    else if(O=="h"||O=="H") GetHelp();
    else if(O=="q"||O=="Q") return 0;
    else if(O[0]=='M')
    {//������ʽ
        string name;
        num++;
        cout<<"�������������";
        cin>>ob;
        cout<<"����������ʽ�����֣�";
        cin>>name;
        m[name]=num;
        Cofactor(D[m[ob]],O[1]-'0'-1,O[2]-'0'-1,D[m[name]]);
        cout<<name<<"��"<<endl;
        OutputDeterminant(D[m[name]]);
    }
    else if(O[0]=='=')
    {//��ֵ
        cout<<"�������������";
        cin>>ob;
        cout<<Evaluation(D[m[ob]])<<endl;
    }
    else if(O[2]=='+')
    {//��
        cout<<"�������������";
        cin>>ob;
        if(O[0]=='l') Add(D[m[ob]],O[1]-'0'-1,O[5]-'0'-1,1,O[3]-'0');
        else Add(D[m[ob]],O[1]-'0'-1,O[5]-'0'-1,0,O[3]-'0');
        cout<<ob<<"��"<<endl;
        OutputDeterminant(D[m[ob]]);
    }
    else if(O[2]=='-')
    {//��
        cout<<"�������������";
        cin>>ob;
        if(O[0]=='l') Add(D[m[ob]],O[1]-'0'-1,O[5]-'0'-1,1,0-(O[3]-'0'));
        else Add(D[m[ob]],O[1]-'0'-1,O[5]-'0'-1,0,0-(O[3]-'0'));
        cout<<ob<<"��"<<endl;
        OutputDeterminant(D[m[ob]]);
    }
    else if(O[3]=='-')
    {//����/��
        cout<<"�������������";
        cin>>ob;
        if(O[0]=='l') Swap(D[m[ob]],O[1]-'0'-1,O[6]-'0'-1,1);
        else Swap(D[m[ob]],O[1]-'0'-1,O[6]-'0'-1,0);
        cout<<ob<<"��"<<endl;
        OutputDeterminant(D[m[ob]]);
    }
    return 1;
}

int main()
{
    m["D0"]=num;
    cout<<"����������ʽ������";
    cin>>D[0].n;
    cout<<"��ʼ¼������ʽ"<<endl;
    for(int i=0;i<D[0].n;i++)
    for(int j=0;j<D[0].n;j++)
    {
        cout<<"������a"<<i+1<<j+1<<':';
        cin>>D[0].d[i][j];
    }
    cout<<"����ʽ¼�����"<<endl;
    cout<<"D0:"<<endl;
    OutputDeterminant(D[0]);
    while(fun());
    return 0;
}