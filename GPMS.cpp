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
{//����
public:
    Table(MYSQL* mysql,string TableName) : mysql(mysql),TableName(TableName){};//��ʼ��

    MYSQL* mysql;//��ǰ���ݿ�
    string TableName;//����

    bool ExecuteSql(MYSQL* mysql, const char* sql)
    {//ִ��SQL���
        if (mysql_query(mysql, sql))
        {//�����log������ֱ����ʾ������̨
            cerr << "ִ��sql���ʧ�ܣ�������ϢΪ�� " << mysql_error(mysql) << endl;
            return 0;
        }
        return 1;
    }
    int delete_line(string a, string b)
    {//ɾ��a��ֵ����b����
        string st = "delete from " + TableName + " where " + a + " = '" + b + "'";//SQL���
        ExecuteSql(mysql, st.c_str());//ִ��
        return 1;
    }
    int update(string a, string b, string c, string d)
    {//��a��ֵ����b���е�c��ֵ����d
        string st = "update " + TableName + " set " + c + " = '" + d + "' where " + a + " = '" + b + "'";//SQL���
        ExecuteSql(mysql, st.c_str());//ִ��
        return 1;
    }
    MYSQL_RES* find(string a, string b)
    {//����a��ֵΪb����
        MYSQL_RES* res;
        string st = "select * from " + TableName + " where " + a + " = '" + b + "'";//SQL
        if (mysql_query(mysql, st.c_str()))
        {
            cout << "����ʧ��" << mysql_error(mysql) << endl;//��ѯ����
        }
        res = mysql_store_result(mysql);//��ȡ�����
        return res;
    }
    MYSQL_RES* find()
    {//��ѯ������
        MYSQL_RES* res;
        string st = "select * from " + TableName ;//SQL���
        if (mysql_query(mysql, st.c_str()))
        {
            cout << "����ʧ��" << mysql_error(mysql) << endl;//��ѯ����
        }
        res = mysql_store_result(mysql);//��ȡ�����
        return res;
    }
};

class Students : public Table
{//ѧ������
public:
    Students(MYSQL* mysql) : Table(mysql,"students"), mysql(mysql){};//��ʼ��������ע����ʾ�Ĺ��츸����

    MYSQL* mysql;//��ǰ���ݿ�
    string TableName="students";//����

    int insert(string ID, string Name, string Sex, string Major, string Class, string Contacts)
    {//����
        string st = "insert into " + TableName + " values ('" + ID + "', '" + Name + "','" + Sex + "','" + Major + "','" + Class + "','" + Contacts + "')";//SQL���
        const char* sql = st.c_str();
        ExecuteSql(mysql, sql);
        return 1;
    }
};

class Teachers : public Table
{//��ʦ����
public:
    Teachers(MYSQL* mysql) : Table(mysql, "teachers"), mysql(mysql){};//��ʼ��

    MYSQL* mysql;//��ǰ���ݿ�
    string TableName= "teachers";//����

    int insert(string ID, string Name, string Sex, string Contacts)
    {//����
        string st = "insert into " + TableName + " values ('" + ID + "', '" + Name + "','" + Sex + "','" + Contacts + "')";//SQL���
        const char* sql = st.c_str();
        ExecuteSql(mysql, sql);
        return 1;
    }
};

class GraduationProject : public Table
{//�������
public:
    GraduationProject(MYSQL* mysql) :Table(mysql,"graduationproject"), mysql(mysql) {};//��ʼ��

