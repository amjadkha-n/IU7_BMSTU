from math import factorial

Matrix = list[list[float]]

# Returns the index of the row in the 'table' list with the closest x value to 'point'
def getClosestRow(table, point):
    prevRow = 0  # Initialize the variable to store the index of the closest row
    for i in range(1, len(table)):  # Iterate through rows starting from the second row
        if table[i][0] > point:  # Check if the current row's x value is greater than the target point
            return prevRow  # If true, return the index of the previous (closest) row
        prevRow += 1  # If not, update the index for the next iteration
    return prevRow  # If the loop completes, return the index of the last (closest) row


# Returns the range of rows to consider based on the given 'row', 'length', and 'extent'
def getRowsRange(row, length, extent) -> tuple[int, int]:
    upside = int(extent / 2) - 1  # Calculate the upper limit for the range
    downside = extent - upside  # Calculate the lower limit for the range

    if row - upside < 0:  # Adjust the range if it extends beyond the beginning of the table
        downside += upside - row
    elif row + downside > length:  # Adjust the range if it extends beyond the end of the table
        upside += (row + downside) - length

    return upside, downside  # Return the calculated upper and lower limits as a tuple


# Returns diffs for Newton's polinom
# Returns the coefficients for Newton's polynomial interpolation based on the given 'table'
def getNewtonCoeffs(table: list[list[float]]) -> list[float]:
    tableLength = len(table)  # Get the total number of rows in the table

    # Calculate the finite differences and append them to the table
    for i in range(tableLength - 1):
        for j in range(tableLength - i - 1):
            table[j].append(table[j + 1][i + 1] - table[j][i + 1])

    diffs = table[0][1:]  # Extract the first differences (coefficients) from the first row

    # Calculate the divided differences and update the coefficients
    for i in range(1, len(diffs)):
        steps = 1  # Initialize the product of step sizes
        for j in range(i):
            steps *= abs(table[j + 1][0] - table[j][0])  # Calculate the product of step sizes
        diffs[i] *= 1 / (factorial(i) * steps)  # Update the coefficient with divided differences

    return diffs  # Return the calculated coefficients for Newton's polynomial


# Swaps the columns of the given 'table' (assumed to be a Matrix)
def swapColumns(table: Matrix):
    swappedTable = table  # Initialize a new reference to the same table (potentially unintended behavior)

    # Iterate through each row in the table
    for i in range(len(table)):
        swappedTable[i] = swappedTable[i][:2]  # Keep only the first two columns of each row
        swappedTable[i] = swappedTable[i][::-1]  # Reverse the order of the remaining columns

    swappedTable.sort(key=lambda x: x[0])  # Sort the table based on the values in the first column
    return swappedTable  # Return the modified table with swapped columns


# Prepares the given 'table' for Hermite interpolation
def prepareForHermite(table: list[list[float]]):
    for i in range(len(table)):
        if len(table[i]) > 2:  # Check if there are enough elements in the row
            table[i][3] = -table[i][3] / table[i][2]**3  # Adjust the third column
            table[i][2] = 1 / table[i][2]  # Invert the values in the second column
            table[i][0], table[i][1] = table[i][1], table[i][0]  # Swap the values in the first two columns

    table.sort(key=lambda x: x[0])  # Sort the table based on the values in the first column
    # Uncomment the following lines to print the prepared table
    # print("PREPARED:")
    # for row in table:
    #     print(row)
    return table  # Return the modified table prepared for Hermite interpolation



# Returns the coefficients for Hermite interpolation based on the given 'preparedData' and 'n'
def getHermiteCoeffs(preparedData: list[list[float]], n: int) -> list[float]:
    n = int(n)
    result = [preparedData[_][1] for _ in range(n)]
    step = 1

    while step < n:
        last_result = result[step-1]
        for i in range(step, n):
            pre_last_result = result[i]
            if i - step >= 0 and len(preparedData[i]) > step + 1:
                result[i] = preparedData[i][step + 1] / factorial(step)
            elif i - step >= 0 and preparedData[i][0] != preparedData[i - step][0]:
                result[i] = ((result[i] - last_result) /
                             (preparedData[i][0] - preparedData[i - step][0]))
            last_result = pre_last_result

        step += 1

    return result


# Calculates the function value at a given point using Newton's polynomial interpolation
def getNewtonIntepolation(table: Matrix, x: float, extent: int) -> float:
    table = [row[0:2] for row in table]  # Extract the first two columns from each row
    row = getClosestRow(table, x)  # Find the closest row index to the given 'x' value
    upside, downside = getRowsRange(row, len(table), extent)  # Get the row range based on the extent
    table = table[int(max(0, row - upside)) : int(min(len(table), row + downside))]  # Extract the relevant rows
    coeffs = getNewtonCoeffs(table)  # Calculate the coefficients for Newton's polynomial
    y = coeffs[0]  # Initialize the result with the constant term

    for i in range(1, len(coeffs)):
        multiplication = 1  # Initialize the product of (x - x_i)
        for j in range(i):
            multiplication *= (x - table[j][0])  # Calculate the product for the current degree
        y += coeffs[i] * multiplication  # Update the result with the current term

    return y  # Return the interpolated value using Newton's polynomial


def getHermiteInterpolation(table: Matrix, x: float, extent: int) -> float:
    row = getClosestRow(table, x)
    upside, downside = getRowsRange(row, len(table), extent)
    table = table[int(max(0, row - upside)) : int(min(len(table), row + downside))]
    newTable = []
    for row in table:
        for _ in range(3):
            newTable.append(row)
    coeffs = getHermiteCoeffs(newTable, extent * 3)
    y = coeffs[0]
    multiplication = 1
    for i in range(1, len(newTable)):
        multiplication *= (x - newTable[i - 1][0])
        y += coeffs[i] * multiplication
    return y
