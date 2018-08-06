from solution_module import solution
from tools import printMatrix, check_nm
if __name__ == '__main__':

    error = 0
    nm = input("input m and n split by space : ")
    error, n, m =check_nm(nm)

    if error == 0:
        input_str = input("input question = ")
        flag, imap = solution(n=n,m=m,input_str=input_str)
        if flag:
            printMatrix(imap)