// EightQueensProblem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>


std::vector<std::vector<int>> initialGeneration(std::size_t populationNumber)
{
    std::vector<std::vector<int>> init(populationNumber,std::vector<int>(8));

    for (std::size_t i = 0; i < populationNumber; i++)
    {
        for (std::size_t j = 0; j < 8; j++)
        {
            init[i][j] = rand() % 8 + 1;
        }
    }

    return init;
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

bool sortingFunction(std::vector<int> a, std::vector<int> b)
{
    return fitnessFunction(a) < fitnessFunction(b);
}

std::vector<std::vector<int>> generateNewGeneration(std::vector<std::vector<int>>& oldGeneration, std::size_t numberToKeep, std::size_t numberOfCrossings)
{
    std::sort(oldGeneration.begin(), oldGeneration.end(), sortingFunction);

    std::vector<std::vector<int>> newGeneration;
    
    for (std::size_t i = 0; i < numberToKeep; i++)
    {
        newGeneration.push_back(oldGeneration[i]);
    }
    for (std::size_t i = 0; i < numberOfCrossings; i++)
    {
        int parent1 = rand() % numberToKeep;
        int parent2 = rand() % numberToKeep;
        std::vector<int> child1 = reproduce(oldGeneration[parent1], oldGeneration[parent2]);
        if (rand() % 100 < 5)
        {
            int mutationIndex = rand() % child1.size();
            child1[mutationIndex] = rand() % 8 + 1;
        }
        newGeneration.push_back(child1);
        std::vector<int> child2 = reproduce(oldGeneration[parent2], oldGeneration[parent1]);
        if (rand() % 100 < 50)
        {
            int mutationIndex = rand() % child2.size();
            child2[mutationIndex] = rand() % 8 + 1;
        }
        newGeneration.push_back(child2);
    }
    
    return newGeneration;
}
bool print(std::vector<std::vector<int>> gen)
{
    for (std::vector<int> solution : gen)
    {
        std::cout << "[ ";
        for (int i : solution)
        {
            std::cout << i << ", ";
        }
        std::cout << " ] - "<< fitnessFunction(solution)  << std::endl;
        if (fitnessFunction(solution) == 0)
        {
            std::cout << "This is a solution for the 8 queens problem";
            return true;
        }
    }
    return false;
}
int main()
{
    std::vector<std::vector<int>> initial = initialGeneration(30);
    std::vector<std::vector<int>> old = initial;
    for (std::size_t i = 1; i <= 1000; i++)
    {
        std::cout << "Generation " << i << std::endl;
        std::vector<std::vector<int>> newGen = generateNewGeneration(old, 4, 13);
        if (print(newGen))
        {
            break;
        }
        old = newGen;
    }
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
