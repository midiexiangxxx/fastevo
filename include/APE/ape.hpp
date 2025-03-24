#include "data_loader/loader.hpp"
#include "common.hpp"
namespace Fevo{
class APE {
public:
  APE() = default;
  ~APE() = default;
private:
  std::pair<Eigen::Matrix<double, 3, Eigen::Dynamic>, Eigen::Matrix<double, 3, Eigen::Dynamic>> alignTimeIdx(double max_diff = 0.01);
  void ApplyUmeyamaCalAPE(double max_diff = 0.01);
  
private:
  std::unordered_map<std::string, double> error_;

public:
  decltype(error_) getError() {
    ApplyUmeyamaCalAPE();
    return error_;
  }
};

inline std::pair<Eigen::Matrix<double, 3, Eigen::Dynamic>, Eigen::Matrix<double, 3, Eigen::Dynamic>> APE::alignTimeIdx(double max_diff) {
  Eigen::Map<Eigen::Matrix<double, 3, Eigen::Dynamic>> refXYZ(Gcontainer_.refXYZ_.data(), 3, Gcontainer_.ref_len_);
  Eigen::Map<Eigen::Matrix<double, 3, Eigen::Dynamic>> estXYZ(Gcontainer_.estXYZ_.data(), 3, Gcontainer_.est_len_);
  // std::cout << "ref_len_: " << refXYZ.size() << " est_len_: " << estXYZ.size() << std::endl;
  Eigen::Map<Eigen::VectorXd> refTimeStamps(Gcontainer_.refTimeStamps_.data(), Gcontainer_.ref_len_);
  Eigen::Map<Eigen::VectorXd> estTimeStamps(Gcontainer_.estTimeStamps_.data(), Gcontainer_.est_len_);

  std::vector<Eigen::Vector3d> ref_aligned, est_aligned;
  ref_aligned.reserve(Gcontainer_.est_len_);
  est_aligned.reserve(Gcontainer_.est_len_);

  for (int i = 0; i < Gcontainer_.est_len_; ++i) {
    double est_time = estTimeStamps(i);
    auto it = std::lower_bound(refTimeStamps.data(), refTimeStamps.data() + Gcontainer_.ref_len_, est_time);
    int idx = std::distance(refTimeStamps.data(), it);

    // Check the closest timestamp in the neighborhood, assume that the timestamps are sorted and est_len < ref_len 
    double min_diff = std::numeric_limits<double>::max();
    int best_idx = -1;
    for (int j = std::max(0, idx - 1); j < std::min(static_cast<int>(Gcontainer_.ref_len_), idx + 2); ++j) {
        double diff = std::abs(refTimeStamps(j) - est_time);
        if (diff < min_diff) {
            min_diff = diff;
            best_idx = j;
        }
    }

    if (best_idx != -1 && min_diff < max_diff) {
        ref_aligned.push_back(refXYZ.col(best_idx));
        est_aligned.push_back(estXYZ.col(i));
    }
  }

  Fevo_check_empty(ref_aligned);

  Eigen::Matrix<double, 3, Eigen::Dynamic> refXYZ_aligned(3, ref_aligned.size());
  Eigen::Matrix<double, 3, Eigen::Dynamic> estXYZ_aligned(3, est_aligned.size());

  for (size_t i = 0; i < ref_aligned.size(); ++i) {
      refXYZ_aligned.col(i) = ref_aligned[i];
      estXYZ_aligned.col(i) = est_aligned[i];
  }

  // std::cout << "Aligned " << ref_aligned.size() << " poses" << std::endl;
  // std::cout << "refXYZ_aligned: " << refXYZ_aligned.cols() << " estXYZ_aligned: " << estXYZ_aligned.cols() << std::endl;

  return std::make_pair(refXYZ_aligned, estXYZ_aligned);
}

inline void APE::ApplyUmeyamaCalAPE(double max_diff) {
  auto [refXYZ_aligned, estXYZ_aligned] = alignTimeIdx(max_diff); 
  Fevo_check_eq(refXYZ_aligned.size(), estXYZ_aligned.size());
  Eigen::Matrix4d transformation = Eigen::umeyama(estXYZ_aligned, refXYZ_aligned, false);
  Eigen::Matrix3d R = transformation.block<3, 3>(0, 0);
  Eigen::Vector3d t = transformation.block<3, 1>(0, 3);
  auto estXYZ_aligned_transform = R * estXYZ_aligned + t.replicate(1, estXYZ_aligned.cols());
  Eigen::Matrix<double, 1, Eigen::Dynamic> errors = (refXYZ_aligned - estXYZ_aligned_transform).colwise().norm();
  // 计算 MSE
  double mse = errors.array().square().mean();

  // 计算 RMSE
  double rmse = std::sqrt(mse);
  error_["MSE"] = mse;
  error_["RMSE"] = rmse;
}

} // namespace Fevo