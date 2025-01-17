set(LLHTTP_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libraries/3rdparty/llhttp)

set(LLHTTP_SRC
    ${LLHTTP_DIR}/src/api.c
    ${LLHTTP_DIR}/src/http.c
    ${LLHTTP_DIR}/src/llhttp.c
    ${LLHTTP_DIR}/include/llhttp.h
)

set(LLHTTP_INC
    ${LLHTTP_DIR}/include
    ${ZEPHYR_DIR}/include
)

# setup static library
add_library(llhttp STATIC ${LLHTTP_SRC})
target_compile_options(llhttp PUBLIC -mcpu=cortex-m33)
target_include_directories(llhttp PUBLIC ${LLHTTP_INC})

target_link_libraries(llhttp PRIVATE
  zephyr_interface
  zephyr_kernel
  zephyr_libc
  zephyr_minimal
  zephyr_posix
  zephyr_syscall
  zephyr_types
)


include(GNUInstallDirs)

install(TARGETS llhttp
        LIBRARY DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}
)

install(DIRECTORY ${LLHTTP_INC}/
        DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}
)
