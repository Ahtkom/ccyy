#ifndef CCYY_TEST_DERIVEDTESTOBJECT_HPP_
#define CCYY_TEST_DERIVEDTESTOBJECT_HPP_

#include <test/BaseTestObject.hpp>

#include <string>

namespace ccyy {
namespace test {

class DerivedTestObject : public BaseTestObject
{
public:
    DerivedTestObject(std::string name = "") :
        BaseTestObject(name),
        data_(999)
    {
        std::cout << "Derived constructor invoked       --" << BaseTestObject::getName() << std::endl;
    }
    ~DerivedTestObject() = default;



    DerivedTestObject &operator=(const DerivedTestObject &other)
    {
        std::cout << "derived\n";
        data_ = other.data_;
    }

    BaseTestObject &operator=(const BaseTestObject &other)
    {
        std::cout << "derived\n";
        if (const DerivedTestObject *p = dynamic_cast<const DerivedTestObject *>(&other)) {
            data_ = p->data_;
        }
    }

// private:
    int data_;
};

} // namespace test
} // namespace ccyy

#endif