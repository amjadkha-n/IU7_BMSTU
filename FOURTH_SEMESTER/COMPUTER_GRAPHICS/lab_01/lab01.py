# На плоскости дано множество точек. Найти такой треугольник с вершинами в этих точках,
# у которого разность максимального и минимального количества точек, попавших в каждый из
# 6-ти треугольников, образованных пересечением медиан, максимальна.

from doctest import master
import tkinter as tk
import tkinter.messagebox as box
from tkinter import *

# a subclass of Canvas for dealing with resizing of windows
class ResizingCanvas(Canvas):
    def __init__(self,parent,**kwargs):
        Canvas.__init__(self,parent,**kwargs)
        self.bind("<Configure>", self.on_resize)
        self.height = self.winfo_reqheight()
        self.width = self.winfo_reqwidth()

    def on_resize(self,event):
        # determine the ratio of old width/height to new width/height
        wscale = float(event.width)/self.width
        hscale = float(event.height)/self.height
        self.width = event.width
        self.height = event.height
        # resize the canvas 
        self.config(width=self.width, height=self.height)
        # rescale all the objects tagged with the "all" tag
        self.scale("all",0,0,wscale,hscale)

class Dot(object):
    def __init__(self, x, y):
        """
        Initialize a Dot object with given x and y coordinates.

        Parameters:
            x (float): The x-coordinate of the dot.
            y (float): The y-coordinate of the dot.
        """
        self.x = x
        self.y = y
    
    def __str__(self):
        """
        Return a string representation of the Dot object.

        Returns:
            str: A string representing the Dot object in the format "(x; y)".
        """
        return ("({}; {})".format(self.x, self.y))

class Line(object):
    def __init__(self, dot_1, dot_2):
        """
        Initialize a Line object with two given points.

        Parameters:
            dot_1 (Dot): The first endpoint of the line segment.
            dot_2 (Dot): The second endpoint of the line segment.
        """
        if dot_1.x == dot_2.x and dot_1.y == dot_2.y:
            return  # If the two points are the same, the line does not exist
        self.dot_1 = dot_1  # First endpoint
        self.dot_2 = dot_2  # Second endpoint
        # Calculate the midpoint of the line segment
        self.center = Dot((dot_1.x + dot_2.x) / 2, (dot_1.y + dot_2.y) / 2)
        # Calculate coefficients of the line equation (Ax + By + C = 0)
        self.A = dot_1.y - dot_2.y
        self.B = dot_2.x - dot_1.x
        self.C = dot_1.x * dot_2.y - dot_2.x * dot_1.y
        # Initialize line borders with endpoints
        self.border_1 = dot_1
        self.border_2 = dot_2

    def print_info(self):
        """
        Print the coefficients of the line equation.
        """
        print(str(self.A) + "x + " + str(self.B) + "y + " + str(self.C))

    def find_intersection(self, line):
        """
        Find the intersection point of two lines.

        Parameters:
            line (Line): The other line to find the intersection with.

        Returns:
            Dot or None: The intersection point if it exists, None otherwise.
        """
        tmp = self.A * line.B - self.B * line.A
        if abs(tmp) >= 1e-7:  # Check if the lines are not parallel
            x = (self.B * line.C - line.B * self.C) / tmp
            y = (self.C * line.A - self.A * line.C) / tmp
            return Dot(x, y)
        else:
            return None  # Lines are parallel, no intersection

    def find_borders(self):
        """
        Find the borders of the line on the canvas.
        """
        if self.A == 0:  # If line is horizontal
            self.border_1 = Dot((-size[0] - 50) * scale[1], self.dot_1.y)
            self.border_2 = Dot((size[0] + 50) * scale[1], self.dot_1.y)
        elif self.B == 0:  # If line is vertical
            self.border_1 = Dot(self.dot_1.x, (size[1] + 50) * scale[1])
            self.border_2 = Dot(self.dot_1.x, (-size[1] - 50) * scale[1])
        else:  # If line is inclined
            self.border_1 = Dot((-size[0] - 50) * scale[1], (-self.C - self.A * (-size[0] - 50) * scale[1]) / self.B)
            self.border_2 = Dot((size[0] + 50) * scale[1], (-self.C - self.A * (size[0] + 50) * scale[1]) / self.B)

    def print_line(self):
        """
        Print the line segment on the canvas with green color.
        """
        self.find_borders()
        x1 = int(self.border_1.x / scale[1]) + size[0] / 2
        y1 = (-1) * int(self.border_1.y / scale[1]) + size[1] / 2
        x2 = int(self.border_2.x / scale[1]) + size[0] / 2
        y2 = (-1) * int(self.border_2.y / scale[1]) + size[1] / 2
        canvas.create_line(x1, y1, x2, y2, fill='green', activewidth=3)

    def print_target(self):
        """
        Print the line segment on the canvas with red color.
        """
        self.find_borders()
        x1 = int(self.border_1.x / scale[1]) + size[0] / 2
        y1 = (-1) * int(self.border_1.y / scale[1]) + size[1] / 2
        x2 = int(self.border_2.x / scale[1]) + size[0] / 2
        y2 = (-1) * int(self.border_2.y / scale[1]) + size[1] / 2
        canvas.create_line(x1, y1, x2, y2, fill='red', activewidth=3)

