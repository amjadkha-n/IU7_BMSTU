from tkinter import *
from tkinter import messagebox
import time
import matplotlib.pyplot as plt
import numpy as np
import colorutils as cu

from methods import *
from pixel import *

dis = 0

C_W = 900
C_H = 780
NUMBER_OF_RUNS = 15
MAX_RADIUS = 10000
STEP = 1000


def lib_ellipse(canvas, xc, yc, ra, rb, color):
    """
    Draw an ellipse on the canvas using a library function.

    Args:
        canvas: Canvas object to draw on.
        xc (int): X-coordinate of the center of the ellipse.
        yc (int): Y-coordinate of the center of the ellipse.
        ra (int): Radius of the ellipse along the x-axis.
        rb (int): Radius of the ellipse along the y-axis.
        color (Color): Color of the ellipse.

    Returns:
        None
    """
    # Draw the ellipse on the canvas.
    canvas.create_oval(xc - ra, yc - rb, xc + ra, yc + rb, outline=color.hex)

    if color == cu.Color((255, 255, 255)):
        # If the color is white, draw another ellipse to ensure visibility.
        canvas.create_oval(xc - ra, yc - rb, xc + ra, yc + rb, outline=color.hex)
def get_color(color_fg):
    """
    Get the corresponding color object based on the selected color index.

    Args:
        color_fg (IntVar): Integer variable representing the selected color index.

    Returns:
        Color: Color object corresponding to the selected color index.
    """
    col_fg = color_fg.get()  # Get the value of the selected color index.

    if col_fg == 0:  # Check if the color index is 0.
        color = cu.Color((255, 255, 255))  # Set color to white.
    elif col_fg == 1:  # Check if the color index is 1.
        color = cu.Color((0, 0, 0))  # Set color to black.
    elif col_fg == 2:  # Check if the color index is 2.
        color = cu.Color((255, 0, 0))  # Set color to red.
    elif col_fg == 3:  # Check if the color index is 3.
        color = cu.Color((0, 0, 255))  # Set color to blue.
    else:  # If the color index is none of the above.
        color = cu.Color((0, 255, 0))  # Set color to green.

    return color  # Return the selected color object.


def draw_figure(
    canvas, color_fg, algorithm, figure, xc_entry, yc_entry, ra_entry, rb_entry
):
    """
    Draw a figure on the canvas based on the provided parameters.

    Args:
        canvas: The canvas object where the figure will be drawn.
        color_fg: The selected color for the figure.
        algorithm: The selected algorithm for drawing the figure.
        figure: The type of figure to draw.
        xc_entry: The entry widget for the x-coordinate of the center.
        yc_entry: The entry widget for the y-coordinate of the center.
        ra_entry: The entry widget for the major axis (radius for circles).
        rb_entry: The entry widget for the minor axis (only for ellipses).
    """
    ellipse = figure.get()  # Get the selected figure type.

    try:
        xc = int(xc_entry.get())  # Get the x-coordinate of the center.
        yc = int(yc_entry.get())  # Get the y-coordinate of the center.
        ra = int(ra_entry.get())  # Get the major axis (radius for circles).

        if ellipse == True:  # Check if the figure is an ellipse.
            rb = int(rb_entry.get())  # Get the minor axis.
    except:
        # Show a warning message if input parameters are invalid.
        messagebox.showwarning(
            "Ошибка", "Неверно заданны параметры фигуры!\n" "Ожидался ввод целых чисел."
        )
        return

    # Check if major and minor axes are valid.
    if ra <= 0 or (ellipse and rb <= 0):
        messagebox.showwarning(
            "Ошибка", "Значения полуосей фигуры должны быть больше 0."
        )
        return

    color = get_color(color_fg)  # Get the color for drawing.
    alg = algorithm.get()  # Get the selected drawing algorithm.

    if ellipse:  # If the selected figure is an ellipse.
        if alg == 0:  # Use canonical ellipse algorithm.
            canonical_ellipse(xc, yc, ra, rb, color, canvas, draw=TRUE)
        elif alg == 1:  # Use parameter ellipse algorithm.
            parameter_ellipse(xc, yc, ra, rb, color, canvas, draw=TRUE)
        elif alg == 2:  # Use Bresenham ellipse algorithm.
            bresenham_ellipse(xc, yc, ra, rb, color, canvas, draw=TRUE)
        elif alg == 3:  # Use midpoint ellipse algorithm.
            midpoint_ellipse(xc, yc, ra, rb, color, canvas, draw=TRUE)
        else:  # Use library ellipse function.
            lib_ellipse(canvas, xc, yc, ra, rb, color)
    else:  # If the selected figure is a circle.
        color = get_color(color_fg)  # Get the color for drawing.
        alg = algorithm.get()  # Get the selected drawing algorithm.

        if alg == 0:  # Use canonical circle algorithm.
            canonical_circle(xc, yc, ra, color, canvas, draw=TRUE)
        elif alg == 1:  # Use parameter circle algorithm.
            parameter_circle(xc, yc, ra, color, canvas, draw=TRUE)
        elif alg == 2:  # Use Bresenham circle algorithm.
            bresenham_circle(xc, yc, ra, color, canvas, draw=TRUE)
        elif alg == 3:  # Use midpoint circle algorithm.
            midpoint_circle(xc, yc, ra, color, canvas, draw=TRUE)
        else:  # Use library ellipse function with equal major and minor axes.
            lib_ellipse(canvas, xc, yc, ra, ra, color)
    return
