#include <string_view>
#include <iostream>
#include "cons.hpp"


struct S
{
    S() = default;
    explicit S(int) {}

    std::string_view get_value()
    {
        return "not-const";
    }

    std::string_view get_value() const
    {
        return "const";
    }
};

const S &as_const(const S &s) { return s; }

// of:

template<typename Obj>
const Obj &as_const_t(const Obj &s) { return s; }



int main()
{
    S s;
    std::cout << "A string: " << s.get_value() << std::endl;
    std::cout << "A string: " << const_cast<const S &>(s).get_value() << std::endl;
    std::cout << "A string: " << static_cast<const S &>(s).get_value() << std::endl;
    std::cout << "A string: " << as_const(s).get_value() << std::endl;
    std::cout << "A string: " << as_const_t(s).get_value() << std::endl;

    const S ss;
    std::cout << "A string: " << ss.get_value() << std::endl;


    return 0;
}

