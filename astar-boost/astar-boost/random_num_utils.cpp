#include "random_num_utils.h"

#include <boost/random/uniform_int.hpp>
#include <boost/random/variate_generator.hpp>

boost::mt19937 global_random_generator;

std::size_t random_int(std::size_t a, std::size_t b) {
    if (b < a)
        b = a;
    boost::uniform_int<> dist(a, b);
    boost::variate_generator<boost::mt19937&, boost::uniform_int<> >
        generate(global_random_generator, dist);
    return generate();
}