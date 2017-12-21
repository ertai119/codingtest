// no_2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <thread>
#include <future>

using namespace std;

class Integer
{
public:
    Integer();
    ~Integer();
    Integer(int n);
    Integer(unsigned int n);
    Integer(long long int n);
    Integer(unsigned long long int n);
    explicit Integer(const std::string& n);
    Integer(const Integer& other);

    //��Ģ ����
    const Integer add(const Integer& other) const;
    const Integer multiply(const Integer& other) const;
    const Integer divide(const Integer& other) const;
    const Integer mod(const Integer& other) const;

    //�� ���� - ����: ������ ���� 0: ���� ��� : �������� ����
    int compare(const Integer& other) const;

    //��ȣ ����
    const Integer signSwitch() const;

    //��Ʈ ����
    const Integer leftShift(unsigned int n) const;
    const Integer rightShift(unsigned int n) const;
    const Integer or (const Integer& other) const;
    const Integer and (const Integer& other) const;
    const Integer xor (const Integer& other) const;
    const Integer not() const;

    //��ȣ ����
    const Integer operator -() const;
    const Integer operator +() const;

    //��Ʈ ����
    const Integer operator <<(unsigned int n) const;
    const Integer operator >>(unsigned int n) const;
    const Integer operator ~() const;

    //���� ����
    Integer& operator =(const Integer& other);
    Integer& operator +=(const Integer& other);
    Integer& operator -=(const Integer& other);
    Integer& operator *=(const Integer& other);
    Integer& operator /=(const Integer& other);
    Integer& operator %=(const Integer& other);
    Integer& operator <<=(unsigned int n);
    Integer& operator >>=(unsigned int n);
    Integer& operator &=(const Integer& other);
    Integer& operator |=(const Integer& other);
    Integer& operator ^=(const Integer& other);

    void print() const;
    const std::string asString() const;
    int asInt() const;
    unsigned int asUnsigned() const;
    long long int asInt64() const;
    unsigned long long int asUnsigned64() const;
    bool isPositive() const;

private:
    inline unsigned int highWord(unsigned int n) const;
    inline unsigned int lowWord(unsigned int n) const;
    void divideWithRemainder(const Integer& divisor, const Integer& dividend,
        Integer* quot, Integer* rem, int bit) const;

    void stringToValue(const std::string& n);
    const std::string valueToString() const;
    void normalize();

    std::vector<unsigned int>		m_Value;
    bool							m_Positive;
};


//���� ���� �Լ���
Integer abs(const Integer& integer);

//������ �����ε�

//��Ģ ����
const Integer operator +(const Integer& lhs, const Integer& rhs);
const Integer operator -(const Integer& lhs, const Integer& rhs);
const Integer operator *(const Integer& lhs, const Integer& rhs);
const Integer operator /(const Integer& lhs, const Integer& rhs);
const Integer operator %(const Integer& lhs, const Integer& rhs);

//�� ����

bool operator ==(const Integer& lhs, const Integer& rhs);
bool operator !=(const Integer& lhs, const Integer& rhs);
bool operator >(const Integer& lhs, const Integer& rhs);
bool operator >=(const Integer& lhs, const Integer& rhs);
bool operator <(const Integer& lhs, const Integer& rhs);
bool operator <=(const Integer& lhs, const Integer& rhs);


//��Ʈ ����
const Integer operator &(const Integer& lhs, const Integer& rhs);
const Integer operator |(const Integer& lhs, const Integer& rhs);
const Integer operator ^(const Integer& lhs, const Integer& rhs);

//���

std::ostream& operator <<(std::ostream& os, const Integer& integer);
std::istream& operator >>(std::istream& is, Integer& integer);


const Integer Integer::add(const Integer& other) const
{
    Integer result;
    std::vector<unsigned int> addValue;
    bool addPositive = true;

    if (other.m_Value.size() > m_Value.size())
    {
        result.m_Value = other.m_Value;
        result.m_Positive = other.m_Positive;
        addValue = m_Value;
        addPositive = m_Positive;
    }
    else
    {
        result.m_Value = m_Value;
        result.m_Positive = m_Positive;
        addValue = other.m_Value;
        addPositive = other.m_Positive;
    }

    while (addValue.size() != result.m_Value.size())
    {
        if (addPositive)
        {
            addValue.push_back(0);
        }
        else
        {
            addValue.push_back(0xffffffff);
        }
    }

    int carryBit = 0;

    for (int i = 0; i < result.m_Value.size(); i++)
    {
        unsigned int original = result.m_Value[i];

        if (i < addValue.size())
        {
            result.m_Value[i] += addValue[i];
        }
        result.m_Value[i] += carryBit;

        //overflow �߻�
        if (original > result.m_Value[i])
        {
            carryBit = 1;
        }
        else
        {
            carryBit = 0;
        }
    }

    if (carryBit == 1)
    {
        if (result.m_Positive != addPositive)
        {
            result.m_Positive = true;
        }
        else if (result.m_Positive == true)
        {
            result.m_Value.push_back(1);
        }
    }

    result.normalize();

    return result;
}

