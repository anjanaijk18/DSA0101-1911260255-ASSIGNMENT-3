#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <stdexcept>
#include <chrono>
using namespace std;

class Time
{
    int hour, minute, second;

    void normalize()
    {
        if(++second == 60)
        {
            second = 0;
            if(++minute == 60)
            {
                minute = 0;
                ++hour;
            }
        }
    }

public:
    Time(int h=0, int m=0, int s=0)
        : hour(h), minute(m), second(s) {}

    // Prefix increment
    Time& operator++()
    {
        normalize();
        return *this;
    }

    // Postfix increment
    Time operator++(int)
    {
        Time old = *this;
        normalize();
        return old;
    }

    bool operator==(const Time& t) const
    {
        return hour == t.hour &&
               minute == t.minute &&
               second == t.second;
    }

    bool operator<(const Time& t) const
    {
        return hour*3600 + minute*60 + second <
               t.hour*3600 + t.minute*60 + t.second;
    }

    void display() const
    {
        cout << setfill('0') << setw(2) << hour << ":"
             << setw(2) << minute << ":"
             << setw(2) << second << setfill(' ');
    }
};

class Playlist
{
    vector<string> tracks;

public:
    Playlist(vector<string> t) : tracks(t) {}

    // Non-const subscript
    string& operator[](int%20i)
    {
        if(i < 0 || i >= (int)tracks.size())
            throw out_of_range("Invalid playlist index");
        return tracks[i];
    }

    // Const subscript
    const string& operator[](int%20i) const
    {
        if(i < 0 || i >= (int)tracks.size())
            throw out_of_range("Invalid playlist index");
        return tracks[i];
    }

    int size() const
    {
        return tracks.size();
    }
};

struct Counter
{
    int v;

    Counter& operator++()
    {
        ++v;
        return *this;
    }

    Counter operator++(int)
    {
        Counter old = *this;
        ++v;
        return old;
    }
};

int main()
{
    cout << "INCREMENT TEST\n";

    Counter c{5};
    Counter a = c++;
    Counter b = ++c;

    cout << a.v << " " << b.v << " " << c.v << endl;

    cout << "\nTIME ROLL-OVER\n";

    Time t(0, 59, 59);
    ++t;
    t.display();

    cout << "\n\nTIME COMPARISON\n";

    Time t1(1, 0, 0);
    Time t2(1, 0, 0);

    cout << boolalpha << (t1 == t2) << endl;
    cout << (t < t1) << endl;

    cout << "\nPLAYLIST\n";

    Playlist p({"Song A", "Song B", "Song C"});

    for(int i = 0; i < p.size(); i++)
        cout << p[i] << endl;

    p[1] = "Updated Song";
    cout << "\nUpdated: " << p[1] << endl;

    cout << "\nINVALID INDEX TEST\n";

    try
    {
        cout << p[-1];
    }
    catch(const out_of_range& e)
    {
        cout << "Error: " << e.what() << endl;
    }

    try
    {
        cout << p[p.size()];
    }
    catch(const out_of_range& e)
    {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
