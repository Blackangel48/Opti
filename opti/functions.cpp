/**
 * @file functions.cpp
 * @brief Implementation of the project functions
 * @author Ronan Champagnat - IUT Informatique La Rochelle
 * @date 10/11/2023
 */

#include "typeDef.h"
#include "functions.h"

#include <iostream>
#include <fstream>

using namespace std;


/*
 * Chronographe functions
 */

/**
 * @brief Retourne l'heure courante avec une grande résolution
 */
chrono::time_point<std::chrono::high_resolution_clock> getTime()
{
    return chrono::high_resolution_clock::now();
}

/**
 * @brief Retourne la différence entre deux heures données et convertit en secondes.
 */
double calculateDuration(chrono::time_point<std::chrono::high_resolution_clock> start, chrono::time_point<std::chrono::high_resolution_clock> end)
{
    return (double)chrono::duration_cast<chrono::nanoseconds>(end - start).count() / 1000000000;
}


/*
 * Utility functions
 */

/**
 * @brief Ouvre le fichier passer en paramètres et le parcours intégralement en comptant le nombre
 * de ligne. Le fichier est fermé avant de retourner le nombre de lignes trouvé.
 */
int nbOfLines(string aFileName)
{
    ifstream iFile(aFileName);
    if (iFile.is_open())
    {
        int nbLines = 0;
        while (!iFile.eof())
        {
            iFile.ignore(256,'\n');
            nbLines++;
        }
        nbLines--;
        return nbLines;
    }
    else
    {
        cout<<"erreur d'ouverture du fichier"<<endl;
        return 0;
    }
}

void clearConsole() {
#ifdef _WIN32
    // Command for Windows
    if (system("cls") != 0) {
        std::cerr << "Failed to clear console on Windows.\n";
    }
#else
    // Command for Linux/macOS
    if (system("clear") != 0) {
        std::cerr << "Failed to clear console on Unix-like system.\n";
    }
#endif
}

/**
 * @brief Affiche une barre de progression au format :
 * [############                  ] 42%
 * Utilisation de \r (voir premier cours de Dév)
 * le nombre de # est proportionnel nb (nombre d'itérations) par rapport à max
 * le pourcentage est la proportion de nb sur max
 */
void printProgressBar(int nb, int max)
{
    string out = "";
    int prct;
    prct = nb * 100 / max;
    int nbBarre = prct * 0.3;
    for (int i=0; i<nbBarre; i++)
    {
        out += "#"; //optimisation en mettant '#' au lieu de "#" ?
    }
    for (int i=0; i<(30-nbBarre); i++)
    {
        out += " ";
    }
    if (prct != 100)
        cout<<"\r["<<out<<"] "<<prct<<'%';
    else
        cout<<"\r["<<out<<"] "<<prct<<'%'<<endl;
}


/*
 * Utility functions for data structure
 */

/**
 * @brief Parcours une liste de type Process afin de libérer la mémoire de toutes les activités
 * puis libère la mémoire de la liste de type Process
 * Chaque élément libéré est mis à pointer sur nullpointer
 */
void clear(Process * aList)
{
    while (aList->firstActivity != nullptr) {
        Activity * del = aList->firstActivity;
        aList->firstActivity = del->nextActivity;
        delete del;
    }
}

/**
 * @brief Parcours tous les processus d'une liste et applique clear sur chaque processus
 * puis libère la mémoire de la liste et fait pointer la liste sur nullptr
 */
void clear(ProcessList * aList)
{
    while (aList->firstProcess != nullptr) {
        Process * del = aList->firstProcess;
        aList->firstProcess = del->nextProcess;
        clear(del);
        delete del;
    }
    delete aList;
    aList = nullptr;
}

/**
 * @brief Affiche le nombre d'activité contenu dans le process
 * puis parcours toutes les activités pour les afficher (nom uniquement)
 * comme suit : Nb activités : 3: a b c \n
 */
void displayActivitiesList(Process * aProcess)
{
    if (aProcess->firstActivity != nullptr)
    {
        string out = "";
        Activity *ptr = aProcess->firstActivity;
        for (int i = 0; i < aProcess->nbActivities; ++i) {
            out += ptr->name + ' ';
            ptr = ptr->nextActivity;
        }
        cout<<"Nb activités : "<<aProcess->nbActivities<<": "<<out<<endl;
    }
    else
        cout<<"Nb activités : 0: "<<endl;
}

