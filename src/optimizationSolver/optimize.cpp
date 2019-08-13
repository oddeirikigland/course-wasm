
#include "optimize.h"
#include "solutionCandidate.h"
#include "cost.h"
#include "feasibilityChecker.h"

float MAX_HEIGHT = 20.0;
float MIN_HEIGHT = 5.0;
float HEIGHT_INCREMENT = 1.0;
float MAX_AVERAGE_HEIGHT = 18;

SolutionCandidates increaseAndDecreaseHeightOfBuilding(int buildingIndexToChange, Buildings buildings, ObjectiveToggles objectiveToggles);
SolutionCandidates getFeasibleSolutionCandidates(const SolutionCandidates& solutionCandidates);
void addSolutionCandidatesToList(SolutionCandidates& listToBeAddedTo, const SolutionCandidates& solutionCandidatesToAdd);


Buildings optimizeBuildings(const Buildings& initialBuildings, ObjectiveToggles objectiveToggles)
{
    SolutionCandidates solutions;
    SolutionCandidate initialSolutionCandidate{createSolutionCandidateFromBuildings(initialBuildings, objectiveToggles, MAX_AVERAGE_HEIGHT)};
    solutions.push_back(initialSolutionCandidate);

    int numberOfBuildings = int (initialBuildings.size());

    for (int buildingIndex = 0; buildingIndex < numberOfBuildings; buildingIndex += 1)
    {
        SolutionCandidates solutionsWithOneBuildingHeightChanged = increaseAndDecreaseHeightOfBuilding(buildingIndex, initialBuildings, objectiveToggles);
        addSolutionCandidatesToList(solutions, solutionsWithOneBuildingHeightChanged);

        for (const SolutionCandidate& solutionCandidate: solutionsWithOneBuildingHeightChanged)
        {
            for (int otherBuildingIndex = buildingIndex + 1; otherBuildingIndex < numberOfBuildings; otherBuildingIndex += 1)
            {
                SolutionCandidates solutionsWithTwoBuildingHeightsChanged = increaseAndDecreaseHeightOfBuilding(otherBuildingIndex, solutionCandidate.buildings, objectiveToggles);
                addSolutionCandidatesToList(solutions, solutionsWithTwoBuildingHeightsChanged);
            }
        }
    }
    SolutionCandidates feasibleSolutionCandidates = getFeasibleSolutionCandidates(solutions);
    SolutionCandidate bestSolutionCandidate = getBestSolutionCandidate(feasibleSolutionCandidates);
    return bestSolutionCandidate.buildings;
}

void addSolutionCandidatesToList(SolutionCandidates& listToBeAddedTo, const SolutionCandidates& solutionCandidatesToAdd)
{
    for (const SolutionCandidate& solutionCandidateToAdd: solutionCandidatesToAdd)
    {
        listToBeAddedTo.push_back(solutionCandidateToAdd);
    }
}

Buildings changeHeightOfBuilding(Buildings buildings, int buildingIndexToChange, float heightIncrement)
{
    Buildings updatedBuildings = buildings;
    updatedBuildings[buildingIndexToChange].height = buildings[buildingIndexToChange].height + heightIncrement;
    return updatedBuildings;
}

SolutionCandidates getFeasibleSolutionCandidates(const SolutionCandidates& solutionCandidates)
{
    SolutionCandidates feasibleSolutionCandidates;
    for (const SolutionCandidate& solutionCandidate: solutionCandidates)
    {
        if (solutionCandidate.isFeasible)
        {
            feasibleSolutionCandidates.push_back(solutionCandidate);
        }
    }
    return feasibleSolutionCandidates;
}


SolutionCandidates increaseAndDecreaseHeightOfBuilding(int buildingIndexToChange, Buildings buildings, ObjectiveToggles objectiveToggles)
{
    SolutionCandidates potentialSolutionCandidates;
    float currentHeight = buildings[buildingIndexToChange].height;
    if (currentHeight <= MAX_HEIGHT + HEIGHT_INCREMENT)
    {
        Buildings buildingsWithIncreasedHeight = changeHeightOfBuilding(buildings, buildingIndexToChange, HEIGHT_INCREMENT);
        potentialSolutionCandidates.push_back({createSolutionCandidateFromBuildings(buildingsWithIncreasedHeight, objectiveToggles, MAX_AVERAGE_HEIGHT)});
    }
    if (currentHeight >= MIN_HEIGHT - HEIGHT_INCREMENT)
    {
        Buildings buildingsWithIncreasedHeight = changeHeightOfBuilding(buildings, buildingIndexToChange, -HEIGHT_INCREMENT);
        potentialSolutionCandidates.push_back({createSolutionCandidateFromBuildings(buildingsWithIncreasedHeight, objectiveToggles, MAX_AVERAGE_HEIGHT)});
    }
    return potentialSolutionCandidates;
}
