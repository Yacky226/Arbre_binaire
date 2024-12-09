#pragma once
#include <queue> 
#include <iostream>
#include <stdexcept> 
#include <algorithm>

template <typename T>
struct Node {
    T data;              // Donn�e  stock�e dans le n�ud
    Node* left;          // Pointeur vers le sous-arbre gauche
    Node* right;         // Pointeur vers le sous-arbre droit
    Node* parent;        // Pointeur vers le parent du n�ud

    // Constructeur : Initialise un n�ud 
    Node(T value) : data(value), left(nullptr), right(nullptr), parent(nullptr) {}
};

template <typename T>
class MinHeap {
private:
    Node<T>* root; // Racine du tas 
    std::queue<Node<T>*> insertionQueue; // File pour suivre les n�uds disponibles pour l'insertion
public:
    MinHeap() : root(nullptr) {} // Constructeur : Initialise un tas vide
    T getRoot() const;           // Renvoie la valeur � la racine du tas
    void heapMontant(Node<T>* node); // R�organise le tas en remontant un n�ud
    void heapDescendant(Node<T>* node); // R�organise le tas en descendant un n�ud
    void insert(T value); // Ins�re une nouvelle valeur dans le tas
    T extractMin(); // Supprime la valeur minimale du tas et la renvoie
    void printHeap(Node<T>* node, int level = 0) const; // Affiche visuellement le tas
    void print(); // M�thode utilitaire pour d�marrer l'affichage � partir de la racine
    void destroyTree(Node<T>* node); // Lib�re la m�moire du tas r�cursivement.
    ~MinHeap(); // Destructeur : Nettoie la m�moire en d�truisant le tas
};

// Renvoie la valeur contenue � la racine du tas
template<typename T>
inline T MinHeap<T>::getRoot() const 
{
    return root->data; // Acc�de � la donn�e stock�e � la racine
}

// R�organise le tas en remontant un n�ud si n�cessaire
template<typename T>
void MinHeap<T>::heapMontant(Node<T>* node) 
{
    if (!node || !node->parent) return; // Si le n�ud n'existe pas ou est la racine, rien � faire

    // Si la valeur du n�ud est inf�rieure � celle de son parent, �change les deux
    if (node->data < node->parent->data) {
        std::swap(node->data, node->parent->data);
        heapMontant(node->parent); // Continue � v�rifier plus haut
    }
}

// R�organise le tas en descendant un n�ud si n�cessaire
template<typename T>
void MinHeap<T>::heapDescendant(Node<T>* node) {
    if (!node) return; // Si le n�ud n'existe pas, rien � faire

    Node<T>* smallest = node; // Suppose que le n�ud actuel est le plus petit

    // V�rifie si le fils gauche a une valeur plus petite
    if (node->left && node->left->data < smallest->data) {
        smallest = node->left;
    }
    // V�rifie si le fils droit a une valeur plus petite
    if (node->right && node->right->data < smallest->data) {
        smallest = node->right;
    }

    // Si un enfant a une valeur plus petite, �change les deux et continue vers le bas
    if (smallest != node) {
        std::swap(node->data, smallest->data);
        heapDescendant(smallest);
    }
}

// Ins�re une nouvelle valeur dans le tas
template<typename T>
void MinHeap<T>::insert(T value) 
{
    Node<T>* newNode = new Node<T>(value); // Cr�e un nouveau n�ud avec la valeur donn�e

    // Si le tas est vide, le n�ud devient la racine
    if (!root) {
        root = newNode;
        insertionQueue.push(root); // Ajoute la racine � la file d'attente
        return;
    }

    Node<T>* current = insertionQueue.front(); // Obtient le n�ud en t�te de la file d'attente

    // Ajoute le nouveau n�ud comme enfant gauche ou droit
    if (!current->left) {
        current->left = newNode;
        newNode->parent = current;
    }
    else if (!current->right) {
        current->right = newNode;
        newNode->parent = current;
        insertionQueue.pop(); // Retire le n�ud de la file si ses deux enfants sont pleins
    }

    insertionQueue.push(newNode); // Ajoute le nouveau n�ud � la file d'attente
    heapMontant(newNode); // R�organise le tas en remontant
}

// Supprime et renvoie la valeur minimale du tas
template<typename T>
T MinHeap<T>::extractMin() {
    if (!root) {
        throw std::out_of_range("Heap is empty"); 
    }

    T minValue = root->data; // Stocke la valeur minimale 

    // Trouve le dernier n�ud ins�r�
    Node<T>* lastNode = insertionQueue.back();
    insertionQueue.pop();

    // Si le dernier n�ud est la racine, le tas devient vide
    if (lastNode == root) {
        delete root;
        root = nullptr;
        return minValue;
    }

    // Remplace la valeur de la racine par celle du dernier n�ud.
    root->data = lastNode->data;

    // Supprime le dernier n�ud de l'arbre.
    Node<T>* parent = lastNode->parent;
    if (parent->right == lastNode) {
        parent->right = nullptr;
    }
    else {
        parent->left = nullptr;
    }

    delete lastNode;

    heapDescendant(root); // R�organise le tas en descendant.
    return minValue;
}

// Affiche le tas de mani�re visuelle (avec indentation pour chaque niveau).
template<typename T>
void MinHeap<T>::printHeap(Node<T>* node, int level) const
{
    if (!node) return; // Si le n�ud n'existe pas, rien � afficher.

    printHeap(node->right, level + 1); // Affiche d'abord le sous-arbre droit.

    // Affiche la donn�e avec une indentation correspondant au niveau du n�ud.
    for (int i = 0; i < level; ++i) {
        std::cout << "    ";
    }
    std::cout << node->data << std::endl;

    printHeap(node->left, level + 1); // Affiche ensuite le sous-arbre gauche.
}

// M�thode utilitaire pour lancer l'affichage depuis la racine.
template<typename T>
void MinHeap<T>::print() {
    printHeap(root);
}

// D�truit l'arbre r�cursivement pour lib�rer la m�moire.
template<typename T>
void MinHeap<T>::destroyTree(Node<T>* node)
{
    if (node) {
        destroyTree(node->left); // D�truit le sous-arbre gauche.
        destroyTree(node->right); // D�truit le sous-arbre droit.
        delete node; // Lib�re le n�ud courant.
    }
}

// Destructeur 
template<typename T>
MinHeap<T>::~MinHeap() {
    destroyTree(root); // D�truit tout l'arbre en commen�ant par la racine.
}
