#include <iostream>
#include <vector>

using namespace std;
typedef pair<int, int> ci; // pair�� ����ϸ� �� �ڷ��� int�� int�� ���� �� �ִ�. 

int ans; //����: �ִ� ����

//���� �� �ִ� �ִ� ���� �����ϴ� �Լ�, cnt: ��� ���� ������ ��, sum: ���ݱ����� ����
void maxConsul(int n, vector<ci>& consulting, int start, int sum) { //vector<ci>& consulting: pass by reference(������ ����)
    if (start > n) //��� ������ ���� ������� �Ѵ´ٸ� -> ����� �� ���� ���
        return; // ����������. 

    ans = max(ans, sum); // ���ݱ����� ���Ͱ� �ִ� ���� �� �� ū ���� ���ο� �ִ� �������� �����. 

    for (int i = start; i < n; i++) //i��° ���� ����ϴ� ���
        maxConsul(n, consulting, i + consulting[i].first, sum + consulting[i].second); //����Լ�. 
    // ������ �� �Ű�����: i + consulting[i].first : ��¥ + �� ��¥�� ����� �Ϸ��ϴµ� �ɸ��� �ð�. 
    // sum + consulting[i].second: ���ݱ����� ���� + i��° ������� ��� ����
}

/**
 * [����] 14501�� - ���
 * ����� ������ ���� ��, ���� �� �ִ� �ִ� ������ ���ϴ� ���α׷�
 *
 * [Ǯ��]
 * 1�� ���� ���޴� ��쿡�� �����ؼ� �� �� �ִ� ��� ����� ���� �� �غ���
 * n = 15 �̹Ƿ�, ����� �ϴµ� �ʿ��� �Ⱓ�� ��� 1���̶� �����ϸ� �ִ� ���� Ƚ����
 * -> C(15,1) + C(15,2) + ... + C(15,15) <= C(15,7) * 15 = 96,525 �̹Ƿ� ����� ���Ʈ ���� ���� ����!
 */

int main() {
    int n; //������ ���� ��

    //�Է�
    cin >> n;
    vector<ci> consulting(n); // ���� �ΰ��� �̷���� ���� consulting ����

    for (int i = 0; i < n; i++)
        cin >> consulting[i].first >> consulting[i].second; //first: ��� �ð�, second: ����

    //����
    maxConsul(n, consulting, 0, 0); // 0,0 ���� �����ؼ� ����Լ��� ���۳����� ������ ���� �� �ݺ��� ���� ���� �ִ� ���� ���

    //���
    cout << ans << '\n'; // maxConsul���� ���� �ִ� ���� ���
     
    return 0; // ���� ����
}