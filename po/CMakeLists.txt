file(GLOB pofiles "${CMAKE_CURRENT_SOURCE_DIR}/*.po")
GETTEXT_CREATE_TRANSLATIONS(kingston_update_notifier.pot ALL ${pofiles})
