#ifndef SUBSETSUM_H
#define SUBSETSUM_H

#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

class SubsetSum {
private:
    vector<int> weights;              // 输入的权重数组
    int target;                       // 目标和
    int n;                           // 权重数组的大小
    vector<vector<int>> solutions;   // 存储所有找到的解决方案
    /**
     * 回溯算法
     * @param index 当前处理的元素索引
     * @param currentSum 当前子集的和
     * @param currentSubset 当前正在构建的子集
     */
    void backtrack(int index, int currentSum, vector<int>& currentSubset);
    bool isDuplicateSolution(const vector<int> &currentSubset);
public:
    /**
     * 构造函数
     * @param targetSum 目标和
     * @param inputWeights 输入的权重数组
     */
    SubsetSum(int targetSum, const vector<int>& inputWeights);
    void solve();                              // 开始求解子集和问题
    void outputToFile(const string &filename); // 将解决方案输出到文件
    int getSolutionCount() const;              // 获取找到的解决方案数量
};

#endif
