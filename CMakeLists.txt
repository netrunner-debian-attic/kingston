project(kingston)

find_package(KDE4 REQUIRED)
include (KDE4Defaults)

include_directories( ${KDE4_INCLUDES} ${QT_INCLUDES} )

find_package(Gettext REQUIRED)

add_subdirectory( src )
add_subdirectory(po)
