import matplotlib.pyplot as plt
import numpy as np
X=[0, 0, 3, 1, 1, 0, 1, 1, 0, 1, 4, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 3, 
 3, 1, 1, 1, 2, 0, 1, 0, 2, 1, 1, 0, 2, 0, 2, 1, 1, 0, 2, 1, 2, 0, 2, 
 0, 0, 1, 0, 0, 0, 0, 1, 1, 4, 1, 2, 2, 0, 0, 0, 1, 1, 1, 1, 3, 3, 2, 
 1, 2, 1, 0, 2, 1, 2, 0, 0, 1, 2, 2, 2, 0, 4, 1, 1, 2, 3, 2, 0, 1, 1, 
 0, 0, 0, 2, 1, 0, 2, 0]
plt.hist(X, bins=[0, 1, 2, 3, 4, 5], align='right', density=True)

plt.show()

