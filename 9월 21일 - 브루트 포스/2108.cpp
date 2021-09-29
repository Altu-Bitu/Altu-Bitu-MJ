#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

const int SIZE = 4000; //양수의 최댓값

int calcMode(vector<int>& frequency) { // 최빈값 구하는 함수. 정수형 벡터 frequency - call by reference
    int max_value = 0;  //최빈값의 빈도수
    for (int i = 0; i <= SIZE * 2; i++) { //최빈값의 빈도수 구하기
        if (frequency[i] > max_value) // 기존의 빈도수가 최빈값의 빈도수보다 많다면 
            max_value = frequency[i]; // 최빈값의 빈도수를 i의 빈도
    }
    //두 번째로 작은 최빈값 구하기
    int cnt = 0;  //최빈값 개수
    int mode = 0; //최빈값
    for (int i = 0; i <= SIZE * 2; i++) { // 최빈값의 빈도수 구하기
        if (frequency[i] == max_value) { // 기존의 빈도수가 최빈값의 빈도수와 같다면
            mode = i - SIZE; //SIZE를 더한 값으로 인덱스에 저장했었으므로 실제 값은 SIZE를 빼주어야 함
            cnt++; //  두 번째로 작은 최빈값을 구하기 위해 최빈값 개수를 +1
            if (cnt == 2) //두 번째로 작은 최빈값
                break; // 두 번째로 작은 최빈값 나오면 반복문 탈출
        }
    }
    return mode; // 최빈값 반환
}

/**
* [백준] 2108번 - 통계학
 * 1. 산술평균 계산 시 실수 자료형으로 맞춰준 후 반올림하는거 주의
 * 2. n은 홀수이므로 중앙값은 항상 (n / 2)번째 인덱스
 * 3. 최빈값은 동일한 빈도수 내에서 두 번째로 '작은' 값임
 * 4. 최빈값이 유일하게 하나만 있는 경우 고려
 */

int main() {
    int n; //n은 홀수

    //입력
    cin >> n; //입력할 정수의 개수 입력

    vector<int> num(n); //입력할 정수의 개수만큼의 정수형 벡터 선언
    vector<int> frequency(SIZE * 2 + 1, 0); //인덱스는 입력 수 + 4000의 값. 따라서 0 ~ 8000. 각 인덱스에 해당 수가 얼마나 나왔는지 저장

    double sum = 0; //평균 구하기 위한 합 변수
    for (int i = 0; i < n; i++) { // 0 ~ n 까지 반복문 돌면서
        cin >> num[i]; // n개만큼의 정수 입력
        sum += (double)num[i]; //정수를 나누면 실수가 될 수도 있기 때문에 형변환 해준다. 
        frequency[num[i] + SIZE]++; // 빈도수 + 1
    }

    //연산
    sort(num.begin(), num.end()); // 처음부터 끝까지 오름차순 정렬

    //출력
    cout << round(sum / n) << '\n';                //산술평균
    cout << num[n / 2] << '\n';                    //중앙값
    cout << calcMode(frequency) << '\n';           //최빈값
    cout << num[num.size() - 1] - num[0] << '\n';  //범위

    return 0;
}