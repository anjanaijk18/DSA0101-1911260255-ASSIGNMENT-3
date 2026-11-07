#include <iostream>
#include <cstring>
using namespace std;

class Text
{
    char *data;
    static int copies;

public:
    Text()
    {
        data = new char[1];
        data[0] = '\0';
    }

    Text(const char *s)
    {
        data = new char[strlen(s) + 1];
        strcpy(data, s);
    }

    // Copy constructor
    Text(const Text &t)
    {
        data = new char[strlen(t.data) + 1];
        strcpy(data, t.data);
        copies++;
    }

    // Copy assignment operator
    Text& operator=(const Text &t)
    {
        if(this != &t)
        {
            char *temp = new char[strlen(t.data) + 1];
            strcpy(temp, t.data);

            delete[] data;
            data = temp;
        }
        return *this;
    }

    // Concatenation operator
    Text operator+(const Text &t) const
    {
        char *temp = new char[strlen(data) + strlen(t.data) + 1];

        strcpy(temp, data);
        strcat(temp, t.data);

        Text result(temp);
        delete[] temp;

        return result;
    }

    // Equality operator
    bool operator==(const Text &t) const
    {
        return strcmp(data, t.data) == 0;
    }

    // Inequality operator
    bool operator!=(const Text &t) const
    {
        return !(*this == t);
    }

    // Output operator
    friend ostream& operator<<(ostream &out, const Text &t)
    {
        out << t.data;
        return out;
    }

    ~Text()
    {
        delete[] data;
    }

    static int getCopies()
    {
        return copies;
    }
};

int Text::copies = 0;

int main()
{
    Text a("Hello ");
    Text b("World");
    Text c("!");

    cout << "TEXT CONCATENATION\n";
    Text result = a + b + c;
    cout << result << endl;

    cout << "\nCOMPARISON\n";
    Text x("Hello");
    Text y("Hello");

    cout << (x == y) << endl;
    cout << (x != y) << endl;

    cout << "\nASSIGNMENT\n";
    Text p;
    p = a;
    cout << p << endl;

    p = p;  // Self-assignment test
    cout << "After self-assignment: " << p << endl;

    cout << "\nEMPTY TEXT\n";
    Text empty;
    cout << "Empty text: [" << empty << "]" << endl;

    cout << "\nLONG TEXT TEST\n";
    Text longText("This is a long SMS message.");
    cout << longText << endl;

    cout << "\nCOPY CONSTRUCTOR COUNT: "
         << Text::getCopies() << endl;

    return 0;
}