def find_middle(first, second):
    """
    Find the midpoint between two given points.

    Parameters:
        first (Dot): The first point.
        second (Dot): The second point.

    Returns:
        Dot: The midpoint between the two points.
    """
    x = (first.x + second.x) / 2  # Calculate the x-coordinate of the midpoint
    y = (first.y + second.y) / 2  # Calculate the y-coordinate of the midpoint
    middle = Dot(x, y)  # Create a Dot object representing the midpoint
    return middle

def find_len(dot_1, dot_2):
    """
    Calculate the Euclidean distance between two points.

    Parameters:
        dot_1 (Dot): The first point.
        dot_2 (Dot): The second point.

    Returns:
        float: The Euclidean distance between the two points.
    """
    return ((dot_1.x - dot_2.x) ** 2 + (dot_1.y - dot_2.y) ** 2) ** (1 / 2)


def draw_axes(scale, x0, y0):
    """
    Draw coordinate axes on the canvas.

    Parameters:
        scale (float): The scale factor.
        x0 (int): X-coordinate of the origin.
        y0 (int): Y-coordinate of the origin.
    """
    border = 60
    delta = 50
    x = 80
    real_x = x0
    real_delta = delta * scale
    smol = 10
    # Draw x-axis
    canvas.create_line(x, size[1] + border, size[0] + x, size[1] + border, width=3)
    while x < size[0] + border:
        canvas.create_line(x, size[1] + border - smol / 2, x, size[1] + border + smol / 2, width=3)
        canvas.create_text(x, size[1] + border + 1.5 * smol, text=f'{real_x:5.2f}')
        x += delta
        real_x += real_delta
    # Draw y-axis
    x = 80
    y = size[1] + border
    real_y = y0
    canvas.create_line(x, 0, x, size[1] + border, width=3)
    while y > 0:
        canvas.create_line(x - smol / 2, y, x + smol / 2, y, width=3)
        canvas.create_text(x - 4 * smol, y, text=f'{real_y:5.2f}')
        y -= delta
        real_y += real_delta


