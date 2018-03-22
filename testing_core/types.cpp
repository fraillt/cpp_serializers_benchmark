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


#include <testing/types.h>
#include <random>
#include <functional>
#include <iostream>
#include "uniform_distributions.h"


static UniformIntDistribution<int16_t> rand_char((int16_t) 'A', (int16_t) 'Z');
static UniformIntDistribution<int> rand_len(1, 10);
static UniformIntDistribution<int16_t> rand_nr(0);
static UniformRealDistribution<float> rand_float(-1.0f, 1.0f);

typedef std::mersenne_twister_engine<
        uint_fast32_t,
        32, 624, 397, 31,
        0x9908b0dfUL, 11,
        0xffffffffUL, 7,
        0x9d2c5680UL, 15,
        0xefc60000UL, 18, 1812433253UL>
        engine;

namespace MyTypes {

    static Weapon createRandomWeapon(engine &e) {
        Weapon res;
        res.damage = rand_nr(e);
        std::generate_n(std::back_inserter(res.name), rand_len(e), std::bind(rand_char, std::ref(e)));
        return res;
    }

    Monster createRandomMonster(engine &e) {
        Monster res{};
        std::generate_n(std::back_inserter(res.name), rand_len(e), std::bind(rand_char, std::ref(e)));
        res.pos.x = rand_float(e);
        res.pos.y = rand_float(e);
        res.pos.z = rand_float(e);
        res.color = static_cast<MyTypes::Color>(rand_len(e) % static_cast<int>(3));
        res.hp = rand_nr(e) % 1000;
        res.mana = std::abs(rand_nr(e) % 500);
        static_assert(std::is_copy_constructible<engine>::value, "");
        std::generate_n(std::back_inserter(res.inventory), rand_len(e), std::bind(rand_len, std::ref(e)));
        std::generate_n(std::back_inserter(res.path), rand_len(e), [&]() {
            return Vec3{rand_float(e), rand_float(e), rand_float(e)};
        });
        res.equipped = createRandomWeapon(e);
        std::generate_n(std::back_inserter(res.weapons), rand_len(e), std::bind(createRandomWeapon, std::ref(e)));
        return res;
    }

    std::vector<MyTypes::Monster> createMonsters(size_t count) {
        std::vector<MyTypes::Monster> res{};
        //always the same seed
        std::seed_seq seed{1,2,3};
        engine e{seed};

        std::generate_n(std::back_inserter(res), count, std::bind(createRandomMonster, std::ref(e)));
        return res;
    }

}

