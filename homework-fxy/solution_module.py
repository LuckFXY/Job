from input_format import format_input
from tools import getKey, isConnection

def solution(n, m, input_str):

    error, src_dst_list, all_point = format_input(input_str, n, m)
    if error != 0:
        return False, None

    out_n, out_m = [i * 2 + 1 for i in [n, m]]
    imap = [['[W]'] * out_m for _ in range(out_n)]
    for i in range(1, out_n, 2):
        for j in range(1, out_m, 2):
            imap[i][j] = '[R]'

    if not input_str:
        return True, imap

    conn_map = dict()

    for src_dst in src_dst_list:

        row = getKey(src_dst)
        if row[0] not in conn_map:
            conn_map[row[0]] = set([row[1]])
        else:
            conn_map[row[0]].add(row[1])
        out_s, out_d = [[i * 2 + 1 for i in j] for j in src_dst]

        imap[out_s[0]][out_s[1]] = '[R]'
        imap[out_d[0]][out_d[1]] = '[R]'

        if out_s[0] == out_d[0]:
            # add horizontal path
            imap[out_s[0]][(out_s[1] + out_d[1]) >> 1] = '[R]'
        elif out_s[1] == out_d[1]:
            # add vertical path
            imap[(out_s[0] + out_d[0]) >> 1][out_s[1]] = '[R]'

    #print(conn_map)
    #printMatrix(imap)

    if not isConnection(conn_map, all_point):
        print("Maze format error")
        return (False, imap)
    return (True, imap)

#------------------------------test-----------------------------
# if __name__ == '__main__':
#     n, m = 4, 3
#     question, answer = generator_test(n, m)
#
#     print("question")
#     print(question)
#     print("answer")
#     printMatrix(answer)
#     print("output")
#     flag, my_answer = solution(n, m, question)
#     if flag:
#
#         if isEqual(my_answer,answer):
#             print('pass')
#         else:
#             print("unequal")
#             printMatrix(my_answer)
#     else:
#         print("None")


