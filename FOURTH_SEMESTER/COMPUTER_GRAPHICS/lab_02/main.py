from tkinter import *
from tkinter import messagebox
import copy
from math import cos, sin, pi, sqrt
from math import cos, sin, radians
from tkinter import StringVar, Label, Entry, Button

# Hides/shows axes
# This function is responsible for hiding or showing the axes on the canvas based on the value of the 'hide' parameter. 
# If the value of 'hide' is 1, it clears the canvas and redraws the points stored in the ActionsStack, effectively hiding 
# the axes. If the value of 'hide' is 0, it calls the 'over_func()' function with the 'OverVar' parameter, which determines
#  whether to draw the axes over or under the existing points.
# Function to hide/show axes based on the value of the 'hide' parameter
# def hide_func(hide):
#     # Check if the 'hide' parameter is equal to 1
#     if hide.get() == 1:
#         # If 'hide' is equal to 1, delete all items on the canvas
#         Can.delete("all")
#         # Redraw the points stored in the last element of the ActionsStack
#         draw_points(ActionsStack[-1])
#     # Check if the 'hide' parameter is equal to 0
#     if hide.get() == 0:
#         # If 'hide' is equal to 0, call the over_func() function with the OverVar parameter
#         over_func(OverVar)


# Purpose of the function:
# This function controls whether axes should be drawn over or under the existing points on the canvas based on the 
# value of the 'over' parameter. It first checks if the HideVar is equal to 0, meaning the axes are not hidden. If 
# 'over' is equal to 1, it clears the canvas, redraws the points from the ActionsStack, and then draws the axes on 
# top of them. If 'over' is equal to 0, it clears the canvas, draws the axes, and then redraws the points on top of the axes.
# Makes axes over/under picture
# Function to make axes appear over/under the picture based on the value of the 'over' parameter
# def over_func(over):
#     # Check if HideVar is equal to 0
#     if HideVar.get() == 0:
#         # Check if the value of the 'over' parameter is equal to 1
#         if over.get() == 1:
#             # If 'over' is equal to 1, clear the canvas
#             Can.delete("all")
#             # Redraw the points stored in the last element of the ActionsStack
#             draw_points(ActionsStack[-1])
#             # Draw axes over the points
#             draw_axes()
#         # Check if the value of the 'over' parameter is equal to 0
#         if over.get() == 0:
#             # If 'over' is equal to 0, clear the canvas
#             Can.delete("all")
#             # Draw axes on the canvas
#             draw_axes()
#             # Redraw the points stored in the last element of the ActionsStack
#             draw_points(ActionsStack[-1])


# Purpose of the function:
# This function is responsible for drawing various shapes (polygons, lines, ovals, and arcs) on the canvas based on 
# the data provided in the 'points' parameter. It iterates over each category of points and uses the create_polygon(), 
# create_line(), and create_oval() methods of the Canvas widget to draw the corresponding shapes with appropriate fill colors and outline colors.
# Draws points
# Function to draw points on the canvas
def draw_points(points):
    # Iterate over polygons in the first element of the 'points' list
    for pol in points[0]:
        # Create a polygon on the canvas with the specified points, fill color, and outline color
        # Can.create_polygon(), Can.create_line(): Built-in functions provided by the Tkinter library for creating shapes on a canvas.
        Can.create_polygon(pol, fill="white", outline="black")

    # Iterate over lines in the second element of the 'points' list
    for line in points[1]:
        # Create a line on the canvas with the specified coordinates
        Can.create_line(line)

    # Iterate over ovals in the third element of the 'points' list
    for oval in points[2]:
        # Create a line (which may represent an oval) on the canvas with the specified coordinates
        Can.create_line(oval)

    # Iterate over arcs in the fourth element of the 'points' list
    for arc in points[3]:
        # Create a line (which may represent an arc) on the canvas with the specified coordinates
        Can.create_line(arc)


