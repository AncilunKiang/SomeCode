#-*-coding:GBK -*-
IndirectDatabaseKey=[]#��ӹ�����
IndirectDatabaseValue=[]#��ӹ����ֵ
DirectDatabaseKey=[]#ֱ�ӹ�����
DirectDatabaseValue=[]#ֱ�ӹ����ֵ
print("          ���������         ")
print("\0������ӹ���⣬����0������")
while(1):
    str=input("�������������Կո������")
    if str== '0': break
    L=str.split()
    IndirectDatabaseKey.append(L)
    str=input("����������")
    IndirectDatabaseValue.append(str)
print("\0����ֱ�ӹ���⣬����0������")
while(1):
    str=input("�������������Կո������")
    if str== '0': break
    L=str.split()
    DirectDatabaseKey.append(L)
    str=input("����������")
    DirectDatabaseValue.append(str)
print("����⹹�����\n")
while(1):#��������
    opt=input("������������Ĳ�����1:��Ӽ�ӹ���⣬2:���ֱ�ӹ���⣬3:��ѯ���0:�˳���")
    if opt=='0' : 
        break
    elif opt=='1' :
        str=input("�������������Կո������")
        L=str.split()
        IndirectDatabaseKey.append(L)
        str=input("����������")
        IndirectDatabaseValue.append(str)
    elif opt=='2' :
        str=input("�������������Կո������")
        L=str.split()
        DirectDatabaseKey.append(L)
        str=input("����������")
        DirectDatabaseValue.append(str)
    elif opt=='3' :
        str=input("������ö������Ҫ�������Կո������")
        CIB=str.split()#�ۺ����ݿ�
        while(1):#�ڼ�ӹ����������
            ms=[]#ƥ��ɹ��ų���
            i=0#�����������
            for x in IndirectDatabaseKey:
                a=1#ƥ��ɹ���־
                if x in ms :#��ƥ��������
                    i+=1
                    continue
                for y in x:#����ƥ��
                    if y not in CIB :
                        i+=1
                        a=0
                        break
                if a==1:#��i������ƥ��ɹ�
                    CIB.append(IndirectDatabaseValue[i])
                    ms.append(x)
                    a=1
                    i+=1
            if a==0 :
                break#���޿�ƥ��
        i=0#�����������
        for x in DirectDatabaseKey:#��ֱ�����ݿ�������
            a=1#ƥ��ɹ���־
            for y in x:#����ƥ��
                if y not in CIB :
                    i+=1
                    a=0
                    break
            if a==1:#��i������ƥ��ɹ�
                print("��������ǣ�")
                print(DirectDatabaseValue[i])
                break
        if a==0:
            print("����ʧ��")
print("����ִ�н���")

