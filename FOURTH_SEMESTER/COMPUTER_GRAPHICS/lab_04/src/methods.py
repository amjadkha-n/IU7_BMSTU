from math import floor, fabs, cos, sin, radians, pi, sqrt
from pixel import draw_pixels


def bresenham_circle(xc, yc, r, color, canvas, draw):
    """
    Draw a circle using Bresenham's algorithm.

    Args:
        xc (int): X-coordinate of the center of the circle.
        yc (int): Y-coordinate of the center of the circle.
        r (int): Radius of the circle.
        color (str): Color of the circle.
        canvas (list): 2D array representing the canvas to draw on.
        draw (bool): Flag indicating whether to draw the circle.

    Returns:
        None
    """

    # Initialize starting point
    x = 0
    y = r

    # Draw the first pixel if draw flag is set
    if draw:
        draw_pixels(canvas, [x + xc, y + yc, color], xc, yc, circle=True)

    # Initial value of the decision parameter
    delta = 2 * (1 - r)

    # Iterate until the x-coordinate crosses y-coordinate
    while x < y:
        # Check the decision parameter
        if delta <= 0:
            # Determine the decision parameter for East pixel
            d = 2 * (delta + y) - 1
            # Move to the East pixel
            x += 1

            # Check if the circle is below the line
            if d >= 0:
                # Determine the decision parameter for South-East pixel
                y -= 1
                # Update the decision parameter
                delta += 2 * (x - y + 1)
            else:
                # Update the decision parameter for East pixel
                delta += x + x + 1
        else:
            # Determine the decision parameter for South pixel
            d = 2 * (delta - x) - 1
            # Move to the South pixel
            y -= 1

            # Check if the circle is below the line
            if d < 0:
                # Move to the South-East pixel
                x += 1
                # Update the decision parameter
                delta += 2 * (x - y + 1)
            else:
                # Update the decision parameter for South pixel
                delta += 1 - y - y

        # Draw the pixel if draw flag is set
        if draw:
            draw_pixels(canvas, [x + xc, y + yc, color], xc, yc, circle=True)

def bresenham_ellipse(xc, yc, ra, rb, color, canvas, draw):
    """
    Draw an ellipse using Bresenham's algorithm.

    Args:
        xc (int): X-coordinate of the center of the ellipse.
        yc (int): Y-coordinate of the center of the ellipse.
        ra (int): Horizontal radius of the ellipse.
        rb (int): Vertical radius of the ellipse.
        color (str): Color of the ellipse.
        canvas (list): 2D array representing the canvas to draw on.
        draw (bool): Flag indicating whether to draw the ellipse.

    Returns:
        None
    """

    # Initialize starting point
    x = 0
    y = rb

    # Draw the first pixel if draw flag is set
    if draw:
        draw_pixels(canvas, [x + xc, y + yc, color], xc, yc, circle=False)

    # Square of horizontal and vertical radii
    sqr_ra = ra * ra
    sqr_rb = rb * rb
    # Initial value of the decision parameter
    delta = sqr_rb - sqr_ra * (rb + rb + 1)

    # Iterate until y-coordinate becomes zero
    while y >= 0:
        # Check the decision parameter
        if delta <= 0:
            # Determine the decision parameter for East pixel
            d = 2 * delta + sqr_ra * (y + y + 2)
            # Move to the East pixel
            x += 1
            # Update the decision parameter
            delta += sqr_rb * (x + x + 1)

            # Check if the ellipse is above the line
            if d >= 0:
                # Move to the South pixel
                y -= 1
                # Update the decision parameter
                delta += sqr_ra * (-y - y + 1)
        else:
            # Determine the decision parameter for South pixel
            d = 2 * delta + sqr_rb * (-x - x + 2)
            # Move to the South pixel
            y -= 1
            # Update the decision parameter
            delta += sqr_ra * (-y - y + 1)

            # Check if the ellipse is above the line
            if d < 0:
                # Move to the East pixel
                x += 1
                # Update the decision parameter
                delta += sqr_rb * (x + x + 1)

        # Draw the pixel if draw flag is set
        if draw:
            draw_pixels(canvas, [x + xc, y + yc, color], xc, yc, circle=False)
