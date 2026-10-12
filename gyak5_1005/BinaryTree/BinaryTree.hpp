#ifndef ADATSZERK_L05_BINARYTREE_HPP
#define ADATSZERK_L05_BINARYTREE_HPP

#include <iostream>
#include <list>

#include "BinaryTreeExceptions.hpp"


/**
 * C++ concept. Biztosítja, hogy fordítási időben el tudjuk dönteni egy template paraméterről, hogy az használható
 * lesz-e az adott implementációban.
 */
template <typename T>
concept Sortable = requires(T lhs, T rhs) {
    // Megvizsgálja, hogy definiálva van-e a < operátor az adott osztályra.
    { lhs < rhs } -> std::same_as<bool>;
};

/**
 * Bináris keresőfa osztály
 * DEFINÍCIÓ
*/
template<Sortable T> // Class vagy typename helyett használjuk az előbb definiált concept-et
class BinaryTree {
    // Belső csúcs struktúra
    struct Node {
        Node *parent;
        Node *left, *right;
        T key;

        explicit Node(const T& k) :
                parent(nullptr), left(nullptr), right(nullptr), key(k) {
        }
        Node(const T& k, Node *p) :
                parent(p), left(nullptr), right(nullptr), key(k) {
        }
    };

    // Adattag
    Node *root;

    // Felszabadító függvény
    void _destroy(Node* x);

    // Segédfüggvények
    static Node* _min(Node* x);
    static Node* _max(Node* x);
    static Node* _next(Node* x);
    static Node* _prev(Node* x);

    std::list<T> _inorder(Node *x) const;
    std::list<T> _preorder(Node *x) const;
    std::list<T> _postorder(Node *x) const;

    std::ostream& _inorder(Node* i, std::ostream& o);
    std::ostream& _preorder(Node* i, std::ostream& o);
    std::ostream& _postorder(Node* i, std::ostream& o);

    size_t _size(Node* x) const;

    Node* _getroot() const;
    Node* _copyOf(Node* n, Node* p);

public:
    // Konstruktor és destruktor
    BinaryTree() : root(nullptr) {}

    ~BinaryTree() {
        _destroy(root);
    }

    // Másoló konstruktor és operátor, valamint segéd függvényeik
    BinaryTree(const BinaryTree<T>& t);
    BinaryTree& operator=(const BinaryTree<T>& t);

    // Alapműveletek
    [[nodiscard]] size_t size() const {
        return _size(root);
    }
    [[nodiscard]] bool isempty() const {
        return root == nullptr;
    }

    T getroot() const;
    bool find(const T& k) const;
    void insert(const T& k);
    void remove(const T& k);

    std::list<T> inorder() const;
    std::list<T> preorder() const;
    std::list<T> postorder() const;

    std::ostream& inorder(std::ostream& o);
    std::ostream& preorder(std::ostream& o);
    std::ostream& postorder(std::ostream& o);

    T min() const {
        if(isempty()) {
           throw internal_error("A fa ures.");
        }
        return _min(root)->key;
    }
    T max() const {
        if(isempty()) {
            throw internal_error("A fa ures.");
        }
        return _max(root)->key;
    }
};

/**
 * Bináris keresőfa osztály
 * FÜGGVÉNYIMPLEMENTÁCIÓK
 */

/**
  * Rekurzívan felszabadítja a csúcsokat.
  * A destruktor hívja meg a gyökérre.
  */
template<Sortable T>
void BinaryTree<T>::_destroy(Node* x) {
    if (x != nullptr) {
        _destroy(x->left);
        _destroy(x->right);
        delete x;
    }
}

/**
  * Visszaadja a fa gyökerét a statikus függvényeknek.
  */
template<Sortable T>
BinaryTree<T>::Node* BinaryTree<T>::_getroot() const {
    return root;
}
/**
  * Segédfüggvény a copy constructor-hoz valamint assigment operator-hoz
  */
template<Sortable T>
BinaryTree<T>::Node* BinaryTree<T>::_copyOf(Node* n, Node* p) {
    if (n==nullptr)
        return nullptr;

    Node *newNode = new Node(n->key, p);
    newNode->left = _copyOf(n->left, newNode);
    newNode->right = _copyOf(n->right, newNode);
    return newNode;

}

