// Graph matching -  This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

struct GraphData {
    int numNodes;
    int numEdges;
    int* src;
    int* dst;
    int* weight;
};

void check_handshaking_gpu(int* strongNeighbor, int* matches, int numNodes);
void markFilterEdges_gpu(int* src, int* dst, int* matches, int* keepEdges, int numEdges);
void exclusive_prefix_sum_gpu(int* oldSum, int* newSum, int distance, int numElements);

void main()
{
    GraphData test;
    test.numEdges = 5;
    test.numNodes = 12;
    test.src = new int[12];
    test.src[0] = 0;
    test.src[1] = 0;
    test.src[2] = 1;
    test.src[3] = 1;
    test.src[4] = 1;
    test.src[5] = 2;
    test.src[6] = 2;
    test.src[7] = 3;
    test.src[8] = 3;
    test.src[9] = 3;
    test.src[10] = 4;
    test.src[11] = 4;
    test.dst = new int[12];
    test.dst[0] = 1;
    test.dst[1] = 4;
    test.dst[2] = 0;
    test.dst[3] = 2;
    test.dst[4] = 3;
    test.dst[5] = 1;
    test.dst[6] = 3;
    test.dst[7] = 1;
    test.dst[8] = 2;
    test.dst[9] = 4;
    test.dst[10] = 0;
    test.dst[11] = 3;
    test.weight = new int[12];
    std::cout << "check_handshaking_gpu method\n";
    int* mat = new int[test.numEdges];
    int* strongNei = new int[test.numEdges];
    strongNei[0] = 1;
    strongNei[1] = 3;
    strongNei[2] = 3;
    strongNei[3] = 2;
    strongNei[4] = 3;
    std::cout << " strongNei: \n";
    for (int i = 0; i < test.numEdges; i++)
        std::cout << strongNei[i] << " ";
    std::cout << "\n";
    for (int i = 0; i < test.numEdges; i++)
        mat[i] = -1;
    check_handshaking_gpu(strongNei, mat, test.numEdges);
    std::cout << " matches: \n";
    for(int i=0;i<test.numEdges;i++)
        std::cout << mat[i] << " ";
    std::cout << "\n";
    std::cout << "markFilterEdges_gpu method\n";
    int* keepE = new int[12];
    markFilterEdges_gpu(test.src, test.dst, mat, keepE, test.numNodes);
    std::cout << " KeepE: \n";
    for (int i = 0; i < test.numNodes; i++)
        std::cout << keepE[i] << " ";
    std::cout << "\n";

    std::cout << "exclusive_prefix_sum_gpu method\n";
    std::cout << "I need more parameters\n";
}

void check_handshaking_gpu(int* strongNeighbor, int* matches, int numNodes)
{
    for (int i = 0; i < numNodes; i++)
    {
        if (i == strongNeighbor[strongNeighbor[i]])
            matches[i] = strongNeighbor[i];
    }
}

void markFilterEdges_gpu(int* src, int* dst, int* matches, int* keepEdges, int numEdges)
{
    for (int i = 0; i < numEdges; i++)
    {
        if (matches[src[i]] == -1 && matches[dst[i]] == -1)
            keepEdges[i] = 1;
        else
            keepEdges[i] = 0;
    }
}
void exclusive_prefix_sum_gpu(int* oldSum, int* newSum, int distance, int numElements)
{
    int step = distance + 1;
    int i = 0;
    for (int j = 0; j < numElements; j++)
    {
        newSum[j] = 0;
    }
    for (int j = 1; j < numElements; j++)
    {
        i = 0;
        while (i < numElements && i<j)
        {
            newSum[j] += oldSum[i];
            i += step;
        }
    }
}