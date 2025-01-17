/**
 * @file main.cpp
 * @brief
 * @author echauvie - IUT LR
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
    ProcessList * aProcessList = new ProcessList;
    aProcessList->size = 0;
    chrono::time_point<std::chrono::high_resolution_clock> startTime = getTime();
    extractProcesses(aProcessList,"largeDataset.txt");
    chrono::time_point<std::chrono::high_resolution_clock> endTime = getTime();
    cout<<"Processes extract in "<<calculateDuration(startTime,endTime)<<'s'<<endl;
    cout<<aProcessList->size<<" process add to the processList"<<endl;
    cout<<"Average process Lenght :"<<averageProcessLength(aProcessList)<<endl;

    cout<<endl<<"Activités de début :"<<endl;
    Process * activityList = new Process;
    startActivities(aProcessList,activityList);
    displayActivitiesList(activityList);
    clear(activityList);

    cout<<"Activités de fin :"<<endl;
    Process * activityList2 = new Process;
    endActivities(aProcessList,activityList2);
    displayActivitiesList(activityList2);
    clear(activityList2);

    cout<<endl<<endl;
    ProcessList * aVariant = new ProcessList;
    aVariant->size = 0;
    chrono::time_point<std::chrono::high_resolution_clock> startTime2 = getTime();
    variants(aProcessList,aVariant);
    chrono::time_point<std::chrono::high_resolution_clock> endTime2 = getTime();
    cout<<"Variants extract in "<<calculateDuration(startTime2,endTime2)<<'s'<<endl;

    cout<<endl<<"Activités de début :"<<endl;
    Process * vActivityList = new Process;
    startActivities(aVariant,vActivityList);
    displayActivitiesList(vActivityList);
    clear(vActivityList);

    cout<<"Activités de fin :"<<endl;
    Process * vActivityList2 = new Process;
    endActivities(aVariant,vActivityList2);
    displayActivitiesList(vActivityList2);
    clear(vActivityList2);

    cout<<endl<<"Clearing"<<endl;
    //clear(aVariant);
    //clear(aProcessList);
}

/**
* @brief Launches the testing suite.
* This function runs a suite of tests to validate the functions.
*/
void launchTests()
{
    cout << "********* Start testing *********" << endl << endl;
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
    int i = 0;
    int nbTest = 16;
    bool isValid = true;
    do {  //boucle de validation entre chaque test avec un tableau de pointeur sur les fonctions.
        cout<<endl<<"Passer a la suite :";
        cin>>input;
        if (input=="y" && i<nbTest)
        {
            clearConsole();
            (*(testTab[++i]))();
        }
        else if (isdigit(input[0]) && isdigit(input[1]) && stoi(input)<=nbTest)//test input = nombre
        {
            i = stoi(input);
            clearConsole();
            (*(testTab[stoi(input)]))();
        }
        else
        {
            cout<<"Bye, Have a nice day!"<<endl;
            isValid = false;
        }
    } while (isValid);

    cout << endl << "********** End testing **********" << endl << endl;
}

/**
* @brief Main function of the program.
* Entry point to process analysis. It can be used to start the analysis or run the tests.
* @return 0 for successful execution.
*/
int main()
{
    cout << "Eliott Chauviere A2" << endl<<endl;

    // Uncomment the line below to run tests
    //launchTests();
    // Start the process analysis
    launchProcessAnalysis();

    return 0;
}
