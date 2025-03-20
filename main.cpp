#include "manager/fevo_manager.hpp"

int main(int argc, char **argv) {
  bpo::options_description opts("Allowed options");
  opts.add_options()
    ("help", "produce help message")
    ("run-mode", bpo::value<std::string>(), "run mode")
    ("data-type", bpo::value<std::string>(), "date type(bag1, bag2, tum, kitti, euroc)")
    ("ref-traj", bpo::value<std::string>(), "reference trajectory path")
    ("est-traj", bpo::value<std::string>(), "estimated trajectory path");
  bpo::positional_options_description p;
  p.add("run-mode", 1);
  p.add("data-type", 1);
  p.add("ref-traj", 1);
  p.add("est-traj", 1);
  bpo::variables_map vm;
  bpo::parsed_options parsed = bpo::command_line_parser(argc, argv).options(opts).positional(p).run();
  bpo::store(parsed, vm);
  // bpo::notify(vm);
  if(vm.count("help")) {
    std::cout << opts << std::endl;
    return 0;
  }
  
  Fevo::FevoCaller::call(vm);
}