raw = input("input the origin data [[...]] : ")
raw = raw.strip()[2:-2].split('],[')
output = []
for row in raw:
    output.append("{"+row+"}")
length = len(raw);
output = "{" + ','.join(output) + "}"
print("line num = %d"%(length))
print(output)
        
    

