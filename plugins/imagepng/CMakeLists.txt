radiant_plugin(imagepng
        plugin.cpp plugin.h
        )

find_package(PNG REQUIRED)
target_include_directories(imagepng PRIVATE ${PNG_INCLUDE_DIR})
target_link_libraries(imagepng PRIVATE ${PNG_LIBRARIES})

install(TARGETS imagepng DESTINATION modules)
