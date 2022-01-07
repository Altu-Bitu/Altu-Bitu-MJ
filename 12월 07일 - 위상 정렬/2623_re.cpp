//
// Created by user on 2021-12-21.
//

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

//위상정렬
vector<int> topologicalSort(int n, vector<int> &indegree, vector<vector<int>> &graph) {
    vector<int> result; // 결과 저장할 벡터
    queue<int> q;   // 순서 정할 때 사용할 큐

    for (int i = 1; i <= n; i++) { // 가수의 수만큼 반복하면서
        if (!indegree[i]) //진입차수가 0이라면
            q.push(i);  // 큐에 push
    }

    while (!q.empty()) {    // 큐가 비어있지 않을동안
        int node = q.front();   // 큐의 첫번째 값을 node에 저장하고
        q.pop();    // 값 저장했으니 pop

        result.push_back(node); //현재 정점 순서에 삽입
        for (int i = 0; i < graph[node].size(); i++) { // 큐의 첫번째 값의 크기만큼 반복하면서
            int next_node = graph[node][i]; // next_node에 다음 값 저장
            indegree[next_node]--; //연결된 정점의 진입차수를 1씩 감소
            if (!indegree[next_node]) //연결된 정점의 진입차수가 0이 되었다면
                q.push(next_node); // 큐에 추가
        }
    }
    return result; // 결과값 반환
}

/**
 * 기본적인 위상 정렬 문제
 * 현재 가수와 바로 전 가수 사이의 선후관계를 정의
 * 순서를 정하는 것이 불가능한 경우(위상정렬을 할 수 없는 경우)는 모든 정점을 탐색하지 못한 경우
 */

int main() {
    int n, m, cnt, prev, cur;

    //입력
    cin >> n >> m; // 가수의 수 n, 보조 pd의 수 m
    vector<int> indegree(n + 1, 0); // 진입차수
    vector<vector<int>> graph(n + 1, vector<int>(0));
    while (m--) { // 보조 pd의 수만큼 반복하면서 입력받기
        cin >> cnt; //담당 가수의 수
        cin >> prev; //처음 가수 입력
        while (--cnt) { //선후관계 정의
            cin >> cur; // 가수들의 순서
            indegree[cur]++;    // 진입 차수 저장
            graph[prev].push_back(cur); // 처음가수가 prev인 그래프에 가수 추가
            prev = cur; // 다음 가수를 처음 가수로 업데이트
        }
    }

    //연산
    vector<int> result = topologicalSort(n, indegree, graph);

    //출력
    if (result.size() != n) { //순서를 정하는 것이 불가한 경우
        cout << "0\n";  // 0 출력하고
        return 0;   // 종료
    }
    for (int i = 0; i < result.size(); i++) // 결과 벡터의 크기만큼 반복하면서
        cout << result[i] << '\n'; // 결과 출력
}