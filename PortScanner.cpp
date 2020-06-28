#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)//解决c4996
#include <iostream>
#include <strstream>
#include <winsock2.h>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <time.h>

using namespace std;

//全局变量:
//待扫描的端口
short g_portsTOscan[] = { 20,21,22,23,25,42,43,47,53,63,67,68,79,80,95,106,107,109,110,113,135,137,138,139,143,
                        144,161,162,443,445,1024,1080,1433,1434,1755,3306,4000,5010,5190,5631,5632,8000,8080 };
const short PORTSNUM = sizeof(g_portsTOscan) / sizeof(short);//端口个数
//等扫描的IP
vector<unsigned long> g_vec_IpToScan;
string g_startIp;
string g_endIp;
//开启的线程数,目前为1个IP1个线程
long g_runThreadNum;

//socket相关
TIMEVAL      g_timeout;//阻塞等待时间
const short TIMEOUT = 1;//阻塞等待时间
WSADATA      g_wsadata;//socket版本信息

//线程中的互斥体
HANDLE g_PortMutex;
HANDLE g_ThreadNumMutex;
HANDLE g_ResultMutex;//输入结果的互斥量

//保存IP扫描的结果
multimap<unsigned long, string> g_map_ScanResult;

DWORD WINAPI ThreadFunc(LPVOID th_para)
{
    //获取需要扫描的IP
    unsigned long ulScanIp = *(unsigned long*)th_para;

    int index = 0;           //端口索引
    SOCKET link_sock;        //SOCKET
    FD_SET    set_flag;      //SOCKET描述
    short select_ret;        //select异步返回值
    short port;              //正在扫描的端口

    while (index < PORTSNUM)
    {
        port = g_portsTOscan[index];

        //创建数据流套接字
        link_sock = socket(AF_INET, SOCK_STREAM, 0);
        if (link_sock == INVALID_SOCKET)
        {
            WaitForSingleObject(g_ThreadNumMutex, INFINITE);
            g_runThreadNum--;
            ReleaseMutex(g_ThreadNumMutex);
            return -1;
        }

        FD_ZERO(&set_flag);             //将指定文件描述符清空
        FD_SET(link_sock, &set_flag); //用于在文件描述符集合中增加一个新的文件描述符

        //设置连接地址
        SOCKADDR_IN  scan_addr;
        scan_addr.sin_family = AF_INET;
        scan_addr.sin_addr.s_addr = ulScanIp;
        scan_addr.sin_port = htons(port);

        unsigned long sock_set = 1;
        ioctlsocket(link_sock, FIONBIO, &sock_set);     //设置套接字为非阻塞模式,第3个参数非0为非阻塞        
        connect(link_sock, (struct sockaddr*) & scan_addr, sizeof(scan_addr));//连接指定IP端口

        select_ret = select(0, NULL, &set_flag, NULL, &g_timeout);//异步返回值

        if (select_ret == 0 || select_ret == -1)
        {
            ++index;
            continue;
        }
        else
        {
            strstream stream_result;
            struct in_addr ipaddr;
            ipaddr.s_addr = ulScanIp;
            char* pStrIp = inet_ntoa(ipaddr);

            stream_result << "\t" << pStrIp << "\t上找到开放的端口: " << port << '\0';
            string str_result(stream_result.str());

            //将扫描结果储存到输出变量中去
            WaitForSingleObject(g_ResultMutex, INFINITE);

            g_map_ScanResult.insert(make_pair(ulScanIp, str_result));

            ReleaseMutex(g_ResultMutex);
        }
        ++index;
    }

    //扫描完一个线程
    shutdown(link_sock, 0);
    closesocket(link_sock);

    WaitForSingleObject(g_ThreadNumMutex, INFINITE);
    g_runThreadNum--;
    ReleaseMutex(g_ThreadNumMutex);

    return 0;
}//线程函数,扫描每一个IP


unsigned long InvertIp(unsigned long srcIp)//将IP转化成能直接递增和递减的地址
{
    unsigned char first;
    unsigned char second;
    unsigned char third;
    unsigned char fourth;

    first = srcIp & 0x00FF;
    second = (srcIp >> 8) & 0x00FF;
    third = (srcIp >> 16) & 0x00FF;
    fourth = (srcIp >> 24) & 0x00FF;

    return   (first << 24) | (second << 16) | (third << 8) | fourth;
}

