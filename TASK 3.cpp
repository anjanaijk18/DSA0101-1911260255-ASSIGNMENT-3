#include <iostream>
using namespace std;

class Event
{
    int rows, seats;
    bool** seatMap;
    int booked;

public:
    Event(int r, int s) : rows(r), seats(s), booked(0)
    {
        seatMap = nullptr;

        if(rows > 0)
        {
            seatMap = new bool*[rows];

            for(int i = 0; i < rows; i++)
            {
                seatMap[i] = new bool[seats]();

            }
        }

        cout << "Event created: "
             << rows << " rows\n";
    }

    void bookSeat(int r, int s)
    {
        if(r >= 0 && r < rows &&
           s >= 0 && s < seats &&
           !seatMap[r][s])
        {
            seatMap[r][s] = true;
            booked++;
            cout << "Seat booked\n";
        }
        else
            cout << "Invalid or occupied seat\n";
    }

    void cancelSeat(int r, int s)
    {
        if(r >= 0 && r < rows &&
           s >= 0 && s < seats &&
           seatMap[r][s])
        {
            seatMap[r][s] = false;
            booked--;
            cout << "Booking cancelled\n";
        }
        else
            cout << "Seat is not booked\n";
    }

    ~Event()
    {
        for(int i = 0; i < rows; i++)
            delete[] seatMap[i];

        delete[] seatMap;

        cout << "Event closed. Booked seats: "
             << booked << endl;
    }

    Event(const Event&) = delete;
    Event& operator=(const Event&) = delete;
};

int main()
{
    cout << "STACK OBJECT\n";
    Event e1(2, 3);
    e1.bookSeat(0, 1);
    e1.bookSeat(1, 2);
    e1.cancelSeat(0, 1);

    cout << "\nBLOCK OBJECT\n";
    {
        Event e2(2, 2);
        e2.bookSeat(0, 0);
    }

    cout << "\nHEAP OBJECT\n";
    Event* e3 = new Event(3, 3);
    e3->bookSeat(1, 1);
    delete e3;

    cout << "\nZERO ROW TEST\n";
    Event e4(0, 5);

    cout << "\nProgram End\n";

    return 0;
}
