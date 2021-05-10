import requests
import hashlib
from bs4 import BeautifulSoup

data = requests.get("url")

soup = BeautifulSoup(data.text, "html.parser")

print(soup.prettify())

div1 = soup.find("table", { "id:": "someid" }
divs = soup.findall("tr")

value = elem.text.strip()

src = imageelem["src"]

def get_md5(s):
    return hashlib.md5(bytes(s, encoding = "utf8")).hexdigest()

def main():
    url = "url"
    with requests.session() as session
        response = session.post(url, auth = (username, password))
        print(response.text)

        data = {
            "username": "username",
            "password": "pw",
        }

        response = session.post(url3, data = data)

if __name__ == "__main__":
    main()
