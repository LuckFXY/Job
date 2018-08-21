
//int walk(map<int, PAIR> graph, int start){
//    int total = 0;
//    vector<int> stack;
//    stack.emplace_back(start);
//    int cur;
//    while(!stack.empty()){
//        cur = stack.back();
//        stack.pop_back();
//
//    }
//}
//int main() {
//
//    int n, m, a, b;
//    cin >> n >> m;
//    vector<int> weight(n);
//    for(int i=0; i<n ;i++){
//        cin>>weight[i];
//    }
//    map<int, map<int, int>> graph;
//
//    for(int i=0; i<m; i++){
//        cin>>a >> b;
//        graph.insert(a, map(b,weight[i]))
//    }
//
//    int nmax = 0, nweight = 0;
//
//    return 0;
//}

//#include <iostream>
//#include <stdio.h>
//#include <map>
//#include <vector>
//#include <string>
//using namespace std;
//int main(){
//
//    map<int , map<int, int>> graph;
//    vector<vector<int>> data={
//            {0,1},
//            {0,5},
//            {1,2},
//            {1,3},
//            {2,3},
//            {3,4},
//            {3,5}
//    };
//    int weight[6] = {2,8,3,5,6,1};
//    for(int i=0; i<6; i++){
//        int start = data[i][0], end = data[i][1];
//        if(graph.find(start) == graph.end()){
//            graph.insert(
//                    make_pair(
//                            start, map<int, int>()
//                    ));
//            graph[start][end] = weight[end];
//        }
//        else{
//            map<int, int>& inner = graph[start];
//            inner.insert(make_pair(end, weight[end]));
//        }
//    }
//
//    for(auto it = graph.begin(); it != graph.end(); it++){
//        printf("%d : ", (*it).first);
//        for(auto jt = (*it).second.begin(); jt != (*it).second.end(); jt++ ){
//            printf("(%d %d) ",(*jt).first, (*jt).second);
//        }
//        cout<<endl;
//    }
//    return 0;
//}
#include <stdio.h>
#include <iostream>
using namespace std;


class Person {
public:
    Person(const string& name, int age) : m_name(name), m_age(age) {}
    int a = 123;
    void ShowInfo() {
        cout << "姓名：" << m_name << endl;
        cout << "年龄：" << m_age << endl;
    }

protected:
    string  m_name;     //姓名

private:
    int     m_age;      //年龄
};

class Teacher : private Person
{
public:
    Teacher(const string& name, int age, const string& title)
            : Person(name, age), m_title(title)
    {
    }

    void ShowTeacherInfo()
    {
        ShowInfo();                             //正确，public属性子类可见
        cout << "姓名：" << m_name << endl;        //正确，protected属性子类可见
        //cout << "年龄：" << m_age << endl;     //错误，private属性子类不可见

        cout << "职称：" << m_title << endl;   //正确，本类中可见自己的所有成员
    }

private:
    string  m_title;        //职称
};
int main(){

    for(int i=1; i<15; i++){
        printf("%d mod %d = %d\n", i, 15, i% 15);
    }
}