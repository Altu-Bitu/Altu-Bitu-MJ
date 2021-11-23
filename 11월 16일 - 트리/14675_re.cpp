//
// Created by user on 2021-11-23.
//

#include <iostream>
#include <vector>

using namespace std;

//단절점, 단절선 파악 함수
string isTrue(int t, int k, vector<vector<int>> &tree) {
    if (t == 2) // k번째 간선이 단절선?
        return "yes"; // 질의가 맞으므로 yes (트리를 양방향 그래프로 저장하기 때문에 모든 간선이 단절선)
    if (tree[k].size() >= 2) // k번 정점이 단절점? (t != 2 -> t == 1)
        return "yes"; // 질의가 맞으므로 yess
    return "no"; // 질의가 틀리므로 no
}

/**
 * 부모 노드를 알 수 없기에 트리를 양방향 그래프로 저장
 * 단절점: 트리는 모든 정점이 연결되어 있고, 싸이클이 존재하지 않기 때문에 연결된 간선이 2개 이상이면 단절점
 * 단절선: 트리는 모든 정점이 연결되어 있고, 싸이클이 존재하지 않기 때문에 모든 간선이 단절선
 */

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); // 입력 속도 최적화
    int n, a, b, q, t, k; // n: 트리의 정점 개수, a, b: 간선의 정보(a정점과 b정점이 연결되어 있음)
    // q: 질의의 개수, t: 1: 단절점? 2: 단절선?, k: 질의하는 간선

    //입력
    cin >> n; //트리의 정점 개수
    vector<vector<int>> tree(n + 1, vector<int>(0)); // 트리 생성
    for (int i = 0; i < n - 1; i++) { // 트리의 정점 개수 만큼
        cin >> a >> b; // 간선의 정보 입력받기
        tree[a].push_back(b); // a와 b가 연결되어 있고,
        tree[b].push_back(a); // b와 a가 연결되어 있음
    }
    cin >> q; // 질의의 개수 입력받기
    while (q--) { // 질의의 개수 동안
        cin >> t >> k; // t와 k 입력받아서
        cout << isTrue(t, k, tree) << '\n'; // 단절점, 단절선을 파악하고 출력.
    }
    return 0;
}