# Purpose of the function:
# This function takes a point, an angle of rotation, and a center of rotation as input parameters. It computes 
# the new coordinates of the point after rotating it around the specified center by the given angle. The function uses 
# trigonometric functions to perform the rotation calculations and returns the new coordinates as a list.
# Function to rotate a point around a given center
def rotate_point(point, angle, center):
    # Unpack the coordinates of the point and the center
    # Here, the point tuple is unpacked into x and y, representing the coordinates of the point to be rotated.
    x, y = point
    # Similarly, the center tuple is unpacked into cx and cy, representing the coordinates of the center of rotation.
    cx, cy = center
    # Compute the new coordinates after rotation
    # The formula used here is the rotation matrix formula applied to each coordinate.
    # Subtract cx from x to shift the origin to the center of rotation.
    # Multiply the difference (x - cx) by the cosine of the angle (converted to radians) to compute the new x-coordinate after rotation.
    # Similarly, subtract cy from y to shift the origin vertically to the center of rotation.
    # Multiply the difference (y - cy) by the sine of the angle (converted to radians) to compute the new x-coordinate after rotation.
    new_x = (x - cx) * cos(radians(angle)) - (y - cy) * sin(radians(angle)) + cx
    new_y = (x - cx) * sin(radians(angle)) + (y - cy) * cos(radians(angle)) + cy
    # Return the new coordinates as a list
    return [new_x, new_y]

# This function generates default points representing different shapes such as rectangles, lines, ovals, and arcs 
# based on a given origin (ox, oy). It initializes a list to store points for different types of shapes and then defines
#  points for each shape accordingly. The function computes and adds points for various structures like walls, doors,
#   cross-shaped structures, and roofs. Additionally, it rotates and shifts lines and adds them, along with ovals and arcs, to the 
#   respective lists. Finally, it returns the list of points representing the default shapes.
# # Function to generate default points representing various shapes at a given origin (ox, oy)
def get_default_points(ox, oy):
    # Initialize a list to store points for different shapes: polygons, lines, ovals, and arcs
    points = [[], [], [], []]

    # Define points for rectangles representing different structures
    # Wall structure
    # (ox - 200, oy - 100): This represents the bottom-left corner of the rectangle. It's calculated by subtracting 200 from 
    # the x-coordinate (ox) and 100 from the y-coordinate (oy).

    # (ox + 200, oy - 100): This represents the bottom-right corner of the rectangle. It's calculated by adding 200 to the 
    # x-coordinate (ox) and 100 from the y-coordinate (oy).

    # (ox + 200, oy + 100): This represents the top-right corner of the rectangle. It's calculated by adding 200 to the 
    # x-coordinate (ox) and 100 to the y-coordinate (oy).

    # (ox - 200, oy + 100): This represents the top-left corner of the rectangle. It's calculated by subtracting 200 from
    #  the x-coordinate (ox) and adding 100 to the y-coordinate (oy).
    points[0].append([[ox - 200, oy - 100], [ox + 200, oy - 100], [ox + 200, oy + 100], [ox - 200, oy + 100]])
    # Structure of the door
    points[0].append([[ox - 150, oy - 60], [ox - 50, oy - 60], [ox - 50, oy + 60], [ox - 150, oy + 60]])
    # Cross-shaped structure
    points[0].append([[ox + 100, oy - 30], [ox + 100, oy - 75], [ox + 100, oy + 30], [ox + 100, oy + 75]])
    points[0].append([[ox + 74, oy], [ox + 124, oy]])
    points[0].append([[ox + 100, oy - 60], [ox + 100, oy + 60]])
    # Structure of the roof
    # Scalene triangle for the roof with the smaller side on the left
    points[0].append([[ox + 200, oy - 100], [ox - 50, oy - 200], [ox - 200, oy - 100]])

    # Generate ellipse points to represent the roof
    ellipse = get_ellipse([ox + 99, oy], 25, 75)
    for i in range(len(ellipse)):
        points[0].append(ellipse[i])

    # Define points for lines
    points[1].append([[ox - 100, oy + 60], [ox - 100, oy - 78]])  # Line

    # Rotate lines by 45 degrees around the origin
    angle = 45
    center = [ox, oy]
    line_1 = [rotate_point([ox - 50, oy - 129], angle, center), rotate_point([ox - 50, oy - 170], angle, center)]
    line_2 = [rotate_point([ox - 77, oy - 128], angle, center), rotate_point([ox - 77, oy - 170], angle, center)]
    line_3 = [rotate_point([ox - 35, oy - 152], angle, center), rotate_point([ox - 35, oy - 203], angle, center)]

    # Move lines to the left in the x-axis
    shift_1 = 110 
    shift_2 = 110
    shift_3 = 150
    line_1 = [[coord[0] - shift_1, coord[1]] for coord in line_1]
    line_2 = [[coord[0] - shift_2, coord[1]] for coord in line_2]
    line_3 = [[coord[0] - shift_3, coord[1]] for coord in line_3]

    # Add the modified lines to points[1]
    points[1].append(line_1)
    points[1].append(line_2)
    points[1].append(line_3)

    # Define points for ovals
    ellipse = get_ellipse([ox - 50, oy - 150], 25, 25)
    for i in range(len(ellipse)):
        points[2].append(ellipse[i])

    # Define points for arcs
    arc = get_arc([ox - 100, oy - 60], 50, 18)
    for i in range(len(arc)):
        points[3].append(arc[i])

    # Return the points representing various shapes
    return points


