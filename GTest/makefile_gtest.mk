# Author: M Pieklo
# Date: 11.04.2022
# Project: UT for camera board.
# License: Opensource

ifeq ($(shell whoami), runner)
$(info I am CI)
CI_PATH := "x86_64-linux-gnu/"
else
$(info I am local PC)
CI_PATH :=
endif

CPPCFLAGS := -std=c++17 \
             -Wall \
             -I/usr/local/include/gtest/ \
             -I/usr/local/include/gmock/ \
             -IGTest/stubs/inc \
             -c

CPPLFLAGS := -std=c++17 \
            -pthread


GTEST     := /usr/local/lib/${CI_PATH}libgtest.a \
             /usr/local/lib/${CI_PATH}libgmock.a

CPP_OBJ_FILES := $(GTEST_DIR)/main.o \
                 $(GTEST_DIR)/gtest_timestamp_stubs.o \
                 $(GTEST_DIR)/camera_tst.o

test: make$(OUT_DIR) $(CPP_OBJ_FILES)
	@echo "$(ccblue)\nLinking$(ccend)"
	$(CPPC) $(CPPLFLAGS) -o $(GTEST_DIR)/test $(CPP_OBJ_FILES) $(GTEST)

$(GTEST_DIR)/main.o:
	$(CPPC) $(CPPCFLAGS) GTest/main.cpp -o $(GTEST_DIR)/main.o

$(GTEST_DIR)/camera_tst.o:
	$(CPPC) $(CPPCFLAGS) GTest/camera_tst.cpp -o $(GTEST_DIR)/camera_tst.o

$(GTEST_DIR)/gtest_timestamp_stubs.o:
	$(CPPC) $(CPPCFLAGS) GTest/stubs/src/gtest_timestamp_stubs.cpp -o $(GTEST_DIR)/gtest_timestamp_stubs.o
	