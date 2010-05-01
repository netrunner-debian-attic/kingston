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
#include "worker.h"
#include "listener.h"
#include "notifier.h"

int main(int argc, char **argv) {
  QApplication app(argc, argv);
  test_window_t* test_window = new test_window_t();
  worker_t* worker = new worker_t();
  QObject::connect(test_window,SIGNAL(check_for_updates_requested()),worker,SLOT(check_for_updates()));
  QObject::connect(worker,SIGNAL(updates_available(int,int)),test_window,SLOT(show_new_updates(int,int)));
  QObject::connect(worker,SIGNAL(error(QString,worker_t::error_code_t)),test_window,SLOT(show_error_message(QString,worker_t::error_code_t)));
  listener_t* listener = new listener_t();
  QObject::connect(listener,SIGNAL(please_check_for_updates()),worker,SLOT(check_for_updates()));
  notifier_t* notifier = new notifier_t();
  QObject::connect(worker,SIGNAL(updates_available(int,int)),notifier,SLOT(notify_new_updates(int,int)));
  test_window->show();
  worker->check_for_updates();
  return app.exec();
}
