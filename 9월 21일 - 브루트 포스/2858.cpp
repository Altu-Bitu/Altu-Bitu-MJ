//
// Created by user on 2021-09-27.
//
/*
 * [백준] 2858번 - 기숙사 바닥
 * 브루트포스로 풀이
 * 입력 - R: 빨간 타일의 수(가장자리) B: 갈색 타일의 수(가운데)
 * 방의 크기: L * W
 * R + B = L * W
 * 출력 - L W (W < L)
 * B = (W - 2) * (L - 2)
 * => 결국 B는 W-2로 나누었을 때 나머지가 0이어야 한다
 * R = L * W - B
 * L과 R의 범위는 모두 5000 미만으로 잡으면 충분 (왜? R의 최대값 + B의 최대값 < 25,000,000)
 */

#include <iostream>
using namespace std;

int main(void) {
    int R, B;
    int area, temp;
    // int L, W;

    cin >> R >> B;
    area = R + B;

    for (int L = 3; L < 5000; L++) {
        for (int W = 3; W < 5000; W++) {
            if (B == (L -2) * (W - 2)) {
                if (R == L  * W  - B) {
                    if (L < W) {
                        swap(L, W);
                    }

                    cout << L << ' ' << W << endl;
                    break;
                }
            }

        }
    }

    return 0;
}