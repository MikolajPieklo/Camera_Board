# Author: M Pieklo
# Date: 11.04.2022
# Project: CameraBoard.
# License: Opensource

include makefiles/makefile_colors.mk
include makefiles/makefile_info.mk
include makefiles/makefile_dir.mk

NAME := $(OUT_DIR)/TARGET
MACH := cortex-m4
MAP  := -Wl,-Map=$(NAME).map  # Create map file
GC   := -Wl,--gc-sections     # Link for code size
DEBUGINFO := #-DDEBUG -g3

# Use newlib.
USE_NOSYS    :=--specs=nosys.specs
USE_NANO     :=--specs=nano.specs
USE_RDIMON   :=--specs=rdimon.specs

CFLAGS := \
	-c \
	-mcpu=$(MACH) \
	-mthumb \
	-mfloat-abi=hard \
	-mfpu=fpv4-sp-d16 \
	-std=gnu11 \
	-O0 \
	-DSTM32F407xx \
	$(USE_NANO) \
	-Wall \
	-Wextra \
	-ffunction-sections \
	-fdata-sections \
	-fstack-usage \
	-MMD \
	-Wfatal-errors \
	-Werror=implicit 

LDFLAGS := \
	-mcpu=$(MACH) \
	-mthumb \
	-mfloat-abi=hard \
	-mfpu=fpv4-sp-d16 \
	-T"STM32F407ZGTX_FLASH.ld" \
	$(MAP) \
	$(GC) \
	-static \
	$(USE_NANO) \
	-Wl,--start-group -lc -lm -Wl,--end-group \
	-L./$(LIB_DIR) \
	-l:libstm32f4xx.a \
	-l:libhal.a
	
CONST := -DUSE_FULL_LL_DRIVER -DHSE_VALUE=8000000 -DHSI_VALUE=16000000 -DLSE_VALUE=32768 -DLSI_VALUE=32000 \
	-DHSE_STARTUP_TIMEOUT=100 -DLSE_STARTUP_TIMEOUT=5000 -DEXTERNAL_CLOCK_VALUE=12288000 -DVDD_VALUE=3300 \
	-DPREFETCH_ENABLE=1 -DINSTRUCTION_CACHE_ENABLE=1 -DDATA_CACHE_ENABLE=1 -DRCC_CFGR_MCO1EN -DUSE_FULL_ASSERT \
	-DHAL_SRAM_MODULE_ENABLED=1 $(CC_COMMON_MACRO)

INC := \
	-ICore/inc/ \
	-IDrivers/STM32F4xx_HAL_Driver/inc/ \
	-IDrivers/CMSIS/Device/ST/STM32F4xx/inc/ \
	-IDrivers/CMSIS/Include/ \
	-IGeneral/inc/ \
	-Icm_backtrace/inc/ \
	-Iembedded_log/inc/ \
	-ICamera/inc/ \
	-ILcd/inc/ \
	-IHal/inc/ \
	-IOS/ \
	-IOS/inc/ \
	-IOS/portable/GCC/ARM_CM4F/ \
	-IOS/CMSIS_RTOS_V2/

all: make$(OUT_DIR) $(LIB_DIR)/libstm32f4xx.a $(LIB_DIR)/libhal.a $(OUT_DIR)/target.elf $(OUT_DIR)/target.hex
	
make$(OUT_DIR):	
	@if [ ! -e $(OUT_DIR) ]; then mkdir $(OUT_DIR); fi
	@if [ ! -e $(BIN_DIR) ]; then mkdir $(BIN_DIR); fi
	@if [ ! -e $(LIB_DIR) ]; then mkdir $(LIB_DIR); fi
	@if [ ! -e $(CM_BACKTRACE_DIR) ]; then mkdir $(CM_BACKTRACE_DIR); fi
	@if [ ! -e $(CAMERA_DIR) ]; then mkdir $(CAMERA_DIR); fi
	@if [ ! -e $(DRIVER_DIR) ]; then mkdir $(DRIVER_DIR); fi
	@if [ ! -e $(GENERAL_DIR) ]; then mkdir $(GENERAL_DIR); fi
	@if [ ! -e $(LCD_DIR) ]; then mkdir $(LCD_DIR); fi
	@if [ ! -e $(LOG_DIR) ]; then mkdir $(LOG_DIR); fi
	@if [ ! -e $(GTEST_DIR) ]; then mkdir $(GTEST_DIR); fi
	@if [ ! -e $(OS_DIR) ]; then mkdir $(OS_DIR); fi

