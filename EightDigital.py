#-*-coding:GBK -*-

class node:#�ڵ���
    def __init__(self,a,b,c):
        self.status=a
        self.f=b
        self.d=c

l=node([1,2,3,
8,0,4,
7,6,5],0,0)#Ŀ�Ľڵ�
open=[]#open��
closed=[]#closed��
map=[]#·��

def GetW(a):#��ȡw
    k=0
    for i in range(4):
        if l.status[i]!=a[i] :
            k+=1
    for i in range(5,9):
        if l.status[i]!=a[i] :
            k+=1
    return k

def Move(n,i,j):#�ƶ�
    k=node(n.status.copy(),0,n.d+1)
    a=k.status[i]
    k.status[i]=k.status[j]
    k.status[j]=a
    k.f=GetW(k.status)+k.d
    return k

def GetMove(n):#��ȡ�ӽڵ�
    N=[]#�洢��״̬
    if n.status.index(0)==0:
        N.append(Move(n,0,1))
        N.append(Move(n,0,3))
    elif n.status.index(0)==1:
        N.append(Move(n,0,1))
        N.append(Move(n,1,2))
        N.append(Move(n,1,4))
    elif n.status.index(0)==2:
        N.append(Move(n,2,1))
        N.append(Move(n,2,5))
    elif n.status.index(0)==3:
        N.append(Move(n,0,3))
        N.append(Move(n,3,4))
        N.append(Move(n,3,6))
    elif n.status.index(0)==4:
        N.append(Move(n,1,4))
        N.append(Move(n,3,4))
        N.append(Move(n,4,5))
        N.append(Move(n,4,7))
    elif n.status.index(0)==5:
        N.append(Move(n,2,5))
        N.append(Move(n,4,5))
        N.append(Move(n,8,5))
    elif n.status.index(0)==6:
        N.append(Move(n,3,6))
        N.append(Move(n,7,6))
    elif n.status.index(0)==7:
        N.append(Move(n,4,7))
        N.append(Move(n,6,7))
        N.append(Move(n,8,7))
    else:
        N.append(Move(n,5,8))
        N.append(Move(n,7,8))
    return N

def TakeF(m):#������
    return m.f

s=node([],0,0)#��ʼ�ڵ�
s.status=input('�������ʼ״̬���ո���0���棺').split()
for i in range(9):#ת��Ϊint����
    s.status[i]=int(s.status[i])
s.f=GetW(s.status)
open.append(s)

while open:#��ѭ��
    n=open.pop()
    if n.status==l.status:#�ɹ�
        closed.append(n)
        break
    N=GetMove(n)
    for i in N:
        o=0
        for j in open:
            if i.status==j.status:
                o=1
                continue
        for j in closed:
            if i.status==j.status:
                o=1
                continue
        open.append(i)
    closed.append(n)
    open.sort(key=TakeF,reverse=True)

#��closed����ѡ��·��
map.append(l)
for i in range(len(closed)-2,0,-1):
    N=GetMove(closed[i])
    for j in N:
        if map[0].status==j.status:
            map.insert(0,closed[i])
            break
map.insert(0,s)

#������
for i in map:
    print('�� {} ����'.format(map.index(i)+1))
    print('      {} {} {}'.format(i.status[0],i.status[1],i.status[2]))
    print('      {} {} {}'.format(i.status[3],i.status[4],i.status[5]))
    print('      {} {} {}\n'.format(i.status[6],i.status[7],i.status[8]))
