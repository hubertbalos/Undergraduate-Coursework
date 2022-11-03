import matplotlib.pyplot as plt
import numpy as np
data = np.loadtxt("data.txt", delimiter = ', ')
x = np.array(data[:,0])
F = np.array(data[:,1])
plt.xscale('log')
plt.yscale('log')
plt.title('Random integration')
plt.xlabel('Number of iterations (n)')
plt.ylabel('Absolute proximity to 2.4076')
plt.plot(x, F)
plt.draw()
plt.show()