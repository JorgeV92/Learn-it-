# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/jorgevelez/Desktop/Learn-it-/Complete/CPP-Complete/BST/build/_deps/cli11_proj-src"
  "/Users/jorgevelez/Desktop/Learn-it-/Complete/CPP-Complete/BST/build/_deps/cli11_proj-build"
  "/Users/jorgevelez/Desktop/Learn-it-/Complete/CPP-Complete/BST/build/_deps/cli11_proj-subbuild/cli11_proj-populate-prefix"
  "/Users/jorgevelez/Desktop/Learn-it-/Complete/CPP-Complete/BST/build/_deps/cli11_proj-subbuild/cli11_proj-populate-prefix/tmp"
  "/Users/jorgevelez/Desktop/Learn-it-/Complete/CPP-Complete/BST/build/_deps/cli11_proj-subbuild/cli11_proj-populate-prefix/src/cli11_proj-populate-stamp"
  "/Users/jorgevelez/Desktop/Learn-it-/Complete/CPP-Complete/BST/build/_deps/cli11_proj-subbuild/cli11_proj-populate-prefix/src"
  "/Users/jorgevelez/Desktop/Learn-it-/Complete/CPP-Complete/BST/build/_deps/cli11_proj-subbuild/cli11_proj-populate-prefix/src/cli11_proj-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/jorgevelez/Desktop/Learn-it-/Complete/CPP-Complete/BST/build/_deps/cli11_proj-subbuild/cli11_proj-populate-prefix/src/cli11_proj-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/jorgevelez/Desktop/Learn-it-/Complete/CPP-Complete/BST/build/_deps/cli11_proj-subbuild/cli11_proj-populate-prefix/src/cli11_proj-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
