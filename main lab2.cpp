#include <iostream>
#include <stdexcept>
#include <iomanip>

class TimeOfDay {
private:
    int h, m, s; // hours, minutes, seconds (0–23, 0–59, 0–59)

    static int toTotal(int hh, int mm, int ss) {
        if (hh < 0 || hh > 23 || mm < 0 || mm > 59 || ss < 0 || ss > 59)
            throw std::out_of_range("Invalid time (out of range)");
        return hh * 3600 + mm * 60 + ss;
    }

    static void fromTotal(int total, int &hh, int &mm, int &ss) {
        if (total < 0 || total > 86399)
            throw std::out_of_range("Total seconds out of range");
        hh = total / 3600;
        mm = (total % 3600) / 60;
        ss = total % 60;
    }

public:
    // Default constructor (00:00:00)
    TimeOfDay() : h(0), m(0), s(0) {}

    // Parameterized constructor
    TimeOfDay(int hh, int mm, int ss) { set(hh, mm, ss); }

    // Destructor
    ~TimeOfDay() {}

    // Set and validate time
    void set(int hh, int mm, int ss) {
        (void)toTotal(hh, mm, ss);
        h = hh; m = mm; s = ss;
    }

    // Read time from user
    void read() {
        int hh, mm, ss;
        std::cout << "Enter time (hours minutes seconds): ";
        std::cin >> hh >> mm >> ss;
        set(hh, mm, ss);
    }

    // Print in 00:00:00 format
    void print() const {
        std::cout << std::setfill('0') << std::setw(2) << h << ":"
                  << std::setw(2) << m << ":" << std::setw(2) << s;
    }

    // Compute time left until end of day
    void timeLeft(int &H, int &M, int &S) const {
        int total = toTotal(h, m, s);
        int delta = 86400 - 1 - total;
        if (delta < 0) delta = 0;
        fromTotal(delta, H, M, S);
    }

    // Add or subtract seconds
    TimeOfDay operator+(int seconds) const {
        int total = toTotal(h, m, s) + seconds;
        if (total < 0 || total > 86399)
            throw std::out_of_range("Resulting time out of range");
        int hh, mm, ss;
        fromTotal(total, hh, mm, ss);
        return TimeOfDay(hh, mm, ss);
    }

    TimeOfDay operator-(int seconds) const {
        return (*this) + (-seconds);
    }
};

int main() {
    std::cout << "=== TimeOfDay Class Demo ===\n";
    TimeOfDay t;
    t.read();

    std::cout << "Current time: ";
    t.print();
    std::cout << "\n";

    int H, M, S;
    t.timeLeft(H, M, S);
    std::cout << "Time left until midnight: "
              << std::setfill('0') << std::setw(2) << H << ":"
              << std::setw(2) << M << ":" << std::setw(2) << S << "\n";

    try {
        TimeOfDay t2 = t + 75;
        std::cout << "t + 75 sec = ";
        t2.print();
        std::cout << "\n";

        TimeOfDay t3 = t - 90;
        std::cout << "t - 90 sec = ";
        t3.print();
        std::cout << "\n";
    } catch (const std::exception &ex) {
        std::cout << "Error: " << ex.what() << "\n";
    }

    return 0;
}
