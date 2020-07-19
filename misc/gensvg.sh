#!/bin/bash

# See http://potrace.sourceforge.net/

# Install:
# sudo apt install potrace

# Run:

echo "Converting android-chrome-512x512.bmp"
echo "Should be a 512 by 512 bitmap"

# foylo version:
potrace android-chrome-512x512.bmp --svg --output safari-pinned-tab.svg
#  -- color \#E30713

echo "Output in safari-pinned-tab.svg"




