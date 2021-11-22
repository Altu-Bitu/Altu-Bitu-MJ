//
// Created by user on 2021-11-22.
// [백준] 5639 - 이진 검색 트리
// 입력값: 전위순회한 값 -> 출력: 후위순회
//

#include <iostream>
using namespace std;

typedef struct TreeNode{
    int key;
    TreeNode *left;
    TreeNode *right;
}TreeNode;

TreeNode* new_node(int item) {  // 새 노드 생성
    TreeNode *node = (TreeNode*)malloc(sizeof(TreeNode));   //새로운 메모리 할당
    node->key = item;       // 값 복사
    node->left = node->right = NULL;    // child 노드를 NULL로 초기화
    // cout << "new";
    return node;                        // 새로 생성된 노드 반환
}

TreeNode* insert_node(TreeNode* node, int key) {    // 해당 위치 탐색해서 key 값 갖는 노드 insert
    if (node == NULL) return new_node(key); // 트리가 공백이면 insert된 새로운 노드 반환
    if (key < node->key)    // insert할 값이 root의 키값보다 작으면 left subtree를 root로 insert 재귀호출
        node->left = insert_node(node->left, key);
    else if (key > node->key) // insert할 값이 root의 키값보다 크면 right subtree를 root로 insert 재귀호출
        node->right = insert_node(node->right, key);
    // cout << node->key << endl;
    return node;    // 변경된 root포인터 반환
}

void postorder(TreeNode* root) {  // 중위 순회
    if (root == NULL) {
        //cout << "empty tree";
        return;   // empty tree면 NULL 반환
    }
    else {
       // cout << "stop postorder";
        postorder(root->left);    // left subtree traverse
        postorder(root->right);   // right subtree traverse
        cout << root->key << endl;
    }
}
int main() {
    TreeNode* root = NULL;
    int data;
    cin >> data;
    root = insert_node(root, data);
    while(cin >> data) {
        if (data == EOF) break;
        root = insert_node(root, data);
        // cout << "insert_print" << '\n';
    }
    // cout << "before post";
    postorder(root);
    return 0;
}

/* 참고 사이트:
 * https://velog.io/@kpg0518/%EB%B0%B1%EC%A4%80-5639%EB%B2%88-%EC%9D%B4%EC%A7%84-%EA%B2%80%EC%83%89%ED%8A%B8%EB%A6%AC
 * https://imnotabear.tistory.com/224
 * 도인실 교수님 수업자료
 *
 */