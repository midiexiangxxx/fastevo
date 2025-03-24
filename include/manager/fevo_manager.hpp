#pragma once
#include "data_loader/loader.hpp"
#include <iostream>
#include <memory>
#include <boost/program_options.hpp>
namespace bpo = boost::program_options;
namespace Fevo{
class FevoBase {
public:
  virtual ~FevoBase() = default;
  virtual void run(const bpo::variables_map& args) = 0;
};

template <class Derived> 
class FevoManager : public FevoBase {
public:
  FevoManager() = default;
  ~FevoManager() = default;
  void run (const bpo::variables_map& args) override final {
    LoaderCaller::call(args);
    std::cout << "Loaded " << container.ref_len_ << " reference poses and " << container.est_len_ << " estimated poses" << std::endl;
    static_cast<Derived*>(this)->Impl(args);
  }
};

class APEImpl : public FevoManager<APEImpl> {
public:
  void Impl(const bpo::variables_map& args) {
    std::cout << "APEimpl" << std::endl;
  }
};

class TrajImpl : public FevoManager<TrajImpl> {
public:
  void Impl(const bpo::variables_map& args) {
    std::cout << "TrajImpl" << std::endl;
  }
};

inline std::unordered_map<std::string, std::function<std::unique_ptr<FevoBase>()>> map = 
{
  {"ape", [] {return std::make_unique<APEImpl>();}},
  {"traj", [] {return std::make_unique<TrajImpl>();}},
};

class FevoCaller {
public:
  static void call(const bpo::variables_map& args) {
    const auto& run_mode = args["run-mode"].as<std::string>();
    if(map.find(run_mode) != map.end()) {
      map[run_mode]()->run(args);
    } else {
      std::cout << "Invalid Run Mode" << std::endl;
    }
  }
};
} // namespace Fevo