/* ---------------------------
Labo        |   ASD2022_L1_COMPLEXITE
Author(s)   |   Agron Markaj - David Schildböck - Edison Sahitaj
Start date  |   21.02.2024
Deadline    |   05.03.2024 (2359)
Goal        |   Implementation file for the OpCounter Class
Note        |   -
Source      |   -
--------------------------- */

#ifndef ASD2022_L1_COMPLEXITE_OPCOUNTERIMPL_H
#define ASD2022_L1_COMPLEXITE_OPCOUNTERIMPL_H


bool OpCounter::operator==(const OpCounter& lhs) const {
    ++pertinentComparaisons;
    return value == lhs.value;
}

bool OpCounter::operator!=(const OpCounter& lhs) const {
    ++pertinentComparaisons;
    return value != lhs.value;
}


bool OpCounter::operator<(const OpCounter& lhs) const {
    ++pertinentComparaisons;
    return value < lhs.value;
}


bool OpCounter::operator>(const OpCounter& lhs) const {
    ++pertinentComparaisons;
    return value > lhs.value;
}


bool OpCounter::operator<=(const OpCounter& lhs) const {
    ++pertinentComparaisons;
    return value <= lhs.value;
}


bool OpCounter::operator>=(const OpCounter& lhs) const {
    ++pertinentComparaisons;
    return value >= lhs.value;
}

OpCounter operator+(const OpCounter& lhs, const OpCounter& rhs) {
    ++OpCounter::pertinentCopy;
    return OpCounter(lhs.value + rhs.value);
}


OpCounter operator-(const OpCounter& lhs, const OpCounter& rhs) {
    ++OpCounter::pertinentCopy;
    return OpCounter(lhs.value - rhs.value);
}


OpCounter operator+=(const OpCounter& lhs, const OpCounter& rhs) {
    ++OpCounter::pertinentCopy;
    return OpCounter(lhs.value + rhs.value);
}

OpCounter operator-=(const OpCounter& lhs, const OpCounter& rhs) {
    ++OpCounter::pertinentCopy;
    return OpCounter(lhs.value - rhs.value);
}


OpCounter operator*(const OpCounter& lhs, const OpCounter& rhs) {
    ++OpCounter::pertinentCopy;
    return OpCounter(lhs.value * rhs.value);
}

OpCounter operator/(const OpCounter& lhs, const OpCounter& rhs) {
    ++OpCounter::pertinentCopy;
    return OpCounter(lhs.value / rhs.value);
}

OpCounter operator*=(const OpCounter& lhs, const OpCounter& rhs) {
    ++OpCounter::pertinentCopy;
    return OpCounter(lhs.value * rhs.value);
}

OpCounter operator/=(const OpCounter& lhs, const OpCounter& rhs) {
    ++OpCounter::pertinentCopy;
    return OpCounter(lhs.value / rhs.value);
}

OpCounter &OpCounter::operator++() {
    ++pertinentCopy;
    ++value;
    return *this;
}

OpCounter &OpCounter::operator++(int) {
    ++pertinentCopy;
    ++value;
    return *this;
}

OpCounter &OpCounter::operator--() {
    ++pertinentCopy;
    --value;
    return *this;
}

OpCounter &OpCounter::operator--(int) {
    ++pertinentCopy;
    --value;
    return *this;
}

OpCounter &OpCounter::operator=(const OpCounter& lhs) {
    ++pertinentCopy;
    value = lhs.value;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const OpCounter& opCounter) {
    os << opCounter.value;
    return os;
}

std::istream& operator>>(std::istream& is, OpCounter& opCounter) {
    is >> opCounter.value;
    return is;
}

/* ---------------------------
Name        | resetPertinentOperations
Parameter(s)| -
Return      | -
Goal        | Reset the pertinent operations
--------------------------- */
void OpCounter::resetPertinentOperations() {
    pertinentCopy = 0;
    pertinentComparaisons = 0;
}

/* ---------------------------
Name        | resetPertinentOperations
Parameter(s)| -
Return      | unsigned long
Goal        | Get the pertinent comparaisons
--------------------------- */
unsigned long OpCounter::getPertinentComparaisons() {
    return pertinentComparaisons;
}

/* ---------------------------
Name        | getPertinentCopy
Parameter(s)| -
Return      | unsigned long
Goal        | Get the pertinent copy
--------------------------- */
unsigned long OpCounter::getPertinentCopy() {
    return pertinentCopy;
}


#endif //ASD2022_L1_COMPLEXITE_OPCOUNTERIMPL_H
