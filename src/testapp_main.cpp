/*
    Copyright (c) 2010 Sune Vuorela <sune@vuorela.dk>

    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without
    restriction, including without limitation the rights to use,
    copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following
    conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
    OTHER DEALINGS IN THE SOFTWARE.

*/

#include <QApplication>
#include "test_window.h"
#include "update_worker.h"
#include "update_listener.h"
#include "notifier.h"
#include "reboot_listener.h"

int main(int argc, char **argv) {
  QApplication app(argc, argv);
  test_window_t* test_window = new test_window_t();
  update_worker_t* update_worker = new update_worker_t();
  QObject::connect(test_window,SIGNAL(check_for_updates_requested()),update_worker,SLOT(check_for_updates()));
  QObject::connect(update_worker,SIGNAL(updates_available(int,int)),test_window,SLOT(show_new_updates(int,int)));
  QObject::connect(update_worker,SIGNAL(error(QString,update_worker_t::error_code_t)),test_window,SLOT(show_error_message(QString,update_worker_t::error_code_t)));
  update_listener_t* update_listener = new update_listener_t();
  QObject::connect(update_listener,SIGNAL(please_check_for_updates()),update_worker,SLOT(check_for_updates()));
  notifier_t* notifier = new notifier_t();
  QObject::connect(update_worker,SIGNAL(updates_available(int,int)),notifier,SLOT(notify_new_updates(int,int)));
  test_window->show();
  update_worker->check_for_updates();
  reboot_listener_t* reboot_listener = new reboot_listener_t();
  QObject::connect(reboot_listener,SIGNAL(request_reboot()),notifier,SLOT(notify_reboot()));
  reboot_listener->check_for_reboot();
  return app.exec();
}
