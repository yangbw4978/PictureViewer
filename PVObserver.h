#ifndef PVOBSERVER_H
#define PVOBSERVER_H

#include <QVariant>
#include <QList>

class PVObserver
{
public:
    virtual void updateData(QVariant &data) = 0;
};

class PVSubject
{
public:
    void registerObserver(PVObserver* observer) { m_allObservers.append(observer); };
    void removeObserver(PVObserver* observer) { m_allObservers.removeOne(observer); };
    virtual void notifyAllObservers() = 0;
protected:
    QList<PVObserver*> m_allObservers;
};

#endif // PVOBSERVER