class Triangle(object):
    """
    Represents a triangle on the canvas.

    Attributes:
        middle_ab (Dot): Middle point of side AB.
        middle_bc (Dot): Middle point of side BC.
        middle_ac (Dot): Middle point of side AC.
        median_middle (Dot): Middle point of the median intersecting at the centroid.
        square (float): Area of the triangle.
        a (Dot): Vertex A of the triangle.
        b (Dot): Vertex B of the triangle.
        c (Dot): Vertex C of the triangle.
    """

    middle_ab = Dot(0, 0)
    middle_bc = Dot(0, 0)
    middle_ac = Dot(0, 0)
    median_middle = Dot(0, 0)
    square = 0

    def __init__(self, a, b, c):
        """
        Initializes a triangle with given vertices.

        Parameters:
            a (Dot): Vertex A of the triangle.
            b (Dot): Vertex B of the triangle.
            c (Dot): Vertex C of the triangle.
        """
        self.a = a
        self.b = b
        self.c = c
        # Calculate the middle points of sides AB, BC, and AC
        self.middle_ab = find_middle(a, b)
        self.middle_bc = find_middle(b, c)
        self.middle_ac = find_middle(a, c)
        # Calculate the area of the triangle and the middle point of the median
        ab = find_len(a, b)
        bc = find_len(b, c)
        ac = find_len(a, c)
        p = (ab + bc + ac) / 2
        self.square = (p * (p - ac) * (p - bc) * (p - ab)) ** (1 / 2)
        if abs(self.square) <= 1e-7:
            self.square = 0
            self.median_middle = Dot(0, 0)
        else:
            self.median_middle = Line(self.a, self.middle_bc).find_intersection(Line(self.b, self.middle_ac))

    def has(self, dot):
        """
        Check if a point lies inside the triangle.

        Parameters:
            dot (Dot): The point to check.

        Returns:
            bool: True if the point is inside the triangle, False otherwise.
        """
        return abs(self.square \
            - Triangle(self.a, self.b, dot).square \
                - Triangle(self.b, self.c, dot).square \
                    - Triangle(self.a, self.c, dot).square) < 1e-7

    def print_info(self):
        """Prints the vertices of the triangle."""
        print(str(self.a) + ", " + str(self.b) + ", " + str(self.c))
    
    def print_info_to_entry(self, i, j, k):
        """
        Prints the vertices of the triangle to the entry widget.

        Parameters:
            i (int): Index of vertex A.
            j (int): Index of vertex B.
            k (int): Index of vertex C.
        """
        results_entry.configure(state='normal')
        results_entry.delete(0, last='end')
        string = f"Vertices at points {i:2d})" + str(self.a) + f", {j:2d})" + str(self.b) + f", {k:2d})" + str(self.c)
        results_entry.insert(0, string)
        results_entry.configure(state='readonly')
            
    def draw(self, with_medians, with_dots, i, j, k):
        """
        Draw the triangle on the canvas.

        Parameters:
            with_medians (bool): Whether to draw the medians.
            with_dots (bool): Whether to draw the points inside the triangle.
            i (int): Index of vertex A.
            j (int): Index of vertex B.
            k (int): Index of vertex C.
        """
        # Clear the canvas
        canvas.delete("all")
        # Find maximum and minimum coordinates among triangle vertices
        max_x = max(self.a.x, self.b.x, self.c.x)
        min_x = min(self.a.x, self.b.x, self.c.x)
        max_y = max(self.a.y, self.b.y, self.c.y)
        min_y = min(self.a.y, self.b.y, self.c.y)
         # Calculate deltas
        delta_x = max_x - min_x
        delta_y = max_y - min_y
        # Initialize scale to 1
        scale = 1
        # Calculate width and height based on deltas
        width = 4 * delta_x / 3
        height = 4 * delta_y / 3
        # Adjust scale based on the aspect ratio
        if width / height < size[0] / size[1]:
            scale = height / size[1]
        else:
            scale = width / size[0]
        # Update width and height based on scale
        width = scale * size[0]
        height = scale * size[1]
        # Print the calculated scale
        print("Scale: {}".format(scale))
        # Calculate initial coordinates for drawing axes
        x0 = min_x - width * 1 / 6
        y0 = min_y - height * 1 / 6
        # Draw axes on the canvas
        draw_axes(scale, x0, y0)
        # Initialize parameters for drawing
        border = 60
        delta = 50
        x = 80
        real_x = x0
        real_delta = delta * scale
        smol = 10
        x0_im = x0 / scale
        y0_im = y0 / scale
        ax_im = self.a.x / scale - x0 / scale + x
        bx_im = self.b.x / scale - x0 / scale + x
        cx_im = self.c.x / scale - x0 / scale + x

        ay_im = size[1] + border - ((self.a.y - y0) / scale)
        by_im = size[1] + border - ((self.b.y  - y0) / scale)
        cy_im = size[1] + border - ((self.c.y - y0) / scale)
        # Draw triangle
        canvas.create_polygon(ax_im, ay_im, bx_im, by_im, cx_im, cy_im, width=2, fill="white", outline="black")
        # Draw medians if required
        if with_medians:
            middle_ab_x_im = self.middle_ab.x / scale - x0 / scale + x
            middle_bc_x_im = self.middle_bc.x / scale - x0 / scale + x
            middle_ac_x_im = self.middle_ac.x / scale - x0 / scale + x

            middle_ab_y_im = size[1] + border - ((self.middle_ab.y - y0) / scale)
            middle_bc_y_im = size[1] + border - ((self.middle_bc.y - y0) / scale)
            middle_ac_y_im = size[1] + border - ((self.middle_ac.y - y0) / scale)
            
            canvas.create_line(middle_ab_x_im, middle_ab_y_im, cx_im, cy_im, width=2, fill="grey")
            canvas.create_line(middle_bc_x_im, middle_bc_y_im, ax_im, ay_im, width=2, fill="grey")
            canvas.create_line(middle_ac_x_im, middle_ac_y_im, bx_im, by_im, width=2, fill="grey")
        # Shift for displaying text
        shift = 15
        # Draw dots if required
        if with_dots:
            radius = 4
            for i, dot in enumerate(dots):
                if dot != self.a and dot != self.b and dot != self.c and self.has(dot):
                    x_im = dot.x / scale - x0 / scale + x
                    y_im = size[1] + border - ((dot.y - y0) / scale)
                    canvas.create_oval(x_im - radius, y_im - radius, x_im + radius, y_im + radius, fill="red")
                    canvas.create_text(x_im, y_im + shift, text=f"{i + 1:2d}) ({dot.x:4.3f}; {dot.y:4.3f})", font="Times 14")
         # Draw vertices of the triangle
        radius = 4
        canvas.create_oval(ax_im - radius, ay_im - radius, ax_im + radius, ay_im + radius, fill="red")
        canvas.create_oval(bx_im - radius, by_im - radius, bx_im + radius, by_im + radius, fill="red")
        canvas.create_oval(cx_im - radius, cy_im - radius, cx_im + radius, cy_im + radius, fill="red")
         # Display coordinates of the vertices
        canvas.create_text(ax_im, ay_im + shift, text=f"{i:2d}) ({self.a.x:4.3f}; {self.a.y:4.3f})", font="Times 14")
        canvas.create_text(bx_im, by_im + shift, text=f"{j:2d}) ({self.b.x:4.3f}; {self.b.y:4.3f})", font="Times 14")
        canvas.create_text(cx_im, cy_im + shift, text=f"{k:2d}) ({self.c.x:4.3f}; {self.c.y:4.3f})", font="Times 14")

