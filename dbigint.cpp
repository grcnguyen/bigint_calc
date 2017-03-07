#include "dbigint.h"
#include <cassert>
#include <algorithm>

dbigint::dbigint(int n)
{
    if (n == 0)
    {
        _data = new size_type[1];
        _data[0] = 0;
        _capacity = 1;
        _neg = false;
        return;
    }

    if (n < 0)
    {
        _neg = true;
        n = -n;
    }
    else
        _neg = false;

    int copy = n;
    _capacity = 0;
    while (copy > 0)
    {
        copy /= 10;
        ++_capacity;
    }

    _data = new size_type[_capacity];
    std::fill(_data, _data+_capacity, 0);
    size_type i(0);
    while (n > 0)
    {
        _data[i++] = n % 10;
        n /= 10;
    }
}

dbigint::dbigint(const std::string & s)
{
    _capacity = s.size()+1;
    _data = new size_type[_capacity];
    _neg = false;
    std::fill(_data, _data+_capacity, 0); //fills the given range with 0's, so it fills the entire bigint with 0s

    if (s.size () == 0) //if the size of the string is 0, nothing is done, so we return the array
        return;

    int start = 0;
    char c = s[0];  //here, we check to see if the first letter is a sign. If it is, we account for it, below:
    assert(c == '-' || c == '+' || isdigit(c));
    if (c == '-')   //these if statements account for any signs that may be included
    {
        _neg = true;
        ++start;
    }
    if (c == '+')
    {
        _neg = false;
        ++start;
    }

    size_type j = 0;
    for (int i = s.size() - 1; i >= start && j < _capacity; --i)    //adds letters _data if they are digits
    {
        assert(isdigit(s[i]));  //make sure that the character is a digit
        _data[j++] = s[i] - '0';      //to get numbers, we subtract our characters from the character 0
    }

    if(std::count(_data, _data+_capacity, 0) == _capacity) //counts the number of 0s in the range to check if all of the digits are 0
    {
        _neg = false;
    }
}

dbigint::dbigint(const dbigint &b)
{
    _capacity = b._capacity;
    _neg = b._neg;
    _data = new size_type[_capacity];
    std::copy(b._data, b._data+_capacity, _data);
}

dbigint::~dbigint()
{
    delete [] _data;
}

void dbigint::operator = (const dbigint & b)
{
    if (&b == this)
        return;
    if (_capacity != b._capacity)
    {
        delete [] _data;
        _capacity = b._capacity;
        _data = new size_type[_capacity];
    }


    _neg = b._neg;
    std::copy(b._data, b._data+_capacity, _data);
}

dbigint::size_type dbigint::operator[](size_type pos) const
{
    if (pos >= _capacity)
        return 0;
    return _data[pos];
}

dbigint::size_type dbigint::size() const
{
    return _capacity;
}

bool dbigint::is_negative() const
{
    return _neg;
}

int dbigint::compare(const dbigint & b) const
{
    if (_neg && !b._neg)
        return -1;
    if (!_neg && b._neg)
        return 1;

    if ((b._capacity < _capacity && _neg) || (b._capacity > _capacity && !_neg))
    {
        return -1;
    }
    else if ((b._capacity < _capacity && !_neg) || (b._capacity > _capacity && _neg))
    {
        return 1;
    }
    else
    {
        for (int i = 0; i < _capacity; ++i)
        {
            if (_data[i] < b._data[i])
            {
                if (_neg)
                    return 1;
                else
                    return -1;
            }
            else if (_data [i] > b._data[i])
            {
                if (_neg)
                    return -1;
                else
                    return 1;
            }
            else
                return 0;
        }
    }
}

void dbigint::negate()
{
    bool is_zero = true;
    for (int i = _capacity - 1; i >= 0; --i)
    {
        if (_data[i] != 0)
            is_zero = false;
    }
    if (_neg==true || is_zero)
        _neg=false;
    else
        _neg=true;
}

void dbigint::reserve(size_type new_capacity)
{
    if (new_capacity > _capacity)
    {
        size_type * newdata = new size_type [new_capacity];
        std::fill (newdata, newdata + new_capacity, 0);
        std::copy(_data, _data + _capacity, newdata);

        delete [] _data;
        _data = newdata;
        _capacity = new_capacity;
    }
}

int dbigint::find_sig() const
{
    int i = 0;
    for (i = _capacity-1; _data[i]==0 && i>0 ; --i);
    return i;
}

std::string dbigint::toStdString() const
{
    std::string ans = "";
    bool is_zero = true;
    for (int i = _capacity - 1; i>=0; --i)
    {
        if (_data [i] != 0)
            is_zero = false;
    }
    if (_neg && !is_zero)
        ans += "-";
    for (int i = find_sig(); i>=0; --i)
        ans += (_data[i] + '0'); //Adds the position of data to character 0 to get the character!
    return ans;
}

