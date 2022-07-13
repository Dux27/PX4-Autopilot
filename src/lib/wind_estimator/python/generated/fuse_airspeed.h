// -----------------------------------------------------------------------------
// This file was autogenerated by symforce from template:
//     backends/cpp/templates/function/FUNCTION.h.jinja
// Do NOT modify by hand.
// -----------------------------------------------------------------------------

#pragma once

#include <matrix/math.hpp>

namespace sym {

/**
 * This function was autogenerated from a symbolic function. Do not modify by hand.
 *
 * Symbolic function: fuse_airspeed
 *
 * Args:
 *     v_local: Matrix31
 *     state: Matrix31
 *     P: Matrix33
 *     airspeed: Scalar
 *     R: Scalar
 *     epsilon: Scalar
 *
 * Outputs:
 *     H: Matrix13
 *     K: Matrix31
 *     innov_var: Scalar
 *     innov: Scalar
 */
template <typename Scalar>
void FuseAirspeed(const matrix::Matrix<Scalar, 3, 1>& v_local,
                  const matrix::Matrix<Scalar, 3, 1>& state, const matrix::Matrix<Scalar, 3, 3>& P,
                  const Scalar airspeed, const Scalar R, const Scalar epsilon,
                  matrix::Matrix<Scalar, 1, 3>* const H = nullptr,
                  matrix::Matrix<Scalar, 3, 1>* const K = nullptr, Scalar* const innov_var = nullptr,
                  Scalar* const innov = nullptr) {
  // Total ops: 56

  // Input arrays

  // Intermediate terms (11)
  const Scalar _tmp0 = -state(0, 0) + v_local(0, 0);
  const Scalar _tmp1 = -state(1, 0) + v_local(1, 0);
  const Scalar _tmp2 = std::sqrt(Scalar(std::pow(_tmp0, Scalar(2)) + std::pow(_tmp1, Scalar(2)) +
                                        epsilon + std::pow(v_local(2, 0), Scalar(2))));
  const Scalar _tmp3 = state(2, 0) / _tmp2;
  const Scalar _tmp4 = _tmp0 * _tmp3;
  const Scalar _tmp5 = _tmp1 * _tmp3;
  const Scalar _tmp6 = -P(0, 0) * _tmp4;
  const Scalar _tmp7 = -P(1, 1) * _tmp5;
  const Scalar _tmp8 = P(2, 2) * _tmp2;
  const Scalar _tmp9 = R + _tmp2 * (-P(0, 2) * _tmp4 - P(1, 2) * _tmp5 + _tmp8) -
                       _tmp4 * (-P(1, 0) * _tmp5 + P(2, 0) * _tmp2 + _tmp6) -
                       _tmp5 * (-P(0, 1) * _tmp4 + P(2, 1) * _tmp2 + _tmp7);
  const Scalar _tmp10 = Scalar(1.0) / (math::max<Scalar>(_tmp9, epsilon));

  // Output terms (4)
  if (H != nullptr) {
    matrix::Matrix<Scalar, 1, 3>& _H = (*H);

    _H(0, 0) = -_tmp4;
    _H(0, 1) = -_tmp5;
    _H(0, 2) = _tmp2;
  }

  if (K != nullptr) {
    matrix::Matrix<Scalar, 3, 1>& _K = (*K);

    _K(0, 0) = _tmp10 * (-P(0, 1) * _tmp5 + P(0, 2) * _tmp2 + _tmp6);
    _K(1, 0) = _tmp10 * (-P(1, 0) * _tmp4 + P(1, 2) * _tmp2 + _tmp7);
    _K(2, 0) = _tmp10 * (-P(2, 0) * _tmp4 - P(2, 1) * _tmp5 + _tmp8);
  }

  if (innov_var != nullptr) {
    Scalar& _innov_var = (*innov_var);

    _innov_var = _tmp9;
  }

  if (innov != nullptr) {
    Scalar& _innov = (*innov);

    _innov = -_tmp2 * state(2, 0) + airspeed;
  }
}  // NOLINT(readability/fn_size)

// NOLINTNEXTLINE(readability/fn_size)
}  // namespace sym