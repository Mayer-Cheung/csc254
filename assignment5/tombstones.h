/////////////////////////////////////////////////////////////////////////////
// tombstones.h, expected interface for CS254 assignment 5
/////////////////////////////////////////////////////////////////////////////

#if !defined(__TOMBSTONES_H__)
#define __TOMBSTONES_H__
#include <cstdlib>
template <class T> class Pointer;
template <class T> void free(Pointer<T>& obj);

template <typename T>
class Tombstone {
public:
    int cnt;
    T* pointee;
};

template <class T>
class Pointer {
public:
    Pointer<T>();                               // default constructor
    Pointer<T>(Pointer<T>& p) {
        ts = p.ts;
        ts->cnt++;
    }
    Pointer<T>(T* p) {
        ts = new Tombstone<T>();
        ts->cnt = 1;
        ts->pointee = p;
    }
    ~Pointer<T>() {
        ts->cnt--;
        if (ts->cnt == 0) {
            delete ts->pointee;
            delete ts;            
        }
    }
    T& operator*() const {
        return *(ts->pointee);
    }
    T* operator->() const {
        return ts->pointee;
    }
    Pointer<T>& operator=(const Pointer<T>& p) {
        if (this != &p) {
            if (ts->cnt == 0) {
                delete ts->pointee;
                delete ts;
            }
            ts = p.ts;
            ts->cnt++;
        }
        return *this;
    }

    // equality comparisons:
    bool operator==(const Pointer<T>& p) const {
        return p.ts == ts;
    }
    bool operator!=(const Pointer<T>& p) const {
        return p.ts != ts;
    }
    bool operator==(const int n) const {
        //  return ts == NULL && n == 0;
        // true iff Pointer is null and int is zero
        if (ts == NULL)
            return n == 0;
        else
            return *(ts->pointee) == n;
    }
    bool operator!=(const int n) const {
        //  return !(ts == NULL && n == 0);
        // false iff Pointer is null and int is zero
        if (ts == NULL)
            return n != 0;
        else
            return *(ts->pointee) != n;
    }
    Tombstone<T>* ts;
};
template <class T>
    void free(Pointer<T>& p) {
        p.ts->cnt--;
        if (p.ts->cnt == 0) {
            delete p.ts->pointee;
            delete p.ts;            
        }
    }

#endif // __TOMBSTONES_H__
