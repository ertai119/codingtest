// sort_collection.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include <vector>
#include <iostream>

void Print(const std::vector<int>& data)
{
    for (const auto& elem : data)
    {
        std::cout << elem << std::endl;
    }
}

void InsertionSort(std::vector<int>& data)
{
    int size = data.size();
    int temp = 0;
    int j = 0;
    for (int i = 1; i < size; i++)
    {
        temp = data[i];

        for (j = i - 1; j >= 0 && temp < data[j]; j--)
        {
            data[j + 1] = data[j];
        }

        data[j + 1] = temp;
    }
}

void SelectionSort(std::vector<int>& data)
{
    int size = data.size();

    for (int i = 0; i < size - 1; i++)
    {
        int minIdx = i;

        for (int j = i; j < size; j++)
        {
            if (data[minIdx] > data[j])
            {
                minIdx = j;
            }
        }

        if (minIdx != i)
        {
            int temp = data[minIdx];
            data[minIdx] = data[i];
            data[i] = temp;
        }
    }
}

void MakeQuick(std::vector<int>& data, int left, int right)
{
    int lHold = left;
    int rHold = right;
    int pivot = data[(left + right) / 2];

    do
    {
        while (data[left] < pivot)
        {
            left++;
        }

        while (data[right] > pivot)
        {
            right--;
        }

        if (left <= right)
        {
            int temp = data[right];
            data[right] = data[left];
            data[left] = temp;
            left++;
            right--;
        }
    } while (left <= right);

    if (lHold < right)
    {
        MakeQuick(data, lHold, right);
    }

    if (rHold > left)
    {
        MakeQuick(data, left, rHold);
    }
}

void QuickSort(std::vector<int>& data)
{
    int size = data.size();
    MakeQuick(data, 0, size - 1);
}

void BubbleSort(std::vector<int>& data)
{
    int size = data.size();
    for (int i = 0 ; i < size - 1 ; i++)
    {
        for (int j = 0; j < size - 1 - i; j++)
        {
            if (data[j] < data[j + 1])
            {
                int temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }
}

struct Node
{
    int value;
    Node* left;
    Node* right;

    Node()
        : value(0)
        , left(nullptr)
        , right(nullptr)
    {}

    explicit Node(int value_)
        : value(value_)
        , left(nullptr)
        , right(nullptr)
    {}
};

void MakeNode(Node* node, int value)
{
    if (node->value > value)
    {
        if (node->left == nullptr)
        {
            Node* temp = new Node(value);
            node->left = temp;
        }
        else
        {
            MakeNode(node->left, value);
        }
    }
    else
    {
        if (node->right == nullptr)
        {
            Node* temp = new Node(value);
            node->right = temp;
        }
        else
        {
            MakeNode(node->right, value);
        }
    }
}

void ReleaseNode(Node* node)
{
    if (node->left != nullptr)
    {
        ReleaseNode(node->left);
    }

    if (node->right != nullptr)
    {
        ReleaseNode(node->right);
    }

    delete node;
}

void InorderTraversal(Node* node, std::vector<int>& out)
{
    if (node->left != nullptr)
    {
        InorderTraversal(node->left, out);
    }

    out.push_back(node->value);

    if (node->right != nullptr)
    {
        InorderTraversal(node->right, out);
    }
}

void BuildTree(std::vector<int>& data)
{
    int size = data.size();
    Node* root = new Node(*data.begin());
    for (int i = 1; i < size; i++)
    {
        MakeNode(root, data[i]);
    }

    std::vector<int> out;
    InorderTraversal(root, out);

    ReleaseNode(root);
}

void IntToStr(char* output, int outputArraySize, int input)
{
    // 이 곳을 채워 넣으세요.
    int digitCount = 0;
    int inputHolder = input;
    int maxDigit = 0;
    while (input)
    {
        input /= 10;
        maxDigit++;
    }

    input = inputHolder;
    for (int i = maxDigit - 1; i >= 0; i--)
    {
        int mod = input % 10;
        input /= 10;
        output[i] = (char)mod + '0';
    }
}

struct ListNode
{
    int value;
    ListNode* next;
    ListNode(int x, ListNode* next) : value(x), next(next)
    {}
};

ListNode* FindNthNodeFromLast(int n)
{
    ListNode* node = new ListNode(2, new ListNode(1, new ListNode(3, new ListNode(6, new ListNode(10, new ListNode(5, nullptr))))));

    int length = 0;
    ListNode* head = node;
    do
    {
        length++;
        head = head->next;
    } while (head);

    ListNode* targetNode = node;
    for (int i = 0 ; i < length; i++)
    {
        if (i == length - n )
        {
            break;
        }

        targetNode = targetNode->next;
    }

    return targetNode;
}


int main()
{
    std::vector<int> data = {4,6,2,5,3,1,7};

    BuildTree(data);

    char output[128] = "";

    //IntToStr(output, sizeof(output), 12345);
    FindNthNodeFromLast(2);

    //Print(data);

    return 0;
}

