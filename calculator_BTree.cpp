/*
采用二叉树的结构，能进行多位整数、小数、负数和负小数的四则运算，具有一定的健壮性

*/

#include<stdio.h>
#include<stdlib.h>

#define OK 1
#define ERROR 0
typedef int Status;
enum{//字符状态描述
    NUMBER,//数字
    CHARACTER,//字符
    DECIMAL,//小数
    NEGATIVE,//负数
    NEGATIVE_DECIMAL//负小数
    }ch_state;
int n=1;//标记小数点后的位数

typedef struct TreeNode
{//二叉树节点
    union
    {
        double opnd;//运算数
        char optr;//运算符
    }data;
    struct TreeNode *lchild,*rchild;//左右孩子指针
}TreeNode,*ExpTree;

typedef struct StackNode_optr
{//定义符号栈节点
    char data;//数据域
    struct StackNode_optr *next;//指针域
}StackNode_optr,*LinkStack_optr;

typedef struct StackNode_expt
{//定义根节点栈节点
    ExpTree data;//数据域
    struct StackNode_expt *next;//指针域
}StackNode_expt,*LinkStack_expt;

Status InitBiTree(ExpTree &T)
{//初始化树节点
    T=new TreeNode;//创建节点
    T->lchild=NULL;T->rchild=NULL;//初始化孩子指针
    return OK;
}

Status InitStack_optr(LinkStack_optr &S)
{//符号栈初始化
    S=NULL;
    return OK;
}

Status InitStack_expt(LinkStack_expt &S)
{//根节点栈初始化
    S=NULL;
    return OK;
}

Status Push_optr(LinkStack_optr &S,char e)
{//符号栈入栈
    LinkStack_optr p;
    p=new StackNode_optr;//生成新结点
    p->data=e;//设置数据域
    p->next=S;//插入栈顶
    S=p;//修改栈顶指针
    return OK;
}

Status Push_expt(LinkStack_expt &S,ExpTree e)
{//根节点栈入栈
    LinkStack_expt p;
    p=new StackNode_expt;//生成新结点
    p->data=e;//设置数据域
    p->next=S;//插入栈顶
    S=p;//修改栈顶指针
    return OK;
}

Status Pop_optr(LinkStack_optr &S,char &e)
{//符号栈出栈
    LinkStack_optr p;
    if(S==NULL) return ERROR;//栈空
    e=S->data;//保留栈顶元素
    p=S;//临时保存栈顶元素空间
    S=S->next;//修改栈顶指针
    delete p;//释放空间
    return OK;
}

Status Pop_expt(LinkStack_expt &S,ExpTree &e)
{//根节点栈出栈
    LinkStack_expt p;
    if(S==NULL) return ERROR;//栈空
    e=S->data;//保留栈顶元素
    p=S;//临时保存栈顶元素空间
    S=S->next;//修改栈顶指针
    delete p;//释放空间
    return OK;
}

char GetTop_optr(LinkStack_optr S)
{//取符号栈顶元素
    if(S!=NULL)//栈非空
    return S->data;//返回栈顶的值
}

bool In(char c)
{//判定运算符
    switch(c)
    {
        case '+' : return true;
        case '-' : return true;
        case '*' : return true;
        case '/' : return true;
        case '#' : return true;
        case '(' : return true;
        case ')' : return true;
        default : return false;
    }
}

char Precede(char t1,char t2)
{//判断优先级
    char f;
    switch(t2)
    {
        case '+':
            if(t1=='('||t1=='#') f='<';
            else f='>';
            break;
        case '-':
            if(t1=='('||t1=='#') f='<';
            else f='>';
            break;
        case '*':
            if(t1=='+'||t1=='-'||t1=='('||t1=='#') f='<';
            else f='>';
            break;
        case '/':
            if(t1=='+'||t1=='-'||t1=='('||t1=='#') f='<';
            else f='>'; break;
        case '(':
                if(t1==')') return 'X';
                else f='<';
                break;
        case ')':
            if(t1=='(') f='=';
            else if(t1=='#') return 'X';
            else f='>';
            break;
        case '#':
            if(t1=='#') f='=';
            else if(t1=='(') return 'X';
            else f='>';
            break;
    }
    return f;
}

Status CreateExpTree_opnd(ExpTree &T,double e)
{//创建以运算数为根节点的二叉树
    InitBiTree(T);//初始化节点
    T->data.opnd=e;//置入运算数
    T->lchild=NULL;//孩子节点置空
    T->rchild=NULL;
    return OK;
}

