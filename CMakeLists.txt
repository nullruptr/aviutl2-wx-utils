cmake_minimum_required(VERSION 3.20)
project(aviutl2_wx_utils CXX)

# 前提: 利用側の include/ に、次の3つが submodule として並んでいること。
#   include/
#   ├─ aviutl2_sdk_mirror/   "aviutl2_sdk/plugin2.h" は aviutl2_sdk_mirror/include 以下
#   ├─ wxCustomControls/     wxButtonCustom.hpp などは wxCustomControls/src 以下
#   └─ aviutl2-wx-utils/     (このリポジトリ)
# 利用側は、add_subdirectory の前に find_package(wxWidgets CONFIG REQUIRED) を済ませておくこと。
get_filename_component(AWX_DEPS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/.." ABSOLUTE)
set(AWX_SDK_INCLUDE_DIR ${AWX_DEPS_DIR}/aviutl2_sdk_mirror/include)
set(AWX_WXCC_INCLUDE_DIR ${AWX_DEPS_DIR}/wxCustomControls/src)

if(NOT EXISTS ${AWX_SDK_INCLUDE_DIR}/aviutl2_sdk/plugin2.h)
    message(FATAL_ERROR "aviutl2_sdk_mirror not found next to this repository: ${AWX_SDK_INCLUDE_DIR}")
endif()
if(NOT EXISTS ${AWX_WXCC_INCLUDE_DIR}/wxButtonCustom.hpp)
    message(FATAL_ERROR "wxCustomControls not found next to this repository: ${AWX_WXCC_INCLUDE_DIR}")
endif()
if(NOT TARGET wxWidgets::wxWidgets)
    message(FATAL_ERROR "call find_package(wxWidgets CONFIG REQUIRED) before add_subdirectory")
endif()

add_library(aviutl2_wx_utils STATIC src/dpi_patch.cpp)
add_library(aviutl2_wx_utils::aviutl2_wx_utils ALIAS aviutl2_wx_utils)

target_compile_features(aviutl2_wx_utils PUBLIC cxx_std_20)
target_compile_definitions(aviutl2_wx_utils PUBLIC UNICODE _UNICODE)
target_compile_options(aviutl2_wx_utils PRIVATE /utf-8)
target_include_directories(aviutl2_wx_utils PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${AWX_SDK_INCLUDE_DIR}
    ${AWX_WXCC_INCLUDE_DIR})
target_link_libraries(aviutl2_wx_utils PUBLIC wxWidgets::wxWidgets)

# 利用側と同じ静的ランタイムにする
set_property(TARGET aviutl2_wx_utils PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
