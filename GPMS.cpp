#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <Windows.h>
#include <conio.h>
#include <ctime>
#include "mysql.h"

using namespace std;

class Table
{//表类
public:
    Table(MYSQL* mysql,string TableName) : mysql(mysql),TableName(TableName){};//初始化

    MYSQL* mysql;//当前数据库
    string TableName;//表名

    bool ExecuteSql(MYSQL* mysql, const char* sql)
    {//执行SQL语句
        if (mysql_query(mysql, sql))
        {//打错误log，这里直接显示到控制台
            cerr << "执行sql语句失败，错误信息为： " << mysql_error(mysql) << endl;
            return 0;
        }
        return 1;
    }
    int delete_line(string a, string b)
    {//删除a的值等于b的行
        string st = "delete from " + TableName + " where " + a + " = '" + b + "'";//SQL语句
        ExecuteSql(mysql, st.c_str());//执行
        return 1;
    }
    int update(string a, string b, string c, string d)
    {//把a的值等于b的行的c的值换成d
        string st = "update " + TableName + " set " + c + " = '" + d + "' where " + a + " = '" + b + "'";//SQL语句
        ExecuteSql(mysql, st.c_str());//执行
        return 1;
    }
    MYSQL_RES* find(string a, string b)
    {//查找a的值为b的行
        MYSQL_RES* res;
        string st = "select * from " + TableName + " where " + a + " = '" + b + "'";//SQL
        if (mysql_query(mysql, st.c_str()))
        {
            cout << "查找失败" << mysql_error(mysql) << endl;//查询数据
        }
        res = mysql_store_result(mysql);//获取结果集
        return res;
    }
    MYSQL_RES* find()
    {//查询整个表
        MYSQL_RES* res;
        string st = "select * from " + TableName ;//SQL语句
        if (mysql_query(mysql, st.c_str()))
        {
            cout << "查找失败" << mysql_error(mysql) << endl;//查询数据
        }
        res = mysql_store_result(mysql);//获取结果集
        return res;
    }
};

class Students : public Table
{//学生表类
public:
    Students(MYSQL* mysql) : Table(mysql,"students"), mysql(mysql){};//初始化！！！注意显示的构造父函数

    MYSQL* mysql;//当前数据库
    string TableName="students";//表名

    int insert(string ID, string Name, string Sex, string Major, string Class, string Contacts)
    {//插入
        string st = "insert into " + TableName + " values ('" + ID + "', '" + Name + "','" + Sex + "','" + Major + "','" + Class + "','" + Contacts + "')";//SQL语句
        const char* sql = st.c_str();
        ExecuteSql(mysql, sql);
        return 1;
    }
};

class Teachers : public Table
{//教师表类
public:
    Teachers(MYSQL* mysql) : Table(mysql, "teachers"), mysql(mysql){};//初始化

    MYSQL* mysql;//当前数据库
    string TableName= "teachers";//表名

    int insert(string ID, string Name, string Sex, string Contacts)
    {//插入
        string st = "insert into " + TableName + " values ('" + ID + "', '" + Name + "','" + Sex + "','" + Contacts + "')";//SQL语句
        const char* sql = st.c_str();
        ExecuteSql(mysql, sql);
        return 1;
    }
};

class GraduationProject : public Table
{//毕设表类
public:
    GraduationProject(MYSQL* mysql) :Table(mysql,"graduationproject"), mysql(mysql) {};//初始化

    MYSQL* mysql;//当前数据库
    string TableName = "graduationproject";//表名
    //以下函数均已重载(有一float类型)
    int insert(string ID, string Topic, string Results, string SubmitterID, string RaterID, string Dateline)
    {//插入(带成绩)
        string st = "insert into " + TableName + " values ('" + ID + "', '" + Topic + "'," + Results + ",'" + SubmitterID + "','" + RaterID + "','" + Dateline + "')";//SQL语句
        const char* sql = st.c_str();
        ExecuteSql(mysql, sql);
        return 1;
    }
    int insert(string ID, string Topic, string SubmitterID, string RaterID, string Dateline)
    {//插入(重载版不带成绩)
        string st = "insert into " + TableName + " values ('" + ID + "', '" + Topic + "',NULL,'" + SubmitterID + "','" + RaterID + "','" + Dateline + "')";//SQL语句
        const char* sql = st.c_str();
        ExecuteSql(mysql, sql);
        return 1;
    }
    int delete_line(string a, string b)
    {//删除a的值等于b的行
        string st;
        if(a=="Results") st = "delete from " + TableName + " where " + a + " = " + b;//成绩类型不是char故需要单算
        else st = "delete from " + TableName + " where " + a + " = '" + b + "'";
        ExecuteSql(mysql, st.c_str());
        return 1;
    }
    int update(string a, string b, string c, string d)
    {//把a的值等于b的行的c的值换成d
        string st;
        if(a=="Results"&&c=="Results") st = "update " + TableName + " set " + c + " = " + d + " where " + a + " = " + b;
        else if(a == "Results") st = "update " + TableName + " set " + c + " = '" + d + "' where " + a + " = " + b;
        else if(c == "Results") st = "update " + TableName + " set " + c + " = " + d + " where " + a + " = '" + b + "'";
        else st = "update " + TableName + " set " + c + " = '" + d + "' where " + a + " = '" + b + "'";
        ExecuteSql(mysql, st.c_str());
        return 1;
    }
    MYSQL_RES* find(string a, string b)
    {//查找a的值为b的行
        string st;
        MYSQL_RES* res;
        if(a=="Results") st = "select * from " + TableName + " where " + a + " = " + b;
        else st = "select * from " + TableName + " where " + a + " = '" + b + "'";
        if (mysql_query(mysql, st.c_str()))
        {
            cout << "查找失败" << mysql_error(mysql) << endl;//查询数据
        }
        res = mysql_store_result(mysql);//获取结果集
        return res;
    }
};

