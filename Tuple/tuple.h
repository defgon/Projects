#ifndef TUPLE_H
#define TUPLE_H

#include <utility>

namespace my {

namespace detail {

// forward declaration
template <std::size_t I, typename... Types>
class storage;

// template specialization
template <std::size_t I, typename Head, typename... Tail>
class storage<I, Head, Tail...>
: public storage<I + 1, Tail...>
{
private:
    Head value;

public:
    storage() = default;
    storage(const storage&) = default;
    storage(storage&&) = default;
    storage& operator=(const storage&) = default;
    storage& operator=(storage&&) = default;

    // constructor with parameters
    storage(Head head, Tail... args)
    : detail::storage<I + 1, Tail...>(args...),
      value(head)
    {}

    // accessor for the attribute
    Head& get(std::integral_constant<std::size_t, I>)
    {
        return value;
    }

    const Head& get(std::integral_constant<std::size_t, I>) const
    {
        return value;
    }

    // NOTE: this makes all methods from base classes accessible for lookup in this class
    using storage<I + 1, Tail...>::get;
};

// specialization to terminate recursion
template <std::size_t I>
class storage<I>
{
public:
    // NOTE: this makes `using storage<I + 1, Tail...>::get;` work for empty Tail
    void get() {}
};

} // namespace detail

template <typename... Types>
class tuple
: public detail::storage<0, Types...>
{
public:
    tuple() = default;
    tuple(const tuple&) = default;
    tuple(tuple&&) = default;
    tuple& operator=(const tuple&) = default;
    tuple& operator=(tuple&&) = default;

    // constructor with parameters
    tuple(Types... args)
    : detail::storage<0, Types...>(args...)
    {}
    // mozne operace s args:
    // 1. expandovani: args...
    // 2. zjistit pocet: sizeof...(args)
};

} // namespace my

// Note: tuple-like types implement the tuple protocol, i.e., such types can be used with std::get, std::tuple_element and std::tuple_size.
// Elements of tuple-like types can be bound with structured binding.
namespace std {

// std::tuple_size provides access to the number of elements in a tuple as a compile-time constant expression.
template <typename... Types>
struct tuple_size< my::tuple<Types...> >
: std::integral_constant<std::size_t, sizeof...(Types)>
{};

// std::tuple_element provides compile-time indexed access to the types of the elements of the tuple.
//
// recursive case
template <std::size_t I,
          typename Head, typename... Tail>
struct tuple_element<I, my::tuple<Head, Tail...>>
: tuple_element<I - 1, my::tuple<Tail...>>
{};

// base case
template <typename Head, typename... Tail>
struct tuple_element<0, my::tuple<Head, Tail...>>
{
    using type = Head;
};

} // namespace std


namespace my {

template <std::size_t I, typename... Types>
typename std::tuple_element<I, tuple<Types...>>::type&
get(tuple<Types...>& tpl)
{
    // compiler finds the member function by tag dispatch
    using tag = std::integral_constant<std::size_t, I>;
    return tpl.get(tag());
}

template <std::size_t I, typename... Types>
const typename std::tuple_element<I, tuple<Types...>>::type&
get(const tuple<Types...>& tpl)
{
    // compiler finds the member function by tag dispatch
    using tag = std::integral_constant<std::size_t, I>;
    return tpl.get(tag());
}

} // namespace my

#endif // TUPLE_H