$(BIN_DIR)/main.o: Core/src/main.c
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) Core/src/main.c -o $(BIN_DIR)/main.o
	#                           		 			  $^              -o $@
	
$(BIN_DIR)/gpio.o: Core/src/gpio.c
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) Core/src/gpio.c -o $(BIN_DIR)/gpio.o
	
$(BIN_DIR)/spi.o: Core/src/spi.c
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) Core/src/spi.c -o $(BIN_DIR)/spi.o
	
$(BIN_DIR)/usart.o: Core/src/usart.c
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) Core/src/usart.c -o $(BIN_DIR)/usart.o	
		
$(BIN_DIR)/syscalls.o: Core/src/syscalls.c
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) Core/src/syscalls.c -o $(BIN_DIR)/syscalls.o	
	
$(BIN_DIR)/sysmem.o: Core/src/sysmem.c
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) Core/src/sysmem.c -o $(BIN_DIR)/sysmem.o	
	
$(BIN_DIR)/stm32f4xx_it.o: Core/src/stm32f4xx_it.c
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) Core/src/stm32f4xx_it.c -o $(BIN_DIR)/stm32f4xx_it.o	
	
$(BIN_DIR)/system_stm32f4xx.o: Core/src/system_stm32f4xx.c
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) Core/src/system_stm32f4xx.c -o $(BIN_DIR)/system_stm32f4xx.o
	
$(BIN_DIR)/startup_stm32f103c8tx.o: Core/Startup/startup_stm32f407zgtx.s
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) -o $@ $^
	
$(DRIVER_DIR)/stm32f4xx_ll_dma.o: Drivers/STM32F4xx_HAL_Driver/src/stm32f4xx_ll_dma.c
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) -o $@ $^
	
$(DRIVER_DIR)/stm32f4xx_ll_exti.o: Drivers/STM32F4xx_HAL_Driver/src/stm32f4xx_ll_exti.c
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) -o $@ $^
	
$(DRIVER_DIR)/stm32f4xx_ll_gpio.o: Drivers/STM32F4xx_HAL_Driver/src/stm32f4xx_ll_gpio.c
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) -o $@ $^
	
$(DRIVER_DIR)/stm32f4xx_ll_i2c.o: Drivers/STM32F4xx_HAL_Driver/src/stm32f4xx_ll_i2c.c
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) -o $@ $^
	
$(DRIVER_DIR)/stm32f4xx_ll_pwr.o: Drivers/STM32F4xx_HAL_Driver/src/stm32f4xx_ll_pwr.c
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) -o $@ $^
	
$(DRIVER_DIR)/stm32f4xx_ll_rcc.o: Drivers/STM32F4xx_HAL_Driver/src/stm32f4xx_ll_rcc.c
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) -o $@ $^
	
$(DRIVER_DIR)/stm32f4xx_ll_spi.o: Drivers/STM32F4xx_HAL_Driver/src/stm32f4xx_ll_spi.c
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) -o $@ $^
	
$(DRIVER_DIR)/stm32f4xx_ll_tim.o: Drivers/STM32F4xx_HAL_Driver/src/stm32f4xx_ll_tim.c
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) -o $@ $^
	
$(DRIVER_DIR)/stm32f4xx_ll_usart.o: Drivers/STM32F4xx_HAL_Driver/src/stm32f4xx_ll_usart.c
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) -o $@ $^
	
$(DRIVER_DIR)/stm32f4xx_ll_utils.o: Drivers/STM32F4xx_HAL_Driver/src/stm32f4xx_ll_utils.c
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) ${INC} -o $@ $^
	
$(DRIVER_DIR)/stm32f4xx_dcmi.o: Drivers/STM32F4xx_HAL_Driver/src/stm32f4xx_dcmi.c
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) ${INC} -o $@ $^
	
$(DRIVER_DIR)/stm32f4xx_fsmc.o: Drivers/STM32F4xx_HAL_Driver/src/stm32f4xx_fsmc.c
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) -o $@ $^
	
$(GENERAL_DIR)/timestamp.o: General/src/timestamp.c
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) General/src/timestamp.c -o $(GENERAL_DIR)/timestamp.o
	
$(GENERAL_DIR)/platform.o:
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) General/src/platform.c -o $(GENERAL_DIR)/platform.o
	
$(GENERAL_DIR)/printf.o: General/src/printf.c
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) General/src/printf.c -o $(GENERAL_DIR)/printf.o
	
$(GENERAL_DIR)/project_info.o: General/src/project_info.c
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) General/src/project_info.c -o $(GENERAL_DIR)/project_info.o
	
