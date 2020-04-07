cmake_minimum_required(VERSION 3.15)
project(Clion_Code)

set(CMAKE_CXX_STANDARD 14)
#SET(CMAKE_CXX_FLAGS "-O3")
#SET(CMAKE_C_FLAGS "-O3")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
#add_subdirectory(./libcuckoo)
SET(CMAKE_CXX_FLAGS -pthread)

add_executable(Clion_Code
        Global_functions/basic_functions.cpp Global_functions/basic_functions.h

        Hash/Hash.h Hash/Hash.cpp
        Hash/MurmurHash3.h Hash/MurmurHash3.cpp

        PD/Header.cpp PD/Header.h
        PD/Body.cpp PD/Body.h
        PD/PD.cpp PD/PD.h

        Safe_PD/v_Header.cpp Safe_PD/v_Header.h
        Safe_PD/v_Body.cpp Safe_PD/v_Body.h
        Safe_PD/safe_PD.cpp Safe_PD/safe_PD.h

        Tests/validation_tests.cpp Tests/validation_tests.h
        Tests/old_benchmark_tests.cpp Tests/old_benchmark_tests.h
        Tests/benchmark_tests.cpp Tests/benchmark_tests.h

        bit_operations/bit_op.cpp bit_operations/bit_op.h
        main.cpp
        Simple_Crate/s_crate.cpp Simple_Crate/s_crate.h SID/SID.cpp SID/SID.h SID/CSD.cpp SID/CSD.h POW2C/pow2c_filter.cpp POW2C/pow2c_filter.h Hash/Permutation.cpp Hash/Permutation.h Naive_PD/naive_PD.cpp Naive_PD/naive_PD.h Naive_PD/naive_Header.cpp Naive_PD/naive_Header.h Naive_PD/naive_Body.cpp Naive_PD/naive_Body.h POW2C/pow2c_naive_filter.cpp POW2C/pow2c_naive_filter.h Global_functions/macros.h Constant_size_PD/const_Header.cpp Constant_size_PD/const_Header.h Constant_size_PD/const_Body.cpp Constant_size_PD/const_Body.h Constant_size_PD/const_PD.cpp Constant_size_PD/const_PD.h POW2C/const_filter.cpp POW2C/const_filter.h Contiguous_PD/constant_contiguous_PD/cc_PD.cpp Contiguous_PD/constant_contiguous_PD/cc_PD.h simple_filter/simple_filter.cpp simple_filter/simple_filter.h Contiguous_PD/cg_PD.cpp Contiguous_PD/cg_PD.h Naive_PD/cg_naive_PD.cpp Naive_PD/cg_naive_PD.h POW2C/gen_2Power.cpp POW2C/gen_2Power.h Hash/static_hashing.h CPD/CPD.cpp CPD/CPD.hpp CPD/Counters_Array.cpp CPD/Counters_Array.hpp CPD/Naive_Counter_Endec.cpp CPD/Naive_Counter_Endec.hpp bit_operations/my_bit_op.cpp bit_operations/my_bit_op.hpp Tests/validate_bit_op.cpp Tests/validate_bit_op.hpp Tests/validate_counters.cpp Tests/validate_counters.hpp Sparse/sparse.cpp Sparse/sparse.hpp
        Hash_Table/hash_table_var.cpp Hash_Table/hash_table_var.hpp Hash_Table/hash_table.cpp Hash_Table/hash_table.hpp Tests/validate_hash_table.cpp Tests/validate_hash_table.hpp Hash/hashutil_backup/lookup3.h Dict/dict.cpp Dict/dict.hpp Tests/validate_dict.hpp Tests/validate_filter.hpp Tests/validate_filter.cpp)


target_link_libraries(Clion_Code cuckoofilter)
