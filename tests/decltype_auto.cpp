template<typename T>
decltype(auto) test(T const& val) {
    return val;
}

auto main() -> int {
    auto const& i = test(42);
}
