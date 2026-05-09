#pragma once

template <class T>
class IEnumerator {
public:
    virtual ~IEnumerator() = default;
    virtual bool moveNext() = 0;
    virtual T getCurrent() const = 0;
    virtual void reset() = 0;
};
