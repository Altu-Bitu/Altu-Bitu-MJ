//
// Created by user on 2021-12-21.
//

#include <iostream>
#include <vector>
#include <queue>

using namespace std;
typedef pair<int, int> ci;

//위상정렬 + DP
vector<vector<int>> topologicalSort(int n, vector<int> &indegree, vector<vector<ci>> &graph) {
    queue<int> q;   // 순서 정할 때 사용할 큐
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0)); //각 부품이 몇 개 필요한지 저장

    for (int i = 1; i <= n; i++) {
        if (!indegree[i]) { //진입차수가 0이라면 -> 기본 부품
            q.push(i); // 큐에 추가
            dp[i][i] = 1; //기본 부품 초기화
        }
    }
    while (!q.empty()) { // 큐가 비어있지 않을 동안(기본부품이 존재할 동안)
        int node = q.front(); // 큐의 첫번째 값(첫번째 기본 부품)을 node에 저장하고
        q.pop();    // 값 저장했으니 pop

        for (int i = 0; i < graph[node].size(); i++) { // 기본부품 y에 대해
            int next_node = graph[node][i].first; // 만들 중간부품이나 완제품 x
            int cnt = graph[node][i].second; //필요한 부품 수 k
            indegree[next_node]--; //연결된 정점의 진입차수를 1씩 감소
            if (!indegree[next_node]) //연결된 정점의 진입차수가 0이 되었다면
                q.push(next_node); // 큐에 추가

            for (int j = 1; j <= n; j++) // 부품 수만큼 반복하면서
                dp[next_node][j] += dp[node][j] * cnt; //(현재 정점을 이루는 부품 개수 * 필요한 현재 정점의 개수)를 더함
        }
    }
    return dp; // 모두 더한 값 반환
}

/**
 * 각 부품마다 종류별 필요한 부품 개수를 저장하기 위해 2차원 배열 사용 (행: 부품, 열: 행을 이루는데 각 부품별 필요한 개수)
 * 위상 정렬 순서에 따라, 이어진 다음 정점의 부품별 개수를 (현재 정점을 이루는 부품별 개수 * 필요한 현재 정점 수)를 더해주며 구함
 */

int main() {
    int n, m, x, y, k; // x, y, k: 어떤 부품을 완성하는데 필요한 부품들 간의 관계

    //입력
    cin >> n >> m; // n: 완제품의 번호, m: 관계의 수
    vector<vector<ci>> graph(n + 1, vector<ci>(0));
    vector<int> indegree(n + 1, 0);
    while (m--) {
        cin >> x >> y >> k; //y -> x
        // 중간 부품이나 완제품 X를 만드는데 중간 부품 혹은 기본 부품 Y가 K개 필요하다
        indegree[x]++; // 진입차수 계산
        graph[y].push_back({x, k}); // 기본부품 y에 대한 관계 저장
    }

    //연산
    vector<vector<int>> result = topologicalSort(n, indegree, graph);

    //출력
    for (int i = 1; i <= n; i++) {
        if (result[i][i]) //기본 부품이라면
            cout << i << ' ' << result[n][i] << '\n'; // 기본부품 번호 + 소요 개수 출력
    }
    return 0;
}