#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "SubsetSum.h"

using namespace std;

int main() {
    int c, n;
    
    // 读取目标和c和元素个数n
    cout << "请输入目标和c和元素个数n: ";
    cin >> c >> n;
    // 读取n个整数
    vector<int> weights(n);
    cout << "请输入" << n << "个整数: ";
    for (int i = 0; i < n; i++) {
        cin >> weights[i];
    }
    // 显示输入的数据
    cout << "\n输入数据:" << endl;
    cout << "目标和: " << c << endl;
    cout << "元素: ";
    for (int i = 0; i < n; i++) {
        cout << weights[i] << " ";
    }
    cout << endl;
    // 创建SubsetSum对象并求解
    SubsetSum subsetSum(c, weights);
    cout << "\n正在求解..." << endl;
    subsetSum.solve();
    // 输出文件名，可以根据需要修改
    string filename = "p01_s_self.txt";
    // 输出结果到文件
    subsetSum.outputToFile(filename);
    return 0;
}
