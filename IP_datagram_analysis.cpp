#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

string b;
int x[]={1,2,4,8,16,32,64,128,256,512};

void C2B(char a)//十六进制转二进制
{
    int d;
    int r;
    b.clear();//容器置空
    if(a>='0'&&a<='9') d=a-'0';//换十进制数字
    else d=a-'W';
    do
    {//循环取余
        r=d%2;
        if(r==1) b.push_back('1');
        else b.push_back('0');
        d=d/2;
    }while(d!=0);
    while(b.size()!=4)//补零
        b.push_back('0');
    reverse(b.begin(),b.end());//倒置
}

int H2D(string a)//二进制转十进制
{
    int d=0;
    int l=a.size();
    for(int i=0;i<l;i++)
    {
        if(a[i]=='0') continue;
        d+=x[l-i-1];
    }
    return d;
}

int main()
{
    vector<char> A;
    vector<string> B;
    cout<<"请粘贴您复制的全部字节，并在结尾加 # 号："<<endl;
    char ch;
    while(ch=getchar(),ch!='#')//输入
        A.push_back(ch);
    cout<<"读取完成..."<<endl;
    cout<<"正在分析..."<<endl;
    for(int i=7;i<=53;i++)//换二进制
    {
        if(A[i]==' ') continue;
        C2B(A[i]);
        B.push_back(b);
    }
    for(int i=81;i<=91;i++)
    {
        if(A[i]==' ') continue;
        C2B(A[i]);
        B.push_back(b);
    }
    cout<<"分析完成..."<<endl;
    cout<<"您输入的全部字节是:"<<endl;
    for(auto i:A)
        cout<<i;
    cout<<endl;
    cout<<"其中IP数据报部分为："<<endl;
    for(int i=7;i<=53;i++)//转换二进制
        cout<<A[i];
    cout<<' ';
    for(int i=81;i<=91;i++)
        cout<<A[i];
    cout<<endl;
    cout<<"转换为二进制为："<<endl;
    for(int i=0;i<20;i++)
    {
        if(i==10) cout<<endl;
        cout<<B[i]<<' ';
    }
    //分析
    cout<<endl<<"分析结果为："<<endl;
    //版本
    cout<<B[0]<<"................................... 代表";
    if(A[7]=='4') cout<<"版本为 IPV4"<<endl;
    else cout<<"版本为 IPV6"<<endl;
    //首部长
    cout<<B[1]<<"................................... 代表";
    cout<<"首部长为 "<<H2D(B[1])<<'B'<<endl;
    //区分服务
    cout<<B[2]<<' '<<B[3]<<".............................. 代表";
    cout<<"区分服务为 "<<B[2]<<' '<<B[3]<<endl;
    //总长度
    cout<<B[4]<<' '<<B[5]<<' '<<B[6]<<' '<<B[7]<<".................... 代表";
    cout<<"总长度为 "<<H2D(B[4]+B[5]+B[6]+B[7])<<'B'<<endl;
    //标识
    cout<<B[8]<<' '<<B[9]<<' '<<B[10]<<' '<<B[11]<<".................... 代表";
    cout<<"标识为 "<<A[19]<<A[20]<<A[22]<<A[23]<<'H'<<endl;
    //标志
    cout<<B[12][0]<<' '<<B[12][1]<<' '<<B[12][2]<<".................................. 代表";
    cout<<"标志为 ";
    if(B[12][1]=='1') cout<<"不可分片";
    else cout<<"可分片";
    if(B[12][2]=='1') cout<<"且此片并非末尾"<<endl;
    else cout<<"且此片为末尾"<<endl;
    //分片偏移
    cout<<B[12][3]<<' '<<B[13]<<' '<<B[14]<<' '<<B[15]<<"....................... 代表";
    cout<<"片偏移为 "<<H2D(B[12][3]+B[13]+B[14]+B[15])*8<<'B'<<endl;
    //生存时间
    cout<<B[16]<<' '<<B[17]<<".............................. 代表";
    cout<<"生存时间为 "<<H2D(B[16]+B[17])<<endl;
    //协议
    cout<<B[18]<<' '<<B[19]<<".............................. 代表";
    cout<<"协议为 "<<H2D(B[18]+B[19])<<endl;
    //首部校验和
    cout<<B[20]<<' '<<B[21]<<' '<<B[22]<<' '<<B[23]<<' '<<"................... 代表";
    cout<<"首部校验和 "<<endl;
    //源IP
    cout<<B[24]<<' '<<B[25]<<' '<<B[26]<<' '<<B[27]<<' '<<B[28]<<' '<<B[29]<<' '<<B[30]<<' '<<B[31]<<" 代表";
    cout<<"源IP地址为 "<<H2D(B[24]+B[25])<<'.'<<H2D(B[26]+B[27])<<'.'<<H2D(B[28]+B[29])<<'.'<<H2D(B[30]+B[31])<<'.'<<endl;
    //目的IP
    cout<<B[32]<<' '<<B[33]<<' '<<B[34]<<' '<<B[35]<<' '<<B[36]<<' '<<B[37]<<' '<<B[38]<<' '<<B[39]<<" 代表";
    cout<<"目的IP地址为 "<<H2D(B[32]+B[33])<<'.'<<H2D(B[34]+B[35])<<'.'<<H2D(B[36]+B[37])<<'.'<<H2D(B[38]+B[39])<<'.'<<endl;
    cout<<endl;
    return 0;
}