class TutorAssignment : public Table
{//导师分配表类
public:
    TutorAssignment(MYSQL* mysql) : Table(mysql, "tutorassignment"), mysql(mysql) {};//初始化

    MYSQL* mysql;
    string TableName = "tutorassignment";

    int insert(string TutorID, string StudentID)
    {//插入
        string st = "insert into " + TableName + " values ('" + TutorID + "', '" + StudentID + "')";
        const char* sql = st.c_str();
        ExecuteSql(mysql, sql);
        return 1;
    }
};

class Account : public Table
{//账号表类
public:
    Account(MYSQL* mysql) : Table(mysql, "account"), mysql(mysql) {};//初始化

    MYSQL* mysql;
    string TableName = "account";

    int insert(string Number, string Password)
    {//插入
        string st = "insert into " + TableName + " values ('" + Number + "', '" + Password + "')";
        const char* sql = st.c_str();
        ExecuteSql(mysql, sql);
        return 1;
    }
};

class User
{//用户类
public:
    User(MYSQL* mysql) : mysql(mysql),a(mysql), s(mysql), t(mysql), g(mysql) {};

    MYSQL* mysql;
    Account a;
    Students s;
    TutorAssignment t;
    GraduationProject g;
    string id;

    int change_password(string new_password)
    {//修改密码
        a.update("Number",id,"Password",new_password);
        return 1;
    }

    MYSQL_ROW query_submission()
    {//查询毕设信息
        MYSQL_RES* res; //一个结果集结构体
        MYSQL_ROW row;  //char** 二维数组，存放一条条记录
        string r;
        res = g.find("SubmitterID", id);
        row = mysql_fetch_row(res);
        if (row == NULL) return NULL;
        return row;
    }

};

class Student :public User
{//学生类
public:
    Student(MYSQL* mysql) :User(mysql), a(mysql), mysql(mysql), s(mysql), ts(mysql), t(mysql), g(mysql) {};

    MYSQL* mysql;
    string id;
    Account a;
    Students s;
    Teachers ts;
    TutorAssignment t;
    GraduationProject g;

    int sign_in(string Number_in, string Password_in)
    {//登录账号密码匹配、权限匹配
        string Number, Password;
        MYSQL_RES* res;
        MYSQL_ROW row;

        if (res = a.find("Number", Number_in))
        {
            if (!(row = mysql_fetch_row(res)))
            {
                cout << "*账号不存在" << endl;
                return 0;
            }
            Number = row[0];
            Password = row[1];
            if (Password_in == Password)
            {
                id = User::id = Number_in;
                return 1;
            }
            else
            {
                cout << "*密码错误" << endl;
                return 0;
            }
        }
        return 0;
    }

    int submit_graduation_project(string Topic, string Dateline)
    {//提交毕设
        MYSQL_RES* res; //一个结果集结构体
        MYSQL_ROW row;  //char** 二维数组，存放一条条记录
        string ID;
        res = t.find("StudentID", id);
        row = mysql_fetch_row(res);
        ID = id + row[0];
        g.insert(ID, Topic, id, row[0], Dateline);
        return 1;
    }

    int change_topic(string new_topic, string new_dateline)
    {//修改毕设题目
        g.update("SubmitterID", id, "Topic", new_topic);
        g.update("SubmitterID", id, "Dateline", new_dateline);
        return 1;
    }

