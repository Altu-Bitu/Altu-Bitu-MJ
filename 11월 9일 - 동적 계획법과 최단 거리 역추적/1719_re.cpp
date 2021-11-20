//
// Created by user on 2021-11-16.
//

#include <iostream>
#include <vector>

using namespace std;
const int INF = 1e5 * 2; //최대 n-1개의 간선을 지나게 됨

void floydWarshall(int n, vector<vector<int>> &graph, vector<vector<int>> &table) { // 간선 정보와 경로 정보 순서대로 입력받음
    for (int k = 1; k <= n; k++) { // 집하장 n개
        for (int i = 1; i <= n; i++) { // 집하장 n개
            for (int j = 1; j <= n; j++) { // 집하장 n개
                int new_dist = graph[i][k] + graph[k][j]; //중간에 k를 거쳐서 i에서 j로 감
                if (new_dist < graph[i][j]) { //i->k->j가 i->j보다 빠른 경로라면
                    graph[i][j] = new_dist; // i->j의 간선정보 갱신
                    table[i][j] = table[i][k]; // i->j의 경로를 i->k의 중간 경로(table[i][k])로 갱신
                }
            }
        }
    }
}

/**
 * graph : 플로이드-워셜 결과 행렬 그래프
 * table : 경로표. table[i][j] = i->j로 가기 위해 제일 먼저 거쳐야 하는 정점
 *
 * 1. i->j의 중간 경로를 i로 초기화
 * 2. i->k->j가 i->j보다 짧다면 i->j의 중간 경로를 i->k의 중간 경로(table[i][k])로 갱신
 *    k로 갱신하는게 아니라 table[i][k]로 갱신하는 이유는?
 *    만약 i->k의 경로가 i->t->k라면 최종 경로는 i->t->k->j
 *    바로 k로 갱신하면 t를 놓칠 수 있기 때문에 table[i][k]로 갱신
 *    line 16을 table[i][j] = k로 바꾸면 결과가 어떻게 되는지 확인해보세요
 */
int main() {
    int n, m, s, d, c; // n: 집하장 개수, m: 집하장간 경로 개수, s:start 집하장 번호, d: destination 집하장 번호, c: 오가는데 필요한 시간

    //입력
    cin >> n >> m;
    vector<vector<int>> graph(n+1, vector<int>(n+1, INF)); // 간선정보 저장
    vector<vector<int>> table(n+1, vector<int>(n+1, 0)); // 경로 정보 저장
    for (int i = 1; i <= n; i++)
        graph[i][i] = 0; // 집하장 i에서 i로 가는 데 걸리는 시간은 0

    while (m--) { //무방향 그래프
        cin >> s >> d >> c; // 모든 경로의 집하장과 소요시간 입력
        //간선 정보
        graph[s][d] = graph[d][s] = c; // 집하장 s와 d를 오가는데 필요한 시간은 c

        //경로 정보 (1. table[i][j]에서 i->j의 중간 경로를 i로 초기화 => 제일 먼저 거쳐야 하는 정점은 j)
        table[s][d] = d; // s -> d로 가기 위해 제일 먼저 거쳐야 하는 정점: d
        table[d][s] = s; // d -> s로 가기 위해 제일 먼저 거쳐야 하는 정점: s
    }

    //연산
    floydWarshall(n, graph, table);

    //출력
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) { // 집하장 n개 -> table 크기: n X n
            if (i == j) // table[i][i]에는
                cout << "- "; // '-' 출력
            else // 그 외의 경우에는
                cout << table[i][j] << ' '; // 경로 정보 출력
        }
        cout << '\n'; // 구분선 출력
    }
}