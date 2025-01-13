/**
 * @file main.cpp
 * @brief
 * @author Ronan Champagnat - IUT Informatique
 * @date 10/11/2023
 */


#include <iostream>

using namespace std;

#include "typeDef.h"
#include "functions.h"
#include "test.h"
#include <fstream>


/**
* @brief Function to execute the analysis of the log file.
**/
void launchProcessAnalysis()
{
    ProcessList aProcessList;
    aProcessList.size = 0;
    chrono::time_point<std::chrono::high_resolution_clock> startTime = getTime();
    extractProcesses(&aProcessList,"smallDataset.txt");
    chrono::time_point<std::chrono::high_resolution_clock> endTime = getTime();
    cout<<"Processes extract in "<<calculateDuration(startTime,endTime)<<'s'<<endl;
}

/**
* @brief Launches the testing suite.
* This function runs a suite of tests to validate the functions.
*/
void launchTests()
{
    cout << endl << "********* Start testing *********" << endl << endl;
    // ProcessList * l = new ProcessList;
    // l->size = 3;
    // Process * p = new Process;
    // p->id = 123;
    // p->nbActivities = 3;
    // p->firstActivity = new Activity;
    // p->firstActivity->name = "a";
    // p->firstActivity->time = "1";
    // p->firstActivity->nextActivity = new Activity;
    // p->firstActivity->nextActivity->name = "b";
    // p->firstActivity->nextActivity->time = "2";
    // p->firstActivity->nextActivity->nextActivity = new Activity;
    // p->firstActivity->nextActivity->nextActivity->name = "c";
    // p->firstActivity->nextActivity->nextActivity->time = "3";
    // p->firstActivity->nextActivity->nextActivity->nextActivity = nullptr;
    // l->firstProcess = p;
    // p = new Process;
    // p->id = 456;
    // p->nbActivities = 1;
    // p->firstActivity = new Activity;
    // p->firstActivity->name = "b";
    // p->firstActivity->time = "4";
    // p->firstActivity->nextActivity = nullptr;
    // l->firstProcess->nextProcess = p;
    // p = new Process;
    // p->id = 789;
    // p->nbActivities = 2;
    // p->firstActivity = new Activity;
    // p->firstActivity->name = "a";
    // p->firstActivity->time = "5";
    // p->firstActivity->nextActivity = new Activity;
    // p->firstActivity->nextActivity->name = "b";
    // p->firstActivity->nextActivity->time = "6";
    // p->firstActivity->nextActivity->nextActivity = nullptr;
    // l->firstProcess->nextProcess->nextProcess = p;
    // l->firstProcess->nextProcess->nextProcess->nextProcess = nullptr;
    // displayProcessesList(l);
    // test_displayProcessesList();
    // test_displayActivitiesList();
    //test_insertActivity();
    //test_printProgressBar();


    // test_push_back();
    // test_push_front();
    // test_addProcess();
    // test_addActivity();

    //test_processExists();

    string input;
    void (*testTab[])() = {test_nbOfLines,
                           test_printProgressBar,
                           test_displayProcessesList,
                           test_push_back,
                           test_addActivity,
                           test_push_front,
                           test_addProcess,
                           test_insertProcessActivity,
                           test_processExists,
                           test_averageProcessLength,
                           test_displayActivitiesList,
                           test_endActivities,
                           test_extractProcesses,
                           test_startActivities,
                           test_variants,
                           test_insertActivity,
                           test_processAlreadyExists
                           };

    for (int i = 0; i < 17; ++i) {//boucle de validation entre chaque test avec un tableau de pointeur sur les fonctions.
        clearConsole();
        (*(testTab[i]))();
        cout<<endl<<"Passer a la suite?";
        cin>>input;
        if (input!="y")
            break;
    }

    //test_extractProcesses();
    cout << endl << "********** End testing **********" << endl << endl;
}

/**
* @brief Main function of the program.
* Entry point to process analysis. It can be used to start the analysis or run the tests.
* @return 0 for successful execution.
*/
int main()
{
    cout << "Eliott Chauviere A2" << endl;

    // Uncomment the line below to run tests
    launchTests();
    // Start the process analysis
    //launchProcessAnalysis();

    return 0;
}
