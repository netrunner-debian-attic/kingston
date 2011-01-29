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
#include <KLocale>
#include <QApplication>
#include <QtDBus>
#include <kworkspace/kworkspace.h>

#include <QTimer>
#include <KNotification>

#include <QDebug>


notifier_t::notifier_t(const KComponentData& component_data, QObject* parent): QObject(parent),
  m_component_data(component_data),
  m_reboot_nagger (new QTimer(this)) {
  m_reboot_nagger->setSingleShot(true);
  m_reboot_nagger->setInterval(60/*minutes*/ * 60/*seconds*/ * 1000/*msec*/);
  connect(m_reboot_nagger,SIGNAL(timeout()),SLOT(notify_reboot()));

}

void notifier_t::notify_new_updates(int updates, int security_updates) {
  if(updates==0 && security_updates==0) {
    if(m_upgrade_notification) {
      m_upgrade_notification.data()->close();
    }
  } else {
    QPixmap px;
    if(security_updates==0) {
      show_update_notification(i18n("It is recommended to update your system"), i18np("There is %1 update available", "There are %1 updates available", updates), "dialog-information");
    } else {
      if(updates==0) {
        show_update_notification(i18n("You should update your system"), i18np("There is %1 security update available", "There are %1 security updates available", security_updates==0), "dialog-warning");
      } else {
        const QString updates_text = i18n("%1 update", "%1 updates", updates);
        const QString security_updates_text = i18n("%1 security update", "%1 security updates", security_updates);
        show_update_notification(i18n("You should update your system"), i18nc("%1 is e.g. '3 updates'; %2 is e.g. '1 security update'", "There are: %1, and %2", updates_text, security_updates_text), "dialog-warning");
      }
    }
      
  }
}

void notifier_t::show_update_notification(const QString& title, const QString& message, const QString& iconname) {
  if(m_upgrade_notification) {
    m_upgrade_notification.data()->close();
  }
  KNotification* note = new KNotification("updatesavailable",0L, KNotification::Persistent);
  note->setTitle(title);
  note->setText(message);
  note->setPixmap(KIcon(iconname).pixmap(QSize(32,32)));
  note->setComponentData(m_component_data);
  note->setActions(QStringList() << i18nc("Do the proposed action (upgrade, reboot, etc) later", "Later")
    << i18nc("Reboot the system", "Reboot"));
  note->sendEvent();
  m_upgrade_notification=note;
  return;
}

void notifier_t::notify_reboot() {
  KNotification* note = new KNotification("requestreboot",0L, KNotification::Persistent);
  note->setTitle(i18n("Please reboot your system"));
  note->setText(i18n("In order to complete this upgrade, you need to reboot your system"));
  note->setPixmap(KIcon("system-reboot").pixmap(QSize(32,32)));
  note->setComponentData(m_component_data);
  note->setActions(QStringList() << i18nc("Do the proposed action (upgrade, reboot, etc) later", "Later"));
  connect(note,SIGNAL(closed()),m_reboot_nagger,SLOT(start()));
  connect(note,SIGNAL(action1Activated()),m_reboot_nagger,SLOT(start()));
  connect(note,SIGNAL(action2Activated()),SLOT(reboot()));
  note->sendEvent();
}

void notifier_t::reboot() {
  QDBusInterface interface("org.kde.ksmserver", "/KSMServer", "org.kde.KSMServerInterface");
  interface.call("logout", KWorkSpace::ShutdownConfirmYes, KWorkSpace::ShutdownTypeReboot, KWorkSpace::ShutdownModeInteractive);
}

#include <notifier.moc>
