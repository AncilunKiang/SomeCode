#-*-coding:GBK -*-

def CFS(N,k):#生成过河方案
    opt=[]#(m,c)
    for j in range(1,k+1):
        for i in range(j//2+1):
            opt.append([j-i,i])
    for i in range(1,k+1):
        opt.append([0,i])
    return opt

N=int(input('请输入野人和传教士人数：'))
k=int(input('请输入渡船能乘几人：'))
opt=CFS(N,k)#过河方案(m,c)
status_l=[N,N,1]#左岸初始状态(m,c,b)
open=[]#open表
closed=[]#closed表
map=[]#记录路线
result=[]#记录结果
open.append(status_l)

while open :
    n=open.pop()
    closed.append(n)
    map.append(n)
    if n==[0,0,0] :#达到目的节点
        result.append(map.copy())#存储该结果
        map.clear()
    node=[]#记录全部的下一节点
    if n[2]==1:#船在左岸
        for i in opt:
            a=[n[0]-i[0],n[1]-i[1],0]
            if n[0]>=i[0] and n[1]>=i[1] :
                if (a[0]>=a[1] or a[0]==0) and (N-a[0]>=N-a[1] or N-a[0]==0):
                    if a not in open and a not in closed :
                        node.append(a)#保存合法节点
    else:#船在右岸
        for i in opt:
            a=[n[0]+i[0],n[1]+i[1],1]
            if N-n[0]>=i[0] and N-n[1]>=i[1] :
                if (a[0]>=a[1] or a[0]==0) and (N-a[0]>=N-a[1] or N-a[0]==0):
                    if a not in open and a not in closed :
                        node.append(a)#保存合法节点
    if node :
        open.extend(node.copy())#合法节点加入open表
    else :
        map.clear()#死路

for i in result:
    print('第一个方案：\n')
    for j in i:
        print(j)