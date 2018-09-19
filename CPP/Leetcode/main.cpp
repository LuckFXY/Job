#include<iostream>
#include<vector>
#include<string>
using namespace std;
int check_line(const vector<vector<short>> &table, int startX, int startY, int dx, int dy){
    int cnt = 1;
    int color=0;
    for(int i=startX, j = startY; i<15; i+=dx, j+=dy){
        if(i+dx >= 15 || j + dy >= 15 || j+dy <0 || i+dx <0) break;
        if(table[i][j]!=0 && table[i][j] ==table[i+dx][j+dy]){
            cnt += 1;
            color = table[i][j];
            if(cnt == 5) break;
        }
        else
            cnt = 0;
    }
    return cnt == 5 ? color : 0;
}
int check(const vector<vector<short>> &table){
    int flag = 0;
    for(int i=0; i<15; i++){
        for(int j=0; j<15; j++){
            flag = check_line(table, i,j, 0, 1);
            if(flag) return flag;
            flag = check_line(table, i,j, 1, 0);
            if(flag) return flag;
            flag = check_line(table, i,j, 1, 1);
            if(flag) return flag;
            flag = check_line(table, i,j, 1, -1);
        }
    }
    return flag;

}
#include<sstream>
stringstream ss;
string test=
        "...............\n"
        "...............\n"
        "...............\n"
        "...............\n"
        "...............\n"
        "...............\n"
        "...............\n"
        "......BW.......\n"
        "......WB.......\n"
        "........B......\n"
        ".........B.....\n"
        "..........B....\n"
        "...............\n"
        "...............\n"
        "...............";
void print(vector<vector<short>> &table){
    for(int i=0; i<15; i++){
        for(int j=0; j<15; j++){
            cout<<table[i][j]<<' ';
        }

        cout<<endl;
    }
}
int main(){
    ss.str(test);
    vector<vector<short>> table(15, vector<short>(15,0));
    string s;
    int status=0;
    int cnt = 0;
    while(ss >> s){
        cnt = 0;
        for(int i=0; i<15; i++){
            if(s[i] == 'B')
                table[0][i] = 1;
            else if(s[i] == 'W')
                table[0][i] = -1;
            else if(s[i] == '.')
                table[0][i]=0;
            else{
                status=-1;
                break;
            }
            cnt += s[i] == '.' ? 0 : 1;
        }

        if(status != -1){
            for(int i=1;i<15 && status != -1; i++){
                ss >> s;
                for(int j=0; j<15;j++){
                    if(s[j] == 'B')
                        table[i][j] = 1;
                    else if(s[j] == 'W')
                        table[i][j] = -1;
                    else if(s[j] == '.')
                        table[i][j]=0;
                    else{
                        status=-1;
                        break;
                    }
                    cnt += s[j] == '.' ? 0 : 1;
                }
            }
        }
        //print(table);
        if(status == -1){
            cout<<"invalid board"<<endl;
        }
        else if(cnt == 15 * 15){
            cout<<"draw"<<endl;
        }
        else{
            int color = check(table);
            if(color == 1)
                cout<<"black win"<<endl;
            else if(color == -1)
                cout<<"white win"<<endl;
            else{
                cout<<"not finished"<<endl;
            }
        }
    }


    return 0;
}