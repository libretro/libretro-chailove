# SDL_tty - Terminal-like output for SDL
# Copyright (C) 2015 Ingo Ruhnke <grumbel@gmail.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.11)
project(SDL_tty VERSION 0.0.0)

set(TINYCMMC_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/external/tinycmmc/modules/")
find_package(tinycmmc CONFIG)
message(STATUS "tinycmmc module path: ${TINYCMMC_MODULE_PATH}")
list(APPEND CMAKE_MODULE_PATH ${TINYCMMC_MODULE_PATH})

include(GNUInstallDirs)

find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)

add_library(SDL_tty src/SDL_fnt.c src/SDL_tty.c)
set_target_properties(SDL_tty PROPERTIES
  PUBLIC_HEADER "include/SDL_tty/SDL_fnt.h;include/SDL_tty/SDL_tty.h")
target_link_libraries(SDL_tty SDL::SDL ${SDL_IMAGE_LIBRARIES})
target_include_directories(SDL_tty
  SYSTEM PUBLIC ${SDL_IMAGE_INCLUDE_DIRS}
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/SDL_tty>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
  $<INSTALL_INTERFACE:include/SDL_tty>)

add_executable(sdltty-fontdump src/fontdump.c)
target_link_libraries(sdltty-fontdump SDL_tty)

# c64lookalike for install
add_executable(sdltty-c64lookalike src/c64lookalike.c)
target_compile_definitions(sdltty-c64lookalike PUBLIC
  SDLTTY_DATADIR=\"${CMAKE_INSTALL_FULL_DATADIR}/${PROJECT_NAME}\")
target_link_libraries(sdltty-c64lookalike SDL_tty)

file(COPY data/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/data/)

install(TARGETS sdltty-c64lookalike sdltty-fontdump
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(DIRECTORY data/
  DESTINATION ${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME})

include(ExportAndInstallLibrary)

# EOF #
