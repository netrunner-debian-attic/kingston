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

#include "update_worker.h"
#include <QProcess>
#include <QDebug>


update_worker_t::update_worker_t(QObject* parent) : QObject(parent){
  m_runner = new QProcess(this);
  connect(m_runner,SIGNAL(finished(int)),this,SLOT(runner_done()));
}


void update_worker_t::check_for_updates() {
  if(m_runner->state()==QProcess::NotRunning) {
    const QString apt_check("/usr/lib/update-notifier/apt-check");
    m_runner->start(apt_check);
  } else {
    emit error("ALREADY RUNNING",already_running);
  }
}

void update_worker_t::runner_done() {
  if(m_runner->exitStatus()==QProcess::NormalExit && m_runner->exitCode()==0) {
    QByteArray result = m_runner->readAllStandardError();
    Q_ASSERT(result.count(';')==1);
    QList<QByteArray> parts = result.trimmed().split(';');
    Q_ASSERT(parts.size()==2);
    bool ok=true;
    int upgrades = parts.at(0).toInt(&ok);
    if(!ok) {
      emit error("PARSING OUTPUT FAILED",temporary_failure);
      return;
    }
    int security_upgrades = parts.at(1).toInt(&ok);
    if(!ok) {
      emit error("PARSING OUTPUT FAILED",temporary_failure);
      return;
    }
    emit updates_available(upgrades,security_upgrades);
  }
  else if(m_runner->exitCode()==255) {
    qDebug() << m_runner->exitStatus() << m_runner->state() << m_runner->error() << m_runner->errorString();
    emit error(QString("RUNNER FAILED"),temporary_failure);
  } else {
    qDebug() << m_runner->exitStatus() << m_runner->state() << m_runner->error() << m_runner->errorString();
    emit error(QString("RUNNER FAILED"),permanent_failure);
  }
}
