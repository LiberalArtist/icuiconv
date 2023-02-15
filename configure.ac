dnl Process this file with autoconf to produce a configure script.
AC_INIT([ICU Iconv],[0.1],[philip@philipmcgrath.com])
dnl SPDX-License-Identifier: CC0-1.0
dnl SPDX-FileCopyrightText:  Philip McGrath
dnl --------------------------------------------------------------------------

dnl Minimum Autoconf version required.
dnl FIXME: do we actually need 2.71?
AC_PREREQ([2.63]) dnf ? might need 2.71

dnl TODO: consider git-version-gen from Gnulib
dnl TODO: how to use AC_COPYRIGHT([my stuff here])

dnl Where to find configure input.
AC_CONFIG_SRCDIR([iconv.c])
AC_CONFIG_AUX_DIR([build-aux])

dnl Checks for programs.
dnl We need a C compiler.
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_MKDIR_P
