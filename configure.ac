##########################################################################
# If not stated otherwise in this file or this component's Licenses.txt
# file the following copyright and licenses apply:
#
# Copyright 2016 RDK Management
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
##########################################################################

AC_PREREQ([2.69])

AC_INIT(tenableHDCP, 0.1, www.broadcom.com)
AC_CONFIG_SRCDIR([tenableHDCP.cpp])

AM_INIT_AUTOMAKE(1.0)
LT_INIT
LT_LANG([C++])
#AM_PROG_AR
# Checks for libraries.
AC_PROG_LIBTOOL

AC_CHECK_LIB(pthread, pthread_create)

AC_SUBST([LDFLAGS])
# Checks for library functions.
AC_FUNC_MALLOC
AC_SUBST(NEXUS_ENDIAN,[1234])
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
