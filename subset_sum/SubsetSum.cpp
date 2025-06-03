#include "SubsetSum.h"
#include <iostream>
#include <iomanip>

using namespace std;

/**
 * @param targetSum Ŀ���
 * @param inputWeights �����Ȩ������
 */
SubsetSum::SubsetSum(int targetSum, const vector<int>& inputWeights) 
    : target(targetSum), weights(inputWeights), n(inputWeights.size()) {
}

/**
 * @param currentSubset ��ǰ�Ӽ�
 * @return ����Ѵ��ڷ���true�����򷵻�false
 */
bool SubsetSum::isDuplicateSolution(const vector<int>& currentSubset) {
    // ���㵱ǰ��ѡ�е�Ȩ��ֵ�Ķ��ؼ���
    vector<int> currentWeights;
    for (int i = 0; i < n; i++) {
        if (currentSubset[i] == 1) {
            currentWeights.push_back(weights[i]);
        }
    }
    sort(currentWeights.begin(), currentWeights.end());
    
    // ����Ƿ������н��Ȩ�ؼ�����ͬ
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
 * @param index ��ǰ����Ԫ�ص�����
 * @param currentSum ��ǰ��ѡԪ�ص��ܺ�
 * @param currentSubset ��ǰ�Ӽ�״̬ (1��ʾѡ�У�0��ʾδѡ)
 */
void SubsetSum::backtrack(int index, int currentSum, vector<int>& currentSubset) {
    // �����ǰ�͵���Ŀ��ֵ���ҵ�һ����
    if (currentSum == target) {
        // ����Ƿ�Ϊ�ظ���
        if (!isDuplicateSolution(currentSubset)) {
            solutions.push_back(currentSubset);
        }
        return;
    }
    // �������Ŀ��ֵ���߱���������Ԫ�أ�����
    if (currentSum > target || index >= n) {
        return;
    }
    // ѡ��ǰԪ��
    currentSubset[index] = 1;
    backtrack(index + 1, currentSum + weights[index], currentSubset);
    // ��ѡ��ǰԪ��
    currentSubset[index] = 0;
    backtrack(index + 1, currentSum, currentSubset);
}

void SubsetSum::solve() {
    vector<int> currentSubset(n, 0);
    solutions.clear();
    backtrack(0, 0, currentSubset);
    
    // ��ӿ���̨���
    if (solutions.empty()) {
        cout << "û���ҵ����������Ľ�" << endl;
    } else {
        cout << "�ҵ� " << solutions.size() << " ����" << endl;
    }
}

/**
 * @param filename ����ļ���·��
 */
void SubsetSum::outputToFile(const string& filename) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cerr << "�޷���������ļ�: " << filename << endl;
        return;
    }
    // ���û�н⣬�����ʾ��Ϣ
    if (solutions.empty()) {
        outFile << "No solution found." << endl;
        outFile.close();
        return;
    }
    //ÿ�д���һ��Ԫ�أ�ÿ�д���һ����
    for (int i = 0; i < n; i++) {
        for (size_t j = 0; j < solutions.size(); j++) {
            outFile << solutions[j][i];
            if (j < solutions.size() - 1) {
                outFile << "  ";  // �����ո�ָ�����p01_s.txt��ʽһ��
            }
        }
        outFile << endl;
    }
    outFile.close();
    cout << "�����������ļ�: " << filename << endl;
    cout << "�ҵ� " << solutions.size() << " ����" << endl;
}

/**
 * @brief �����ҵ��Ľ����������
 * @return �Ӽ�������Ľ�ĸ���
 */
int SubsetSum::getSolutionCount() const {
    return solutions.size();
}