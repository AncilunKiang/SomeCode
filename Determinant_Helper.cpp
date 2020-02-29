#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<set>
using namespace std;

struct Determinant
{//����ʽ
    int n;
    int d[9][9];
    int c=1;
    string name="D0";
};

vector<Determinant> D;
Determinant TD;
map<string,int> m;
set<string> namelist;

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
    int Td[D.n][D.n];
    for(int i=0;i<D.n;i++)
    for(int j=0;j<D.n;j++)
        Td[i][j]=D.d[j][i];
    for(int i=0;i<D.n;i++)
    for(int j=0;j<D.n;j++)
        D.d[i][j]=Td[i][j];
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
    D.c=0-D.c;
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
void Split(Determinant D,int i,int j,int a,int b,Determinant &A,Determinant &B)
{//aij���ѳ�a+b���ֱ����A��B��
    A.n=B.n=D.n;
    for(int x=0;x<D.n;x++)
    for(int y=0;y<D.n;y++)
        A.d[x][y]=B.d[x][y]=D.d[x][y];
    A.d[i][j]=a;
    B.d[i][j]=b;
}
void FactorOutCoefficients(Determinant &D,int i,int k,bool l)
{//���ϵ��k
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
{//��ȡ��������
    cout<<"q/Q      :�˳�"<<endl;
    cout<<"C/c      :��������"<<endl;
    cout<<"H/h      :�鿴��������"<<endl;
    cout<<"=        :������ʽ��ֵ"<<endl;
    cout<<"aij->x+y :aij����Ϊx+y"<<endl;
    cout<<"Mij      :��aij������ʽ"<<endl;
    cout<<"T        :���ת������ʽ"<<endl;
    cout<<"li<->lj  :��i�к͵�j�л���"<<endl;
    cout<<"ci<->cj  :��i�к͵�j�л���"<<endl;
    cout<<"kli      :�����i�е�ϵ��k"<<endl;
    cout<<"kci      :�����i�е�ϵ��k"<<endl;
    cout<<"li+klj   :��i�м���k���ĵ�j��"<<endl;
    cout<<"ci+kcj   :��i�м���k���ĵ�j��"<<endl;
    cout<<"li-klj   :��i�м�ȥk���ĵ�j��"<<endl;
    cout<<"ci-kcj   :��i�м�ȥk���ĵ�j��"<<endl;

}
int fun()
{//��������
    string O,ob;
    cout<<"�����������";
    cin>>O;
    if(O[0]=='T')
    {//ת��
        cout<<"�������������";
        while(1)
        {
            cin>>ob;
            if(namelist.find(ob)!=namelist.end()) break;
            cout<<"��������������������룺";
        }
        Transpose(D[m[ob]]);
        cout<<ob<<"��  ϵ����"<<D[m[ob]].c<<endl;
        OutputDeterminant(D[m[ob]]);
    }
    else if(O=="h"||O=="H") GetHelp();
    else if(O=="q"||O=="Q") return 0;
    else if(O=="C"||O=="c") return 2;
    else if(O[0]=='M')
    {//������ʽ
        string name;
        cout<<"�������������";
        while(1)
        {
            cin>>ob;
            if(namelist.find(ob)!=namelist.end()) break;
            cout<<"��������������������룺";
        }
        cout<<"����������ʽ�����֣�";
        while(1)
        {
            cin>>name;
            if(namelist.find(name)==namelist.end())
            {
                namelist.insert(name);
                break;
            }
            cout<<"�����ظ������������룺";
        }
        m[name]=D.size();
        TD.name=name;
        D.push_back(TD);
        Cofactor(D[m[ob]],O[1]-'0'-1,O[2]-'0'-1,D[m[name]]);
        cout<<name<<"��  ϵ����"<<D[m[name]].c<<endl;
        OutputDeterminant(D[m[name]]);
    }
    else if(O[0]=='=')
    {//��ֵ
        cout<<"�������������";
        while(1)
        {
            cin>>ob;
            if(namelist.find(ob)!=namelist.end()) break;
            cout<<"��������������������룺";
        }
        int e=Evaluation(D[m[ob]]);
        cout<<D[m[ob]].name<<'='<<D[m[ob]].c<<'*'<<e<<'='<<e*D[m[ob]].c<<endl;
    }
    else if(O[1]=='l'||O[1]=='c')
    {//��ȡϵ��
        cout<<"�������������";
        while(1)
        {
            cin>>ob;
            if(namelist.find(ob)!=namelist.end()) break;
            cout<<"��������������������룺";
        }
        if(O[1]=='l')
        FactorOutCoefficients(D[m[ob]],O[2]-'0'-1,O[0]-'0',1);
        else
        FactorOutCoefficients(D[m[ob]],O[2]-'0'-1,O[0]-'0',0);
        cout<<ob<<"��  ϵ����"<<D[m[ob]].c<<endl;
        OutputDeterminant(D[m[ob]]);
    }
    else if(O[2]=='+')
    {//��
        cout<<"�������������";
        while(1)
        {
            cin>>ob;
            if(namelist.find(ob)!=namelist.end()) break;
            cout<<"��������������������룺";
        }
        if(O[0]=='l') Add(D[m[ob]],O[1]-'0'-1,O[5]-'0'-1,1,O[3]-'0');
        else Add(D[m[ob]],O[1]-'0'-1,O[5]-'0'-1,0,O[3]-'0');
        cout<<ob<<"��  ϵ����"<<D[m[ob]].c<<endl;
        OutputDeterminant(D[m[ob]]);
    }
    else if(O[2]=='-')
    {//��
        cout<<"�������������";
        while(1)
        {
            cin>>ob;
            if(namelist.find(ob)!=namelist.end()) break;
            cout<<"��������������������룺";
        }
        if(O[0]=='l') Add(D[m[ob]],O[1]-'0'-1,O[5]-'0'-1,1,0-(O[3]-'0'));
        else Add(D[m[ob]],O[1]-'0'-1,O[5]-'0'-1,0,0-(O[3]-'0'));
        cout<<ob<<"��  ϵ����"<<D[m[ob]].c<<endl;
        OutputDeterminant(D[m[ob]]);
    }
    else if(O[2]=='<')
    {//����/��
        cout<<"�������������";
        while(1)
        {
            cin>>ob;
            if(namelist.find(ob)!=namelist.end()) break;
            cout<<"��������������������룺";
        }
        if(O[0]=='l') Swap(D[m[ob]],O[1]-'0'-1,O[6]-'0'-1,1);
        else Swap(D[m[ob]],O[1]-'0'-1,O[6]-'0'-1,0);
        cout<<ob<<"��  ϵ����"<<D[m[ob]].c<<endl;
        OutputDeterminant(D[m[ob]]);
    }
    else if(O[3]=='-')
    {//����
        string na,nb;
        cout<<"�������������";
        while(1)
        {
            cin>>ob;
            if(namelist.find(ob)!=namelist.end()) break;
            cout<<"��������������������룺";
        }
        cout<<"�������һ��������ʽ�����֣�";
        while(1)
        {
            cin>>na;
            if(namelist.find(na)==namelist.end())
            {
                namelist.insert(na);
                break;
            }
            cout<<"�����ظ������������룺";
        }
        m[na]=D.size();
        TD.name=na;
        D.push_back(TD);
        cout<<"������ڶ���������ʽ�����֣�";
        while(1)
        {
            cin>>nb;
            if(namelist.find(nb)==namelist.end())
            {
                namelist.insert(nb);
                break;
            }
            cout<<"�����ظ������������룺";
        }
        m[nb]=D.size();
        TD.name=nb;
        D.push_back(TD);
        Split(D[m[ob]],O[1]-'0'-1,O[2]-'0'-1,O[5]-'0',O[7]-'0',D[m[na]],D[m[nb]]);
        cout<<na<<"��  ϵ����"<<D[m[na]].c<<endl;
        OutputDeterminant(D[m[na]]);
        cout<<nb<<"��  ϵ����"<<D[m[nb]].c<<endl;
        OutputDeterminant(D[m[nb]]);
    }
    else cout<<"ָ�����";
    return 1;
}

int main()
{
    while(1)
    {
        int status;
        cout<<"����������ʽ���ƣ�";
        cin>>TD.name;
        namelist.insert(TD.name);
        m[TD.name]=D.size();
        cout<<"����������ʽ������";
        cin>>TD.n;
        cout<<"��ʼ¼������ʽ"<<endl;
        for(int i=0;i<TD.n;i++)
        for(int j=0;j<TD.n;j++)
        {
            cout<<"������a"<<i+1<<j+1<<':';
            cin>>TD.d[i][j];
        }
        D.push_back(TD);
        cout<<"����ʽ¼�����"<<endl;
        cout<<TD.name<<":  ϵ����1"<<endl;
        OutputDeterminant(D[0]);
        while(1)
        {
            status=fun();
            if(status!=1) break;
        }
        if(status==2)
        {
            D.clear();
            m.clear();
            namelist.clear();
            continue;
        }
        break;
    }
    return 0;
}