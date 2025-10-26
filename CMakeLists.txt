cmake_minimum_required(VERSION 3.10)
project(dinamica)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/HEADER_FILES)

file(GLOB SRC_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")

add_executable(dinamica ${SRC_FILES})

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system)
    target_link_libraries(dinamica PRIVATE sfml-graphics sfml-window sfml-system)
else()
    target_link_libraries(dinamica PRIVATE -lm -lpthread -lsfml-graphics -lsfml-window -lsfml-system)
endif()

add_custom_target(clean_all
    COMMAND ${CMAKE_COMMAND} -E echo "Limpando conteúdo da pasta de build..."
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/CMakeFiles
    COMMAND ${CMAKE_COMMAND} -E remove -f ${CMAKE_BINARY_DIR}/CMakeCache.txt
    COMMAND ${CMAKE_COMMAND} -E remove -f ${CMAKE_BINARY_DIR}/Makefile
    COMMAND ${CMAKE_COMMAND} -E remove -f ${CMAKE_BINARY_DIR}/cmake_install.cmake
    COMMAND ${CMAKE_COMMAND} -E echo "Build limpo, pasta preservada."
    COMMENT "Removendo arquivos gerados pelo CMake, mas mantendo a pasta build..."
)