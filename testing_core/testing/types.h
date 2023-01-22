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


#ifndef CPP_SERIALIZERS_BENCHMARK_TESTING_CORE_TYPES_H
#define CPP_SERIALIZERS_BENCHMARK_TESTING_CORE_TYPES_H

#include <string>
#include <vector>
#include <valarray>
#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

namespace MyTypes {
    enum Color : uint8_t {
        Red,
        Green,
        Blue
    };

    struct Vec3 {
        float x;
        float y;
        float z;

        bool operator==(const MyTypes::Vec3 &rhs) const {
//            return x == rhs.x &&
//                   y == rhs.y &&
//                   z == rhs.z;
//    //compare with epsilon 0.05f
            std::valarray<float> lh({x, y, z});
            std::valarray<float> rh({rhs.x, rhs.y, rhs.z});
            return (std::abs(lh - rh) < 0.05f).min();
        };
    };

    struct Weapon {
        std::string name;
        int16_t damage;

        bool operator==(const Weapon &rhs) const {
            return name == rhs.name &&
                   damage == rhs.damage;
        };
    };

    struct Monster {
        Vec3 pos;
        int16_t mana;
        int16_t hp;
        std::string name;
        std::vector<uint8_t> inventory;
        Color color;
        std::vector<Weapon> weapons;
        Weapon equipped;
        std::vector<Vec3> path;
//        std::vector<uint8_t> image;
        cv::Mat image;

        bool areImagesEqual(const cv::Mat &a, const cv::Mat &b) const {
            if ((a.rows != b.rows) || (a.cols != b.cols))
                return false;
            cv::Scalar s = sum(a - b);
            return (s[0] == 0) && (s[1] == 0) && (s[2] == 0);
        }

        static bool areImagesEqual(const std::vector<uint8_t> &a, const std::vector<uint8_t> &b) {
            cv::Mat imgA = cv::imdecode(a, cv::IMREAD_UNCHANGED);
            cv::Mat imgB = cv::imdecode(b, cv::IMREAD_UNCHANGED);

            if ((imgA.rows != imgB.rows) || (imgA.cols != imgB.cols))
                return false;
            cv::Scalar s = sum(imgA - imgB);
            return (s[0] == 0) && (s[1] == 0) && (s[2] == 0);
        }


        bool operator==(const MyTypes::Monster &rhs) const {
            return pos == rhs.pos &&
                   mana == rhs.mana &&
                   hp == rhs.hp &&
                   name == rhs.name &&
                   inventory == rhs.inventory &&
                   color == rhs.color &&
                   weapons == rhs.weapons &&
                   equipped == rhs.equipped &&
                   path == rhs.path &&
                   areImagesEqual(image, rhs.image);
        };

    };

    std::vector<Monster> createMonsters(size_t count);
}

#endif //CPP_SERIALIZERS_BENCHMARK_TESTING_CORE_TYPES_H
