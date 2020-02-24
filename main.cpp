#include<iostream>
#include<memory>

struct TemplateHelpers {
public:
    template <class X, class... Y>
    static constexpr bool IsSameClass(){
        return (!!IsSameClassHelper<X, Y>::value && ...);
    }

private:

    template <class A, class B>
    struct IsSameClassHelper {
        enum {value = false};
    };

    template <class T>
    struct IsSameClassHelper<T, T> {
        enum {value = true};
    };

};

class A {};
class B {};

int main() {

    const auto aa = new A();
    const auto ab = new A();

    constexpr auto ba = B();
    constexpr auto bb = B();

    std::cout << std::boolalpha;
    std::cout << TemplateHelpers::IsSameClass<std::decay_t<decltype(aa)>, A*>() << "\n";
    std::cout << TemplateHelpers::IsSameClass<std::decay_t<decltype(ba)>, std::decay_t<decltype(bb)>, A>() << "\n";
    std::cout << TemplateHelpers::IsSameClass<std::decay_t<decltype(aa)>, std::decay_t<decltype(ab)>, A*>() << "\n";
    std::cout << TemplateHelpers::IsSameClass<std::decay_t<decltype(ba)>, std::decay_t<decltype(bb)>, A>() << "\n";

    return 0;
}