def enter_dot():
    """
    Adds a new dot to the list of dots.

    Reads coordinates from the entry widget, creates a Dot object, and appends it to the dots list.
    Updates the dots listbox with the new dot.

    If the input format is incorrect, displays a warning message.

    """
    try:
        # Attempt to extract x and y coordinates from the entry widget
        x, y = map(float, dots_entry.get().split())
        # Create a new Dot object with the given coordinates
        new_dot = Dot(x, y)
        # Append the new dot to the dots list
        dots.append(new_dot)
        # Format the dot coordinates as a string
        dot_string = "{:d}) ({:6.4f}; {:6.4f})".format(len(dots), x, y)
        # Insert the dot string into the dots listbox
        dots_listbox.insert(len(dots), dot_string)
        # Clear the entry widget after successful input
        dots_entry.delete(0, last='end')
    except ValueError:
        # Display a warning message if the input format is incorrect
        box.showwarning("Ошибка ввода", "Вы ввели неверные координаты точки. Координаты точек - вещественные числа, введённые через пробел")


def delete_dot():
    """
    Deletes a dot from the list of dots.

    Reads the index of the dot to be deleted from the entry widget.
    Removes the dot from the dots list and updates the dots listbox accordingly.
    Updates the indices of dots in the dots listbox after deletion.

    If the input format is incorrect or the index is out of range, displays a warning message.

    """
    try:
        # Attempt to extract the index of the dot to be deleted from the entry widget
        number = int(delete_dot_entry.get())
        # Check if the index is within the valid range
        if number >= 0 and number <= dots_listbox.size():
            # Remove the dot from the dots list
            dots.pop(number - 1)
            # Delete the dot from the dots listbox
            dots_listbox.delete(number - 1)
            # Update the indices of dots in the dots listbox after deletion
            for i in range(dots_listbox.size()):
                # Extract dot information from the listbox entry
                dot_string = dots_listbox.get(i)
                # Remove unnecessary characters from the dot string
                dot_string = dot_string.replace(")", "")
                dot_string = dot_string.replace("(", "")
                dot_string = dot_string.replace(";", "")
                # Extract dot number, x, and y coordinates from the dot string
                cur_num, x, y = map(float, dot_string.split())
                cur_num = int(cur_num)
                # If the dot number is greater than or equal to the deleted dot's number, update it
                if cur_num >= number:
                    cur_num -= 1
                    # Format the updated dot string with the new dot number
                    dot_string = "{:d}) ({:6.4f}; {:6.4f})".format(cur_num, x, y)
                    # Delete the old entry and insert the updated entry in the dots listbox
                    dots_listbox.delete(cur_num - 1)
                    dots_listbox.insert(cur_num - 1, dot_string)
            # Clear the entry widget after successful deletion
            delete_dot_entry.delete(0, last='end')
        else:
            # Clear the entry widget if the index is out of range
            delete_dot_entry.delete(0, last='end')
            # Display a warning message for invalid input
            box.showwarning("Ошибка ввода", "Вы ввели неверный номер точки. Уточните, пожалуйста")
    except ValueError:
        # Display a warning message if the input format is incorrect
        box.showwarning("Ошибка ввода", "Вы ввели неверный номер точки. Номер точки - неотрицательное целое число")


