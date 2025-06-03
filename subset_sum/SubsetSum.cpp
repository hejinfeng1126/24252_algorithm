#include "SubsetSum.h"
#include <iostream>
#include <iomanip>

using namespace std;

/**
 * @param targetSum 目标和
 * @param inputWeights 输入的权重数组
 */
SubsetSum::SubsetSum(int targetSum, const vector<int>& inputWeights) 
    : target(targetSum), weights(inputWeights), n(inputWeights.size()) {
}

/**
 * @param currentSubset 当前子集
 * @return 如果已存在返回true，否则返回false
 */
bool SubsetSum::isDuplicateSolution(const vector<int>& currentSubset) {
    // 计算当前解选中的权重值的多重集合
    vector<int> currentWeights;
    for (int i = 0; i < n; i++) {
        if (currentSubset[i] == 1) {
            currentWeights.push_back(weights[i]);
        }
    }
    sort(currentWeights.begin(), currentWeights.end());
    
    // 检查是否与已有解的权重集合相同
    for (const auto& solution : solutions) {
        vector<int> solutionWeights;
        for (int i = 0; i < n; i++) {
            if (solution[i] == 1) {
                solutionWeights.push_back(weights[i]);
            }
        }
        sort(solutionWeights.begin(), solutionWeights.end());
        
        if (currentWeights == solutionWeights) {
            return true;
        }
    }
    return false;
}

/**
 * @param index 当前处理元素的索引
 * @param currentSum 当前已选元素的总和
 * @param currentSubset 当前子集状态 (1表示选中，0表示未选)
 */
void SubsetSum::backtrack(int index, int currentSum, vector<int>& currentSubset) {
    // 如果当前和等于目标值，找到一个解
    if (currentSum == target) {
        // 检查是否为重复解
        if (!isDuplicateSolution(currentSubset)) {
            solutions.push_back(currentSubset);
        }
        return;
    }
    // 如果超过目标值或者遍历完所有元素，回溯
    if (currentSum > target || index >= n) {
        return;
    }
    // 选择当前元素
    currentSubset[index] = 1;
    backtrack(index + 1, currentSum + weights[index], currentSubset);
    // 不选择当前元素
    currentSubset[index] = 0;
    backtrack(index + 1, currentSum, currentSubset);
}

void SubsetSum::solve() {
    vector<int> currentSubset(n, 0);
    solutions.clear();
    backtrack(0, 0, currentSubset);
    
    // 添加控制台输出
    if (solutions.empty()) {
        cout << "没有找到满足条件的解" << endl;
    } else {
        cout << "找到 " << solutions.size() << " 个解" << endl;
    }
}

/**
 * @param filename 输出文件的路径
 */
void SubsetSum::outputToFile(const string& filename) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cerr << "无法创建输出文件: " << filename << endl;
        return;
    }
    // 如果没有解，输出提示信息
    if (solutions.empty()) {
        outFile << "No solution found." << endl;
        outFile.close();
        return;
    }
    //每行代表一个元素，每列代表一个解
    for (int i = 0; i < n; i++) {
        for (size_t j = 0; j < solutions.size(); j++) {
            outFile << solutions[j][i];
            if (j < solutions.size() - 1) {
                outFile << "  ";  // 两个空格分隔，与p01_s.txt格式一致
            }
        }
        outFile << endl;
    }
    outFile.close();
    cout << "结果已输出到文件: " << filename << endl;
    cout << "找到 " << solutions.size() << " 个解" << endl;
}

/**
 * @brief 返回找到的解决方案数量
 * @return 子集和问题的解的个数
 */
int SubsetSum::getSolutionCount() const {
    return solutions.size();
}