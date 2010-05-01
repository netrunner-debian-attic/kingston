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

#include "test_window.h"
#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTimer>


test_window_t::test_window_t(QWidget* parent): QWidget(parent) {
  QHBoxLayout* lay = new QHBoxLayout();
  m_updates = new QLabel(this);
  m_request = new QPushButton("Check for updates",this);
  connect(m_request,SIGNAL(clicked()),SIGNAL(check_for_updates_requested()));
  lay->addWidget(m_updates);
  lay->addWidget(m_request);
  setLayout(lay);
}

void test_window_t::show_new_updates(int updates, int security_updates) {
  m_updates->setText(QString("%1 updates and %2 security updates available").arg(updates).arg(security_updates));
}

void test_window_t::show_error_message(QString error,worker_t::error_code_t errorcode) {
  m_updates->setText(error);
  if(errorcode== worker_t::temporary_failure) {
    QTimer::singleShot(60*1000,this,SIGNAL(check_for_updates_requested()));
  }
}


