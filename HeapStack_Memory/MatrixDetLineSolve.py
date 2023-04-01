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

#A[1,:] = A[0,:] 
print(f"A is \n{A}\n")


np.savetxt("/home/jack/snap/Matrix.txt", A, delimiter = ' ', fmt='%.04f')

 
print(f"Det of A is :\n{np.linalg.det(A)}\n")
print(f"inverse of A is :\n{np.linalg.inv(A)}")
