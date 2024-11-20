#pragma once

#include <list>

namespace deferred {
// Oberklasse VAktion
template <class T> class Action {
protected:
  std::list<T> &m_listRef; // 指向对象列表的指针。
public:
  Action() = delete; // 是否需要一个默认构造函数？
  Action(std::list<T> &ptListe) : m_listRef(ptListe) {}
  virtual ~Action() = default;
  virtual void executeAction() = 0;
};

template <class T> class PushBack : public Action<T> {
private:
  T m_object;

public:
  PushBack() = delete;
  PushBack(std::list<T> &liste, T obj)
      : Action<T>(liste), m_object(std::move(obj)) {}
  virtual ~PushBack() = default;
  void executeAction() override {
    Action<T>::m_listRef.push_back(std::move(m_object));
  }
};

template <class T> class PushFront : public Action<T> {
private:
  T m_object;

public:
  PushFront() = delete; // 禁用默认构造函数
  PushFront(std::list<T> &liste, T obj)
      : Action<T>(liste), m_object(std::move(obj)) {}

  virtual ~PushFront() = default;

  void executeAction() override {
    Action<T>::m_listRef.push_front(std::move(m_object));
  }
};

template <class T> class Erase : public Action<T> {
public:
  using iterator = typename std::list<T>::iterator;

private:
  iterator p_it; // bei erase Iterator speichern

public:
  Erase() = delete;
  Erase(std::list<T> &liste, iterator it) : Action<T>(liste), p_it(it) {}
  virtual ~Erase() = default;
  void executeAction() override { Action<T>::m_listRef.erase(p_it); }
};
} // namespace deferred
