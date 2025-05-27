#include "subset_sum.h"

using namespace std;

SubsetSumSolver::SubsetSumSolver() {
    weights = nullptr;
    bestSolution = nullptr;
    target = 0;
    n = 0;
    bestSum = 0;
    nodeCount = 0;
}

SubsetSumSolver::~SubsetSumSolver() {
    delete[] weights;
    delete[] bestSolution;
}

bool SubsetSumSolver::loadProblem(const string& weightFile, const string& targetFile) {
    // 读取目标值
    ifstream targetFile_stream(targetFile);
    if (!targetFile_stream.is_open()) {
        cout << "无法打开目标文件：" << targetFile << endl;
        return false;
    }
    targetFile_stream >> target;
    targetFile_stream.close();
    
    // 读取权重数组
    ifstream weightFile_stream(weightFile);
    if (!weightFile_stream.is_open()) {
        cout << "无法打开权重文件：" << weightFile << endl;
        return false;
    }
    
    // 先统计权重个数
    n = 0;
    int temp;
    while (weightFile_stream >> temp) {
        n++;
    }
    
    // 分配内存
    weights = new int[n];
    bestSolution = new bool[n];
    
    // 重新读取权重数据
    weightFile_stream.clear();
    weightFile_stream.seekg(0);
    for (int i = 0; i < n; i++) {
        weightFile_stream >> weights[i];
        bestSolution[i] = false;  // 初始化解
    }
    weightFile_stream.close();
    
    bestSum = 0;
    nodeCount = 0;
    
    cout << "成功加载问题：目标值 = " << target << ", 权重个数 = " << n << endl;
    return true;
}

void SubsetSumSolver::solve() {
    cout << "\n开始求解子集和问题..." << endl;
    
    // 创建当前解数组
    bool* currentSolution = new bool[n];
    for (int i = 0; i < n; i++) {
        currentSolution[i] = false;
    }
    
    // 开始回溯搜索
    backtrack(0, 0, currentSolution);
    
    delete[] currentSolution;
    
    cout << "求解完成！搜索了 " << nodeCount << " 个节点" << endl;
}

void SubsetSumSolver::backtrack(int index, int currentSum, bool* currentSolution) {
    nodeCount++;  // 统计搜索节点数
    
    // 如果找到更好的解，更新最优解
    if (currentSum > bestSum && currentSum <= target) {
        bestSum = currentSum;
        for (int i = 0; i < n; i++) {
            bestSolution[i] = currentSolution[i];
        }
    }
    
    // 如果找到精确解，可以提前结束
    if (currentSum == target) {
        return;
    }
    
    // 如果已经处理完所有元素，返回
    if (index >= n) {
        return;
    }
    
    // 剪枝：如果当前和已经超过目标值，不再继续
    if (currentSum > target) {
        return;
    }
    
    // 剪枝：如果无法得到更好的解，不再继续
    if (canPrune(index, currentSum)) {
        return;
    }
    
    // 选择当前元素
    currentSolution[index] = true;
    backtrack(index + 1, currentSum + weights[index], currentSolution);
    
    // 不选择当前元素
    currentSolution[index] = false;
    backtrack(index + 1, currentSum, currentSolution);
}

bool SubsetSumSolver::canPrune(int index, int currentSum) {
    // 计算剩余所有元素的和
    int remainingSum = 0;
    for (int i = index; i < n; i++) {
        remainingSum += weights[i];
    }
    
    // 如果当前和加上剩余所有元素的和都不能超过当前最优解，则剪枝
    if (currentSum + remainingSum <= bestSum) {
        return true;
    }
    
    return false;
}

void SubsetSumSolver::printResults() {
    cout << "\n========== 求解结果 ==========" << endl;
    cout << "目标值：" << target << endl;
    cout << "找到的最优解的和：" << bestSum << endl;
    
    if (bestSum == target) {
        cout << "状态：找到精确解！" << endl;
    } else {
        cout << "状态：找到近似解（差距：" << (target - bestSum) << "）" << endl;
    }
    
    cout << "搜索节点数：" << nodeCount << endl;
    
    cout << "\n选中的权重：" << endl;
    for (int i = 0; i < n; i++) {
        if (bestSolution[i]) {
            cout << "weights[" << i << "] = " << weights[i] << endl;
        }
    }
    
    cout << "\n解的二进制表示：";
    for (int i = 0; i < n; i++) {
        cout << (bestSolution[i] ? "1" : "0") << " ";
    }
    cout << endl;
    cout << "=============================" << endl;
}

bool SubsetSumSolver::checkSolution(const string& solutionFile) {
    ifstream file(solutionFile);
    if (!file.is_open()) {
        cout << "无法打开解文件：" << solutionFile << endl;
        return false;
    }
    
    // 读取标准解
    bool* standardSolution = new bool[n];
    for (int i = 0; i < n; i++) {
        int bit;
        file >> bit;
        standardSolution[i] = (bit == 1);
    }
    file.close();
    
    // 计算标准解的和
    int standardSum = 0;
    for (int i = 0; i < n; i++) {
        if (standardSolution[i]) {
            standardSum += weights[i];
        }
    }
    
    cout << "\n========== 解的验证 ==========" << endl;
    cout << "标准解的和：" << standardSum << endl;
    cout << "我们的解的和：" << bestSum << endl;
    
    if (bestSum >= standardSum) {
        cout << "验证结果：我们的解不差于标准解 ✓" << endl;
    } else {
        cout << "验证结果：我们的解不如标准解 ✗" << endl;
    }
    
    delete[] standardSolution;
    return true;
}
