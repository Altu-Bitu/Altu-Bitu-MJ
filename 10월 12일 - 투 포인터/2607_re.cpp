//
// Created by user on 2021-11-02.
//

#include <iostream>
#include <vector>

using namespace std;
const int SIZE = 26; // 알파벳 수 26개

//알파벳별 등장횟수 저장
vector<int> alphaMap(string str) {
    vector<int> result(SIZE, 0); // 알파벳 수 만큼의 크기의 벡터 생성
    for (int i = 0; i < str.size(); i++) // 입력한 문자열의 길이만큼 반복문 돌면서
        result[str[i] - 'A']++; // 알파벳 등장했다면 배열 수 추가해주기
    return result; // 정답 반환
}

/**
 * 단어가 같은 구성일 조건
 * 1. 두 개의 단어가 같은 종류의 문자로 이루어짐
 * 2. 같은 문자는 같은 개수만큼 있음
 *
 * 비슷한 단어의 조건
 * 1. 한 단어에서 한 문자를 더하거나, 빼면 같은 구성이 됨
 *    -> 두 단어에서 다른 문자의 개수가 총 1개
 * 2. 한 단어에서 한 문자를 바꾸면 같은 구성이 됨
 *    -> 두 단어에서 다른 문자의 개수가 총 2개
 *    -> !주의! 이때, 두 단어의 길이가 같아야 함 cf) doll | do
 */
int main() {
    int n, ans = 0; // n: 단어의 개수
    string source, target; // source: 첫번째 단어 (비교군)

    //입력
    cin >> n >> source;

    //연산
    vector<int> source_alpha = alphaMap(source); // 첫번째 단어 알파벳 등장횟수 정리
    while (--n) { // 첫 단어는 비교군으로 빠졌으니까 --n으로 (n - 1만큼 반복)
        cin >> target; // 비교할 단어 입력

        int diff = 0; // 두 단어의 차이 계산
        vector<int> target_alpha = alphaMap(target); // 비교할 단어 알파벳 등장횟수
        for (int i = 0; i < SIZE; i++) //두 단어의 차이
            diff += abs(source_alpha[i] - target_alpha[i]); // 알파벳별 등장횟수의 차의 합
        if (diff <= 1 || (diff == 2 && source.size() == target.size())) //문자를 더하거나, 빼거나, 바꾸거나
            ans++; // 정답 증가
    }

    //출력
    cout << ans;
}