    MYSQL* mysql;//��ǰ���ݿ�
    string TableName = "graduationproject";//����
    //���º�����������(��һfloat����)
    int insert(string ID, string Topic, string Results, string SubmitterID, string RaterID, string Dateline)
    {//����(���ɼ�)
        string st = "insert into " + TableName + " values ('" + ID + "', '" + Topic + "'," + Results + ",'" + SubmitterID + "','" + RaterID + "','" + Dateline + "')";//SQL���
        const char* sql = st.c_str();
        ExecuteSql(mysql, sql);
        return 1;
    }
    int insert(string ID, string Topic, string SubmitterID, string RaterID, string Dateline)
    {//����(���ذ治���ɼ�)
        string st = "insert into " + TableName + " values ('" + ID + "', '" + Topic + "',NULL,'" + SubmitterID + "','" + RaterID + "','" + Dateline + "')";//SQL���
        const char* sql = st.c_str();
        ExecuteSql(mysql, sql);
        return 1;
    }
    int delete_line(string a, string b)
    {//ɾ��a��ֵ����b����
        string st;
        if(a=="Results") st = "delete from " + TableName + " where " + a + " = " + b;//�ɼ����Ͳ���char����Ҫ����
        else st = "delete from " + TableName + " where " + a + " = '" + b + "'";
        ExecuteSql(mysql, st.c_str());
        return 1;
    }
    int update(string a, string b, string c, string d)
    {//��a��ֵ����b���е�c��ֵ����d
        string st;
        if(a=="Results"&&c=="Results") st = "update " + TableName + " set " + c + " = " + d + " where " + a + " = " + b;
        else if(a == "Results") st = "update " + TableName + " set " + c + " = '" + d + "' where " + a + " = " + b;
        else if(c == "Results") st = "update " + TableName + " set " + c + " = " + d + " where " + a + " = '" + b + "'";
        else st = "update " + TableName + " set " + c + " = '" + d + "' where " + a + " = '" + b + "'";
        ExecuteSql(mysql, st.c_str());
        return 1;
    }
    MYSQL_RES* find(string a, string b)
    {//����a��ֵΪb����
        string st;
        MYSQL_RES* res;
        if(a=="Results") st = "select * from " + TableName + " where " + a + " = " + b;
        else st = "select * from " + TableName + " where " + a + " = '" + b + "'";
        if (mysql_query(mysql, st.c_str()))
        {
            cout << "����ʧ��" << mysql_error(mysql) << endl;//��ѯ����
        }
        res = mysql_store_result(mysql);//��ȡ�����
        return res;
    }
};

class TutorAssignment : public Table
{//��ʦ�������
public:
    TutorAssignment(MYSQL* mysql) : Table(mysql, "tutorassignment"), mysql(mysql) {};//��ʼ��

    MYSQL* mysql;
    string TableName = "tutorassignment";

    int insert(string TutorID, string StudentID)
    {//����
        string st = "insert into " + TableName + " values ('" + TutorID + "', '" + StudentID + "')";
        const char* sql = st.c_str();
        ExecuteSql(mysql, sql);
        return 1;
    }
};

class Account : public Table
{//�˺ű���
public:
    Account(MYSQL* mysql) : Table(mysql, "account"), mysql(mysql) {};//��ʼ��

    MYSQL* mysql;
    string TableName = "account";

    int insert(string Number, string Password)
    {//����
        string st = "insert into " + TableName + " values ('" + Number + "', '" + Password + "')";
        const char* sql = st.c_str();
        ExecuteSql(mysql, sql);
        return 1;
    }
};

class User
{//�û���
public:
    User(MYSQL* mysql) : mysql(mysql),a(mysql), s(mysql), t(mysql), g(mysql) {};

    MYSQL* mysql;
    Account a;
    Students s;
    TutorAssignment t;
    GraduationProject g;
    string id;

    int change_password(string new_password)
    {//�޸�����
        a.update("Number",id,"Password",new_password);
        return 1;
    }

    MYSQL_ROW query_submission()
    {//��ѯ������Ϣ
        MYSQL_RES* res; //һ��������ṹ��
        MYSQL_ROW row;  //char** ��ά���飬���һ������¼
        string r;
        res = g.find("SubmitterID", id);
        row = mysql_fetch_row(res);
        if (row == NULL) return NULL;
        return row;
    }

};

class Student :public User
{//ѧ����
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
    {//��¼�˺�����ƥ�䡢Ȩ��ƥ��
        string Number, Password;
        MYSQL_RES* res;
        MYSQL_ROW row;

        if (res = a.find("Number", Number_in))
        {
            if (!(row = mysql_fetch_row(res)))
            {
                cout << "*�˺Ų�����" << endl;
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
                cout << "*�������" << endl;
                return 0;
            }
        }
        return 0;
    }

    int submit_graduation_project(string Topic, string Dateline)
    {//�ύ����
        MYSQL_RES* res; //һ��������ṹ��
        MYSQL_ROW row;  //char** ��ά���飬���һ������¼
        string ID;
        res = t.find("StudentID", id);
        row = mysql_fetch_row(res);
        ID = id + row[0];
        g.insert(ID, Topic, id, row[0], Dateline);
        return 1;
    }

    int change_topic(string new_topic, string new_dateline)
    {//�޸ı�����Ŀ
        g.update("SubmitterID", id, "Topic", new_topic);
        g.update("SubmitterID", id, "Dateline", new_dateline);
        return 1;
    }

