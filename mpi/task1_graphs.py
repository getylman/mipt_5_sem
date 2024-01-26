import matplotlib.pyplot as plt

# Define the x values
x = [10**3, 10**6, 10**8]

p1 = [0.093846, 0.093626, 0.662281]

# Define the y values
y1 = [1, 1, 1]
y2 = [p1[0] / 0.085560, p1[1] / 0.087151, p1[2] / 0.395158]
y3 = [p1[0] / 0.085124, p1[1] / 0.087455, p1[2] / 0.307230]
y4 = [p1[0] / 0.085134, p1[1] / 0.103515, p1[2] / 0.269459]
y5 = [p1[0] / 0.102991, p1[1] / 0.113427, p1[2] / 0.301007]
y6 = [p1[0] / 0.097477, p1[1] / 0.107270, p1[2] / 0.266606]
y7 = [p1[0] / 0.101322, p1[1] / 0.111206, p1[2] / 0.275768]
y8 = [p1[0] / 0.105527, p1[1] / 0.117166, p1[2] / 0.286544]


# Create the plot
plt.plot(x, y1, label='p1', marker='o')
plt.plot(x, y2, label='p2', marker='o')
plt.plot(x, y3, label='p3', marker='o')
plt.plot(x, y4, label='p4', marker='o')
plt.plot(x, y5, label='p5', marker='o')
plt.plot(x, y6, label='p6', marker='o')
plt.plot(x, y7, label='p7', marker='o')
plt.plot(x, y8, label='p8', marker='o')
plt.xticks([10**3, 10**6, 10**8])
plt.grid()
# Add labels and title
plt.xlabel('N')
plt.ylabel('S')
plt.title('Acceleration by num of processors and by N')
plt.legend()
# Show the plot
plt.show()

'''
total time A1 is 0.093846
total time A1 is 0.085560
total time A1 is 0.085124
total time A1 is 0.085134
total time A1 is 0.102991
total time A1 is 0.097477
total time A1 is 0.101322
total time A1 is 0.105527
total time A2 is 0.093626
total time A2 is 0.087151
total time A2 is 0.087455
total time A2 is 0.103515
total time A2 is 0.113427
total time A2 is 0.107270
total time A2 is 0.111206
total time A2 is 0.117166
total time A3 is 0.662281
total time A3 is 0.395158
total time A3 is 0.307230
total time A3 is 0.269459
total time A3 is 0.301007
total time A3 is 0.266606
total time A3 is 0.275768
total time A3 is 0.286544
'''
