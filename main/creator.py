from PIL import Image
import numpy as np

f = open("output.txt","r")

lines = f.readlines()
sizes = lines[1].split(" ")

size = [int(sizes[0]),int(sizes[1][:-1])]

print(size)
img = np.zeros([size[0],size[1],3])
for n,i in enumerate(lines[3:]):
    val= i.split(" ")
    img[n%size[1],int(n/size[1])]=[int(i) for i in val]
print(img.shape)
image = Image.fromarray(img,"RBG")
image.show()

print(image.size)
