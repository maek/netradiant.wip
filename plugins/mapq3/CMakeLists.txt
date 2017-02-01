radiant_plugin(mapq3
        parse.cpp parse.h
        plugin.cpp plugin.h
        write.cpp write.h
        )

install(TARGETS mapq3 DESTINATION modules)
