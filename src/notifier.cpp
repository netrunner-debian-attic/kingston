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
#include <KPassivePopup>
#include <KIcon>
#include <QApplication>

#include <QDBusConnectionInterface>
#include <QDBusConnection>
#include <QDBusMessage>
#include <QDebug>

notifier_t::notifier_t(QObject* parent): QObject(parent) {

}

void notifier_t::notify_new_updates(int updates, int security_updates) {
  if(updates==0 && security_updates==0) {
    //do nothing, I guess
  } else {
    QPixmap px;
    if(security_updates==0) {
      show_notification( "It is recommended to update your system", QString("There is %1 updates available").arg(updates), "dialog-information");
    } else {
      if(updates==0) {
        show_notification( "You should update your system", QString("There is %1 security updates available").arg(security_updates), "dialog-warning");
      } else {
        show_notification( "You should update your system", QString("There is %1 updates and %2 security updates available").arg(updates).arg(security_updates), "dialog-warning" );
      }
    }
      
  }
}

void notifier_t::show_notification(const QString& title, const QString& message, const QString& iconname) {
  QDBusConnectionInterface* interface = QDBusConnection::sessionBus().interface();
  if(!interface) {
    KPassivePopup::message(title, message, KIcon(iconname).pixmap(QSize(32,32)) ,QApplication::activeWindow(),-1 );
    return;
  }
  QString dbus_service_name("org.freedesktop.Notifications"); 
  QString dbus_interface_name("org.freedesktop.Notifications");
  QString dbus_path("/org/freedesktop/Notifications");
  QString KDE43_SERVICE = "org.kde.VisualNotifications";
  //kde4.3 doesn't support the fdo notifications
  if(interface->isServiceRegistered(KDE43_SERVICE)) {
    dbus_service_name = KDE43_SERVICE;
    dbus_interface_name = "org.kde.VisualNotifications";
    dbus_path  = "/VisualNotifications";
  }
  if(!interface->isServiceRegistered(dbus_service_name)) {
    KPassivePopup::message(title, message, KIcon(iconname).pixmap(QSize(32,32)) ,QApplication::activeWindow(),-1 );
    return;
  }
  QDBusMessage dbusmessage = QDBusMessage::createMethodCall(dbus_service_name, dbus_path, dbus_interface_name, "Notify");
  QList<QVariant> args;
  args << "Update notification" << 0U;
  if(KDE43_SERVICE==dbus_service_name) {
    args << "foo"; //dummy for kde4.3;
  }
  args << iconname << title << message << QStringList() << QVariantMap() << 60*1000;

  dbusmessage.setArguments(args);
  QDBusMessage reply = QDBusConnection::sessionBus().call(dbusmessage);
  if(reply.type() == QDBusMessage::ReplyMessage) {
    if(!reply.arguments().isEmpty()) {
      //success
      return;
    }
  }
  //fallback
  KPassivePopup::message(title, message, KIcon(iconname).pixmap(QSize(32,32)) ,QApplication::activeWindow(),60*1000 );
}


