import sys

def xor(a, b):
    #input: two byearrays
    #output: bytearray of their xor
    if len(a) > len(b):
        temp = a
        a = b
        b = temp
    s = []
    for i in range(0, len(a)):
        s.append(a[i] ^ b[i])
    for i in range(len(a), len(b)):
        s.append(b[i])
    return s

def cribpend(a, crib, loc):
    #crib is too small; append it with 0's depending on location
    s = []
    for i in range(0, loc):
        s.append(0)
    for i in range(0, len(crib)):
        s.append(crib[i])
    for i in range(len(crib) + loc, len(a)):
        s.append(0)
    s = s[:len(a)]
    return s

def bit(a):
    #returns bitstring of integer
    s = ""
    while (a != 0):
        if (a % 2 == 0):
            s += "0"
            a /= 2
        else:
            s += "1"
            a -= 1
            a /= 2
    while len(s) < 8:
        s += "0"
    s = s[::-1]
    return s

def s_to_ints(s):
    #convert string to integer list ("bytearray")
    b = []
    for i in range(0, len(s)):
        b.append(ord(s[i]))
    return b
    

def showbytes(a):
    s = ""
    chars = []
    for i in range(65, 91):
        chars.append(i)
    for i in range(97, 123):
        chars.append(i)
    for i in range(44, 47):
        chars.append(i)
    #return string of bytestring
    for i in range(0, len(a)):
        if (a[i] in chars):
            s += chr(a[i])
        elif (a[i] == 0):
            s += " "
        elif (a[i] == 32):
            s += "_"
        else:
            s += "*"
    return s

c1 = open('ctext0', 'rb')
c2 = open('ctext1', 'rb')
c1 = c1.read()
c2 = c2.read()
x = xor(c1, c2)

# word_bag = [bytearray(" the ", 'utf-8'), bytearray(". So ", 'utf-8'), bytearray("held", 'utf-8'), bytearray(" ambi", 'utf-8'),
# bytearray("text", 'utf-8'),  bytearray("ohre ", 'utf-8'), bytearray(" the e", 'utf-8'),
# bytearray(" that ", 'utf-8'), bytearray(". Sony ", 'utf-8'), bytearray(" from ", 'utf-8'), bytearray(" be ", 'utf-8')]

# for word in word_bag:
#     for element in range(0, len(x)):
#         if element + len(word) >= len(x):
#             break
#         print(element, end = '')
#         print(bytearray(xor(x[element: element + len(word)], word)))

attempt = bytearray(input("Try some inputs!"), 'utf-8')

for element in range(0, len(x)):
    if element + len(attempt) >= len(x):
        break
    print(element, end=' ')
    print(bytearray(xor(x[element: element + len(attempt)], attempt)))

attempe1 = "\
    000000000000000Sony 00000000000000000000\
    0000000000000000000000000000000000000000\
    0000000000000000000000000000000000000000\
    000000000000000000000000000 shar00000000\
    0000000000000000000000000000000000000000\
    00000000000000000000000 that000000000000\
    0000000000000000000 text0000000000000000\
    0000000000000000000000000000000000000000\
    0000000000000000000000000000000000000000\
    0000000000000000000000000000000000000000"

attempe2 = bytearray(attempe1, 'utf-8')
print(bytearray(xor(x, attempe2)))