# This function generates points along the circumference of an ellipse given its center and semi-major (a) 
# and semi-minor (b) axes. Each point is calculated using the parametric equation of the ellipse and is stored 
# in the ellipse list as line segments connecting consecutive points. The function then returns this list of points.
# Function to generate points representing an ellipse given its center and semi-major (a) and semi-minor (b) axes
def get_ellipse(centre, a, b):
    # Initialize a list to store points representing the ellipse
    ellipse = []
    # Define the number of points to generate along the ellipse circumference
    num = 60
    # Calculate the step size between each point based on the semi-major axis
    step = abs(a) * 2 / num

    # Generate points on the upper half of the ellipse
    for i in range(num):
        # Calculate x-coordinate of the current point
        x = -a + step * i
        # Calculate y-coordinate of the current point on the upper half of the ellipse
        y = sqrt((1 - (x**2)/(a**2)) * b**2)
        # Calculate x-coordinate of the next point
        x1 = -a + step * (i + 1)
        # Calculate y-coordinate of the next point on the upper half of the ellipse
        y1 = sqrt((1 - (x1**2)/(a**2)) * b**2)
        # Append line segments connecting consecutive points
        ellipse.append([[x + centre[0], y + centre[1]], [x1 + centre[0], y1 + centre[1]]])

    # Generate points on the lower half of the ellipse
    for i in range(num):
        # Calculate x-coordinate of the current point
        x = -a + step * i
        # Calculate y-coordinate of the current point on the lower half of the ellipse
        y = -sqrt((1 - (x**2)/(a**2)) * b**2)
        # Calculate x-coordinate of the next point
        x1 = -a + step * (i + 1)
        # Calculate y-coordinate of the next point on the lower half of the ellipse
        y1 = -sqrt((1 - (x1**2)/(a**2)) * b**2)
        # Append line segments connecting consecutive points
        ellipse.append([[x + centre[0], y + centre[1]], [x1 + centre[0], y1 + centre[1]]])

    # Return the list of points representing the ellipse
    return ellipse


# This function generates points along an arc of an ellipse given its center and semi-major (a) and semi-minor (b) axes. 
# It iterates through a specified number of points (num) along the arc and calculates the coordinates of each point on the 
# upper half of the arc using the parametric equation of the ellipse. Each point is stored as a line segment connecting it to 
# the next point on the upper half of the arc, and these line segments are appended to the arc list. Finally, the function returns
#  the list of points representing the arc.
# Function to generate points representing an arc of an ellipse given its center and semi-major (a) and semi-minor (b) axes
def get_arc(centre, a, b):
    # Initialize a list to store points representing the arc
    arc = []
    # Define the number of points to generate along the arc
    num = 60
    # Calculate the step size between each point based on the semi-major axis
    step = abs(a) * 2 / num

    # Generate points on the arc
    for i in range(num):
        # Calculate x and y coordinates of the current point on the upper half of the arc
        x = -a + step * i
        y = -sqrt((1 - (x**2)/(a**2)) * b**2)
        # Calculate x and y coordinates of the next point on the upper half of the arc
        x1 = -a + step * (i + 1)
        y1 = -sqrt((1 - (x1**2)/(a**2)) * b**2)
        # Append line segment connecting the current point to the next point on the upper half of the arc
        arc.append([[x + centre[0], y + centre[1]], [x1 + centre[0], y1 + centre[1]]])

    # Return the list of points representing the arc
    return arc


