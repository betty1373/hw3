#include "version.h"
#include "lib.h"
namespace libSrc 
{
    int version()
    {
        return PROJECT_VERSION_PATCH;
    }

    ip_str_t split(const std::string &str, char d)
    {
        ip_str_t r;

        std::string::size_type start = 0;
        std::string::size_type stop = str.find_first_of(d);
        while(stop != std::string::npos)
        {
            r.emplace_back(str.substr(start, stop - start));

            start = stop + 1;
            stop = str.find_first_of(d, start);
        }

        r.emplace_back(str.substr(start));
        return r;
    }
    ip_t strToInt(const ip_str_t &str_ip)
    {
        ip_t r;

        for (auto &part :str_ip)
        {
            r.emplace_back(std::stoi(part));
        }
        return r;
    }

    void sort(ip_pool_t &ip_pool)
    {
        std::sort(ip_pool.begin(),ip_pool.end(),std::greater<ip_t>());
    }

    void print(const ip_pool_t &ip_pool)
    {
        for(auto& ip : ip_pool)
        {
            for(auto& ip_part : ip)
            {
                if (&ip_part != &ip[0])
                {
                    std::cout << ".";

                }
                std::cout << ip_part;
            }
            std::cout << std::endl;
        }
    }

    ip_pool_t filter(const ip_pool_t &ip_pool, int part)
    {
        ip_pool_t r;

        for(auto& ip : ip_pool)
        {
            if (ip[0]==part) r.emplace_back(ip);
        }
        return r;
    }
    ip_pool_t filter(const ip_pool_t &ip_pool, int part1, int part2)
    {
        ip_pool_t r;

        for(auto& ip : ip_pool)
        {
            if (ip[0]==part1 && ip[1]==part2) r.emplace_back(ip);
        }
        return r;
    }
    ip_pool_t filter_any(const ip_pool_t &ip_pool, int part)
    {
        ip_pool_t r;
        for(auto& ip : ip_pool)
        {
            for(auto& ip_part : ip)
            {
                if (ip_part == part) r.emplace_back(ip);
            }
        }
        return r;
    }
}
