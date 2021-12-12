import matplotlib.pyplot as plt
import numpy as np

with open("./script/noise.txt") as f:
    noise = f.read()
noise = [int(i) for i in noise.strip().split(" ")]
x = np.arange(0, 41, step=1)

print(x)

plt.plot(noise, 'o')
plt.title("Uniform Noise")
plt.xticks(np.arange(0, 41, step=5), np.arange(-20, 21, step=5))
plt.yticks(np.arange(0, 7000, step=700))
plt.ylim(0, 7001)
plt.savefig('./script/Uniform Noise.png')
plt.show()
