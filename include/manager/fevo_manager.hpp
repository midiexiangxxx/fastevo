#pragma once
#include "APE/ape.hpp"
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
    // std::cout << "Loaded " << Gcontainer_.ref_len_ << " reference poses and " << Gcontainer_.est_len_ << " estimated poses" << std::endl;
    static_cast<Derived*>(this)->Impl(args);
  }
};

class APEManager : public FevoManager<APEManager> {
public:
  void Impl(const bpo::variables_map& args) {
    // std::cout << "APEManager" << std::endl;
    APE ape;
    auto error = ape.getError();
    std::cout << error["RMSE"] << std::endl;
  }
};

class TrajManager : public FevoManager<TrajManager> {
public:
  void Impl(const bpo::variables_map& args) {
    std::cout << "TrajManager" << std::endl;
  }
};

inline std::unordered_map<std::string, std::function<std::unique_ptr<FevoBase>()>> map = 
{
  {"ape", [] {return std::make_unique<APEManager>();}},
  {"traj", [] {return std::make_unique<TrajManager>();}},
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