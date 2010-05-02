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

#include "notifier.h"
#include <KIcon>
#include <QApplication>

#include <KNotification>

#include <QDebug>

notifier_t::notifier_t(QObject* parent): QObject(parent) {
  m_component_data= new KComponentData("kingston_update_notifier");

}

void notifier_t::notify_new_updates(int updates, int security_updates) {
  if(updates==0 && security_updates==0) {
    //do nothing, I guess
  } else {
    QPixmap px;
    if(security_updates==0) {
      show_update_notification( "It is recommended to update your system", QString("There is %1 updates available").arg(updates), "dialog-information");
    } else {
      if(updates==0) {
        show_update_notification( "You should update your system", QString("There is %1 security updates available").arg(security_updates), "dialog-warning");
      } else {
        show_update_notification( "You should update your system", QString("There is %1 updates and %2 security updates available").arg(updates).arg(security_updates), "dialog-warning" );
      }
    }
      
  }
}

void notifier_t::show_update_notification(const QString& title, const QString& message, const QString& iconname) {
  KNotification* note = new KNotification("updatesavailable",0L, KNotification::Persistent);
  note->setTitle(title);
  note->setText(message);
  note->setPixmap(KIcon(iconname).pixmap(QSize(32,32)));
  note->setComponentData(*m_component_data);
  note->setActions(QStringList() << "Later");
  connect(note,SIGNAL(activated()),note,SLOT(close()));
  note->sendEvent();
  return;
}


