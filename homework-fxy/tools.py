def printMatrix(m):
    if not m:
        return
    for row in m:
        for x in row:
            print(x,end=' ')
        print('')

def getKey(src_dst):
    ret = []
    for xy in src_dst:
        ret.append("%d,%d"%(xy[0], xy[1]))
    return ret

#--------------------check the connection---------
def find(C, u):
    if C[u] != u:
        C[u] = find(C, C[u])
    return C[u]

def union(C, R, u, v):
    u, v = find(C, u), find(C, v)
    if R[u] > R[v]:
        C[v] = u
    else:
        C[u] = v
    if R[u] == R[v]:
        R[v] += 1

def isConnection(G, all_point):
    C, R = {u: u for u in all_point}, {u: 0 for u in all_point}

    for u, v_set in G.items():
        for v in v_set:
            union(C, R, u, v)
    start = all_point.pop()
    all_point.add(start)
    flag = find(C, start)
    for u in all_point:
        cur = find(C, u)
        if flag != cur:
            return False
    return True

def isEqual(mat1, mat2):
    '''
    m1, m2 是二维数组
    '''
    if not mat1 or not mat2:
        if mat1 == mat2:
            return True
        else:
            return False
    n1, m1 = len(mat1), len(mat1[0])
    n2, m2 = len(mat2), len(mat2[0])
    if n1 != n2 or m1 != m2:
        return False
    for i in range(n1):
        for j in range(m1):
            if mat1[i][j] != mat2[i][j]:
                return False
    return True

def check_nm(nm):
    #c = input("input m and n split by space : ")
    error, n, m = 0, None, None
    if nm:
        nm = nm.split(' ')
        if len(nm) != 2:
            error = 1
        else:
            n, m = nm

            try:
                nfloat = float(n)
                n = int(n)
                mfloat = float(m)
                m = int(m)
            except:
                error = 1

            if nfloat != n or mfloat != m:
                error = 1
            elif n * m <= 0:
                error = 2

        if error == 1:
            print("Invalid number format")
        elif error == 2:
            print("Number out of range")

        return error, n, m