Integer::Integer()
{
    m_Value.push_back(0);
    m_Positive = true;
}

Integer::Integer(int n)
{
    m_Value.push_back(n);
    if (n < 0)
    {
        m_Positive = false;
    }
    else
    {
        m_Positive = true;
    }
}

Integer::Integer(const std::string& n)
{
    m_Positive = true;

    if (n[0] == '-')
    {
        std::string number(n.begin() + 1, n.end());
        stringToValue(number);
        *this = signSwitch();
    }
    else if (n[0] == '+')
    {
        std::string number(n.begin() + 1, n.end());
        stringToValue(number);
    }
    else
    {
        stringToValue(n);
    }
}

Integer::Integer(const Integer& other)
    : m_Value(other.m_Value), m_Positive(other.m_Positive)
{
}

Integer::Integer(unsigned int n)
{
    m_Value.push_back(n);
    m_Positive = true;
}

Integer::Integer(long long int n)
{
    //���� 32��Ʈ
    m_Value.push_back(n & 0xffffffff);
    //���� 32��Ʈ
    m_Value.push_back((n >> 32) & 0xffffffff);

    m_Positive = (n >= 0);
}

Integer::Integer(unsigned long long int n)
{
    //���� 32��Ʈ
    m_Value.push_back(n & 0xffffffff);
    //���� 32��Ʈ
    m_Value.push_back((n >> 32) & 0xffffffff);

    m_Positive = true;
}

Integer::~Integer()
{

}

void Integer::stringToValue(const std::string& n)
{
    std::deque<int> str;
    std::vector<int> binary;

    m_Value.clear();

    for (int i = 0; i < n.size(); i++)
    {
        str.push_back(n[i] - '0');
    }

    while (!str.empty())
    {
        int bit = str[str.size() - 1] % 2;
        binary.push_back(bit);

        for (int i = 0; i < str.size(); i++)
        {
            if (str[i] % 2 != 0 && i != str.size() - 1)
            {
                str[i + 1] += 10;
            }
            str[i] /= 2;
        }

        while (!str.empty() && str[0] == 0)
        {
            str.pop_front();
        }
    }

    for (int i = 0; i < binary.size(); i += 32)
    {
        int digit = (i + 32 < binary.size()) ? i + 32 : binary.size();

        m_Value.push_back(0);
        for (int j = digit - 1; j >= i; j--)
        {
            int size = m_Value.size();

            m_Value[size - 1] = m_Value[size - 1] * 2 + binary[j];
        }
    }
}

const Integer Integer::signSwitch() const
{
    Integer result = *this;

    for (auto& digit : result.m_Value)
    {
        digit = ~digit;
    }
    result.m_Positive = !this->m_Positive;
    result = result.add(1);

    //���� 0�� ���� ������ ��ȣ�� ����� ����.
    if (result.m_Value.size() == 1 && result.m_Value[0] == 0)
    {
        result.m_Positive = true;
    }

    return result;
}

const std::string Integer::valueToString() const
{
    if (!m_Positive)
    {
        Integer negative = this->signSwitch();
        return "-" + negative.valueToString();
    }

    std::string str = "0";
    std::vector<int> binary;

    for (int i = 0; i < m_Value.size(); i++)
    {
        unsigned int value = m_Value[i];

        for (int j = 0; j < 32; j++)
        {
            binary.push_back(value % 2);
            value /= 2;
        }
    }

    for (int i = binary.size() - 1; i >= 0; i--)
    {
        int carry = binary[i];
        for (int j = str.size() - 1; j >= 0; j--)
        {
            int digit = (str[j] - '0') * 2 + carry;

            carry = digit / 10;
            str[j] = (digit % 10) + '0';
        }

        if (carry == 1)
        {
            str.insert(str.begin(), '1');
        }
    }

    return str;
}