def canonical_circle(xc, yc, r, color, canvas, draw):
    """
    Draw a circle using canonical equation.

    Args:
        xc (int): X-coordinate of the center of the circle.
        yc (int): Y-coordinate of the center of the circle.
        r (int): Radius of the circle.
        color (str): Color of the circle.
        canvas (list): 2D array representing the canvas to draw on.
        draw (bool): Flag indicating whether to draw the circle.

    Returns:
        None
    """

    # Square of the radius
    sqr_r = r ** 2

    # Calculate the boundary for the loop
    border = round(xc + r / sqrt(2))

    # Iterate over the x-coordinates
    for x in range(xc, border + 1):
        # Calculate the corresponding y-coordinate using the canonical equation
        y = yc + sqrt(sqr_r - (x - xc) ** 2)

        # Draw the pixel if draw flag is set
        if draw:
            draw_pixels(canvas, [x, y, color], xc, yc, circle=True)

"""
In Python, a canonical ellipse refers to an ellipse that is centered at the origin (0,0) with its major and minor axes 
aligned with the x and y axes. This means that the equation of a canonical ellipse is of the form x^2/a^2 + y^2/b^2 = 1,
 where a is the length of the semi-major axis and b is the length of the semi-minor axis.
"""
def canonical_ellipse(xc, yc, ra, rb, color, canvas, draw):
    """
    Draw an ellipse using canonical equation.

    Args:
        xc (int): X-coordinate of the center of the ellipse.
        yc (int): Y-coordinate of the center of the ellipse.
        ra (int): Major axis radius of the ellipse.
        rb (int): Minor axis radius of the ellipse.
        color (str): Color of the ellipse.
        canvas (list): 2D array representing the canvas to draw on.
        draw (bool): Flag indicating whether to draw the ellipse.

    Returns:
        None
    """

    # Square of the major and minor axis radii
    sqr_ra = ra * ra
    sqr_rb = rb * rb

    # Calculate the boundary for the loop in x-direction
    border_x = round(xc + ra / sqrt(1 + sqr_rb / sqr_ra))
    # Calculate the boundary for the loop in y-direction
    border_y = round(yc + rb / sqrt(1 + sqr_ra / sqr_rb))

    # Iterate over the x-coordinates
    for x in range(xc, border_x + 1):
        # Calculate the corresponding y-coordinate using the canonical equation for the upper half
        y = yc + sqrt(sqr_ra * sqr_rb - (x - xc) ** 2 * sqr_rb) / ra

        # Draw the pixel if draw flag is set
        if draw:
            draw_pixels(canvas, [x, y, color], xc, yc, circle=False)

    # Iterate over the y-coordinates in reverse order
    for y in range(border_y, yc - 1, -1):
        # Calculate the corresponding x-coordinate using the canonical equation for the lower half
        x = xc + sqrt(sqr_ra * sqr_rb - (y - yc) ** 2 * sqr_ra) / rb

        # Draw the pixel if draw flag is set
        if draw:
            draw_pixels(canvas, [x, y, color], xc, yc, circle=False)

def midpoint_circle(xc, yc, r, color, canvas, draw):
    """
    Draw a circle using midpoint algorithm.

    Args:
        xc (int): X-coordinate of the center of the circle.
        yc (int): Y-coordinate of the center of the circle.
        r (int): Radius of the circle.
        color (str): Color of the circle.
        canvas (list): 2D array representing the canvas to draw on.
        draw (bool): Flag indicating whether to draw the circle.

    Returns:
        None
    """

    # Initialize starting point
    x = r
    y = 0

    # Draw the first pixel if draw flag is set
    if draw:
        draw_pixels(canvas, [x + xc, y + yc, color], xc, yc, circle=True)

    # Initialize the decision parameter
    delta = 1 - r

    # Iteratively plot the circle points
    while y < x:
        y += 1

        # Update decision parameter
        if delta >= 0:
            x -= 1
            delta -= x + x

        delta += y + y + 1

        # Draw the pixel if draw flag is set
        if draw:
            draw_pixels(canvas, [x + xc, y + yc, color], xc, yc, circle=True)


