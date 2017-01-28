radiant_plugin(imagewebp
        plugin.cpp plugin.h
        )

find_package(WEBP REQUIRED)
target_include_directories(imagewebp PRIVATE ${WEBP_INCLUDE_DIR})
target_link_libraries(imagewebp PRIVATE ${WEBP_LIBRARIES})
