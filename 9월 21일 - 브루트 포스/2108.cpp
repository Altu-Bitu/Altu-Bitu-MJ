#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

const int SIZE = 4000; //����� �ִ�

int calcMode(vector<int>& frequency) { // �ֺ� ���ϴ� �Լ�. ������ ���� frequency - call by reference
    int max_value = 0;  //�ֺ��� �󵵼�
    for (int i = 0; i <= SIZE * 2; i++) { //�ֺ��� �󵵼� ���ϱ�
        if (frequency[i] > max_value) // ������ �󵵼��� �ֺ��� �󵵼����� ���ٸ� 
            max_value = frequency[i]; // �ֺ��� �󵵼��� i�� ��
    }
    //�� ��°�� ���� �ֺ� ���ϱ�
    int cnt = 0;  //�ֺ� ����
    int mode = 0; //�ֺ�
    for (int i = 0; i <= SIZE * 2; i++) { // �ֺ��� �󵵼� ���ϱ�
        if (frequency[i] == max_value) { // ������ �󵵼��� �ֺ��� �󵵼��� ���ٸ�
            mode = i - SIZE; //SIZE�� ���� ������ �ε����� �����߾����Ƿ� ���� ���� SIZE�� ���־�� ��
            cnt++; //  �� ��°�� ���� �ֺ��� ���ϱ� ���� �ֺ� ������ +1
            if (cnt == 2) //�� ��°�� ���� �ֺ�
                break; // �� ��°�� ���� �ֺ� ������ �ݺ��� Ż��
        }
    }
    return mode; // �ֺ� ��ȯ
}

/**
* [����] 2108�� - �����
 * 1. ������ ��� �� �Ǽ� �ڷ������� ������ �� �ݿø��ϴ°� ����
 * 2. n�� Ȧ���̹Ƿ� �߾Ӱ��� �׻� (n / 2)��° �ε���
 * 3. �ֺ��� ������ �󵵼� ������ �� ��°�� '����' ����
 * 4. �ֺ��� �����ϰ� �ϳ��� �ִ� ��� ���
 */

int main() {
    int n; //n�� Ȧ��

    //�Է�
    cin >> n; //�Է��� ������ ���� �Է�

    vector<int> num(n); //�Է��� ������ ������ŭ�� ������ ���� ����
    vector<int> frequency(SIZE * 2 + 1, 0); //�ε����� �Է� �� + 4000�� ��. ���� 0 ~ 8000. �� �ε����� �ش� ���� �󸶳� ���Դ��� ����

    double sum = 0; //��� ���ϱ� ���� �� ����
    for (int i = 0; i < n; i++) { // 0 ~ n ���� �ݺ��� ���鼭
        cin >> num[i]; // n����ŭ�� ���� �Է�
        sum += (double)num[i]; //������ ������ �Ǽ��� �� ���� �ֱ� ������ ����ȯ ���ش�. 
        frequency[num[i] + SIZE]++; // �󵵼� + 1
    }

    //����
    sort(num.begin(), num.end()); // ó������ ������ �������� ����

    //���
    cout << round(sum / n) << '\n';                //������
    cout << num[n / 2] << '\n';                    //�߾Ӱ�
    cout << calcMode(frequency) << '\n';           //�ֺ�
    cout << num[num.size() - 1] - num[0] << '\n';  //����

    return 0;
}