def edit_dot():
    """
    Edits the coordinates of a dot in the list of dots.

    Reads the index and new coordinates of the dot from the entry widget.
    Updates the dot with the new coordinates in the dots list and updates the dots listbox accordingly.

    If the input format is incorrect or the index is out of range, displays a warning message.

    """
    try:
        # Attempt to extract the index and new coordinates of the dot from the entry widget
        number, x, y = map(float, edit_dot_entry.get().split())
        number = int(number)
        # Check if the index is within the valid range
        if number >= 0 and number <= dots_listbox.size():
            # Format the dot string with the new coordinates
            dot_string = "{:d}) ({:6.4f}; {:6.4f})".format(number, x, y)
            # Create a new dot with the new coordinates
            new_dot = Dot(x, y)
            # Update the dot at the specified index in the dots list
            dots[number - 1] = new_dot
            # Delete the old dot entry and insert the updated dot entry in the dots listbox
            dots_listbox.delete(number - 1)
            dots_listbox.insert(number - 1, dot_string)
            # Clear the entry widget after successful edit
            edit_dot_entry.delete(0, last='end')
        else:
            # Clear the entry widget if the index is out of range
            edit_dot_entry.delete(0, last='end')
            # Display a warning message for invalid input
            box.showwarning("Ошибка ввода", "Вы ввели неверный номер точки. Номер точки - неотрицательное целое число")
    except ValueError:
        # Display a warning message if the input format is incorrect
        box.showwarning("Ошибка ввода", "Номер точки - неотрицательное целое число, координаты - действительные числа")


def enter_dot_event(event):
    enter_dot()

