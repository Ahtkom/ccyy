#ifndef CCYY_TEST_BASETESTOBJECT_HPP_
#define CCYY_TEST_BASETESTOBJECT_HPP_

#include <iostream>
#include <string>
#include <memory>

namespace ccyy {
namespace test {

class BaseTestObject
{
public:
    BaseTestObject(std::string name = "") :
        name_(name),
        cc_(0),
        mc_(0),
        ca_(0),
        ma_(0)
    {
        std::cout << "Base constructor invoked       --" << name_ << std::endl;
    }

    BaseTestObject(const BaseTestObject &other) :
        name_(other.getName()),
        cc_(other.cc_ + 1),
        mc_(other.mc_),
        ca_(other.ca_),
        ma_(other.ma_)
    {
        std::cout << "Base copy constructor invoked  --" << name_
                  << "_cc" << cc_ << "_mc" << mc_ << std::endl;
    }

    BaseTestObject(BaseTestObject &&other) :
        name_(other.getName()),
        cc_(other.cc_),
        mc_(other.mc_ + 1),
        ca_(other.ca_),
        ma_(other.ma_)
    {
        std::cout << "Base move constructor invoked  --" << name_
                  << "_cc" << cc_ << "_mc" << mc_ << std::endl;
    }

    virtual ~BaseTestObject()
    {
        std::cout << "Base destructor invoked        --" << name_;
        if (cc_ != 0 || mc_ != 0) {
            std::cout << "_cc" << cc_ << "_mc" << mc_ << std::endl;
        } else {
            std::cout << std::endl;
        }
    }

    BaseTestObject &operator=(const BaseTestObject &other)
    {
        setName(other.getName());
        std::cout << "Base copy assignment invoked   --" << name_ << std::endl;
        return *this;
    }

    BaseTestObject &operator=(BaseTestObject &&other)
    {
        setName(other.getName());
        std::cout << "Base move assignment invoked   --" << name_ << std::endl;
        return *this;
    }

    std::string getName() const { return name_; }
    void setName(const std::string &name) { name_ = name; }
    void print() const { std::cout << getName() << std::endl; }

private:
    std::string name_;

    // Times of copy/move constructor and assignment invoked, used to mark
    // and trace the objects by adding suffix.
    int cc_, mc_, ca_, ma_;
};

} // namespace test
} // namespace ccyy

#endif