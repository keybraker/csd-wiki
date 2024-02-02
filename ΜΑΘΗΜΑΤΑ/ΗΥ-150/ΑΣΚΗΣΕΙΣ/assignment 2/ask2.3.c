#include <std_lib_facilities.h>

float funk(float px, float py, float kx, float ky)
{ // these are all floats because we want to be specific ex. 1.4313245

    float solu, num;

    if (px > kx)
    { // Finds which posibilities is the correct one
        if (py > ky)
        { // and executes the I arithmetical sentence.
            num = ((px - kx) * (px - kx) + (kx - ky) * (kx - ky));
            solu = pow(num, 0.5);
        }
        else if (ky > py)
        {
            num = (px - kx) * (px - kx) + (ky - py) * (ky - py);
            solu = pow(num, 0.5); // Using function from cmath library because " ^ " is not valid in C++
        }
        else
        {
            solu = px - kx;
        }
    }
    else if (kx > px)
    { // There is a check for every possibility
        if (py > ky)
        {
            num = (kx - px) * (kx - px) + (py - ky) * (py - ky);
            solu = pow(num, 0.5);
        }
        else if (ky > py)
        {
            num = (kx - px) * (kx - px) + (ky - py) * (ky - py);
            solu = pow(num, 0.5);
        }
        else
        {
            solu = kx - px;
        }
    }
    else
    {
        if (py > ky)
        {
            solu = py - ky; // The two following solutions have the one point same
        }
        else if (ky > py)
        {
            solu = ky - py;
        }
        else
        {
            solu = 0; // Returning zero because the two points are the same
        }
    }
    return solu;
}

int main()
{

    float px, py, kx, ky;
    std::cout << "Enter the first point: ";
    std::cin >> px;
    std::cin >> py;
    std::cout << "Enter the second point: ";
    std::cin >> kx;
    std::cin >> ky;

    // Printing solution exactly as it was meant to be
    std::cout << "Distance between ( " << px << ", " << py << " ) and ( " << kx << ", " << ky << " ) is " << funk(px, py, kx, ky) << std::endl;

    return 0;
}
