/////////////////////////////////////////////////////////////////////////////
// tombstones.h, expected interface for CS254 assignment 5
/////////////////////////////////////////////////////////////////////////////

#if !defined(__TOMBSTONES_H__)
#define __TOMBSTONES_H__
#include <cstdlib>
template <class T> class Pointer;
template <class T> void free(Pointer<T>& obj);

template <class T>
class Pointer {
public:
    Pointer<T>();                               // default constructor
    Pointer<T>(Pointer<T>& p) {
        ts = p.ts;
        ts->cnt++;
    }
    Pointer<T>(T* p) {
        ts = new Tombstone();
        ts->cnt = 1;
        ts->pointee = p;
    }
    ~Pointer<T>() {
        if (ts->pointee != NULL) {
            delete ts->pointee;
            ts->pointee = NULL;
        }
        delete ts;
    }
    T& operator*() const {
        return *(ts->pointee);
    }
    T* operator->() const {
        if (ts->cnt == 0)
            return NULL;
        return ts->pointee;
    }
    Pointer<T>& operator=(const Pointer<T>& p) {
        ts = p.ts;
        ts->cnt++;
    }

    // equality comparisons:
    bool operator==(const Pointer<T>& p) const {
        return p.ts == ts;
    }
    bool operator!=(const Pointer<T>& p) const {
        return p.ts == ts;
    }
    bool operator==(const int n) const {
        return ts == NULL && n == 0;
        // true iff Pointer is null and int is zero
    }
    bool operator!=(const int n) const {
        return !(ts == NULL && n == 0);
        // false iff Pointer is null and int is zero
    }
    class Tombstone {
    public:
        int cnt;
        T* pointee;
    };
    Tombstone* ts;
};
template <class T>
    void free(Pointer<T>& p) {
        if (p.ts->pointee == 0 || p.ts->pointee == NULL)
            return;
        (p.ts->cnt)--;
        if (p.ts->cnt == 0) {
            delete p.ts->pointee;
            p.ts->pointee = NULL;
        }
    }

#endif // __TOMBSTONES_H__
