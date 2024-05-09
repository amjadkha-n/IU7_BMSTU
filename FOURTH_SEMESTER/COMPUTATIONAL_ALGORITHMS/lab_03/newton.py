def divided_diff(table):
    """
    Calculate the divided differences for a given set of points.

    Args:
        table (list): A list of points in the format [[x0, f(x0), f'(x0)], [x1, f(x1), f'(x1)], ...].

    Returns:
        list: A list containing the divided differences.

    Notes:
        Divided differences are a way to represent the coefficients of the Newton interpolation polynomial.
        This function computes the divided differences table for the given set of points.

    """
    # Creating a temporary table filled with zeros
    temp = [[0] * (len(table)) for i in range(len(table) + 2)]

    # Copying values from the input table to the temporary table
    for i in range(len(table)):
        temp[0][i] = table[i][0]  # Copying the first column from the input table
        temp[1][i] = table[i][2]  # Copying the third column from the input table
        temp[2][i] = table[i][1]  # Copying the second column from the input table

    # Initializing a variable to track the position for differences computation
    x_barrier = 1

    # Looping through the rows of the temporary table to compute divided differences
    for i in range(3, len(temp)):
        # Looping through the columns of the temporary table to compute divided differences
        for j in range(len(temp[0]) - i + 2):
            # Checking if the denominator is zero, if so, assign the value from the third row
            if temp[0][j] - temp[0][j + x_barrier] == 0:
                temp[i][j] = temp[1][j]
            else:
                # Computing divided differences using the Newton's divided difference formula
                temp[i][j] = (temp[i - 1][j] - temp[i - 1][j + 1]) / (temp[0][j] - temp[0][j + x_barrier])
        x_barrier += 1  # Incrementing the barrier

    # Returning the computed divided differences
    return [temp[i][0] for i in range(3, len(temp))]

def select_points_newton(table, x, n):
    """
    Selects points for Newton interpolation around a given point.

    Args:
        table (list): A list of points in the format [[x0, f(x0)], [x1, f(x1)], ...] sorted by x-coordinate.
        x (float): The x-coordinate around which to select points for interpolation.
        n (int): The number of points to select for interpolation.

    Returns:
        list: A list of n + 1 points selected for interpolation, including the point nearest to x.

    Notes:
        This function selects n + 1 points from the given table for Newton interpolation around the point with
        the x-coordinate closest to the specified x value. If there are not enough points available, it returns None.
    """
    new_table = []

    pos = 0
    while pos < len(table) - 1 and table[pos][0] < x:
        pos += 1

    new_table.append(table[pos].copy())

    l_bound = pos - 1
    r_bound = pos + 1

    while len(new_table) < n + 1:
        if l_bound >= 0 and len(new_table) < n + 1:
            new_table.append(table[l_bound].copy())
            l_bound -= 1
        if r_bound < len(table) and len(new_table) < n + 1:
            new_table.append(table[r_bound].copy())
            r_bound += 1

    new_table.sort(key=lambda x: x[0])

    if len(new_table) == n + 1:
        return new_table
    else:
        return None


def approximate_newton(table, x, n):
    """
    Approximates the value of a function at a given point using Newton interpolation.

    Args:
        table (list): A list of points in the format [[x0, f(x0)], [x1, f(x1)], ...] sorted by x-coordinate.
        x (float): The x-coordinate at which to approximate the function value.
        n (int): The degree of the Newton polynomial to use for interpolation.

    Returns:
        float: The interpolated value of the function at the given point.

    Notes:
        This function performs Newton interpolation using the specified degree of the polynomial.
        It selects points around the given x-coordinate and computes the divided differences for these points.
        Then, it evaluates the Newton polynomial at the given x-coordinate to obtain the interpolated function value.
    """
    selected_points = select_points_newton(table, x, n)

    diffs = divided_diff(selected_points)

    res = selected_points[0][1]

    accum = 1
    i = 0
    while i < len(diffs):
        accum *= (x - selected_points[i][0])
        res += accum * diffs[i]
        i += 1

    return res
