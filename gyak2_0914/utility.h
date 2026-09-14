#ifndef INC_01_VALTOZOK_UTILITY_H
#define INC_01_VALTOZOK_UTILITY_H

#include <string_view>

// Függvény egy típusnév szöveggé alakítására.
// A __PRETTY_FUNCTION__ egy compiler által létrehozott string, tartalma a
// függvény amiből elérik. A függvény nevének része a template paraméter neve,
// így kapjuk meg a típusnevet. Mivel compiler hozza létre és nincs a
// standardban, értéke függ a compilertől, ezért szükséges az ifdef-ekben
// compiler specifikus megoldásokat használni.
// Kevésbé szép eredményt ad a typeid(var).name()
// Clang: __clang__ g++: __GNUC__ MSVC: __MSC_VER
// Forrás:
// https://stackoverflow.com/questions/81870/is-it-possible-to-print-a-variables-type-in-standard-c
template <typename T> constexpr auto type_name() noexcept {
    std::string_view name, prefix, suffix;
#ifdef __clang__
    name = __PRETTY_FUNCTION__;
    prefix = "auto type_name() [T = ";
    suffix = "]";
#elif defined(__GNUC__)
    name = __PRETTY_FUNCTION__;
    prefix = "constexpr auto type_name() [with T = ";
    suffix = "]";
#elif defined(_MSC_VER)
    name = __FUNCSIG__;
    prefix = "auto __cdecl type_name<";
    suffix = ">(void) noexcept";
#endif
    name.remove_prefix(prefix.size());
    name.remove_suffix(suffix.size());
    return name;
}

#endif // INC_01_VALTOZOK_UTILITY_H