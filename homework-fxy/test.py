from input_format import format_input
from tools import getKey, printMatrix, isConnection, isEqual
from sample_generator import generator_test
from solution_module import solution
import unittest
class TestSolver(unittest.TestCase):
    def test_invalid_number_format(self):
        '''
        测试用例：输入无效的数字
        '''
        print("\n--------------test: invalid_number_format")
        n_list = [3, 'ab', 0.5, '0.5']
        m_list = [3, 'ab', 0.5, '0.5']
        s_list = [
        'a,1 0,2;0,0 1,0;0,1 1,1;0,2 1,2;1,0 1,1;1,1 1,2;1,1 2,1;1,2 2,2;2,0 2,1',
         '*,1 0,2;0,0 1,0;0,1 1,1;0,2 1,2;1,0 1,1;1,1 1,2;1,1 2,1;1,2 2,2;2,0 2,1',
         '0.5,1 0,2;0,0 1,0;0,1 1,1']
        for n in n_list:
            for m in m_list:
                for s in s_list:
                    error, src_dst_list, all_point = format_input(s, n, m)
                    err_msg = "failed: n,m,s= %s" % str([error, n, m, s])
                    self.assertEqual(error,1,err_msg)


    def test_number_out_of_range(self):
        '''
        测试用例：输入数字超出预定范围
        '''
        print("--------------test: number_out_of_range")
        print("test result:")
        n_list = [3, -2, 0, 9999]
        m_list = [3, -2, 0, 9999]
        s_list = \
        ['-8,1 0,2;0,0 1,0;0,1 1,1;0,2 1,2;1,0 1,1;1,1 1,2;1,1 2,1;1,2 2,2;2,0 2,1',
         '99999,1 0,2;0,0 1,0;0,1 1,1;0,2 1,2;1,0 1,1;1,1 1,2;1,1 2,1;1,2 2,2;2,0 2,1']
        for n in n_list:
            for m in m_list:
                for s in s_list:
                    error, src_dst_list, all_point = format_input(s, n, m)
                    err_msg = "failed: n,m,s= %s" % str([error, n, m, s])
                    self.assertEqual(error,2,err_msg)
                    #print(error)
                    #print(src_dst_list)
                    #print(all_point)

    def test_incorrect_command_format(self):
        '''
        测试用例：输入数字格式错误
        '''
        print("----------------test: incorrect_command_format")
        n_list = [3, 2]
        m_list = [3, 5]
        s_list = \
        ['0,1,0,2;0,0 1,0;0,1 1,1;0,2 1,2;1,0 1,1;1,1 1,2;1,1 2,1;1,2 2,2;2,0 2,1',
         '0;1 0,2;0,0 1,0;0,1 1,1;0,2 1,2;1,0 1,1;1,1 1,2;1,1 2,1;1,2 2,2;2,0 2,1',
         '0,1=0,2;0,0 1,0;0,1 1,1;0,2 1,2;1,0 1,1;1,1 1,2;1,1 2,1;1,2 2,2;2,0 2,1']
        for n in n_list:
            for m in m_list:
                for s in s_list:
                    error, src_dst_list, all_point = format_input(s, n, m)
                    err_msg = "failed: n,m,s= %s" % str([error, n, m, s])
                    self.assertEqual(error, 3, err_msg)
            #print(error)
            #print(src_dst_list)
            #print(all_point)

    def test_maze_format_error(self):
        '''
        测试用例：输入存在连通性错误
        '''
        print("-----------------test: maze_format_error")
        n, m = 3, 3
        s_list = \
        ['0,0 1,0;0,1 1,1;0,2 1,2;1,1 1,2;1,1 2,1;2,0 2,1',
        '0,1 1,1;0,2 1,2;1,2 2,2;2,1 2,2']
        for s in s_list:
            flag, my_answer = solution(n, m, s)
            err_msg = "failed at s = %s"%s
            self.assertEqual(flag, False, err_msg)
            print("passed")


    def test_sample_generator(self):
        '''
        测试样本生成器的有效性
        :return:
        '''
        print("---------------unit test: sample generator")
        n, m = 3,3
        s_list = \
        ['0,1 0,2;0,0 1,0;0,1 1,1;0,2 1,2;1,0 1,1;1,1 1,2;1,1 2,1;1,2 2,2;2,0 2,1',
         '0,0 0,1;0,1 0,2;0,0 1,0;0,2 1,2;1,2 2,2;2,0 2,1;2,1 2,2',
         '0,1 0,2;0,1 1,1;1,1 1,2;1,2 2,2;2,0 2,1;2,1 2,2',
         '0,1 0,2;0,1 1,1;1,1 1,2;2,1 2,2'
         ]
        for s in s_list:
            s_set = set(s.split(';'))
            passed = False
            for i in range(50000):
                question, answer = generator_test(3,3)
                question_set = set(question.split(';'))
                if question_set == s_set:
                    passed = True
                    break
            err_msg = "failed at s = %s" % s
            self.assertEqual(passed, True, err_msg)
            print("passed")


    def test_pass(self):
        '''
        测试用例：输入的数字有效，输出的字符串正确
        '''
        print("-------------test:solution test")
        n, m = 3, 3
        s_list = \
        [ '0,1 0,2;0,0 1,0;0,1 1,1;0,2 1,2;1,0 1,1;1,1 1,2;1,1 2,1;1,2 2,2;2,0 2,1',
         '0,0 0,1;0,0 1,0;0,1 1,1;1,0 1,1;1,0 2,0;1,1 2,1',
         '0,0 0,1;0,1 0,2;0,0 1,0;0,2 1,2;1,0 2,0;1,2 2,2',]
        for s in s_list:
            #print(n,m,s_list)
            flag, my_answer = solution(n, m, s)
            err_msg = "failed at s = %s" % s
            self.assertEqual(flag, True, err_msg)
            print("passed")

if __name__ == '__main__':
    unittest.main()
