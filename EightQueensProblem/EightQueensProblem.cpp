// EightQueensProblem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

bool sortingFunction(std::vector<int> a, std::vector<int> b)
{
    return fitnessFunction(a) < fitnessFunction(b);
}

std::vector<int> reproduce(std::vector<int>& parent1, std::vector<int>& parent2)
{
    int split = parent1.size() / 2;

    std::vector<int> child(8);

    for (int i = 0; i < split; i++)
    {
        child[i] = parent1[i];
    }

    for (int i = split; i < 8; i++)
    {
        child[i] = parent2[i];
    }
    return child;
}

int fitnessFunction(std::vector<int>& solution)
{
    std::size_t collisions = 0;
    for (std::size_t i = 0; i < solution.size(); i++)
    {
        for (std::size_t j = i + 1;  j < solution.size(); j++)
        {
            if (solution[i] == solution[j] || abs(solution[i] - solution[j]) == j - i) collisions++;
        }
    }

    return collisions;
}

std::vector<std::vector<int>> generateNewGeneration(std::vector<std::vector<int>>& oldGeneration, std::size_t numberToKeep)
{
    std::sort(oldGeneration.begin(), oldGeneration.end(), sortingFunction);

    std::vector<std::vector<int>> newGeneration;
    for (std::size_t i = 0; i < numberToKeep; i++)
    {
        newGeneration.push_back(oldGeneration[i]);
    }

    for(auto parent)
}
int main()
{
    std::vector<int> v1{ 3, 6, 3, 1, 4, 7, 5, 2 };
    std::vector<int> v2{ 8,7,6,5,4,3,2,1 };
    std::vector<int> child = reproduce(v1, v2);
    std::cout << fitnessFunction(v1);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
