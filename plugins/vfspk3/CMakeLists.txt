radiant_plugin(vfspk3
        archive.cpp archive.h
        vfs.cpp vfs.h
        vfspk3.cpp vfspk3.h
        )

find_package(GLIB REQUIRED)
target_include_directories(vfspk3 PRIVATE ${GLIB_INCLUDE_DIRS})
target_link_libraries(vfspk3 PRIVATE ${GLIB_LIBRARIES})

target_include_directories(vfspk3 PRIVATE filematch)
target_link_libraries(vfspk3 PRIVATE filematch)

install(TARGETS vfspk3 DESTINATION modules)
