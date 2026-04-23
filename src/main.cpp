#include <iostream>

// -exec p/x argv[0]
// $2 = 0x1a28f42f3d0
// -exec p/x *argv[0]
// $3 = 0x44
// -exec p *argv[0]
// $4 = 68 'D'
// -exec p *argv[1]
// $5 = 49 '1'
// -exec p *argv[2]
// $6 = 50 '2'
// -exec p *argv[3]
// $7 = 51 '3'
// -exec p *argv[4]

int main(int argc, char *argv[])
{
    if (argc != 4) // first argument is the program name, so we need 4 arguments in total
    {
        std::cout << "Usage: ./ipv4_lpm prefix1 prefix2 ip\n";
        return 1;
    }

    std::cout << "OK - program działa\n";
    return 0;
}