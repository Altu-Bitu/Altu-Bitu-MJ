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
void unionInput(int x, int y) {
    int xp = findParent(x); // x의 루트 정점
    int yp = findParent(y); // y의 루트 정점

    if (xp == yp) //같은 집합에 있다면 유니온 할 수 없음
        return; // 할 수 없으므로 함수 종료
    if (parent[xp] < parent[yp]) { //새로운 루트 xp
        parent[xp] += parent[yp];   // xp에 yp 트리 추가
        parent[yp] = xp;    // yp의 루트 정점을 xp로 설정
    } else { //새로운 루트 yp
        parent[yp] += parent[xp];   // yp에 xp 추가
        parent[xp] = yp;    // xp의 루트 정점을 yp로 설정
    }
}

/**
 * 입력으로 주어지는 i, j 도시의 연결정보를 통해 서로소 집합을 만든 후,
 * 여행 계획으로 세운 도시들이 모두 같은 집합에 속하는지 확인하는 문제
 */

int main() {
    int n, m, a, b, input; // n: 도시의 수, m: 여행 계획에 속한 도시들의 수

    //입력
    cin >> n >> m;
    parent.assign(n + 1, -1);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {  // i번째 줄의 j번째 수는 i번 도시와 j번 도시의 연결 정보
            cin >> input;   // 1이면 연결, 0이면 연결 안되어있음
            if (input) //두 정점이 연결되어 있다면
                unionInput(i, j); // Union 연산
        }
    }
    cin >> a; //시작 정점
    while (--m) {   // 계획에 속한 도시들 수 줄여가면서
        cin >> b;   // 여행 계획 순서
        if (findParent(a) != findParent(b)) { //서로 다른 집합이라면 -> 해당 경로 불가능
            cout << "NO";   // No 출력
            return 0;   // 함수 종료
        }
    }
    cout << "YES";  // 가능하므로 YES 출력
}
