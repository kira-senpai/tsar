find_package(Threads REQUIRED)

add_executable(peer src/Main.cpp)

add_subdirectory(src)

target_link_libraries(peer libsecp256k1.so)
target_link_libraries(peer Threads::Threads)