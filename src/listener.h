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

#ifndef LISTENER_H
#define LISTENER_H

#include <QObject>

class KDirWatch;
class QTimer;

class listener_t : public QObject {
  Q_OBJECT
  public:
    listener_t(QObject *parent=0);
  Q_SIGNALS:
    void please_check_for_updates();
  private Q_SLOTS:
    /**
     * function that buffers what happens on the file system and only emits the latest
     * changed, rather than 100 notifications if the same files is modified quickly
     */
    void filesystem_event_happened();
  private:
    KDirWatch* m_watcher;
    QTimer* m_buffer_timer;
};

#endif // NOTIFIER_H
