#include "manager/fevo_manager.hpp"

// class base{};
// class derived1 : public base {};
// class derived2 : public base {};

// void foo(base) {
//   std::cout << "base called" << std::endl;
// }

// void foo(derived1) {
//   std::cout << "derived1 called" << std::endl;
// }

// void foo(derived2) {
//   std::cout << "derived2 called" << std::endl;
// }

int main(int argc, char **argv) {
  bpo::options_description opts("Allowed options");
  opts.add_options()
    ("help", "produce help message")
    ("run-mode", bpo::value<std::string>(), "run mode")
    ("data-type", bpo::value<std::string>(), "date type(bag1, bag2, tum, kitti, euroc)");
  bpo::variables_map vm;
  bpo::store(bpo::parse_command_line(argc, argv, opts), vm);
  bpo::notify(vm);
  if(vm.count("help")) {
    std::cout << opts << std::endl;
    return 0;
  }
  FevoCaller::call(vm);
}