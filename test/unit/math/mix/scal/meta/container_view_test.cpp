#include <gtest/gtest.h>
#include <stan/math/prim/scal/meta/container_view.hpp>
#include <boost/type_traits/conditional.hpp>
#include <stan/math/rev/core.hpp>
#include <stan/math/fwd/core.hpp>
#include <stan/math/prim/scal/meta/is_constant_struct.hpp>

TEST(MathMeta, container_view_var) {
  using stan::math::container_view;
  using stan::math::var;
  using stan::math::fvar;

  stan::math::start_nested();
  var* y = static_cast<var*>(stan::math::chainable::operator new(sizeof(var) * 1));
  container_view<fvar<var>, var> view_test(var(4.0), y);
  view_test[0] = 1.0;
  EXPECT_FLOAT_EQ(1.0, view_test[0].val());
  EXPECT_FLOAT_EQ(1.0, y[0].val());
}

TEST(MathMeta, container_view_fvar_var) {
  using stan::math::container_view;
  using stan::math::var;
  using stan::math::fvar;

  stan::math::start_nested();
  fvar<var>* y = static_cast<fvar<var>*>(stan::math::chainable::operator new(sizeof(fvar<var>) * 1));
  container_view<fvar<fvar<var> >, fvar<var> > view_test(var(4.0), y);
  view_test[0] = 1.0;
  EXPECT_FLOAT_EQ(1.0, view_test[0].val_.val());
  EXPECT_FLOAT_EQ(1.0, y[0].val_.val());
}

TEST(MathMeta, container_view_no_throw_var) {
  using stan::math::container_view;
  using boost::conditional;
  using stan::math::dummy;
  using stan::is_constant_struct;
  using stan::math::var;
  using stan::math::fvar;

  var* arr = static_cast<var*>(stan::math::chainable::operator new(sizeof(var) * 1));
  container_view<conditional<is_constant_struct<fvar<var> >::value, dummy, fvar<var> >::type, var> view_test(var(4.0), arr);
  EXPECT_NO_THROW(view_test[0]);
}

TEST(MathMeta, container_view_no_throw_fvar_var) {
  using stan::math::container_view;
  using boost::conditional;
  using stan::math::dummy;
  using stan::is_constant_struct;
  using stan::math::var;
  using stan::math::fvar;

  fvar<var>* arr = static_cast<fvar<var>*>(stan::math::chainable::operator new(sizeof(fvar<var>) * 1));
  container_view<conditional<is_constant_struct<fvar<fvar<var> > >::value, dummy, fvar<fvar<var> > >::type, fvar<var> > view_test(var(4.0), arr);
  EXPECT_NO_THROW(view_test[0]);
}
