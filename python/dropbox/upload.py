from dotenv import load_dotenv
import os
import dropbox

# sudo pip3 install dropbox
# https://dropbox-sdk-python.readthedocs.io/en/latest/

load_dotenv()

TOKEN = os.environ.get("TOKEN")

f = open("test.txt", "rb")

dbx = dropbox.Dropbox(TOKEN)
dbx.files_upload(f.read(), "/test.txt")

f.close()

for entry in dbx.files_list_folder('').entries:
    print(entry.name)