Status CreateExpTree_optr(ExpTree &T,ExpTree L,ExpTree R,char theta)
{//创建以运算符为根节点，运算数为孩子节点的二叉树
    InitBiTree(T);//初始化树
    T->data.optr=theta;//置入运算符
    T->lchild=L;//链接孩子节点
    T->rchild=R;
    return OK;
}

Status Char_to_Number(LinkStack_expt &EXPT,char ch)
{//将字符转换为数字并压入栈
    double x;
    ExpTree e;
    switch (ch_state)
    {
        case NUMBER://多位数字
            Pop_expt(EXPT,e);//弹出高位数字
            x=(e->data.opnd)*10+(double)(ch-'0');//合并数字
            e->data.opnd=x;//更新数据域
            Push_expt(EXPT,e);//重新入栈
            break;
        case CHARACTER://一位数字
            CreateExpTree_opnd(e,(int)(ch-'0'));//以ch为根创建一颗二叉树
            Push_expt(EXPT,e);//将刚刚创建的根节点入栈
            break;
        case DECIMAL://浮点数
            Pop_expt(EXPT,e);//弹出高位数字
            x=(double)(ch-'0');//转化为小数点后面的数字
            for(int i=1;i<=n;i++) x=x/10;
            e->data.opnd=e->data.opnd+x;//更新数据域
            Push_expt(EXPT,e);//重新入栈
            n++;//标记小数位数
            break;
        case NEGATIVE://负数
            CreateExpTree_opnd(e,(0-(int)(ch-'0')));//以ch为根创建一颗二叉树
            Push_expt(EXPT,e);//将刚刚创建的根节点入栈
            break;
        case NEGATIVE_DECIMAL://负小数
            Pop_expt(EXPT,e);//弹出高位数字
            x=0-(double)(ch-'0');//转化为小数点后面的数字
            for(int i=1;i<=n;i++) x=x/10;
            e->data.opnd=e->data.opnd+x;//更新数据域
            Push_expt(EXPT,e);//重新入栈
            n++;//标记小数位数
            break;
        default:
            return ERROR;
    }
    return OK;
}

Status Error_detection(char ch,char ched)
{//检查输入错误
    if(ched=='#') return OK;
    else if(ch=='(') return OK;
    else if(ched=='('&&(ch=='-'||ch=='(')) return OK;
    else if(ched==')') return OK;
    else if(!In(ched)) return OK;
    else return ERROR;
}

