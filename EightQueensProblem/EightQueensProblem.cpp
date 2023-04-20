// EightQueensProblem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <chrono>

/**
 * @brief - initializes a starting population with random solutions
 * @param populationNumber - how many solutions are gonna be generated
 * @return - a population
*/
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

/**
 * @brief - function for creating a new solution from two old ones
 * @param parent1 
 * @param parent2 
 * @return a new solution
*/
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
/**
 * @brief - fitness function that counts number of collisions between queens in a solution
 * @return - number of collisions , the lower the better
*/
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
/**
 * @brief  - sorting function for std::sort , sorts two elements in ascending order based on their fitness function
*/
bool sortingFunction(std::vector<int> a, std::vector<int> b)
{
    return fitnessFunction(a) < fitnessFunction(b);
}

/**
 * @brief - function that makes a new generation of solutions
 * @param oldGeneration - old generation of solutions
 * @param solutionsToUse - number indicating how many of the best solutions are going to be used for crossing
 * @param numberOfCrossings - how many crossings are gonna be made
 * @return a new generation of solutions
*/
std::vector<std::vector<int>> generateNewGeneration(std::vector<std::vector<int>>& oldGeneration, std::size_t solutionsToUse, std::size_t numberOfCrossings)
{
    std::sort(oldGeneration.begin(), oldGeneration.end(), sortingFunction);

    std::vector<std::vector<int>> newGeneration;
    
    for (std::size_t i = 0; i < numberOfCrossings; i++)
    {
        int parent1 = rand() % solutionsToUse;
        int parent2 = rand() % solutionsToUse;
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
/**
 * @brief - prints a generation on the console
 * @param gen - generation to be printed
 * @return  - returns true if a solution is valid , false otherwise
*/
bool print(std::vector<std::vector<int>> gen)
{
    for (std::vector<int> solution : gen)
    {
        std::cout << "[ ";
        for (int i : solution)
        {
            std::cout << i << ", ";
        }
        std::cout << "] - " << fitnessFunction(solution);
        if (fitnessFunction(solution) == 0)
        {
            std::cout << " This is a solution for the 8 queens problem";
            return true;
        }
        std::cout << std::endl;
    }
    return false;
}
int main()
{
    srand(time(NULL));
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::vector<int>> initial = initialGeneration(50);
    std::vector<std::vector<int>> old = initial;
    for (std::size_t i = 1; i <= 2000; i++)
    {
        std::cout << "Generation " << i << std::endl;
        std::vector<std::vector<int>> newGen = generateNewGeneration(old, 10, 20);
        if (print(newGen))
        {
            break;
        }
        old = newGen;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "\n Duration: " << duration.count();
    return 0;
}