# This function is responsible for drawing the coordinate axes on the canvas. It creates lines representing 
# the x-axis and y-axis, arrowheads at the ends of each axis, and labels for the axes. The axes are drawn based 
# on the values of OX and OY, which represent the coordinates of the origin point.
# Function to draw the coordinate axes on the canvas
def draw_axes():
    # Draw vertical line representing the y-axis
    Can.create_line([OX, 0], [OX, can_h])
    # Draw horizontal line representing the x-axis
    Can.create_line([0, OY], [can_w, OY])
    # Draw arrowhead at the end of the y-axis
    Can.create_polygon([OX, can_h], [OX - 5, can_h - 10], [OX + 5, can_h - 10])
    # Draw arrowhead at the end of the x-axis
    Can.create_polygon([can_w, OY], [can_w - 10, OY - 5], [can_w - 10, OY + 5])
    # Label the y-axis
    Can.create_text(OX + 15, can_h - 10, text="Y", font=Font)
    # Label the x-axis
    Can.create_text(can_w - 10, OY - 15, text="X", font=Font)


# This function is responsible for moving all the figures on the canvas by the specified deltas (dx and dy) in the x and 
# y directions. It first attempts to convert the input deltas to float values. If successful, it appends a deep copy of 
# the last action stack to the action stack. Then, it iterates over each form, figure, and coordinate in the last action 
# stack, updating the x and y coordinates of each coordinate by adding the specified deltas. Finally, it rebuilds the 
# scene to reflect the changes made to the figures' positions. If the input cannot be converted to float, it displays an error message.
# Function to move all figures on the canvas by the specified deltas in the x and y directions
def move(dx, dy):
    try:
        # Convert input to float values
        dx = float(dx.get())
        dy = float(dy.get())
    except ValueError:
        # Show error message if input cannot be converted to float
        messagebox.showinfo("Attention", "Incorrect data!")
        # Return -1 to indicate failure
        return -1

    # Append a deep copy of the last action stack to the action stack\
    # ActionsStack[-1]: Accesses the last element in the ActionsStack list. This is typically the most recent state or 
    # configuration of some graphical objects or actions.
    # copy.deepcopy(): This function from the copy module creates a deep copy of the provided object. A deep copy 
    # creates a new compound object and then, recursively, inserts copies into it of the objects found in the original.
    # ActionsStack.append(): Adds the deep copy of the last element of ActionsStack to the ActionsStack list. This 
    # effectively saves a snapshot of the current state or configuration of graphical objects or actions into the ActionsStack,
    #  preserving the previous state.
    ActionsStack.append(copy.deepcopy(ActionsStack[-1]))
    
    # Iterate over each form in the last action stack
    for form in ActionsStack[-1]:
        # Iterate over each figure in the current form
        for figure in form:
            # Iterate over each coordinate in the current figure
            for coord in figure:
                # Update x and y coordinates of each coordinate by adding deltas
                coord[0] += dx
                coord[1] += dy

    # Rebuild the scene after moving all figures
    rebuild_scene()