def draw_spectrum_ellipse(canvas, color_fg, algorithm, xc, yc):
    """
    Draw a spectrum of ellipses on the canvas.

    Args:
        canvas: The canvas object where the ellipses will be drawn.
        color_fg: The selected color for the ellipses.
        algorithm: The selected algorithm for drawing the ellipses.
        xc: The x-coordinate of the center for all ellipses.
        yc: The y-coordinate of the center for all ellipses.
    """
    radius_x_entry = ent9  # Get the entry widget for the major axis.
    radius_y_entry = ent10  # Get the entry widget for the minor axis.
    st_entr = ent7  # Get the entry widget for the step size.
    count_figure_entry = ent8  # Get the entry widget for the number of ellipses.

    ra = int(radius_x_entry.get())  # Get the initial major axis value.
    rb = int(radius_y_entry.get())  # Get the initial minor axis value.
    step = int(st_entr.get())  # Get the step size for changing the major axis.
    count_fig = int(count_figure_entry.get())  # Get the number of ellipses to draw.

    constant = ra / rb  # Calculate the constant ratio of major to minor axis.

    while count_fig > 0:
        color = get_color(color_fg)  # Get the color for drawing the ellipse.
        alg = algorithm.get()  # Get the selected drawing algorithm.

        # Draw the ellipse based on the selected algorithm.
        if alg == 0:
            canonical_ellipse(xc, yc, ra, rb, color, canvas, draw=True)
        elif alg == 1:
            parameter_ellipse(xc, yc, ra, rb, color, canvas, draw=True)
        elif alg == 2:
            bresenham_ellipse(xc, yc, ra, rb, color, canvas, draw=True)
        elif alg == 3:
            midpoint_ellipse(xc, yc, ra, rb, color, canvas, draw=True)
        else:
            lib_ellipse(canvas, xc, yc, ra, rb, color)

        # Increment the major axis and calculate the new minor axis based on the constant ratio.
        ra += step
        rb = round(ra / constant)

        count_fig -= 1  # Decrement the count of ellipses to draw.


