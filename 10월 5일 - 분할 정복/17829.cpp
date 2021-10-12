//
// Created by user on 2021-10-12.
// [백준] 17829 - 222-풀링
// 211005 - 분할 정복 (conquer - divide - combine)
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> matrix; // 행렬

int divide(int row, int col, int size) {    // 행, 열, 가장 큰 행렬(정사각형) 한 변의 길이
    //Conquer : n의 크기가 1
    if (size == 1)
        return matrix[row][col]; // 그럼 어차피 남은 수는 받은 row, col에 있는 값

    //Divide : 행렬 4등분 하기
    int next_size = size / 2;   // 행렬의 길이의 절반
    vector<int> sub_problem;    // 다음 결과로 나온 새 행렬
    for (int i = 0; i <= next_size; i += next_size) {   // 행 길이의 반
        for (int j = 0; j <= next_size; j += next_size) // 열 길이의 반 이중 반복문 돌면서
            sub_problem.push_back(divide(row + i, col + j, next_size)); // 4등분된 행렬에 대해 재귀
    }

    //Combine : 두번째로 큰 수만 남기기
    sort(sub_problem.begin(), sub_problem.end(), greater<>());  // 4등분 된 행렬의 값을 내림차순 정렬
    return sub_problem[1];  // sub_problem[0]: 첫 번째로 큰 수. sub_problem[1]: 두 번째로 큰 수
}

/**
 * 1. 행렬 4등분 하기
 * 2. 행렬의 크기가 1이라면 원소 리턴
 * 3. 리턴된 원소 4개 모아서 두번째로 큰 수만 리턴
 */
int main() {
    int n;  // n은 항상 2의 거듭제곱 꼴

    //입력
    cin >> n;
    matrix.assign(n, vector<int>(n));   // 행렬 선언
    for (int i = 0; i < n; i++) {   // n개의 줄 마다
        for (int j = 0; j < n; j++) // 각 행의 원소 n개
            cin >> matrix[i][j];    // 입력받아 matrix에 복사
    }

    //연산 & 출력
    cout << divide(0, 0, n);
}