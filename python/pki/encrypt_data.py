import rsa
from cryptography.fernet import Fernet

# Read symmetric key
with open("symmetric.key", "rb") as fk:
	key = fk.read()

# Create the cipher
cipher = Fernet(key)

# Read the data to encrypt
with open("data.txt", "rb") as fi:
   data = fi.read()

# Encrypt the data
encrypted_data = cipher.encrypt(data)
with open("encrypted_data", "wb") as fo:
   fo.write(encrypted_data)

# Read public key
with open("publickey.pem", "rb") as fk:
	publickey = fk.read()

pubkey = rsa.PublicKey.load_pkcs1(publickey)

# Encrypt the symmetric key with the public key
encrypted_key = rsa.encrypt(key, pubkey)

# Save the encrypted symmetric key
with open("encrypted_key", "wb") as fo:
   fo.write(encrypted_key)


