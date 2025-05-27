#include "subset_sum.h"

using namespace std;

int main() {
    cout << "=== 子集和问题求解器 - 回溯法 ===" << endl;
    cout << "算法设计与分析课程作业" << endl;
    cout << "使用Florida State University数据集" << endl;
    
    SubsetSumSolver solver;
    
    // 测试P01问题（小规模，适合演示）
    cout << "\n>>> 测试问题P01 <<<" << endl;
    if (solver.loadProblem("../4.2 Florida State University/p01_w.txt", 
                          "../4.2 Florida State University/p01_c.txt")) {
        solver.solve();
        solver.printResults();
        solver.checkSolution("../4.2 Florida State University/p01_s.txt");
    }
    
    // 测试P04问题
    cout << "\n\n>>> 测试问题P04 <<<" << endl;
    SubsetSumSolver solver2;
    if (solver2.loadProblem("../4.2 Florida State University/p04_w.txt", 
                           "../4.2 Florida State University/p04_c.txt")) {
        solver2.solve();
        solver2.printResults();
        solver2.checkSolution("../4.2 Florida State University/p04_s.txt");
    }
    
    // 测试P06问题（很小的问题，容易理解）
    cout << "\n\n>>> 测试问题P06 <<<" << endl;
    SubsetSumSolver solver3;
    if (solver3.loadProblem("../4.2 Florida State University/p06_w.txt", 
                           "../4.2 Florida State University/p06_c.txt")) {
        solver3.solve();
        solver3.printResults();
        solver3.checkSolution("../4.2 Florida State University/p06_s.txt");
    }
    
    cout << "\n=== 算法总结 ===" << endl;
    cout << "1. 回溯法：系统地尝试所有可能的选择" << endl;
    cout << "2. 剪枝优化：" << endl;
    cout << "   - 当前和超过目标值时停止搜索" << endl;
    cout << "   - 当无法得到更好解时停止搜索" << endl;
    cout << "3. 时间复杂度：O(2^n) 最坏情况" << endl;
    cout << "4. 空间复杂度：O(n) 递归栈空间" << endl;
    
    cout << "\n编译运行方法：" << endl;
    cout << "g++ -o subset_sum subset_sum.cpp main.cpp" << endl;
    cout << "./subset_sum" << endl;
    
    return 0;
}
