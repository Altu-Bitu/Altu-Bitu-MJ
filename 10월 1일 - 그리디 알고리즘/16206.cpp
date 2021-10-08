//
// Created by user on 2021-10-06.
//
/*
 * [백준] 16206 - 롤케이크
 * 입력 - N: 롤케이크 개수, M: 자를 수 있는 최대 횟수
 *  - N개만큼의 롤케이크의 길이
 *  출력: 만들 수 있는 길이가 10인 롤케이크 개수의 최대값
 */
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int n, m;
int len, ans = 0; // len: 롤케이크의 길이, ans: 롤케이크 개수 저장값
vector <int> cake_len, cnt; // cake_len: N개만큼의 롤케이크 길이 저장, cnt: 마지막 연산


// 케이크 자르는 함수
void cut(int len) {
    while (m > 0 && len > 10) {
        if (len == 10) //케이크의 길이가 10이라면 자를 필요가 없으므로 그냥
            ans++; // 정답 개수만 한 개 증가
        else if (len % 10 == 0) {
            len -= 10; // 길이를 10만큼 줄이면 (케이크를 자르면)
            ans++; // 길이가 10인 롤케이크의 개수는 한 개 늘어나고
            m--; // 자를 수 있는 횟수는 줄어든다.
        }


        break; // 종료
    }
}

int main(void) {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> len;
        if (len < 10) // 길이가 10 미만이면 계산할 필요가 없다.
            continue;
        cake_len.push_back(len); // 입력받은 값 저장
    }

    sort(cake_len.begin(), cake_len.end()); // 길이 정렬

    for (int i = 0; i < cake_len.size(); i++) {

        // cout << cake_len[i] << " ";
        if (m <= 0) // m이 0이하이면 더이상 케이크를 자를 수 없기 때문에 종료
            break;
        else if (cake_len[i] == 10) //케이크의 길이가 10이라면 자를 필요가 없으므로 그냥
            ans++;  // 정답 개수만 한 개 증가
        else if (cake_len[i] % 10 == 0) // 10의 배수이면 바로 함수 돌리기
            cut(cake_len[i]);
        else cnt.push_back(cake_len[i]); // m이 1 이상이고, 길이가 10 이상인데 10의 배수가 아닌 경우

        // cut(cake_len[i]);
    }
/*
    for (int i = 0; i < cnt.size(); i++)
        cut(cnt[i]);
*/
    cout << ans << endl;

    return 0;
}