/**
 * @brief Affiche le nombre de processus contenus dans une liste puis parcours la liste
 * pour afficher l'id de chaque processus et ses activités (utilise displayActivitiesList)
 * comme suit : Nombre de processus : 3\n123:\tNb activités : 3: a b c \n456:\tNb activités : 1: b \n789:\tNb activités : 2: a b \n\n
 */
void displayProcessesList(ProcessList * aList) //on connait toute les taille -> il est inutile de parcourir jusqu'à != nullptr; de plus, il ne prend pas le dernier en compte donc éviter
{
    if (aList->firstProcess == nullptr)
    {
        cout<<"Nombre de processus : 0"<<endl;
    }
    else
    {
        cout<<"Nombre de processus : "<<aList->size<<endl;
        Process * actual = aList->firstProcess;
        for (int i = 0; i < aList->size; ++i) {
            cout<<actual->id<<":\t";
            displayActivitiesList(actual);
            actual = actual->nextProcess;
        }
        cout<<endl;
    }
}

/**
 * @brief Si la liste le processus ne contient aucune activité, l'activité est ajouté en tête
 * sinon la liste des activités est parcourue et l'activité est ajoutée en queue.
 * Le nombre d'activités du processus est incrémenté de 1
 */
void push_back(Process * aProcess, Activity* anActivity)
{
    if (aProcess->firstActivity == nullptr)
        aProcess->firstActivity = anActivity;
    else
    {
        Activity * tracker = aProcess->firstActivity;
        while (tracker->nextActivity != nullptr)
            tracker = tracker->nextActivity;
        tracker->nextActivity = anActivity;
    }
    aProcess->nbActivities++;
}

/**
 * @brief Construit un pointeur de type Activity et l'initialise au valeurs données
 * puis utilise push_back pour ajouter l'activité à la fin de la liste (au processus)
 */
void addActivity(Process * aProcess, string anActivityName, string aTime)
{
    Activity *anActivity = new Activity;
    anActivity->name = anActivityName;
    anActivity->time = aTime;
    push_back(aProcess, anActivity);
}

/**
 * @brief Ajoute un processus (Process) en tête de liste ProcessList
 */
void push_front(ProcessList * aList, Process * aProcess)
{
    if (aList->firstProcess == nullptr)
        aList->firstProcess = aProcess;
    else
    {
        aProcess->nextProcess = aList->firstProcess;
        aList->firstProcess = aProcess;
    }
    aList->size++;
}

/**
 * @brief Construit un pointeur de type Process, positionne le champ id à la valeur donnée
 * puis utilise addActivity pour ajouter l'activité passée en paramètre au processus créé
 * puis utilise push_front pour ajouter le processus à la liste de processus
 */
void addProcess(ProcessList * aList, int aProcessId, string anActivityName, string aTime)
{
    Process *aProcess = new Process;
    aProcess->id = aProcessId;
    addActivity(aProcess, anActivityName, aTime);
    push_front(aList, aProcess);
}

/**
 * @brief Parcours la liste des processus
 * quand le processus est trouvé (comparaison des id à aProcessID) on utilise addActivity pour ajouter
 * l'activité donnée au processus trouvé
 */
void insertProcessActivity(ProcessList * aList, int aProcessId, string anActivityName, string aTime)
{
    if (aList->size != 0)
    {
        Process * processPtr = aList->firstProcess;
        while (processPtr != nullptr && processPtr->id != aProcessId) //tant que l'ID est différent et que le suivant existe, on parcours
        {
            processPtr = processPtr->nextProcess;
        }
        if (processPtr == nullptr) //si le processus n'est pas trouvé, on le crée
            addProcess(aList,aProcessId,anActivityName,aTime);
        else
            addActivity(processPtr,anActivityName,aTime); //sinon, on ajoute l'activité au processus lié
    }
    else
        addProcess(aList,aProcessId,anActivityName,aTime); //si aucun processus n'existe, on le crée
}

/**
 * @brief Parcours la liste des processus
 * Si un processus correspond au process Id donné retourner un pointeur vers ce processus
 * retourne nullptr sinon
 */
Process * processExists(ProcessList * aList, int aProcessId)
{
    Process * processPtr = aList->firstProcess;
    while (processPtr != nullptr && processPtr->id != aProcessId) //tant que l'ID est différent et que le suivant existe, on parcours
    {
        processPtr = processPtr->nextProcess;
    }
    return processPtr;//si le processus n'est pas trouvé, on renvoie nullptr,sinon, on retourne le pointeur
}


