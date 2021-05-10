import re

a = "7: 14 5 | 1 21"

rx7 = re.compile(f"(?P<id>[0-9]*): (?P<a1>[0-9]*) (?P<a2>[0-9]*) \| (?P<b1>[0-9]*) (?P<b2>[0-9]*)( ?P<b3>[0-9]*)?")

match = rx7.match(a)
if match:
	print(match["id"])
	print(match["a1"])
	print(match["a2"])
	print(match["a3"])
	print(match["b1"])
	print(match["b2"])
	print(match["b3"])

