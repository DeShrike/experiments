from configparser import ConfigParser
from os.path import dirname, join, expanduser

INSTALL_DIR = dirname(__file__)

config = ConfigParser()
config.read([
	join(INSTALL_DIR, "defaults.ini"),
	expanduser("~/.tool.ini"),
	"config.ini"
])

print(__file__)
print(INSTALL_DIR)
print(expanduser("~/.tool.ini"))

print(config.get("server", "host"))
print(config.getint("server","port"))
print(config.get("server","url"))


for sect in config.sections():
	print("Section:", sect)
	for k,v in config.items(sect):
		print(f" {k} = {v}")
	print()

config["server"]["loglevel"] = str(1)

with open("./test.ini", "w") as fpo:
	config.write(fpo)