# This function is responsible for rebuilding the scene on the canvas based on the current state variables HideVar and OverVar. 
# It first clears the canvas. Then, depending on the state of these variables, it either draws points only, draws axes and points, 
# or draws points and then axes. If hiding is enabled (HideVar.get() returns 1), it draws only the points. If overlay is disabled 
# (OverVar.get() returns 0), it draws axes first and then points. If overlay is enabled (OverVar.get() returns 1), it draws points first and then axes.
# Function to rebuild the scene on the canvas based on current state variables
def rebuild_scene():
    # Clear the canvas
    Can.delete("all")
    
    # Check if hiding is enabled
    # if HideVar.get() == 1:
    #     # Draw points if hiding is enabled
    #     draw_points(ActionsStack[-1])
    # Check if overlay is disabled
    if OverVar.get() == 0:
        # Draw axes and points if overlay is disabled
        draw_axes()
        draw_points(ActionsStack[-1])
    # Check if overlay is enabled
    elif OverVar.get() == 1:
        # Draw points and then axes if overlay is enabled
        draw_points(ActionsStack[-1])
        draw_axes()

# This function prints the contents of the ActionsStack in a formatted manner. It first prints a header indicating the start 
# of the stack printing. Then, for each set of points in the stack, it prints the index of the points and then iterates over
# the polygons, lines, ovals, and arcs within that set, printing each one individually. Finally, it prints a newline for 
# separation between different sets of points.
# Function to print the contents of the ActionsStack
# def print_stack():
#     # Print stack header
#     print("==========STACK==========")
#     # Print the length of the stack
#     print("Stack length: " + str(len(ActionsStack)))
    
#     # Iterate through each set of points in the stack
#     for points in range(len(ActionsStack)):
#         # Print the index of the points
#         print("Points №" + str(points))
        
#         # Print polygons
#         print("Polygons:")
#         for i in ActionsStack[points][0]:
#             print(i)
        
#         # Print lines
#         print("Lines:")
#         for i in ActionsStack[points][1]:
#             print(i)
        
#         # Print ovals
#         print("Ovals:")
#         for i in ActionsStack[points][2]:
#             print(i)
        
#         # Print arcs
#         print("Arcs:")
#         for i in ActionsStack[points][3]:
#             print(i)
        
#         # Print newline for separation
#         print()
    
#     # Print newline for separation
#     print()



# This function resets the scene by appending default points, obtained using the get_default_points function with the 
# specified origin (OX, OY), to the ActionsStack. Then, it rebuilds the scene using the rebuild_scene function.
# Function to reset the scene by appending default points to the ActionsStack and rebuilding the scene
def reset():
    # Append default points to the ActionsStack
    ActionsStack.append(get_default_points(OX, OY))
    
    # Rebuild the scene
    rebuild_scene()


# This function cancels the last action performed by removing the last element from the ActionsStack. If there is more than one element in the ActionsStack,
#  it rebuilds the scene using the rebuild_scene function.
# Function to cancel the last action by removing the last element from ActionsStack and rebuilding the scene
def cancel():
    # Check if there are more than one element in ActionsStack
    if len(ActionsStack) > 1:
        # Remove the last element from ActionsStack
        ActionsStack.pop(-1)
        
        # Rebuild the scene
        rebuild_scene()



# This function scales the scene by a given factor along the x and y axes with respect to a specified center
#  point (xc, yc). It updates the coordinates of all shapes in the scene accordingly and then rebuilds the 
# scene using the rebuild_scene function. If the input data is incorrect (not convertible to float), it shows
#  an info message box.
# Function to scale the scene by a given factor along the x and y axes with respect to a specified center
def scale(kx, ky, xc, yc):
    try:
        # Convert input values to float
        kx = float(kx.get())  # Get scaling factor along x-axis
        ky = float(ky.get())  # Get scaling factor along y-axis
        xc = float(xc.get())  # Get x-coordinate of the center point
        yc = float(yc.get())  # Get y-coordinate of the center point
    except ValueError:
        # Show an info message box if input data is incorrect
        messagebox.showinfo("Attention", "Incorrect data!")
        return -1

    # Append a deep copy of the last element in ActionsStack to maintain history
    ActionsStack.append(copy.deepcopy(ActionsStack[-1]))
    
    # Iterate over the elements in the last element of ActionsStack
    for form in ActionsStack[-1]:
        for figure in form:
            for coord in figure:
                # Scale each coordinate with respect to the specified center
                # (coord[0] - xc - OX): This subtracts the x-coordinate of the center point (xc) and the origin x-coordinate 
                # (OX) from the current x-coordinate of the point. This centers the point's x-coordinate around the specified center (xc, yc).
                # (coord[0] - xc - OX) * kx: This multiplies the centered x-coordinate by the scaling factor kx, effectively scaling the x-coordinate.
                # + xc + OX: Finally, this adds back the x-coordinate of the center point (xc) and the origin x-coordinate (OX). This re-centers
                #  the scaled x-coordinate around the center point.
                coord[0] = (coord[0] - xc - OX) * kx + xc + OX  # Scale x-coordinate
                coord[1] = (coord[1] - yc - OY) * ky + yc + OY  # Scale y-coordinate

    # Rebuild the scene with the updated coordinates
    rebuild_scene()


