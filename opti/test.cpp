/**
 * @file tests.cpp
 * @brief implementation of unit tests functions of the project
 * @author Ronan Champagnat - IUT Informatique La Rochelle
 * @date 11/10/2023
 */

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <iostream>
#include <fstream>
#include <sstream>

#include "typeDef.h"
#include "functions.h"



using namespace std;

const string FILENAME_TEST = "testDataset.txt";

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define BLUE    "\033[34m"


/*
 * Utility functions for test
 */

ProcessList * generateProcessList()
{
    ProcessList * l = new ProcessList;
    l->size = 3;
    Process * p = new Process;
    p->id = 123;
    p->nbActivities = 3;
    p->firstActivity = new Activity;
    p->firstActivity->name = "a";
    p->firstActivity->time = "1";
    p->firstActivity->nextActivity = new Activity;
    p->firstActivity->nextActivity->name = "b";
    p->firstActivity->nextActivity->time = "2";
    p->firstActivity->nextActivity->nextActivity = new Activity;
    //p->lastActivity = p->firstActivity->nextActivity->nextActivity;
    p->firstActivity->nextActivity->nextActivity->name = "c";
    p->firstActivity->nextActivity->nextActivity->time = "3";
    p->firstActivity->nextActivity->nextActivity->nextActivity = nullptr;
    l->firstProcess = p;
    p = new Process;
    p->id = 456;
    p->nbActivities = 1;
    p->firstActivity = new Activity;
    //p->lastActivity = p->firstActivity;
    p->firstActivity->name = "b";
    p->firstActivity->time = "4";
    p->firstActivity->nextActivity = nullptr;
    l->firstProcess->nextProcess = p;
    p = new Process;
    p->id = 789;
    p->nbActivities = 2;
    p->firstActivity = new Activity;
    p->firstActivity->name = "a";
    p->firstActivity->time = "5";
    p->firstActivity->nextActivity = new Activity;
    //p->lastActivity = p->firstActivity->nextActivity;
    p->firstActivity->nextActivity->name = "b";
    p->firstActivity->nextActivity->time = "6";
    p->firstActivity->nextActivity->nextActivity = nullptr;
    l->firstProcess->nextProcess->nextProcess = p;
    l->firstProcess->nextProcess->nextProcess->nextProcess = nullptr;
    return l;
}

ProcessList * generateDuplicateProcessList()
{
    ProcessList * l = new ProcessList;
    l->size = 3;
    Process * p = new Process;
    p->id = 123;
    p->nbActivities = 3;
    p->firstActivity = new Activity;
    p->firstActivity->name = "a";
    p->firstActivity->time = "1";
    p->firstActivity->nextActivity = new Activity;
    p->firstActivity->nextActivity->name = "b";
    p->firstActivity->nextActivity->time = "2";
    p->firstActivity->nextActivity->nextActivity = new Activity;
    //p->lastActivity = p->firstActivity->nextActivity->nextActivity;
    p->firstActivity->nextActivity->nextActivity->name = "c";
    p->firstActivity->nextActivity->nextActivity->time = "3";
    p->firstActivity->nextActivity->nextActivity->nextActivity = nullptr;
    l->firstProcess = p;
    p = new Process;
    p->id = 456;
    p->nbActivities = 1;
    p->firstActivity = new Activity;
    //p->lastActivity = p->firstActivity;
    p->firstActivity->name = "b";
    p->firstActivity->time = "4";
    p->firstActivity->nextActivity = nullptr;
    l->firstProcess->nextProcess = p;
    p = new Process;
    p->id = 789;
    p->nbActivities = 2;
    p->firstActivity = new Activity;
    p->firstActivity->name = "a";
    p->firstActivity->time = "5";
    p->firstActivity->nextActivity = new Activity;
    //p->lastActivity = p->firstActivity->nextActivity;
    p->firstActivity->nextActivity->name = "b";
    p->firstActivity->nextActivity->time = "6";
    p->firstActivity->nextActivity->nextActivity = nullptr;
    l->firstProcess->nextProcess->nextProcess = p;
    l->firstProcess->nextProcess->nextProcess->nextProcess = nullptr;
    return l;
}

/*
 * Utility functions
 */
void test_nbOfLines()
{
    int pass = 0;
    int failed = 0;
    cout << "********* Start testing of nbOfLine() *********" << endl;
    ofstream of(FILENAME_TEST);
    of.close();
    ifstream f(FILENAME_TEST);
    if (nbOfLines(FILENAME_TEST) == 0)
    {
        cout << GREEN << "PASS" << RESET << " \t: file 0 line" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: file 0 line" << endl;
        failed++;
    }
    f.close();
    of.open(FILENAME_TEST);
    for (int i=0; i<35; i++)
    {
        of << i << endl;
    }
    of.close();
    f.open(FILENAME_TEST);
    if (nbOfLines(FILENAME_TEST) == 35)
    {
        cout << GREEN << "PASS" << RESET << " \t: file 35 lines" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: file 35 lines" << endl;
        failed++;
    }
    f.close();
    of.open(FILENAME_TEST);
    for (int i=0; i<100000; i++)
    {
        of << i << endl;
    }
    of.close();
    f.open(FILENAME_TEST);
    if (nbOfLines(FILENAME_TEST) == 100000)
    {
        cout << GREEN << "PASS" << RESET << " \t: file 100 000 lines" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: file 100 000 lines" << endl;
        failed++;
    }
    f.close();
    cout << BLUE << "Totals: " << pass << " passed, " << failed << " failed" << RESET << endl;
    cout << "********* Finished testing of nbOfLine() *********" << endl;
}

