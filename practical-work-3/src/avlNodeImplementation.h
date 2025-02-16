#ifndef ASD_AVLNODEIMPLEMENTATION_H
#define ASD_AVLNODEIMPLEMENTATION_H

#include "avlNode.h"

namespace avl {

    template<typename Key>
    void insertIntoSubtree(Node<Key> *&subtreeRoot, Key const &keyToInsert) {
        if (!subtreeRoot) {
            subtreeRoot = new Node<Key>{keyToInsert, Node<Key>::NO_CHILD, 1};
            return;
        }
        if (keyToInsert == subtreeRoot->key) {
            return;
        }
        Side s = keyToInsert < subtreeRoot->key ? LEFT : RIGHT;
        insertIntoSubtree(subtreeRoot->children[s], keyToInsert);
        rebalance(subtreeRoot);
    }

    template<typename Key>
    std::ostream &show_indented(Node<Key> *r,
                                std::ostream &out,
                                std::string before,
                                bool isright) {
        out << before;
        if (not r) {
            out << ".\n";
        } else {
            if (not before.empty()) {
                before[before.size() - 2] = ' ';
                if (isright) {
                    before[before.size() - 3] = ' ';
                }
            }
            out << r->key << std::endl;
            if (r->children != Node<Key>::NO_CHILD) {
                for (Side s: {LEFT, RIGHT}) {
                    show_indented(r->children[s], out, before + "|_ ", s);
                }
            }
        }
        return out;
    }

    template<typename Key>
    void destroy(Node<Key> *&subtreeRoot) noexcept {
        if (subtreeRoot != nullptr) {
            destroy(subtreeRoot->left());
            destroy(subtreeRoot->right());
            delete subtreeRoot;
            subtreeRoot = nullptr;
        }
    }

    template<typename Key>
    bool contains(const Node<Key> *const &subtreeRoot, Key const &keyToSearch) noexcept {
        if (!subtreeRoot) {
            return false;
        }
        if (keyToSearch == subtreeRoot->key) {
            return true;
        }
        Side sideToSearch = keyToSearch < subtreeRoot->key ? LEFT : RIGHT;
        return contains(subtreeRoot->children[sideToSearch], keyToSearch);
    }

    template<typename Key>
    Node<Key> *removeMin(Node<Key> *&subtreeRoot) noexcept {
        if (subtreeRoot->left()) {
            return removeMin(subtreeRoot->left());
        }
        Node<Key>* remove = subtreeRoot;
        subtreeRoot = subtreeRoot->right();
        return remove;
    }

    template<typename Key>
    void erase(Node<Key> *&subtreeRoot, Key const &keyToSearch) noexcept {
        if (!subtreeRoot) {
            return;
        }
        if (keyToSearch < subtreeRoot->key) {
            erase(subtreeRoot->left(), keyToSearch);
            rebalance(subtreeRoot);
            return;
        }
        if (keyToSearch > subtreeRoot->key) {
            erase(subtreeRoot->right(), keyToSearch);
            rebalance(subtreeRoot);
            return;
        }
        Node<Key> *tmp = subtreeRoot;
        if (!subtreeRoot->left()) {
            subtreeRoot = subtreeRoot->right();
        } else if (!subtreeRoot->right()) {
            subtreeRoot = subtreeRoot->left();
        } else {
            Node<Key> *min = removeMin(subtreeRoot->right());
            min->right() = subtreeRoot->right();
            min->left() = subtreeRoot->left();
            subtreeRoot = min;
        }

        delete tmp;
    }

    template<typename Key>
    std::ostream &displayInline(Node<Key> *subtreeRoot, std::ostream &outputStream) {
        if (!subtreeRoot) {
            return outputStream << ".";
        }
        outputStream << subtreeRoot->key << "(";
        displayInline(subtreeRoot->left(), outputStream);
        outputStream << ",";
        displayInline(subtreeRoot->right(), outputStream);
        outputStream << ")";
        return outputStream;
    }