    MYSQL_ROW get_my_teacher()
    {//获取我的导师信息
        vector<string> v;
        string t_id;
        MYSQL_RES* res; //一个结果集结构体
        MYSQL_ROW row;  //char** 二维数组，存放一条条记录
        res = t.find("StudentID", id);
        row = mysql_fetch_row(res);
        t_id = row[0];
        res = ts.find("ID", t_id);
        row = mysql_fetch_row(res);
        return row;
    }

    int print_opt()
    {//功能选项
        cout << "请选择操作：" << endl;
        cout << "*A：提交课设       B：修改课设题目     C：查看毕业设计信息" << endl;
        cout << "*D：查看我的导师   E：修改密码         F：退出登录";
        return 1;
    }

};

class Teacher :public User
{//教师类
public:
    Teacher(MYSQL* mysql) :User(mysql), a(mysql), mysql(mysql), s(mysql), t(mysql), g(mysql) {};

    MYSQL* mysql;
    vector<vector<string>> MyStudents;//学生列表
    string id;
    Account a;
    Students s;
    TutorAssignment t;
    GraduationProject g;

    int sign_in(string Number_in, string Password_in)
    {//登录账号密码匹配、权限匹配
        string Number, Password;
        MYSQL_RES* res;
        MYSQL_ROW row;

        if (res = a.find("Number", Number_in))
        {
            if (!(row = mysql_fetch_row(res)))
            {
                cout << "*账号不存在" << endl;
                return 0;
            }
            Number = row[0];
            Password = row[1];
            if (Password_in == Password)
            {
                id = User::id = Number_in;
                return 1;
            }
            else
            {
                cout << "*密码错误" << endl;
                return 0;
            }
        }
        return 0;
    }

    int get_my_students_info()
    {//获取我的学生信息列表
        vector<string> ids;
        MYSQL_RES* res; //一个结果集结构体
        MYSQL_ROW row;  //char** 二维数组，存放一条条记录
        res = t.find("TutorID", id);
        while (row = mysql_fetch_row(res))
        {//获取我负责的学生的学号
            ids.push_back(row[1]);
        }
        for (string x : ids)
        {
            res = s.find("ID", x);
            row = mysql_fetch_row(res);
            MyStudents.push_back({ row[0],row[1],row[2] ,row[3] ,row[4],row[5] });
        }
        return 1;
    }

    vector<vector<string>> get_my_students_gp()
    {//获取毕设信息
        vector<vector<string>> gps;
        MYSQL_RES* res; //一个结果集结构体
        MYSQL_ROW row;  //char** 二维数组，存放一条条记录
        for (vector<string> i : MyStudents)
        {
            res = g.find("SubmitterID", i[0]);
            row = mysql_fetch_row(res);
            if (row == NULL) gps.push_back({ i[0],i[1],"未提交" });
            else
            {
                if(row[2]==NULL)
                    gps.push_back({ i[0],i[1],row[0],row[1] ,"未批改" ,row[5] });
                else
                    gps.push_back({ i[0],i[1],row[0],row[1] ,row[2] ,row[5] });
            }
        }
        return gps;
    }

    int change_results(string id, string results)
    {//提交成绩
        g.update("SubmitterID", id, "Results", results);
        return 1;
    }

    int print_opt()
    {//功能选项
        cout << "请选择操作：" << endl;
        cout << "*A：查看学生列表      B：查看学生毕设信息     C：成绩录入" << endl;
        cout << "*D：修改密码          E：退出登录";
        return 1;
    }
};

class Administrator :public User
{//管理员类
public:
    Administrator(MYSQL* mysql) :User(mysql), a(mysql), mysql(mysql), ts(mysql), s(mysql), t(mysql), g(mysql) {};

    MYSQL* mysql;
    string id;
    Account a;
    Students s;
    Teachers ts;
    TutorAssignment t;
    GraduationProject g;

    int sign_in(string Number_in, string Password_in)
    {//登录账号密码匹配、权限匹配
        string Number, Password;
        MYSQL_RES* res;
        MYSQL_ROW row;

        if (res = a.find("Number", Number_in))
        {
            if (!(row = mysql_fetch_row(res)))
            {
                cout << "*账号不存在" << endl;
                return 0;
            }
            Number = row[0];
            Password = row[1];
            if (Password_in == Password)
            {
                id = User::id = Number_in;
                return 1;
            }
            else
            {
                cout << "*密码错误" << endl;
                return 0;
            }
        }
        return 0;
    }

    vector<vector<string>> get_students()
    {//获取学生表
        vector<vector<string>> v;
        MYSQL_RES* res; //一个结果集结构体
        MYSQL_ROW row;  //char** 二维数组，存放一条条记录
        res = s.find();
        while (row = mysql_fetch_row(res))
        {
            v.push_back({ row[0],row[1],row[2] ,row[3] ,row[4] ,row[5] });
        }
        return v;
    }

