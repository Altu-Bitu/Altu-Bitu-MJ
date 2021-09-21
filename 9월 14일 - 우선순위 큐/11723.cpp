//
// Created by user on 2021-09-21.
//
#include <iostream>
#include <vector>
#include <string>

using namespace std;
const int SIZE = 21;

/**
 * 배열 사용 풀이
 * 1. 집합에는 1~20의 숫자만 입력 or 제거됨 (=true or false)
 * 2. 크기 21의 bool 배열을 선언
 * 3. 입력은 true 처리, 제거는 false 처리
 */
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int m, num;
    string cmd;
    vector<bool> s(SIZE, false);

    cin >> m; // 수행해야 하는 연산의 수
    while (m--) { // m개의 줄에 수행해야하는 연산이 하나씩 주어지고, m의 값은 줄어든다/
        // 그러면 m개의 연산 출력
        cin >> cmd;
        // all: S를 {1, 2, ...., 20}으로 변경
        if (cmd == "all") { //1~20까지 true가 되도록 재할당
            // 원소의 개수: SIZE(21)로 벡터 s를 채운다.
            s.assign(SIZE, true);
            continue;
        }
        // empty: S를 공집합으로 바꾼다. (false값을 넣어주면 집합이 비게 된다.)
        if (cmd == "empty") { //1~20까지 false가 되도록 재할당
            s.assign(SIZE, false);
            continue;
        }

        cin >> num;
        // add x: S에 x 추가 (x 대신 num 사용)
        if (cmd == "add") { //num을 true 처리
            s[num] = true;
            continue;
        }
        // remove x: S에서 x 제거. 이미 s[num]이 false라면 아무 일도 일어나지 않을 것.
        if (cmd == "remove") { //num을 false 처리
            s[num] = false;
            continue;
        }
        // check x: S에 x가 있으면 1을, 없으면 0을 출력한다.
        // s[num] true라면 1을, false라면 0을 출력할 것
        if (cmd == "check") { //num의 상태 확인
            cout << s[num] << '\n';
            continue;
        }
        // toggle x: S에 x가 있으면 x를 제거하고, 없으면 x를 추가한다.
        // 반대 값으로 채워주면 제시된 toggle 연산의 조건을 만족시킬 수 있다 -> != 사용
        if (cmd == "toggle") { //true->false, false->true
            s[num] = !s[num];
            continue;
        }
    }
}
