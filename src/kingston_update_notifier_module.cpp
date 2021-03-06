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


#include "kingston_update_notifier_module.h"
#include "update_worker.h"
#include "update_listener.h"
#include "notifier.h"
#include "reboot_listener.h"
#include <KPluginFactory>
#include <KPluginLoader>
#include <QDebug>
#include <QTimer>

K_PLUGIN_FACTORY(kingston_update_notifier_factory,
                registerPlugin<kingston_update_notifier_module_t>();
                );
K_EXPORT_PLUGIN(kingston_update_notifier_factory("kingston_update_notifier"))
kingston_update_notifier_module_t::kingston_update_notifier_module_t(QObject* parent, const QList< QVariant >& ): KDEDModule(parent),
    m_update_worker(new update_worker_t(this)), m_update_listener(new update_listener_t(this)), m_notifier(new notifier_t(kingston_update_notifier_factory::componentData(), this)),
    m_reboot_listener(new reboot_listener_t(this)){
  connect(m_update_listener,SIGNAL(please_check_for_updates()),m_update_worker,SLOT(check_for_updates()));
  connect(m_update_worker,SIGNAL(updates_available(int,int)),m_notifier,SLOT(notify_new_updates(int,int)));
  QTimer::singleShot(2 /*minutes*/ * 60 /*seconds*/ * 1000 /*msec*/,m_update_worker,SLOT(check_for_updates()) );
  connect(m_reboot_listener,SIGNAL(request_reboot()),m_notifier,SLOT(notify_reboot()));
  QTimer::singleShot(2 /*minutes*/ * 60 /*seconds*/ * 1000 /*msec*/,m_reboot_listener,SLOT(check_for_reboot()) );
}


