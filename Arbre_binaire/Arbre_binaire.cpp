// Arbre_binaire.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
#include <iostream>
#include "Tree.h"
int main() {
    srand(time(0));
    std::vector<int> v;
    MinHeap<int> heap;

    for (int i = 0; i < 100000000; i++)  v.push_back(rand() % 100);

    for (auto it = v.begin(); it != v.end(); it++) heap.insert(*it);
                                           
    std::cout << "Tas min :\n";
    heap.print();

    std::cout << "\n";
    std::cout << "\nExtraction du minimum : " << heap.extractMin() << std::endl;

    std::cout << "Tas min apres extraction :\n";
    heap.print();

    return 0;
}


// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
