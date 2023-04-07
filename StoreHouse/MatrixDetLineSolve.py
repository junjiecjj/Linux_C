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
import scipy


np.set_printoptions(suppress=True, threshold=np.inf)
# suppress 设置是否科学记数法显示 （默认值：False）
# threshold numpy在print时会有...省略掉中间部分，如果希望显示处完整数组：
np.set_printoptions(precision=4)   # precision 设置浮点数的精度 （默认值：8）


N = 10
A = np.random.randint(-5, 5, N**2)*1.11
A = A.reshape(N, N)

#A[1,:] = A[0,:] 
print(f"A is \n{A}\n")


np.savetxt("/home/jack/snap/Matrix.txt", A, delimiter = ' ', fmt='%.04f')

 
print(f"Det of A is :\n{np.linalg.det(A)}\n")
print(f"inverse of A is :\n{np.linalg.inv(A)}")



L = np.array([[2, 0, 0, 0 ],
              [-3, 11, 0, 0,],
              [1, -3, -0.272727, 0],
              [4, -6, 2.454545, -4.0]])

U = np.array([[1.00000 ,    5.000  ,   0.0 ,    -1.50000],
              [0,           1.00000 ,    -1.090909 ,    0.772727],
              [0,           0,           1.00000,     0.66666667],
              [0,           0,           0,           1 ]])


result=np.dot(L,U)
print(result)

 

L = np.array([[1,    0,          0,       0 ],
              [-1.5, 1,          0,       0,],
              [0.5,  -0.272727,  1,       0],
              [2,    -0.545454,  -9, 1]])

U = np.array([[2.00000 ,    10.000  ,   0.0 ,       -3.0000],
              [0,           11.00000,   -12.0,      8.5],
              [0,           0,          -0.272727,  -0.181818],
              [0,           0,           0,         -4]])


result=np.dot(L,U)
print(result)





A = np.arange(1, 17).reshape(4, 4)
l, u = scipy.linalg.lu(a=A, permute_l=True, overwrite_a=False, check_finite=True)

print('原矩阵\n', A)
#print('p矩阵\n', p)
print('l矩阵\n', l)
print('u矩阵\n', u)

# scipy.linalg.qr
# scipy.linalg.svd





A = np.array([[5,7,6,5],[7,10,8,7],[6,8,10,9],[5,7,9,10]])

# A = np.array([[1,0,0,0],[0,0,0,4],[0,3,0,0],[0,0,0,0],[2,0,0,0]])
V , P = np.linalg.eigh(A)

print(f"A = \n{A}\n特征值 = \n{V}\n特征向量 = \n{P}\n")



'''-------------------矩阵奇异值分解np.linalg.svd()-------------------'''
import numpy as np

#1. SVD分解
A= [[1,1,3,6,1],[5,1,8,4,2],[7,9,2,1,2]]

A = np.array([[1,0,0,0],[0,0,0,4],[0,3,0,0],[0,0,0,0],[2,0,0,0]])

A=np.array(A)


U,s,VT = np.linalg.svd(A) 
# 为节省空间，svd输出s只有奇异值的向量
print('奇异值：',s)
# 根据奇异值向量s，生成奇异值矩阵
Sigma = np.zeros(np.shape(A))
Sigma[:len(s),:len(s)] = np.diag(s)

print("U：\n",U)
print('Sigma：\n',Sigma)
print('VT：\n',VT)
print('VT.T：\n',VT.T)


#2.SVD重构
B = U.dot(Sigma.dot(VT))
print('重构后的矩阵B：\n', B)

print('原矩阵与重构矩阵是否相同？',np.allclose(A,B))

# 3. SVD矩阵压缩（降维）
for k in range(3,0,-1):  # 3,2,1
    # U的k列，VT的k行
    D = U[:,:k].dot(Sigma[:k,:k].dot(VT[:k,:]))
    print('k=',k,"压缩后的矩阵：\n",np.round(D,1))  # round取整数




A= [[1,1,3,6,1],[5,1,8,4,2],[7,9,2,1,2]]
V , P = np.linalg.eigh(A)
print(f"ATA = \n{A}\nATA特征值 = \n{V}\nATA特征向量 = \n{P}\n")


ATA = A.T@A

V , P = np.linalg.eigh(ATA)

print(f"ATA = \n{ATA}\nATA特征值 = \n{V}\nATA特征向量 = \n{P}\n")


# U1,s1,VT1 = np.linalg.svd(ATA) 
# # 为节省空间，svd输出s只有奇异值的向量
# print('奇异值：',s1)
# # 根据奇异值向量s，生成奇异值矩阵
# Sigma1 = np.zeros(np.shape(ATA))
# Sigma1[:len(s1),:len(s1)] = np.diag(s1)

# print("U1：\n",U1)
# print('Sigma1：\n',Sigma1)
# print('VT1：\n',VT1)

# #2.SVD重构
# B1 = U1.dot(Sigma1.dot(VT1))
# print('重构后的矩阵B：\n', B1)

# print('原矩阵与重构矩阵是否相同？',np.allclose(ATA,B1))


AAT = A@A.T

V1 , P1 = np.linalg.eigh(AAT)

print(f"AAT = \n{AAT}1\nAAT特征值 = \n{V1}\nAAT特征向量 = \n{P1}\n")


# U1,s1,VT1 = np.linalg.svd(ATA) 
# # 为节省空间，svd输出s只有奇异值的向量
# print('奇异值：',s1)
# # 根据奇异值向量s，生成奇异值矩阵
# Sigma1 = np.zeros(np.shape(ATA))
# Sigma1[:len(s1),:len(s1)] = np.diag(s1)

# print("U1：\n",U1)
# print('Sigma1：\n',Sigma1)
# print('VT1：\n',VT1)

# #2.SVD重构
# B1 = U1.dot(Sigma1.dot(VT1))
# print('重构后的矩阵B：\n', B1)

# print('原矩阵与重构矩阵是否相同？',np.allclose(ATA,B1))



















