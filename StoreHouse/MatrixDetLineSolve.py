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


N = 5
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

Doolittle分解, L 矩阵为:
1.00000     0.00000     0.00000     0.00000
-1.50000    1.00000     0.00000     0.00000
0.50000     -0.27273    1.00000     0.00000
2.00000     -0.54545    -9.00000    1.00000

U 矩阵为:
2.00000     10.00000    0.00000     -3.00000
0.00000     11.00000    -12.00000   8.50000
0.00000     0.00000     -0.27273    -0.18182
0.00000     0.00000     0.00000     -4.00000


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

