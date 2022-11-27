#include <boost/unordered_map.hpp>
namespace boost{
    template <typename T> using coord = boost::tuples::tuple<T, T, T>;

    template <typename T> struct ihash
        : std::unary_function<coord<T>, std::size_t>
    {
        std::size_t operator()(coord<T> const& e) const
        {
            std::size_t seed = 0;
            boost::hash_combine( seed, e.template get<0>() );
            boost::hash_combine( seed, e.template get<1>() );
            boost::hash_combine( seed, e.template get<2>() );
            return seed;
        }
    };

    template <typename T> struct iequal_to
        : std::binary_function<coord<T>, coord<T>, bool>
    {
        bool operator()(coord<T> const& x, coord<T> const& y) const
        {
            return ( x.template get<0>()==y.template get<0>() &&
                    x.template get<1>()==y.template get<1>() &&
                    x.template get<2>()==y.template get<2>());
        }
    };
    template <typename T> using coord_map = boost::unordered_map< coord<T>, int, ihash<T>, iequal_to<T> >;
}