#pragma once

//#include <boost/lexical_cast.hpp>
#include <boost/random/mersenne_twister.hpp>
//#include <boost/random/uniform_int.hpp>
//#include <boost/random/variate_generator.hpp>

extern boost::mt19937 global_random_generator;

std::size_t random_int(std::size_t a, std::size_t b);

//std::size_t random_int(std::size_t a, std::size_t b) {
//    if (b < a)
//        b = a;
//    boost::uniform_int<> dist(a, b);
//    boost::variate_generator<boost::mt19937&, boost::uniform_int<> >
//        generate(global_random_generator, dist);
//    return generate();
//}