int GetIpToScan(const string& StartIp, const string& EndIp, vector<unsigned long>& vec_ip)//将IP内的IP转化成一个一个unsigned long 类型存在数组中
{
    //判断输入的IP是否合法
    unsigned long ulStartIp = inet_addr(StartIp.c_str());
    unsigned long ulEndIp = inet_addr(EndIp.c_str());

    if (
        INADDR_NONE == ulStartIp
        ||
        INADDR_NONE == ulEndIp
        )
    {
        cout << "请输入合法的IP" << endl;
        return -1;
    }

    //判断查询的是一个IP还是IP段
    if (ulStartIp == ulEndIp && ulStartIp != 0)
    {
        vec_ip.push_back(ulStartIp);
        return 0;
    }

    if (ulStartIp == 0 && ulEndIp == 0)
    {
        return 0;
    }

    if (ulStartIp == 0)
    {
        vec_ip.push_back(ulEndIp);
        return 0;
    }

    if (ulEndIp == 0)
    {
        vec_ip.push_back(ulStartIp);
        return 0;
    }

    //将IP转换成可以递增比较的类型
    ulStartIp = InvertIp(ulStartIp);
    ulEndIp = InvertIp(ulEndIp);

    //指定前后顺序,ulEndIp较大
    unsigned long max_ip;
    if (ulStartIp > ulEndIp)
    {
        max_ip = ulStartIp;
        ulStartIp = ulEndIp;
        ulEndIp = max_ip;
    }

    int ipnums = ulEndIp - ulStartIp;

    for (int i = 0; i <= ipnums; ++i)
    {
        //将每个IP的unsigned long型存到数组中供扫描
        vec_ip.push_back(InvertIp(ulStartIp++));
    }
    return 0;
}

int ScanIp(const string& start_Ip, const string& endIp, multimap<unsigned long, string>& ouputMap)//功能:  输入一个IP段,输出该IP段内的端口开放情况信息
{
    //分解IP段内的IP到全局数组中去
    GetIpToScan(start_Ip, endIp, g_vec_IpToScan);

    int scanNum = g_vec_IpToScan.size();

    //线程总数
    g_runThreadNum = scanNum;
    cout << "---------------共有 " << scanNum << " 个IP要扫描---------------" << endl;
    //对每个IP开一个线程
    for (int i = 0; i < scanNum; ++i)
    {
        CreateThread(NULL, 0, ThreadFunc, &g_vec_IpToScan[i], 0, NULL);
        //要是不间隔时间的话,同时创建socket会出现10093错误
        Sleep(50);
    }

    return 0;
}

int OutPutScanInfo()//输出扫描结果
{
    multimap<unsigned long, string>::iterator iter = g_map_ScanResult.begin();
    ofstream out("out.txt");
    cout << "共扫描到 " << g_map_ScanResult.size() << " 个端口" << endl;
    for (; iter != g_map_ScanResult.end(); ++iter)
    {
        out << iter->second << endl;
        cout << iter->second << endl;
    }
    return 0;
}

void UserInput()//开始界面
{
    cout << "  ---------------------------------------------------------" << endl;
    cout << " |  输入两个点分十进制的IP地址，将扫描该网段的所有IP       |" << endl;
    cout << " |          若只扫描一个IP,则输入两个相同IP                |" << endl;
    cout << "  ---------------------------------------------------------" << endl;
    cout << endl<< endl;
    cout << "请输入起始IP: ";
    cin >> g_startIp;
    cout << "请输入结束IP: ";
    cin >> g_endIp;
}

void InitProc()//初始化相关信息
{
    //初始化socket相关信息
    int ws_result;
    ws_result = WSAStartup(MAKEWORD(2, 2), &g_wsadata);

    if (ws_result != 0)
        cout << "socket WSAStartup初始化失败" << endl;
    //设置阻塞函数的超时时间
    g_timeout.tv_sec = TIMEOUT;
    g_PortMutex = CreateMutex(NULL, FALSE, "port mutex");
    g_ThreadNumMutex = CreateMutex(NULL, FALSE, "threadnums mutex");
    g_ResultMutex = CreateMutex(NULL, FALSE, "result mutex");
}

void CleanProc()//清理
{
    //线程都执行完后清理socket相关信息
    while (1)
    {
        WaitForSingleObject(g_ThreadNumMutex, INFINITE);
        if (g_runThreadNum == 0) break;
        ReleaseMutex(g_ThreadNumMutex);
        Sleep(100);
    }
    WSACleanup();//清理socket相关信息
}

int main()   //主函数
{
    clock_t start_time;
    clock_t end_time;
    double cost_time = 0;
    start_time = clock();
    InitProc();//初始化
    UserInput();//输入
    ScanIp(g_startIp, g_endIp, g_map_ScanResult);//开始扫描
    CleanProc();//清理结束后进程
    OutPutScanInfo();//输出结果
  //计算程序运行时间
    end_time = clock();
    cost_time = (double)((double)end_time - (double)start_time) / CLOCKS_PER_SEC;
    cout << "耗时 " << cost_time << " 秒" << endl;
    return 0;
}
