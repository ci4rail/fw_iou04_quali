# The following lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)
set(EXTRA_COMPONENT_DIRS $ENV{IDF_PATH}/examples/common_components)

# get the project name from PKG_FIRMWARE_NAME in fw-package.env
file(READ "fw-package.env" FW_PACKAGE_ENV)
string(REGEX MATCH "PKG_FIRMWARE_NAME=[a-zA-Z0-9\\-]+" PNAME ${FW_PACKAGE_ENV})
string(REPLACE "PKG_FIRMWARE_NAME=" "" PNAME ${PNAME})

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(${PNAME})
