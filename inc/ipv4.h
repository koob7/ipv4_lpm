#include <cstdint>
#include <cstdlib>
#include <optional>

class ipv4_t
{
    static constexpr uint8_t MASK_MAX_LENGTH = 32;

  public:
    union b4_32_t
    {
        uint8_t bytes[4];
        uint32_t value;
    };

    struct ip_address_t
    {
        b4_32_t host;
        b4_32_t mask;
        uint8_t get_mask_length() { return __builtin_popcount(mask.value); }
    } ip_address;

    ipv4_t() : ipv4_t(0, 0) {}
    ipv4_t(uint32_t host) : ipv4_t(host, 0xFFFFFFFF) {}
    ipv4_t(uint32_t host, uint32_t mask) : ip_address{{.value = host}, {.value = mask}} {}

    static std::optional<uint32_t> parse_host(const char *ip_str);
    static std::optional<uint32_t> parse_mask(const char *ip_str);

    bool valid_host_with_mask();

  private:
    static std::optional<uint8_t> read_numberf_from_string(char *&ptr);
};