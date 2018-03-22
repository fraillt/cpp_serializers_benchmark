//MIT License
//
//Copyright (c) 2017 Mindaugas Vinkelis
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.

#ifndef CPP_SERIALIZERS_BENCHMARK_UNIFORM_DISTRIBUTIONS_H
#define CPP_SERIALIZERS_BENCHMARK_UNIFORM_DISTRIBUTIONS_H

#include <type_traits>
#include <cassert>

//simple implementations of uniform distribution functions to generate same test data on different platforms.
template <typename TValue>
class UniformIntDistribution {
public:
    static_assert(std::is_integral<TValue>::value, "");
    UniformIntDistribution(TValue a, TValue b = std::numeric_limits<TValue>::max())
            :_a{a}, _b{b}
    {
        assert(a < b);
    }

    template <typename Engine>
    TValue operator()(Engine& eng) {
        auto urange = _b - _a;
        auto erange = eng.max() - eng.min();
        assert(erange > urange);
        auto scale = erange / urange;
        while (true) {
            auto res = eng() - eng.min();
            if (res >= scale * urange)
                continue;
            return res / scale + _a;
        }
    }
private:
    TValue _a;
    TValue _b;
};

template <typename TValue>
class UniformRealDistribution {
public:
    static_assert(std::is_floating_point<TValue>::value, "");
    UniformRealDistribution(TValue a, TValue b)
            :_a{a}, _b{b}
    {
        assert(a < b);
    }

    template <typename Engine>
    TValue operator()(Engine& eng) {
        auto urange = _b - _a;
        auto erange = eng.max() - eng.min();
        return static_cast<TValue>(eng()) / erange * (urange) + _a;
    }
private:
    TValue _a;
    TValue _b;
};

#endif //CPP_SERIALIZERS_BENCHMARK_UNIFORM_DISTRIBUTIONS_H
