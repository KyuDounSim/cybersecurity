import re
import zlib

pdf = open("/Users/kdsim/Downloads/COMP3632/Project/project.pdf").read()
stream = re.compile(r'.*?FlateDecode.*?stream(.*?)endstream', re.S)
for s in stream.findall(pdf):
	s = s.strip(b'\r\n')
	try:
		print(zlib.decompress(s))
		print("")
	except:
		pass
