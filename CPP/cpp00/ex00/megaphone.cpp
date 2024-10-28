#include <iostream>
#include <cctype> // Pour std::toupper

/****************************************************************************

$>./megaphone "shhhhh... I think the students are asleep..."
SHHHHH... I THINK THE STUDENTS ARE ASLEEP...
$>./megaphone Damnit " ! " "Sorry students, I thought this thing was off."
DAMNIT ! SORRY STUDENTS, I THOUGHT THIS THING WAS OFF.
$>./megaphone
* LOUD AND UNBEARABLE FEEDBACK NOISE *
$>

******************************************************************************/

void     StrToUpper(char *s)
{
    int len = strlen(s);
    for(int i = 0; i < len; i++)
        std::cout << static_cast<char>(std::toupper(s[i]));
}

int main(int argc, char** argv)
{
    if (argc == 1)
        std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *"<< std::endl;
    else
    {
        for (int i = 1; i < argc; i++)
            StrToUpper(argv[i]);
        std::cout<<std::endl;
    }
    return 0;
}
