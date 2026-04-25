#include <iostream>
#include <ipv4.h>
#include <vector>

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

#define ROUTING_ADDRESSES 2

int main(int argc, char *argv[])
{
    if (argc != 1 + ROUTING_ADDRESSES + 1) // first argument is the program name, so we need 4 arguments in total
    {
        std::cout << "Wrong number of arguments passed\n";
        std::cout << "you should pass 2 ip addresses with mask in short format and one ip address\n";
        std::cout << "example: ./ipv4_lpm 194.168.1.0/24 10.0.0.0/8 192.168.1.1\n";

        return 1;
    }

    std::vector<ipv4_t> routing_table;

    std::optional<uint32_t> host;
    std::optional<uint32_t> mask;
    ipv4_t ip_address;

    for (size_t i = 1; i < 1 + ROUTING_ADDRESSES; i++)
    {
        host = ipv4_t::parse_host(argv[i]);
        mask = ipv4_t::parse_mask(argv[i]);

        if (!host || !mask)
        {
            std::cout << "Wrong format of ip address nr: " << i << "\n";
            return 1;
        }

        ip_address = ipv4_t(*host, *mask);

        if (!ip_address.valid_host_with_mask())
        {
            std::cout << "IP address not possible nr: " << i << "\n";
            return 1;
        }

        routing_table.emplace_back(*host, *mask);
    }

    host = ipv4_t::parse_host(argv[1 + ROUTING_ADDRESSES]);

    ipv4_t ip_address_to_find(*host);

    ipv4_t *best_match = nullptr;

    for (auto &entry : routing_table)
    {
        if ((ip_address_to_find.ip_address.host.value & entry.ip_address.mask.value) == entry.ip_address.host.value)
        {
            if (best_match == nullptr || entry.ip_address.get_mask_length() > best_match->ip_address.get_mask_length())
            {
                best_match = &entry;
            }
        }
    }

    if (best_match)
    {
        std::cout << "Best match found: ";
        best_match->print_address();
    }
    else
    {
        std::cout << "No match found\n";
    }

    return 0;
}