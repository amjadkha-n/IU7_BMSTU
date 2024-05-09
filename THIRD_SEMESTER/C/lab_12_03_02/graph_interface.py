# Import necessary modules from the tkinter library
from tkinter import Entry, Label, Button, Tk, messagebox, END
from tkinter import ttk
import ctypes

# Specify the path to the shared library (C extension)
lib_path = './lib/libfunction.so'
# Load the shared library using ctypes
lib = ctypes.CDLL(lib_path)

# Define the function prototype for the C function
_add_num_after_even = lib.add_num_after_even
_add_num_after_even.argtypes = (ctypes.POINTER(ctypes.c_int), ctypes.c_int, ctypes.POINTER(ctypes.c_int), ctypes.c_int, ctypes.c_int)
_add_num_after_even.restype = ctypes.c_int

# Define a Python function that calls the C function
def add_num_after_even(arr, size_arr, size_res_arr, numb):
    # Convert input list to ctypes array
    arr_ctypes = (ctypes.c_int * size_arr)(*arr)

    # Initialize result array with zeros using a different method
    res_arr = (ctypes.c_int * max(size_res_arr, len(arr)))()

    # Call the C function
    numb_elem = _add_num_after_even(arr_ctypes, size_arr, res_arr, size_res_arr, numb)

    # Resize the result array if necessary
    if numb_elem > size_res_arr:
        res_arr = (ctypes.c_int * numb_elem)(*res_arr)
        _add_num_after_even(arr_ctypes, size_arr, res_arr, numb_elem, numb)

    # Convert the result array back to Python list
    result_list = list(res_arr)

    return result_list

# Define a function to handle the button click event
def add_number_to_array():
    try:
        # Get the specified number from the entry field
        numb = int(entry_field_3.get())
    except ValueError:
        # Display an error message if the input is not a valid number
        show_error_message("An error occurred when inserting a number into the array!")
        return

    # Get the array elements as a string from the entry field
    str_arr = entry_field_2.get()

    try:
        # Parse the input array string into a Python list of integers
        arr = parse_input_array(str_arr)
    except ValueError:
        # Display an error message if there are extraneous characters in the entered array
        show_error_message("There are extraneous characters in the entered array!")
        return

    # Call the add_num_after_even function and update the output field
    res_arr = add_num_after_even(arr, len(arr), len(arr), numb)
    update_output_field(res_arr)

# Define a function to display an error message dialog
def show_error_message(message):
    messagebox.showerror("Input error", message)

# Define a function to parse an input array string into a Python list of integers
def parse_input_array(input_str):
    return [int(i) for i in input_str.split()]

# Define a function to update the output field with the resulting array
def update_output_field(result_array):
    str_result = ' '.join(map(str, result_array))
    output_field_2.delete(0, END)
    output_field_2.insert(0, str_result)

# Define the main application class
class ArrayManipulatorApp:
    def __init__(self, master):
        # Initialize the main application window
        self.master = master
        self.master['bg'] = '#F5F5F5'
        self.master.title('Lab_12')
        self.master.geometry("400x430")

        # Configure the style for the ttk buttons
        self.style = ttk.Style()
        self.style.configure('TButton', font=('Helvetica', 12))

        # Create the GUI widgets
        self.create_widgets()

    def create_widgets(self):
        # Create and place labels, entry fields, and buttons in the main window
        txt_input_2 = Label(self.master, text='Enter the elements of array', bg='#F5F5F5', font=('Helvetica', 16))
        txt_input_2.place(x=20, y=170, width=360, height=30)

        self.entry_field_2 = Entry(self.master, width=35, font=('Helvetica', 16))
        self.entry_field_2.place(x=20, y=205, width=360, height=30)

        txt_input_3 = Label(self.master, text='Enter the number:', bg='#F5F5F5', font=('Helvetica', 16))
        txt_input_3.place(x=20, y=250, width=270, height=30)

        self.entry_field_3 = Entry(self.master, width=5, font=('Helvetica', 16))
        self.entry_field_3.place(x=300, y=250, width=70, height=30)

        btn_add_elem = Button(self.master, text='Add the specified number\nafter each even element',
                              font=('Helvetica', 14), command=self.add_number_to_array)
        btn_add_elem.place(x=20, y=290, width=360, height=45)

        txt_output = Label(self.master, text='The resulting array:', bg='#F5F5F5', font=('Helvetica', 16))
        txt_output.place(x=20, y=345, width=360, height=30)

        self.output_field_2 = Entry(self.master, width=5, font=('Helvetica', 16))
        self.output_field_2.place(x=20, y=375, width=360, height=30)

    # Define a method to handle button click events within the class
    def add_number_to_array(self):
        try:
            # Get the specified number from the entry field
            numb = int(self.entry_field_3.get())
        except ValueError:
            # Display an error message if the input is not a valid number
            self.show_error_message("An error occurred when inserting a number into the array!")
            return

        # Get the array elements as a string from the entry field
        str_arr = self.entry_field_2.get()

        try:
            # Parse the input array string into a Python list of integers
            arr = self.parse_input_array(str_arr)
        except ValueError:
            # Display an error message if there are extraneous characters in the entered array
            self.show_error_message("There are extraneous characters in the entered array!")
            return

        # Call the add_num_after_even function and update the output field
        res_arr = add_num_after_even(arr, len(arr), len(arr), numb)
        self.update_output_field(res_arr)

    # Define a method to show an error message dialog within the class
    def show_error_message(self, message):
        messagebox.showerror("Input error", message)

    # Define a method to parse an input array string into a Python list of integers within the class
    def parse_input_array(self, input_str):
        return [int(i) for i in input_str.split()]

    # Define a method to update the output field with the resulting array within the class
    def update_output_field(self, result_array):
        str_result = ' '.join(map(str, result_array))
        self.output_field_2.delete(0, END)
        self.output_field_2.insert(0, str_result)

# Define the main function to start the application
def main():
    root = Tk()
    app = ArrayManipulatorApp(root)
    root.mainloop()

# Check if the script is executed directly and not imported as a module
if __name__ == "__main__":
    main()