Status InitExpTree(ExpTree &T)
{//表达式树创建
    LinkStack_expt EXPT;//根节点栈
    LinkStack_optr OPTR;//符号栈
    char ch,theta,ched;
    ExpTree R,a,b;
    InitStack_expt(EXPT);//初始化EXPT栈
    InitStack_optr(OPTR);//初始化OPTR栈
    fflush(stdin);//清空缓冲区
    ch=getchar();
    ched=ch;//保存ch的历史值
    while(ch!='#')
    {//检测表达式是否以#开头
        printf("表达式未以 “#” 开头，请重新输入：\n");
        fflush(stdin);//清空缓冲区
        ch=getchar();
        ched=ch;//保存ch的历史值
    }
    ch_state=CHARACTER;//标记ch为字符
    Push_optr(OPTR,ch);//'#'压入符号栈
    ched=ch;//保存ch的历史值
    ch=getchar();
    if(ch=='\n') return ERROR;//检错
    while(ch!='#'||GetTop_optr(OPTR)!='#')//表达式没有扫描完毕或者栈顶元素不为'#'
    {
        if(!In(ch))//ch不是运算符
        {
            if((ch<'0'||ch>'9')&&(ch!='.'))
            return ERROR;//检错
            if(ch=='.'&&ch_state==NUMBER) //如果是小数点则标记,再获取下一个字符
            {
                ch_state=DECIMAL;
                n=1;//标记小数位数
                ched=ch;//保存ch的历史值
                ch=getchar();
                if(ch=='\n') return ERROR;//检错
            }
            else if(ch=='.'&&ch_state==NEGATIVE)
            {
                ch_state=NEGATIVE_DECIMAL;//如果是负小数则标记
                n=1;//标记小数位数
                ched=ch;//保存ch的历史值
                ch=getchar();
                if(ch=='\n') return ERROR;//检错
            }
            else if(ch=='.'&&ch_state==CHARACTER)
                return ERROR;//检错
            Char_to_Number(EXPT,ch);//将字符转换为对应状态的数字
            ched=ch;//保存ch的历史值
            ch=getchar();//获取下一个字符
            if(ch=='\n') return ERROR;//检错
            if(ch_state!=NEGATIVE&&ch_state!=NEGATIVE_DECIMAL&&ch_state!=DECIMAL)//未标记，则标记ch为数字
                ch_state=NUMBER;
        }//if
        else
        {
            if(!Error_detection(ch,ched)) return ERROR;
            if(ch_state==NEGATIVE) ch_state=CHARACTER;
            switch(Precede(GetTop_optr(OPTR),ch))//比较优先级
            {
                case '<':
                    if(GetTop_optr(OPTR)=='('&&ch=='-')//检测到括号与负号相邻
                    {
                        ch_state=NEGATIVE;//标记为负数
                        ched=ch;//保存ch的历史值
                        ch=getchar();//获取下一个字符
                        break;//进行下一次循环
                    }
                    Push_optr(OPTR,ch);//压入符号栈，读取下一个字符
                    ched=ch;//保存ch的历史值
                    ch=getchar();
                    if(ch=='\n') return ERROR;//检错
                    break;
                case '>':
                    Pop_optr(OPTR,theta);//弹出栈顶运算符
                    Pop_expt(EXPT,b);//弹出两个运算数
                    Pop_expt(EXPT,a);
                    CreateExpTree_optr(R,a,b,theta);//以运算符为根，两运算数为叶创建二叉树
                    Push_expt(EXPT,R);//根节点入栈
                    break;
                case '='://栈顶符号为“（”，ch是“）”
                    ched=ch;//保存ch的历史值
                    Pop_optr(OPTR,ch);//弹出“（”，读入下一字符
                    ch=getchar();
                    if(ch=='\n') return ERROR;//检错
                    break;
                default: return ERROR;
            }//switch
            if(ch_state!=NEGATIVE)
                ch_state=CHARACTER;//标记ch为字符
        }//else
    }//while
    T=EXPT->data;
    return OK;
}

double Operate(double a,char theta,double b)
{//运算函数
    double c;
    switch(theta)
    {
        case '+': c=a+b;break;
        case '-': c=a-b;break;
        case '*': c=a*b;break;
        case '/': c=a/b;break;
    }
    return c;
}

double EvaluateExpTree(ExpTree T)
{//遍历表达式树进行求值
    double lvalue=0,rvalue=0;//初始化左右子树的值
    if(T->lchild==NULL&&T->rchild==NULL)//节点为操作数则返回节点值
        return T->data.opnd;
    else//节点为运算符
    {
        lvalue=EvaluateExpTree(T->lchild);//递归计算左子树的值
        rvalue=EvaluateExpTree(T->rchild);//递归计算右子树的值
        return Operate(lvalue,T->data.optr,rvalue);//运算
    }
}

void PostOrderTraverse(ExpTree T)
{//后序遍历输出逆波兰式
    if(T!=NULL)
    {
        PostOrderTraverse(T->lchild);//后序遍历左子树
        PostOrderTraverse(T->rchild);//后序遍历右子树
        if(In(T->data.optr))//运算符节点
            printf("%c ",T->data.optr);
        else//数字节点
            printf("%.2lf ",T->data.opnd);
    }
}

int main()
{
    double a;
    ExpTree T;
    char opt;
    printf("可运算多位整数、浮点数、负数和负小数，并输出其逆波兰式\n");
    printf("（请使用英文输入法，若输入负数请加括号，如：(-1)）\n\n");
    while(1)
    {
        printf("请输入以 “#” 开头结尾的正确表达式：\n");
        while(!InitExpTree(T))//创建表达式树树，且检错
            printf("表达式错误，请重新输入：\n");
        a=EvaluateExpTree(T);//运算
        printf("\n表达式结果为：%.2lf\n",a);
        printf("表达式的逆波兰式为：");
        PostOrderTraverse(T);//输出逆波兰式
        printf("\n");
        printf("\n按“q”以退出程序，或按任意键继续\n");
        fflush(stdin);//清空缓冲区
        opt=getchar();
        if(opt=='q'||opt=='Q') break;
    }
    system("pause");
    return 0;
}