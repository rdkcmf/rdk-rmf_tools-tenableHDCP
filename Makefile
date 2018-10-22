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
TENABLEHDCP_DIR?=$(RDK_DIR)/tenableHDCP


RM          := rm -rf 
INCLUDE     := -I$(RDK_DIR)/devicesettings/ds/include       \
    	       -I$(RDK_DIR)/devicesettings/ds               \
  	       -I$(RDK_DIR)/devicesettings/rpc/include      \
    	       -I$(RDK_DIR)/devicesettings/hal/include      \
    	       -I$(RDK_DIR)/devicesettings/src              \
               -I$(RDK_DIR)/iarmmgrs/generic/mfr/include    \
               -I$(RDK_DIR)/logger/include/

INCLUDE      += $(HAL_INCLUDE)

INSTALL     := $(TENABLEHDCP_DIR)/bin

LDFLAGS     := -L$(RDK_DIR)/devicesettings/install/lib -lds 


LDFLAGS		+= $(HAL_LDFLAGS)
LDFLAGS		+= $(GLIB_LDFLAGS)

CFLAGS      +=   -g -fPIC -D_REENTRANT -Wall $(INCLUDE)

.PHONY: $(OUTPUT)

BINARIES    := $(patsubst %.cpp,%,$(wildcard *.cpp))
UNINSTALL   := $(patsubst %,$(PWD)/install/bin/%, $(BINARIES))

all: $(BINARIES)  install
	@echo "Build Finished...."

$(BINARIES):
	@echo "Building $@ ...."
	$(CXX) $(CFLAGS) $@.cpp -o $@ $(LDFLAGS)
	@mkdir -p $(INSTALL)
	@cp -f $@ $(INSTALL)/.

install:
	@echo "Copying the binaries to bin install folder..."
	@mv $(BINARIES) $(INSTALL)/.

uninstall:
	@echo "Removing bin from install folder..."
	@$(RM) $(UNINSTALL)

clean:
	@echo "Cleaning the directory..."
	@$(RM) $(BINARIES)



