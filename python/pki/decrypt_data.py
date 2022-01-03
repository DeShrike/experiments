import rsa
from cryptography.fernet import Fernet

# Read private key
with open("privatekey.pem", "rb") as fk:
	privatekey = fk.read()

privkey = rsa.PrivateKey.load_pkcs1(privatekey)

# Read encrypted symmetric key
with open("encrypted_key", "rb") as fk:
	encrypted_key = fk.read()

decrypted_key = rsa.decrypt(encrypted_key, privkey)

# Create the cipher
cipher = Fernet(decrypted_key)

# Read the data to encrypt
with open("encrypted_data", "rb") as fi:
   encrypted_data = fi.read()

# Decrypt the data
decrypted_data = cipher.decrypt(encrypted_data)

print(decrypted_data)


