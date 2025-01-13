/**
 * @file test.h
 * @brief Declaration of test functions to test the implemented functions
 * in functions.cpp file
 * @author Ronan Champagnat - IUT Informatique La Rochelle
 * @date 10/11/2023
 */

#ifndef TESTS_H
#define TESTS_H

/*
 * Utility functions
 */
/**
 * @brief unit test function for nbOfLines
 * Generates files of various size and check if nbOfLines
 * returns the correct values.
 */
void test_nbOfLines();
/**
 * @brief unit test function for printProgressBar
 * Generate a progress bar and check if it is correctly displayed
 */
void test_printProgressBar();

/*
 * Utility functions for data structure
 */
/**
 * @brief unit test function for displayProcessesList
 * Generate a list and check if it is correctly displayed
 */
void test_displayProcessesList();
/**
 * @brief unit test for push_back
 * Check if an activity is correctly added at the end of a process and
 * if the size of the list is correctly updated
 */
void test_push_back();
/**
 * @brief unit test for addActivity
 * Check if an activity is correctly created and added at the end of a process and
 * if the size of the list is correctly updated
 */
void test_addActivity();
/**
 * @brief unit test for push_front
 * Test if a process is correctly added at the head of a process list and if the size
 * of the process list is correctly updated
 */
void test_push_front();
/**
 * @brief unit test for addProcess
 * Test if a process is correctly created and added at the head of a process list and if the size
 * of the process list is correctly updated
 */
void test_addProcess();
/**
 * @brief unit test for insertProcessActivity
 * Test if an activity is correctly created and added at the end of the corresponding
 * process (with a corresponding id)
 */
void test_insertProcessActivity();
/**
 * @brief unit test for processExists
 * Test if processExists function can find correctly process id in a process list
 */
void test_processExists();


/*
 * Processes Functions
 */
/**
 * @brief unit test ofr averageProcessLength
 * Test if the average size of process in a process list is calculated correctly
 */
void test_averageProcessLength();
/**
 * @brief unit test for displayActivitiesList
 * Test if a process is correctly displayed
 */
void test_displayActivitiesList();
/**
 * @brief unit test for endActivities
 * Test if endActivities function return a correct list of end
 * activities (size and element) for a given process list
 */
void test_endActivities();
/**
 * @brief unit test for extractProcesses
 * Test if the function extract a correct process list
 * from a given file
 */
void test_extractProcesses();
/**
 * @brief unit test for startActivities
 * Test if startActivities function return a correct list of start
 * activities (size and element) for a given process list
 */
void test_startActivities();
/**
 * @brief unit test for variants
 * Test if the list of variants is correctly updated for a given
 * process list and a given process.
 */
void test_variants();
/**
 * @brief unit test for insertActivity
 * Test if an activity is correctly inserted (i.e. sorted by activity name
 * with no duplicate)
 */
void test_insertActivity();
/**
 * @brief unit test for processAlreadyExists
 * Test if the function can determine if a given process already exists in
 * given process list
 */
void test_processAlreadyExists();


#endif // TESTS_H
