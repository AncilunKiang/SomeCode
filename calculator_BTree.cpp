/*
���ö������Ľṹ���ܽ��ж�λ������С���������͸�С�����������㣬����һ���Ľ�׳��

*/

#include<stdio.h>
#include<stdlib.h>

#define OK 1
#define ERROR 0
typedef int Status;
enum{//�ַ�״̬����
    NUMBER,//����
    CHARACTER,//�ַ�
    DECIMAL,//С��
    NEGATIVE,//����
    NEGATIVE_DECIMAL//��С��
    }ch_state;
int n=1;//���С������λ��

typedef struct TreeNode
{//�������ڵ�
    union
    {
        double opnd;//������
        char optr;//�����
    }data;
    struct TreeNode *lchild,*rchild;//���Һ���ָ��
}TreeNode,*ExpTree;

typedef struct StackNode_optr
{//�������ջ�ڵ�
    char data;//������
    struct StackNode_optr *next;//ָ����
}StackNode_optr,*LinkStack_optr;

typedef struct StackNode_expt
{//������ڵ�ջ�ڵ�
    ExpTree data;//������
    struct StackNode_expt *next;//ָ����
}StackNode_expt,*LinkStack_expt;

Status InitBiTree(ExpTree &T)
{//��ʼ�����ڵ�
    T=new TreeNode;//�����ڵ�
    T->lchild=NULL;T->rchild=NULL;//��ʼ������ָ��
    return OK;
}

Status InitStack_optr(LinkStack_optr &S)
{//����ջ��ʼ��
    S=NULL;
    return OK;
}

Status InitStack_expt(LinkStack_expt &S)
{//���ڵ�ջ��ʼ��
    S=NULL;
    return OK;
}

Status Push_optr(LinkStack_optr &S,char e)
{//����ջ��ջ
    LinkStack_optr p;
    p=new StackNode_optr;//�����½��
    p->data=e;//����������
    p->next=S;//����ջ��
    S=p;//�޸�ջ��ָ��
    return OK;
}

Status Push_expt(LinkStack_expt &S,ExpTree e)
{//���ڵ�ջ��ջ
    LinkStack_expt p;
    p=new StackNode_expt;//�����½��
    p->data=e;//����������
    p->next=S;//����ջ��
    S=p;//�޸�ջ��ָ��
    return OK;
}

Status Pop_optr(LinkStack_optr &S,char &e)
{//����ջ��ջ
    LinkStack_optr p;
    if(S==NULL) return ERROR;//ջ��
    e=S->data;//����ջ��Ԫ��
    p=S;//��ʱ����ջ��Ԫ�ؿռ�
    S=S->next;//�޸�ջ��ָ��
    delete p;//�ͷſռ�
    return OK;
}

Status Pop_expt(LinkStack_expt &S,ExpTree &e)
{//���ڵ�ջ��ջ
    LinkStack_expt p;
    if(S==NULL) return ERROR;//ջ��
    e=S->data;//����ջ��Ԫ��
    p=S;//��ʱ����ջ��Ԫ�ؿռ�
    S=S->next;//�޸�ջ��ָ��
    delete p;//�ͷſռ�
    return OK;
}

char GetTop_optr(LinkStack_optr S)
{//ȡ����ջ��Ԫ��
    if(S!=NULL)//ջ�ǿ�
    return S->data;//����ջ����ֵ
}

