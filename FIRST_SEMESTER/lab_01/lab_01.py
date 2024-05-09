# Amjad Faqirzai
# ИУ7И-16Б
# First lab
# finding height, Surface, volume and radii of described and inscribed spheres of Tetrahedron
import math as m

#a = float(input("Please enter the length of the edge a: "))
a = -4
if a < 0:
    print("Enter the positive numbers only")
    

Height = (a * m.sqrt(6)) / 3 # Height of the Tetrahedron

Surface = a * a * m.sqrt(3) # Surface of Tetrahedron

Volume = (a * a * a * m.sqrt(2)) / 12 # Volume of Tetrahedron

Radius_of_described_sphere = (a * m.sqrt(6)) / 4 # Radius of described sphere

Radius_of_inscribed_sphere = (a * m.sqrt(6)) / 12 # Radius of inscribed sphere


print(f"Height = {Height:.6g}")
print(f"Surface = {Surface:.6g}")
print(f"Volume = {Volume:.6g}")
print(f"Radius of the described speher = {Radius_of_described_sphere:.6g}")
print(f"Radius of the inscribed sphere = {Radius_of_inscribed_sphere:.6g}")