// Másoló konstruktor (klónozás - meglévő fából készít másolatot)
template<Sortable T>
BinaryTree<T>::BinaryTree(const BinaryTree<T>& t) {
    root = _copyOf(t.root, nullptr);
}

// Assigment operator (meglévő fát tesz egyenlővé egy másikkal)
template<Sortable T>
BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree<T>& t) {
    if (this != &t) {
        _destroy(t.root);
        root = _copyOf(t.root, nullptr);
    }
    return *this;
}

// Visszaadja az x gyökerű részfa legkisebb értékű csúcsát.
// Előfeltétel: x != nil
template<Sortable T>
BinaryTree<T>::Node *BinaryTree<T>::_min(Node* x) {
    if (x==nullptr) return nullptr;
    while (x->left!=nullptr) x = x->left;
    return x;
}
/**
  * Visszaadja az x gyökerű részfa legnagyobb értékű csúcsát.
  * Előfeltétel: x != nil
  */
template<Sortable T>
BinaryTree<T>::Node *BinaryTree<T>::_max(Node* x) {
    if (x==nullptr) return nullptr;
    while (x->right!=nullptr) x = x->right;
    return x;
}

/**
  * Visszaadja a fából az x csúcs rákövetkezőjét,
  * vagy nil-t, ha x az legnagyobb kulcsú elem.
  * Előfeltétel: x != nil
  */
template<Sortable T>
BinaryTree<T>::Node *BinaryTree<T>::_next(Node* x) {
    if (x == nullptr) return nullptr;
    if (x->left!=nullptr) return _min(x->right);

    Node* y = x->parent;
    while (y != nullptr && y->right) {
        x = y;
        y = y->parent;
    }
    return y;
}

/**
  * Visszaadja a fából az x csúcs megelőzőjét,
  * vagy nil-t, ha x az legkisebb kulcsú elem.
  * Előfeltétel: x != nil
  */
template<Sortable T>
BinaryTree<T>::Node *BinaryTree<T>::_prev(Node* x) {
    if (x==nullptr) return nullptr;
    if (x->left != nullptr) {
        return _max(x->left);
    }
    Node* y = x->parent;
    while (y != nullptr && y->left) {
        x=y;
        y=y->parent;
    }
    return y;
}

/**
  * Rekurzívan meghatározza, és visszaadja
  * az x gyökerű részfa elemeinek számát.
  * Megjegyzés: üres fára is működik -> 0-t ad vissza
  */
template<Sortable T>
size_t BinaryTree<T>::_size(Node* x) const {
    if (x == nullptr) {
        return 0;
    }
    return 1 + _size(x->left) + _size(x->right);
}

template<Sortable T>
T BinaryTree<T>::getroot() const {
    if (isempty()) {
        throw internal_error("A fa ures.");
    }
    return root->key;
}

/**
  * Lekérdezi, hogy található-e k kulcs a fában.
  * Igazat ad vissza, ha található.
  */
template<Sortable T>
bool BinaryTree<T>::find(const T& k) const {
    Node* x = root;
    while (x != nullptr) {
        if (k < x->key) {
            x = x->left;
        } else if (x->key < k) {
            x = x->right;
        } else {
            return true;
        }
    }
    return false;
}

/**
  * Beszúrja a k értéket a fába.
  * Ha már van k érték a fában, akkor nem csinál semmit.
  */
template<Sortable T>
void BinaryTree<T>::insert(const T& k) {
    Node* y = nullptr;
    Node* x = root;

    while (x != nullptr) {
        y = x;
        if (k < x->key) {
            x = x->left;
        } else if (x->key < k) {
            x = x->right;
        } else {
            return;
        }
    }

    Node* z = new Node(k, y);

    if (y == nullptr) {
        root = z;
    } else if (k < y->key) {
        y->left = z;
    } else {
        y->right = z;
    }
}

/**
  * Eltávolítja a k értéket a fából.
  * Ha nem volt k érték a fában, akkor nem csinál semmit.
  */
