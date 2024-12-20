#pragma once

#include <list>

namespace vertagt {
// Oberklasse VAktion
template<class T>
class VAktion
{
protected:
    std::list<T> &p_pListe; // 指向对象列表的指针。
public:
    VAktion() = delete; //是否需要一个默认构造函数？
    VAktion(std::list<T> &ptListe)
        : p_pListe(ptListe)
    {}
    virtual ~VAktion() = default;
    virtual void vAusfuehren() = 0;
};

// PushBack
template<class T>
class VPushBack : public VAktion<T>
{
private:
    T p_objekt;

public:
    VPushBack() = delete;
    VPushBack(std::list<T> &liste, T obj)
        : VAktion<T>(liste)
        , p_objekt(std::move(obj))
    {}
    virtual ~VPushBack() = default;
    void vAusfuehren() override { VAktion<T>::p_pListe.push_back(std::move(p_objekt)); }
};

// PushFront
template<class T>
class VPushFront : public VAktion<T>
{
private:
    T p_objekt;

public:
    VPushFront() = delete; // 禁用默认构造函数
    VPushFront(std::list<T> &liste, T obj)
        : VAktion<T>(liste)
        , p_objekt(std::move(obj))
    {}

    virtual ~VPushFront() = default;

    void vAusfuehren() override { VAktion<T>::p_pListe.push_front(std::move(p_objekt)); }
};
// Erase
template<class T>
class VErase : public VAktion<T>
{
public:
    using iterator = typename std::list<T>::iterator;

private:
    iterator p_it; // bei erase Iterator speichern

public:
    VErase() = delete;
    VErase(std::list<T> &liste, iterator it)
        : VAktion<T>(liste)
        , p_it(it)
    {}
    virtual ~VErase() = default;
    void vAusfuehren() override { VAktion<T>::p_pListe.erase(p_it); }
};
} // namespace vertagt