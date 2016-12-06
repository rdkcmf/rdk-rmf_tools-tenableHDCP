#!/bin/bash
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
#

#SCRIPT=$(readlink -f "$0")
#SCRIPTS_DIR=`dirname "$SCRIPT"`
#export BUILDS_DIR=${RDK_DIR}
#export COMBINED_DIR=${RDK_DIR}

echo "BUILDS_DIR=$BUILDS_DIR"


echo "Setting hal Environment variables..."
PWD=`pwd`
export RDK_DIR=`echo $PWD/..`
source $PWD/soc/build/soc_env.sh

echo "Building TenableHDCP tool..."
make
make all
if [ $? -ne 0 ] ; then
  echo "TenableHDCP Build Failed..."
  exit 1
else
  echo "TenableHDCP Build Success.."
  exit 0
fi

