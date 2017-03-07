#ifndef DBIGINT_H
#define DBIGINT_H

#include <string.h>
#include <iostream>

class dbigint
{
public:

    typedef std::size_t size_type;

/******************************4 Crucial Functions for Dynamic classes**********************************************/
    //pre: none
    //post: creates a dynamic bigint with given initial value
    dbigint(int n = 0);

    //pre: s[0] is either +, -, or a digit
    //     s[1[, ... , s[s.size()-1] are digits
    //post: returns the bigint equivalent of the string
    dbigint(const std::string &);

    //pre: none
    //post: copy constructor: creates new dbigint which is a copy of the given dbigint
    dbigint(const dbigint &);

    //pre: none
    //post: returns dynamicall allocated memory to heap
    ~dbigint();

    //pre: none
    //post: makes this dynamic bigint a copy of given dbigint
    void operator = (const dbigint &);

/**********************************************************************************************************************/

    //pre: none
    //post: returns the digit at the given pos (0 if does not exist). pos 0 is the least significant (units) digit
    size_type operator [] (size_type pos) const;

    //pre:
    //post: returns 0 if this dbigint = given dbigint
    //              1 if this dbigint > given dbigint
    //              -1 if this dbigint < given dbigint
    int compare(const dbigint &) const;

    //pre: none
    //post: returns a string equal to this dbigint
    std::string toStdString() const;

    //pre: none
    //post: returns if true if this dbigint is negative, false if positive
    bool is_negative() const;

    //pre: none
    //post: returns current capacity of this dbigint
    size_type size() const;

    //pre: none
    //post: flips the sign of this dbigint
    void negate();

    //pre: none
    //post: finds significant digit of this dbigint and returns the index
    int find_sig() const;

    //pre: none
    //post: adds/subtracts given dbigint to/from current dbigint
    void operator +=(const dbigint &);
    void operator -=(const dbigint &);
    void operator *=(const dbigint &);
    void operator *= (size_type digit);

    //pre: none
    //post: if new_capacity <= _capacity, then do nothing (you cannot shrink). else, allocate a new block with size
    //new_capacity. Copy existing digits and fill the rest with 0
    void reserve (size_type new_capacity);

private:
    size_type *_data;
    size_type _capacity;
    bool _neg;

    //INVARIANTS:
    //_data points to (has the address of) a dynamic array of _capacity digits
    //_data[0] is the least significant (units) digit
    //_data[k] is the kth digit of this dbigint. It is 0 if not used
    //_neg = true if this dbigit is negative
    //     = false if this dbigint is nonnegative (including 0)
};

dbigint operator +(const dbigint &, const dbigint &);
dbigint operator -(const dbigint &, const dbigint &);
dbigint operator -(const dbigint &);
dbigint operator *(const dbigint &, const dbigint &);
dbigint operator *(const dbigint & a, dbigint::size_type d);

bool operator < (const dbigint &, const dbigint &);
bool operator > (const dbigint &, const dbigint &);
bool operator <= (const dbigint &, const dbigint &);
bool operator >= (const dbigint &, const dbigint &);
bool operator == (const dbigint &, const dbigint &);
bool operator != (const dbigint &, const dbigint &);

std::ostream & operator << (std::ostream &, const dbigint &);

#endif // DBIGINT_H
