#ifndef ASD_AVL_H
#define ASD_AVL_H

#include <string>
#include <array>
#include <iostream>

#include "avlNode.h"

template<typename Key> class avlTree;

template <typename Key> std::ostream& operator<<(std::ostream& out, avlTree<Key> const& tree);
template <typename Key> std::istream& operator>>(std::istream& in, avlTree<Key> & tree);

template<typename Key>
class avlTree {
    friend std::ostream &operator<<<>(std::ostream &, avlTree<Key> const &);
    friend std::istream &operator>><>(std::istream &, avlTree<Key> &);

    avl::Node<Key>* root;
public:

    avlTree();
    void insert(Key const &k);
    avlTree(avlTree const &other);
    avlTree<Key> & operator=(const avlTree<Key> &other);
    avlTree(std::initializer_list<Key> const &values);
    ~avlTree();

    bool contains(Key const& k) const noexcept ;

    Key const& max() const;
    Key const& min() const;

    void eraseMax();
    void eraseMin();
    void erase(Key const& k) noexcept;
    [[nodiscard]] unsigned char height() const noexcept;
    std::ostream& show_indented(std::ostream& out = std::cout) const;
};

#include "avlTreeImplementation.h"

#endif //ASD_AVL_H
