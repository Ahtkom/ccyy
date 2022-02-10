#ifndef CCYY_TESTOBJECT_HPP_
#define CCYY_TESTOBJECT_HPP_

#include <iostream>
#include <string>
#include <memory>

namespace ccyy {
namespace test {

class TestObject
{
public:
    TestObject(std::string name = "") :
        name_(name),
        cc_(0),
        mc_(0),
        ca_(0),
        ma_(0)
    {
        std::cout << "Constructor invoked       --" << name_ << std::endl;
    }

    TestObject(const TestObject &other) :
        name_(other.getName()),
        cc_(other.cc_ + 1),
        mc_(other.mc_),
        ca_(other.ca_),
        ma_(other.ma_)
    {
        std::cout << "Copy constructor invoked  --" << name_
                  << "_cc" << cc_ << "_mc" << mc_ << std::endl;
    }

    TestObject(TestObject &&other) :
        name_(other.getName()),
        cc_(other.cc_),
        mc_(other.mc_ + 1),
        ca_(other.ca_),
        ma_(other.ma_)
    {
        std::cout << "Move constructor invoked  --" << name_
                  << "_cc" << cc_ << "_mc" << mc_ << std::endl;
    }

    ~TestObject()
    {
        std::cout << "Destructor invoked        --" << name_;
        if (cc_ != 0 || mc_ != 0) {
            std::cout << "_cc" << cc_ << "_mc" << mc_ << std::endl;
        } else {
            std::cout << std::endl;
        }
    }

    TestObject &operator=(const TestObject &other)
    {
        setName(other.getName());
        std::cout << "Copy assignment invoked   --" << name_ << std::endl;
        return *this;
    }

    TestObject &operator=(TestObject &&other)
    {
        setName(other.getName());
        std::cout << "Move assignment invoked   --" << name_ << std::endl;
        return *this;
    }

    std::string getName() const { return name_; }
    void setName(const std::string &name) { name_ = name; }

private:
    std::string name_;

    // Times of copy/move constructor and assignment invoked, used to mark
    // and trace the objects by adding suffix.
    int cc_, mc_, ca_, ma_;
};

} // namespace test
} // namespace ccyy

#endif