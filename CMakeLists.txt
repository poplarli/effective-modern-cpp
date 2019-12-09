cmake_minimum_required (VERSION 2.6)
PROJECT(ModernCpp)

INCLUDE_DIRECTORIES("/usr/local/include/boost")

SET(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/bin")

ADD_SUBDIRECTORY(TypeDeduction)
ADD_SUBDIRECTORY(auto)