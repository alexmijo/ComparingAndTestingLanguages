
dict1 = {1:0, 2:0, 3:0}
dict2 = dict1
dict3 = dict1.copy()

dict1[1] += 1

print("dict1:", dict1)
print("dict2:", dict2)
print("dict3:", dict3)

dict1 = {1:3, 2:3, 3:3, 4:3}

print("dict1:", dict1)
print("dict2:", dict2)
print("dict3:", dict3)

# Conclusion: Aliasing/copying/reasigning works as expected