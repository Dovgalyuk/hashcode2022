#include <iostream>
#include <fstream>

std::ifstream in;
std::ofstream out;

int main(int argc, char **argv)
{
    if (argc < 3)
        return 1;

    in.open(argv[1]);
    out.open(argv[2]);

    out << "Answer\n";
}