void Integer::print() const
{
    std::cout << valueToString() << std::endl;
}

const Integer Integer::operator+() const
{
    return *this;
}

Integer& Integer::operator +=(const Integer& other)
{
    return *this = (*this) + other;
}

Integer& Integer::operator =(const Integer& other)
{
    m_Value = other.m_Value;
    m_Positive = other.m_Positive;

    return *this;
}

const Integer Integer::operator-() const
{
    return signSwitch();
}

unsigned int Integer::highWord(unsigned int n) const
{
    return n >> 16;
}

unsigned int Integer::lowWord(unsigned int n) const
{
    return n & (0xffff);
}

const Integer Integer::leftShift(unsigned int n) const
{
    Integer result = *this;
    int pushNum = n / 32;
    int shiftNum = n % 32;
    size_t size = result.m_Value.size();

    if (shiftNum != 0)
    {
        unsigned int overflow = result.m_Value[size - 1] >> (32 - shiftNum);
        //���� ū �ڸ������� �����÷ο� �� ��� �׸�ŭ �� �ڿ� �߰�
        if (overflow != 0)
        {
            result.m_Value.push_back(overflow);
        }

        for (int i = size - 1; i >= 0; i--)
        {
            result.m_Value[i] <<= shiftNum;

            if (i > 0)
            {
                result.m_Value[i] +=
                    result.m_Value[i - 1] >> (32 - shiftNum);
            }
        }
    }

    for (int i = 0; i < pushNum; i++)
    {
        result.m_Value.insert(result.m_Value.begin(), 0);
    }

    result.normalize();

    return result;
}

const Integer Integer::rightShift(unsigned int n) const
{
    Integer result = *this;
    int popNum = n / 32;
    int shiftNum = n % 32;

    for (int i = 0; i < popNum && !m_Value.empty(); i++)
    {
        result.m_Value.erase(result.m_Value.begin());
    }

    for (int i = 0; i < result.m_Value.size(); i++)
    {
        result.m_Value[i] >>= shiftNum;

        if (i + 1 < result.m_Value.size())
        {
            result.m_Value[i] += result.m_Value[i + 1] << (32 - shiftNum);
        }
    }

    return result;
}

const Integer Integer::operator<<(unsigned int n) const
{
    return leftShift(n);
}

const Integer Integer::operator>>(unsigned int n) const
{
    return rightShift(n);
}

Integer& Integer::operator -=(const Integer& other)
{
    return *this = (*this) - other;
}

Integer& Integer::operator <<=(unsigned int n)
{
    return *this = (*this) << n;
}

Integer& Integer::operator >>=(unsigned int n)
{
    return *this = (*this) >> n;
}

//Karatsuba Algorithm ���
const Integer Integer::multiply(const Integer& other) const
{
    Integer a = abs(*this);
    Integer b = abs(other);

    //base
    if (m_Value.size() == 1 && other.m_Value.size() == 1)
    {
        unsigned x0 = lowWord(a.m_Value[0]);
        unsigned x1 = highWord(a.m_Value[0]);
        unsigned y0 = lowWord(b.m_Value[0]);
        unsigned y1 = highWord(b.m_Value[0]);
        unsigned z0 = x0 * y0;
        unsigned z2 = x1 * y1;
        Integer result = (x1 + x0)*(y1 + y0) - z2 - z0;
        Integer added = z2;
        result = (added << 32) + (result << 16) + z0;

        if (m_Positive^other.m_Positive)
        {
            result = -result;
        }

        return result;
    }
    size_t aMid = (a.m_Value.size() + 1) / 2;
    size_t bMid = (b.m_Value.size() + 1) / 2;
    size_t size = aMid > bMid ? aMid : bMid;
    auto first0 = a.m_Value.begin();
    auto mid0 = size < a.m_Value.size() ? (first0 + size) : a.m_Value.end();
    auto end0 = a.m_Value.end();
    auto first1 = b.m_Value.begin();
    auto mid1 = size < b.m_Value.size() ? (first1 + size) : b.m_Value.end();
    auto end1 = b.m_Value.end();

    Integer x0;
    x0.m_Value.assign(first0, mid0);
    Integer x1;
    x1.m_Value.assign(mid0, end0);
    if (x1.m_Value.empty())
    {
        x1.m_Value.push_back(0);
    }
    Integer y0;
    y0.m_Value.assign(first1, mid1);
    Integer y1;
    y1.m_Value.assign(mid1, end1);
    if (y1.m_Value.empty())
    {
        y1.m_Value.push_back(0);
    }

    Integer z0 = x0 * y0;
    Integer z2 = x1 * y1;
    Integer z1 = (x1 + x0)*(y1 + y0) - z2 - z0;
    Integer result = (z2 << (64 * size)) + (z1 << (32 * size)) + z0;

    if (m_Positive^other.m_Positive)
    {
        result = -result;
    }

    return result;
}

