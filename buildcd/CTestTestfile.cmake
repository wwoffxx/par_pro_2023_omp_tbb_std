# CMake generated Testfile for 
# Source directory: /mnt/c/Users/Lenovo/par_pro_2023_omp_tbb_std
# Build directory: /mnt/c/Users/Lenovo/par_pro_2023_omp_tbb_std/buildcd
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(lint.modules "/usr/bin/gmake" "lint.modules")
set_tests_properties(lint.modules PROPERTIES  _BACKTRACE_TRIPLES "/mnt/c/Users/Lenovo/par_pro_2023_omp_tbb_std/cmake/cpplint.cmake;127;add_test;/mnt/c/Users/Lenovo/par_pro_2023_omp_tbb_std/CMakeLists.txt;52;cpplint_add_subdirectory;/mnt/c/Users/Lenovo/par_pro_2023_omp_tbb_std/CMakeLists.txt;0;")
subdirs("modules")
