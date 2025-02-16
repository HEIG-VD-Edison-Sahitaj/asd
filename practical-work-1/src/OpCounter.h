/* ---------------------------
Labo        |   ASD2022_L1_COMPLEXITE
Author(s)   |   Agron Markaj - David Schildböck - Edison Sahitaj
Start date  |   21.02.2024
Deadline    |   05.03.2024 (2359)
Goal        |   Header file for the OpCounter Class
Note        |   -
Source      |   -
--------------------------- */

#ifndef LABO_1_COMPLEXITES_SCHILDBOCK_MARKAJ_SAHITAJ_OPCOUNTER_H
#define LABO_1_COMPLEXITES_SCHILDBOCK_MARKAJ_SAHITAJ_OPCOUNTER_H

#include <type_traits>
#include <concepts>
#include <iostream>

class OpCounter {
public:
    OpCounter() : value(0) {}
    OpCounter(const int value) : value(value) {}

    // Operators for the class
    bool operator==(const OpCounter& lhs) const;
    bool operator!=(const OpCounter& lhs) const;
    bool operator<(const OpCounter& lhs) const;
    bool operator>(const OpCounter& lhs) const;
    bool operator<=(const OpCounter& lhs) const;
    bool operator>=(const OpCounter& lhs) const;

    friend OpCounter operator+(const OpCounter& lhs, const OpCounter& rhs);
    friend OpCounter operator-(const OpCounter& lhs, const OpCounter& rhs);
    friend OpCounter operator+=(const OpCounter& lhs, const OpCounter& rhs);
    friend OpCounter operator-=(const OpCounter& lhs, const OpCounter& rhs);
    friend OpCounter operator*(const OpCounter& lhs, const OpCounter& rhs);
    friend OpCounter operator/(const OpCounter& lhs, const OpCounter& rhs);
    friend OpCounter operator*=(const OpCounter& lhs, const OpCounter& rhs);
    friend OpCounter operator/=(const OpCounter& lhs, const OpCounter& rhs);

    OpCounter &operator++();
    OpCounter &operator++(int);
    OpCounter &operator--();
    OpCounter &operator--(int);
    OpCounter &operator=(const OpCounter& lhs);

    friend std::ostream& operator<<(std::ostream& os, const OpCounter& opCounter);
    friend std::istream& operator>>(std::istream& is, OpCounter& opCounter);

    // functions for the class
    static void resetPertinentOperations();
    static unsigned long getPertinentComparaisons();
    static unsigned long getPertinentCopy();

private:
    inline static unsigned long pertinentComparaisons = 0, pertinentCopy = 0;
    int value;
};

#include "OpCounterImpl.h"

#endif //LABO_1_COMPLEXITES_SCHILDBOCK_MARKAJ_SAHITAJ_OPCOUNTER_H
