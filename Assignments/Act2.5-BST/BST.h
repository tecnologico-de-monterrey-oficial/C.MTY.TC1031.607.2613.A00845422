#if !defined(BST_H)
#define BST_H

#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>

#include "NodeT.h"

using namespace std;

template <typename T>
class BST {
private:
    NodeT<T>* root;

    void printTree(NodeT<T>* node, string prefix,
                   bool isRight, bool isRoot);

    void preOrder(NodeT<T>* node);
    void inOrder(NodeT<T>* node);
    void postOrder(NodeT<T>* node);
    void levelByLevel();

    int height(NodeT<T>* node);
    void clear(NodeT<T>* node);

public:
    BST() : root(nullptr) {}
    ~BST();

    // evitamos copiar los apuntadores del árbol
    BST(const BST&) = delete;
    BST& operator=(const BST&) = delete;

    void insert(T data);
    bool find(T data);
    void remove(T data);
    void print();

    void visit(int method);
    void visit(string method);

    int height();
    void ancestors(T data);
    int whatLevelAmI(T data);
};

// liberamos la memoria al destruir el árbol
template <typename T>
BST<T>::~BST() {
    clear(root);
}

template <typename T>
void BST<T>::clear(NodeT<T>* node) {
    if (node != nullptr) {
        // liberamos primero los hijos
        clear(node->left);
        clear(node->right);

        // removemos el nodo
        delete node;
    }
}

template <typename T>
void BST<T>::insert(T data) {
    // validamos si el árbol está vacío
    if (root == nullptr) {
        // apuntamos root al nuevo nodo
        root = new NodeT<T>(data);
    } else {
        // creamos un apuntador aux igual a root
        NodeT<T>* aux = root;

        // creamos un apuntador father igual a root
        NodeT<T>* father = root;

        // iteramos hasta encontrar donde insertar el nodo
        while (aux != nullptr) {
            // validamos si el dato ya existe
            if (aux->data == data) {
                return;
            } else {
                // hacemos father igual a aux
                father = aux;

                // recorremos aux
                if (data < aux->data) {
                    aux = aux->left;
                } else {
                    aux = aux->right;
                }
            }
        }

        // insertamos el nodo en el lado correspondiente
        if (data < father->data) {
            father->left = new NodeT<T>(data);
        } else {
            father->right = new NodeT<T>(data);
        }
    }
}

template <typename T>
bool BST<T>::find(T data) {
    // creamos un apuntador aux igual a root
    NodeT<T>* aux = root;

    // iteramos hasta encontrar el dato o llegar a nullptr
    while (aux != nullptr) {
        if (aux->data == data) {
            // encontramos el dato
            return true;
        } else {
            // recorremos aux
            if (data < aux->data) {
                aux = aux->left;
            } else {
                aux = aux->right;
            }
        }
    }

    // no se encontró el dato
    return false;
}

template <typename T>
void BST<T>::remove(T data) {
    // creamos un apuntador aux igual a root
    NodeT<T>* aux = root;

    // root no tiene padre
    NodeT<T>* father = nullptr;

    // buscamos el nodo a borrar
    while (aux != nullptr) {
        if (aux->data == data) {
            break;
        }

        // recorremos aux y father
        father = aux;

        if (data < aux->data) {
            aux = aux->left;
        } else {
            aux = aux->right;
        }
    }

    // validamos si encontramos el nodo
    if (aux == nullptr) {
        throw out_of_range("El nodo a borrar no existe");
    }

    // validamos si el nodo tiene dos hijos
    if (aux->left != nullptr && aux->right != nullptr) {
        // buscamos el más grande del lado izquierdo
        NodeT<T>* fatherRemove = aux;
        NodeT<T>* auxRemove = aux->left;

        // iteramos hasta encontrar el más grande
        while (auxRemove->right != nullptr) {
            fatherRemove = auxRemove;
            auxRemove = auxRemove->right;
        }

        // actualizamos el dato del nodo a borrar
        aux->data = auxRemove->data;

        // conservamos el hijo izquierdo del reemplazo
        if (fatherRemove == aux) {
            aux->left = auxRemove->left;
        } else {
            fatherRemove->right = auxRemove->left;
        }

        // removemos el nodo utilizado como reemplazo
        delete auxRemove;
        return;
    }

    // el nodo tiene un hijo o no tiene hijos
    NodeT<T>* child = nullptr;

    if (aux->left != nullptr) {
        child = aux->left;
    } else {
        child = aux->right;
    }

    // validamos si vamos a borrar root
    if (father == nullptr) {
        root = child;
    } else {
        // conectamos el padre con el hijo correspondiente
        if (father->left == aux) {
            father->left = child;
        } else {
            father->right = child;
        }
    }

    // removemos el nodo
    delete aux;
}