    vector<vector<string>> get_teachers()
    {//获取教师表
        vector<vector<string>> v;
        MYSQL_RES* res; //一个结果集结构体
        MYSQL_ROW row;  //char** 二维数组，存放一条条记录
        res = ts.find();
        while (row = mysql_fetch_row(res))
        {
            v.push_back({ row[0],row[1],row[2] ,row[3] });
        }
        return v;
    }

    vector<vector<string>> get_tuor_assignment()
    {//获取分配信息表
        vector<vector<string>> v;
        string t_name, s_name;
        MYSQL_RES* res1; //一个结果集结构体
        MYSQL_RES* res2; //一个结果集结构体
        MYSQL_ROW row1;  //char** 二维数组，存放一条条记录
        MYSQL_ROW row2;  //char** 二维数组，存放一条条记录
        res1 = t.find();
        while (row1 = mysql_fetch_row(res1))
        {
            res2 = ts.find("ID", row1[0]);
            row2 = mysql_fetch_row(res2);
            t_name = row2[1];
            res2 = s.find("ID", row1[1]);
            row2 = mysql_fetch_row(res2);
            s_name = row2[1];
            v.push_back({ row1[0],t_name,row1[1],s_name });
        }
        return v;
    }

    int random_allocation()
    {//随机分配
        MYSQL_RES* res; //一个结果集结构体
        MYSQL_ROW row;  //char** 二维数组，存放一条条记录
        vector<string> sid, tid;
        vector<int> r;//随机数组
        unsigned long tn,sn;
        res = s.find();
        sn = res->row_count;//学生人数
        while (row = mysql_fetch_row(res)) sid.push_back(row[0]);//获取所有学号
        res = ts.find();
        tn = res->row_count;//教师人数
        while (row = mysql_fetch_row(res)) tid.push_back(row[0]);//获取所有教师号
        while (r.size() != sn)
        {//生成随机数组
            int i = rand() % sn;
            if (find(r.begin(), r.end(), i) == r.end()) r.push_back(i);
        }
        for (int i = 0; i < tn; i++)
        {//按随机数组分配
            for (int j = 0; j < sn / tn; j++)
            {
                t.insert(tid[i], sid[*(end(r)-1)]);
                r.pop_back();
            }
        }
        while (!r.empty())
        {//把剩的人都给最后一个老师
            t.insert(*(end(tid) - 1), sid[*(end(r) - 1)]);
            r.pop_back();
        }
        return 0;
    }

    int manual_allocation(string tid,string sid)
    {//人工分配
        t.insert(tid, sid);
        return 1;
    }

    int print_opt()
    {//操作选项
        cout << "请选择操作：" << endl;
        cout << "*A：查看学生列表      B：查看教师列表     C：查看分配表" << endl;
        cout << "*D：导师分配          E：修改密码         F：退出登录";
        return 1;
    }
};

class Windows
{
public:
    Windows()
    {//初始化边框
        vector<char> r;
        for (int i = 0; i < 100; i++) r.push_back('*');//顶行
        frame.push_back(r);
        for (int i = 1; i <= 98; i++) r[i] = ' ';
        for (int i = 0; i < 27; i++) frame.push_back(r);//空白行数
        for (int i = 1; i <= 98; i++) r[i] = '*';//底行
        frame.push_back(r);
    };

    vector<vector<char>> frame;//边框100*27

