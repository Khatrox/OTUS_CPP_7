cmake_minimum_required(VERSION 3.12.4)

if($ENV{TRAVIS_BUILD_NUMBER})
    set(VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    set(VERSION 6.6.6)
endif()

project(OTUS_CPP_7 VERSION ${VERSION})

add_executable(bulk src/main.cpp)
add_library(BulkLibrary
            src/Bulk.h
            src/Bulk.cpp
            src/BulkParser.h
            src/BulkParser.cpp
            src/BulkListener.h
            src/BulkSubject.h
            src/otus.h
            src/OutputBulk.h
            src/OutputBulk.cpp
            src/OutputBulkInFile.h
            src/OutputBulkInFile.cpp
            src/SimpleParser.h
            src/SimpleParser.cpp
            src/BlockParser.h
            src/DynamicParser.h
            src/DynamicParser.cpp
            src/WrongScopeException.h
        )

set_target_properties(bulk BulkLibrary PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

target_include_directories(BulkLibrary PUBLIC ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(bulk PRIVATE BulkLibrary)

enable_testing()
add_subdirectory(${CMAKE_SOURCE_DIR}/test)

install(TARGETS bulk RUNTIME DESTINATION bin)
set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})

set(CPACK_PACKAGE_CONTACT masteryilerki@yandex.ru)

include(CPack)

