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

#ifndef KINGSTON_UPDATE_NOTIFIER_MODULE_H
#define KINGSTON_UPDATE_NOTIFIER_MODULE_H

#include <KDEDModule>
#include <QObject>

class listener_t;
class notifier_t;
class worker_t;
class reboot_listener_t;
class kingston_update_notifier_module_t : public KDEDModule {
  public:
    kingston_update_notifier_module_t(QObject* parent,  const QList<QVariant>&);
  private:
    worker_t* m_worker;
    listener_t* m_listener;
    notifier_t* m_notifier;
    reboot_listener_t* m_reboot_listener;
    
};

#endif // KINGSTON_UPDATE_NOTIFIER_MODULE_H