    MYSQL_ROW get_my_teacher()
    {//��ȡ�ҵĵ�ʦ��Ϣ
        vector<string> v;
        string t_id;
        MYSQL_RES* res; //һ��������ṹ��
        MYSQL_ROW row;  //char** ��ά���飬���һ������¼
        res = t.find("StudentID", id);
        row = mysql_fetch_row(res);
        t_id = row[0];
        res = ts.find("ID", t_id);
        row = mysql_fetch_row(res);
        return row;
    }

    int print_opt()
    {//����ѡ��
        cout << "��ѡ�������" << endl;
        cout << "*A���ύ����       B���޸Ŀ�����Ŀ     C���鿴��ҵ�����Ϣ" << endl;
        cout << "*D���鿴�ҵĵ�ʦ   E���޸�����         F���˳���¼";
        return 1;
    }

};

class Teacher :public User
{//��ʦ��
public:
    Teacher(MYSQL* mysql) :User(mysql), a(mysql), mysql(mysql), s(mysql), t(mysql), g(mysql) {};

    MYSQL* mysql;
    vector<vector<string>> MyStudents;//ѧ���б�
    string id;
    Account a;
    Students s;
    TutorAssignment t;
    GraduationProject g;

    int sign_in(string Number_in, string Password_in)
    {//��¼�˺�����ƥ�䡢Ȩ��ƥ��
        string Number, Password;
        MYSQL_RES* res;
        MYSQL_ROW row;

        if (res = a.find("Number", Number_in))
        {
            if (!(row = mysql_fetch_row(res)))
            {
                cout << "*�˺Ų�����" << endl;
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
                cout << "*�������" << endl;
                return 0;
            }
        }
        return 0;
    }

