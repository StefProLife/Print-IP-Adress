#include <list>
#include <tuple>
#include <vector>
#include <iostream>
#include <type_traits>


const static std::string strSeparator = ".";
const static std::string strEmpty = "";


template <typename T>
struct is_string : std::is_same<std::string, T> {};


template <typename T>
struct is_vector : std::false_type {};

template <typename T>
struct is_vector<std::vector<T>> : std::true_type {};


template <typename T>
struct is_list : std::false_type {};

template <typename T>
struct is_list<std::list<T>> : std::true_type {};



template <typename T>
struct is_tuple : std::false_type {};

template <typename... Args>
struct is_tuple<std::tuple<Args...>> : std::true_type {};


template <typename TupleType, size_t... I>
void printTupleElements(const TupleType& t, std::index_sequence<I...>) {
    ((std::cout << std::get<I>(t) << (I != sizeof...(I) - 1 ? strSeparator : strEmpty)), ...);
}

template <typename... Args>
void print_ip(const std::tuple<Args...>& type) {
    printTupleElements(type, std::make_index_sequence<sizeof...(Args)>{});
    std::cout << std::endl;
}


template <typename T>
typename std::enable_if<std::is_integral<T>::value, void>::type
print_ip(T value)
{
    uint8_t* ptr = reinterpret_cast<uint8_t*>(&value);
    size_t size = sizeof(value);

    for (int i = size - 1; i >= 0; --i)
    {
        uint8_t byte = ptr[i];
        std::cout << static_cast<uint64_t>(byte);

        if (i != 0)
            std::cout <<  strSeparator;
    }

    std::cout << std::endl;
}

template <typename T>
typename std::enable_if<is_string<T>::value, void>::type
print_ip(T value)
{
    std::cout << value << std::endl;
}

template <typename T>
typename std::enable_if<is_vector<T>::value, void>::type
print_ip(const T& container)
{
    for (const auto& item : container)
    {
        std::cout << item;
        if (item != container.back())
            std::cout << strSeparator;
    }

    std::cout << std::endl;
}

template <typename T>
typename std::enable_if<is_list<T>::value, void>::type
print_ip(const T& container)
{
    int size = 0;
    for (const auto& item : container)
    {
        ++size;
        std::cout << item;
        if (size != container.size())
            std::cout << strSeparator;
    }

    std::cout << std::endl;
}

template <typename T>
typename std::enable_if<is_tuple<T>::value, void>::type
print_ip(const T& container)
{

    printTupleElements(container);
}

int main(int argc, char const* argv[])
{
    print_ip( int8_t { -1 } ); // 255
    print_ip( int16_t { 0 } ); // 0.0
    print_ip( int32_t { 2130706433 } ); // 127.0.0.1
    print_ip( int64_t { 8875824491850138409 } ); // 123.45.67.89.101.112.131.41
    print_ip( std::string { "Hello, World!"} ); // Hello, World!
    print_ip( std::vector<int> { 100, 200, 300, 400 } ); // 100.200.300.400
    print_ip( std::list<short> { 400, 300, 200, 100 } ); // 400.300.200.100
    print_ip( std::make_tuple( 123, 456, 789, 0 ) ); // 123.456.789.0
    return 0;
}