#-*-coding:GBK -*-

def CFS(N,k):#���ɹ��ӷ���
    opt=[]#(m,c)
    for j in range(1,k+1):
        for i in range(j//2+1):
            opt.append([j-i,i])
    for i in range(1,k+1):
        opt.append([0,i])
    return opt

N=int(input('������Ұ�˺ʹ���ʿ������'))
k=int(input('������ɴ��ܳ˼��ˣ�'))
opt=CFS(N,k)#���ӷ���(m,c)
status_l=[N,N,1]#�󰶳�ʼ״̬(m,c,b)
open=[]#open��
closed=[]#closed��
map=[]#��¼·��
result=[]#��¼���
open.append(status_l)

while open :
    n=open.pop()
    closed.append(n)
    map.append(n)
    if n==[0,0,0] :#�ﵽĿ�Ľڵ�
        result.append(map.copy())#�洢�ý��
        map.clear()
    node=[]#��¼ȫ������һ�ڵ�
    if n[2]==1:#������
        for i in opt:
            a=[n[0]-i[0],n[1]-i[1],0]
            if n[0]>=i[0] and n[1]>=i[1] :
                if (a[0]>=a[1] or a[0]==0) and (N-a[0]>=N-a[1] or N-a[0]==0):
                    if a not in open and a not in closed :
                        node.append(a)#����Ϸ��ڵ�
    else:#�����Ұ�
        for i in opt:
            a=[n[0]+i[0],n[1]+i[1],1]
            if N-n[0]>=i[0] and N-n[1]>=i[1] :
                if (a[0]>=a[1] or a[0]==0) and (N-a[0]>=N-a[1] or N-a[0]==0):
                    if a not in open and a not in closed :
                        node.append(a)#����Ϸ��ڵ�
    if node :
        open.extend(node.copy())#�Ϸ��ڵ����open��
    else :
        map.clear()#��·

for i in result:
    print('��һ��������\n')
    for j in i:
        print(j)