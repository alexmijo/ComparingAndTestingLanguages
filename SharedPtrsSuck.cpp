#include <iostream>
#include <memory>

namespace ptrs {
class Base1 {
  public:
    virtual int FirstNumbah() { return 0; }
};

class Derived1 : public Base1 {
    int FirstNumbah() override { return 1; }
    int SecondNumbah() { return 2; }
};

class Base2 {
  public:
    virtual Base1 *GetBase1Ptr() { return &base1; }
    int GetFirstNumbah() {
        return GetBase1Ptr()->FirstNumbah();
    }

  private:
    Base1 base1;
};

class Derived2 : public Base2 {
  public:
    Derived1 *GetBase1Ptr() override { return &derived1; }

  private:
    Derived1 derived1;
};
} // namespace ptrs

namespace sharedPtrs {
class Base1 {
  public:
    virtual int FirstNumbah() { return 0; }
};

class Derived1 : public Base1 {
    int FirstNumbah() override { return 1; }
    int SecondNumbah() { return 2; }
};

class Base2 {
  public:
    virtual std::shared_ptr<Base1> GetBase1Ptr() { return base1; }
    int GetFirstNumbah() {
        return GetBase1Ptr()->FirstNumbah();
    }

  private:
    std::shared_ptr<Base1> base1 = std::make_shared<Base1>();
};

class Derived2 : public Base2 {
  public:
    // Compile error!!!
    // std::shared_ptr<Derived1> GetBase1Ptr() override { return derived1; }
    std::shared_ptr<Base1> GetBase1Ptr() override { return derived1; }

  private:
    std::shared_ptr<Derived1> derived1 = std::make_shared<Derived1>();
};
} // namespace sharedPtrs

int main() {
    ptrs::Base2 base2p;
    ptrs::Derived2 derived2p;
    std::cout << "ptrs::base2: " << base2p.GetFirstNumbah() << std::endl;
    std::cout << "ptrs::derived2: " << derived2p.GetFirstNumbah() << std::endl;

    sharedPtrs::Base2 base2s;
    sharedPtrs::Derived2 derived2s;
    std::cout << "sharedPtrs::base2: " << base2s.GetFirstNumbah() << std::endl;
    std::cout << "sharedPtrs::derived2: " << derived2s.GetFirstNumbah() << std::endl;
}
// Don't count any more time for this for now after 4:35