def del_dots():
    dots.clear()
    dots_entry.delete(0, last='end')
    dots_listbox.delete(0, dots_listbox.size())

def delete_dot_event(event):
    delete_dot()

def edit_dot_event(event):
    edit_dot()

def is_parallel(line_1, line_2):
    """
    Checks if two lines are parallel.

    This function determines whether two lines are parallel by comparing their coefficients. It first checks if both lines are horizontal 
    or vertical, in which case they are considered parallel. Then, it compares the ratios of the coefficients A and B for both lines. 
    If the ratios are equal within a small tolerance, the lines are considered parallel.

    Args:
        line_1 (Line): The first line object.
        line_2 (Line): The second line object.

    Returns:
        int: 1 if the lines are parallel, 0 otherwise.

    """
    # Check if both lines are horizontal or vertical
    if line_1.A == 0 and line_2.A == 0 or line_1.B == 0 and line_2.B == 0:
        return 1
    
    # Check if the ratios of coefficients A and B are equal within a tolerance
    if line_1.A != 0 and line_1.B != 0 and line_2.A != 0 and line_2.B != 0 \
            and abs(line_1.A / line_2.A - line_1.B / line_2.B) < 1e-8:
        return 1
    
    return 0


def process(triangle):
    """
    Processes a triangle to calculate the difference between the maximum and minimum number of points within the sub-triangles formed by its medians.

    This function calculates the difference between the maximum and minimum number of points within the six sub-triangles formed by the medians 
    of the input triangle. It iterates through each dot in the set of points and checks which sub-triangle the dot belongs to. Then, 
    it counts the number of dots in each sub-triangle. Finally, it computes the difference between the maximum and minimum dot counts.

    Args:
        triangle (Triangle): The triangle object to be processed.

    Returns:
        int: The difference between the maximum and minimum number of points within the sub-triangles.
    """
    amount = len(dots)
    min_amount = -1
    max_amount = amount + 1

    amount_1 = 0; amount_2 = 0; amount_3 = 0
    amount_4 = 0; amount_5 = 0; amount_6 = 0
    
    # Form sub-triangles using the medians of the input triangle
    first = Triangle(triangle.a, triangle.middle_ab, triangle.median_middle)
    second = Triangle(triangle.b, triangle.middle_ab, triangle.median_middle)
    third = Triangle(triangle.b, triangle.middle_bc, triangle.median_middle)
    fourth = Triangle(triangle.median_middle, triangle.middle_bc, triangle.c)
    fifth = Triangle(triangle.median_middle, triangle.c, triangle.middle_ac)
    sixth = Triangle(triangle.median_middle, triangle.middle_ac, triangle.a)
    
    # Iterate through each dot and count the number of dots in each sub-triangle
    for dot in dots:
        if dot != triangle.a and dot != triangle.b and dot != triangle.c:
            if first.has(dot):
                amount_1 += 1
            if second.has(dot):
                amount_2 += 1
            if third.has(dot):
                amount_3 += 1
            if fourth.has(dot):
                amount_4 += 1
            if fifth.has(dot):
                amount_5 += 1
            if sixth.has(dot):
                amount_6 += 1

    # Compute the difference between the maximum and minimum dot counts
    result = max(amount_1, amount_2, amount_3, amount_4, amount_5, amount_6) - min(amount_1, amount_2, amount_3, amount_4, amount_5, amount_6)
    return result


