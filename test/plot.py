import matplotlib.pyplot as plt
import numpy as np

with open("test/naive1.txt") as f:
    naive1 = [float(x) for x in f.readlines()]

with open("test/naive2.txt") as f:
    naive2 = [float(x) for x in f.readlines()]

with open("test/memo1.txt") as f:
    memo1 = [float(x) for x in f.readlines()]

with open("test/memo2.txt") as f:
    memo2 = [float(x) for x in f.readlines()]

x_labels = ["Zoom In", "Zoom in", "Zoom In", "Complete Black", "Zoom out", "Zoom out", "Zoom out"]

barWidth = 1/5
fig = plt.subplots(figsize =(12, 8))

br2 = np.arange(len(x_labels))
br1 = [x - barWidth for x in br2]
br3 = [x + barWidth for x in br2]
br4 = [x + barWidth for x in br3]

plt.bar(br1,naive1,width=barWidth,
        edgecolor='black',label='Naive method')
plt.bar(br2,memo1,width=barWidth,
        edgecolor='black',label='Memoisation')
plt.bar(br3,naive2,width=barWidth,
        edgecolor='black',label='Multi-threading')
plt.bar(br4,memo2,width=barWidth,
        edgecolor='black',label='Memoisation and Multi-threading')

plt.title("Comparison of Runtime", fontweight ='bold', fontsize = 20)
plt.xlabel('Steps', fontweight ='bold', fontsize = 15)
plt.ylabel('Time taken(sec)', fontweight ='bold', fontsize = 15)
plt.xticks([r + barWidth/2 for r in range(len(x_labels))],x_labels)
plt.legend()

plt.savefig("images/comparison.png")
plt.close()
