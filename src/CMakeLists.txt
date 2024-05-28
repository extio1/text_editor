# Boost serialization is used in several targets
find_package(Boost REQUIRED COMPONENTS serialization)

add_subdirectory(document)
add_subdirectory(utils)
add_subdirectory(compositor)
add_subdirectory(executor)
add_subdirectory(gui)
