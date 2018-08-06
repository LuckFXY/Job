def format_input(input_str, n, m):
    error = 0
    src_dst_list = []
    all_point = set()

    try:
        nfloat = float(n)
        n = int(n)
        mfloat = float(m)
        m = int(m)
    except:
        error = 1
        print("Invalid number format")
        return error, src_dst_list, all_point
    if nfloat != n or mfloat != m:
        error = 1
        print("Invalid number format")
        return error, src_dst_list, all_point
    if n * m <= 0:
        error = 2
        print("Number out of range")
        return error, src_dst_list, all_point

    for row in input_str.split(';'):
        row = row.split(' ')
        row_src_dst = []
        if len(row) != 2:
            error = 3
            break

        for val in row:
            all_point.add(val)
            src_dst = []
            val = val.split(',')
            if len(val) != 2:
                error = 3
                break
            for v in val:
                try:
                    v = int(v)
                except:
                    error = 1
                    break

                src_dst.append(int(v))
            if error != 0:
                break
            if src_dst[0] < 0 or src_dst[0] >= n:
                error = 2
                break
            if src_dst[1] < 0 or src_dst[1] >= m:
                error = 2
                break
            row_src_dst.append(src_dst)

        src_dst_list.append(row_src_dst)

        if error != 0:
            break

    if error == 1:
        print("Invalid number format")
    elif error == 2:
        print("Number out of range")
    elif error == 3:
        print("Incorrect command format")

    return error, src_dst_list, all_point

if __name__ == '__main__':
    s1 = '0,1 0,2;0,0 1,0;0,1 1,1;0,2 1,2;1,0 1,1;1,1 1,2;1,1 2,1;1,2 2,2;2,0 2,1'
    error, src_dst_list, all_point = format_input(s1, 3, 3)
    print(error)
    print(src_dst_list)
    print(all_point)