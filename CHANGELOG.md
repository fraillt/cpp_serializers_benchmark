# 2021-08-23

* updated bitsery 5.0.3 -> 5.2.1
* updated boost 1.72.0 -> 1.77.0
* updated flatbuufers 1.11.0 -> 2.0.0
* updated protobuf 3.11.2 -> 3.17.3
* updated yas 7.0.5 -> 7.1.0
* updated zpp 0.4 -> 0.5
* added msgpack 3.3.0 (thanks to [cnx-tcsikos](https://github.com/cnx-tcsikos))

# 2020-01-29

* updated bitsery 5.0.0 -> 5.0.3
* updated boost 1.70.0 -> 1.72.0
* updated cereal 1.2.2 -> 1.3.0
* updated yas 7.0.2 -> 7.0.5
* updated protobuf 3.8.0 -> 3.11.2
* updated zpp 0.3 -> 0.4

# 2019-07-09

* added protobuf tests
* updated bitsery 4.5.1 -> 5.0.0
* updated boost 1.69.0 -> 1.70.0
* updated flatbuffers 1.10.0 -> 1.11.0
* optimized flatbuffers serialization

# 2019-01-22

* updated bitsery 4.3.0 -> 4.5.1
* updated boost 1.66.0 -> 1.69.0
* updated flatbuffers 1.8.0 -> 1.10.0
* updated yas 6.0.3 -> 7.0.2
* updated zpp 0.1 -> 0.3
* updated compilers
  * gcc 7.3.0 -> 8.2.0
  * clang 5.0.1 -> 8.0.0
* updated test environment
  * ubuntu 17.10 -> 18.04

# 2018-08-23

* updated bitsery 4.2.1 -> 4.3.0
* added bitsery tests that doesn't check for buffer size on deserialization

# 2018-04-23

* added pull request for zpp serializer

# 2018-03-21

* updated testing frameworks
  * bitsery 4.1.0 -> 4.2.1
  * boost 1.65.1 -> 1.66.0
  * flatbuffers 1.7.1 -> 1.8.0
  * yas 5.0.0 -> 6.0.3
* updated test results with different compilers
  * ubuntu 16.04 -> 17.10
  * gcc 7.1.0 -> 7.2.0
  * clang 4.0.0 -> 5.0.0
* improved project sturcture
* added handwritten uniform distribution functions, to generate same test data on all platforms and compilers.
* added `tools` nodejs project, to help generate test results

# 2017-10-27

* updated bitsery 4.0.0 -> 4.1.0

# 2017-10-19

* added boost 1.65.1

# 2017-10-19

* created CMakeLists.txt for each library

# 2017-10-09

* initial commit with libraries:
  * bitsery 4.0.0
  * cereal 1.2.2
  * flatbuffers 1.7.1
  * yas 5.0.0
