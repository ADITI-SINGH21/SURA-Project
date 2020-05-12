import numpy as np
import pandas as pd
import matplotlib
matplotlib.use('TkAgg')
import matplotlib.pyplot as plt
size=40
lines=10

for i in range(lines):
	X = np.loadtxt('result/time'+str(i)+'.txt')
	Y = np.loadtxt('result/sitey'+str(i)+'.txt')
	plt.plot(X,Y,linestyle = '--')

plt.title("No. of nodes = "+str(size)+"*"+str(size)+"*"+str(size)+", No. of lines = "+str(lines))
plt.xlabel("time")
plt.ylabel("sites open")
#X = np.loadtxt('Xavg.txt')
#Y = np.loadtxt('Yavg.txt')
#plt.plot(X,Y, linestyle = '--')
plt.savefig('graph/Fraction'+str(size)+'.png', bbox_inches='tight')
plt.close()