/*
 * Processes Functions
 */

/**
 * @brief Affiche la taille du fichier à analyser (en utilisant nbOfLines)
 * Puis parcours le fichier
 * met à jour la barre de progression en utilisant pringProgressBar
 * utilise cin pour récupérer l'identifiant du processus, le nom de l'activité et la date de l'activité
 * si le processus existe (id déjà présent, pour cela on utilise processExist)
 * l'activité est ajoutée au processus trouvé en utilisant insertProcessActivity
 * ajoute le processus à la liste des processus sinon en utilisant addProcess
 * Ne pas oublier de fermer le fichier
 */
void extractProcesses(ProcessList* aList, string aFileName)
{
    int nbLines = nbOfLines(aFileName);
    int nb100Lines = nbLines/100 +1;
    cout<<"Début de l'analyse du fichier, "<<nbLines<<" lignes trouvés"<<endl;
    ifstream iFile(aFileName);
    if (iFile.is_open())
    {
        int id;
        string name;
        string time;
        Process * ptr;
        SummaryCell * summaryPtr = nullptr;
        int iteration = 0;
        while (iteration != nbLines) //(!iFile.eof())
        {
            iteration++;
            if (iteration % nb100Lines == 0)
                printProgressBar(iteration, nbLines);
            if (iFile >> id >> name >> time)
            {
                ptr = processSummaryExists(aList,id);
                if (ptr == nullptr)  //si le processus n'existe pas
                {
                    summaryPtr = summarySame(aList,id); //on teste si un sommaire du debut de l'id processus existe
                    if (summaryPtr == nullptr)          //s'il n'existe pas, on crée le processus et le sommaire, et le sommaire pointe vers le processus
                    {
                        addProcess(aList,id,name,time);
                        addSummary(aList,aList->firstProcess);
                    }
                    else                                // s'il existe, on crée le processus au bon sommaire(comme un livre à chapitre)
                    {
                        addProcessSummary(aList,id,name,time);
                    }
                }
                else //si le processus existe déjà, on lui ajoute une activité
                {
                    addActivity(ptr,name,time);
                }
            }
            else
                cout<<"Erreur de lecture du fichier"<<endl;
        }
        printProgressBar(iteration, nbLines);
    }
    else
    {
        cout<<"Erreur d'ouverture du fichier"<<endl;
    }
    iFile.close();
}

/**
 * @brief Initialise une variable somme
 * Parcours la liste des processus puis ajoute le nombre d'activité de chaque processus
 * à la variable somme
 * retourne la moyenne somme/nombre de processus en réel
 */
double averageProcessLength(ProcessList * aList)
{
    double sum = 0;
    double nbProcess = 0;
    if (aList->size != 0)
    {
        Process * processPtr = aList->firstProcess;
        while (processPtr->nextProcess != nullptr) {
            sum += processPtr->nbActivities;
            nbProcess++;
            processPtr = processPtr->nextProcess;
        }
        sum += processPtr->nbActivities;
        nbProcess++;
    }
    return sum / nbProcess;
}

/**
 * @brief Insère une activité dans un processus en respectant l'ordre croissant sur le nom des activités
 * et à condition que le nom de l'activité n'existe pas déjà
 */
void insertActivity(Process * aProcess, Activity* anActivity)
{
    aProcess->nbActivities++;
    if (aProcess->firstActivity != nullptr)
    {
        Activity * activityPtr = aProcess->firstActivity;
        if (anActivity->name < activityPtr->name)   //si plus grand que la première activité
        {
            anActivity->nextActivity = aProcess->firstActivity;
            aProcess->firstActivity = anActivity;
        }
        else if (anActivity->name == activityPtr->name)  //si identique
        {
            aProcess->nbActivities--;
        }
        else    //si plus petit que première activité
        {
            if (activityPtr->nextActivity == nullptr) //si suivant n'existe pas, mettre l'activité en suivant
                activityPtr->nextActivity = anActivity;
            else
            {
                while (anActivity->name > activityPtr->nextActivity->name && activityPtr->nextActivity->nextActivity != nullptr) //tant que le nom est plus petit et que le suivant existe, on parcours
                {
                    activityPtr = activityPtr->nextActivity;
                }
                if (anActivity->name < activityPtr->nextActivity->name)  //si l'activité est plus petite
                {
                    anActivity->nextActivity = activityPtr->nextActivity;   //on racroche le suivant à notre activité
                    activityPtr->nextActivity = anActivity;                 //on ajoute notre activité à la liste
                }
                else if (anActivity->name == activityPtr->nextActivity->name)   //si identique
                {
                    aProcess->nbActivities--;
                }
                else if (activityPtr->nextActivity->nextActivity == nullptr)
                    activityPtr->nextActivity->nextActivity = anActivity;   //si le suivant n'existe pas, on ajoute à la fin de la liste
            }
        }
    }
    else
        aProcess->firstActivity = anActivity;       //si aucune activité existe, on l'ajoute en premier
}