def get_necessary_data_for_spectrum(r_beg, r_end, step, count_fig):
    """
    Calculate necessary data for drawing a spectrum of shapes.

    This function calculates the starting radius, step size, and number of shapes
    based on the given parameters.

    Args:
        r_beg: The starting radius.
        r_end: The ending radius.
        step: The step size for changing the radius.
        count_fig: The number of shapes to draw.

    Returns:
        Tuple: A tuple containing the starting radius, step size, and number of shapes.
    """
    if r_beg == 0:
        r_beg = r_end - (count_fig - 1) * step  # Calculate starting radius if not provided.
    elif step == 0:
        if count_fig == 0:
            step = int(r_end - r_beg) + 1  # Calculate step size if not provided.
        else:
            step = int((r_end - r_beg) / (count_fig - 1))  # Calculate step size based on count of figures.
    elif count_fig == 0:
        count_fig = int((r_end - r_beg) / step) + 1  # Calculate count of figures if not provided.

    return r_beg, step, count_fig  # Return calculated data.


def draw_spectrum_circle(canvas, color_fg, algorithm, xc, yc):
    """
    Draw a spectrum of circles on the canvas.

    This function draws a spectrum of circles on the canvas based on the given parameters.

    Args:
        canvas: The canvas to draw on.
        color_fg: The foreground color of the circles.
        algorithm: The algorithm to use for drawing circles.
        xc: The x-coordinate of the center of the circles.
        yc: The y-coordinate of the center of the circles.

    Returns:
        None
    """
    global dis  # Global variable indicating if the count_figure_entry is disabled
    beg_radius_entry = ent5  # Entry widget for the beginning radius of the circles
    end_radius_entry = ent6  # Entry widget for the ending radius of the circles
    step_entry = ent7  # Entry widget for the step size between consecutive circles
    count_figure_entry = ent8  # Entry widget for the number of circles to draw

    r_beg, r_end, step, count_fig = 0, 0, 0, 0  # Initialize variables

    # Retrieve the values from entry widgets and convert them to integers
    r_beg = int(beg_radius_entry.get())
    r_end = int(end_radius_entry.get())
    step = int(step_entry.get())
    count_fig = 0

    # Check if count_figure_entry is enabled (dis == 0) and retrieve its value
    if dis == 0:
        count_fig = int(count_figure_entry.get())

    # Calculate necessary data for drawing the spectrum of circles
    r, step, count_fig = get_necessary_data_for_spectrum(r_beg, r_end, step, count_fig)

    # Draw the spectrum of circles
    while count_fig > 0:
        color = get_color(color_fg)  # Get the color for the circle
        alg = algorithm.get()  # Get the selected algorithm for drawing circles

        # Select the appropriate algorithm and draw the circle
        if alg == 0:
            canonical_circle(xc, yc, r, color, canvas, draw=True)
        elif alg == 1:
            parameter_circle(xc, yc, r, color, canvas, draw=True)
        elif alg == 2:
            bresenham_circle(xc, yc, r, color, canvas, draw=True)
        elif alg == 3:
            midpoint_circle(xc, yc, r, color, canvas, draw=True)
        else:
            lib_ellipse(canvas, xc, yc, r, r, color)

        # Update the radius for the next circle and decrease the count
        r += step
        count_fig -= 1


def draw_spectrum(canvas, color_fg, algorithm, figure, xc_entry, yc_entry):
    """
    Draw a spectrum of shapes (either ellipses or circles) on the canvas.

    This function draws a spectrum of shapes (either ellipses or circles) on the canvas based on the given parameters.

    Args:
        canvas: The canvas to draw on.
        color_fg: The foreground color of the shapes.
        algorithm: The algorithm to use for drawing shapes.
        figure: The type of shape to draw (0 for circle, 1 for ellipse).
        xc_entry: The entry widget for the x-coordinate of the center of the shapes.
        yc_entry: The entry widget for the y-coordinate of the center of the shapes.

    Returns:
        None
    """
    try:
        xc = int(xc_entry.get())  # Get the x-coordinate of the center of the shapes
        yc = int(yc_entry.get())  # Get the y-coordinate of the center of the shapes
    except:
        # Show a warning message if the coordinates are incorrectly specified
        messagebox.showwarning(
            "Ошибка",
            "Неверно заданны координаты центра фигуры!\n" "Ожидался ввод целых чисел.",
        )
        return

    # Determine whether to draw ellipses or circles based on the value of 'figure'
    if figure.get() == 1:
        draw_spectrum_ellipse(canvas, color_fg, algorithm, xc, yc)  # Draw ellipses
    else:
        draw_spectrum_circle(canvas, color_fg, algorithm, xc, yc)  # Draw circles

