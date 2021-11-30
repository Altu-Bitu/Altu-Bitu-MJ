//
// Created by user on 2021-11-30.
//

#include <iostream>
#include <vector>

using namespace std;

vector<int> parent;

//Find 연산
int findParent(int node) {
    if (parent[node] < 0) //루트 정점
        return node;    // 입력한 노드가 루트 정점이므로 노드 반환
    return parent[node] = findParent(parent[node]); //그래프 압축하며 루트 정점 찾기
}

//Union 연산
bool unionInput(int x, int y) {
    int xp = findParent(x); // x의 루트 정점
    int yp = findParent(y); // y의 루트 정점

    if (xp == yp) //같은 집합에 있다면 유니온 할 수 없음
        return false; // 할 수 없으므로 false 반환
    if (parent[xp] < parent[yp]) { //새로운 루트 xp
        parent[xp] += parent[yp];   // xp에 yp 트리 추가
        parent[yp] = xp;    // yp의 루트 정점을 xp로 설정
    } else { //새로운 루트 yp
        parent[yp] += parent[xp];   // yp에 xp 추가
        parent[xp] = yp;    // xp의 루트 정점을 yp로 설정
    }
    return true;        // Union 가능하므로 true 반환
}
/**
 * 사이클이 발생한 순간 = 같은 집합에 있는 원소 두 개를 유니온하려 할 때
 * unionInput 함수의 반환형을 bool로 선언하여 cycle이 생성되는 순간 발견하기
 */
int main() {
    int n, m, x, y; // n: 점의 개수, m: 게임 차례, x, y: 플레이어가 자신의 차례에 선택한 두 개의 점

    //입력
    cin >> n >> m;
    parent.assign(n, -1);   // 점의 개수만큼 -1로 초기화
    for (int i = 0; i < m; i++) {   // 차례만큼
        cin >> x >> y;  // 선택한 두 개의 점 입력

        //연산 & 출력
        if (!unionInput(x, y)) { //유니온 할 수 없음 = 사이클이 생성됨
            cout << i + 1;  // i의 시작 값을 0으로 설정했으므로 사이클이 만들어진 차례의 번호는 i+1
            return 0;   // 종료
        }
    }
    cout << 0;  // m번의 차례를 모두 처리한 이후에도 종료되지 않았으므로 0 출력
}