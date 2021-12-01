import matplotlib.pyplot as plt

with open("./script/gray.txt") as f:
    data1 = f.read()
data1 = [int(i) for i in data1.strip().split(" ")]

with open("./script/subsample.txt") as f:
    data2 = f.read()
data2 = [int(i) for i in data2.strip().split(" ")]

plt.plot(data1)
plt.title("Gray-Level Histogram")
plt.savefig('./script/Gray-Level_Histogram.png')
plt.show()

plt.plot(data2)
plt.title("Downsample_merge_Histogram")
plt.savefig('./script/Downsample_merge_Histogram.png')
plt.show()
