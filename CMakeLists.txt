cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(print_ip_adress VERSION ${PROJECT_VESRION})


add_executable(print_ip_adress_cli print_ip_adress.cpp)

set_target_properties(print_ip_adress_cli PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(print_ip_adress_cli
    PRIVATE "${CMAKE_BINARY_DIR}"
)

install(TARGETS print_ip_adress_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT yuri.andreev@mail.com)
set(CPACK_PACKAGE_VENDOR "Andreev@Company")
set(CPACK_PACKAGE_NAME "Print-ip")
set(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.md")
include(CPack)