format = "Hello %s, it's %s today!"
values = ("world", "hot")
print (format % values)

from string import Template
temp = Template('this is a $x string')
print(temp.safe_substitute(x='magic'))

s = "Bill has a girl friend in Tianjin! Bill"
print(s.find("Tianjin"))
print(s.find("Bill"))
print(s.count("l"))
print(s.rfind("ll"))

s = "Bill"
if s.lower() in ["bill", "neil"] :print("found it!")

if s in ["bill", "neil"] :print("found it!")
else : print("Not found!")