    inline void gotoxy(short x, short y)
    {//system.h太古老了，只能自己写个gotoxy函数用
        COORD pos = { x,y };
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);// 获取标准输出设备句柄
        SetConsoleCursorPosition(hOut, pos);//两个参数分别是指定哪个窗体，具体位置
    }

    inline void hide()
    {//隐藏光标
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO CursorInfo;
        GetConsoleCursorInfo(handle, &CursorInfo);//获取控制台光标信息
        CursorInfo.bVisible = false; //隐藏控制台光标
        SetConsoleCursorInfo(handle, &CursorInfo);//设置控制台光标状态
    }

    void refresh()
    {//清屏绘制框架
        gotoxy(0, 0);
        for (auto a : frame)
        {
            for (auto b : a)
            {
                cout << b;
            }
            cout << endl;
        }
    }

    void loding(int n)
    {//加载函数
        for (int i=0; i < n; i++)
        {
            Sleep(100);
            cout << '.';
        }
    }

    void welcome()
    {//输出欢迎界面
        refresh();
        gotoxy(1,  3); cout << "   ◆  ◆  ◆      ◆◆◆◆◆      ◆◆              ◆◆◆◆        ◆◆◆      ◆◆◆  ◆◆◆  ";
        gotoxy(1,  4); cout << "   ◆  ◆  ◆      ◆              ◆              ◆        ◆    ◆      ◆      ◆◆  ◆◆    ";
        gotoxy(1,  5); cout << "   ◆  ◆  ◆      ◆              ◆              ◆        ◆  ◆          ◆    ◆◆  ◆◆    ";
        gotoxy(1,  6); cout << "   ◆  ◆  ◆      ◆              ◆            ◆              ◆          ◆    ◆◆  ◆◆    ";
        gotoxy(1,  7); cout << "   ◆  ◆  ◆      ◆◆◆◆◆      ◆            ◆              ◆          ◆    ◆◆  ◆◆    ";
        gotoxy(1,  8); cout << "   ◆  ◆  ◆      ◆              ◆            ◆              ◆          ◆    ◆◆  ◆◆    ";
        gotoxy(1,  9); cout << "   ◆◆  ◆◆      ◆              ◆            ◆              ◆          ◆    ◆  ◆  ◆    ";
        gotoxy(1, 10); cout << "     ◆  ◆        ◆              ◆            ◆              ◆          ◆    ◆  ◆  ◆    ";
        gotoxy(1, 11); cout << "     ◆  ◆        ◆              ◆             ◆         ◆  ◆          ◆    ◆  ◆  ◆    ";
        gotoxy(1, 12); cout << "     ◆  ◆        ◆              ◆              ◆      ◆      ◆      ◆      ◆  ◆  ◆    ";
        gotoxy(1, 13); cout << "     ◆  ◆        ◆◆◆◆◆      ◆◆◆◆◆◆      ◆◆◆          ◆◆◆      ◆◆  ◆  ◆◆  ";
        gotoxy(35, 20);
        loding(25);
    }

    void bye()
    {//退出界面
        refresh();
        gotoxy(1, 1);
        cout << "感谢您的使用";
        loding(10);
    }
};

