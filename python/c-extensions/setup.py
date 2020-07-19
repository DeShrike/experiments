from distutils.core import setup, Extension

# Install the HelloC module
# Uaage:
#    sudo python3.8 setup.py build
#    sudo python3.8 setup.py install

module = Extension("HelloC", sources = ["helloc.c"])

setup(name = "HelloC",
      version = "1.1",
      description = "This module contains C extensions",
      ext_modules = [module] )


