#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <vector>

#define USE_PRETTY 1

template<typename T,size_t lot>
struct logging_allocator {
    using value_type = T;

    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    template<typename U>
    struct rebind {
        using other = logging_allocator<U,lot>;
    };

    logging_allocator() = default;
    ~logging_allocator() = default;

    // template<typename U,size_t num> 
    // logging_allocator(const logging_allocator<U>&,) {

    // }

    T *allocate(std::size_t n) {
#ifndef USE_PRETTY
        std::cout << "allocate: [n = " << n << "]" << std::endl;
#else
        std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
#endif
        if (bufCnt+n > lot){
            throw std::bad_alloc();
        }
        if (!bufPtr){
            bufPtr = reinterpret_cast<pointer>(std::malloc(n+sizeof(T)));
        }
        
        if (!bufPtr){
            throw std::bad_alloc();
        }
        pointer pp = bufPtr+bufCnt;
        bufCnt += n;
        return pp;
    }

    void deallocate(T *p, std::size_t n) {
#ifndef USE_PRETTY
        std::cout << "deallocate: [n  = " << n << "] " << std::endl;
#else
        std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
#endif
        if (!p) return;
        if ((bufCnt-=n)!=0) return;
        std::free(bufPtr);
        bufPtr = nullptr;
    }

    template<typename U, typename ...Args>
    void construct(U *p, Args &&...args) {
#ifndef USE_PRETTY
        std::cout << "construct" << std::endl;
#else
        std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
        new(p) U(std::forward<Args>(args)...);
    };

    void destroy(T *p) {
#ifndef USE_PRETTY
        std::cout << "destroy" << std::endl;
#else
        std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
        p->~T();
    }
    private:
        pointer bufPtr = nullptr;
        size_t bufCnt = 0;  
};
template<typename Container>
void printContainter(const Container& values) {
    for (auto v : values)
        std::cout << v << ' ';
    std::cout << std::endl;
};
std::ostream& operator<<(std::ostream& os, const std::pair<const int, int>& pair) {
    os << pair.first << " " << pair.second << '\n';
    return os;
};
int fact(int V) {
    return (V==0 || V==1) ? 1 :fact(V-1) * V;
};

int main(int, char *[]) {
    const int num_els = 12;
    auto std_map = std::map<int,int,std::less<int>,std::allocator<std::pair<const int,int>>>{};  

    for (auto i=0;i<num_els;++i) {
        std_map.emplace(std::pair<int,int>(i,fact(i)));
    }

    auto cust_map = std::map<int,int,std::less<int>,logging_allocator<std::pair<const int,int>,num_els>>{};  

    for (auto i=0;i<num_els;++i) {
        cust_map.emplace(std::pair<int,int>(i,fact(i)));
    }
    printContainter(cust_map);
    return 0;
}
