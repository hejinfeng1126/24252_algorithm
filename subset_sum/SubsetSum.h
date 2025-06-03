#ifndef SUBSETSUM_H
#define SUBSETSUM_H

#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

class SubsetSum {
private:
    vector<int> weights;              // �����Ȩ������
    int target;                       // Ŀ���
    int n;                           // Ȩ������Ĵ�С
    vector<vector<int>> solutions;   // �洢�����ҵ��Ľ������
    /**
     * �����㷨
     * @param index ��ǰ�����Ԫ������
     * @param currentSum ��ǰ�Ӽ��ĺ�
     * @param currentSubset ��ǰ���ڹ������Ӽ�
     */
    void backtrack(int index, int currentSum, vector<int>& currentSubset);
    bool isDuplicateSolution(const vector<int> &currentSubset);
public:
    /**
     * ���캯��
     * @param targetSum Ŀ���
     * @param inputWeights �����Ȩ������
     */
    SubsetSum(int targetSum, const vector<int>& inputWeights);
    void solve();                              // ��ʼ����Ӽ�������
    void outputToFile(const string &filename); // ���������������ļ�
    int getSolutionCount() const;              // ��ȡ�ҵ��Ľ����������
};

#endif
