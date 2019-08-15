#ifndef STAN_MATH_PRIM_MAT_FUN_TRACE_GEN_INV_QUAD_FORM_LDLT_HPP
#define STAN_MATH_PRIM_MAT_FUN_TRACE_GEN_INV_QUAD_FORM_LDLT_HPP

#include <stan/math/prim/meta.hpp>
#include <stan/math/prim/mat/fun/Eigen.hpp>
#include <stan/math/prim/mat/fun/LDLT_factor.hpp>
#include <stan/math/prim/mat/err/check_multiplicable.hpp>
#include <stan/math/prim/mat/err/check_square.hpp>
#include <stan/math/prim/mat/fun/mdivide_left_ldlt.hpp>
#include <stan/math/prim/mat/fun/trace.hpp>
#include <stan/math/prim/mat/fun/transpose.hpp>
#include <stan/math/prim/mat/fun/multiply.hpp>

namespace stan {
namespace math {

/*
 * Compute the trace of an inverse quadratic form.  I.E., this computes
 *       trace(D B^T A^-1 B)
 * where D is a square matrix and the LDLT_factor of A is provided.
 */
template <typename T1, typename T2, typename T3, int R1, int C1, int R2, int C2,
          int R3, int C3, typename = enable_if_any_not_var<T1, T2, T3>>
inline return_type_t<T1, T2, T3> trace_gen_inv_quad_form_ldlt(
    const Eigen::Matrix<T1, R1, C1> &D, const LDLT_factor<T2, R2, C2> &A,
    const Eigen::Matrix<T3, R3, C3> &B) {
  check_square("trace_gen_inv_quad_form_ldlt", "D", D);
  check_multiplicable("trace_gen_inv_quad_form_ldlt", "A", A, "B", B);
  check_multiplicable("trace_gen_inv_quad_form_ldlt", "B", B, "D", D);

  return trace(multiply(multiply(D, transpose(B)), mdivide_left_ldlt(A, B)));
}

}  // namespace math
}  // namespace stan
#endif
