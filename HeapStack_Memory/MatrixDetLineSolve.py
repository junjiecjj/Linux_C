# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""

import os
import networkx as nx
import matplotlib.pyplot as plt
import math
import numpy as np

np.set_printoptions(suppress=True, threshold=np.inf)
# suppress 设置是否科学记数法显示 （默认值：False）
# threshold numpy在print时会有...省略掉中间部分，如果希望显示处完整数组：
np.set_printoptions(precision=4)   # precision 设置浮点数的精度 （默认值：8）


N = 20
A = np.random.randint(-5, 5, N**2)*1.11
A = A.reshape(N, N)
# A[0,:] = 0
print(f"A is \n{A}")
np.savetxt("/home/jack/snap/Matrix.txt", A, delimiter = ' ', fmt='%.04f')

# [[2 5 5]
#  [0 4 6]
#  [5 8 8]]


print(np.linalg.det(A))

# A is 
# [[ -9.99   0.    -1.11  -4.44   5.55]
#  [  0.     6.66 -11.1    1.11  -3.33]
#  [ -7.77  -3.33   2.22   9.99   3.33]
#  [ -1.11   0.    -6.66  -4.44  -2.22]
#  [  7.77  -4.44   3.33   9.99  -3.33]]
# -13165.359365796308


# A is 
# [[ -5.55  -8.88   3.33  -5.55   8.88  -1.11  -7.77  -2.22   7.77   2.22]
#  [  8.88   6.66 -11.1   -3.33   5.55  -7.77  -6.66   2.22  -8.88   1.11]
#  [ -9.99  -9.99  -7.77   7.77  -6.66   4.44  -4.44  -2.22   7.77   5.55]
#  [ -8.88  -3.33   1.11   3.33   6.66  -7.77  -4.44   3.33   4.44  -8.88]
#  [ -2.22  -2.22   5.55  -3.33   9.99  -1.11   4.44   4.44  -8.88  -7.77]
#  [  8.88   1.11  -3.33  -6.66  -3.33   3.33  -9.99  -3.33   2.22   9.99]
#  [ -3.33   9.99  -6.66  -4.44   1.11   2.22  -1.11 -11.1    6.66   0.  ]
#  [  5.55  -2.22  -7.77   0.    -5.55  -5.55  -2.22   9.99 -11.1    5.55]
#  [ -6.66   4.44   1.11   1.11   0.     0.     0.     3.33   0.    -1.11]
#  [  9.99  -4.44   7.77  -5.55  -4.44  -4.44   3.33   7.77  -4.44   2.22]]
# -3901870822.8763394



import numpy as np
def Gauss_elimination(A):
    # 高斯消去法求解
    # 消元,化为上三角
    print(f"A = \n{A}\n\n")
    for k in range(len(A[0])):
        print(f"k = {k}\n")
        for i in range(k+1,len(A)):      
            print(f"  i = {i}\n")
            m=A[i][k]/A[k][k]
            print(f"  m = {m}\n")
            for j in range(k,len(A[0])):
                A[i][j]-=m*A[k][j]
    print(f"  A = \n{A}\n ")

    #回代
    X=[]     #设置空列表X来存储方程组的解x1,x2,...
    X.append(A[len(A)-1][len(A[0])-1]/A[len(A)-1][len(A[0])-2])     #将所得的xn添加置列表X
    for i in range(len(A)-2,-1,-1):     
        s=A[i][len(A[0])-1]   
        for j in range(i+1,len(A)):
                s = s - A[i][j] * X[len(A)-1-j]     
        X.append(s/A[i][i])      
    X.reverse()     
    return X
 
A = np.array([[3,1,-1,4],[4,0,4,8],[12,-3,3,9]])*1.0  
print(Gauss_elimination(A))


import numpy as numpy
def Gauss_Lelimination(A):  
    # 列主元高斯消去法求解
    for k in range(len(A[0])-1):
        # 在整个系数矩阵中选择列主元
        max=A[k][k]
        for i in range(k+1,len(A)):  
            # 选主元
            if (abs(max)<abs(A[i][k])):  
                max=A[i][k]
                x=i  #记录选择交换的行数
        A[[k,i],:]=A[[i,k],:]
    return Gauss_elimination(A)

def Gauss_elimination(A):
    # 消元,化为上三角
    for k in range(len(A[0])):     
        for i in range(k+1,len(A)):    
            m=A[i][k]/A[k][k]
            for j in range(k,len(A[0])):  
                A[i][j]-=m*A[k][j]
    #回代
    X=[]    #设置空列表X来存储方程组的解x1,x2,...
    X.append(A[len(A)-1][len(A[0])-1]/A[len(A)-1][len(A[0])-2])    
    for i in range(len(A)-2,-1,-1):    
        s=A[i][len(A[0])-1]   
        for j in range(i+1,len(A)):
                s = s - A[i][j] * X[len(A)-1-j]  
        X.append(s/A[i][i])    
    X.reverse()   
    return X
A = np.array([[3,1,-1,4],[4,0,4,8],[12,-3,3,9]])  
print(Gauss_Lelimination(A))



import numpy as numpy
def Gauss_Qelimination(A):
    # 全主元高斯消去法求解
    for k in range(len(A[0])-1):
        max=A[k][k]
        for i in range(k,len(A)):
            for j in range(k,len(A[0])-1):
                if (abs(max) < abs(A[i][j])):   #选去绝对值最大者作为主元
                    max=A[i][j]
                    x=i   #记录选择交换的行数
                    y=j   #记录选择交换的列数
        A[[k,x],:]=A[[x,k],:]    #交换第k行和第x行
        A[:,[k,y]]=A[:,[y,k]]    #交换第k列和第y列
        print(f"k = {k}")
        print(f"A = \n{A}")
        for i in range(k+1,len(A)):
            m=A[i][k]/A[k][k]
            for j in range(k,len(A[0])): 
                A[i][j]-=m*A[k][j]
    #回代
    X=[]    #设置空列表X来存储方程组的解x1,x2,...
    X.append(A[len(A)-1][len(A[0])-1]/A[len(A)-1][len(A[0])-2])    
    for i in range(len(A)-2,-1,-1):     
        s=A[i][len(A[0])-1]
        for j in range(i+1,len(A)):
                s = s - A[i][j] * X[len(A)-1-j]  
        X.append(s/A[i][i])    
    X.reverse()  
    return X

A = np.array([[0.007,-0.8,0.7],[-0.1,10,10]]) 
print(Gauss_Qelimination(A))



