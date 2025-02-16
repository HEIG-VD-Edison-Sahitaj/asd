#ifndef ArrayDeque_h
#define ArrayDeque_h

#include <cstddef> // std::size_t
#include <ostream> // std::ostream

// Ajoutez si nécessaire d'autres inclusions de librairies
#include <cstring>
#include <memory>

template < class T >
class ArrayDeque {
public:
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using size_type = std::size_t;

    explicit ArrayDeque(size_type _capacite = 0) : debut(0),
                                          taille(0),
                                          capacite(_capacite),
                                          buffer(nullptr) {
        if (capacite)
            buffer = reinterpret_cast<pointer> (
                    ::operator new(capacite * sizeof(value_type)));
    }

    // Placez ici les méthodes publiques nécessaires pour passer le codecheck
    /**
     * @brief A copy constructor of the ArrayDeque where the new capacity is rhs.capacite
     * @param rhs
     */
    ArrayDeque(const ArrayDeque<T> &rhs) : ArrayDeque(rhs.capacite) {
            for (size_type i = 0; i < rhs.size(); ++i) {
                new(&buffer[i_physique(i)]) value_type(std::move(rhs.buffer[rhs.i_physique(i)]));
                ++taille;
            }
    }

    /**
     * @brief A copy constructor of the ArrayDeque where the new capacity is the parameter new_capacite
     * @param rhs
     * @param new_capacite
     */
    ArrayDeque(const ArrayDeque<T> &rhs, const size_type new_capacite) : ArrayDeque(new_capacite) {
        for (size_type i = 0; i < rhs.size(); ++i) {
            new(&buffer[i_physique(i)]) value_type(std::move(rhs.buffer[rhs.i_physique(i)]));
            ++taille;
        }
    }

    /**
    * @brief Destructor of the ArrayDeque
    * @param -
    * @return -
    */
    ~ArrayDeque() {
        if (buffer) {
        for (size_type i = 0; i < taille; ++i)
            std::destroy_at(buffer + i_physique(i));
        }
        ::operator delete(buffer);
    }

    size_type size() const noexcept { return taille; };
    size_type capacity() const noexcept { return capacite; };
    bool empty() const noexcept { return taille == 0; };

    reference front() { return at(0); };
    const_reference front() const { return at(0); };
    reference back() { return at(taille - 1); };
    const_reference back() const { return at(taille - 1); };

    void push_front(const_reference value);
    void push_back(const_reference value);
    void pop_front();
    void pop_back();

    void swap(ArrayDeque<T>& rhs);
    void shrink_to_fit();

    constexpr reference operator[]( size_type i ) { return at(i); };
    constexpr const_reference operator[]( size_type i ) const { return at(i); };

    ArrayDeque<T>& operator=(const ArrayDeque<T>& rhs);

private:
    pointer buffer;
    size_type capacite;
    size_type debut;
    size_type taille;

    // Placez ici les méthodes privées qui permettent de rendre votre code plus clair
    reference at(size_type i) { return buffer[i_physique(i)]; };
    const_reference at(size_type i) const { return buffer[i_physique(i)]; };

    size_t i_physique(size_t i_logique);
    size_t i_physique(size_t i_logique) const;

    size_type new_capacity();
    void copy_buffer_new_capacity(size_type capacite);

};

template <typename T> inline
std::ostream& operator<<(std::ostream& s,
                         const ArrayDeque<T>& v) {
    s << "(" << v.size() << "/" << v.capacity() << ") : ";
    if (not v.empty())
        s << v.front() << " -> " << v.back() << " : ";
    s << "[";
    for (size_t i = 0; i < v.size(); ++i) {
        s << v[i];
        if (i != v.size() - 1)
            s << ", ";
    }
    s << "]";
    return s;
}

/**
 * @brief Add an element at the beginning of the ArrayDeque <- wrong?
 * @param value
 * @tparam T
 * @return ArrayDeque<T>&
 */
template <typename T>
ArrayDeque<T>& ArrayDeque<T>::operator=(const ArrayDeque<T>& rhs) {
    if(this != &rhs){
        ArrayDeque<T> tmp(rhs);
        swap(tmp);
    }
    return *this;
}

/**
 * @brief Calcul the physical index
 * @tparam T
 * @param i_logique
 * @return size_t
 */
template <typename T>
size_t ArrayDeque<T>::i_physique(size_t i_logique) {
    return (debut + i_logique) % capacite;
}

/**
 * @brief Calcul the physical index
 * @tparam T
 * @param i_logique
 * @return size_t
 */
template <typename T>
size_t ArrayDeque<T>::i_physique(size_t i_logique) const {
    return (debut + i_logique) % capacite;
}

/**
 * @brief calcul the new capacity
 * @param -
 * @tparam T
 * @return size_T
 */
template <typename T>
size_t ArrayDeque<T>::new_capacity(){
    if (!capacite){
        return 1;
    } else{
        return 2*capacite;
    }
}

/**
 * @brief Create a temp object using the copy constructor with the correct capacity and swap it
 * @tparam T
 * @param new_capacite
 * @return -
 */
template <typename T>
void ArrayDeque<T>::copy_buffer_new_capacity(size_t new_capacite){
    ArrayDeque<T> temp(*this, new_capacite);
    swap(temp);
}

/**
 * @brief Swap the content of the ArrayDeque with another ArrayDeque
 * @param other
 * @tparam T
 * @return -
 */
template <typename T>
void ArrayDeque<T>::swap(ArrayDeque<T>& rhs) {
    using std::swap;
    swap(buffer, rhs.buffer);
    swap(debut, rhs.debut);
    swap(taille, rhs.taille);
    swap(capacite, rhs.capacite);
}

/**
 * @brief Resize the ArrayDeque (capacity = size)
 * @param -
 * @tparam T
 */
template <typename T>
void ArrayDeque<T>::shrink_to_fit() {
    if (taille == capacite) return;
    copy_buffer_new_capacity(taille);
}

/**
 * @brief Add an element at the beginning of the ArrayDeque
 * @param value
 * @tparam T
 * @return -
 */
template <typename T>
void ArrayDeque<T>::push_front(const T& value) {
    if (taille >= capacite){
       copy_buffer_new_capacity(new_capacity());
    }
    size_t avant = i_physique(capacite - 1);
    new(&buffer[avant]) value_type(value);
    debut = avant;
    ++taille;
}

/**
 * @brief Add an element at the end of the ArrayDeque
 * @param value
 * @tparam T
 * @return -
 */
template <typename T>
void ArrayDeque<T>::push_back(const T& value) {
    if (taille >= capacite){
        copy_buffer_new_capacity(new_capacity());
    }
    new(&buffer[i_physique(taille)]) value_type(value);
    ++taille;
}

/**
 * @brief Remove the first element of the ArrayDeque
 * @param -
 * @tparam T
 * @return -
 */
template <typename T>
void ArrayDeque<T>::pop_front() {
    std::destroy_at(buffer + i_physique(0));
    debut = i_physique(1);
    --taille;
}

/**
 * @brief Remove the last element of the ArrayDeque
 * @param -
 * @tparam T
 * @return -
 */
template <typename T>
void ArrayDeque<T>::pop_back() {
    std::destroy_at(buffer + i_physique(taille - 1));
    --taille;
}

#endif /* ArrayDeque_h */