template <typename T>
void BST<T>::printTree(NodeT<T>* node, string prefix,
                       bool isRight, bool isRoot) {
    if (node == nullptr) {
        return;
    }

    // imprimimos el subárbol derecho
    printTree(
        node->right,
        prefix + (isRoot ? "" : (isRight ? "      " : "|     ")),
        true,
        false
    );

    // imprimimos el nodo
    cout << prefix
         << (isRoot ? "" : (isRight ? ".---- " : "`---- "))
         << node->data << endl;

    // imprimimos el subárbol izquierdo
    printTree(
        node->left,
        prefix + (isRoot ? "" : (isRight ? "|     " : "      ")),
        false,
        false
    );
}

template <typename T>
void BST<T>::print() {
    // validamos si el árbol está vacío
    if (root == nullptr) {
        cout << "(arbol vacio)" << endl;
        return;
    }

    printTree(root, "", false, true);
}

template <typename T>
void BST<T>::preOrder(NodeT<T>* node) {
    if (node != nullptr) {
        // imprimimos data
        cout << node->data << " ";

        // hacemos preOrder con left
        preOrder(node->left);

        // hacemos preOrder con right
        preOrder(node->right);
    }
}

template <typename T>
void BST<T>::inOrder(NodeT<T>* node) {
    if (node != nullptr) {
        // hacemos inOrder con left
        inOrder(node->left);

        // imprimimos data
        cout << node->data << " ";

        // hacemos inOrder con right
        inOrder(node->right);
    }
}

template <typename T>
void BST<T>::postOrder(NodeT<T>* node) {
    if (node != nullptr) {
        // hacemos postOrder con left
        postOrder(node->left);

        // hacemos postOrder con right
        postOrder(node->right);

        // imprimimos data
        cout << node->data << " ";
    }
}

template <typename T>
void BST<T>::levelByLevel() {
    // validamos si el árbol está vacío
    if (root == nullptr) {
        return;
    }

    // creamos una fila de apuntadores a nodos
    queue<NodeT<T>*> pending;

    // agregamos root a la fila
    pending.push(root);

    // iteramos mientras existan nodos pendientes
    while (!pending.empty()) {
        // obtenemos el primer nodo
        NodeT<T>* aux = pending.front();
        pending.pop();

        // imprimimos data
        cout << aux->data << " ";

        // agregamos el hijo izquierdo
        if (aux->left != nullptr) {
            pending.push(aux->left);
        }

        // agregamos el hijo derecho
        if (aux->right != nullptr) {
            pending.push(aux->right);
        }
    }
}

template <typename T>
void BST<T>::visit(int method) {
    switch (method) {
        case 1:
            preOrder(root);
            break;

        case 2:
            inOrder(root);
            break;

        case 3:
            postOrder(root);
            break;

        case 4:
            levelByLevel();
            break;

        default:
            throw invalid_argument("El recorrido debe estar entre 1 y 4");
    }

    cout << endl;
}

template <typename T>
void BST<T>::visit(string method) {
    // conservamos las llamadas de tu código original
    if (method == "preOrder") {
        visit(1);
    } else if (method == "inOrder") {
        visit(2);
    } else if (method == "postOrder") {
        visit(3);
    } else if (method == "levelByLevel") {
        visit(4);
    } else {
        throw invalid_argument("El recorrido no existe");
    }
}

template <typename T>
int BST<T>::height(NodeT<T>* node) {
    // un subárbol vacío tiene altura -1
    if (node == nullptr) {
        return -1;
    }

    // calculamos la altura de cada subárbol
    int leftHeight = height(node->left);
    int rightHeight = height(node->right);

    // regresamos la mayor altura más una conexión
    if (leftHeight > rightHeight) {
        return leftHeight + 1;
    } else {
        return rightHeight + 1;
    }
}

template <typename T>
int BST<T>::height() {
    // calculamos la altura desde root
    return height(root);
}

template <typename T>
void BST<T>::ancestors(T data) {
    // validamos que exista antes de imprimir
    if (!find(data)) {
        cout << "El dato no existe en el arbol." << endl;
        return;
    }

    // validamos si el dato es root
    if (root->data == data) {
        cout << "La raiz no tiene ancestros." << endl;
        return;
    }

    // creamos un apuntador aux igual a root
    NodeT<T>* aux = root;

    // imprimimos el camino sin incluir el nodo buscado
    while (aux != nullptr) {
        if (aux->data == data) {
            break;
        }

        // el nodo actual es un ancestro
        cout << aux->data << " ";

        // recorremos aux
        if (data < aux->data) {
            aux = aux->left;
        } else {
            aux = aux->right;
        }
    }

    cout << endl;
}

template <typename T>
int BST<T>::whatLevelAmI(T data) {
    // creamos un apuntador aux igual a root
    NodeT<T>* aux = root;

    // la raíz está en el nivel 0
    int level = 0;

    // buscamos el dato contando las conexiones
    while (aux != nullptr) {
        if (aux->data == data) {
            return level;
        }

        // recorremos aux
        if (data < aux->data) {
            aux = aux->left;
        } else {
            aux = aux->right;
        }

        // avanzamos un nivel
        level++;
    }

    // no encontramos el dato
    return -1;
}

#endif // BST_H