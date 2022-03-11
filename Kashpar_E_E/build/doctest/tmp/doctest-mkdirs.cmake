# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/home/Desktop/OOP_PROJECT/Kashpar_E_E/build/doctest/src/doctest"
  "C:/Users/home/Desktop/OOP_PROJECT/Kashpar_E_E/build/doctest/src/doctest-build"
  "C:/Users/home/Desktop/OOP_PROJECT/Kashpar_E_E/build/doctest"
  "C:/Users/home/Desktop/OOP_PROJECT/Kashpar_E_E/build/doctest/tmp"
  "C:/Users/home/Desktop/OOP_PROJECT/Kashpar_E_E/build/doctest/src/doctest-stamp"
  "C:/Users/home/Desktop/OOP_PROJECT/Kashpar_E_E/build/doctest/src"
  "C:/Users/home/Desktop/OOP_PROJECT/Kashpar_E_E/build/doctest/src/doctest-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/home/Desktop/OOP_PROJECT/Kashpar_E_E/build/doctest/src/doctest-stamp/${subDir}")
endforeach()
