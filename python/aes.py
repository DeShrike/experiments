from Crypto.Cipher import AES

# key has to be 16, 24 or 32 bytes
key = "Sixteen byte key"

# plaintext has to be in multiple of 16 bytes
plaintext = "Secrets 16 bytes"

cipher = AES.new(key)

ciphertext = cipher.encrypt(plaintext)

print(plaintext)
print(len(plaintext))
print(ciphertext)
print(len(ciphertext))

decrypted = cipher.decrypt(ciphertext)

print(decrypted)
print(len(decrypted))
