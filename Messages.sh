#!/bin/sh
$XGETTEXT `find src -name \*.cpp | grep -v testapp | grep -v test_window` -o $podir/kingston_update_notifier.pot
