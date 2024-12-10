import matplotlib.pyplot as plt
import numpy as np

def f(x, y, b):
    return (x ** 2 + b * (y ** 2)) / 2

def step(x, y, b):
    return (x ** 2 + 2 * (b ** 2) * (y ** 2)) / (x ** 2 + 2 * (b ** 3) * (y ** 2))

def next_iteration(x, y, s, b):
    return [(1 - s) * x, (1 - b * s) * y]

# For b = 1, after the first iteration, we get that s = 1, x = 0 and y = 0, so we reached the local minimum of the function. If we try to compute the next value for the step, we get a division by zero, so we can't continue the gradient descent.

bs = [1/2, 1/5, 1/10]

for b in bs:
  print ("b =", b)
  iterations = 10
  x = np.zeros(iterations + 2)
  y = np.zeros(iterations + 2)

  # initial value
  x[0] = 1
  y[0] = 1

  # gradient descent
  k = 0
  s = step(x[k], y[k], b)
  [x[k + 1], y[k + 1]] = next_iteration(x[k], y[k], s, b)

  while k < iterations and not(x[k + 1] == 0 and y[k + 1] == 0):
      print(k, x[k], y[k], f(x[k], y[k], b))
      k += 1
      s = step(x[k], y[k], b)
      [x[k + 1], y[k + 1]] = next_iteration(x[k], y[k], s, b)

  xlist = np.linspace(-2.0, 2.0, 100)
  ylist = np.linspace(-2.0, 2.0, 100)
  X, Y = np.meshgrid(xlist, ylist)
  Z = f(X, Y, b)

  # define the contour levels
  nlevels = 7
  levels = np.zeros(nlevels + 2)
  if k < nlevels:
    nlevels = k
  for k in range(nlevels):
      levels[k] = f(x[k], y[k], b)
  levels[nlevels], levels[nlevels + 1] = [0.1, 0.15]
  levels = np.sort(levels)

  # plot the contour lines
  contours = plt.contour(X, Y, Z, levels, colors = 'black')
  plt.clabel(contours, inline = True, fontsize = 8)

  # plot the gradient descent iterations
  plt.plot(x[:iterations], y[:iterations], 'r--o')
  
  title = "b = " + str(b)
  plt.title(title)

  plt.show()
