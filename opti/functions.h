/**
 * @file functions.h
 * @brief Declaration of the functions of the project
 * @author Ronan Champagnat - IUT Informatique La Rochelle
 * @date 10/11/2023
 */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "typeDef.h"
#include <iostream>
#include <chrono>

using namespace std;

/*
 * Chronographe functions
 */

/**
 * @brief Get the current time
 * @return the current time with the higher resolution
 */
chrono::time_point<std::chrono::high_resolution_clock> getTime();

/**
 * @brief Calculate the duration between to times in secondes
 * @param: the start time
 * @param: the end time
 * @return the duration
 */
double calculateDuration(chrono::time_point<std::chrono::high_resolution_clock> t1, chrono::time_point<std::chrono::high_resolution_clock> t2);


/*
 * Utility functions
 */

/**
 * @brief Count the number of lines of a file
 * @param: string, the file name
 * @return an int corresponding to the number of lines
 */
int nbOfLines(string aFileName);

/**
 * @brief Clears the console screen based on the operating system.
 *
 * This function clears the console screen by executing system commands specific to the operating system.
 * On Windows, it uses the "cls" command, while on Linux and macOS, it uses the "clear" command.
 * If the system command fails, an error message is displayed in the console.
 */
void clearConsole();

/**
 * @brief Display a progress bar
 * @param: int, the current value of the progression
 * @param: int, the max value
 */
void printProgressBar(int nb, int max);


/*
 * Utility functions for data structure
 */

/**
 * @brief Delete a process. Free the memory occupied by each Activity * then the Process *
 * @param: Process *, a list to delete
 */
void clear(Process * aList);

/**
 * @brief Delete a process list. Free the memory occupied by each element Process * then the ProcessList *
 * @param: ProcessList *, a process list to delete
 */
void clear(ProcessList * aList);

/**
 * @brief Display a list of activities of a process
 * @param: a Process*
 */
void displayActivitiesList(Process * aProcess);

/**
 * @brief display a list of processes from a process list
 * @param: a List*
 */
void displayProcessesList(ProcessList * aList);

/**
 * @brief Add an activity at the end of an activity list
 * @param: a Process*
 * @param: an Activity*
 */
void push_back(Process * aProcess, Activity* anActivity);

/**
 * @brief Add an activity to a process
 * @param: Process*, a process
 * @param: string, an activity name
 * @param: string a timestamp
 */
void addActivity(Process * aProcess, string anActivityName, string aTime);

/**
 * @brief Add a process to a process list at the top/head of the list
 * @param: ProcessList *, a process list
 * @param: Process*, the process to add
 */
void push_front(ProcessList * aList, Process * aProcess);

/**
 * @brief Add a new process, with its first activity to a process list
 * @param: ProcessList *, a process list
 * @param: int, a process id
 * @param: string, the first activity name
 * @param: string, the first timestamp
 */
void addProcess(ProcessList * aList, int aProcessId, string anActivityName, string aTime);

/**
 * @brief Add a new activity of a process registered in the process list
 * @param: ProcessList *, a process list
 * @param: int, a process id
 * @param: string, the activity name
 * @param: string, the timestamp
 */
void insertProcessActivity(ProcessList * aList, int aProcessId, string anActivityName, string aTime);

/**
 * @brief Determine if a process id is already in the process list
 * @param: ProcessList *, a process list
 * @param: int, the process id
 * @return a Process * if the id already exists, nullptr otherwise
 */
Process * processExists(ProcessList * aList, int aProcessId);


/*
 * Processes Functions
 */

/**
 * @brief Calculate the average number of activities in the processes
 * in a process list
 * @param: ProcessList *, a process list
 */
double averageProcessLength(ProcessList * aList);

/**
 * @brief Determine the set of end activities of process list
 * @param: ProcessList *, the process list
 * @param: Process *, the list of start activities
 */
void endActivities(ProcessList * processList, Process * activityList);

/**
 * @brief Extract all the processes from a file and store them
 * in a given process list
 * @param: ProcessList *, the process list,
 * @param: string, the file name
 */
void extractProcesses(ProcessList* aList, string fileName);

/**
 * @brief Determine the set of start activities of process list
 * @param: ProcessList *, the process list
 * @param: Process *, the list of start activities
 */
void startActivities(ProcessList * processList, Process * activityList);

/**
 * @brief Extract the variant of a process list
 * A variant is a unique variation of a business process
 * @param: ProcessList *, a process list
 * @param: ProcessList *, the resulting list of variants
 */
void variants(ProcessList * aProcessList, ProcessList * aVariant);

/**
 * @brief Insert a sorted, unduplicated activity in a process
 * @param: Process *, the process
 * @param : Activity *, the activity
 */
void insertActivity(Process * aProcess, Activity* anActivity);

/**
 * @brief Determine if a process already exists in a process list
 * @param: ProcessList *, a process list
 * @param: Process *, the process
 * @return true if the process is found
 */
bool processAlreadyExists(ProcessList * aProcessList, Process * aProcess);

// Functions ADD by the student
/**
 * @brief addSummary: Crée un sommaire, pointe vers un process puis ce positionne au début de la liste comme un push_front
 * @param aList ProcessList d'extraction
 * @param aProcess Le Process pointé
 */
void addSummary(ProcessList * aList, Process * aProcess);

/**
 * @brief pushSummaryFront: ajoute un processus au début du sommaire correspondant
 * @param aList ProcessList
 * @param aProcess Le Processus à positionner
 */
void pushSummaryFront(ProcessList * aList, Process * aProcess);

/**
 * @brief summarySame: Renvoie le sommaire correspondant à l'ID passé en paramètre
 * @param aList ProcessList
 * @param aProcessId L'ID de référence pour le sommaire
 * @return renvoie l'adresse du sommaire correspondant
 */
SummaryCell * summarySame(ProcessList * aList, int aProcessId);

/**
 * Cherche si le processus existe déjà dans la liste donné comme processExists mais voyage par Sommaire(Summary).
 * Renvoie le pointeur du processus ou nullptr s'il n'existe pas
 */
Process * processSummaryExists(ProcessList * aList,  int aProcessId);

/**
 * @brief firstNumberId : Renvoie les premiers chiffres de l'ID donné
 * @param aProcessId ID donné à manipulé
 * @return Renvoie les n premiers chiffres de l'ID
 */
int firstNumberId(int aProcessId);

/**
 * @brief Construit un pointeur de type Process, positionne le champ id à la valeur donnée
 * puis utilise addActivity pour ajouter l'activité passée en paramètre au processus créé
 * puis utilise push_front par Sommaire pour ajouter le processus à la liste de processus
 */
void addProcessSummary(ProcessList * aList, int aProcessId, string anActivityName, string aTime);

/**
 * @brief displaySummary : Affiche la liste des sommaires créés
 * @param aList
 */
void displaySummary(ProcessList * aList);


#endif // FUNCTIONS_H