std::ostream & operator << (std::ostream &os, const dbigint &b)
{
    if (b.is_negative())
        os << "-";
    bool leading(true);
    for (int i = b.size() - 1; i >= 0; --i)
    {
        if (b[i] != 0)
            leading = false;
        if (!leading)
            os << b[i];
    }
    if (leading)
        os << "0";
    return os;
}

void dbigint::operator += (const dbigint & ob)
{
    size_type new_capacity = 1 + std::max(_capacity, ob._capacity);
    reserve (new_capacity);

    dbigint b(ob);
    b.reserve(new_capacity);

    if (_neg == b._neg)
        {
            int sum, carry(0);
            for (int i = 0; i < _capacity; ++i)
            {
                sum = _data[i] + b._data[i] + carry;
                _data[i] = sum % 10;
                carry = sum / 10;
            }
        }

        else
        {
            int diff, borrow(0);
            for (int i = 0; i < _capacity; ++i)
            {
                diff = _data[i] - b._data[i] - borrow;
                if (diff < 0)
                {
                    diff += 10;
                    borrow = 1;
                }
                else
                    borrow = 0;
                _data[i] = diff;
            }
            if (borrow == 1)
            {
                _neg = !_neg;
                borrow = 0;
               for (int i = 0; i < _capacity; ++i)
                {
                    int sum = 10 - _data[i] - borrow;
                    _data[i] = sum % 10;
                    borrow = 1 - sum / 10;

                }
            }
        }

        if (std::count(_data, _data+_capacity, 0) == _capacity)
            _neg = false;
}

void dbigint::operator -= (const dbigint & ob)
{
    dbigint temp = ob;
    temp.negate();
    *this += temp;
}


void dbigint::operator *= (size_type digit)
{
    reserve(_capacity +1);
    assert(digit < 10);
    int sum, carry(0);
    for (int i = 0; i < _capacity; ++i)
    {
        sum = _data[i] * digit + carry;
        _data[i] = sum % 10;
        carry = sum / 10;
    }
    if (std::count(_data, _data+_capacity, 0) == _capacity)
        _neg = false;
}

void dbigint::operator *= (const dbigint & b)
{
    dbigint temp;

    for (int i = b._capacity-1; i >=0; --i)
    {
        // shift left
        temp.reserve(temp._capacity+1);
        for (int j = temp._capacity-1; j > 0; --j)
            temp._data[j] = temp._data[j-1];
        temp._data[0] = 0;

        temp += ((*this) * b[i]);

    }

    temp._neg = (_neg != b._neg);
    *this = temp;
    if (std::count(_data, _data+_capacity, 0) == _capacity)
        _neg = false;

}


bool operator < (const dbigint &a, const dbigint &b)
{
    bool is_less = false;
    int comp = a.compare(b);
    if (comp == -1)
        is_less = true;
    return is_less;
}

bool operator > (const dbigint &a, const dbigint &b)
{
    bool is_greater = false;
    int comp = a.compare(b);
    if (comp == 1)
        is_greater = true;
    return is_greater;
}

bool operator <= (const dbigint &a, const dbigint &b)
{
    bool is_less = false;
    int comp = a.compare(b);
    if (comp == -1 || comp == 0)
        is_less = true;
    return is_less;
}

bool operator >= (const dbigint &a, const dbigint &b)
{
    bool is_greater = false;
    int comp = a.compare(b);
    if (comp == 1 || comp == 0)
        is_greater = true;
    return is_greater;
}

bool operator == (const dbigint &a, const dbigint &b)
{
     bool is_equal = true;
     int comp = a.compare(b);
     if (comp != 0)
         is_equal = false;
     return is_equal;
}

bool operator != (const dbigint &a, const dbigint &b)
{
    bool is_equal = false;
    int comp = a.compare(b);
    if (comp != 0)
        is_equal = true;
    return is_equal;
}

dbigint operator -(const dbigint &b)
{
    dbigint ans;
    ans = b;
    ans.negate();
    return ans;
}

dbigint operator +(const dbigint &a, const dbigint &b)
{
    dbigint ans;
    ans = a;
    ans += b;
    return ans;
}

dbigint operator -(const dbigint &a, const dbigint &b)
{
    dbigint ans;
    ans = a;
    ans -= b;
    return ans;
}

dbigint operator *(const dbigint &a, const dbigint &b)
{
    dbigint ans;
    ans = a;
    ans *= b;
    return ans;
}

dbigint operator *(const dbigint & a, dbigint::size_type d)
{
    dbigint ans = a;
    ans *= d;
    return ans;
}
