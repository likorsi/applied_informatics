#include <iostream>

class safe_long_long_t 
{
private:
    long long value;
public:
    // конструктор
    safe_long_long_t(long long a) { 
        value = a; 
    }
    
    // оператор присваивания
    const safe_long_long_t& operator=(const safe_long_long_t& a)
    {
        return safe_long_long_t(this->value = a.value);
    }

    // операторы составного присваивания
    const safe_long_long_t& operator+=(const safe_long_long_t& a)
    {
        return (this->value += a.value);
    }

    const safe_long_long_t& operator-=(const safe_long_long_t& a)
    {
        return (this->value -= a.value);
    }

    const safe_long_long_t& operator*=(const safe_long_long_t& a)
    {
        return (this->value *= a.value);
    }

    const safe_long_long_t& operator/=(const safe_long_long_t& a)
    {
        return (this->value /= a.value);
    }

    const safe_long_long_t& operator%=(const safe_long_long_t& a)
    {
        return (this->value %= a.value);
    }

    // инкремент и декремент
    safe_long_long_t& operator++() { //префиксный
        value++;
        return *this;
    }
    safe_long_long_t operator++(int) { //постфиксный
        safe_long_long_t a(value);
        ++(*this);
        return a;
    }
    safe_long_long_t& operator--() { //префиксный
        value--;
        return *this;
    }
    safe_long_long_t operator--(int) { //постфиксный
        safe_long_long_t a(value);
        --(*this);
        return a;
    }

    // арифмитические операторы
    const safe_long_long_t operator+(const safe_long_long_t& a) {
        return safe_long_long_t(*this) += a;
    }
    const safe_long_long_t operator-(const safe_long_long_t& a) {
        return safe_long_long_t(*this) -= a;
    }
    const safe_long_long_t operator*(const safe_long_long_t& a) {
        return safe_long_long_t(*this) *= a;
    }
    const safe_long_long_t operator/(const safe_long_long_t& a) {
        return safe_long_long_t(*this) /= a;
    }
    const safe_long_long_t operator%(const safe_long_long_t& a) {
        return safe_long_long_t(*this) %= a;
    }

    // операторы сравнения
    bool operator==(const safe_long_long_t& a) const {
        return (this->value == a.value);
    }
    bool operator!=(const safe_long_long_t& a) const {
        return (this->value != a.value);
    }
    bool operator>(const safe_long_long_t& a) const {
        return (this->value > a.value);
    }
    bool operator<(const safe_long_long_t& a) const {
        return (this->value < a.value);
    }
    bool operator>=(const safe_long_long_t& a) const {
        return (this->value >= a.value);
    }
    bool operator<=(const safe_long_long_t& a) const {
        return (this->value <= a.value);
    }

    // операторы ввода и вывода
    friend std::ostream& operator<<(std::ostream& out, const safe_long_long_t& a);
    friend std::istream& operator>>(std::istream& in, safe_long_long_t& a);

};

std::ostream& operator<<(std::ostream& out, const safe_long_long_t& a) 
{
    return out << a.value;
}

std::istream& operator>> (std::istream& in, safe_long_long_t& a)
{
    return in >> a.value;
}

int main()
{
    // оператор присваивания
    safe_long_long_t x(45);
    safe_long_long_t y = 60;
    std::cout << "x = " << x << ", y = " << y << "\n";
    // инкремент и декремент
    std::cout << "x++ = " << x++ << "\ny-- = " << y-- << "\n";
    std::cout << "++x = " << ++x << "\n--y = " << --y << "\n";
    // арифмитические операторы
    std::cout << "x + 45 = " << x + 45 << "\ny - 90 = " << y - 90 << "\n";
    std::cout << "x + y = " << x + y << "\nx - y = " << x - y << "\n";
    std::cout << "x * y = " << x * y << "\nx / y = " << x / y << "\nx % y = " << x % y << "\n";
    // операторы сравнения
    if (x == y)
        std::cout << x << " == " << y << "\n";
    if (x != y)
        std::cout << x << " != " << y << "\n";
    if (x > y)
        std::cout << x << " > " << y << "\n";
    if (x < y)
        std::cout << x << " < " << y << "\n";
    if (x >= y)
        std::cout << x << " >= " << y << "\n";
    if (x <= y)
        std::cout << x << " <= " << y << "\n";

    return 0;
}