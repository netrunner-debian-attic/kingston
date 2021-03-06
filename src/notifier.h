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

#ifndef NOTIFIER_H
#define NOTIFIER_H

#include <QObject>

#include <KComponentData>
#include <QWeakPointer>

class KNotification;
class QTimer;
class notifier_t : public QObject{
  Q_OBJECT
  public:
    notifier_t(const KComponentData& component_data, QObject* parent=0);
  public Q_SLOTS:
    void notify_new_updates(int updates, int security_updates);
    void notify_reboot();
    void reboot();
  private:
    void show_update_notification(const QString& title, const QString& message, const QString& iconname);
    KComponentData m_component_data;
    QTimer* m_reboot_nagger;
    QWeakPointer<KNotification> m_upgrade_notification;
};

#endif // NOTIFIER_H