void test_printProgressBar()
{
    int pass = 0;
    int failed = 0;
    cout << "********* Start testing of printProgressBar() *********" << endl;
    stringstream output;
    streambuf* OldBuf;
    string s;
    string result[15] = {"\r[                              ] 0%",
                         "\r[##                            ] 7%",
                         "\r[####                          ] 14%",
                         "\r[######                        ] 21%",
                         "\r[########                      ] 28%",
                         "\r[##########                    ] 35%",
                         "\r[############                  ] 42%",
                         "\r[###############               ] 50%",
                         "\r[#################             ] 57%",
                         "\r[###################           ] 64%",
                         "\r[#####################         ] 71%",
                         "\r[#######################       ] 78%",
                         "\r[#########################     ] 85%",
                         "\r[###########################   ] 92%",
                         "\r[##############################] 100%\n"};
    string displayResult[15] = {"[                              ] 0%",
                                "[##                            ] 7%",
                                "[####                          ] 14%",
                                "[######                        ] 21%",
                                "[########                      ] 28%",
                                "[##########                    ] 35%",
                                "[############                  ] 42%",
                                "[###############               ] 50%",
                                "[#################             ] 57%",
                                "[###################           ] 64%",
                                "[#####################         ] 71%",
                                "[#######################       ] 78%",
                                "[#########################     ] 85%",
                                "[###########################   ] 92%",
                                "[##############################] 100%"};
    for (int i=0; i<15; i++)
    {
        OldBuf = cout.rdbuf(output.rdbuf());
        printProgressBar(i, 14);
        s=output.str();
        cout.rdbuf(OldBuf);
        if (s == result[i])
        {
            cout << GREEN << "PASS" << RESET << " \t: " << displayResult[i] << endl;
            pass++;
        }
        else
        {
            cout << RED << "FAIL!" << RESET << " \t: " << displayResult[i] << endl;
            failed++;
        }
        s="";
        output.str("");
    }
    cout << BLUE << "Totals: " << pass << " passed, " << failed << " failed" << RESET << endl;
    cout << "********* Finished testing of printProgressBar() *********" << endl;
}


/*
 * Utility functions for data structure
 */
void test_displayProcessesList()
{
    int pass = 0;
    int failed = 0;
    cout << "********* Start testing of displayProcessesList() *********" << endl;
    ProcessList * l = generateProcessList();
    stringstream output;
    streambuf* OldBuf = cout.rdbuf(output.rdbuf());
    displayProcessesList(l);
    cout.rdbuf(OldBuf);
    // Vous pouvez modifier le test en accord avec votre affichage
    if (output.str() == "Nombre de processus : 3\n123:\tNb activités : 3: a b c \n456:\tNb activités : 1: b \n789:\tNb activités : 2: a b \n\n")
    {
        cout << GREEN << "PASS" << RESET << " \t: " << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: " << endl;
        failed++;
    }
    clear(l);
    cout << BLUE << "Totals: " << pass << " passed, " << failed << " failed" << RESET << endl;
    cout << "********* Finished testing of displayProcessesList() *********" << endl;
}

void test_push_back()
{
    int pass = 0;
    int failed = 0;
    cout << "********* Start testing of push_back() *********" << endl;
    Process * p = new Process;
    Activity * a = new Activity;
    a->name = "a";
    a->time = "1";
    Activity * b = new Activity;
    b->name = "b";
    b->time = "2";
    Activity * c = new Activity;
    c->name = "c";
    c->time = "2";
    push_back(p, a);
    if (p->nbActivities == 1)
    {
        cout << GREEN << "PASS" << RESET << " \t: set nbActivities at 1 when adding a in empty list" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: set nbActivities at 1 when adding a in empty list" << endl;
        failed++;
    }
    if (p->firstActivity->name == "a")
    {
        cout << GREEN << "PASS" << RESET << " \t: add a in empty list" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: add a in empty list" << endl;
        failed++;
    }
    push_back(p, b);
    if (p->nbActivities == 2)
    {
        cout << GREEN << "PASS" << RESET << " \t: set nbActivities at 2 when adding b in (a) list" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: set nbActivities at 2 when adding b in (a) list" << endl;
        failed++;
    }
    if (p->firstActivity->nextActivity->name == "b")
    {
        cout << GREEN << "PASS" << RESET << " \t: add b in (a) list" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: add b in (a) list" << endl;
        failed++;
    }
    push_back(p, c);
    if (p->nbActivities == 3)
    {
        cout << GREEN << "PASS" << RESET << " \t: set nbActivities at 3 when adding c in (a,b) list" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: set nbActivities at 3 when adding c in (a,b) list" << endl;
        failed++;
    }
    if (p->firstActivity->nextActivity->nextActivity->name == "c")
    {
        cout << GREEN << "PASS" << RESET << " \t: add c in (a,b) list" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: add c in (a,b) list" << endl;
        failed++;
    }
    clear(p);
    cout << BLUE << "Totals: " << pass << " passed, " << failed << " failed" << RESET << endl;
    cout << "********* Finished testing of push_back() *********" << endl;
}