# This function rotates the scene by a specified angle around a given center point (xc, yc). It updates the coordinates 
# of all shapes in the scene accordingly using trigonometric functions to calculate the new coordinates after rotation. 
# If the input data is incorrect (not convertible to float), it shows an info message box. 
# Function to rotate the scene by a specified angle around a given center point (xc, yc)
def turn(xc, yc, angle):
    try:
        # Convert input values to float
        xc = float(xc.get())    # Get x-coordinate of the center point
        yc = float(yc.get())    # Get y-coordinate of the center point
        angle = float(angle.get())  # Get the rotation angle
    except ValueError:
        # Show an info message box if input data is incorrect
        messagebox.showinfo("Attention", "Incorrect data!")
        return -1

    # Append a deep copy of the last element in ActionsStack to maintain history
    ActionsStack.append(copy.deepcopy(ActionsStack[-1]))
    
    # Iterate over the elements in the last element of ActionsStack
    # form iterates over the elements (forms) in the first dimension of the list ActionsStack[-1].
    # Each form likely represents a collection of shapes or geometric elements.
    for form in ActionsStack[-1]:
        # figure iterates over the elements (figures) within each form.
        # Each figure likely represents a specific shape or geometric figure within the current form.
        for figure in form:
            # coord iterates over the elements (coordinates) within each figure.
            # Each coord likely represents a pair of (x, y) coordinates defining a point or vertex of the geometric 
            # figure represented by the current figure.
            for coord in figure:
                # Translate coordinates to the origin
                coord[0] -= OX
                coord[1] -= OY
                # Rotate the coordinates around the center point
                # New_x calculation
                # new_x: The x-coordinate of the rotated point is calculated using the formula for rotation about 
                # the origin. It involves adding the x-component of the vector from the center point to the original point 
                # multiplied by the cosine of the angle and the y-component of the same vector multiplied by the sine of the angle.
                new_x = xc + (coord[0] - xc) * d_cos(angle) + (coord[1] - yc) * d_sin(angle)
                # New_y calculation
                new_y = yc - (coord[0] - xc) * d_sin(angle) + (coord[1] - yc) * d_cos(angle)
                coord[0] = new_x
                coord[1] = new_y
                # Translate coordinates back to their original position
                coord[0] += OX
                coord[1] += OY

    # Rebuild the scene with the updated coordinates
    rebuild_scene()


# Cos of angle from rads to degrees
# Define a function to calculate the cosine of an angle in degrees
# Cosine (d_cos): This function takes an angle a in degrees, converts it to radians (since the trigonometric functions in 
# Python's math module work with radians), and then calculates the cosine of that angle.
# Formula: cos(a * pi / 180), where pi is the constant representing π (pi), and the angle is converted from degrees to 
# radians by multiplying it by π/180.
def d_cos(a):
    return cos(a * pi / 180)

# Define a function to calculate the sine of an angle in degrees
# Sine (d_sin): Similar to cosine, this function takes an angle a in degrees, converts it to radians, and then calculates the sine of that angle.
# Formula: sin(a * pi / 180), where pi is the constant representing π (pi), and the angle is converted from 
# degrees to radians by multiplying it by π/180.
def d_sin(a):
    return sin(a * pi / 180)



# Main window
root = Tk()  # Initialize the Tkinter root window
root.resizable(False, False)  # Set the root window to be non-resizable
can_h = 800  # Height of the canvas
can_w = 800  # Width of the canvas
but_w = 290  # Width of buttons (constant)

