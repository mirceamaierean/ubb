
import numpy as np
from scipy.interpolate import make_interp_spline
import matplotlib.pyplot as plt
 
# Dataset
sum = 0

x = []
y = []

for i in range(1, 5000):
  term = 1 / i
  
  if i % 2 == 0:
    term = -term
  
  sum += term
  x.append(i)
  y.append(sum)

x = np.array(x)
y = np.array(y)

X_Y_Spline = make_interp_spline(x, y)
 
# Returns evenly spaced numbers
# over a specified interval.
X_ = np.linspace(x.min(), x.max(), 10000)
Y_ = X_Y_Spline(X_)
 
# Plotting the Graph
plt.plot(X_, Y_)
plt.title("Plot Smooth Curve Ilustrating the Value of The Sum, Without Rearranging the Terms, When n Goes Up to 100")
plt.xlabel("n")
plt.ylabel("Σ")
plt.show()