void test_addActivity()
{
    int pass = 0;
    int failed = 0;
    Process * p = new Process;
    cout << "********* Start testing of addActivity() *********" << endl;
    addActivity(p, "a", "1");
    if (p->nbActivities == 1)
    {
        cout << GREEN << "PASS" << RESET << " \t: set nbActivities at 1 when adding activity a,1 in empty list" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: set nbActivities at 1 when adding activity a,1 in empty list" << endl;
        failed++;
    }
    if (p->firstActivity->name == "a")
    {
        cout << GREEN << "PASS" << RESET << " \t: set name at a when adding activity a,1 in empty list" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: set name at a when adding activity a,1 in empty list" << endl;
        failed++;
    }
    if (p->firstActivity->time =="1")
    {
        cout << GREEN << "PASS" << RESET << " \t: set time at 1 when adding activity a,1 in empty list" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: set time at 1 when adding activity a,1 in empty list" << endl;
        failed++;
    }
    addActivity(p, "b", "2");
    if (p->nbActivities == 2)
    {
        cout << GREEN << "PASS" << RESET << " \t: set nbActivities at 2 when adding activity b,2 in <(a,1)> list" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: set nbActivities at 2 when adding activity b,2 in <(a,1)> list" << endl;
        failed++;
    }
    if (p->firstActivity->nextActivity->name == "b")
    {
        cout << GREEN << "PASS" << RESET << " \t: set name at b when adding activity b,2 in <(a,1)> list" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: set name at b when adding activity b,2 in <(a,1)> list" << endl;
        failed++;
    }
    if (p->firstActivity->nextActivity->time =="2")
    {
        cout << GREEN << "PASS" << RESET << " \t: set time at 2 when adding activity b,2 in <(a,1)> list" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: set time at 2 when adding activity b,2 in <(a,1)> list" << endl;
        failed++;
    }
    clear(p);
    cout << BLUE << "Totals: " << pass << " passed, " << failed << " failed" << RESET << endl;
    cout << "********* Finished testing of addActivity() *********" << endl;
}

void test_push_front()
{
    int pass = 0;
    int failed = 0;
    cout << "********* Start testing of push_front() *********" << endl;
    ProcessList * l = new ProcessList;
    Process * a = new Process;
    Process * b = new Process;
    a->id = 123;
    b->id = 456;
    push_front(l, a);
    if (l->size == 1)
    {
        cout << GREEN << "PASS" << RESET << " \t: set size at 1 when adding a process with id 123 in empty list" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: set size at 1 when adding a process with id 123 in empty list" << endl;
        failed++;
    }
    if (l->firstProcess->id == 123)
    {
        cout << GREEN << "PASS" << RESET << " \t: set id at 123 when adding a process with id 123 in empty list" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: set id at 123 when adding a process with id 123 in empty list" << endl;
        failed++;
    }
    push_front(l, b);
    if (l->size == 2)
    {
        cout << GREEN << "PASS" << RESET << " \t: set size at 2 when adding a process with id 456 in <id=123> list" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: set size at 2 when adding a process with id 456 in <id=123> list" << endl;
        failed++;
    }
    if (l->firstProcess->id == 456)
    {
        cout << GREEN << "PASS" << RESET << " \t: set id at 456 when adding a process with id 456 in <id=123> list" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: set id at 456 when adding a process with id 456 in <id=123> list" << endl;
        failed++;
    }
    clear(l);
    cout << BLUE << "Totals: " << pass << " passed, " << failed << " failed" << RESET << endl;
    cout << "********* Finished testing of push_front() *********" << endl;
}

