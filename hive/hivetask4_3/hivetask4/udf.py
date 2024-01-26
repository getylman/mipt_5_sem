import sys
for line in sys.stdin:
	try:
		size = int(line.strip())
	except ValueError as e:
		continue
	if size is not None:
		print(100 - size)
	else:
		print(NULL)