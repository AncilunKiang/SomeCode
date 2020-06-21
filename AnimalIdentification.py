#-*-coding:GBK -*-
IndirectDatabaseKey=[]#间接规则库键
IndirectDatabaseValue=[]#间接规则库值
DirectDatabaseKey=[]#直接规则库键
DirectDatabaseValue=[]#直接规则库值
print("          构建规则库         ")
print("\0构建间接规则库，输入0结束：")
while(1):
    str=input("请输入条件，以空格隔开：")
    if str== '0': break
    L=str.split()
    IndirectDatabaseKey.append(L)
    str=input("请输入结果：")
    IndirectDatabaseValue.append(str)
print("\0构建直接规则库，输入0结束：")
while(1):
    str=input("请输入条件，以空格隔开：")
    if str== '0': break
    L=str.split()
    DirectDatabaseKey.append(L)
    str=input("请输入结果：")
    DirectDatabaseValue.append(str)
print("规则库构建完成\n")
while(1):#操作部分
    opt=input("请输入接下来的操作，1:添加间接规则库，2:添加直接规则库，3:查询动物，0:退出：")
    if opt=='0' : 
        break
    elif opt=='1' :
        str=input("请输入条件，以空格隔开：")
        L=str.split()
        IndirectDatabaseKey.append(L)
        str=input("请输入结果：")
        IndirectDatabaseValue.append(str)
    elif opt=='2' :
        str=input("请输入条件，以空格隔开：")
        L=str.split()
        DirectDatabaseKey.append(L)
        str=input("请输入结果：")
        DirectDatabaseValue.append(str)
    elif opt=='3' :
        str=input("请输入该动物的主要特征，以空格隔开：")
        CIB=str.split()#综合数据库
        while(1):#在间接规则库中推理
            ms=[]#匹配成功排除区
            i=0#规则库索引号
            for x in IndirectDatabaseKey:
                a=1#匹配成功标志
                if x in ms :#已匹配则跳过
                    i+=1
                    continue
                for y in x:#逐项匹配
                    if y not in CIB :
                        i+=1
                        a=0
                        break
                if a==1:#第i条规则匹配成功
                    CIB.append(IndirectDatabaseValue[i])
                    ms.append(x)
                    a=1
                    i+=1
            if a==0 :
                break#已无可匹配
        i=0#规则库索引号
        for x in DirectDatabaseKey:#在直接数据库中推理
            a=1#匹配成功标志
            for y in x:#逐项匹配
                if y not in CIB :
                    i+=1
                    a=0
                    break
            if a==1:#第i条规则匹配成功
                print("这个动物是：")
                print(DirectDatabaseValue[i])
                break
        if a==0:
            print("推理失败")
print("程序执行结束")