void test_addProcess()
{
    int pass = 0;
    int failed = 0;
    cout << "********* Start testing of addProcess() *********" << endl;
    ProcessList * l = new ProcessList;
    addProcess(l, 123, "a", "1");
    if (l->size == 1)
    {
        cout << GREEN << "PASS" << RESET << " \t: set process list size at 1 when adding process (<id=123,a,1>) in empty process list" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: set process list size at 1 when adding process (<id=123,a,1>) in empty process list" << endl;
        failed++;
    }
    if (l->firstProcess->id == 123)
    {
        cout << GREEN << "PASS" << RESET << " \t: set id at 123 when adding process (<id=123,a,1>) in empty process list" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: set id at 123 when adding process (<id=123,a,1>) in empty process list" << endl;
        failed++;
    }
    if (l->firstProcess->nbActivities == 1)
    {
        cout << GREEN << "PASS" << RESET << " \t: set nbActivities at 1 when adding process (<id=123,a,1>) in empty process list" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: set nbActivities at 1 when adding process (<id=123,a,1>) in empty process list" << endl;
        failed++;
    }
    if (l->firstProcess->nextProcess == nullptr)
    {
        cout << GREEN << "PASS" << RESET << " \t: set nextProcess at nullptr when adding process (<id=123,a,1>) in empty process list" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: set nextProcess at nullptr when adding process (<id=123,a,1>) in empty process list" << endl;
        failed++;
    }
    if (l->firstProcess->firstActivity->name == "a")
    {
        cout << GREEN << "PASS" << RESET << " \t: set name at a when adding process (<id=123,a,1>) in empty process list" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: set name at a when adding process (<id=123,a,1>) in empty process list" << endl;
        failed++;
    }
    if (l->firstProcess->firstActivity->time == "1")
    {
        cout << GREEN << "PASS" << RESET << " \t: set time at 1 when adding process (<id=123,a,1>) in empty process list" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: set time at 1 when adding process (<id=123,a,1>) in empty process list" << endl;
        failed++;
    }
    clear(l);
    cout << BLUE << "Totals: " << pass << " passed, " << failed << " failed" << RESET << endl;
    cout << "********* Finished testing of addProcess() *********" << endl;
}

void test_insertProcessActivity()
{
    int pass = 0;
    int failed = 0;
    cout << "********* Start testing of insertProcessActivity() *********" << endl;
    ProcessList * l = new ProcessList;
    Process * p = new Process;
    Activity * a = new Activity;
    p->id = 123;
    p->nbActivities = 1;
    p->firstActivity = a;
    //p->lastActivity = a;
    p->firstActivity->name = "a";
    p->firstActivity->time = "1";
    p->firstActivity->nextActivity = nullptr;
    p->nextProcess = nullptr;
    l->size = 1;
    l->firstProcess = p;
    insertProcessActivity(l, 123, "b", "2");
    if (l->size == 1)
    {
        cout << GREEN << "PASS" << RESET << " \t: set process list size at 1 when adding activity (b,2) at process <id=123, (a,1)>" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: set process list size at 1 when adding activity (b,2) at process <id=123, (a,1)>" << endl;
        failed++;
    }
    if (l->firstProcess->id == 123)
    {
        cout << GREEN << "PASS" << RESET << " \t: set process id at 123 when adding activity (b,2) at process <id=123, (a,1)>" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: set process id at 123 when adding activity (b,2) at process <id=123, (a,1)>" << endl;
        failed++;
    }
    if (l->firstProcess->nbActivities == 2)
    {
        cout << GREEN << "PASS" << RESET << " \t: set nbActivites at 2 of process id=123 when adding activity (b,2) at process <id=123, (a,1)>" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: set nbActivites at 2 of process id=123 when adding activity (b,2) at process <id=123, (a,1)>" << endl;
        failed++;
    }
    if (l->firstProcess->firstActivity->nextActivity->name == "b")
    {
        cout << GREEN << "PASS" << RESET << " \t: set name at b when adding activity (b,2) at process <id=123, (a,1)>" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: set name at b when adding activity (b,2) at process <id=123, (a,1)>" << endl;
        failed++;
    }
    if (l->firstProcess->firstActivity->nextActivity->time == "2")
    {
        cout << GREEN << "PASS" << RESET << " \t: set time at 2 when adding activity (b,2) at process <id=123, (a,1)>" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: set time at 2 when adding activity (b,2) at process <id=123, (a,1)>" << endl;
        failed++;
    }
    if (l->firstProcess->firstActivity->nextActivity->nextActivity == nullptr)
    {
        cout << GREEN << "PASS" << RESET << " \t: set nextActivity at nullptr when adding activity (b,2) at process <id=123, (a,1)>" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: set nextActivity at nullptr when adding activity (b,2) at process <id=123, (a,1)>" << endl;
        failed++;
    }
    clear(l);
    cout << BLUE << "Totals: " << pass << " passed, " << failed << " failed" << RESET << endl;
    cout << "********* Finished testing of insertProcessActivity() *********" << endl;
}