Integer& Integer::operator *=(const Integer& other)
{
    return *this = (*this) * other;
}

const std::string Integer::asString() const
{
    return valueToString();
}

void Integer::normalize()
{
    for (int i = m_Value.size() - 1; i > 0; i--)
    {
        if (m_Value[i] == 0)
        {
            m_Value.pop_back();
        }
        else
        {
            return;
        }
    }
}

bool Integer::isPositive() const
{
    return m_Positive;
}

const Integer Integer::divide(const Integer& other) const
{
    Integer quot = 0;
    Integer rem = 0;

    divideWithRemainder(abs(*this), abs(other), &quot, &rem, 0);


    //���� ������ ��ȣ �ٸ� ��� ����.
    if (m_Positive ^ other.m_Positive)
    {
        quot = -quot;
    }

    return quot;
}

int Integer::compare(const Integer& other) const
{
    if (m_Positive & !other.m_Positive)
    {
        return 1;
    }
    if (!m_Positive & other.m_Positive)
    {
        return -1;
    }

    //���̰� �� ������ ������ ŭ
    if (m_Value.size() > other.m_Value.size())
    {
        return m_Positive ? 1 : -1;
    }
    else if (m_Value.size() < other.m_Value.size())
    {
        return m_Positive ? -1 : 1;
    }

    //���̰� ���� ��� ���� ū �ڸ����� ������ ��.

    for (int i = m_Value.size() - 1; i >= 0; i--)
    {
        if (m_Value[i] > other.m_Value[i])
        {
            return m_Positive ? 1 : -1;
        }
        else if (m_Value[i] < other.m_Value[i])
        {
            return m_Positive ? -1 : 1;
        }
    }

    return 0;
}

void Integer::divideWithRemainder(const Integer& divisor, const Integer& dividend,
    Integer* quot, Integer* rem, int bit) const
{
    //base. �������� �������� ũ�� ���� 0, �������� ������ ��.
    if (divisor < dividend)
    {
        *rem = divisor;
        return;
    }

    Integer divd = dividend;
    divd <<= bit;

    while (divisor > (divd << 1))
    {
        divd <<= 1;
        bit++;
    }

    Integer divs = divisor;
    Integer quotAdd = 1;
    quotAdd <<= bit;

    while (divs >= divd)
    {
        divs -= divd;
        *quot += quotAdd;
    }

    divideWithRemainder(divs, dividend, quot, rem, bit > 2 ? bit - 2 : 0);
}

const Integer Integer::mod(const Integer& other) const
{
    Integer quot = 0;
    Integer rem = 0;

    divideWithRemainder(abs(*this), abs(other), &quot, &rem, 0);

    //C/C++�� ó���� ���缭, ������ ��ȣ�� ��ⷯ ������ ��� ��ȣ�� �����ϵ��� ó��.
    if (!m_Positive)
    {
        rem = -rem;
    }

    return rem;
}

Integer& Integer::operator/=(const Integer& other)
{
    return *this = (*this) / other;
}

Integer& Integer::operator%=(const Integer& other)
{
    return *this = (*this) % other;
}

const Integer Integer:: or (const Integer& other) const
{
    Integer result = (*this);

    for (int i = 0; i < m_Value.size(); i++)
    {
        result.m_Value[i] |= other.m_Value[i];
    }

    return result;
}

const Integer Integer:: and (const Integer& other) const
{
    Integer result = 0;

    result.m_Value.clear();

    //�� ������ ũ�Ⱑ ���� �� ����.
    size_t size = m_Value.size() < other.m_Value.size() ?
        m_Value.size() : other.m_Value.size();

    for (int i = 0; i < size; i++)
    {
        result.m_Value.push_back(m_Value[i] & other.m_Value[i]);
    }

    return result;
}

const Integer Integer:: xor (const Integer& other) const
{
    const Integer& x = *this;
    const Integer& y = other;

    return ~(x&y) &~(~x&~y);
}

