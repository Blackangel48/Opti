/**
 * @file typedef.h
 * @brief This file defines various enums and structures used in the project.
 * @author Ronan Champagnat - IUT Informatique La Rochelle
 * @date 10/11/2023
 */

#ifndef TYPEDEF_H
#define TYPEDEF_H

#include <iostream>

using namespace std;

/*
 * Il est possible d'ajouter des champs aux structures,
 * mais vous ne pouvez pas modifier ou supprimer les champs existants
 */

/*
 * Element of an activity list
 * name: the name of the activity (check-stock-availability)
 * time: the time at which the activity occurred (Tue-Oct--3-11:38:33-2023)
 */
struct Activity
{
    string name;
    string time;
    Activity * nextActivity = nullptr;
};

/*
 * Element of a process list
 * nbActivities: the number of activities in the process
 * id: the Id of the process (34594400)
 */
struct Process
{
    int nbActivities = 0;
    int id = 0;
    Activity * firstActivity = nullptr;
    Process * nextProcess = nullptr;
};

/*
 * Definition of a process list
 */
struct ProcessList
{
    int size = 0;
    Process * firstProcess = nullptr;
};

#endif // TYPEDEF_H
