import numpy as np
import pandas as pd
import matplotlib
matplotlib.use('TkAgg')
import matplotlib.pyplot as plt


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