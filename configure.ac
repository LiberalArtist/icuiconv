dnl Process this file with autoconf to produce a configure script.
AC_INIT([ICU Iconv],
        [0.1],
        [philip@philipmcgrath.com],
        [icuiconv],
        [https://github.com/LiberalArtist/icuiconv])
dnl SPDX-License-Identifier: CC0-1.0
dnl SPDX-FileCopyrightText:  Philip McGrath <philip@philipmcgrath.com>
dnl --------------------------------------------------------------------------

dnl Minimum Autoconf version required.
dnl FIXME: do we actually need 2.71?
AC_PREREQ([2.63]) dnf ? might need 2.71

dnl Where to find configure input.
AC_CONFIG_SRCDIR([iconv.c])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([build-aux/m4])

dnl Checks for programs.
dnl We need a C compiler.
dnl TODO: check for Zuo.
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_MKDIR_P
AC_PROG_MAKE_SET()

AX_CHECK_ICU([2.6], [], [])

AC_CONFIG_FILES([Makefile main.zuo])
AC_OUTPUT()
