#include <iostream>
#include <ipv4.h>

std::optional<uint8_t> ipv4_t::read_numberf_from_string(char *&ptr)
{
    uint32_t number = strtoul(ptr, &ptr, 10);
    if (ptr == nullptr)
    {
        return std::nullopt;
    }

    if (number > UINT8_MAX)
    {
        return std::nullopt;
    }

    return static_cast<uint8_t>(number);
}

std::optional<uint32_t> ipv4_t::parse_host(const char *ip_str)
{
    char *pointer = const_cast<char *>(ip_str);

    b4_32_t value{};

    std::optional<uint8_t> number;

    for (uint8_t i = 0; i < sizeof(value.bytes); i++)
    {

        if (*pointer == '\0')
        {
            return std::nullopt;
        }

        number = read_numberf_from_string(pointer);
        if (!number)
        {
            return std::nullopt;
        }

        value.bytes[i] = *number;

        if (*pointer != '.' && i < sizeof(value.bytes) - 1)
        {
            return std::nullopt;
        }
        pointer++;
    }

    return value.value;
}

std::optional<uint32_t> ipv4_t::parse_mask(const char *ip_str)
{
    char *pointer = const_cast<char *>(ip_str);
    while (*pointer != '/')
    {
        if (*pointer == '\0')
        {
            return std::nullopt;
        }

        pointer++;
    }

    uint32_t mask = strtoul(pointer + 1, &pointer, 10);

    if (pointer == nullptr)
    {
        return std::nullopt;
    }

    if (mask > MASK_MAX_LENGTH)
    {
        return std::nullopt;
    }

    return (static_cast<uint64_t>(1) << mask) - 1;
}

bool ipv4_t::valid_host_with_mask()
{
    bool result = true;

    result &= ip_address.host.value != 0;
    result &= ip_address.mask.value != 0;

    result &= (ip_address.host.value & ip_address.mask.value) == ip_address.host.value;

    uint8_t mask_length = ip_address.get_mask_length();

    return result;
}

void ipv4_t::print_address()
{
    std::cout << "IP Address: ";

    for (size_t i = 0; i < sizeof(ip_address.host.bytes); i++)
    {
        std::cout << static_cast<int>(ip_address.host.bytes[i]);
        if (i < sizeof(ip_address.host.bytes) - 1)
        {
            std::cout << ".";
        }
    }

    std::cout << "/" << __builtin_popcount(ip_address.mask.value) << "\n";
}