def find():
    """
    Finds the triangle with the maximal difference between the maximum and minimum number of points within the sub-triangles formed by its medians.

    This function iterates through all combinations of three distinct points from the set of dots. For each combination, 
    it constructs a triangle and calculates the difference between the maximum and minimum number of points within the
     sub-triangles formed by its medians using the process function. It keeps track of the triangle with the highest
      difference and returns it along with the indices of its vertices.

    Returns:
        Tuple: A tuple containing the triangle object with the maximal difference, and the indices of its vertices (1-indexed).
    """
    top_result = -1
    res_triangle = None
    i_res = 0
    j_res = 0
    k_res = 0

    # Iterate through all combinations of three distinct points
    for i, a in enumerate(dots):
        for j, b in enumerate(dots):
            for k, c in enumerate(dots):
                if a != b and a != c and b != c:
                    triangle = Triangle(a, b, c)
                    # If the triangle is valid and not already found
                    if not res_triangle and triangle:
                        res_triangle = triangle
                        i_res = i
                        j_res = j
                        k_res = k
                    # If the triangle is valid, calculate the difference between max and min dot counts
                    if abs(triangle.square) > 1e-7 and triangle.median_middle != None:
                        result = process(triangle)
                        # Update the top result if the current triangle has a higher difference
                        if result > top_result:
                            top_result = result
                            res_triangle = triangle
                            i_res = i
                            j_res = j
                            k_res = k
    return res_triangle, i_res + 1, j_res + 1, k_res + 1

def is_inside(dot):
    """
    Checks if a given dot is inside the visible area of the canvas.

    Args:
        dot (Dot): The dot to be checked.

    Returns:
        bool: True if the dot is inside the visible area, False otherwise.
    """
    # Check if the dot's coordinates fall within the visible area of the canvas
    if 0 < dot.x / scale[1] + size[0] / 2 < size[0] and 0 < dot.y / scale[1] - size[1]/2 < size[1]:
        return True
    else:
        return False


def find_scale():
    """
    Finds the appropriate scale factor for drawing objects on the canvas.

    This function calculates the scale factor based on the range of coordinates
    of the dots and lines in the current drawing, ensuring that all objects fit
    within the visible area of the canvas.

    """
    # Initialize variables to store minimum and maximum coordinates
    min_x = 100000000000
    min_y = 100000000000
    max_x = -100000000000
    max_y = -100000000000
    
    # Iterate through all dots to find the minimum and maximum coordinates
    for dot in dots:
        if dot.x > max_x:
            max_x = dot.x
        if dot.x < min_x:
            min_x = dot.x
        if dot.y > max_y:
            max_y = dot.y
        if dot.y < min_y:
            min_y = dot.y
    
    # Iterate through all lines to find the minimum and maximum coordinates of their endpoints
    for line in lines:
        dot = line.dot_1
        if dot.x > max_x:
            max_x = dot.x
        if dot.x < min_x:
            min_x = dot.x
        if dot.y > max_y:
            max_y = dot.y
        if dot.y < min_y:
            min_y = dot.y
        dot = line.dot_2
        if dot.x > max_x:
            max_x = dot.x
        if dot.x < min_x:
            min_x = dot.x
        if dot.y > max_y:
            max_y = dot.y
        if dot.y < min_y:
            min_y = dot.y
    
    # Calculate the scale factor based on the range of coordinates and the size of the canvas
    scale[1] = max(abs(max_x - min_x) / size[0] * 2, abs(max_y - min_y) / size[1] * 2) * 1.1

def build(triangle, i, j, k):
    """
    Build and display the triangle on the canvas.

    Args:
    - triangle: The triangle object to build and display.
    - i: Index of the first vertex.
    - j: Index of the second vertex.
    - k: Index of the third vertex.

    This function prints information about the triangle, sets up an entry
    in the GUI to display triangle information, clears the canvas, and draws
    the triangle with medians and dots.

    """
    if triangle:
        triangle.print_info()  # Print information about the triangle
        triangle.print_info_to_entry(i, j, k)  # Set up an entry in the GUI to display triangle information
        canvas.delete("all")  # Clear the canvas
        triangle.draw(True, True, i, j, k)  # Draw the triangle with medians and dots

def find_and_build():
    """
    Find a suitable triangle and build it on the canvas.

    This function first checks if there are enough dots to form a triangle.
    If there are, it finds a suitable triangle using the `find()` function.
    Then, it builds and displays the triangle on the canvas using the `build()`
    function.

    """
    if len(dots) < 3:
        box.showwarning("Недостаточное количество точек", "Элементов недостаточно. Введите больше точек (как минимум 3)")
        return 
    triangle, i, j, k = find()  # Find a suitable triangle
    if triangle:
        if abs(triangle.square) < 1e-7:
            box.showwarning("Все треугольники вырожденные", "Не удалось найти подходящий треугольник. Попробуйте добавить больше точек в множество")
        else:
            build(triangle, i, j, k)  # Build and display the triangle


