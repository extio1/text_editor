# Boost serialization is used in several targets
<<<<<<< HEAD
find_package(Boost REQUIRED COMPONENTS serialization)
=======
find_package(Boost 1.80.0 REQUIRED COMPONENTS serialization)
>>>>>>> origin/up-30

add_subdirectory(document)
add_subdirectory(utils)
add_subdirectory(compositor)
<<<<<<< HEAD
add_subdirectory(executor)
add_subdirectory(gui)
=======
add_subdirectory(executor)
>>>>>>> origin/up-30