void test_processExists()
{
    int pass = 0;
    int failed = 0;
    cout << "********* Start testing of processExists() *********" << endl;
    ProcessList * l = new ProcessList;
    Process * a = new Process;
    Process * b = new Process;
    a->id = 123;
    b->id = 456;
    a->nextProcess = b;
    l->firstProcess = a;
    l->size = 2;
    if (processExists(l, 789) == nullptr)
    {
        cout << GREEN << "PASS" << RESET << " \t: return nullptr when process id not found" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: return nullptr when process id not found" << endl;
        failed++;
    }
    if (processExists(l, 123) == a)
    {
        cout << GREEN << "PASS" << RESET << " \t: return first process when found" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: return first process when found" << endl;
        failed++;
    }
    if (processExists(l, 456) == b)
    {
        cout << GREEN << "PASS" << RESET << " \t: return last process when found" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: return last process when found" << endl;
        failed++;
    }
    cout << BLUE << "Totals: " << pass << " passed, " << failed << " failed" << RESET << endl;
    cout << "********* Finished testing of processExists() *********" << endl;
}


/*
 * Processes Functions
 */
void test_averageProcessLength()
{
    int pass = 0;
    int failed = 0;
    ProcessList * l = generateProcessList();
    cout << "********* Start testing of averageProcessLength() *********" << endl;
    if (averageProcessLength(l) == 2)
    {
        cout << GREEN << "PASS" << RESET << " \t: length = 2" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: length = 2" << endl;
        failed++;
    }
    clear(l);
    cout << BLUE << "Totals: " << pass << " passed, " << failed << " failed" << RESET << endl;
    cout << "********* Finished testing of averageProcessLength() *********" << endl;
}

void test_displayActivitiesList()
{
    int pass = 0;
    int failed = 0;
    cout << "********* Start testing of displayActivitiesList() *********" << endl;
    Process * p = new Process;
    p->id = 123;
    p->nbActivities = 3;
    p->firstActivity = new Activity;
    p->firstActivity->name = "a";
    p->firstActivity->time = "1";
    p->firstActivity->nextActivity = new Activity;
    p->firstActivity->nextActivity->name = "b";
    p->firstActivity->nextActivity->time = "2";
    p->firstActivity->nextActivity->nextActivity = new Activity;
    p->firstActivity->nextActivity->nextActivity->name = "c";
    p->firstActivity->nextActivity->nextActivity->time = "3";
    p->firstActivity->nextActivity->nextActivity->nextActivity = nullptr;
    stringstream output;
    streambuf* OldBuf = cout.rdbuf(output.rdbuf());
    displayActivitiesList(p);
    cout.rdbuf(OldBuf);
    // Vous pouvez modifier le test en accord avec votre affichage
    if (output.str() == "Nb activités : 3: a b c \n")
    {
        cout << GREEN << "PASS" << RESET << " \t: " << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: " << endl;
        failed++;
    }
    clear(p);
    cout << BLUE << "Totals: " << pass << " passed, " << failed << " failed" << RESET << endl;
    cout << "********* Finished testing of displayActivitiesList() *********" << endl;
}

void test_endActivities()
{
    int pass = 0;
    int failed = 0;
    cout << "********* Start testing of endActivities() *********" << endl;
    ProcessList * l = generateProcessList();
    Process * p = new Process;
    endActivities(l, p);
    if (p->nbActivities == 2)
    {
        cout << GREEN << "PASS" << RESET << " \t: number of activities found = 2" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: number of activities found = 2" << endl;
        failed++;
    }
    if (p->firstActivity->name == "b" and p->firstActivity->nextActivity->name == "c")
    {
        cout << GREEN << "PASS" << RESET << " \t: <b, c> activities found" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: <b, c> activities found" << endl;
        failed++;
    }
    cout<<"start clearing"<<endl;
    clear(l);
    cout<<"clearing done"<<endl;
    cout << BLUE << "Totals: " << pass << " passed, " << failed << " failed" << RESET << endl;
    cout << "********* Finished testing of endActivities() *********" << endl;
}

