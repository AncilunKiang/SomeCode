#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

string b;
int x[]={1,2,4,8,16,32,64,128,256,512};

void C2B(char a)//ʮ������ת������
{
    int d;
    int r;
    b.clear();//�����ÿ�
    if(a>='0'&&a<='9') d=a-'0';//��ʮ��������
    else d=a-'W';
    do
    {//ѭ��ȡ��
        r=d%2;
        if(r==1) b.push_back('1');
        else b.push_back('0');
        d=d/2;
    }while(d!=0);
    while(b.size()!=4)//����
        b.push_back('0');
    reverse(b.begin(),b.end());//����
}

int H2D(string a)//������תʮ����
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
    cout<<"��ճ�������Ƶ�ȫ���ֽڣ����ڽ�β�� # �ţ�"<<endl;
    char ch;
    while(ch=getchar(),ch!='#')//����
        A.push_back(ch);
    cout<<"��ȡ���..."<<endl;
    cout<<"���ڷ���..."<<endl;
    for(int i=7;i<=53;i++)//��������
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
    cout<<"�������..."<<endl;
    cout<<"�������ȫ���ֽ���:"<<endl;
    for(auto i:A)
        cout<<i;
    cout<<endl;
    cout<<"����IP���ݱ�����Ϊ��"<<endl;
    for(int i=7;i<=53;i++)//ת��������
        cout<<A[i];
    cout<<' ';
    for(int i=81;i<=91;i++)
        cout<<A[i];
    cout<<endl;
    cout<<"ת��Ϊ������Ϊ��"<<endl;
    for(int i=0;i<20;i++)
    {
        if(i==10) cout<<endl;
        cout<<B[i]<<' ';
    }
    //����
    cout<<endl<<"�������Ϊ��"<<endl;
    //�汾
    cout<<B[0]<<"................................... ����";
    if(A[7]=='4') cout<<"�汾Ϊ IPV4"<<endl;
    else cout<<"�汾Ϊ IPV6"<<endl;
    //�ײ���
    cout<<B[1]<<"................................... ����";
    cout<<"�ײ���Ϊ "<<H2D(B[1])<<'B'<<endl;
    //���ַ���
    cout<<B[2]<<' '<<B[3]<<".............................. ����";
    cout<<"���ַ���Ϊ "<<B[2]<<' '<<B[3]<<endl;
    //�ܳ���
    cout<<B[4]<<' '<<B[5]<<' '<<B[6]<<' '<<B[7]<<".................... ����";
    cout<<"�ܳ���Ϊ "<<H2D(B[4]+B[5]+B[6]+B[7])<<'B'<<endl;
    //��ʶ
    cout<<B[8]<<' '<<B[9]<<' '<<B[10]<<' '<<B[11]<<".................... ����";
    cout<<"��ʶΪ "<<A[19]<<A[20]<<A[22]<<A[23]<<'H'<<endl;
    //��־
    cout<<B[12][0]<<' '<<B[12][1]<<' '<<B[12][2]<<".................................. ����";
    cout<<"��־Ϊ ";
    if(B[12][1]=='1') cout<<"���ɷ�Ƭ";
    else cout<<"�ɷ�Ƭ";
    if(B[12][2]=='1') cout<<"�Ҵ�Ƭ����ĩβ"<<endl;
    else cout<<"�Ҵ�ƬΪĩβ"<<endl;
    //��Ƭƫ��
    cout<<B[12][3]<<' '<<B[13]<<' '<<B[14]<<' '<<B[15]<<"....................... ����";
    cout<<"Ƭƫ��Ϊ "<<H2D(B[12][3]+B[13]+B[14]+B[15])*8<<'B'<<endl;
    //����ʱ��
    cout<<B[16]<<' '<<B[17]<<".............................. ����";
    cout<<"����ʱ��Ϊ "<<H2D(B[16]+B[17])<<endl;
    //Э��
    cout<<B[18]<<' '<<B[19]<<".............................. ����";
    cout<<"Э��Ϊ "<<H2D(B[18]+B[19])<<endl;
    //�ײ�У���
    cout<<B[20]<<' '<<B[21]<<' '<<B[22]<<' '<<B[23]<<' '<<"................... ����";
    cout<<"�ײ�У��� "<<endl;
    //ԴIP
    cout<<B[24]<<' '<<B[25]<<' '<<B[26]<<' '<<B[27]<<' '<<B[28]<<' '<<B[29]<<' '<<B[30]<<' '<<B[31]<<" ����";
    cout<<"ԴIP��ַΪ "<<H2D(B[24]+B[25])<<'.'<<H2D(B[26]+B[27])<<'.'<<H2D(B[28]+B[29])<<'.'<<H2D(B[30]+B[31])<<'.'<<endl;
    //Ŀ��IP
    cout<<B[32]<<' '<<B[33]<<' '<<B[34]<<' '<<B[35]<<' '<<B[36]<<' '<<B[37]<<' '<<B[38]<<' '<<B[39]<<" ����";
    cout<<"Ŀ��IP��ַΪ "<<H2D(B[32]+B[33])<<'.'<<H2D(B[34]+B[35])<<'.'<<H2D(B[36]+B[37])<<'.'<<H2D(B[38]+B[39])<<'.'<<endl;
    cout<<endl;
    return 0;
}