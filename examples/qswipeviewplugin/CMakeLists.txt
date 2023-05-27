
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

add_library(qswipeviewplugin
    qswipeviewplugin.cpp
    qpageindicatorplugin.cpp
)

target_link_libraries(qswipeviewplugin  PRIVATE Qt${QT_VERSION_MAJOR}::Widgets qswipeview)    

# TODO PRO resources ==> cmake resources ??? 
# resources.files = \
#     images/icons8-swipe-64.png \
#     images/icons8-dots-loading-64.png
# resources.prefix = /

# RESOURCES = resources
