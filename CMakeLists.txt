cmake_minimum_required(VERSION 3.22)
project(DeltaHedger)

set(CMAKE_CXX_STANDARD 20)

include_directories(src)

add_executable(DeltaHedger main.cpp
        src/BlackScholesModel/BlackScholesModel.cpp
        src/BlackScholesModel/BlackScholesModel.hpp
        src/DeltaHedger/DeltaHedger.cpp
        src/DeltaHedger/DeltaHedger.hpp
        src/Options/Option.hpp
        src/Options/CallOption.cpp
        src/Options/CallOption.hpp
        src/Options/PutOption.cpp
        src/Options/PutOption.hpp
        src/MathUtils/MathUtils.cpp
        src/MathUtils/MathUtils.hpp)
