import sys
import csv
from funcs import Matrix, \
    getHermiteInterpolation, \
    getNewtonIntepolation, \
    swapColumns, \
    prepareForHermite
from plot import showIntersection, showRoot, showPlot


# Takes the first arg with filename.csv
def checkArgs() -> str:
    args = sys.argv
    if len(args) < 2:
        return None
    return args[1]


# Gets user input value of X
def getPoint() -> float:
    x = input("Enter x to find the value of the function: ")
    try:
        x = float(x)
    except:
        return None
    return x


# Gets polinom extent from user
def getExtent() -> int:
    a = input("Enter the degree of the polynomial: ")
    try:
        a = int(a)
    except:
        return None
    return a


# Loads data table from csv
def loadTable(file: str) -> Matrix:
    with open(file, 'r') as table:
        reader = csv.reader(table, delimiter=',')
        reader = list(reader)[1:]
        data = [list(map(float, row)) for row in reader]
    return data


def doTask1(table: Matrix):
    pointToCalculate = getPoint()
    if pointToCalculate is None:
        print("Invalid value!")
        return
    calculationExtent = getExtent()
    if calculationExtent is None:
        print("Invalid value!")
        return
    print("The result of Newton's interpolation:", round(getNewtonIntepolation(table, pointToCalculate, calculationExtent), 5))
    print("Hermite interpolation result: ", round(getHermiteInterpolation(table, pointToCalculate, calculationExtent), 5))
    tableLength = 14 * calculationExtent + 1
    print(" " * 7 + "-" * (tableLength) + "\n" + " " * 7, end="")
    for i in range(int(calculationExtent)):
        print("|" + " " * 6 + f"{i + 1}" + " " * 6, end="")
    print("|")
    print(" " * 7 + "-" * (tableLength) + "\nNewton |", end="")
    for i in range(int(calculationExtent)):
        print(f" {getNewtonIntepolation(table, pointToCalculate, i + 1): 10g} ", end=" |")
    print("\n" + " " * 7 + "-" * (tableLength) + "\n" + "Hermite  |", end="")
    for i in range(int(calculationExtent)):
        print(f" {getHermiteInterpolation(table, pointToCalculate, i + 1): 10g} ", end=" |")
    print("\n" + " " * 7 + "-" * (tableLength))
    showPlot(table, pointToCalculate)


def doTask2(table):
    calculationExtent = getExtent()
    if calculationExtent is None:
        print("Invalid value!")
        return
    print("The Newton root:", getNewtonIntepolation(swapColumns(table.copy()), 0.0, min(2, calculationExtent)))
    print("The Hermite root:", getHermiteInterpolation(prepareForHermite(table.copy()), 0.0, min(2, calculationExtent)))


def doTask3(t1: Matrix, t2: Matrix):
    foundTable = []
    for i in range(len(t1)):
        foundTable.append([t1[i][1], getNewtonIntepolation(t2, t1[i][1], 5)])
    diffTable = []
    for i in range(len(foundTable)):
        diffTable.append([foundTable[i][0], round(foundTable[i][1] - t1[i][0], 5)])
    for i in range(len(diffTable)):
        diffTable[i] = [diffTable[i][1], diffTable[i][0]]
    diffTable.sort(key=lambda x: x[0])
    result = getNewtonIntepolation(diffTable, 0.0, 3)
    print("Root:", result)


def main():
    tableFile = checkArgs()
    if not tableFile:
        return
    table = loadTable(tableFile)

    print("\n=========\nTask 1\n=========\n")
    doTask1(table.copy())

    print("\n=========\nTask 2\n=========\n")
    doTask2(table.copy())
    showRoot(table)

    table1 = loadTable('table1.csv')
    table2 = loadTable('table2.csv')

    print("\n=========\nTask 3\n=========\n")
    doTask3(table1, table2)
    showIntersection(table1, table2)


if __name__ == '__main__':
    main()