    int get_my_students_info()
    {//��ȡ�ҵ�ѧ����Ϣ�б�
        vector<string> ids;
        MYSQL_RES* res; //һ��������ṹ��
        MYSQL_ROW row;  //char** ��ά���飬���һ������¼
        res = t.find("TutorID", id);
        while (row = mysql_fetch_row(res))
        {//��ȡ�Ҹ����ѧ����ѧ��
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
    {//��ȡ������Ϣ
        vector<vector<string>> gps;
        MYSQL_RES* res; //һ��������ṹ��
        MYSQL_ROW row;  //char** ��ά���飬���һ������¼
        for (vector<string> i : MyStudents)
        {
            res = g.find("SubmitterID", i[0]);
            row = mysql_fetch_row(res);
            if (row == NULL) gps.push_back({ i[0],i[1],"δ�ύ" });
            else
            {
                if(row[2]==NULL)
                    gps.push_back({ i[0],i[1],row[0],row[1] ,"δ����" ,row[5] });
                else
                    gps.push_back({ i[0],i[1],row[0],row[1] ,row[2] ,row[5] });
            }
        }
        return gps;
    }

    int change_results(string id, string results)
    {//�ύ�ɼ�
        g.update("SubmitterID", id, "Results", results);
        return 1;
    }

    int print_opt()
    {//����ѡ��
        cout << "��ѡ�������" << endl;
        cout << "*A���鿴ѧ���б�      B���鿴ѧ��������Ϣ     C���ɼ�¼��" << endl;
        cout << "*D���޸�����          E���˳���¼";
        return 1;
    }
};

class Administrator :public User
{//����Ա��
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
    {//��¼�˺�����ƥ�䡢Ȩ��ƥ��
        string Number, Password;
        MYSQL_RES* res;
        MYSQL_ROW row;

        if (res = a.find("Number", Number_in))
        {
            if (!(row = mysql_fetch_row(res)))
            {
                cout << "*�˺Ų�����" << endl;
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
                cout << "*�������" << endl;
                return 0;
            }
        }
        return 0;
    }

    vector<vector<string>> get_students()
    {//��ȡѧ����
        vector<vector<string>> v;
        MYSQL_RES* res; //һ��������ṹ��
        MYSQL_ROW row;  //char** ��ά���飬���һ������¼
        res = s.find();
        while (row = mysql_fetch_row(res))
        {
            v.push_back({ row[0],row[1],row[2] ,row[3] ,row[4] ,row[5] });
        }
        return v;
    }

    vector<vector<string>> get_teachers()
    {//��ȡ��ʦ��
        vector<vector<string>> v;
        MYSQL_RES* res; //һ��������ṹ��
        MYSQL_ROW row;  //char** ��ά���飬���һ������¼
        res = ts.find();
        while (row = mysql_fetch_row(res))
        {
            v.push_back({ row[0],row[1],row[2] ,row[3] });
        }
        return v;
    }

    vector<vector<string>> get_tuor_assignment()
    {//��ȡ������Ϣ��
        vector<vector<string>> v;
        string t_name, s_name;
        MYSQL_RES* res1; //һ��������ṹ��
        MYSQL_RES* res2; //һ��������ṹ��
        MYSQL_ROW row1;  //char** ��ά���飬���һ������¼
        MYSQL_ROW row2;  //char** ��ά���飬���һ������¼
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
    {//�������
        MYSQL_RES* res; //һ��������ṹ��
        MYSQL_ROW row;  //char** ��ά���飬���һ������¼
        vector<string> sid, tid;
        vector<int> r;//�������
        unsigned long tn,sn;
        res = s.find();
        sn = res->row_count;//ѧ������
        while (row = mysql_fetch_row(res)) sid.push_back(row[0]);//��ȡ����ѧ��
        res = ts.find();
        tn = res->row_count;//��ʦ����
        while (row = mysql_fetch_row(res)) tid.push_back(row[0]);//��ȡ���н�ʦ��
        while (r.size() != sn)
        {//�����������
            int i = rand() % sn;
            if (find(r.begin(), r.end(), i) == r.end()) r.push_back(i);
        }
        for (int i = 0; i < tn; i++)
        {//������������
            for (int j = 0; j < sn / tn; j++)
            {
                t.insert(tid[i], sid[*(end(r)-1)]);
                r.pop_back();
            }
        }
        while (!r.empty())
        {//��ʣ���˶������һ����ʦ
            t.insert(*(end(tid) - 1), sid[*(end(r) - 1)]);
            r.pop_back();
        }
        return 0;
    }

    int manual_allocation(string tid,string sid)
    {//�˹�����
        t.insert(tid, sid);
        return 1;
    }

    int print_opt()
    {//����ѡ��
        cout << "��ѡ�������" << endl;
        cout << "*A���鿴ѧ���б�      B���鿴��ʦ�б�     C���鿴�����" << endl;
        cout << "*D����ʦ����          E���޸�����         F���˳���¼";
        return 1;
    }
};

class Windows
{
public:
    Windows()
    {//��ʼ���߿�
        vector<char> r;
        for (int i = 0; i < 100; i++) r.push_back('*');//����
        frame.push_back(r);
        for (int i = 1; i <= 98; i++) r[i] = ' ';
        for (int i = 0; i < 27; i++) frame.push_back(r);//�հ�����
        for (int i = 1; i <= 98; i++) r[i] = '*';//����
        frame.push_back(r);
    };

    vector<vector<char>> frame;//�߿�100*27

    inline void gotoxy(short x, short y)
    {//system.h̫�����ˣ�ֻ���Լ�д��gotoxy������
        COORD pos = { x,y };
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);// ��ȡ��׼����豸���
        SetConsoleCursorPosition(hOut, pos);//���������ֱ���ָ���ĸ����壬����λ��
    }

    inline void hide()
    {//���ع��
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO CursorInfo;
        GetConsoleCursorInfo(handle, &CursorInfo);//��ȡ����̨�����Ϣ
        CursorInfo.bVisible = false; //���ؿ���̨���
        SetConsoleCursorInfo(handle, &CursorInfo);//���ÿ���̨���״̬
    }

    void refresh()
    {//�������ƿ��
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
    {//���غ���
        for (int i=0; i < n; i++)
        {
            Sleep(100);
            cout << '.';
        }
    }

    void welcome()
    {//�����ӭ����
        refresh();
        gotoxy(1,  3); cout << "   ��  ��  ��      ����������      ����              ��������        ������      ������  ������  ";
        gotoxy(1,  4); cout << "   ��  ��  ��      ��              ��              ��        ��    ��      ��      ����  ����    ";
        gotoxy(1,  5); cout << "   ��  ��  ��      ��              ��              ��        ��  ��          ��    ����  ����    ";
        gotoxy(1,  6); cout << "   ��  ��  ��      ��              ��            ��              ��          ��    ����  ����    ";
        gotoxy(1,  7); cout << "   ��  ��  ��      ����������      ��            ��              ��          ��    ����  ����    ";
        gotoxy(1,  8); cout << "   ��  ��  ��      ��              ��            ��              ��          ��    ����  ����    ";
        gotoxy(1,  9); cout << "   ����  ����      ��              ��            ��              ��          ��    ��  ��  ��    ";
        gotoxy(1, 10); cout << "     ��  ��        ��              ��            ��              ��          ��    ��  ��  ��    ";
        gotoxy(1, 11); cout << "     ��  ��        ��              ��             ��         ��  ��          ��    ��  ��  ��    ";
        gotoxy(1, 12); cout << "     ��  ��        ��              ��              ��      ��      ��      ��      ��  ��  ��    ";
        gotoxy(1, 13); cout << "     ��  ��        ����������      ������������      ������          ������      ����  ��  ����  ";
        gotoxy(35, 20);
        loding(25);
    }

    void bye()
    {//�˳�����
        refresh();
        gotoxy(1, 1);
        cout << "��л����ʹ��";
        loding(10);
    }
};

int main()
{
    MYSQL mysql; //һ�����ݿ�ṹ��
    Windows w;//���������
    MYSQL_RES* res; //һ��������ṹ��
    MYSQL_ROW row;  //char** ��ά���飬���һ������¼
    char opt = '0';//ѡ��

    w.hide();//����ָ��
    w.welcome();//�����ӭ����
    w.refresh();//ˢ�¿��

    mysql_init(&mysql);//��ʼ�����ݿ�
    mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");//���ñ��뷽ʽ
    if (mysql_real_connect(&mysql, "localhost", "root", "102576", "gpmsd", 3306, NULL, 0) == NULL)
    {//�������ݿ�,�������ʧ�ܾͰ�����ʧ�ܵ���Ϣ��ʾ����
        w.gotoxy(1, 1);
        cout << (mysql_error(&mysql));
    }
    else
    {//���ӳɹ�
        w.gotoxy(1, 1);
        cout << "���ݿ����ӳɹ�";
        w.loding(10);
    }

    while (1)
    {
        w.refresh();//����ˢ��
        w.gotoxy(1, 1);
        cout << "A/a������Ա��½     T/t����ʦ��¼      S/s��ѧ����¼" << endl;
        cout << endl;
        cout << "*��ѡ���¼Ȩ��";

        while (1)
        {//��½���ѡ��
            opt = _getch();//��ȡ�ַ������ԣ�c++��conio.h�е�getch()�������滻��_getch()
            if (opt == 'a' || opt == 'A' || opt == 't' || opt == 'T' || opt == 's' || opt == 'S' || opt == 'q' || opt == 'Q') break;
        }
        if (opt == 'a' || opt == 'A')
        {//����Ա��½
            Administrator a(&mysql);
            string id, password;
            while (1)
            {//��¼
                w.refresh();
                w.gotoxy(1, 1);
                cout << "�װ��Ĺ���Ա�����¼.....";
                w.gotoxy(1, 3);
                cout << "�˺�(����b���˻���ҳ)��";
                cin >> id;
                if (id == "b" || id == "B") break;
                w.gotoxy(1, 4);
                cout << "���룺";
                cin >> password;
                if (a.sign_in(id, password) == 1)
                {
                    cout << "*��½�ɹ�";
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
            {//��ѭ��
                w.refresh();
                w.gotoxy(1, 1);
                a.print_opt();
                while (1)
                {//����ѡ��
                    opt = _getch();
                    if (opt == 'a' || opt == 'A' || opt == 'b' || opt == 'B' || opt == 'c' || opt == 'C' || opt == 'd' || opt == 'D' || opt == 'e' || opt == 'E' || opt == 'f' || opt == 'F') break;
                }
                if (opt == 'a' || opt == 'A')
                {//�鿴ѧ����
                    w.refresh();
                    w.gotoxy(1, 1);
                    cout << "ѧ��           ����   �Ա�   רҵ               �༶         ��ϵ��ʽ" << endl;
                    vector<vector<string>> v = a.get_students();
                    for (vector<string> s : v)
                    {
                        cout << "*" << s[0] << "   " << s[1] << "   " << s[2] << "     " << s[3] << "   " << s[4] << "   " << s[5] << endl;
                    }
                    cout << "*�����������";
                    while (!_kbhit())
                        continue;
                }
                else if (opt == 'b' || opt == 'B')
                {//�鿴��ʦ�б�
                    w.refresh();
                    w.gotoxy(1, 1);
                    cout << "��ʦ��    ����   �Ա�         ��ϵ��ʽ" << endl;
                    vector<vector<string>> v = a.get_teachers();
                    for (vector<string> s : v)
                    {
                        cout << "*" << s[0] << "       " << s[1] << "   " << s[2] << "           " << s[3] << endl;
                    }
                    cout << "*�����������";
                    while (!_kbhit())
                        continue;
                }
                else if (opt == 'c' || opt == 'C')
                {//��ȡ�����
                    w.refresh();
                    w.gotoxy(1, 1);
                    cout << "��ʦ��    ����          ѧ��             ����" << endl;
                    vector<vector<string>> v = a.get_tuor_assignment();
                    for (vector<string> s : v)
                    {
                        cout << "*" << s[0] << "       " << s[1] << "   " << "����" << "   " << s[2] << "     " << s[3] << endl;
                    }
                    cout << "*�����������";
                    while (!_kbhit())
                        continue;
                }
                else if (opt == 'd' || opt == 'D')
                {//��ʦ����
                    w.refresh();
                    w.gotoxy(1, 1);
                    vector<vector<string>> gps;
                    while (1)
                    {
                        w.refresh();
                        w.gotoxy(1, 1);
                        cout << "��ѡ�����ģʽ" << endl;
                        cout << "*A���������     B���˹�����      Q��������ҳ" << endl;
                        while (1)
                        {//����ѡ��
                            opt = _getch();
                            if (opt == 'a' || opt == 'A' || opt == 'b' || opt == 'B' || opt == 'q' || opt == 'Q') break;
                        }
                        if (opt == 'a' || opt == 'A')
                        {//�������
                            a.random_allocation();
                            w.refresh();
                            w.gotoxy(1, 1);
                            cout << "����ɹ�";
                            w.loding(10);
                        }
                        else if (opt == 'b' || opt == 'B')
                        {//�˹�����
                            while (1)
                            {
                                w.refresh();
                                w.gotoxy(1, 1);
                                string sid, tid;
                                cout << "�������ʦ��(����b�˻���ҳ)��";
                                cin >> tid;
                                if (tid == "b" || tid == "B") break;
                                cout << "*������ѧ�ţ�";
                                cin >> sid;
                                if (sid == "b" || sid == "B") break;
                                a.manual_allocation(tid, sid);
                            }
                        }
                        else if (opt == 'q' || opt == 'Q') break;
                    }
                }
                else if (opt == 'e' || opt == 'E')
                {//��������
                    w.refresh();
                    w.gotoxy(1, 1);
                    string new_password;
                    cout << "������������(����b���˻�ѡ�����)��";
                    cin >> new_password;
                    if (new_password == "b" || new_password == "B") continue;
                    if (a.change_password(new_password))
                    {
                        cout << "*�޸ĳɹ�";
                        w.loding(10);
                    }
                }
                else if (opt == 'f' || opt == 'F') break;
            }
        }
        else if (opt == 't' || opt == 'T')
        {//��ʦ��¼
            Teacher t(&mysql);
            string id, password;
            while (1)
            {//��¼
                w.refresh();
                w.gotoxy(1, 1);
                cout << "�װ�����ʦ�����¼.....";
                w.gotoxy(1, 3);
                cout << "�˺�(����b���˻���ҳ)��";
                cin >> id;
                if (id == "b" || id == "B") break;
                w.gotoxy(1, 4);
                cout << "���룺";
                cin >> password;
                if (t.sign_in(id, password) == 1)
                {
                    cout << "*��½�ɹ�";
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
            {//��ѭ��
                w.refresh();
                w.gotoxy(1, 1);
                t.print_opt();
                while (1)
                {//����ѡ��
                    opt = _getch();
                    if (opt == 'a' || opt == 'A' || opt == 'b' || opt == 'B' || opt == 'c' || opt == 'C' || opt == 'd' || opt == 'D' || opt == 'e' || opt == 'E') break;
                }
                if (opt == 'a' || opt == 'A')
                {//�鿴ѧ���б�
                    w.refresh();
                    w.gotoxy(1, 1);
                    cout << "ѧ��           ����   �Ա�   רҵ               �༶         ��ϵ��ʽ" << endl;
                    for (vector<string> s : t.MyStudents)
                    {
                        cout << "*" << s[0] << "   " << s[1] << "   " << s[2] << "     " << s[3] << "   " << s[4] << "   " << s[5] << endl;
                    }
                    cout << "*�����������";
                    while (!_kbhit())
                        continue;
                }
                else if (opt == 'b' || opt == 'B')
                {//�鿴ѧ��������Ϣ
                    w.refresh();
                    w.gotoxy(1, 1);
                    vector<vector<string>> gps;
                    gps = t.get_my_students_gp();
                    cout << "ѧ��           ����   ������              ��Ŀ               �ɼ�         �ύʱ��" << endl;
                    for (vector<string> i : gps)
                    {
                        if (i.size() == 6)
                            cout << "*" << i[0] << "   " << i[1] << "   " << i[2] << "       " << i[3] << "         " << i[4] << "       " << i[5] << endl;
                        else
                            cout << "*" << i[0] << "   " << i[1] << "   " << i[2] << endl;
                    }
                    cout << "*�����������";
                    while (!_kbhit())
                        continue;
                }
                else if (opt == 'c' || opt == 'C')
                {//�ɼ�����
                    w.refresh();
                    w.gotoxy(1, 1);
                    vector<vector<string>> gps;
                    gps = t.get_my_students_gp();
                    while (1)
                    {
                        w.refresh();
                        w.gotoxy(1, 1);
                        cout << "ѧ��           ����   ������              ��Ŀ               �ɼ�         �ύʱ��" << endl;
                        for (vector<string> i : gps)
                        {
                            if (i.size() == 6)
                                cout << "*" << i[0] << "   " << i[1] << "   " << i[2] << "       " << i[3] << "         " << i[4] << "       " << i[5] << endl;
                            else
                                cout << "*" << i[0] << "   " << i[1] << "   " << i[2] << endl;
                        }
                        cout << endl;
                        cout << "*��ѡ������ģʽ" << endl;
                        cout << "*A����������     B��ѡ������      Q��������ҳ" << endl;
                        while (1)
                        {//����ѡ��
                            opt = _getch();
                            if (opt == 'a' || opt == 'A' || opt == 'b' || opt == 'B' || opt == 'q' || opt == 'Q') break;
                        }
                        if (opt == 'a' || opt == 'A')
                        {//��������ģʽ
                            for (int i = 0; i < gps.size(); i++)
                            {
                                w.refresh();
                                w.gotoxy(1, 1);
                                gps = t.get_my_students_gp();
                                cout << "ѧ��           ����   ������              ��Ŀ               �ɼ�         �ύʱ��" << endl;
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
                                cout << "*������ " << gps[i][1] << " ͬѧ�ĳɼ�(����b�˻���ҳ)��";
                                cin >> results;
                                if (results == "b" || results == "B") break;
                                else
                                    t.change_results(gps[i][0], results);
                            }
                        }
                        else if (opt == 'b' || opt == 'B')
                        {//ѡ������
                            while (1)
                            {
                                w.refresh();
                                w.gotoxy(1, 1);
                                gps = t.get_my_students_gp();
                                cout << "ѧ��           ����   ������              ��Ŀ               �ɼ�         �ύʱ��" << endl;
                                for (vector<string> i : gps)
                                {
                                    if (i.size() == 6)
                                        cout << "*" << i[0] << "   " << i[1] << "   " << i[2] << "       " << i[3] << "         " << i[4] << "       " << i[5] << endl;
                                    else
                                        cout << "*" << i[0] << "   " << i[1] << "   " << i[2] << endl;
                                }
                                cout << endl;
                                string id, results;
                                cout << "*��ѡ��ѧ��ѧ��(����b�˻���ҳ)��";
                                cin >> id;
                                if (id == "b" || id == "B") break;
                                cout << "*������ɼ���";
                                cin >> results;
                                if (results == "b" || results == "B") break;
                                t.change_results(id, results);
                            }
                        }
                        else if (opt == 'q' || opt == 'Q') break;
                    }
                }
                else if (opt == 'd' || opt == 'D')
                {//�޸�����
                    w.refresh();
                    w.gotoxy(1, 1);
                    string new_password;
                    cout << "������������(����b���˻�ѡ�����)��";
                    cin >> new_password;
                    if (new_password == "b" || new_password == "B") continue;
                    if (t.change_password(new_password))
                    {
                        cout << "*�޸ĳɹ�";
                        w.loding(10);
                    }
                }
                else if (opt == 'e' || opt == 'E') break;
            }
        }
        else if (opt == 's' || opt == 'S')
        {//ѧ����½
            Student s(&mysql);
            string id, password;
            while (1)
            {//��¼
                w.refresh();
                w.gotoxy(1, 1);
                cout << "�װ���ͬѧ�����¼.....";
                w.gotoxy(1, 3);
                cout << "�˺�(����b���˻���ҳ)��";
                cin >> id;
                if (id == "b" || id == "B") break;
                w.gotoxy(1, 4);
                cout << "���룺";
                cin >> password;
                if (s.sign_in(id, password) == 1)
                {
                    cout << "*��½�ɹ�";
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
            {//��ѭ��
                w.refresh();
                w.gotoxy(1, 1);
                s.print_opt();
                while (1)
                {//����ѡ��
                    opt = _getch();
                    if (opt == 'a' || opt == 'A' || opt == 'b' || opt == 'B' || opt == 'c' || opt == 'C' || opt == 'd' || opt == 'D' || opt == 'e' || opt == 'E' || opt == 'f' || opt == 'F') break;
                }
                if (opt == 'a' || opt == 'A')
                {//�ύ����
                    w.refresh();
                    w.gotoxy(1, 1);
                    string topic;
                    char Date[18];
                    time_t rawtime;
                    tm t;
                    time(&rawtime);
                    localtime_s(&t, &rawtime);//ע��ʹ����localtime()�ᱨc4996,��Ϊlocaltime()ʹ�ò���__int64������32λָ��᷵��NULL�����˷��������30���ӣ�ܳ
                    strftime(Date, sizeof(Date), "%Y-%m-%d", &t);
                    cout << "�������ҵ�����Ŀ(����b���˻�ѡ�����)��";
                    cin >> topic;
                    if (topic == "b" || topic == "B") continue;
                    if (s.submit_graduation_project(topic, Date))
                    {
                        cout << "*�ύ�ɹ�";
                        w.loding(10);
                    }
                }
                else if (opt == 'b' || opt == 'B')
                {//�޸Ŀ�����Ŀ
                    w.refresh();
                    w.gotoxy(1, 1);
                    string topic;
                    char Date[18];
                    time_t rawtime;
                    tm t;
                    time(&rawtime);
                    localtime_s(&t, &rawtime);//ע��ʹ����localtime()�ᱨc4996,��Ϊlocaltime()ʹ�ò���__int64������32λָ��᷵��NULL�����˷��������30���ӣ�ܳ
                    strftime(Date, sizeof(Date), "%Y-%m-%d", &t);
                    cout << "�������ҵ�����Ŀ(����b���˻�ѡ�����)��";
                    cin >> topic;
                    if (topic == "b" || topic == "B") continue;
                    if (s.change_topic(topic, Date))
                    {
                        cout << "*�޸ĳɹ�";
                        w.loding(10);
                    }
                }
                else if (opt == 'c' || opt == 'C')
                {//��ѯ������Ϣ
                    w.refresh();
                    w.gotoxy(1, 1);
                    MYSQL_ROW row;
                    row = s.query_submission();
                    if (row == NULL) cout << "����δ�ύ" << endl;
                    else
                    {
                        cout << "���                 ��Ŀ            �ɼ�          �ύʱ��" << endl;
                        if (row[2] != NULL)
                            cout << "*" << row[0] << "      " << row[1] << "         " << row[2];
                        else
                            cout << "*" << row[0] << "      " << row[1] << "              ";
                        cout << "         " << row[5] << endl;
                    }
                    cout << "*�����������";
                    while (!_kbhit())
                        continue;
                }
                else if (opt == 'd' || opt == 'D')
                {//��ȡ�ҵĵ�ʦ
                    w.refresh();
                    w.gotoxy(1, 1);
                    MYSQL_ROW row;
                    row = s.get_my_teacher();
                    cout << "��ʦ��    ����   �Ա�         ��ϵ��ʽ" << endl;
                    cout << "*" << row[0] << "       " << row[1] << "   " << row[2] << "           " << row[3] << endl;
                    cout << "*�����������";
                    while (!_kbhit())
                        continue;
                }
                else if (opt == 'e' || opt == 'E')
                {//�޸�����
                    w.refresh();
                    w.gotoxy(1, 1);
                    string new_password;
                    cout << "������������(����b���˻�ѡ�����)��";
                    cin >> new_password;
                    if (new_password == "b" || new_password == "B") continue;
                    if (s.change_password(new_password))
                    {
                        cout << "*�޸ĳɹ�";
                        w.loding(10);
                    }
                }
                else if (opt == 'f' || opt == 'F') break;
            }
        }
        else if (opt == 'q' || opt == 'Q') break;
    }

    w.bye();//��������
    w.gotoxy(0, 29);
    return 0;
}