dots = []  # массив для точек
lines = []  # координаты точек, задающих прямую
scale = [1, 1]  # масштаб для canvas
size = [1600, 600]
main_window = tk.Tk()
main_window.geometry("1600x1500")
main_window.title("Лаб. работа №1 \"Геометрическая задача")
dots_listbox = tk.Listbox(master=main_window, font='Times 14', height=14)

task_label1 = tk.Label(master=main_window, text='На плоскости дано множество точек. Найти такой треугольник с вершинами в этих точках, у которого разность макс.',
                      font='Times 14')
task_label2 = tk.Label(master=main_window, text='и мин. количества точек, попавших в каждый из 6-ти треугольников, образованных пересечением медиан, максимальна.',
                      font='Times 14')
task_label1.grid(row=0, column=0, columnspan=100)
task_label2.grid(row=1, column=0, columnspan=100)

dots_label = tk.Label(master=main_window, text='Добавление точки. Введите координаты по х, у через \
пробел:', font='Times 14')
dots_label.grid(row=2, column=0)
dots_entry = tk.Entry(master=main_window, font='Times 14')
dots_entry.bind("<Return>", enter_dot_event)
dots_entry.grid(row=2, column=1)
dots_button = tk.Button(master=main_window, text='Добавить точку', font='Times 14', command=enter_dot)
dots_button.grid(row=2, column=2)
dots_listbox_label = tk.Label(master=main_window, text='Введённые точки:', font='Times 14')
dots_listbox_label.grid(row=2, column=3)
dots_listbox.grid(row=2, column=4, rowspan=4)
dots_del_button = tk.Button(master=main_window, text='Сброс', font='Times 14', command=del_dots)
dots_del_button.grid(row=3, column=2)

delete_label = tk.Label(master=main_window, text='Удаление. Для удаления введите номер точки:', font='\
Times 14')
delete_label.grid(row=4, column=0)
delete_dot_entry = tk.Entry(master=main_window, font='Times 14')
delete_dot_entry.bind("<Return>", delete_dot_event)
delete_dot_entry.grid(row=4, column=1)
delete_dot_button = tk.Button(master=main_window, text='Удалить точку', font='Times 14', command=delete_dot)
delete_dot_button.grid(row=4, column=2)

edit_dot_label = tk.Label(master=main_window, text='Редактирование. Введите номер точки и новые координаты, через пробел:', font='Times 14')
edit_dot_label.grid(row=5, column=0)
edit_dot_entry = tk.Entry(master=main_window, font='Times 14')
edit_dot_entry.bind("<Return>", edit_dot_event)
edit_dot_entry.grid(row=5, column=1)
edit_dot_button = tk.Button(master=main_window, text='Редактировать', font='Times 14', command=edit_dot)
edit_dot_button.grid(row=5, column=2)

final_button = tk.Button(master=main_window, text='Найти треугольник, построить иллюстрацию', font='Arial\
 16', command=find_and_build)
final_button.grid(row=6, column=0)
results_label = tk.Label(master=main_window, text='Результаты: ', font='Times 16')
results_label.grid(row=6, column=1)
results_entry = tk.Entry(master=main_window, font='Times 16', width=60, state='disabled')
results_entry.grid(row=6, column=2, columnspan=3)

canvas = ResizingCanvas(main_window, height=size[1], width=size[0], bg='white')
canvas.grid(row=7, column=0, columnspan=7)

for row_num in range(main_window.grid_size()[1]):
    main_window.rowconfigure(row_num, weight=1)
for col_num in range(main_window.grid_size()[0]):
    main_window.columnconfigure(col_num, weight=1)

main_window.mainloop()