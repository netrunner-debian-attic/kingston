set(kingston_SRCS reboot_listener.cpp
   update_listener.cpp
   notifier.cpp
   update_worker.cpp
 )

kde4_add_executable(testapp_kingston testapp_main.cpp test_window.cpp ${kingston_SRCS})

target_link_libraries(testapp_kingston ${KDE4_KDEUI_LIBS} ${KDE4_KIO_LIBS} )

kde4_add_plugin(kded_kingston_update_notifier kingston_update_notifier_module.cpp ${kingston_SRCS})
# for our builds this should be always true
if(CMAKE_COMPILER_IS_GNUCXX)
        set(MINIMAL_LINKING "-Wl,--no-undefined -Wl,--as-needed")
else(CMAKE_COMPILER_IS_GNUCXX)
        set(MINIMAL_LINKING)
endif(CMAKE_COMPILER_IS_GNUCXX)
target_link_libraries(kded_kingston_update_notifier ${KDE4_KDEUI_LIBS} ${KDE4_KIO_LIBS} )
set_target_properties(kded_kingston_update_notifier PROPERTIES
        LINK_FLAGS "${MINIMAL_LINKING}"
        )

########### install files ###############

install( FILES kingston_update_notifier.desktop  DESTINATION ${SERVICES_INSTALL_DIR}/kded )
install( TARGETS kded_kingston_update_notifier DESTINATION  ${PLUGIN_INSTALL_DIR})
install( FILES kingston_update_notifier.notifyrc  DESTINATION  ${DATA_INSTALL_DIR}/kingston_update_notifier )
