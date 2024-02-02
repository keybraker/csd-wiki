#include <std_lib_facilities.h>

float calculateCharges(int c)
{
    if (c < 3)
    {
        return 2;
    }
    else if (c < 20)
    {                                 // There is 20 and not 24 because 20 minus 1 is the
        return (((c - 3) * 0.5) + 2); // 19 that if dicreased by 3 (the hours
    }
    else
    {              // from the beggining) = 16 multiplied with 0.5
        return 10; // gives 8 plus 2 = 10 euro which is our charge limit.
    }
    return -1;
}

int main()
{

    float c1, c2, c3, nc1, nc2, nc3;                   // I used floats for my time because time can be anything
    std::cout << "Enter the hours parked for 3 cars:"; // But when I pass the data to my function it comes as an
    std::cin >> c1;                                    // int because i dont care about minutes but about hours.
    if (c1 < 0)
    {
        std::cout << "Error: negative time" << std::endl;
        return 0;
    }
    std::cin >> c2;
    if (c2 < 0)
    {
        std::cout << "Error: negative time" << std::endl;
        return 0;
    }
    std::cin >> c3;
    if (c3 < 0)
    {
        std::cout << "Error: negative time" << std::endl;
        return 0;
    }

    nc1 = calculateCharges(c1);
    nc2 = calculateCharges(c2);
    nc3 = calculateCharges(c3);

    std::cout << "Car          Hours          Charge" << std::endl;
    std::cout << " 1            " << c1 << "              " << nc1 << std::endl;
    std::cout << " 2            " << c2 << "              " << nc2 << std::endl;
    std::cout << " 3            " << c3 << "              " << nc3 << std::endl;
    std::cout << "TOTAL         " << c1 + c2 + c3 << "              " << nc1 + nc2 + nc3 << std::endl;

    return 0;
}