def time_comparison(canvas, color_fg, algorithm, figure):
    """
    Perform time comparison of different algorithms for drawing shapes and plot the results.

    This function measures the time taken by different algorithms to draw shapes and plots the results on a graph.

    Args:
        canvas: The canvas to draw on.
        color_fg: The foreground color of the shapes.
        algorithm: The algorithm to use for drawing shapes.
        figure: The type of shape to draw (0 for circle, 1 for ellipse).

    Returns:
        None
    """
    time_list = []  # List to store the time measurements

    xc = C_W // 2  # Calculate the x-coordinate of the center of the canvas
    yc = C_H // 2  # Calculate the y-coordinate of the center of the canvas

    ellipse = figure.get()  # Get the type of shape to draw
    old_algorithm = algorithm.get()  # Get the current algorithm selected

    for i in range(5):  # Repeat the process for 5 iterations
        algorithm.set(i)  # Set the algorithm for the current iteration

        # Lists to store start and end times for each radius
        time_start = [0] * (MAX_RADIUS // STEP)
        time_end = [0] * (MAX_RADIUS // STEP)

        for _ in range(NUMBER_OF_RUNS):  # Repeat the drawing process for the specified number of runs
            ra = STEP  # Initialize the major radius with the step size
            rb = STEP  # Initialize the minor radius with the step size

            for j in range(MAX_RADIUS // STEP):  # Iterate over different radius values
                if ellipse:  # If drawing an ellipse
                    time_start[j] += time.time()  # Record the start time
                    color = get_color(color_fg)  # Get the color for the shape
                    alg = algorithm.get()  # Get the current algorithm selected
                    if alg == 0:
                        canonical_ellipse(xc, yc, ra, rb, color, canvas, draw=FALSE)
                    elif alg == 1:
                        parameter_ellipse(xc, yc, ra, rb, color, canvas, draw=FALSE)
                    elif alg == 2:
                        bresenham_ellipse(xc, yc, ra, rb, color, canvas, draw=FALSE)
                    elif alg == 3:
                        midpoint_ellipse(xc, yc, ra, rb, color, canvas, draw=FALSE)
                    else:
                        lib_ellipse(canvas, xc, yc, ra, rb, color)
                    time_end[j] += time.time()  # Record the end time
                    rb += STEP  # Increment the minor radius
                else:  # If drawing a circle
                    time_start[j] += time.time()  # Record the start time
                    color = get_color(color_fg)  # Get the color for the shape
                    alg = algorithm.get()  # Get the current algorithm selected
                    if alg == 0:
                        canonical_circle(xc, yc, ra, color, canvas, draw=FALSE)
                    elif alg == 1:
                        parameter_circle(xc, yc, ra, color, canvas, draw=FALSE)
                    elif alg == 2:
                        bresenham_circle(xc, yc, ra, color, canvas, draw=FALSE)
                    elif alg == 3:
                        midpoint_circle(xc, yc, ra, color, canvas, draw=FALSE)
                    else:
                        lib_ellipse(canvas, xc, yc, ra, ra, color)
                    time_end[j] += time.time()  # Record the end time
                ra += STEP  # Increment the major radius

            clear_canvas(canvas)  # Clear the canvas after drawing the shape

        # Calculate the average time for each radius and append to the time list
        size = len(time_start)
        time_list.append(
            [(time_end[i] - time_start[i]) / NUMBER_OF_RUNS for i in range(size)]
        )

    algorithm.set(old_algorithm)  # Restore the original algorithm
    radius_arr = [i for i in range(STEP, MAX_RADIUS + STEP, STEP)]  # Generate the list of radii

    # Plot the time measurements for different algorithms
    plt.figure(figsize=(10, 6))
    plt.rcParams["font.size"] = "12"
    plt.title("Замеры времени для построения фигуры различными методами")

    plt.plot(radius_arr, time_list[0], label="Каноническое уравнение")
    plt.plot(radius_arr, time_list[1], label="Параметрическое уравнение")
    plt.plot(radius_arr, time_list[2], label="Алгоритм Брезенхема")
    plt.plot(radius_arr, time_list[3], label="Алгоритм средней точки")
    plt.plot(radius_arr, time_list[4], label="Библиотечная функция")

    plt.xticks(np.arange(STEP, MAX_RADIUS + STEP, STEP))  # Set x-axis ticks
    plt.legend()  # Display legend
    plt.xlabel("Длина радиуса")  # Set x-axis label
    plt.ylabel("Время")  # Set y-axis label

    plt.show()  # Display the plot

def clear_canvas(canvas):
    canvas.delete("all")


def check_buttons(t, tn):
    """
    Show or hide UI elements based on the selected shape type.

    This function adjusts the visibility and position of UI elements based on the selected shape type.

    Args:
        t: The type of shape (0 for circle, 1 for ellipse).
        tn: The type of algorithm (0 for canonical, 1 for parameter, 2 for Bresenham, 3 for midpoint, 4 for library).

    Returns:
        None
    """
    if t == 0:  # If the selected shape is a circle
        label14.place_forget()  # Hide label14
        label15.place_forget()  # Hide label15
        label9.place(x=30, y=535)  # Place label9
        label10.place(x=90, y=535)  # Place label10
        label13.place(x=105, y=585)  # Place label13

        radbutton13.place(x=20, y=605)  # Place radbutton13
        radbutton14.place(x=80, y=605)  # Place radbutton14
        radbutton15.place(x=140, y=605)  # Place radbutton15
        radbutton16.place(x=200, y=605)  # Place radbutton16

        ent9.place_forget()  # Hide ent9
        ent10.place_forget()  # Hide ent10
        ent5.place(x=15, y=555, width=50, height=25)  # Place ent5
        ent6.place(x=80, y=555, width=50, height=25)  # Place ent6

        check_hiding(tn)  # Call check_hiding function with argument tn
    elif t == 1:  # If the selected shape is an ellipse
        label9.place_forget()  # Hide label9
        label10.place_forget()  # Hide label10
        label13.place_forget()  # Hide label13
        label14.place(x=30, y=535)  # Place label14
        label15.place(x=90, y=535)  # Place label15

        radbutton13.place_forget()  # Hide radbutton13
        radbutton14.place_forget()  # Hide radbutton14
        radbutton15.place_forget()  # Hide radbutton15
        radbutton16.place_forget()  # Hide radbutton16

        ent5.place_forget()  # Hide ent5
        ent6.place_forget()  # Hide ent6
        ent9.place(x=15, y=555, width=50, height=25)  # Place ent9
        ent10.place(x=80, y=555, width=50, height=25)  # Place ent10

        ent7.configure(state=NORMAL)  # Enable ent7
        ent8.configure(state=NORMAL)  # Enable ent8


def check_hiding(t):
    """
    Enable or disable certain UI elements based on the selected algorithm type.

    This function adjusts the state of UI elements based on the selected algorithm type.

    Args:
        t: The type of algorithm (0 for canonical, 1 for parameter, 2 for Bresenham, 3 for midpoint).

    Returns:
        None
    """
    global dis
    ent5.configure(state=NORMAL)  # Enable ent5
    ent6.configure(state=NORMAL)  # Enable ent6
    ent7.configure(state=NORMAL)  # Enable ent7
    ent8.configure(state=NORMAL)  # Enable ent8

    if t == 0:
        ent5.configure(state=DISABLED)  # Disable ent5
        dis = 0
    elif t == 1:
        ent6.configure(state=DISABLED)  # Disable ent6
        dis = 0
    elif t == 2:
        ent7.configure(state=DISABLED)  # Disable ent7
        dis = 0
    elif t == 3:
        ent8.configure(state=DISABLED)  # Disable ent8
        dis = 1

window = Tk()
window.title("lab_04")
window.geometry("1200x780")
window["bg"] = "pink"

c = Canvas(window, width=C_W, height=C_H, bg="white")
c.place(x=300, y=0)

color_fg = IntVar()
color_fg.set(2)

alg = IntVar()
alg.set(0)

t = IntVar()
t.set(0)

hide = IntVar()
hide.set(0)

label1 = Label(
    window,
    text="Выбор цвета",
    height="4",
    bg="pink",
    fg="black",
    font=("arial", 14),
)
label1.place(x=95, y=150)

label2 = Label(
    window,
    text="Выбор алгоритма",
    height="3",
    bg="pink",
    fg="black",
    font=("arial", 14),
)
label2.place(x=75, y=-25)

label3 = Label(
    window,
    text="Построение фигуры",
    height="1",
    bg="pink",
    fg="black",
    font=("arial", 14),
)
label3.place(x=65, y=350)

label4 = Label(window, text="Xc", height="1", bg="pink", fg="black")
label4.place(x=30, y=405)

label5 = Label(window, text="Yc", height="1", bg="pink", fg="black")
label5.place(x=90, y=405)

label6 = Label(window, text="Rx", height="1", bg="pink", fg="black")
label6.place(x=160, y=405)

label7 = Label(window, text="Ry", height="1", bg="pink", fg="black")
label7.place(x=225, y=405)

label8 = Label(
    window,
    text="Построение спектра",
    height="1",
    bg="pink",
    font=("arial", 14),
    fg="black",
)
label8.place(x=65, y=510)

label9 = Label(window, text="Rb", height="1", bg="pink", fg="black")

label10 = Label(window, text="Re", height="1", bg="pink", fg="black")

label11 = Label(window, text="Шаг", height="1", bg="pink", fg="black")
label11.place(x=160, y=535)

label12 = Label(window, text="Кол-во", height="1", bg="pink", fg="black")
label12.place(x=210, y=535)

label13 = Label(window, text="Скрыть", height="1", bg="pink", fg="black")

label14 = Label(window, text="Ra", height="1", bg="pink", fg="black")

label15 = Label(window, text="Rb", height="1", bg="pink", fg="black")

radbutton1 = Radiobutton(
    window,
    text="Фоновый",
    variable=color_fg,
    value=0,
    height="1",
    bg="pink",
    fg="black",
)
radbutton1.place(x=20, y=200)

radbutton2 = Radiobutton(
    window,
    text="Чёрный",
    variable=color_fg,
    value=1,
    height="1",
    bg="pink",
    fg="black",
)
radbutton2.place(x=20, y=230)

radbutton3 = Radiobutton(
    window,
    text="Красный",
    variable=color_fg,
    value=2,
    height="1",
    bg="pink",
    fg="black",
)
radbutton3.place(x=20, y=260)

radbutton4 = Radiobutton(
    window,
    text="Синий",
    variable=color_fg,
    value=3,
    height="1",
    bg="pink",
    fg="black",
)
radbutton4.place(x=20, y=290)

radbutton5 = Radiobutton(
    window,
    text="Зелёный",
    variable=color_fg,
    value=4,
    height="1",
    bg="pink",
    fg="black",
)
radbutton5.place(x=20, y=320)

radbutton6 = Radiobutton(
    window,
    text="Каноническое уравнение",
    variable=alg,
    value=0,
    height="2",
    bg="pink",
    fg="black",
)
radbutton6.place(x=20, y=20)

radbutton7 = Radiobutton(
    window,
    text="Параметрическое уравнение",
    variable=alg,
    value=1,
    height="2",
    bg="pink",
    fg="black",
)
radbutton7.place(x=20, y=50)

radbutton8 = Radiobutton(
    window,
    text="Алгоритм Брезенхема",
    variable=alg,
    value=2,
    height="2",
    bg="pink",
    fg="black",
)
radbutton8.place(x=20, y=80)

radbutton9 = Radiobutton(
    window,
    text="Алгоритм средней точки",
    variable=alg,
    value=3,
    height="2",
    bg="pink",
    fg="black",
)
radbutton9.place(x=20, y=110)

radbutton10 = Radiobutton(
    window,
    text="Библиотечная функция",
    variable=alg,
    value=4,
    height="2",
    bg="pink",
    fg="black",
)
radbutton10.place(x=20, y=141)

radbutton11 = Radiobutton(
    window,
    text="Окружность",
    variable=t,
    value=0,
    height="2",
    bg="pink",
    fg="black",
    command=lambda: check_buttons(t.get(), hide.get()),
)
radbutton11.place(x=20, y=370)

radbutton12 = Radiobutton(
    window,
    text="Эллипс",
    variable=t,
    value=1,
    height="2",
    bg="pink",
    fg="black",
    command=lambda: check_buttons(t.get(), hide.get()),
)
radbutton12.place(x=150, y=370)

radbutton13 = Radiobutton(
    window,
    text="Rb",
    variable=hide,
    value=0,
    height="1",
    bg="pink",
    fg="black",
    command=lambda: check_hiding(hide.get()),
)

radbutton14 = Radiobutton(
    window,
    text="Re",
    variable=hide,
    value=1,
    height="1",
    bg="pink",
    fg="black",
    command=lambda: check_hiding(hide.get()),
)

radbutton15 = Radiobutton(
    window,
    text="Шаг",
    variable=hide,
    value=2,
    height="1",
    bg="pink",
    fg="black",
    command=lambda: check_hiding(hide.get()),
)

radbutton16 = Radiobutton(
    window,
    text="Кол-во",
    variable=hide,
    value=3,
    height="1",
    bg="pink",
    fg="black",
    command=lambda: check_hiding(hide.get()),
)

ent1 = Entry(window, bg="white", fg="black")
ent1.place(x=15, y=425, width=50, height=25)
ent1.insert(0, 450)

ent2 = Entry(window, bg="white", fg="black")
ent2.place(x=80, y=425, width=50, height=25)
ent2.insert(0, 390)

ent3 = Entry(window, bg="white", fg="black")
ent3.place(x=150, y=425, width=50, height=25)
ent3.insert(0, 200)

ent4 = Entry(window, bg="white", fg="black")
ent4.place(x=215, y=425, width=50, height=25)
ent4.insert(0, 150)

ent5 = Entry(window, bg="white", fg="black")
ent5.insert(0, 100)

ent6 = Entry(window, bg="white", fg="black")
ent6.insert(0, 340)

ent7 = Entry(window, bg="white", fg="black")
ent7.place(x=150, y=555, width=50, height=25)
ent7.insert(0, 10)

ent8 = Entry(window, bg="white", fg="black")
ent8.place(x=215, y=555, width=50, height=25)
ent8.insert(0, 20)

ent9 = Entry(window, bg="white", fg="black")
ent9.insert(0, 150)

ent10 = Entry(window, bg="white", fg="black")
ent10.insert(0, 100)

butn1 = Button(
    text="Построить фигуру",
    fg="black",
    command=lambda: draw_figure(c, color_fg, alg, t, ent1, ent2, ent3, ent4),
)
butn1.place(x=15, y=460, width=250, height=40)

butn2 = Button(
    text="Построить спектр",
    fg="black",
    command=lambda: draw_spectrum(c, color_fg, alg, t, ent1, ent2),
)
butn2.place(x=15, y=635, width=250, height=40)

butn3 = Button(
    text="Сравнить время",
    fg="black",
    command=lambda: time_comparison(c, color_fg, alg, t),
)
butn3.place(x=15, y=685, width=250, height=35)

butn4 = Button(text="Очистить поле", fg="black", command=lambda: clear_canvas(c))
butn4.place(x=15, y=730, width=250, height=35)

check_hiding(0)
check_buttons(0, hide)
ent5.configure(state=DISABLED)

window.mainloop()