bool In(char c)
{//�ж������
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
{//�ж����ȼ�
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
{//������������Ϊ���ڵ�Ķ�����
    InitBiTree(T);//��ʼ���ڵ�
    T->data.opnd=e;//����������
    T->lchild=NULL;//���ӽڵ��ÿ�
    T->rchild=NULL;
    return OK;
}

Status CreateExpTree_optr(ExpTree &T,ExpTree L,ExpTree R,char theta)
{//�����������Ϊ���ڵ㣬������Ϊ���ӽڵ�Ķ�����
    InitBiTree(T);//��ʼ����
    T->data.optr=theta;//���������
    T->lchild=L;//���Ӻ��ӽڵ�
    T->rchild=R;
    return OK;
}

Status Char_to_Number(LinkStack_expt &EXPT,char ch)
{//���ַ�ת��Ϊ���ֲ�ѹ��ջ
    double x;
    ExpTree e;
    switch (ch_state)
    {
        case NUMBER://��λ����
            Pop_expt(EXPT,e);//������λ����
            x=(e->data.opnd)*10+(double)(ch-'0');//�ϲ�����
            e->data.opnd=x;//����������
            Push_expt(EXPT,e);//������ջ
            break;
        case CHARACTER://һλ����
            CreateExpTree_opnd(e,(int)(ch-'0'));//��chΪ������һ�Ŷ�����
            Push_expt(EXPT,e);//���ոմ����ĸ��ڵ���ջ
            break;
        case DECIMAL://������
            Pop_expt(EXPT,e);//������λ����
            x=(double)(ch-'0');//ת��ΪС������������
            for(int i=1;i<=n;i++) x=x/10;
            e->data.opnd=e->data.opnd+x;//����������
            Push_expt(EXPT,e);//������ջ
            n++;//���С��λ��
            break;
        case NEGATIVE://����
            CreateExpTree_opnd(e,(0-(int)(ch-'0')));//��chΪ������һ�Ŷ�����
            Push_expt(EXPT,e);//���ոմ����ĸ��ڵ���ջ
            break;
        case NEGATIVE_DECIMAL://��С��
            Pop_expt(EXPT,e);//������λ����
            x=0-(double)(ch-'0');//ת��ΪС������������
            for(int i=1;i<=n;i++) x=x/10;
            e->data.opnd=e->data.opnd+x;//����������
            Push_expt(EXPT,e);//������ջ
            n++;//���С��λ��
            break;
        default:
            return ERROR;
    }
    return OK;
}

Status Error_detection(char ch,char ched)
{//����������
    if(ched=='#') return OK;
    else if(ch=='(') return OK;
    else if(ched=='('&&(ch=='-'||ch=='(')) return OK;
    else if(ched==')') return OK;
    else if(!In(ched)) return OK;
    else return ERROR;
}

Status InitExpTree(ExpTree &T)
{//���ʽ������
    LinkStack_expt EXPT;//���ڵ�ջ
    LinkStack_optr OPTR;//����ջ
    char ch,theta,ched;
    ExpTree R,a,b;
    InitStack_expt(EXPT);//��ʼ��EXPTջ
    InitStack_optr(OPTR);//��ʼ��OPTRջ
    fflush(stdin);//��ջ�����
    ch=getchar();
    ched=ch;//����ch����ʷֵ
    while(ch!='#')
    {//�����ʽ�Ƿ���#��ͷ
        printf("���ʽδ�� ��#�� ��ͷ�����������룺\n");
        fflush(stdin);//��ջ�����
        ch=getchar();
        ched=ch;//����ch����ʷֵ
    }
    ch_state=CHARACTER;//���chΪ�ַ�
    Push_optr(OPTR,ch);//'#'ѹ�����ջ
    ched=ch;//����ch����ʷֵ
    ch=getchar();
    if(ch=='\n') return ERROR;//���
    while(ch!='#'||GetTop_optr(OPTR)!='#')//���ʽû��ɨ����ϻ���ջ��Ԫ�ز�Ϊ'#'
    {
        if(!In(ch))//ch���������
        {
            if((ch<'0'||ch>'9')&&(ch!='.'))
            return ERROR;//���
            if(ch=='.'&&ch_state==NUMBER) //�����С��������,�ٻ�ȡ��һ���ַ�
            {
                ch_state=DECIMAL;
                n=1;//���С��λ��
                ched=ch;//����ch����ʷֵ
                ch=getchar();
                if(ch=='\n') return ERROR;//���
            }
            else if(ch=='.'&&ch_state==NEGATIVE)
            {
                ch_state=NEGATIVE_DECIMAL;//����Ǹ�С������
                n=1;//���С��λ��
                ched=ch;//����ch����ʷֵ
                ch=getchar();
                if(ch=='\n') return ERROR;//���
            }
            else if(ch=='.'&&ch_state==CHARACTER)
                return ERROR;//���
            Char_to_Number(EXPT,ch);//���ַ�ת��Ϊ��Ӧ״̬������
            ched=ch;//����ch����ʷֵ
            ch=getchar();//��ȡ��һ���ַ�
            if(ch=='\n') return ERROR;//���
            if(ch_state!=NEGATIVE&&ch_state!=NEGATIVE_DECIMAL&&ch_state!=DECIMAL)//δ��ǣ�����chΪ����
                ch_state=NUMBER;
        }//if
        else
        {
            if(!Error_detection(ch,ched)) return ERROR;
            if(ch_state==NEGATIVE) ch_state=CHARACTER;
            switch(Precede(GetTop_optr(OPTR),ch))//�Ƚ����ȼ�
            {
                case '<':
                    if(GetTop_optr(OPTR)=='('&&ch=='-')//��⵽�����븺������
                    {
                        ch_state=NEGATIVE;//���Ϊ����
                        ched=ch;//����ch����ʷֵ
                        ch=getchar();//��ȡ��һ���ַ�
                        break;//������һ��ѭ��
                    }
                    Push_optr(OPTR,ch);//ѹ�����ջ����ȡ��һ���ַ�
                    ched=ch;//����ch����ʷֵ
                    ch=getchar();
                    if(ch=='\n') return ERROR;//���
                    break;
                case '>':
                    Pop_optr(OPTR,theta);//����ջ�������
                    Pop_expt(EXPT,b);//��������������
                    Pop_expt(EXPT,a);
                    CreateExpTree_optr(R,a,b,theta);//�������Ϊ������������ΪҶ����������
                    Push_expt(EXPT,R);//���ڵ���ջ
                    break;
                case '='://ջ������Ϊ��������ch�ǡ�����
                    ched=ch;//����ch����ʷֵ
                    Pop_optr(OPTR,ch);//������������������һ�ַ�
                    ch=getchar();
                    if(ch=='\n') return ERROR;//���
                    break;
                default: return ERROR;
            }//switch
            if(ch_state!=NEGATIVE)
                ch_state=CHARACTER;//���chΪ�ַ�
        }//else
    }//while
    T=EXPT->data;
    return OK;
}

double Operate(double a,char theta,double b)
{//���㺯��
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
{//�������ʽ��������ֵ
    double lvalue=0,rvalue=0;//��ʼ������������ֵ
    if(T->lchild==NULL&&T->rchild==NULL)//�ڵ�Ϊ�������򷵻ؽڵ�ֵ
        return T->data.opnd;
    else//�ڵ�Ϊ�����
    {
        lvalue=EvaluateExpTree(T->lchild);//�ݹ������������ֵ
        rvalue=EvaluateExpTree(T->rchild);//�ݹ������������ֵ
        return Operate(lvalue,T->data.optr,rvalue);//����
    }
}

void PostOrderTraverse(ExpTree T)
{//�����������沨��ʽ
    if(T!=NULL)
    {
        PostOrderTraverse(T->lchild);//�������������
        PostOrderTraverse(T->rchild);//�������������
        if(In(T->data.optr))//������ڵ�
            printf("%c ",T->data.optr);
        else//���ֽڵ�
            printf("%.2lf ",T->data.opnd);
    }
}

int main()
{
    double a;
    ExpTree T;
    char opt;
    printf("�������λ�������������������͸�С������������沨��ʽ\n");
    printf("����ʹ��Ӣ�����뷨�������븺��������ţ��磺(-1)��\n\n");
    while(1)
    {
        printf("�������� ��#�� ��ͷ��β����ȷ���ʽ��\n");
        while(!InitExpTree(T))//�������ʽ�������Ҽ��
            printf("���ʽ�������������룺\n");
        a=EvaluateExpTree(T);//����
        printf("\n���ʽ���Ϊ��%.2lf\n",a);
        printf("���ʽ���沨��ʽΪ��");
        PostOrderTraverse(T);//����沨��ʽ
        printf("\n");
        printf("\n����q�����˳����򣬻����������\n");
        fflush(stdin);//��ջ�����
        opt=getchar();
        if(opt=='q'||opt=='Q') break;
    }
    system("pause");
    return 0;
}