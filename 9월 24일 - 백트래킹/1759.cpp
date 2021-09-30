//
// Created by user on 2021-09-30.
//
/*
 * [백준] 1759번 - 암호 만들기
 * 1. 암호는 서로 다른 L개의 알파벳 '소문자'
 * 조건1. 알파벳은 최소 한 개의 모음과 최소 두 개의 자음으로 구성 (!조건!)
 *  - 모음의 경우 a, e, i, o, u 5개이므로 별도로 선언을 하지 않고 if문에서 판단.
 * 조건2.  정렬된 문자열 (알파벳이 암호에서 증가하는 순서)
 * 4. 문자의 종류는 C가지
 * 입력 - C: 주어지는 알파벳 소문자의 수, L: 암호의 알파벳 수
 * 입력 범위: 3 <= L <= C <= 15
 */

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;
char alphabet[16]; // 입력 최대값이 15
int L, C;

// pos: 현재 문자의 위치, vowel: 모음, con: 자음 (consonant)
void backTracking(int pos, string str, int vowel, int con)
{
    if (str.size() == L) //입력된 문자열의 크기가 L(암호의 길이)와 같다면
    {
        if (vowel >= 1 && con >= 2) // 조건 1. 모음이 1개 이상, 자음이 2개 이상이라면 => 조건 만족
        {
            cout << str << endl; // 조건에 모두 부합하므로 문자열 출력
            return;
        }
    }
    for (int i = pos; i <= C; i++) //입력한 모든 알파벳(C)에 대한 반복문을 돌면서
    {   // 알파벳이 모음이라면
        if (alphabet[i] == 'a' || alphabet[i] == 'e' || alphabet[i] == 'i' || alphabet[i] == 'o' || alphabet[i] == 'u')
        {   // 재귀함수 - 위치는 하나 늘리고, 문자열에 해당 문자열 추가하고, 모음은 1개 늘리고, 자음은 변화 x
            backTracking(i + 1, str + alphabet[i], vowel + 1, con);
        }
        else // 알파벳이 자음이라면
        {   // 재귀함수 - 위치는 하나 늘리고, 문자열에 해당 문자열 추가하고, 모음은 변화 x, 자음은 1개 늘린다.
            backTracking(i + 1, str + alphabet[i], vowel, con + 1);
        }
    }
}
int main(void) {
    cin >> L >> C; // L과 C를 입력받는다.
    for (int i = 1; i <= C; i++)
        cin >> alphabet[i]; // C개만큼의 알파벳 입력받는다.

    sort(alphabet, alphabet + C + 1); // 조건 2. 정렬하기. backTrack 함수를 실행하기 전 꼭! 먼저 정렬해야 한다.
    // backTracking 함수에 대해 시작점은 1 (이건 따로 질문하기)
    // str은 입력된 것이 없으므로 빈 문자열, 마찬가지로 모음과 자음의 개수도 0이므로 0으로 입력.
    backTracking(1, "", 0, 0);

    return 0;
}
