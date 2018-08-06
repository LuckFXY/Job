import random
from tools import printMatrix, check_nm, isEqual
from solution_module import solution
def generator_test(n, m):
    '''
    always_right 不能保证连通性,其他条件满足
    '''
    try:
        n = int(n)
        m = int(m)
    except:
        print("generator_test : Invalid number format")
        return None, None

    #random.seed(200)
    out_n, out_m = [i * 2 + 1 for i in [n, m]]
    # print(out_n, out_m)
    answer = [['[W]'] * out_m for _ in range(out_n)]
    question = []
    for i in range(out_n):
        for j in range(out_m):

            if 0 < i < out_n - 1 and 0 < j < out_m - 1:
                if i & 1 == 1 and j & 1 == 1:
                    answer[i][j] = '[R]'
                elif i & 1 == 1 or j & 1 == 1:
                    answer[i][j] = random.choice(['[W]','[R]'])

                    if answer[i][j] == '[R]':
                        if i & 1 == 1:
                            src = i // 2, (j - 1) // 2
                            dst = i // 2, (j + 1) // 2
                            question.append('%d,%d %d,%d' % (src[0], src[1], dst[0], dst[1]))
                        else:
                            src = (i - 1) // 2, j // 2
                            dst = (i + 1) // 2, j // 2
                            question.append('%d,%d %d,%d' % (src[0], src[1], dst[0], dst[1]))

                        #printMatrix(answer)
                        #print(question[-1])


    question = ';'.join(question)

    # printMatrix(answer)
    # print(question)
    return question, answer

if __name__ == '__main__':
    nm = input("input m and n split by space : ")
    error, n, m = check_nm(nm)
    print(n,m)
    if error == 0:
        for i in range(10):
            print("case %d"%i)
            question, answer = generator_test(n, m)
            print("Random generator result(Does not guarantee connectivity):")
            print("question")
            print(question)
            print("answer")
            printMatrix(answer)

            flag, my_answer = solution(n, m, question)
            print("solution output:")

            if flag:
                if isEqual(answer, my_answer):
                    print("passed")
                else:
                    print("False")
                    printMatrix(my_answer)
            else:
                print("please check it by hand")
                printMatrix(my_answer)


