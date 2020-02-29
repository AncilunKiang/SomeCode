#include<iostream>
#include<string>
#include<map>
using namespace std;

struct Determinant
{//行列式
    int n;
    int d[9][9];
    int c=1;
    string name="D0";
};

map<string,int> m;
Determinant D[20];
int num=0;

void OutputDeterminant(Determinant D)
{//输出行列式
    for(int i=0;i<D.n;i++)
    for(int j=0;j<D.n;j++)
    {
        printf("%3d",D.d[i][j]);
        if(j==D.n-1) {cout<<endl;break;}
    }
}
void Transpose(Determinant &D)
{//转置行列式
    int TD[D.n][D.n];
    for(int i=0;i<D.n;i++)
    for(int j=0;j<D.n;j++)
        TD[i][j]=D.d[j][i];
    for(int i=0;i<D.n;i++)
    for(int j=0;j<D.n;j++)
        D.d[i][j]=TD[i][j];
}
void Swap(Determinant &D,int i,int j,bool l)
{//行/列互换(l真则换行否则换列，i、j为待还行/列)
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
{//行/列相加/减(l真则换行否则换列，k为倍数)
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
    D.c=0-D.c;
}
void Cofactor(Determinant D,int i,int j,Determinant &A)
{//求aij的余子式
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
{//行列式求值
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
void Split(Determinant D,int i,int j,int a,int b,Determinant &A,Determinant &B)
{//aij分裂成a+b，分别放在A、B里
    A.n=B.n=D.n;
    for(int x=0;x<D.n;x++)
    for(int y=0;y<D.n;y++)
        A.d[x][y]=B.d[x][y]=D.d[x][y];
    A.d[i][j]=a;
    B.d[i][j]=b;
}
void FactorOutCoefficients(Determinant &D,int i,int k,bool l)
{//提出系数k
    if(l)
    {
        for(int a=0;a<D.n;a++)
            D.d[i][a]/=k;
    }
    else
    {
        for(int a=0;a<D.n;a++)
            D.d[a][i]/=k;
    }
    D.c*=k;
}
void GetHelp()
{//获取操作帮助
    cout<<"q/Q      :退出"<<endl;
    cout<<"H/h      :查看操作帮助"<<endl;
    cout<<"=        :求行列式的值"<<endl;
    cout<<"aij->x+y :aij分裂为x+y"<<endl;
    cout<<"Mij      :第aij的余子式"<<endl;
    cout<<"T        :求的转置行列式"<<endl;
    cout<<"li<->lj  :第i行和第j行互换"<<endl;
    cout<<"ci<->cj  :第i列和第j列互换"<<endl;
    cout<<"kli      :提出第i行的系数k"<<endl;
    cout<<"kci      :提出第i列的系数k"<<endl;
    cout<<"li+klj   :第i行加上k倍的第j行"<<endl;
    cout<<"ci+kcj   :第i列加上k倍的第j列"<<endl;
    cout<<"li-klj   :第i行减去k倍的第j行"<<endl;
    cout<<"ci-kcj   :第i列减去k倍的第j列"<<endl;

}
bool fun()
{//操作函数
    string O,ob;
    cout<<"请输入操作：";
    cin>>O;
    if(O[0]=='T')
    {//转置
        cout<<"请输入操作对象：";
        cin>>ob;
        Transpose(D[m[ob]]);
        cout<<ob<<"：  系数："<<D[m[ob]].c<<endl;
        OutputDeterminant(D[m[ob]]);
    }
    else if(O=="h"||O=="H") GetHelp();
    else if(O=="q"||O=="Q") return 0;
    else if(O[0]=='M')
    {//求余子式
        string name;
        num++;
        cout<<"请输入操作对象：";
        cin>>ob;
        cout<<"请输入余子式的名字：";
        cin>>name;
        m[name]=num;
        Cofactor(D[m[ob]],O[1]-'0'-1,O[2]-'0'-1,D[m[name]]);
        D[m[name]].name=name;
        cout<<name<<"：  系数："<<D[m[name]].c<<endl;
        OutputDeterminant(D[m[name]]);
    }
    else if(O[0]=='=')
    {//求值
        cout<<"请输入操作对象：";
        cin>>ob;
        int e=Evaluation(D[m[ob]]);
        cout<<D[m[ob]].name<<'='<<D[m[ob]].c<<'*'<<e<<'='<<e*D[m[ob]].c<<endl;
    }
    else if(O[1]=='l'||O[1]=='c')
    {//提取系数
        cout<<"请输入操作对象：";
        cin>>ob;
        if(O[1]=='l')
        FactorOutCoefficients(D[m[ob]],O[2]-'0'-1,O[0]-'0',1);
        else
        FactorOutCoefficients(D[m[ob]],O[2]-'0'-1,O[0]-'0',0);
        cout<<ob<<"：  系数："<<D[m[ob]].c<<endl;
        OutputDeterminant(D[m[ob]]);
    }
    else if(O[2]=='+')
    {//加
        cout<<"请输入操作对象：";
        cin>>ob;
        if(O[0]=='l') Add(D[m[ob]],O[1]-'0'-1,O[5]-'0'-1,1,O[3]-'0');
        else Add(D[m[ob]],O[1]-'0'-1,O[5]-'0'-1,0,O[3]-'0');
        cout<<ob<<"：  系数："<<D[m[ob]].c<<endl;
        OutputDeterminant(D[m[ob]]);
    }
    else if(O[2]=='-')
    {//减
        cout<<"请输入操作对象：";
        cin>>ob;
        if(O[0]=='l') Add(D[m[ob]],O[1]-'0'-1,O[5]-'0'-1,1,0-(O[3]-'0'));
        else Add(D[m[ob]],O[1]-'0'-1,O[5]-'0'-1,0,0-(O[3]-'0'));
        cout<<ob<<"：  系数："<<D[m[ob]].c<<endl;
        OutputDeterminant(D[m[ob]]);
    }
    else if(O[2]=='<')
    {//换行/列
        cout<<"请输入操作对象：";
        cin>>ob;
        if(O[0]=='l') Swap(D[m[ob]],O[1]-'0'-1,O[6]-'0'-1,1);
        else Swap(D[m[ob]],O[1]-'0'-1,O[6]-'0'-1,0);
        cout<<ob<<"：  系数："<<D[m[ob]].c<<endl;
        OutputDeterminant(D[m[ob]]);
    }
    else if(O[3]=='-')
    {//分裂
        string na,nb;
        cout<<"请输入操作对象：";
        cin>>ob;
        num++;
        cout<<"请输入第一个子行列式的名字：";
        cin>>na;
        m[na]=num;
        num++;
        cout<<"请输入第二个子行列式的名字：";
        cin>>nb;
        m[nb]=num;
        Split(D[m[ob]],O[1]-'0'-1,O[2]-'0'-1,O[5]-'0',O[7]-'0',D[m[na]],D[m[nb]]);
        cout<<na<<"：  系数："<<D[m[na]].c<<endl;
        OutputDeterminant(D[m[na]]);
        cout<<nb<<"：  系数："<<D[m[nb]].c<<endl;
        OutputDeterminant(D[m[nb]]);
    }
    return 1;
}

int main()
{
    m["D0"]=num;
    cout<<"请输入行列式阶数：";
    cin>>D[0].n;
    cout<<"开始录入行列式"<<endl;
    for(int i=0;i<D[0].n;i++)
    for(int j=0;j<D[0].n;j++)
    {
        cout<<"请输入a"<<i+1<<j+1<<':';
        cin>>D[0].d[i][j];
    }
    cout<<"行列式录入完成"<<endl;
    cout<<"D0:  系数：1"<<endl;
    OutputDeterminant(D[0]);
    while(fun());
    return 0;
}