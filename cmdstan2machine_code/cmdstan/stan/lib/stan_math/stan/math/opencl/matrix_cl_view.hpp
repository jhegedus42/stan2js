#ifndef STAN_MATH_OPENCL_TRIANGULAR_HPP
#define STAN_MATH_OPENCL_TRIANGULAR_HPP
#ifdef STAN_OPENCL

#include <stan/math/opencl/stringify.hpp>
#include <Eigen/Core>
#include <type_traits>

namespace stan {
namespace math {
enum class matrix_cl_view { Diagonal = 0, Lower = 1, Upper = 2, Entire = 3 };

/**
 * Determines which parts are nonzero in any of the input views.
 * @param left_view first view
 * @param right_view second view
 * @return combined view
 */
inline const matrix_cl_view either(const matrix_cl_view left_view,
                                   const matrix_cl_view right_view) {
  typedef typename std::underlying_type<matrix_cl_view>::type underlying;
  return static_cast<matrix_cl_view>(static_cast<underlying>(left_view)
                                     | static_cast<underlying>(right_view));
}

/**
 * Determines which parts are nonzero in both input views.
 * @param left_view first view
 * @param right_view second view
 * @return common nonzero part
 */
inline const matrix_cl_view both(const matrix_cl_view left_view,
                                 const matrix_cl_view right_view) {
  typedef typename std::underlying_type<matrix_cl_view>::type underlying;
  return static_cast<matrix_cl_view>(static_cast<underlying>(left_view)
                                     & static_cast<underlying>(right_view));
}

/**
 * Check whether a view contains certain nonzero part
 * @param view view to check
 * @param part part to check for (usually `Lower` or `Upper`)
 * @return true, if `view` has `part` nonzero
 */
inline bool contains_nonzero(const matrix_cl_view view,
                             const matrix_cl_view part) {
  return static_cast<bool>(both(view, part));
}

/**
 * Transposes a view - swaps lower and upper parts.
 * @param view view to transpose
 * @return transposition of input
 */
inline const matrix_cl_view transpose(const matrix_cl_view view) {
  if (view == matrix_cl_view::Lower) {
    return matrix_cl_view::Upper;
  }
  if (view == matrix_cl_view::Upper) {
    return matrix_cl_view::Lower;
  }
  return view;
}

/**
 * Inverts a view. Parts that are zero in the input become nonzero in
 * output and vice versa.
 * @param view view to invert
 * @return inverted view
 */
inline const matrix_cl_view invert(const matrix_cl_view view) {
  typedef typename std::underlying_type<matrix_cl_view>::type underlying;
  return static_cast<matrix_cl_view>(~static_cast<underlying>(view));
}

/**
 * Creates a view from `Eigen::UpLoType`. `Eigen::Lower`,
 * `Eigen::StrictlyLower` and `Eigen::UnitLower` become
 * `PartialViewCL::Lower`. Similar for `Upper`. Any other view becomes
 * `PartialViewCL::Entire`.
 * @param eigen_type `UpLoType` to create a view from
 * @return view
 */
inline matrix_cl_view from_eigen_uplo_type(Eigen::UpLoType eigen_type) {
  if (eigen_type & Eigen::Lower) {
    return matrix_cl_view::Lower;
  }
  if (eigen_type & Eigen::Upper) {
    return matrix_cl_view::Upper;
  }
  return matrix_cl_view::Entire;
}

enum class TriangularMapCL { UpperToLower = 0, LowerToUpper = 1 };

// \cond
static const char* view_kernel_helpers = STRINGIFY(
    // \endcond
    /**
     * Determines which parts are nonzero in any of the input views.
     * @param left_view first view
     * @param right_view second view
     * @return combined view
     */
    int either(int left_view, int right_view) { return left_view | right_view; }

    /**
     * Determines which parts are nonzero in both input views.
     * @param left_view first view
     * @param right_view second view
     * @return common nonzero part
     */
    int both(int left_view, int right_view) { return left_view & right_view; }

    /**
     * Check whether a view contains certain nonzero part
     * @param view view to check
     * @param part part to check for (usually `Lower` or `Upper`)
     * @return true, if `view` has `part` nonzero
     */
    bool contains_nonzero(int view, int part) { return both(view, part); }
    // \cond
);
// \endcond

}  // namespace math
}  // namespace stan
#endif
#endif
