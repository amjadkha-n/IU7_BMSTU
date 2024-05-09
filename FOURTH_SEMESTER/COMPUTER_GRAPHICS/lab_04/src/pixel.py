import colorutils as cu

import colorutils as cu

def set_pixel(canvas, x, y, color):
    """
    Set the color of a pixel on the canvas.

    Args:
        canvas: Canvas object to draw on.
        x (int): X-coordinate of the pixel.
        y (int): Y-coordinate of the pixel.
        color (Color): Color of the pixel.

    Returns:
        None
    """
    canvas.create_line(x, y, x + 1, y, fill=color.hex)  # Draw a line to represent the pixel.

def reflect_dots_diag(dots, xc, yc):
    """
    Reflect dots diagonally across a point.

    Args:
        dots (list): List of dots to be reflected.
        xc (int): X-coordinate of the reflection point.
        yc (int): Y-coordinate of the reflection point.

    Returns:
        None
    """
    count_dots = len(dots)

    for i in range(count_dots):
        # Reflect each dot across the diagonal.
        dots.append([dots[i][1] - yc + xc, dots[i][0] - xc + yc, dots[i][2]])

def reflect_dots_Oy(dots, xc):
    """
    Reflect dots across the Y-axis.

    Args:
        dots (list): List of dots to be reflected.
        xc (int): X-coordinate of the reflection axis.

    Returns:
        None
    """
    count_dots = len(dots)

    for i in range(count_dots):
        # Reflect each dot across the Y-axis.
        dots.append([-(dots[i][0] - xc) + xc, dots[i][1], dots[i][2]])

def reflect_dots_Ox(dots, yc):
    """
    Reflect dots across the X-axis.

    Args:
        dots (list): List of dots to be reflected.
        yc (int): Y-coordinate of the reflection axis.

    Returns:
        None
    """
    count_dots = len(dots)

    for i in range(count_dots):
        # Reflect each dot across the X-axis.
        dots.append([dots[i][0], -(dots[i][1] - yc) + yc, dots[i][2]])

def draw_pixels(canvas, dot, xc, yc, circle=True):
    """
    Draw pixels on the canvas.

    Args:
        canvas: Canvas object to draw on.
        dot (list): Dot to be drawn [x, y, color].
        xc (int): X-coordinate of the center.
        yc (int): Y-coordinate of the center.
        circle (bool): Indicates if the pixels are part of a circle.

    Returns:
        None
    """
    dots = [dot]  # Initialize a list to store the dots.

    if circle:
        reflect_dots_diag(dots, xc, yc)  # Reflect dots diagonally if drawing a circle.

    reflect_dots_Oy(dots, xc)  # Reflect dots across the Y-axis.
    reflect_dots_Ox(dots, yc)  # Reflect dots across the X-axis.

    if dots[0][2] == cu.Color((255, 255, 255)):
        # If the color is white, draw multiple times to ensure visibility.
        for _ in range(6):
            for i in dots:
                set_pixel(canvas, i[0], i[1], i[2])
    else:
        # Draw each dot on the canvas.
        for i in dots:
            set_pixel(canvas, i[0], i[1], i[2])
