#include <std_lib_facilities.h>

std::string functionname()
{                     // there are four function for the four words that have to be read
    std::string name; // there is also one fuction used to read a number
    std::cout << "Please enter a name:";
    std::cin >> name;
    return name;
}

std::string functionnoun()
{
    std::string noun;
    std::cout << "Please enter a plural noun:";
    std::cin >> noun;
    return noun;
}

int functionnumber()
{
    int number;
    std::cout << "Please enter a number:";
    std::cin >> number;
    return number;
}

std::string functionbodypart()
{
    std::string bodypart;
    std::cout << "Please enter a bodypart:";
    std::cin >> bodypart;
    return bodypart;
}

std::string functionverb()
{
    std::string verb;
    std::cout << "Please enter a verb:";
    std::cin >> verb;
    return verb;
}

int main()
{

    int number;
    std::string name, noun, bodypart, verb; // using string because char would only save the first character of the word

    std::cout << "Welcome to the Story Maker." << std::endl
              << std::endl;
    std::cout << "Answer the following questions to help me create a new story." << std::endl;

    name = functionname(); // getting all the information from functions
    noun = functionnoun();
    number = functionnumber();
    bodypart = functionbodypart();
    verb = functionverb(); // printing the story trough main

    std::cout << std::endl
              << std::endl
              << "Here's your story:" << std::endl;
    std::cout << "The famous explorer " << name << " had nearly given up a life long quest to find" << std::endl;
    std::cout << "The Lost City of " << noun << " when one day, the " << noun << " found the explorer." << std::endl;
    std::cout << "Surrounded by " << number << " " << noun << ", a tear came to " << name << "'s" << bodypart << " ." << std::endl;
    std::cout << "After all this time, the quest was finally over. And then, the " << noun << std::endl;
    std::cout << "promptly devoured " << name << ". The moral of the story ? Be careful what you " << verb << " for." << std::endl;

    return 0;
}
