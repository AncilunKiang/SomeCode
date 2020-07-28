#-*-coding:GBK -*-

class node:#节点类
    def __init__(self,a,b,c):
        self.status=a
        self.f=b
        self.d=c

l=node([1,2,3,
8,0,4,
7,6,5],0,0)#目的节点
open=[]#open表
closed=[]#closed表
map=[]#路线

def GetW(a):#获取w
    k=0
    for i in range(4):
        if l.status[i]!=a[i] :
            k+=1
    for i in range(5,9):
        if l.status[i]!=a[i] :
            k+=1
    return k

def Move(n,i,j):#移动
    k=node(n.status.copy(),0,n.d+1)
    a=k.status[i]
    k.status[i]=k.status[j]
    k.status[j]=a
    k.f=GetW(k.status)+k.d
    return k

def GetMove(n):#获取子节点
    N=[]#存储子状态
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

def TakeF(m):#排序函数
    return m.f

s=node([],0,0)#初始节点
s.status=input('请输入初始状态，空格用0代替：').split()
for i in range(9):#转换为int类型
    s.status[i]=int(s.status[i])
s.f=GetW(s.status)
open.append(s)

while open:#主循环
    n=open.pop()
    if n.status==l.status:#成功
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

#从closed表中选出路径
map.append(l)
for i in range(len(closed)-2,0,-1):
    N=GetMove(closed[i])
    for j in N:
        if map[0].status==j.status:
            map.insert(0,closed[i])
            break
map.insert(0,s)

#输出结果
for i in map:
    print('第 {} 步：'.format(map.index(i)+1))
    print('      {} {} {}'.format(i.status[0],i.status[1],i.status[2]))
    print('      {} {} {}'.format(i.status[3],i.status[4],i.status[5]))
    print('      {} {} {}\n'.format(i.status[6],i.status[7],i.status[8]))
