from Crypto.Cipher import AES
import random
keybytes = [0] * 16
for k in range(14, 16):
    keybytes[k] = random.randint(0, 255)
keybytes[13] = random.randint(0, 15)
key = bytes(bytearray(keybytes))
cipher = AES.new(key, AES.MODE_ECB)
plaintext = "THIS IS JUST A TTHIS IS JUST A TTHIS IS JUST A T"
ciphertext = cipher.encrypt(plaintext)

f = open("aestext", "wb")
f.write(ciphertext)
f.close()
print(keybytes)
