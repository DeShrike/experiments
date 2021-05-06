import logging
import os, time
import shutil

# Initialization

log = logging.getLogger("spacemonitor")
log.setLevel(logging.INFO)

try:
    treshold = 10240 #int(os.getenv("TRESHOLD"))
    scaninterval = 60 # int(os.getenv("SCANINTERVAL"))
    outputfile = "/home/pi/spacemonitor/spacemonitor.log" #os.getenv("OUTPUTFILE")
except:
    logging.critical("ERROR: Have you exported all required environment variables? (TRESHOLD, OUTPUTFILE, SCANINTERVAL)")
    exit(1)

logging.basicConfig(filename = outputfile, filemode = 'a', format = '%(asctime)s - %(name)s - %(levelname)s - %(message)s')

def DoScan():
    global initial_used
    log.debug("Scanning")
    total, used, free = shutil.disk_usage("/")
    diff = used - initial_used
    # print(diff)
    if abs(diff) > treshold:
        msg = f"Total: {total} Used: {used} Free: {free} Difference: {diff}"
        log.info(msg)
        initial_used = used

def main():
    global initial_total, initial_used, initial_free
    initial_total, initial_used, initial_free = shutil.disk_usage("/")
    log.debug("main()")
    while True:
        time.sleep(scaninterval)
        DoScan()


if __name__ == "__main__":
    log.info("Starting")
    main()
