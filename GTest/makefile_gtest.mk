CPPCFLAGS := -std=c++17 -Wall -I/usr/local/include/gtest/ -I/usr/local/include/gmock/ -IGTest/stubs/Inc -c
CPPLFLAGS := -std=c++17 -pthread
GTEST     := /usr/local/lib/libgtest.a \
             /usr/local/lib/libgmock.a

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
	$(CPPC) $(CPPCFLAGS) GTest/stubs/Src/gtest_timestamp_stubs.cpp -o $(GTEST_DIR)/gtest_timestamp_stubs.o