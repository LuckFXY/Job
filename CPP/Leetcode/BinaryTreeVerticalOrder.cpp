#include<iostream>
#include<vector>
#include<map>

struct Node{
    int key;
    Node *left;
    Node *right;
};
Node* newNode(int key){
    Node* node = new Node;
    node->key = key;
    node->left = node->right = NULL;
    return node;
}
void getVerticalOrder(Node* root, int distance, std::map<int, std::vector<int>> &result){
    if(NULL == root) return ;
    result[distance].push_back(root->key);
    getVerticalOrder(root->left, distance-1, result);
    getVerticalOrder(root->right, distance+1, result);
}
void printVerticalOrder(Node* root){
    std::map<int, std::vector<int>> result;
    int distance = 0;
    getVerticalOrder(root, distance, result);
    std::map<int, std::vector<int>>::iterator it;
    for( it = result.begin(); it != result.end(); it++){
        std::vector<int> &columns = it->second;
        for(unsigned i=0; i<columns.size(); i++){
            std::cout<<columns[i]<<' ';
        }
        std::cout<<std::endl;
    }
}
Node* CreateTreeDemo(){
    /*
                 1
                /\
               /  \
              2    3
             /\    /\
            /  \  /  \
           4   5  6   7
     */
    Node* root = newNode(1);
    Node* n2 = newNode(2);
    Node* n3 = newNode(3);
    root->left = n2;
    root->right = n3;
    n2->left = newNode(4);
    n2->right = newNode(5);
    n3->left = newNode(6);
    n3->right = newNode(7);
    return root;
}
//int main(){
//    Node* root = CreateTreeDemo();
//    printVerticalOrder(root);
//    return 0;
//}