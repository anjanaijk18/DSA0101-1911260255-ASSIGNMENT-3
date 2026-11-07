#include <iostream>
#include <cmath>
#include <stdexcept>
using namespace std;

class Complex
{
    double real, imag;

public:

    Complex() : real(0), imag(0) {}

    Complex(double r) : real(r), imag(0) {}

    Complex(double r, double i) : real(r), imag(i) {}

    Complex operator+(const Complex &c) const
    {
        return Complex(real+c.real, imag+c.imag);
    }

    Complex operator-(const Complex &c) const
    {
        return Complex(real-c.real, imag-c.imag);
    }

    Complex operator*(const Complex &c) const
    {
        return Complex(real*c.real-imag*c.imag,
                       real*c.imag+imag*c.real);
    }

    Complex operator/(const Complex &c) const
    {
        double d = c.real*c.real + c.imag*c.imag;

        if(d == 0)
            throw runtime_error("Division by zero impedance");

        return Complex((real*c.real+imag*c.imag)/d,
                       (imag*c.real-real*c.imag)/d);
    }

    bool operator==(const Complex &c) const
    {
        return real == c.real && imag == c.imag;
    }

    double magnitude() const
    {
        return sqrt(real*real + imag*imag);
    }

    double phase() const
    {
        return atan2(imag, real) * 180 / 3.14159265;
    }

    friend ostream& operator<<(ostream &out, const Complex &c)
    {
        out << c.real;

        if(c.imag >= 0)
            out << " + j" << c.imag;
        else
            out << " - j" << -c.imag;

        return out;
    }
};

int main()
{
    try
    {
        Complex R(10, 0);
        Complex L(0, 5);
        Complex C(0, -2);

        Complex series = R + L + C;

        Complex parallel = Complex(1) /
                           (Complex(1)/R +
                            Complex(1)/L +
                            Complex(1)/C);

        cout << "AC CIRCUIT IMPEDANCE\n";

        cout << "Series Impedance: " << series << endl;
        cout << "Magnitude: " << series.magnitude() << endl;
        cout << "Phase: " << series.phase() << " degrees\n";

        cout << "\nParallel Impedance: " << parallel << endl;
        cout << "Magnitude: " << parallel.magnitude() << endl;
        cout << "Phase: " << parallel.phase() << " degrees\n";

        Complex zero(0, 0);

        cout << "\nZERO DIVISION TEST\n";
        Complex test = R / zero;
    }
    catch(const runtime_error &e)
    {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
