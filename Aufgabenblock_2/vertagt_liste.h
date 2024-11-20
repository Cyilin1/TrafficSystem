#pragma once

#include "vertagt_aktion.h"
#include <list>

namespace deferred {
template <class T> class DeferredList {
private:
  std::list<T> m_object;
  std::list<std::unique_ptr<Action<T>>> m_actions;

public:
  // Typdefinitionen
  using iterator = typename std::list<T>::iterator;
  using const_iterator = typename std::list<T>::const_iterator;

  DeferredList() = default;
  ~DeferredList() {
    applyActionToList();
    m_object.clear();
  }

  void clear() {
    applyActionToList();
    m_object.clear();
  }

  const_iterator begin() const { return m_object.begin(); }
  const_iterator end() const { return m_object.end(); }
  iterator begin() { return m_object.begin(); }
  iterator end() { return m_object.end(); }
  bool empty() const { return m_object.empty(); }

  void push_back(T obj) {
    m_actions.push_back(
        std::make_unique<PushBack<T>>(m_object, std::move(obj)));
  }

  void push_front(T obj) {
    m_actions.push_back(
        std::make_unique<PushFront<T>>(m_object, std::move(obj)));
  }

  void erase(iterator it) {
    m_actions.push_back(std::make_unique<Erase<T>>(m_object, it));
  }

  void applyActionToList() {
    for (auto &action : m_actions) {
      action->executeAction(); // 执行每个操作
    }
    m_actions.clear(); // 清空操作列表
  }
};
} // namespace deferred
