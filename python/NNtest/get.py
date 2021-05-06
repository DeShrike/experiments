import requests as req
import time
import math

BRIGHTRED = u"\u001b[31;1m"
BRIGHTGREEN = u"\u001b[32;1m"
RESET = u"\u001b[0m"
INVERSE = u"\u001b[5m"

urls = [ "https://192.168.0.220:5001/Books",
         "https://192.168.0.220:5001/",
         "https://192.168.0.220:5001/Picture",
         "https://192.168.0.220:5001/Page1",
         "https://192.168.0.220:5001/Home/Privacy"]

totaltime = 0
requestcount = 0

def doreq(url):
    global totaltime, requestcount
    start = time.time()
    resp = req.get(url)
    end = time.time()
    ellapsed = end - start
    totaltime += ellapsed
    requestcount += 1
    print(f"{BRIGHTGREEN}{resp.status_code}{RESET} {BRIGHTRED}{ellapsed:.4}{RESET} {url}")

def main():
    for i in range(100):
        for url in urls:
            doreq(url)
    print("Average: %s%.5f%s seconds" % (BRIGHTRED, totaltime / requestcount, RESET))

if __name__ == "__main__":
    main()

