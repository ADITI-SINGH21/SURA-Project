import numpy as np
import pandas as pd
import matplotlib
matplotlib.use('TkAgg')
import matplotlib.pyplot as plt

"""S = np.loadtxt('size.txt')

for i in S:
	X = np.loadtxt('result/x'+str(int(i))+'.txt')
	Y = np.loadtxt('result/fracyavg'+str(int(i))+'.txt')
	plt.plot(X,Y, label='size='+str(int(i)))
	plt.legend()
plt.title("Average Fraction v/s Applied Pressure for Different Sizes")
plt.xlabel("Applied pressure")
plt.ylabel("Fraction of open nodes(avg)")
plt.savefig('graph/AvgFraction'+'.png', bbox_inches='tight')
plt.close()

for i in S:
	X = np.loadtxt('result/x'+str(int(i))+'.txt')
	Y = np.loadtxt('result/flowyavg'+str(int(i))+'.txt')
	plt.plot(X,Y, label='size='+str(int(i)))
	plt.legend()
plt.title("Average Flowrate v/s Applied Pressure for Different Sizes")
plt.xlabel("Applied pressure")
plt.ylabel("Flow Rate(avg)")
plt.savefig('graph/AvgFlowrate.png', bbox_inches='tight')
plt.close()
"""
S = np.loadtxt('sizecube.txt')
Y = np.loadtxt('MaxPress.txt')
plt.plot(S,Y)
plt.scatter(S,Y)
plt.title("Pressure at which all nodes open vs Size^3")
plt.xlabel("Size^3")
plt.ylabel("Minimum Pressure required for all nodes with finite resistance to open")
plt.savefig('graph/AllNodesOpenCube.png', bbox_inches='tight')
plt.close()

Y = np.loadtxt('MinPress.txt')
plt.plot(S,Y)
plt.scatter(S,Y)
plt.title("Min Pressure required for percolation vs Size^3")
plt.xlabel("Size^3")
plt.ylabel("Minimum Pressure required for fluid to exit")
plt.savefig('graph/FirstFlowpathOpenCube.png', bbox_inches='tight')
plt.close()

Y = np.loadtxt('MaxFrac.txt')
plt.plot(S,Y)
plt.scatter(S,Y)
plt.title("Max Fraction of Nodes Openned v/s Size^3")
plt.xlabel("Size^3")
plt.ylabel("Max Fraction of Nodes Opened")
plt.savefig('graph/MaxFractionCube.png', bbox_inches='tight')
plt.close()