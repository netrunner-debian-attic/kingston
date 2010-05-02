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

#ifndef UPDATE_WORKER_H
#define UPDATE_WORKER_H


#include <QObject>

class QProcess;

class update_worker_t : public QObject {
  Q_OBJECT
  public:
    update_worker_t(QObject* parent=0);
    enum error_code_t {
      temporary_failure,
      permanent_failure,
      already_running
    };
  public Q_SLOTS:
    void check_for_updates();
  Q_SIGNALS:
    void updates_available(int updates,int security_updates);
    void error(QString message, update_worker_t::error_code_t);
  private Q_SLOTS:
    void runner_done();
  private:
    QProcess* m_runner;
    
};

#endif // UPDATE_WORKER_H
