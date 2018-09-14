//
// Created by Administrator on 2018/9/9.
//转载 http://discuss.acmcoder.com/topic/5b951e5933e70c1e00cc0ac4 coder_Ecjlqo4i
//

#include<iostream>
#include<vector>
#include<set>
#define FRE
using namespace std;
int T;
int N, M;
int completely_graph(){
#ifdef FRE
    freopen("in.txt","r",stdin);
#endif
    cin >> T;
    for(int t=0; t<T; t++){
        cin >> N >> M;
        vector<int> aa(N+1, 0);
        vector<vector<int>> arr(N+1, aa);
        bool valid = true;
        for(int i=0; i< M; i++){
            int x, y;
            // 用邻接矩阵保存数据，注意无向图的保存
            cin >> x >> y;
            arr[x][y] = 1;
            arr[y][x] = 1;
        }
        /*
         * 每一个新的点都跟已有的集合进行比较，
         * 如果和集合中的点都不相连就加入结合，否则创建新的集合
         */
        vector<set<int>> set_arr;
        for(int i=1; i<= N; i++){
            bool insertFlag = false;
            for(auto &iset : set_arr){
                int num = 0; //一个集合中冲突的点个数
                for(auto item : iset){
                    //检测冲突
                    if (arr[i][item] == 1)
                        num += 1;
                }
                /*
                 * n = iset.size() 与这个集合中每个点都冲突,换一个集合
                 * n = 0           没有冲突
                 * n < iset.sizs() 部分冲突
                 */
                if(num == iset.size())
                    continue;
                else if (num==0){
                    if(!insertFlag){
                        //没有冲突，加入当前集合set
                        iset.insert(i);
                        insertFlag = true;
                    }
                    else{
                        //一个点只能加入一个集合，所以出现第二次插入是时，出错
                        valid = false;
                        i = N+1;
                        break;
                    }
                }
                else{
                    //当前点不在集合中，但是要满足集合中任意一点与该点连接，否则非完全分部图。
                    valid = false;
                    i = N+1;
                    break;
                }
            }
            if(!insertFlag){
                //全部冲突，新建一个集合
                set<int> tmp;
                tmp.insert(i);
                set_arr.push_back(tmp);
            }
        }
        if(valid)
            cout<<"Yes"<<endl;
        else
            cout<<"No"<<endl;
    }
    return 0;
}