$(GENERAL_DIR)/self_test.o: General/src/self_test.c
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) General/src/self_test.c -o $(GENERAL_DIR)/self_test.o

$(BIN_DIR)/dcmi_hal.o:
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) Hal/src/dcmi_hal.c -o $(BIN_DIR)/dcmi_hal.o
	
$(BIN_DIR)/dma_hal.o:
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) Hal/src/dma_hal.c -o $(BIN_DIR)/dma_hal.o
	
$(BIN_DIR)/iic_hal.o:
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) Hal/src/iic_hal.c -o $(BIN_DIR)/iic_hal.o

$(BIN_DIR)/fsmc_hal.o:
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) Hal/src/fsmc_hal.c -o $(BIN_DIR)/fsmc_hal.o
	
$(BIN_DIR)/mco_hal.o:
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) Hal/src/mco_hal.c -o $(BIN_DIR)/mco_hal.o

$(CM_BACKTRACE_DIR)/cm_backtrace.o: cm_backtrace/src/cm_backtrace.c
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) cm_backtrace/src/cm_backtrace.c -o $(CM_BACKTRACE_DIR)/cm_backtrace.o
	
$(CM_BACKTRACE_DIR)/fault_test.o: cm_backtrace/src/fault_test.c
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) cm_backtrace/src/fault_test.c -o $(CM_BACKTRACE_DIR)/fault_test.o

$(LOG_DIR)/log.o: embedded_log/src/log.c 
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) embedded_log/src/log.c -o $(LOG_DIR)/log.o
	
$(CAMERA_DIR)/camera.o: Camera/src/camera.c Camera/inc/camera.h
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) Camera/src/camera.c -o $(CAMERA_DIR)/camera.o
	
$(LCD_DIR)/lcd.o: Lcd/src/lcd.c Lcd/inc/lcd.h
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) Lcd/src/lcd.c -o $(LCD_DIR)/lcd.o

$(LCD_DIR)/st7789.o: Lcd/src/st7789.c Lcd/inc/st7789.h
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) Lcd/src/st7789.c -o $(LCD_DIR)/st7789.o
	
$(OS_DIR)/tasks.o: OS/src/tasks.c
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) OS/src/tasks.c -o $(OS_DIR)/tasks.o
	
$(OS_DIR)/timers.o: OS/src/timers.c
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) OS/src/timers.c -o $(OS_DIR)/timers.o
	
$(OS_DIR)/list.o: OS/src/list.c
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) OS/src/list.c -o $(OS_DIR)/list.o
	
$(OS_DIR)/queue.o: OS/src/queue.c
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) OS/src/queue.c -o $(OS_DIR)/queue.o
	
$(OS_DIR)/heap_4.o: OS/portable/MemMang/heap_4.c
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) OS/portable/MemMang/heap_4.c -o $(OS_DIR)/heap_4.o
	
$(OS_DIR)/port.o: OS/portable/GCC/ARM_CM4F/port.c
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) OS/portable/GCC/ARM_CM4F/port.c -o $(OS_DIR)/port.o
	
$(OS_DIR)/cmsis_os2.o: OS/CMSIS_RTOS_V2/cmsis_os2.c
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) OS/CMSIS_RTOS_V2/cmsis_os2.c -o $(OS_DIR)/cmsis_os2.o
	
$(OS_DIR)/idle_thread.o: OS/idle_thread.c
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) OS/idle_thread.c -o $(OS_DIR)/idle_thread.o
	
$(OS_DIR)/camera_thread.o: OS/camera_thread.c
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) OS/camera_thread.c -o $(OS_DIR)/camera_thread.o

LIB_FILES_STM32F4 := \
	$(DRIVER_DIR)/stm32f4xx_ll_dma.o \
	$(DRIVER_DIR)/stm32f4xx_ll_exti.o \
	$(DRIVER_DIR)/stm32f4xx_ll_gpio.o \
	$(DRIVER_DIR)/stm32f4xx_ll_i2c.o \
	$(DRIVER_DIR)/stm32f4xx_ll_pwr.o \
	$(DRIVER_DIR)/stm32f4xx_ll_rcc.o\
	$(DRIVER_DIR)/stm32f4xx_ll_spi.o\
	$(DRIVER_DIR)/stm32f4xx_ll_tim.o \
	$(DRIVER_DIR)/stm32f4xx_ll_usart.o \
	$(DRIVER_DIR)/stm32f4xx_ll_utils.o \
	$(DRIVER_DIR)/stm32f4xx_dcmi.o \
	$(DRIVER_DIR)/stm32f4xx_fsmc.o 

