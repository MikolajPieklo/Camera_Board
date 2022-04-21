C_PROJECT_NAME_DEF := -DPROJECT_NAME="\"CamDev\""
C_USER_NAME_DEF    := -DUSER_NAME="\"$(shell whoami)\""
C_BUILD_DATE_DEF   := -DBUILD_DATE="\"$(shell date +%Y-%m-%d)\""
C_BUILD_TIME_DEF   := -DBUILD_TIME="\"$(shell date +%H:%M:%S)\""
CC_PATH            := $(shell which arm-none-eabi-gcc)
CC_VERSION         := $(shell arm-none-eabi-gcc -dumpversion)
CC                 := arm-none-eabi-gcc
CC_OBJCOPY         := arm-none-eabi-objcopy
CC_OBJDUMP         := arm-none-eabi-objdump
CC_AR              := arm-none-eabi-ar
VERSION            := $(shell git describe --tags)
COMMIT_ID          := $(shell git rev-parse HEAD)

CPPC_PATH          := $(shell which g++)
CPPC_VERSION       := $(shell g++ -dumpversion)
CPPC               := g++

$(info --------------------------)
$(info User: $(shell whoami))
$(info Date: $(shell date +%d-%m-%Y))
$(info Time: $(shell date +%H:%M:%S))

ifneq ($(shell test -e $(CC_PATH) && echo -n yes),yes)
$(error error: ARM package '$(CC_PATH)' does not exist!)
else
$(info CC_PATH: $(CC_PATH))
$(info CC version: $(CC_VERSION))
endif

ifneq ($(shell test -e $(CPPC_PATH) && echo -n yes),yes)
$(error error: Compiler '$(CPPC_PATH)' does not exist!)
else
$(info CPPC_PATH: $(CPPC_PATH))
$(info CPPC version: $(CPPC_VERSION))
endif

$(info --------------------------)
$(info Version: $(VERSION))
$(info Commit ID: $(COMMIT_ID))
$(info --------------------------)

CC_COMMON_MACRO = $(C_PROJECT_NAME_DEF) $(C_USER_NAME_DEF) $(C_BUILD_DATE_DEF) $(C_BUILD_TIME_DEF)