void test_extractProcesses()
{
    int pass = 0;
    int failed = 0;
    cout << "********* Start testing of extractProcesses() *********" << endl;
    ofstream of(FILENAME_TEST);
    of << "123 a 1" << endl;
    of << "456 b 2" << endl;
    of << "789 a 3" << endl;
    of << "123 b 4" << endl;
    of << "789 b 5" << endl;
    of << "789 c 6" << endl;
    of.close();
    ProcessList * l = new ProcessList;
    extractProcesses(l, FILENAME_TEST);
    if (l->size == 3 and l->firstProcess->nextProcess->nextProcess->nextProcess == nullptr)
    {
        cout << GREEN << "PASS" << RESET << " \t: Number of processes extracted" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: Number of processes extracted" << endl;
        failed++;
    }
    if (l->firstProcess->id == 789)
    {
        cout << GREEN << "PASS" << RESET << " \t: id of the first process extracted (789)" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: id of the first process extracted (789)" << endl;
        failed++;
    }
    if (l->firstProcess->nbActivities == 3)
    {
        cout << GREEN << "PASS" << RESET << " \t: size of the first process extracted (3)" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: size of the first process extracted (3)" << endl;
        failed++;
    }
    if (l->firstProcess->firstActivity->name == "a" and
        l->firstProcess->firstActivity->time == "3" and
        l->firstProcess->firstActivity->nextActivity->name == "b" and
        l->firstProcess->firstActivity->nextActivity->time == "5" and
        l->firstProcess->firstActivity->nextActivity->nextActivity->name == "c" and
        l->firstProcess->firstActivity->nextActivity->nextActivity->time == "6")
    {
        cout << GREEN << "PASS" << RESET << " \t: first process extracted <(a,3), (b,5), (c,6)>" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: first process extracted <(a,3), (b,5), (c,6)>" << endl;
        failed++;
    }
    if (l->firstProcess->nextProcess->id == 456)
    {
        cout << GREEN << "PASS" << RESET << " \t: id of the second process extracted (456)" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: id of the second process extracted (456)" << endl;
        failed++;
    }
    if (l->firstProcess->nextProcess->nbActivities == 1)
    {
        cout << GREEN << "PASS" << RESET << " \t: size of the second process extracted (1)" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: size of the second process extracted (1)" << endl;
        failed++;
    }
    if (l->firstProcess->nextProcess->firstActivity->name == "b" and
        l->firstProcess->nextProcess->firstActivity->time == "2")
    {
        cout << GREEN << "PASS" << RESET << " \t: second process extracted <(b,2)>" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: second process extracted <(b,2)>" << endl;
        failed++;
    }
    if (l->firstProcess->nextProcess->nextProcess->id == 123)
    {
        cout << GREEN << "PASS" << RESET << " \t: id of the third process extracted (123)" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: id of the third process extracted (123)" << endl;
        failed++;
    }
    if (l->firstProcess->nextProcess->nextProcess->nbActivities == 2)
    {
        cout << GREEN << "PASS" << RESET << " \t: size of the third process extracted (2)" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: size of the third process extracted (2)" << endl;
        failed++;
    }
    if (l->firstProcess->nextProcess->nextProcess->firstActivity->name == "a" and
        l->firstProcess->nextProcess->nextProcess->firstActivity->time == "1" and
        l->firstProcess->nextProcess->nextProcess->firstActivity->nextActivity->name == "b" and
        l->firstProcess->nextProcess->nextProcess->firstActivity->nextActivity->time == "4")
    {
        cout << GREEN << "PASS" << RESET << " \t: third process extracted <(a,1), (b,4)>" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: third process extracted <(a,1), (b,4)>" << endl;
        failed++;
    }
    cout << BLUE << "Totals: " << pass << " passed, " << failed << " failed" << RESET << endl;
    cout << "********* Finished testing of extractProcesses() *********" << endl;
}

void test_startActivities()
{
    int pass = 0;
    int failed = 0;
    cout << "********* Start testing of startActivities() *********" << endl;
    ProcessList * l = generateProcessList();
    Process * p = new Process;
    startActivities(l, p);
    if (p->nbActivities == 2)
    {
        cout << GREEN << "PASS" << RESET << " \t: number of activities found = 2" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: number of activities found = 2" << endl;
        failed++;
    }
    if (p->firstActivity->name == "a" and p->firstActivity->nextActivity->name == "b")
    {
        cout << GREEN << "PASS" << RESET << " \t: <a, b> activities found" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: <a, b> activities found" << endl;
        failed++;
    }
    clear(l);
    cout << BLUE << "Totals: " << pass << " passed, " << failed << " failed" << RESET << endl;
    cout << "********* Finished testing of startActivities() *********" << endl;
}

void test_variants()
{
    int pass = 0;
    int failed = 0;
    cout << "********* Start testing of test_variants() *********" << endl;
    ProcessList * l = new ProcessList;
    ProcessList * v = new ProcessList;
    l = generateProcessList();
    variants(l, v);
    if (v->size == 3)
    {
        cout << GREEN << "PASS" << RESET << " \t: size of variant without duplicated processes" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: size of variant without duplicated processes" << endl;
        failed++;
    }
    if (v->firstProcess->firstActivity->name == "a" and
        v->firstProcess->firstActivity->nextActivity->name == "b" and
        v->firstProcess->nextProcess->firstActivity->name == "b" and
        v->firstProcess->nextProcess->nextProcess->firstActivity->name == "a" and
        v->firstProcess->nextProcess->nextProcess->firstActivity->nextActivity->name == "b" and
        v->firstProcess->nextProcess->nextProcess->firstActivity->nextActivity->nextActivity->name == "c" and
        v->firstProcess->firstActivity->nextActivity->nextActivity == nullptr)
    {
        cout << GREEN << "PASS" << RESET << " \t: variants found in dataset without duplicated processes" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: variants found in dataset without duplicated processes" << endl;
        failed++;
    }
    clear(v);
    clear(l);
    l = new ProcessList;
    v = new ProcessList;
    l = generateDuplicateProcessList();
    variants(l, v);
    if (v->size == 2)
    {
        cout << GREEN << "PASS" << RESET << " \t: size of variant with duplicated processes" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: size of variant with duplicated processes" << endl;
        failed++;
    }
    if (v->firstProcess->firstActivity->name == "b" and
        v->firstProcess->nextProcess->firstActivity->name == "a" and
        v->firstProcess->nextProcess->firstActivity->nextActivity->name == "b" and
        v->firstProcess->nextProcess->firstActivity->nextActivity->nextActivity->name == "c")
    {
        cout << GREEN << "PASS" << RESET << " \t: variants found in dataset with duplicated processes" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: variants found in dataset with duplicated processes" << endl;
        failed++;
    }
    clear(v);
    clear(l);
    cout << BLUE << "Totals: " << pass << " passed, " << failed << " failed" << RESET << endl;
    cout << "********* Finished testing of test_variants() *********" << endl;
}

