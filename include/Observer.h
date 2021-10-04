#ifndef OBSERVER_H
#define OBSERVER_H

#include <vector>

class Observer {
public:
    virtual void update() = 0;
};

class Observable {
private:
    std::vector<Observer*> m_observers;

public:
    void addObserver(Observer *observer) {
        m_observers.push_back(observer);
    }

    void notifyUpdate() {
        int size = m_observers.size();
        for (int i = 0; i < size; i++) {
            m_observers[i]->update();
        }
    }
};

#endif // OBSERVER_H