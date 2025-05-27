#ifndef SUBSET_SUM_H
#define SUBSET_SUM_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class SubsetSumSolver {
private:
    int* weights;           // 权重数组
    int target;             // 目标值
    int n;                  // 权重数量
    bool* bestSolution;     // 最优解
    int bestSum;            // 最优解的和
    int nodeCount;          // 搜索节点计数
    
    // 回溯算法核心函数
    void backtrack(int index, int currentSum, bool* currentSolution);
    
    // 剪枝函数 - 检查是否可以剪枝
    bool canPrune(int index, int currentSum);

public:
    SubsetSumSolver();
    ~SubsetSumSolver();
    
    // 从文件加载问题数据
    bool loadProblem(const string& weightFile, const string& targetFile);
    
    // 求解子集和问题
    void solve();
    
    // 打印结果
    void printResults();
    
    // 验证给定的解是否正确
    bool checkSolution(const string& solutionFile);
};

#endif // SUBSET_SUM_H
