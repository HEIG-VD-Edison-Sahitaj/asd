#ifndef ASD_AVLNODE_H
#define ASD_AVLNODE_H

namespace avl {

    enum Side {
        LEFT = 0, RIGHT = 1
    };

    template<typename Key>
    struct Node {
        Key const key;
        std::array<Node*, 2> children;
        unsigned char height;

        inline Node*& left() noexcept { return children[LEFT]; }
        inline Node* const& left() const noexcept { return children[LEFT]; }
        inline Node*& right() noexcept { return children[RIGHT]; }
        inline Node* const& right() const noexcept { return children[RIGHT]; }

        static constexpr std::array<Node*, 2> NO_CHILD{nullptr, nullptr};
    };

    template<typename Key>
    void insertIntoSubtree(Node<Key> *&subtreeRoot, Key const &keyToInsert);

    template<typename Key>
    std::ostream&  show_indented(Node<Key> *r,
                       std::ostream &out = std::cout,
                       std::string before = "",
                       bool isright = false);

    template<typename Key>
    void destroy(Node<Key> *&subtreeRoot) noexcept;

    template<typename Key>
    bool contains(const Node<Key> *const &subtreeRoot, Key const &keyToSearch) noexcept;

    template<typename Key>
    Node<Key> *removeMin(Node<Key> *&subtreeRoot) noexcept;

    template<typename Key>
    void erase(Node<Key> *&subtreeRoot, Key const &keyToSearch) noexcept;

    template<typename Key>
    std::ostream &displayInline(Node<Key> *subtreeRoot, std::ostream &outputStream);

    template<typename Key>
    Node<Key> *copy(const Node<Key> *const &subtreeRoot);

    template<typename Key>
    Key const &extremumKey(const Node<Key> *const &subtreeRoot, Side side);

    template<typename Key>
    const Node<Key> *const &extremumNode(const Node<Key> *const &subtreeRoot, Side side);

    template<typename Key>
    unsigned char height(const Node<Key> *const &subtreeRoot) noexcept;

    template<typename Key>
    std::istream &operator>>(std::istream &inputStream, Node<Key> *&subtreeRoot);

    template<typename Key>
    std::istream &buildFromStream(std::istream &inputStream, Node<Key> *&subtreeRoot);

    template<typename Key>
    void updateHeight(Node<Key> *const &subtreeRoot) noexcept;

    template<typename  Key>
    void rebalance(Node<Key> *&subtreeRoot) noexcept;

    template<typename  Key>
    void rotate(Node<Key> *&subtreeRoot, Side side) noexcept;

    template<typename  Key>
    int balanceValue(const Node<Key> *const &subtreeRoot) noexcept;
}

#include "avlNodeImplementation.h"

#endif //ASD_AVLNODE_H
