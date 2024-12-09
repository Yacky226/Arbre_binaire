#pragma once
#include <queue> 
#include <iostream>
#include <stdexcept> 
#include <algorithm>

template <typename T>
struct Node {
    T data;              // Donnée  stockée dans le nœud
    Node* left;          // Pointeur vers le sous-arbre gauche
    Node* right;         // Pointeur vers le sous-arbre droit
    Node* parent;        // Pointeur vers le parent du nœud

    // Constructeur : Initialise un nœud 
    Node(T value) : data(value), left(nullptr), right(nullptr), parent(nullptr) {}
};

template <typename T>
class MinHeap {
private:
    Node<T>* root; // Racine du tas 
    std::queue<Node<T>*> insertionQueue; // File pour suivre les nœuds disponibles pour l'insertion
public:
    MinHeap() : root(nullptr) {} // Constructeur : Initialise un tas vide
    T getRoot() const;           // Renvoie la valeur à la racine du tas
    void heapMontant(Node<T>* node); // Réorganise le tas en remontant un nœud
    void heapDescendant(Node<T>* node); // Réorganise le tas en descendant un nœud
    void insert(T value); // Insère une nouvelle valeur dans le tas
    T extractMin(); // Supprime la valeur minimale du tas et la renvoie
    void printHeap(Node<T>* node, int level = 0) const; // Affiche visuellement le tas
    void print(); // Méthode utilitaire pour démarrer l'affichage à partir de la racine
    void destroyTree(Node<T>* node); // Libère la mémoire du tas récursivement.
    ~MinHeap(); // Destructeur : Nettoie la mémoire en détruisant le tas
};

// Renvoie la valeur contenue à la racine du tas
template<typename T>
inline T MinHeap<T>::getRoot() const 
{
    return root->data; // Accède à la donnée stockée à la racine
}

// Réorganise le tas en remontant un nœud si nécessaire
template<typename T>
void MinHeap<T>::heapMontant(Node<T>* node) 
{
    if (!node || !node->parent) return; // Si le nœud n'existe pas ou est la racine, rien à faire

    // Si la valeur du nœud est inférieure à celle de son parent, échange les deux
    if (node->data < node->parent->data) {
        std::swap(node->data, node->parent->data);
        heapMontant(node->parent); // Continue à vérifier plus haut
    }
}

// Réorganise le tas en descendant un nœud si nécessaire
template<typename T>
void MinHeap<T>::heapDescendant(Node<T>* node) {
    if (!node) return; // Si le nœud n'existe pas, rien à faire

    Node<T>* smallest = node; // Suppose que le nœud actuel est le plus petit

    // Vérifie si le fils gauche a une valeur plus petite
    if (node->left && node->left->data < smallest->data) {
        smallest = node->left;
    }
    // Vérifie si le fils droit a une valeur plus petite
    if (node->right && node->right->data < smallest->data) {
        smallest = node->right;
    }

    // Si un enfant a une valeur plus petite, échange les deux et continue vers le bas
    if (smallest != node) {
        std::swap(node->data, smallest->data);
        heapDescendant(smallest);
    }
}

// Insère une nouvelle valeur dans le tas
template<typename T>
void MinHeap<T>::insert(T value) 
{
    Node<T>* newNode = new Node<T>(value); // Crée un nouveau nœud avec la valeur donnée

    // Si le tas est vide, le nœud devient la racine
    if (!root) {
        root = newNode;
        insertionQueue.push(root); // Ajoute la racine à la file d'attente
        return;
    }

    Node<T>* current = insertionQueue.front(); // Obtient le nœud en tête de la file d'attente

    // Ajoute le nouveau nœud comme enfant gauche ou droit
    if (!current->left) {
        current->left = newNode;
        newNode->parent = current;
    }
    else if (!current->right) {
        current->right = newNode;
        newNode->parent = current;
        insertionQueue.pop(); // Retire le nœud de la file si ses deux enfants sont pleins
    }

    insertionQueue.push(newNode); // Ajoute le nouveau nœud à la file d'attente
    heapMontant(newNode); // Réorganise le tas en remontant
}

// Supprime et renvoie la valeur minimale du tas
template<typename T>
T MinHeap<T>::extractMin() {
    if (!root) {
        throw std::out_of_range("Heap is empty"); 
    }

    T minValue = root->data; // Stocke la valeur minimale 

    // Trouve le dernier nœud inséré
    Node<T>* lastNode = insertionQueue.back();
    insertionQueue.pop();

    // Si le dernier nœud est la racine, le tas devient vide
    if (lastNode == root) {
        delete root;
        root = nullptr;
        return minValue;
    }

    // Remplace la valeur de la racine par celle du dernier nœud.
    root->data = lastNode->data;

    // Supprime le dernier nœud de l'arbre.
    Node<T>* parent = lastNode->parent;
    if (parent->right == lastNode) {
        parent->right = nullptr;
    }
    else {
        parent->left = nullptr;
    }

    delete lastNode;

    heapDescendant(root); // Réorganise le tas en descendant.
    return minValue;
}

// Affiche le tas de manière visuelle (avec indentation pour chaque niveau).
template<typename T>
void MinHeap<T>::printHeap(Node<T>* node, int level) const
{
    if (!node) return; // Si le nœud n'existe pas, rien à afficher.

    printHeap(node->right, level + 1); // Affiche d'abord le sous-arbre droit.

    // Affiche la donnée avec une indentation correspondant au niveau du nœud.
    for (int i = 0; i < level; ++i) {
        std::cout << "    ";
    }
    std::cout << node->data << std::endl;

    printHeap(node->left, level + 1); // Affiche ensuite le sous-arbre gauche.
}

// Méthode utilitaire pour lancer l'affichage depuis la racine.
template<typename T>
void MinHeap<T>::print() {
    printHeap(root);
}

// Détruit l'arbre récursivement pour libérer la mémoire.
template<typename T>
void MinHeap<T>::destroyTree(Node<T>* node)
{
    if (node) {
        destroyTree(node->left); // Détruit le sous-arbre gauche.
        destroyTree(node->right); // Détruit le sous-arbre droit.
        delete node; // Libère le nœud courant.
    }
}

// Destructeur 
template<typename T>
MinHeap<T>::~MinHeap() {
    destroyTree(root); // Détruit tout l'arbre en commençant par la racine.
}
