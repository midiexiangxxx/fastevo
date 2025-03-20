#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include <Eigen/Eigen>
#include <boost/program_options.hpp>
namespace bpo = boost::program_options;

namespace Fevo{
struct PoseStemp {
  double timestamp;
  Eigen::Vector3d position;
  Eigen::Quaterniond orientation;
};

struct Container {
  std::vector<double> refTimeStamps_;
  std::vector<double> estTimeStamps_;
  std::vector<double> refXYZ_;
  std::vector<double> estXYZ_;
  size_t ref_len_;
  size_t est_len_;
} container;

class LoaderBase {
public:
  virtual ~LoaderBase() = default;
  virtual void run(const bpo::variables_map& args) = 0;
};

template <class Derived>
class DataLoader : public LoaderBase {
public: 
  DataLoader() = default;
  ~DataLoader() = default;
  void run(const bpo::variables_map& args) override final {
    static_cast<Derived*>(this)->Impl(args);
  }
  void clear() {
    container.refTimeStamps_.clear();
    container.estTimeStamps_.clear();
    container.refXYZ_.clear();
    container.estXYZ_.clear();
  }

};

class TUMLoader : public DataLoader<TUMLoader> {
public:
  void Impl(const bpo::variables_map& args) {
    clear();
    auto && ref_traj = args["ref-traj"].as<std::string>();
    auto && est_traj = args["est-traj"].as<std::string>();
    if(!std::filesystem::exists(ref_traj)) {
      std::cout << "reference trajectory file does not exist\n\"" << ref_traj << "\"\n, aborting" << std::endl;
    }
    if(!std::filesystem::exists(est_traj)) {
      std::cout << "estimated trajectory file does not exist\n\"" << est_traj << "\"\n, aborting" << std::endl;
    }
    loadTrajectory(ref_traj, container.refTimeStamps_, container.refXYZ_);
    loadTrajectory(est_traj, container.estTimeStamps_, container.estXYZ_);
    container.ref_len_ = container.refTimeStamps_.size();
    container.est_len_ = container.estTimeStamps_.size();
  }
private:
  void loadTrajectory(const std::string& file_path, std::vector<double>& timestamps, std::vector<double>& xyz) {
    std::ifstream traj_file_stream{file_path};
    std::string line;
    while (std::getline(traj_file_stream, line)) {
      std::istringstream iss(line);
      PoseStemp data;
      iss >> data.timestamp >>
              data.position.x() >> data.position.y() >> data.position.z() >> 
              data.orientation.x() >> data.orientation.y() >> data.orientation.z() >> data.orientation.w();
      timestamps.emplace_back(data.timestamp);
      xyz.emplace_back(data.position.x());
      xyz.emplace_back(data.position.y());
      xyz.emplace_back(data.position.z());
    }
    traj_file_stream.close();
  }
};

inline std::unordered_map<std::string, std::function<std::unique_ptr<LoaderBase>()>> loader_map = 
{
  {"tum", [] {return std::make_unique<TUMLoader>();}},
};

class LoaderCaller {
public:
  static void call(const bpo::variables_map& args) {
    const auto& run_mode = args["data-type"].as<std::string>();
    if(loader_map.find(run_mode) != loader_map.end()) {
      loader_map[run_mode]()->run(args);
    } else {
      std::cout << "Invalid Data Type" << std::endl;
    }
  }
};

} // namespace Fevo