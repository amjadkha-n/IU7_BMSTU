# Sorting the given array with the help of insertion method
n = int(input("Please enter the length of the array: "))

arr = []
for i in range(n):
    arr.append(int(input(f"Please enter the {i + 1} element: ")))
for i in range(1, len(arr)):
    num = arr[i]
    j = i - 1
    while j >= 0 and num < arr[j]:
        arr[j + 1] = arr[j]
        j -= 1
    arr[j + 1] = num
print(f"sorted array = {arr}")
