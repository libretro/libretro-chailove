cmake_minimum_required(VERSION 3.0)
project(noarch
	VERSION 1.3.0
	LANGUAGES C )

add_executable(noarch
	noarch.c
	vendor/libretro-common/vfs/vfs_implementation.c
	vendor/libretro-common/file/file_path.c
	vendor/libretro-common/compat/compat_strl.c
	vendor/libretro-common/string/stdstring.c
	vendor/libretro-common/encodings/encoding_utf.c
	vendor/libretro-common/time/rtime.c
)

#target_compile_options(noarch PRIVATE -Wall -Wextra -pedantic -Werror)
target_link_libraries(noarch dl)
target_include_directories(noarch PRIVATE vendor/libretro-common/include)
target_compile_definitions(noarch PRIVATE VFS_FRONTEND)
