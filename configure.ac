AC_PREREQ([2.69])
AC_INIT([jsmincpp], [1.0RC], [damon at damonblog.com])
AC_LANG(C++)
AM_INIT_AUTOMAKE([foreign subdir-objects])

AC_CHECK_PROG(RAGEL_CHECK, ragel, yes)
if test x"$RAGEL_CHECK" != x"yes" ; then
    AC_MSG_WARN([ragel is not installed. Please install ragel.])
fi

LIBS=" -lpthread -lgmock -lgtest"
AC_CHECK_LIB([gtest_main], [main],
  [HAVE_GTEST=1] [TEST_LIBS="$TEST_LIBS -lgtest_main -lgtest"],
  AC_MSG_WARN([libgtest is not installed. Please install libgtest.]))

AC_CHECK_LIB([gmock_main], [main],
  [HAVE_GMOCK=1] [TEST_LIBS="$TEST_LIBS -lgmock_main -lgmock"],
  AC_MSG_WARN([libgmock is not installed. Please install libgmock.]))
LIBS=""

AC_CONFIG_FILES([Makefile include/Makefile tests/Makefile])
AC_OUTPUT