template<Sortable T>
void BinaryTree<T>::remove(const T& k) {
    // megtaláljuk a törlendő z csúcsot
    Node* z = root;
    while (z != nullptr) {
        if (k < z->key) {
            z = z->left;
        } else if (z->key < k) {
            z = z->right;
        } else {
            break;
        }
    }

    if (z == nullptr) {
        return; // Nem találtuk meg az elemet, nincs mit törölni
    }

    // 2. Törlés előkészítése (y: a csúcs amit fizikailag kivágunk a fából)
    Node* y;
    if (z->left == nullptr || z->right == nullptr) {
        y = z; // Ha 0 vagy 1 gyermeke van, magát a csúcsot vágjuk ki
    } else {
        y = _next(z); // Ha 2 gyermeke van, a rákövetkezőjét fogjuk kivágni, és annak az értékét felmásolni
    }

    // 3. (x: az y kivágott csúcs gyermeke, amit be kell kötnünk a helyére)
    Node* x;
    if (y->left != nullptr) {
        x = y->left;
    } else {
        x = y->right;
    }

    if (x != nullptr) {
        x->parent = y->parent;
    }

    if (y->parent == nullptr) {
        root = x;
    } else if (y == y->parent->left) {
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }

    if (y != z) {
        z->key = y->key;
    }

    delete y;
}


// Bináris keresőfa bejárások implementációi.
// Preorder bejárás.
template<Sortable T>
std::ostream& BinaryTree<T>::_preorder(Node* i, std::ostream& o) {
    if (i!=nullptr) {
        o << i->key << " ";
        _preorder(i->left, o);
        _preorder(i->right, o);
    }
    return o;
}

// Postorder bejárás.
template<Sortable T>
std::ostream& BinaryTree<T>::_postorder(Node* i, std::ostream& o) {
    if (i!=nullptr) {
        _postorder(i->left, o);
        _postorder(i->right, o);
        o << i->key << " ";
    }
    return o;
}

// Inorder bejárás.
template<Sortable T>
std::ostream& BinaryTree<T>::_inorder(Node* i, std::ostream& o) {
    if (i != nullptr) {
        _inorder(i->left, o);
        o << i->key << " ";
        _inorder(i->right, o);
    }
    return o;
}


// Bináris keresőfa bejárások kívülről elérhető függvényei.
template<Sortable T>
std::ostream& BinaryTree<T>::preorder(std::ostream& o) {
    return _preorder(root, o);
}

template<Sortable T>
std::ostream& BinaryTree<T>::postorder(std::ostream& o) {
    return _postorder(root, o);
}

template<Sortable T>
std::ostream& BinaryTree<T>::inorder(std::ostream& o) {
    return _inorder(root, o);
}

/**
 * Segédfüggvények a tesztekhez
 */
template<Sortable T>
std::list<T> BinaryTree<T>::_inorder(Node *x) const {
    std::list<T> ret{};
    if (x->left != nullptr){
        auto left = _inorder(x->left);
        ret.insert(ret.end(), left.begin(), left.end());
    }
    ret.push_back(x->key);
    if (x->right != nullptr){
        auto right = _inorder(x->right);
        ret.insert(ret.end(), right.begin(), right.end());
    }
    return ret;
}

template<Sortable T>
std::list<T> BinaryTree<T>::inorder() const {
    return _inorder(root);
}

template<Sortable T>
std::list<T> BinaryTree<T>::_postorder(Node *x) const {
    std::list<T> ret{};
    if (x == nullptr) return ret;

    if (x->left != nullptr){
        auto left = _inorder(x->left);
        ret.insert(ret.end(), left.begin(), left.end());
    }
    if (x->right != nullptr){
        auto right = _inorder(x->right);
        ret.insert(ret.end(), right.begin(), right.end());
    }
    ret.push_back(x->key);
    return ret;
}

template<Sortable T>
std::list<T> BinaryTree<T>::postorder() const {
    return _postorder(root);
}

template<Sortable T>
std::list<T> BinaryTree<T>::_preorder(Node *x) const {
    std::list<T> ret{};
    if (x == nullptr) return ret;

    ret.push_back(x->key);
    if (x->left != nullptr){
        auto left = _inorder(x->left);
        ret.insert(ret.end(), left.begin(), left.end());
    }
    if (x->right != nullptr){
        auto right = _inorder(x->right);
        ret.insert(ret.end(), right.begin(), right.end());
    }
    return ret;
}

template<Sortable T>
std::list<T> BinaryTree<T>::preorder() const {
    return _preorder(root);
}

#endif //ADATSZERK_L05_BINARYTREE_HPP

