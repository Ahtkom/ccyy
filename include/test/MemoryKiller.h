#ifndef CCYY_TEST_MEMORYKILLER_H_
#define CCYY_TEST_MEMORYKILLER_H_

namespace ccyy {
namespace test {

class MemoryKiller
{
public:
    ~MemoryKiller() = default;

    static void killMemory(int n_GB = 1) {
        MemoryKiller mk(n_GB);
        std::size_t n = static_cast<std::size_t>(mk.getNGB() * 1024 * 1024 * 1024 / 4);
        for (std::size_t i = 0; i != n; ++i) {
            int *p = new int(0);
        }
    }

    int getNGB() const { return n_GB_; }

protected:
    MemoryKiller(int n_GB = 1) : n_GB_(n_GB) {}

private:
    int n_GB_;
};

    
} // namespace test
} // namespace ccyy

#endif