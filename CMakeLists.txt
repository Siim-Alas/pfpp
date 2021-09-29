cmake_minimum_required(VERSION 3.16.3)

project(pfpp)

include(FetchContent)

FetchContent_Declare(
	lapp
	GIT_REPOSITORY	https://github.com/Siim-Alas/lapp.git
	GIT_TAG		origin/main
)

FetchContent_MakeAvailable(lapp)

enable_testing()

add_executable(IncludingLAPPWorks tests/IncludingLAPPWorks.cpp)
add_test(IncludingLAPPWorks IncludingLAPPWorks)

