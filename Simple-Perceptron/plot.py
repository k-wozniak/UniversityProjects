import matplotlib
matplotlib.use('TkAgg')
import matplotlib.pyplot as plt
import numpy as np

plt.style.use('ggplot')
plt.rcParams["figure.figsize"] = [1,1]

fig = plt.figure()
fig.set_figheight(2)
fig.set_figwidth(2)
#fig = plt.xkcd()

plt.scatter(0, 0, s=50, color="red", zorder=3)
plt.scatter(0, 1, s=50, color="green", zorder=3)
plt.scatter(1, 0, s=50, color="green", zorder=3)
plt.scatter(1, 1, s=50, color="red", zorder=3)

# Set the axis limits
plt.xlim(-0.25,1.25)
plt.ylim(-0.25,1.25)

plt.yticks(np.arange(0, 1.5, 0.5))
plt.xticks(np.arange(0, 1.5, 0.5))

# Label the plot
plt.xlabel("Input 1")
plt.ylabel("Input 2")
plt.title("XOR")

plt.axline((0, 1.5), (1.5, 0), color='k')
plt.axline((0, 0.5), (0.5, 0), color='k')

# Turn on grid lines
plt.grid(True, linewidth=1, linestyle=':')

# Autosize (stops the labels getting cut off)
plt.tight_layout()

# Show the plot
plt.show()