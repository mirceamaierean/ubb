
import numpy as np
from scipy.interpolate import make_interp_spline
import matplotlib.pyplot as plt

# The convex function i have chose is f(x) = 2 x ^ 2 + 2 x
# The derivative of this function if f'(x) = 4 x + 2

# The nonconvex function i have chose is f(x) = -(2 x ^ 2 + 2 x)
# The derivative of this function if f'(x) = -(4 x + 2)

def func_derivative_of_function(sign, x, n):
  return sign * n * (4 * x + 2)

def compute_values_for_graph(n, sign, lgth):
  x = [1]
  y = [10]
  for i in range(2, lgth):
    val = y[-1] - func_derivative_of_function(sign, y[-1], n)
    x.append(i)
    y.append(val)
  
  return x, y



def print_graph(x, y, title):
  x = np.array(x)
  y = np.array(y)

  X_Y_Spline = make_interp_spline(x, y)

  X_ = np.linspace(x.min(), x.max(), 10000)
  Y_ = X_Y_Spline(X_)
  
  plt.plot(X_, Y_)
  plt.title(title)
  plt.xlabel("x")
  plt.ylabel("f(x)")
  plt.show()


def graph_for_convex_function_and_small_n(n, title, sign, lgth):
  x, y = compute_values_for_graph(n, sign, lgth)
  print_graph(x, y, title)

graph_for_convex_function_and_small_n(0.05, "Plot Smooth Curve Ilustrating the Gradient Descent for the convex function, with the learning rate η = 0.05", 1, 200)
graph_for_convex_function_and_small_n(0.1, "Plot Smooth Curve Ilustrating the Gradient Descent for the convex function, with the learning rate η = 0.1", 1, 200)
graph_for_convex_function_and_small_n(1, "Plot Smooth Curve Ilustrating the Gradient Descent for the convex function, with the learning rate η = 1", 1, 200)
graph_for_convex_function_and_small_n(0.001, "Plot Smooth Curve Ilustrating the Gradient Descent for the non-convex function, with the learning rate η = 0.001", -1, 200)
