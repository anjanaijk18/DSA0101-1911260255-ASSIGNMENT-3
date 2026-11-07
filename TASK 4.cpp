#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

class Money
{
    long long paise;

public:
    Money(long long rupees = 0, int p = 0)
        : paise(rupees * 100 + p) {}

    // Addition
    Money operator+(const Money& m) const
    {
        return Money(0, paise + m.paise);
    }

    // Subtraction
    Money operator-(const Money& m) const
    {
        return Money(0, paise - m.paise);
    }

    // Addition assignment
    Money& operator+=(const Money& m)
    {
        paise += m.paise;
        return *this;
    }

    // Equality comparison
    bool operator==(const Money& m) const
    {
        return paise == m.paise;
    }

    // Less-than comparison
    bool operator<(const Money& m) const
    {
        return paise < m.paise;
    }

    // Output operator
    friend ostream& operator<<(ostream& out,
                               const Money& m)
    {
        long long amount = m.paise;

        if(amount < 0)
            out << "-Rs ";
        else
            out << "Rs ";

        amount = llabs(amount);

        out << amount / 100 << "."
            << setw(2) << setfill('0')
            << amount % 100
            << setfill(' ');

        return out;
    }

    // Input operator
    friend istream& operator>>(istream& in, Money& m)
    {
        long long r;
        int p;

        cout << "Enter rupees and paise: ";

        if(in >> r >> p)
            m = Money(r, p);

        return in;
    }
};

int main()
{
    Money a(120, 75);
    Money b(79, 25);

    // Addition
    Money c = a + b;

    cout << c << endl;

    // Equality
    cout << boolalpha << (c == Money(200)) << endl;

    // Carry test
    Money x(0, 75);
    Money y(0, 50);

    cout << "\nCARRY TEST\n";
    cout << x + y << endl;

    // Subtraction test
    cout << "\nSUBTRACTION TEST\n";
    cout << Money(10, 0) - Money(15, 50) << endl;

    // Addition assignment
    cout << "\nBILL CALCULATION\n";
    Money bill(100, 50);
    bill += Money(50, 75);
    cout << bill << endl;

    // Comparison
    cout << "\nCOMPARISON\n";
    cout << boolalpha << (a < b) << endl;

    return 0;
}
