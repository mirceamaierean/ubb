import matplotlib.pyplot as plt
import numpy as np

def plot_value(p):
  x = np.random.random_sample((10000))
  final_x = []

  for j in range(2):
    for i in x:
      final_x.append(i)

  for j in range(2):
    for i in x:
      final_x.append(-i)

  y = []
  final_y = []

  for i in x:
    y.append(np.power(1 - np.power(i, p), 1.0000 / p))

  for j in range(2):
    for i in y:
      final_y.append(i)

    for i in y:
      final_y.append(-i)
  
  y = np.random.random_sample((100000))
  x = []

  for i in y:
    x.append(np.power(1 - np.power(i, p), 1.0000 / p))
   
  for j in range(2):
    for i in x:
      final_x.append(i)

  for j in range(2):
    for i in x:
      final_x.append(-i)

  for j in range(2):
    for i in y:
      final_y.append(i)

    for i in y:
      final_y.append(-i)

  plt.title("Unit ball when p = " + str(p))
  plt.plot(final_x, final_y, "go", markersize = 0.5)
  plt.show()

plot_value(1)
plot_value(1.25)
plot_value(1.5)
plot_value(2)
plot_value(3)
plot_value(8)
plot_value(10000)