void test_insertActivity()
{
    int pass = 0;
    int failed = 0;
    cout << "********* Start testing of test_insertActivity() *********" << endl;
    Process * p = new Process;
    Activity * a = new Activity;
    a->name = "c";
    a->time = "1";
    insertActivity(p, a);
    if (p->nbActivities == 1)
    {
        cout << GREEN << "PASS" << RESET << " \t: size = 1 in insert activity c in empty process" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: size = 1 in insert activity c in empty process" << endl;
        failed++;
    }
    if (p->firstActivity->name == "c" and
        p->firstActivity->nextActivity == nullptr)
    {
        cout << GREEN << "PASS" << RESET << " \t: insert activity c in empty process" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: insert activity c in empty process" << endl;
        failed++;
    }
    a = new Activity;
    a->name = "a";
    a->time = "2";
    insertActivity(p, a);
    if (p->nbActivities == 2)
    {
        cout << GREEN << "PASS" << RESET << " \t: size = 2 insert activity a in process <c> (first)" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: size = 2 insert activity a in process <c> (first)" << endl;
        failed++;
    }
    if (p->firstActivity->name == "a" and
        p->firstActivity->nextActivity->name == "c" and
        p->firstActivity->nextActivity->nextActivity == nullptr)
    {
        cout << GREEN << "PASS" << RESET << " \t: insert activity a in process <c> (first)" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: insert activity a in process <c> (first)" << endl;
        failed++;
    }
    a = new Activity;
    a->name = "d";
    a->time = "3";
    insertActivity(p, a);
    if (p->nbActivities == 3)
    {
        cout << GREEN << "PASS" << RESET << " \t: size = 3 in insert activity d in process <a, c> (last)" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: size = 3 in insert activity d in process <a, c> (last)" << endl;
        failed++;
    }
    if (p->firstActivity->name == "a" and
        p->firstActivity->nextActivity->name == "c" and
        p->firstActivity->nextActivity->nextActivity->name == "d" and
        p->firstActivity->nextActivity->nextActivity->nextActivity == nullptr)
    {
        cout << GREEN << "PASS" << RESET << " \t: insert activity d in process <a, c> (last)" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: insert activity d in process <a, c> (last)" << endl;
        failed++;
    }
    a = new Activity;
    a->name = "b";
    a->time = "4";
    insertActivity(p, a);
    if (p->nbActivities == 4)
    {
        cout << GREEN << "PASS" << RESET << " \t: size = 4 in insert activity b in process <a, c, d> (middle)" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: size = 4 in insert activity b in process <a, c, d> (middle)" << endl;
        failed++;
    }
    if (p->firstActivity->name == "a" and
        p->firstActivity->nextActivity->name == "b" and
        p->firstActivity->nextActivity->nextActivity->name == "c" and
        p->firstActivity->nextActivity->nextActivity->nextActivity->name =="d" and
        p->firstActivity->nextActivity->nextActivity->nextActivity->nextActivity == nullptr)
    {
        cout << GREEN << "PASS" << RESET << " \t: insert activity b in process <a, c, d> (middle)" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: insert activity b in process <a, c, d> (middle)" << endl;
        failed++;
    }
    a = new Activity;
    a->name = "a";
    a->time = "5";
    insertActivity(p, a);
    if (p->nbActivities == 4)
    {
        cout << GREEN << "PASS" << RESET << " \t: size = 4 in insert duplicate activity a in process <a, b, c, d>" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: size = 4 in insert duplicate activity a in process <a, b, c, d>" << endl;
        failed++;
    }
    if (p->firstActivity->name == "a" and
        p->firstActivity->nextActivity->name == "b" and
        p->firstActivity->nextActivity->nextActivity->name == "c" and
        p->firstActivity->nextActivity->nextActivity->nextActivity->name =="d" and
        p->firstActivity->nextActivity->nextActivity->nextActivity->nextActivity == nullptr)
    {
        cout << GREEN << "PASS" << RESET << " \t: insert duplicate activity a in process <a, b, c, d>" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: insert duplicate activity a in process <a, b, c, d>" << endl;
        failed++;
    }
    a = new Activity;
    a->name = "c";
    a->time = "6";
    insertActivity(p, a);
    if (p->nbActivities == 4)
    {
        cout << GREEN << "PASS" << RESET << " \t: size = 4 insert duplicate activity c in process <a, b, c, d>" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: size = 4 insert duplicate activity c in process <a, b, c, d>" << endl;
        failed++;
    }
    if (p->firstActivity->name == "a" and
        p->firstActivity->nextActivity->name == "b" and
        p->firstActivity->nextActivity->nextActivity->name == "c" and
        p->firstActivity->nextActivity->nextActivity->nextActivity->name =="d" and
        p->firstActivity->nextActivity->nextActivity->nextActivity->nextActivity == nullptr)
    {
        cout << GREEN << "PASS" << RESET << " \t: insert duplicate activity c in process <a, b, c, d>" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: insert duplicate activity c in process <a, b, c, d>" << endl;
        failed++;
    }
    a = new Activity;
    a->name = "d";
    a->time = "7";
    insertActivity(p, a);
    if (p->nbActivities == 4)
    {
        cout << GREEN << "PASS" << RESET << " \t: size = 4 insert duplicate activity d in process <a, b, c, d>" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: size = 4 insert duplicate activity d in process <a, b, c, d>" << endl;
        failed++;
    }
    if (p->firstActivity->name == "a" and
        p->firstActivity->nextActivity->name == "b" and
        p->firstActivity->nextActivity->nextActivity->name == "c" and
        p->firstActivity->nextActivity->nextActivity->nextActivity->name =="d" and
        p->firstActivity->nextActivity->nextActivity->nextActivity->nextActivity == nullptr)
    {
        cout << GREEN << "PASS" << RESET << " \t: insert duplicate activity d in process <a, b, c, d>" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: insert duplicate activity d in process <a, b, c, d>" << endl;
        failed++;
    }
    clear(p);
    cout << BLUE << "Totals: " << pass << " passed, " << failed << " failed" << RESET << endl;
    cout << "********* Finished testing of test_insertActivity() *********" << endl;
}

