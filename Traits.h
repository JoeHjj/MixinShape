#pragma once

#include <cstddef>
#include <type_traits>

template<typename... Types> struct typeList_t{};

template<auto index, typename... Types>
struct selectTypeByIndex;

/* no types to return */
template<auto index>
struct selectTypeByIndex<index>
{
    using type = std::nullptr_t;
};

template<auto index>
struct selectTypeByIndex<index, typeList_t<>>
{
    using type = std::nullptr_t;
};

/* return first type */
template<typename Type>
struct selectTypeByIndex<0, Type>
{
    using type = Type;
};

template<typename Type, typename... Types>
struct selectTypeByIndex<0, Type, Types...>
{
    using type = Type;
};

/* return others */
template<auto index, typename Type, typename... Types>
struct selectTypeByIndex<index, Type, Types...>
{
    using type = std::conditional_t<index==0,
        Type, typename selectTypeByIndex<index-1, Types...>::type>;
};


/* type list */
template<typename Type, typename... Types>
struct selectTypeByIndex<0, typeList_t<Type, Types...>>
{
    using type = Type;
};


template<auto index, typename Type, typename... Types>
struct selectTypeByIndex<index, typeList_t<Type, Types...>>
{
    using type = std::conditional_t<index==0,
        Type, typename selectTypeByIndex<index-1, Types...>::type>;
};

template<auto index, typename... Types>
using selectTypeByIndex_t = typename selectTypeByIndex<index, Types...>::type;

template<typename... Types>
struct typesCount
{
    static constexpr size_t value = sizeof...(Types);
};

template<typename... Types>
struct typesCount<typeList_t<Types...>>
{
    static constexpr size_t value = sizeof...(Types);
};

template<typename... Types>
constexpr auto typesCount_v = typesCount<Types...>::value;

template<typename T, typename... Ts>
using enable_if_all = std::enable_if_t<std::conjunction_v<std::is_same<T, Ts>...>>;

template<typename T, typename... Ts>
using enable_if_any = std::enable_if_t<std::disjunction_v<std::is_same<T, Ts>...>>;