    template<typename Key>
    void updateHeight(Node<Key> *const &subtreeRoot) noexcept {
        if (!subtreeRoot) {
            return;
        }
        subtreeRoot->height = std::max(height(subtreeRoot->left()), height(subtreeRoot->right())) + 1;
    }

    template<typename Key>
    std::istream &buildFromStream(std::istream &inputStream, Node<Key> *&subtreeRoot) {
        char ch;
        if (!(inputStream >> ch)) {
            throw std::invalid_argument("Expected '.' or digit");
        }

        if (ch == '.') {
            subtreeRoot = nullptr;
            return inputStream;
        }

        if (!::isdigit(ch)) {
            throw std::invalid_argument("Expected '.' or digit");
        }

        inputStream.putback(ch);
        inputStream >> std::skipws >> subtreeRoot;

        if (std::ws(inputStream).get() != '(') {
            throw std::invalid_argument("Expected '(' after parent node");
        }

        buildFromStream(inputStream, subtreeRoot->left());

        if (std::ws(inputStream).get() != ',') {
            throw std::invalid_argument("Expected ',' after left node");
        }

        buildFromStream(inputStream, subtreeRoot->right());

        updateHeight(subtreeRoot);

        if (std::ws(inputStream).get() != ')') {
            throw std::invalid_argument("Expected ')' after right node");
        }

        return inputStream;
    }

    template<typename Key>
    Node<Key> *copy(const Node<Key> *const &subtreeRoot) {
        if (!subtreeRoot) {
            return nullptr;
        }
        Node<Key> *leftTree = copy(subtreeRoot->left());
        Node<Key> *rightTree = copy(subtreeRoot->right());
        return new Node<Key>{subtreeRoot->key, leftTree, rightTree, subtreeRoot->height};
    }

    template<typename Key>
    const Node<Key> *const &extremumNode(const Node<Key> *const &subtreeRoot, Side side) {
        if (!subtreeRoot) {
            throw std::invalid_argument("Empty tree");
        }
        return subtreeRoot->children[side] ? extremumNode(subtreeRoot->children[side], side): subtreeRoot;
    }

    template<typename Key>
    Key const &extremumKey(const Node<Key> *const &subtreeRoot, Side side) {
        return extremumNode(subtreeRoot, side)->key;
    }

    template<typename Key>
    unsigned char height(const Node<Key> *const &subtreeRoot) noexcept {
        return subtreeRoot ? subtreeRoot->height : 0;
    }

    template<typename Key>
    std::istream &operator>>(std::istream &inputStream, Node<Key> *&subtreeRoot) {
        Key k;
        inputStream >> k;
        insertIntoSubtree(subtreeRoot, k);
        return inputStream;
    }

    template<typename Key>
    void rotate(Node<Key> *&subtreeRoot, Side side) noexcept {
        Node<Key> *pivotNode = subtreeRoot->children[size_t(side + 1) % 2];
        subtreeRoot->children[size_t(side + 1) % 2] = pivotNode->children[side];
        pivotNode->children[side] = subtreeRoot;
        subtreeRoot = pivotNode;

        updateHeight(subtreeRoot->children[side]);
        updateHeight(subtreeRoot);
    }

    template<typename Key>
    int balanceValue(const Node<Key> *const &subtreeRoot) noexcept {
        if (!subtreeRoot) {
            return 0;
        }
        return height(subtreeRoot->left()) - height(subtreeRoot->right());
    }

template<typename Key>
void rebalance(Node<Key> *&subtreeRoot) noexcept {
    if (!subtreeRoot) {
        return;
    }

    int balance = balanceValue(subtreeRoot);

    if (balance < -1) {
        if (balanceValue(subtreeRoot->right()) > 0) {
            rotate(subtreeRoot->right(), RIGHT);
        }
        rotate(subtreeRoot, LEFT);
    } else if (balance > 1) {
        if (balanceValue(subtreeRoot->left()) < 0) {
            rotate(subtreeRoot->left(), LEFT);
        }
        rotate(subtreeRoot, RIGHT);
    } else {
        updateHeight(subtreeRoot);
    }
}
}

#endif //ASD_AVLNODEIMPLEMENTATION_H
