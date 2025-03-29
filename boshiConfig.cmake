# boshiConfig.cmake
# This file is used by `find_package(boshi)` to locate the library.

# Set the path for the header files
set(BOSHI_INCLUDE_DIRS "${CMAKE_INSTALL_PREFIX}/include/boshi")

# Set the path for the library files
set(BOSHI_LIBRARIES "${CMAKE_INSTALL_PREFIX}/lib/libboshi.a")

# Export the variables so they can be used in the parent project
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(boshi REQUIRED_VARS BOSHI_LIBRARIES BOSHI_INCLUDE_DIRS)