# Print the width of the screen
print(root.winfo_screenwidth())

# Set the geometry of the root window
root.geometry(str(can_w + but_w) + "x" + str(can_h))

# Set the title of the root window
root.title("Computer_Graphics-2")

# Define font style for labels and buttons
Font = "Arial 16"

# Width of the entry widgets
EntryW = 10

# Create a Canvas widget with specified height, width, and background color
Can = Canvas(root, height=can_h, width=can_w, bg='white')

# Define the origin coordinates for the canvas
OX = can_w / 2  # x-coordinate of the origin
OY = can_h / 2  # y-coordinate of the origin

# Initialize an empty list to store actions (e.g., transformations) on the canvas
ActionsStack = []

# Frames for organizing buttons
Buttons = Frame(root)  # Frame to hold all buttons
Move = Frame(Buttons)   # Frame for movement-related buttons
Scale = Frame(Buttons)  # Frame for scaling-related buttons
Turn = Frame(Buttons)   # Frame for rotation-related buttons
Settings = Frame(Buttons)  # Frame for settings-related buttons


# Move
# A StringVar object in Tkinter can help manage the value of a widget such as an Entry widget or a Label widget. 
MoveDxVar = StringVar()  # Variable to store the dx value for movement
MoveDyVar = StringVar()  # Variable to store the dy value for movement

# Label indicating movement operation
MoveName = Label(Move, text="Перенос:", font=Font).grid(row=0, column=0, columnspan=4)

# Labels for dx and dy values
MoveDx = Label(Move, text="dx:", font=Font).grid(row=1, column=0)
MoveDy = Label(Move, text="dy:", font=Font).grid(row=1, column=2)

# Entry widgets to input dx and dy values
MoveDxEntry = Entry(Move, width=EntryW, textvariable=MoveDxVar).grid(row=1, column=1)
MoveDyEntry = Entry(Move, width=EntryW, textvariable=MoveDyVar).grid(row=1, column=3)

# Button to execute movement operation
MoveButton = Button(Move, text="Выполнить", font=Font, command=lambda: move(MoveDxVar, MoveDyVar)).grid(row=2, column=1, columnspan=2)

# Grid placement for the Move frame within the root window
Move.grid(row=0, column=0)

# Scale
# Import necessary modules

# Variables to store scale factors and center coordinates
ScaleKxVar = StringVar()  # Variable for Kx (horizontal scale factor)
ScaleKyVar = StringVar()  # Variable for Ky (vertical scale factor)
ScaleXcVar = StringVar()  # Variable for Xc (x-coordinate of the center)
ScaleYcVar = StringVar()  # Variable for Yc (y-coordinate of the center)

# Label to indicate scaling operation
ScaleName = Label(Scale, text="Масштабирование:", font=Font).grid(row=0, column=0, columnspan=4)  # Creating label and placing it in the grid

# Labels for input fields
ScaleKx = Label(Scale, text="Kx:", font=Font).grid(row=1, column=0)  # Label for horizontal scale factor
ScaleKy = Label(Scale, text="Ky:", font=Font).grid(row=1, column=2)  # Label for vertical scale factor
ScaleXc = Label(Scale, text="Xc:", font=Font).grid(row=2, column=0)  # Label for x-coordinate of the center
ScaleYc = Label(Scale, text="Yc:", font=Font).grid(row=2, column=2)  # Label for y-coordinate of the center

# Entry fields for user input
ScaleKxEntry = Entry(Scale, width=EntryW, textvariable=ScaleKxVar).grid(row=1, column=1)  # Entry field for horizontal scale factor
ScaleKyEntry = Entry(Scale, width=EntryW, textvariable=ScaleKyVar).grid(row=1, column=3)  # Entry field for vertical scale factor
ScaleXcEntry = Entry(Scale, width=EntryW, textvariable=ScaleXcVar).grid(row=2, column=1)  # Entry field for x-coordinate of the center
ScaleYcEntry = Entry(Scale, width=EntryW, textvariable=ScaleYcVar).grid(row=2, column=3)  # Entry field for y-coordinate of the center

