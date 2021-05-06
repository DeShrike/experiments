#!/usr/bin/python

import bluetooth
import time
import urllib2

print "In/Out Board"

while True:
    print "Checking " + time.strftime("%a, %d %b %Y %H:%M:%S", time.gmtime())

    result = bluetooth.lookup_name('XX:XX:XX:XX:XX:XX', timeout=5)
    if (result != None):
        print "Jeroen: in"
    else:
        print "Jeroen: out"
    print "Sleeping for 10"
    time.sleep(10)


