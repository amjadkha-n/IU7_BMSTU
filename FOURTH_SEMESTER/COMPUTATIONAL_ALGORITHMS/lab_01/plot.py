from matplotlib import pyplot as plt


def showPlot(table, x):
    plt.rcParams["figure.figsize"] = [7.00, 3.50]
    plt.rcParams["figure.autolayout"] = True
    x1 = [row[0] for row in table]
    y1 = [row[1] for row in table]
    x2 = [x, x]
    y2 = [min(y1), max(y1)]
    plt.grid()
    plt.plot(x1, y1, marker=".", markersize=10, markeredgecolor="blue", markerfacecolor="blue")
    plt.plot(x2, y2, marker=".", markersize=10, markeredgecolor="red", markerfacecolor="red")
    plt.show()


def showRoot(table):
    plt.rcParams["figure.figsize"] = [7.00, 3.50]
    plt.rcParams["figure.autolayout"] = True
    x = [row[1] for row in table]
    y = [row[0] for row in table]
    zero_x = [min(x), max(x)]
    zero_y = [0, 0]
    plt.grid()
    plt.plot(x, y, marker=".", markersize=10, markeredgecolor="blue", markerfacecolor="blue")
    plt.plot(zero_x, zero_y, marker=".", markersize=10, markeredgecolor="red", markerfacecolor="red")
    plt.show()


def showIntersection(t1, t2):
    plt.rcParams["figure.figsize"] = [7.00, 3.50]
    plt.rcParams["figure.autolayout"] = True
    x1 = [row[1] for row in t1]
    y1 = [row[0] for row in t1]
    x2 = [row[0] for row in t2]
    y2 = [row[1] for row in t2]
    plt.grid()
    plt.plot(x1, y1, marker=".", markersize=10, markeredgecolor="red", markerfacecolor="red")
    plt.plot(x2, y2, marker=".", markersize=10, markeredgecolor="blue", markerfacecolor="blue")
    plt.show()
