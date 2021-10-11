//
// Created by user on 2021-10-11.
//
/*
 * [백준] 1074 - Z
 * - 입력: N (판의 크기 2^N * 2^N), r, c. (찾고자 하는 위치의 좌표 (r, c))
 */

#include <iostream>
#include <cmath>
using namespace std;
int N, r, c;
int count, result; // 최종 값

void getCount(int row, int col, int size) {    // row, col 시작 좌표, size: 한 변의 길이
    /*if (row == r && col == c) { // 원하는 위치에 도달하면 종료
        cout << count << endl;
        return;
    }*/
    if (size == 1)
        return;
    int box = size * size / 4;
    // 구간별
    // 왼쪽 상단 (A)
    if (r < size / 2 && col < size / 2) {
        getCount(row, col, size / 2);
        //cout << "A " << count << "\n";

    }
    // 오른쪽 상단 (B)
    else if (r < size / 2 && col >= size / 2) {
        // A 계산한걸로 치고 더해주기
        count += box;
        getCount(row + size / 2, col, size / 2);
        //cout << "B " << count << "\n";

    }
    // 왼쪽 하단 (C)
    else if (r >= size / 2 && col < size / 2) {
        // A, B 계산한걸로 치고 더해주기
        count += (box * 2);
        getCount(row, col + size / 2, size / 2);
        //cout << "C " << count << "\n";
    }
    // 오른쪽 하단 (D)
    else {
        // A, B, C 계산한걸로 치고 더해주기
        count += (box * 3);
        getCount(row + size / 2, col + size / 2, size / 2);
        //cout << "D " << count << "\n";

    }

}

int main() {
    cin >> N >> r >> c;
    getCount(0, 0, pow(2, N));
    // 시작점: (0, 0). 사각형 한 변의 길이는 2^N
    cout << count << endl;
    return 0;
}
