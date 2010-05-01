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

#include "listener.h"
#include <QTimer>
#include <QFileSystemWatcher>
#include <QStringList>
#include <QDebug>
#include <QFile>

listener_t::listener_t(QObject* parent): QObject(parent) {
  m_watcher = new QFileSystemWatcher(this);
  QStringList paths;
  paths << "/var/lib/update-notifier/dpkg-run-stamp" << "/var/lib/update-notifier/updates-available" << "/var/lib/apt/periodic/update-success-stamp";
  Q_FOREACH(const QString& path, paths) {
    if(QFile::exists(path)) {
      m_watcher->addPath(path);
    }
  }
  m_buffer_timer = new QTimer(this);
  m_buffer_timer->setSingleShot(true);
  m_buffer_timer->setInterval(500);
  connect(m_watcher,SIGNAL(fileChanged(QString)),this,SLOT(filesystem_event_happened()));
  connect(m_watcher,SIGNAL(directoryChanged(QString)),this,SLOT(filesystem_event_happened()));
  connect(m_buffer_timer,SIGNAL(timeout()),this,SIGNAL(please_check_for_updates()));
}

void listener_t::filesystem_event_happened() {
  qDebug() << "filesystemevent";
  m_buffer_timer->start();
}


