
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

def mutate_dict(dict, key, new_value):
    dict[key] = new_value
mutate_dict(dict1, 4, 0)

print("dict1 after mutate_dict(dict1, 4, 0):", dict1)

# Conclusion: Python is call by object reference value, like Java

for i in range(40):
    pass
print(i)

# Conclusion: loop variable persists as its last value

dict4 = {1:2, 2:3, 3:4}
dict5 = {1:2, 2:3, 3:3}
dict6 = dict4.copy()
dict5[3] += 1

print(dict4 == dict5)
print(dict4 == dict6)
print(dict5 == dict6)

# Conclusion: All true, so compares values

class Parent1:
    def __init__(self):
        print("Hi1")

class Parent2:
    def __init__(self, times):
        print("Hi2" * times)

class Parent3:
    pass

class Child1(Parent1):
    pass

class Child2(Parent2):
    pass

class OtherChild2(Parent2):
    def __init__(self):
        print("OtherHi2")

class Child3(Parent3):
    pass

Parent1()
Parent2(3)
Parent3()
Child1()
Child2(3)
OtherChild2()
# Doesn't work
# OtherChild2(2)
Child3()

# Conclusion: If a child has a constructor it overwrites their parents constructor, even if the
#  number of parameters are different.

def param_count():
    print("P")

def param_count(cols):
    print("P" * cols)

def param_count(cols, rows):
    for i in range(rows):
        print("P" * cols)

# Don't work
# param_count()
# param_count(2)
param_count(3, 3)

# Conclusion: Can't have two functions with the same name but a different number of parameters in
#  Python.