int main()
{
    MYSQL mysql; //一个数据库结构体
    Windows w;//画面输出类
    MYSQL_RES* res; //一个结果集结构体
    MYSQL_ROW row;  //char** 二维数组，存放一条条记录
    char opt = '0';//选项

    w.hide();//隐藏指针
    w.welcome();//输出欢迎界面
    w.refresh();//刷新框架

    mysql_init(&mysql);//初始化数据库
    mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");//设置编码方式
    if (mysql_real_connect(&mysql, "localhost", "root", "102576", "gpmsd", 3306, NULL, 0) == NULL)
    {//连接数据库,如果连接失败就把连接失败的信息显示出来
        w.gotoxy(1, 1);
        cout << (mysql_error(&mysql));
    }
    else
    {//连接成功
        w.gotoxy(1, 1);
        cout << "数据库连接成功";
        w.loding(10);
    }

    while (1)
    {
        w.refresh();//界面刷新
        w.gotoxy(1, 1);
        cout << "A/a：管理员登陆     T/t：教师登录      S/s：学生登录" << endl;
        cout << endl;
        cout << "*请选择登录权限";

        while (1)
        {//登陆身份选择
            opt = _getch();//获取字符不回显，c++的conio.h中的getch()函数已替换成_getch()
            if (opt == 'a' || opt == 'A' || opt == 't' || opt == 'T' || opt == 's' || opt == 'S' || opt == 'q' || opt == 'Q') break;
        }
        if (opt == 'a' || opt == 'A')
        {//管理员登陆
            Administrator a(&mysql);
            string id, password;
            while (1)
            {//登录
                w.refresh();
                w.gotoxy(1, 1);
                cout << "亲爱的管理员，请登录.....";
                w.gotoxy(1, 3);
                cout << "账号(输入b可退回上页)：";
                cin >> id;
                if (id == "b" || id == "B") break;
                w.gotoxy(1, 4);
                cout << "密码：";
                cin >> password;
                if (a.sign_in(id, password) == 1)
                {
                    cout << "*登陆成功";
                    w.loding(10);
                    break;
                }
                else
                {
                    w.loding(10);
                }
            }
            if (id == "b" || id == "B") continue;
            while (1)
            {//主循环
                w.refresh();
                w.gotoxy(1, 1);
                a.print_opt();
                while (1)
                {//操作选择
                    opt = _getch();
                    if (opt == 'a' || opt == 'A' || opt == 'b' || opt == 'B' || opt == 'c' || opt == 'C' || opt == 'd' || opt == 'D' || opt == 'e' || opt == 'E' || opt == 'f' || opt == 'F') break;
                }
                if (opt == 'a' || opt == 'A')
                {//查看学生表
                    w.refresh();
                    w.gotoxy(1, 1);
                    cout << "学号           姓名   性别   专业               班级         联系方式" << endl;
                    vector<vector<string>> v = a.get_students();
                    for (vector<string> s : v)
                    {
                        cout << "*" << s[0] << "   " << s[1] << "   " << s[2] << "     " << s[3] << "   " << s[4] << "   " << s[5] << endl;
                    }
                    cout << "*按任意键返回";
                    while (!_kbhit())
                        continue;
                }
                else if (opt == 'b' || opt == 'B')
                {//查看教师列表
                    w.refresh();
                    w.gotoxy(1, 1);
                    cout << "教师号    姓名   性别         联系方式" << endl;
                    vector<vector<string>> v = a.get_teachers();
                    for (vector<string> s : v)
                    {
                        cout << "*" << s[0] << "       " << s[1] << "   " << s[2] << "           " << s[3] << endl;
                    }
                    cout << "*按任意键返回";
                    while (!_kbhit())
                        continue;
                }
                else if (opt == 'c' || opt == 'C')
                {//获取分配表
                    w.refresh();
                    w.gotoxy(1, 1);
                    cout << "教师号    姓名          学号             姓名" << endl;
                    vector<vector<string>> v = a.get_tuor_assignment();
                    for (vector<string> s : v)
                    {
                        cout << "*" << s[0] << "       " << s[1] << "   " << "负责" << "   " << s[2] << "     " << s[3] << endl;
                    }
                    cout << "*按任意键返回";
                    while (!_kbhit())
                        continue;
                }
                else if (opt == 'd' || opt == 'D')
                {//导师分配
                    w.refresh();
                    w.gotoxy(1, 1);
                    vector<vector<string>> gps;
                    while (1)
                    {
                        w.refresh();
                        w.gotoxy(1, 1);
                        cout << "请选择分配模式" << endl;
                        cout << "*A：随机分配     B：人工分配      Q：返回上页" << endl;
                        while (1)
                        {//操作选择
                            opt = _getch();
                            if (opt == 'a' || opt == 'A' || opt == 'b' || opt == 'B' || opt == 'q' || opt == 'Q') break;
                        }
                        if (opt == 'a' || opt == 'A')
                        {//随机分配
                            a.random_allocation();
                            w.refresh();
                            w.gotoxy(1, 1);
                            cout << "分配成功";
                            w.loding(10);
                        }
                        else if (opt == 'b' || opt == 'B')
                        {//人工分配
                            while (1)
                            {
                                w.refresh();
                                w.gotoxy(1, 1);
                                string sid, tid;
                                cout << "请输入教师号(输入b退回上页)：";
                                cin >> tid;
                                if (tid == "b" || tid == "B") break;
                                cout << "*请输入学号：";
                                cin >> sid;
                                if (sid == "b" || sid == "B") break;
                                a.manual_allocation(tid, sid);
                            }
                        }
                        else if (opt == 'q' || opt == 'Q') break;
                    }
                }
                else if (opt == 'e' || opt == 'E')
                {//更改密码
                    w.refresh();
                    w.gotoxy(1, 1);
                    string new_password;
                    cout << "请输入新密码(输入b可退回选择界面)：";
                    cin >> new_password;
                    if (new_password == "b" || new_password == "B") continue;
                    if (a.change_password(new_password))
                    {
                        cout << "*修改成功";
                        w.loding(10);
                    }
                }
                else if (opt == 'f' || opt == 'F') break;
            }
        }
        else if (opt == 't' || opt == 'T')
        {//教师登录
            Teacher t(&mysql);
            string id, password;
            while (1)
            {//登录
                w.refresh();
                w.gotoxy(1, 1);
                cout << "亲爱的老师，请登录.....";
                w.gotoxy(1, 3);
                cout << "账号(输入b可退回上页)：";
                cin >> id;
                if (id == "b" || id == "B") break;
                w.gotoxy(1, 4);
                cout << "密码：";
                cin >> password;
                if (t.sign_in(id, password) == 1)
                {
                    cout << "*登陆成功";
                    w.loding(10);
                    break;
                }
                else
                {
                    w.loding(10);
                }
            }
            if (id == "b" || id == "B") continue;
            t.get_my_students_info();
            while (1)
            {//主循环
                w.refresh();
                w.gotoxy(1, 1);
                t.print_opt();
                while (1)
                {//操作选择
                    opt = _getch();
                    if (opt == 'a' || opt == 'A' || opt == 'b' || opt == 'B' || opt == 'c' || opt == 'C' || opt == 'd' || opt == 'D' || opt == 'e' || opt == 'E') break;
                }
                if (opt == 'a' || opt == 'A')
                {//查看学生列表
                    w.refresh();
                    w.gotoxy(1, 1);
                    cout << "学号           姓名   性别   专业               班级         联系方式" << endl;
                    for (vector<string> s : t.MyStudents)
                    {
                        cout << "*" << s[0] << "   " << s[1] << "   " << s[2] << "     " << s[3] << "   " << s[4] << "   " << s[5] << endl;
                    }
                    cout << "*按任意键返回";
                    while (!_kbhit())
                        continue;
                }
                else if (opt == 'b' || opt == 'B')
                {//查看学生毕设信息
                    w.refresh();
                    w.gotoxy(1, 1);
                    vector<vector<string>> gps;
                    gps = t.get_my_students_gp();
                    cout << "学号           姓名   毕设编号              题目               成绩         提交时间" << endl;
                    for (vector<string> i : gps)
                    {
                        if (i.size() == 6)
                            cout << "*" << i[0] << "   " << i[1] << "   " << i[2] << "       " << i[3] << "         " << i[4] << "       " << i[5] << endl;
                        else
                            cout << "*" << i[0] << "   " << i[1] << "   " << i[2] << endl;
                    }
                    cout << "*按任意键返回";
                    while (!_kbhit())
                        continue;
                }
                else if (opt == 'c' || opt == 'C')
                {//成绩批改
                    w.refresh();
                    w.gotoxy(1, 1);
                    vector<vector<string>> gps;
                    gps = t.get_my_students_gp();
                    while (1)
                    {
                        w.refresh();
                        w.gotoxy(1, 1);
                        cout << "学号           姓名   毕设编号              题目               成绩         提交时间" << endl;
                        for (vector<string> i : gps)
                        {
                            if (i.size() == 6)
                                cout << "*" << i[0] << "   " << i[1] << "   " << i[2] << "       " << i[3] << "         " << i[4] << "       " << i[5] << endl;
                            else
                                cout << "*" << i[0] << "   " << i[1] << "   " << i[2] << endl;
                        }
                        cout << endl;
                        cout << "*请选择批改模式" << endl;
                        cout << "*A：连续填入     B：选号填入      Q：返回上页" << endl;
                        while (1)
                        {//操作选择
                            opt = _getch();
                            if (opt == 'a' || opt == 'A' || opt == 'b' || opt == 'B' || opt == 'q' || opt == 'Q') break;
                        }
                        if (opt == 'a' || opt == 'A')
                        {//连续填入模式
                            for (int i = 0; i < gps.size(); i++)
                            {
                                w.refresh();
                                w.gotoxy(1, 1);
                                gps = t.get_my_students_gp();
                                cout << "学号           姓名   毕设编号              题目               成绩         提交时间" << endl;
                                for (vector<string> i : gps)
                                {
                                    if (i.size() == 6)
                                        cout << "*" << i[0] << "   " << i[1] << "   " << i[2] << "       " << i[3] << "         " << i[4] << "       " << i[5] << endl;
                                    else
                                        cout << "*" << i[0] << "   " << i[1] << "   " << i[2] << endl;
                                }
                                if (gps[i].size() == 3) continue;
                                string results;
                                cout << endl;
                                cout << "*请输入 " << gps[i][1] << " 同学的成绩(输入b退回上页)：";
                                cin >> results;
                                if (results == "b" || results == "B") break;
                                else
                                    t.change_results(gps[i][0], results);
                            }
                        }
                        else if (opt == 'b' || opt == 'B')
                        {//选号填入
                            while (1)
                            {
                                w.refresh();
                                w.gotoxy(1, 1);
                                gps = t.get_my_students_gp();
                                cout << "学号           姓名   毕设编号              题目               成绩         提交时间" << endl;
                                for (vector<string> i : gps)
                                {
                                    if (i.size() == 6)
                                        cout << "*" << i[0] << "   " << i[1] << "   " << i[2] << "       " << i[3] << "         " << i[4] << "       " << i[5] << endl;
                                    else
                                        cout << "*" << i[0] << "   " << i[1] << "   " << i[2] << endl;
                                }
                                cout << endl;
                                string id, results;
                                cout << "*请选择学生学号(输入b退回上页)：";
                                cin >> id;
                                if (id == "b" || id == "B") break;
                                cout << "*请输入成绩：";
                                cin >> results;
                                if (results == "b" || results == "B") break;
                                t.change_results(id, results);
                            }
                        }
                        else if (opt == 'q' || opt == 'Q') break;
                    }
                }
                else if (opt == 'd' || opt == 'D')
                {//修改密码
                    w.refresh();
                    w.gotoxy(1, 1);
                    string new_password;
                    cout << "请输入新密码(输入b可退回选择界面)：";
                    cin >> new_password;
                    if (new_password == "b" || new_password == "B") continue;
                    if (t.change_password(new_password))
                    {
                        cout << "*修改成功";
                        w.loding(10);
                    }
                }
                else if (opt == 'e' || opt == 'E') break;
            }
        }
        else if (opt == 's' || opt == 'S')
        {//学生登陆
            Student s(&mysql);
            string id, password;
            while (1)
            {//登录
                w.refresh();
                w.gotoxy(1, 1);
                cout << "亲爱的同学，请登录.....";
                w.gotoxy(1, 3);
                cout << "账号(输入b可退回上页)：";
                cin >> id;
                if (id == "b" || id == "B") break;
                w.gotoxy(1, 4);
                cout << "密码：";
                cin >> password;
                if (s.sign_in(id, password) == 1)
                {
                    cout << "*登陆成功";
                    w.loding(10);
                    break;
                }
                else
                {
                    w.loding(10);
                }
            }
            if (id == "b" || id == "B") continue;
            while (1)
            {//主循环
                w.refresh();
                w.gotoxy(1, 1);
                s.print_opt();
                while (1)
                {//操作选择
                    opt = _getch();
                    if (opt == 'a' || opt == 'A' || opt == 'b' || opt == 'B' || opt == 'c' || opt == 'C' || opt == 'd' || opt == 'D' || opt == 'e' || opt == 'E' || opt == 'f' || opt == 'F') break;
                }
                if (opt == 'a' || opt == 'A')
                {//提交课设
                    w.refresh();
                    w.gotoxy(1, 1);
                    string topic;
                    char Date[18];
                    time_t rawtime;
                    tm t;
                    time(&rawtime);
                    localtime_s(&t, &rawtime);//注意使用用localtime()会报c4996,因为localtime()使用参数__int64，传入32位指针会返回NULL，又浪费了阳间的30分钟，艹
                    strftime(Date, sizeof(Date), "%Y-%m-%d", &t);
                    cout << "请输入毕业设计题目(输入b可退回选择界面)：";
                    cin >> topic;
                    if (topic == "b" || topic == "B") continue;
                    if (s.submit_graduation_project(topic, Date))
                    {
                        cout << "*提交成功";
                        w.loding(10);
                    }
                }
                else if (opt == 'b' || opt == 'B')
                {//修改课设题目
                    w.refresh();
                    w.gotoxy(1, 1);
                    string topic;
                    char Date[18];
                    time_t rawtime;
                    tm t;
                    time(&rawtime);
                    localtime_s(&t, &rawtime);//注意使用用localtime()会报c4996,因为localtime()使用参数__int64，传入32位指针会返回NULL，又浪费了阳间的30分钟，艹
                    strftime(Date, sizeof(Date), "%Y-%m-%d", &t);
                    cout << "请输入毕业设计题目(输入b可退回选择界面)：";
                    cin >> topic;
                    if (topic == "b" || topic == "B") continue;
                    if (s.change_topic(topic, Date))
                    {
                        cout << "*修改成功";
                        w.loding(10);
                    }
                }
                else if (opt == 'c' || opt == 'C')
                {//查询课设信息
                    w.refresh();
                    w.gotoxy(1, 1);
                    MYSQL_ROW row;
                    row = s.query_submission();
                    if (row == NULL) cout << "您还未提交" << endl;
                    else
                    {
                        cout << "编号                 题目            成绩          提交时间" << endl;
                        if (row[2] != NULL)
                            cout << "*" << row[0] << "      " << row[1] << "         " << row[2];
                        else
                            cout << "*" << row[0] << "      " << row[1] << "              ";
                        cout << "         " << row[5] << endl;
                    }
                    cout << "*按任意键返回";
                    while (!_kbhit())
                        continue;
                }
                else if (opt == 'd' || opt == 'D')
                {//获取我的导师
                    w.refresh();
                    w.gotoxy(1, 1);
                    MYSQL_ROW row;
                    row = s.get_my_teacher();
                    cout << "教师号    姓名   性别         联系方式" << endl;
                    cout << "*" << row[0] << "       " << row[1] << "   " << row[2] << "           " << row[3] << endl;
                    cout << "*按任意键返回";
                    while (!_kbhit())
                        continue;
                }
                else if (opt == 'e' || opt == 'E')
                {//修改密码
                    w.refresh();
                    w.gotoxy(1, 1);
                    string new_password;
                    cout << "请输入新密码(输入b可退回选择界面)：";
                    cin >> new_password;
                    if (new_password == "b" || new_password == "B") continue;
                    if (s.change_password(new_password))
                    {
                        cout << "*修改成功";
                        w.loding(10);
                    }
                }
                else if (opt == 'f' || opt == 'F') break;
            }
        }
        else if (opt == 'q' || opt == 'Q') break;
    }

    w.bye();//结束画面
    w.gotoxy(0, 29);
    return 0;
}