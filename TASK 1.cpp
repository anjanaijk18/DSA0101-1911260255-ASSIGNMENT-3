#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

class Book
{
    string title;
    int copies;

public:
    Book(string t, int c) : title(t), copies(c)
    {
        if(c < 0)
            throw invalid_argument("Invalid number of copies");
    }

    Book() : Book("Empty Record", 0) {}

    Book(string t) : Book(t, 1) {}

    void display()
    {
        cout << "Title: " << title
             << " | Copies: " << copies << endl;
    }
};

int main()
{
    try
    {
        Book b1("C++ Programming", 5);
        Book b2("Python Programming");
        Book b3;

        cout << "BOOK RECORDS\n";
        b1.display();
        b2.display();
        b3.display();

        cout << "\nBOOK ARRAY\n";
        Book books[2];

        for(int i = 0; i < 2; i++)
            books[i].display();

        cout << "\nNEGATIVE COPY TEST\n";
        Book b4("Java Programming", -3);
    }
    catch(const invalid_argument &e)
    {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