/**
 * @brief Parcours la liste des processus
 * ajoute la première activité de chaque processus en utilisant
 * insertActivity (pas de doublons)
 */
void startActivities(ProcessList * aProcessList, Process * anActivityList)
{
    if (aProcessList->size != 0) //si processList non-vide
    {
        Process * processPtr = aProcessList->firstProcess;
        while (processPtr->nextProcess != nullptr) {       //tant que l'élément suivant existe : ajouté la première activité à activityList et passer au suivant;
            insertActivity(anActivityList,processPtr->firstActivity);
            processPtr = processPtr->nextProcess;
        }
        insertActivity(anActivityList,processPtr->firstActivity);
    }
}

/**
 * @brief Parcours la liste des processus
 * Parcours la liste des activité de chaque processus
 * ajoute la dernière activité de chaque processus en utilisant
 * insertActivity (pas de doublons)
 */
void endActivities(ProcessList * aProcessList, Process * anActivityList)
{
    if (aProcessList->firstProcess != nullptr)
    {
        Process * processPtr = aProcessList->firstProcess;
        Activity * activityPtr;
        while (processPtr != nullptr) { //tant que le processus suivant existe, parcourir les activités jusqu'a la dernière, créer une copie et l'insérer
            activityPtr = processPtr->firstActivity;
            while (activityPtr->nextActivity != nullptr) {
                activityPtr = activityPtr->nextActivity;
            }
            Activity *anActivity = new Activity;
            anActivity->name = activityPtr->name;
            anActivity->time = activityPtr->time;
            insertActivity(anActivityList,anActivity);
            processPtr = processPtr->nextProcess;
        }
    }
}

/**
 * @brief Parcours la liste des processus
 * pour chaque processus parcours la liste des activités et la compare avec la liste des activité du processus donné
 * retourne vrai si un processus identique est trouvé, faux sinon
 */
bool processAlreadyExists(ProcessList * aProcessList, Process * aProcess)
{
    if (aProcessList->size != 0)
    {
        Process * processPtr = aProcessList->firstProcess;
        Activity * activityPtr = nullptr;
        Activity * ptrAProcessActivities = nullptr;
        bool isIdentic = true;
        while (processPtr->nextProcess != nullptr) //tant que l'élément suivant de la liste de process existe
        {
            activityPtr = processPtr->firstActivity;   //reinitialiser les variables de base
            ptrAProcessActivities = aProcess->firstActivity;
            isIdentic = true;
            for (int i = 0; i < aProcess->nbActivities; ++i) {   //parcourir tout les activités en comparant avec le process donné, si différent passé au process suivant
                if (activityPtr->name != ptrAProcessActivities->name)
                {
                    isIdentic = false;
                    break;
                }
            }
            if (isIdentic == true)
                return true;
            else
                processPtr = processPtr->nextProcess;
        }
        return false;
    }
    else
        return false;
}

/**
 * @brief Parcours la liste des processus
 * affiche la barre de progression en utilisant pringProgressBar
 * pour chaque processus vérifie qu'il n'est pas déjà dans la lite des variants
 * (utilise processAlreadyExists)
 * si c'est un nouveau variant créer un nouveau processus
 * y ajouter toutes les activités en utilisant addActivity
 * puis utiliser push_front pour ajouter le processus à la liste des variants
 */