void test_processAlreadyExists()
{
    int pass = 0;
    int failed = 0;
    cout << "********* Start testing of processAlreadyExists() *********" << endl;
    ProcessList * l = generateProcessList();
    Process * p = new Process;
    p->id = 1;
    p->nbActivities = 1;
    p->firstActivity = new Activity;
    p->firstActivity->name = "a";
    p->firstActivity->time = "11";
    p->firstActivity->nextActivity = nullptr;
    if (processAlreadyExists(l, p) == false)
    {
        cout << GREEN << "PASS" << RESET << " \t: no process found" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: no process found" << endl;
        failed++;
    }
    clear(p);
    p = new Process;
    p->id = 1;
    p->nbActivities = 3;
    p->firstActivity = new Activity;
    p->firstActivity->name = "a";
    p->firstActivity->time = "11";
    p->firstActivity->nextActivity = new Activity;
    p->firstActivity->nextActivity->name = "b";
    p->firstActivity->nextActivity->time = "12";
    p->firstActivity->nextActivity->nextActivity = new Activity;
    p->firstActivity->nextActivity->nextActivity->name = "c";
    p->firstActivity->nextActivity->nextActivity->time = "13";
    p->firstActivity->nextActivity->nextActivity->nextActivity = nullptr;
    if (processAlreadyExists(l, p) == true)
    {
        cout << GREEN << "PASS" << RESET << " \t: first process found" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: first process found" << endl;
        failed++;
    }
    clear(p);
    p = new Process;
    p->id = 4;
    p->nbActivities = 1;
    p->firstActivity = new Activity;
    p->firstActivity->name = "b";
    p->firstActivity->time = "14";
    p->firstActivity->nextActivity = nullptr;
    if (processAlreadyExists(l, p) == true)
    {
        cout << GREEN << "PASS" << RESET << " \t: process length 1 found" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: process length 1 found" << endl;
        failed++;
    }
    clear(p);
    p = new Process;
    p->id = 7;
    p->nbActivities = 2;
    p->firstActivity = new Activity;
    p->firstActivity->name = "a";
    p->firstActivity->time = "15";
    p->firstActivity->nextActivity = new Activity;
    p->firstActivity->nextActivity->name = "b";
    p->firstActivity->nextActivity->time = "16";
    p->firstActivity->nextActivity->nextActivity = nullptr;
    if (processAlreadyExists(l, p) == true)
    {
        cout << GREEN << "PASS" << RESET << " \t: last process found" << endl;
        pass++;
    }
    else
    {
        cout << RED << "FAIL!" << RESET << " \t: last process found" << endl;
        failed++;
    }
    clear(l);
    cout << BLUE << "Totals: " << pass << " passed, " << failed << " failed" << RESET << endl;
    cout << "********* Finished testing of processAlreadyExists() *********" << endl;
}
