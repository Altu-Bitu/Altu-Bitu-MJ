#include <iostream>
#include <vector>

using namespace std;

const int SIZE = 45; // n * (n+1) 이 2000이하여야 하므로 n의 최대값은 44


vector<int> tri_num(SIZE); //삼각수 저장할 정수형 벡터
bool ans_recursion; //재귀함수 풀이 시 사용할 정답

//유레카인지 검사하는 재귀함수
void eurekaRecur(int k, int cnt, int sum) {
    if (cnt == 3) { //정확히 3 개의 삼각수
        if (sum == k) //입력한 자연수와 합이 같다면
            ans_recursion = true; // 삼각수라고 반환 (true)
        return; //if문 종료
    }
    for (int i = 1; i <= 45; i++)
        eurekaRecur(k, cnt + 1, sum + tri_num[i]); 
    // 삼각수 몇 개 입력했는지 늘려가면서 (cnt + 1) 합이 삼각수의 합 (sum + tri_num[i]과 같은지 재귀함수로 판단.
}

//유레카인지 검사하는 반복문 함수
bool eureka(int num) {
    for (int i = 1; i <= 45; i++) { // 첫번째 삼각수
        for (int j = 1; j <= 45; j++) { // 두번째 삼각수
            for (int k = 1; k <= 45; k++) { // 세번재 삼각수
                // 반복문 3개 돌면서 세 삼각수의 합이 num과 일치하면 true를 반환한다. 
                if (tri_num[i] + tri_num[j] + tri_num[k] == num)
                    return true;
            }
        }
    }

    return false;
}

/**
 * [유레카 이론]
 * 삼각수 T(n) = n * (n + 1) / 2
 * 어떤 자연수가 정확히 3개의 삼각수의 합으로 표현 가능한지 검사해라
 *
 * [풀이]
 * 어떤 자연수(k)가 주어졌을 때, n=1부터 모든 삼각수 합을 3개씩 조합해보자
 * 이때, n = 45일 때, T(45) = 45 * 46 / 2 = 1,035 이고, k의 최댓값은 1,000이므로 45의 삼각수까지만 계산하면 됨!
 * 모두 해봤자, 45 * 45 * 45 < 1억 이므로, 브루트 포스 접근 완전 가능!
 */

int main() {
    int t, k;

    //입력
    cin >> t;

    //삼각수 SIZE까지 미리 구하기
    for (int i = 1; i <= 45; i++)
        tri_num[i] = i * (i + 1) / 2; // 45까지 돌리면 1000이하의 삼각수를 모두 저장할 수 있다. 

    //입력 + 연산 + 출력
    while (t--) { // 자연수 몇 개 입력할건지. 입력받은 값에서 1씩 내려가면서 받아야 t개의 자연수에 대해 코드를 수행가능
        cin >> k; // 3개의 삼각수의 합으로 표현되는지 입력할 자연수

        //반복문 풀이
        cout << eureka(k) << '\n'; // true이면 1, false이면 0 출력

        //재귀함수 풀이
        //ans_recursion = false;
        //eurekaRecur(k, 0, 0);
        //cout << ans_recursion << '\n';
    }

    return 0; // 정상 종료
}