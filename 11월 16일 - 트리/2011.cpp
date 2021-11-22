
 Created by user on 2021-11-22.
 [백준] 2011번 - 암호코드
 - 알파벳 A ~ Z까지 각각 1 ~ 26의 숫자 배정.
 - 점화식 2개 도출 가능 왜 예를 들어 14는 1, 4 또는 14 두개로 나타낼 수 있기 대문
      - dp[n] = dp[n] + dp[n -1] 한자리 숫자
      - dp[n] = dp[n] + dp[n - 2] 두자리 숫자
      - 점화식은 이전 글자 + 현재 글자의 dp의 합
      - 예외처리 0은 제외

#include iostream
#include algorithm
#include string
using namespace std;
#define MAX 5001
#define MOD 1000000
int dp[MAX], arr[MAX], alpha, len;


int password() {
    dp[0] = 1;
    for (int i = 1; i = len; i++) {
        if (arr[i]  0 && arr[i]  10) {
            dp[i] = (dp[i] + dp[i - 1]) % MOD;
        }
        int x = arr[i -1]  10 + arr[i];  두자리로 만들기
        if (x = 10 && x = 26)
            dp[i] = (dp[i] + dp[i - 2]) % MOD;
    }
    return dp[len];
}

int main() {
    string s;
    cin  s;
    len = s.length();
    for (int i = 1; i = len; i++) {
        arr[i] = s[i - 1] - '0';  dp 1부터 채우기. s는 string형이기 때문에 '0'을 빼서 정수형 변환
    }
    cout  password()  endl;

    return 0;
}

 참고 사이트
  httpsmygumi.tistory.com137
  httpsjaimemin.tistory.com459
 