void variants(ProcessList * aProcessList, ProcessList * aVariant)
{
    int nb100process = aProcessList->size/100 + 1;
    int iteration = 0;
    cout<<"Début de l'analyse des variants, "<<aProcessList->size<<" processus trouvés"<<endl;
    for (Process * processPtr = aProcessList->firstProcess; processPtr->nextProcess != nullptr; processPtr = processPtr->nextProcess) {
        if (iteration % nb100process == 0)
            printProgressBar(iteration,aProcessList->size);
        iteration++;
        if (!processAlreadyExists(aVariant,processPtr))
        {
            Process *aProcess = new Process;
            aProcess->id = processPtr->id;
            for (Activity * activityPtr = processPtr->firstActivity; activityPtr->nextActivity != nullptr; activityPtr = activityPtr->nextActivity) {
                addActivity(aProcess, activityPtr->name, "0");
            }
            push_front(aVariant, aProcess);
        }
    }
    printProgressBar(aProcessList->size,aProcessList->size);
    cout<<aVariant->size<<" variants trouvés"<<endl;
}


// Functions ADD by the student

void addSummary(ProcessList * aList, Process * aProcess)
{
    SummaryCell * aSummaryCell = new SummaryCell;
    aSummaryCell->id = firstNumberId(aProcess->id);
    aSummaryCell->firstProcess = aProcess;
    if (aList->Summary != nullptr) //ajoute le sommaire au début
    {
        aSummaryCell->nextSummary = aList->Summary;
        aList->Summary = aSummaryCell;
    }
    else
        aList->Summary = aSummaryCell;
    //pushSummaryFront(aList, aProcess);  //si le sommaire du processus n'existe pas, on le créer, on ajoute le process normalement à la liste, et on fait pointer le sommaire vers le process
}


void pushSummaryFront(ProcessList * aList, Process * aProcess)
{
    SummaryCell * summary = summarySame(aList, aProcess->id);

    aProcess->nextProcess = summary->firstProcess->nextProcess;
    summary->firstProcess->nextProcess = aProcess;
    aList->size++;
}


SummaryCell * summarySame(ProcessList * aList, int aProcessId)
{
    SummaryCell * summaryPtr = aList->Summary;
    int firstNb = firstNumberId(aProcessId);
    while (summaryPtr != nullptr && summaryPtr->id != firstNb) //tant que l'ID est différent et que le suivant existe, on parcours
    {
        summaryPtr = summaryPtr->nextSummary;
    }
    return summaryPtr;//si le sommaire n'est pas trouvé, on renvoie nullptr, sinon, on retourne le pointeur
}

/*
 * Cherche si le processus existe déjà comme processExists mais voyage par Sommaire(Summary).
 * Renvoie le pointeur du processus ou nullptr s'il n'existe pas
 */
Process * processSummaryExists(ProcessList * aList, int aProcessId)
{
    SummaryCell * summary = summarySame(aList, aProcessId);  //crée le pointeur
    if (summary == nullptr)  //si pas de sommaire
    {
        return nullptr;
    }
    else
    {
        Process * processPtr = summary->firstProcess;  //pointeur de processus
        //tant que le processus pointé existe et qu'il commence par le même id que le sommaire et qu'il n'existe pas déjà, alors on passe au suivant
        while (processPtr != nullptr && firstNumberId(processPtr->id) == summary->id && processPtr->id != aProcessId)
        {
            processPtr = processPtr->nextProcess;
        }
        if (processPtr == nullptr || firstNumberId(processPtr->id) != summary->id)
        {
            return nullptr;
        }
        else if (processPtr->id == aProcessId) //si processus identique(même), alors on renvoie son adresse
        {
            return processPtr;
        }
    }
}


int firstNumberId(int aProcessId)
{
    int significantNumber = 100000;   //7 chiffre significatif
    //cout<<"firstNumberOfId :"<<(aProcessId/significantNumber)<<endl;
    return (aProcessId/significantNumber);
}


/**
 * @brief Construit un pointeur de type Process, positionne le champ id à la valeur donnée
 * puis utilise addActivity pour ajouter l'activité passée en paramètre au processus créé
 * puis utilise push_front pour ajouter le processus à la liste de processus
 */
void addProcessSummary(ProcessList * aList, int aProcessId, string anActivityName, string aTime)
{
    Process *aProcess = new Process;
    aProcess->id = aProcessId;
    addActivity(aProcess, anActivityName, aTime);
    pushSummaryFront(aList, aProcess);
}


void displaySummary(ProcessList * aList)
{
    cout<<"#======# Display #======#"<<endl;
    SummaryCell * summaryPtr = aList->Summary;
    while (summaryPtr != nullptr)
    {
        cout<<summaryPtr->id<<" -> ";
        summaryPtr = summaryPtr->nextSummary;
    }
    cout<<"nullptr"<<endl<<"#======#   End   #======#"<<endl<<endl;
}