LIB_FILES_HAL := \
	$(BIN_DIR)/dcmi_hal.o \
	$(BIN_DIR)/dma_hal.o \
	$(BIN_DIR)/iic_hal.o \
	$(BIN_DIR)/fsmc_hal.o \
	$(BIN_DIR)/mco_hal.o 
	
$(LIB_DIR)/libstm32f4xx.a: $(LIB_FILES_STM32F4)
	@echo "$(ccblue)\nGenerating libstm32f4xx.a$(ccend)"
	$(CC_AR) rcsv $@ $^
	
$(LIB_DIR)/libhal.a: $(LIB_FILES_HAL)
	@echo "$(ccblue)\nGenerating libhal.a$(ccend)"
	$(CC_AR) rcsv $@ $^

$(OUT_DIR)/target.elf: \
	$(BIN_DIR)/system_stm32f4xx.o \
	$(BIN_DIR)/gpio.o \
	$(BIN_DIR)/spi.o \
	$(BIN_DIR)/usart.o \
	$(BIN_DIR)/stm32f4xx_it.o \
	$(BIN_DIR)/syscalls.o \
	$(BIN_DIR)/sysmem.o \
	$(BIN_DIR)/startup_stm32f103c8tx.o\
	$(BIN_DIR)/main.o \
	$(CM_BACKTRACE_DIR)/cm_backtrace.o \
	$(CM_BACKTRACE_DIR)/fault_test.o \
	$(GENERAL_DIR)/timestamp.o \
	$(GENERAL_DIR)/printf.o \
	$(GENERAL_DIR)/platform.o \
	$(GENERAL_DIR)/project_info.o \
	$(GENERAL_DIR)/self_test.o \
	$(LOG_DIR)/log.o \
	$(CAMERA_DIR)/camera.o \
	$(LCD_DIR)/lcd.o \
	$(LCD_DIR)/st7789.o \
	$(OS_DIR)/tasks.o \
	$(OS_DIR)/list.o \
	$(OS_DIR)/queue.o \
	$(OS_DIR)/heap_4.o \
	$(OS_DIR)/port.o \
	$(OS_DIR)/cmsis_os2.o \
	$(OS_DIR)/idle_thread.o \
	$(OS_DIR)/camera_thread.o \
	$(OS_DIR)/timers.o \
	$(LIB_DIR)/libhal.a \
	$(LIB_DIR)/libstm32f4xx.a
		@echo "$(ccblue)\nLinking$(ccend)"
		$(CC) $(LDFLAGS) $^ -o $@

$(OUT_DIR)/target.hex:
	@echo "$(ccblue)\nCreating hex file$(ccend)"
	$(CC_OBJCOPY) -O ihex $(OUT_DIR)/target.elf $(OUT_DIR)/target.hex
	
	@echo "$(ccblue)\nCreating bin file$(ccend)"
	$(CC_OBJCOPY) -O binary  $(OUT_DIR)/target.elf  $(OUT_DIR)/target.bin
		
	@echo "$(ccblue)\nGenerating list file$(ccend)"
	$(CC_OBJDUMP) -h -S  $(OUT_DIR)/target.elf > $(OUT_DIR)/target.list
	
	@echo "$(ccpurple)"
	arm-none-eabi-size $(OUT_DIR)/target.elf -A -x
	@echo "$(ccend)"
	
include GTest/makefile_gtest.mk

clean:
	rm -rf $(OUT_DIR)
	
load:
	openocd -f /usr/local/share/openocd/scripts/interface/st-link.cfg \
		-f /usr/local/share/openocd/scripts/target/stm32f4x.cfg \
		-c "program $(OUT_DIR)/target.elf verify reset exit"  #zamiast makra sprobowac out
		
restart:
	openocd -f /usr/local/share/openocd/scripts/interface/st-link.cfg \
		-f /usr/local/share/openocd/scripts/target/stm32f4x.cfg \
		-c "init"\
		-c "reset" \
		-c "exit"

reset:
	openocd -f /usr/local/share/openocd/scripts/interface/st-link.cfg \
		-f /usr/local/share/openocd/scripts/target/stm32f4x.cfg \
		-c "init"\
		-c "reset" \
		-c "exit"
		
doc :
	doxygen

.PHONY: all clean doc load make$(OUT_DIR) $(OUT_DIR)/target.hex restart reset test $(LIB_DIR)/libstm32f4xx.a $(LIB_DIR)/libhal.a
