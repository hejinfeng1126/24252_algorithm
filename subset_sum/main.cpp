#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "SubsetSum.h"

using namespace std;

int main() {
    int c, n;
    
    // ��ȡĿ���c��Ԫ�ظ���n
    cout << "������Ŀ���c��Ԫ�ظ���n: ";
    cin >> c >> n;
    // ��ȡn������
    vector<int> weights(n);
    cout << "������" << n << "������: ";
    for (int i = 0; i < n; i++) {
        cin >> weights[i];
    }
    // ��ʾ���������
    cout << "\n��������:" << endl;
    cout << "Ŀ���: " << c << endl;
    cout << "Ԫ��: ";
    for (int i = 0; i < n; i++) {
        cout << weights[i] << " ";
    }
    cout << endl;
    // ����SubsetSum�������
    SubsetSum subsetSum(c, weights);
    cout << "\n�������..." << endl;
    subsetSum.solve();
    // ����ļ��������Ը�����Ҫ�޸�
    string filename = "p01_s_self.txt";
    // ���������ļ�
    subsetSum.outputToFile(filename);
    return 0;
}
