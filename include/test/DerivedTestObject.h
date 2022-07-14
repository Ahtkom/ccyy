#ifndef CCYY_TEST_DERIVEDTESTOBJECT_HPP_
#define CCYY_TEST_DERIVEDTESTOBJECT_HPP_

#include <test/BaseTestObject.h>

#include <string>

namespace ccyy {
namespace test {

class DerivedTestObject : public BaseTestObject
{
public:
    DerivedTestObject(std::string name = "", int data = 999) :
        BaseTestObject(name),
        data_(data)
    {

#ifdef CCYY_DEBUG
        std::cout << "Derived constructor invoked       --" << BaseTestObject::getName() << std::endl;
#endif

    }

    ~DerivedTestObject() = default;


    DerivedTestObject &operator=(const DerivedTestObject &other)
    {

#ifdef CCYY_DEBUG
        std::cout << "derived\n";
#endif

        data_ = other.data_;

        return *this;
    }

    BaseTestObject &operator=(const BaseTestObject &other)
    {

#ifdef CCYY_DEBUG
        std::cout << "derived\n";
#endif

        if (const DerivedTestObject *p = dynamic_cast<const DerivedTestObject *>(&other)) {
            data_ = p->data_;
        }

        return *this;
    }

// private:
    int data_;
};

} // namespace test
} // namespace ccyy

#endif