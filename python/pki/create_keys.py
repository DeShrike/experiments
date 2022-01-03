import rsa
from cryptography.fernet import Fernet

# Create the symmetric key
key = Fernet.generate_key()

# Safe symmetric key
with open("symmetric.key", "wb") as fk:
	fk.write(key)

# Create public and private keys
(pubkey, privkey) = rsa.newkeys(2048)

# Safe public key
with open("publickey.pem", "wb") as fk:
	fk.write(pubkey.save_pkcs1('PEM'))

# Safe private key
with open("privatekey.pem", "wb") as fk:
	fk.write(privkey.save_pkcs1('PEM'))