# Button to execute scaling operation
ScaleButton = Button(Scale, text="Выполнить", command=lambda: scale(ScaleKxVar, ScaleKyVar, ScaleXcVar, ScaleYcVar), font=Font).grid(row=3, column=1, columnspan=2)  # Creating button and placing it in the grid

# Place the Scale widget in the main window
Scale.grid(row=1, column=0)  # Placing the Scale widget in the grid

# In this section of code, StringVar variables are defined to store the Xc, Yc, and angle values for rotation.
#  Labels are created to indicate the rotation operation and to label the Xc, Yc, and angle entry fields. Entry 
# widgets are created to input the Xc, Yc, and angle values. A button is provided to execute the rotation operation.
#  Finally, the Turn frame is placed within the root window using the grid layout manager. Each line is commented to explain its purpose.
# Turn
TurnXcVar = StringVar()  # Variable to store the Xc value for rotation
TurnYcVar = StringVar()  # Variable to store the Yc value for rotation
TurnAngleVar = StringVar()  # Variable to store the angle value for rotation

# Label indicating rotation operation
TurnName = Label(Turn, text="Поворот:", font=Font).grid(row=0, column=0, columnspan=4)

# Labels for Xc, Yc, and angle values
TurnXc = Label(Turn, text="Xc:", font=Font).grid(row=1, column=0)
TurnYc = Label(Turn, text="Yc:", font=Font).grid(row=1, column=2)
TurnAngle = Label(Turn, text="Угол:", font=Font).grid(row=2, column=0)

# Entry widgets to input Xc, Yc, and angle values
TurnXcEntry = Entry(Turn, width=EntryW, textvariable=TurnXcVar).grid(row=1, column=1)
TurnYcEntry = Entry(Turn, width=EntryW, textvariable=TurnYcVar).grid(row=1, column=3)
TurnAngleEntry = Entry(Turn, width=EntryW, textvariable=TurnAngleVar).grid(row=2, column=1)

# Button to execute rotation operation
TurnButton = Button(Turn, text="Выполнить", command=lambda: turn(TurnXcVar, TurnYcVar, TurnAngleVar), font=Font).grid(row=3, column=1, columnspan=2)

# Grid placement for the Turn frame within the root window
Turn.grid(row=2, column=0)

# Settings
HideVar = IntVar()
OverVar = IntVar()

SettingsResetButton = Button(Settings, text="Восстановить", command=lambda: reset(), font=Font).grid(row=0, column=0, columnspan=2)
SettingsCancelButton = Button(Settings, text="Отменить", command=lambda: cancel(), font=Font).grid(row=1, column=0, columnspan=2)
# SettingsHide = Label(Settings, text="Скрыть оси:", font=Font).grid(row=2, column=0)
# SettingsOver = Label(Settings, text="Ось сверху:", font=Font).grid(row=3, column=0)h
# SettingsHideCheck = Checkbutton(Settings, variable=HideVar, command=lambda: hide_func(HideVar)).grid(row=2, column=1)
# SettingsOverCheck = Checkbutton(Settings, variable=OverVar, command=lambda: over_func(OverVar)).grid(row=3, column=1)

# Grid placement for the Settings frame within the root window
Settings.grid(row=3, column=0)

# Grid placement for the Can (Canvas) widget within the root window
Can.grid(row=0, column=0)

# Grid placement for the Buttons frame within the root window, with sticky option set to "nsew" for resizing
Buttons.grid(row=0, column=1, sticky="nsew")

# Configure row weights for the Buttons frame to allow resizing
Buttons.rowconfigure(0, weight=1)
Buttons.rowconfigure(1, weight=1)
Buttons.rowconfigure(2, weight=1)
Buttons.rowconfigure(3, weight=1)

# Configure column weight for the second column of the root window to allow resizing
root.columnconfigure(1, weight=1)

# Main program: Obtain default points, draw axes and points, and append initial points to ActionsStack
Points = get_default_points(OX, OY)
draw_axes()
draw_points(Points)
ActionsStack.append(Points)

# Start the main event loop
root.mainloop()
