#ifndef ASD_AVL_IMPL_H
#define ASD_AVL_IMPL_H

#include <utility>
#include <algorithm>

template<typename Key>
avlTree<Key>::avlTree() : root(nullptr) {}

template<typename Key>
avlTree<Key>::avlTree(std::initializer_list<Key> const &values) : root(nullptr) {
    for (auto const &v: values) {
        insert(v);
    }
}

template<typename Key>
avlTree<Key>::avlTree(avlTree const &other) : root(nullptr){
    root = avl::copy(other.root);
}

template<typename Key>
avlTree<Key>::~avlTree() {
    avl::destroy(root);
}

template<typename Key>
void avlTree<Key>::insert(Key const& k) {
    avl::insertIntoSubtree(root, k);
}

template<typename Key>
Key const& avlTree<Key>::min() const{
    return avl::extremumKey(root, avl::LEFT);
}

template<typename Key>
Key const& avlTree<Key>::max() const{
    return avl::extremumKey(root, avl::RIGHT);
}

template<typename Key>
std::ostream& avlTree<Key>::show_indented(std::ostream& out) const {
    return avl::show_indented(root, out);
}

template<typename Key>
std::ostream &operator<<(std::ostream & out, avlTree<Key> const & tree) {
    return avl::displayInline(tree.root, out);
}

template<typename Key>
avlTree<Key> & avlTree<Key>::operator=(avlTree<Key> const &other) {
    if (this != &other) {
        avlTree<Key> tmp{other};
        std::swap(root, tmp.root);
    }
    return *this;
}

template<typename Key>
bool avlTree<Key>::contains(Key const &k) const noexcept {
    return avl::contains(root, k);
}

template<typename Key>
unsigned char avlTree<Key>::height() const noexcept {
    return avl::height(root);
}

template<typename Key>
void avlTree<Key>::erase(Key const &k) noexcept {
    avl::erase(root, k);
}

template<typename Key>
void avlTree<Key>::eraseMin() {
    erase(avl::extremumKey(root, avl::LEFT));
}

template<typename Key>
void avlTree<Key>::eraseMax() {
    erase(avl::extremumKey(root, avl::RIGHT));
}

template<typename Key>
std::istream &operator>>(std::istream &is, avlTree<Key> &tree) {
    return avl::buildFromStream(is, tree.root);
}

#endif //ASD_AVL_IMPL_H