def midpoint_ellipse(xc, yc, ra, rb, color, canvas, draw):
    """
    Draw an ellipse using midpoint algorithm.

    Args:
        xc (int): X-coordinate of the center of the ellipse.
        yc (int): Y-coordinate of the center of the ellipse.
        ra (int): Radius along the x-axis of the ellipse.
        rb (int): Radius along the y-axis of the ellipse.
        color (str): Color of the ellipse.
        canvas (list): 2D array representing the canvas to draw on.
        draw (bool): Flag indicating whether to draw the ellipse.

    Returns:
        None
    """

    # Calculate squared radii
    sqr_ra = ra * ra
    sqr_rb = rb * rb

    # Calculate border based on ra and rb
    border = round(ra / sqrt(1 + sqr_rb / sqr_ra))

    # Initialize starting point for the first quadrant
    x = 0
    y = rb

    # Draw the first pixel if draw flag is set
    if draw:
        draw_pixels(canvas, [x + xc, y + yc, color], xc, yc, circle=False)

    # Initialize decision parameter for the first quadrant
    delta = sqr_rb - round(sqr_ra * (rb - 1 / 4))

    # Iterate over the first quadrant
    while x < border:
        if delta > 0:
            y -= 1
            delta -= sqr_ra * y * 2

        x += 1
        delta += sqr_rb * (x + x + 1)

        # Draw the pixel if draw flag is set
        if draw:
            draw_pixels(canvas, [x + xc, y + yc, color], xc, yc, circle=False)

    # Calculate border for the second quadrant
    border = round(rb / sqrt(1 + sqr_ra / sqr_rb))

    # Initialize starting point for the second quadrant
    x = ra
    y = 0

    # Draw the first pixel if draw flag is set
    if draw:
        draw_pixels(canvas, [x + xc, y + yc, color], xc, yc, circle=False)

    # Initialize decision parameter for the second quadrant
    delta = sqr_ra - round(sqr_rb * (x - 1 / 4))

    # Iterate over the second quadrant
    while y < border:
        if delta > 0:
            x -= 1
            delta -= 2 * sqr_rb * x

        y += 1
        delta += sqr_ra * (y + y + 1)

        # Draw the pixel if draw flag is set
        if draw:
            draw_pixels(canvas, [x + xc, y + yc, color], xc, yc, circle=False)

def parameter_circle(xc, yc, r, color, canvas, draw):
    """
    Draw a circle using parameterization method.

    Args:
        xc (int): X-coordinate of the center of the circle.
        yc (int): Y-coordinate of the center of the circle.
        r (int): Radius of the circle.
        color (str): Color of the circle.
        canvas (list): 2D array representing the canvas to draw on.
        draw (bool): Flag indicating whether to draw the circle.

    Returns:
        None
    """

    # Calculate step size for parameterization
    step = 1 / r

    # Initialize parameter
    i = 0

    # Iterate over parameter values
    while i <= pi / 4 + step:
        # Calculate coordinates using parameterization
        x = xc + round(r * cos(i))
        y = yc + round(r * sin(i))

        # Draw the pixel if draw flag is set
        if draw:
            draw_pixels(canvas, [x, y, color], xc, yc, circle=True)

        # Increment parameter
        i += step
"""
A parameter ellipse is an ellipse that is defined by a set of parameters, such as the center coordinates, major and minor 
axes lengths, and orientation angle. These parameters can be used to represent the ellipse in mathematical equations or in computer graphics.


"""
def parameter_ellipse(xc, yc, ra, rb, color, canvas, draw):
    """
    Draw an ellipse using parameterization method.

    Args:
        xc (int): X-coordinate of the center of the ellipse.
        yc (int): Y-coordinate of the center of the ellipse.
        ra (int): Major axis radius of the ellipse.
        rb (int): Minor axis radius of the ellipse.
        color (str): Color of the ellipse.
        canvas (list): 2D array representing the canvas to draw on.
        draw (bool): Flag indicating whether to draw the ellipse.

    Returns:
        None
    """

    # Determine the step size for parameterization based on the major or minor axis
    if ra > rb:
        step = 1 / ra
    else:
        step = 1 / rb

    # Initialize parameter
    i = 0

    # Iterate over parameter values
    while i <= pi / 2 + step:
        # Calculate coordinates using parameterization
        x = xc + round(ra * cos(i))
        y = yc + round(rb * sin(i))

        # Draw the pixel if draw flag is set
        if draw:
            draw_pixels(canvas, [x, y, color], xc, yc, circle=False)

        # Increment parameter
        i += step
