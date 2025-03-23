import random
from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.primitives import padding
import binascii

def rand_hex(length):
    return ''.join(random.choice('0123456789abcdef') for i in range(length))

def rand_3char():
    return ''.join(random.choice('abcdefghijklmnopqrstuvwxyz') for i in range(3)).upper()

def format(hex_string):
    hex_pairs = [i for i in hex_string]
    form = "".join(f'\\x{hex(i)[2:]}' if len(hex(i)[2:]) == 2 else f'\\x0{hex(i)[2:]}' for i in hex_pairs)
    return form

def encrypt(pt, key, iv):
    try:
        cipher = Cipher(algorithms.AES(key), modes.CBC(iv), backend=default_backend())
        encryptor = cipher.encryptor()

        padder = padding.PKCS7(algorithms.AES.block_size).padder()
        padded_data = padder.update(pt.encode()) + padder.finalize()

        cipher_text = encryptor.update(padded_data) + encryptor.finalize()
        encoded = binascii.hexlify(cipher_text).decode('utf-8')

        return cipher_text 
    except Exception as e:
        print("Encryption error:", e)
        exit(1)

template = None
with open("template.cpp", "r") as f:
    template = f.read()

for i in range(1, 10+1):
    iv = rand_hex(15) 
    key = rand_hex(31)
    global_mem = rand_3char()
    flag = f'flag{{{rand_hex(16)}}}'
    enc_flag = encrypt(flag, key.encode().ljust(32, b'\x00'), iv.encode().ljust(16, b'\x00'))
    # print(enc_flag.hex())
    # print(f'{format(enc_flag)=}')
    # print(f'{enc_flag=}')
    print(f'Flag for challenge{i}: {flag}')


    with open(f"src/dll_{i}.cpp", "w") as f:
        stuff = template.replace("_IV", iv)
        stuff = stuff.replace("__KEY", key)
        stuff = stuff.replace("_FLAG", format(enc_flag))
        stuff = stuff.replace("_GLOBAL_MEM", global_mem)
        f.write(stuff)