const Integer Integer::not() const
{
    Integer result = *this;

    for (int i = 0; i < result.m_Value.size(); i++)
    {
        result.m_Value[i] = ~result.m_Value[i];
    }

    return result;
}

Integer& Integer::operator&=(const Integer& other)
{
    return *this = (*this) & other;
}

Integer& Integer::operator|=(const Integer& other)
{
    return *this = (*this) | other;
}

Integer& Integer::operator^=(const Integer& other)
{
    return *this = (*this) ^ other;
}

unsigned int Integer::asUnsigned() const
{
    return m_Value[0];
}

long long int Integer::asInt64() const
{
    long long int res = 0;

    if (m_Value.size() >= 2)
    {
        res = m_Value[1];
        res <<= 32;
    }

    res |= m_Value[0];

    return res;
}

unsigned long long int Integer::asUnsigned64() const
{
    long long int res = 0;

    if (m_Value.size() >= 2)
    {
        res = m_Value[1];
        res <<= 32;
    }

    res |= m_Value[0];

    return res;
}

const Integer Integer::operator ~() const
{
    return not();
}

Integer abs(const Integer& integer)
{
    if (integer.isPositive())
    {
        return integer;
    }
    else
    {
        return -integer;
    }
}

const Integer operator+(const Integer& lhs, const Integer& rhs)
{
    return lhs.add(rhs);
}

const Integer operator-(const Integer& lhs, const Integer& rhs)
{
    return lhs.add(-rhs);
}


const Integer operator*(const Integer& lhs, const Integer& rhs)
{
    return lhs.multiply(rhs);
}

const Integer operator/(const Integer& lhs, const Integer& rhs)
{
    return lhs.divide(rhs);
}

const Integer operator%(const Integer& lhs, const Integer& rhs)
{
    return lhs.mod(rhs);
}

bool operator==(const Integer& lhs, const Integer& rhs)
{
    return lhs.compare(rhs) == 0;
}

bool operator!=(const Integer& lhs, const Integer& rhs)
{
    return lhs.compare(rhs) != 0;
}

bool operator>(const Integer& lhs, const Integer& rhs)
{
    return lhs.compare(rhs) == 1;
}

bool operator>=(const Integer& lhs, const Integer& rhs)
{
    return lhs.compare(rhs) >= 0;
}

bool operator<(const Integer& lhs, const Integer& rhs)
{
    return lhs.compare(rhs) == -1;
}

bool operator<=(const Integer& lhs, const Integer& rhs)
{
    return lhs.compare(rhs) <= 0;
}

const Integer operator&(const Integer& lhs, const Integer& rhs)
{
    return lhs. and (rhs);
}

const Integer operator|(const Integer& lhs, const Integer& rhs)
{
    return lhs. or (rhs);
}

const Integer operator^(const Integer& lhs, const Integer& rhs)
{
    return lhs. xor (rhs);
}

std::ostream& operator<<(std::ostream& os, const Integer& integer)
{
    os << integer.asString();

    return os;
}

std::istream& operator>>(std::istream& is, Integer& integer)
{
    std::string n;

    is >> n;

    integer = Integer(n);

    return is;
}

void ThreadFunc(Integer value, Integer count, std::promise<Integer>& retVal)
{
    for (int i = 0; i < count; i++)
    {
        value *= value;
    }

    retVal.set_value(value);
}

unsigned long long DivideValue(unsigned long long left, unsigned long long value, int step)
{
    unsigned long long left2 = left / 2;
    unsigned long long right2 = left2 + left % 2;
    
    step++;
    if (step >= 60 || left < 1000)
    {
        value = pow(value, left);
        return value;
    }

    unsigned long long leftRet = DivideValue(left2, value, step);
    unsigned long long rightRet = DivideValue(right2, value, step);

    return leftRet * rightRet;
}

int main() {

	unsigned long long a = 85;
    //unsigned long long b = 97;
    //unsigned long long t = 1234567891234567890;
    unsigned long long b = 97;
    unsigned long long t = 1234567891234567890;

    unsigned long long left = t / 2;
    unsigned long long right = left + t % 2;
    
    int step = 0;
    unsigned long long value1 = DivideValue(left, b, step);
    unsigned long long value2 = DivideValue(right, b, step);

    unsigned long long totalValue = value1 * value2;

    Integer newT = t / 2;

    //for (unsigned long long i = 0; i < t; i++)
	//std::cout << result;

	return 0;
}