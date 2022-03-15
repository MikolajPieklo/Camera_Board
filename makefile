# Author: M Pieklo
# Date: 11.04.2022
# Project: Camera_board.
# License: Opensource

include makefiles/makefile_colors.mk
include makefiles/makefile_info.mk
include makefiles/makefile_dir.mk

NAME := $(OUT_DIR)/TARGET
MACH := cortex-m4
MAP  := -Wl,-Map=$(NAME).map  # Create map file
GC   := -Wl,--gc-sections     # Link for code size
DEBUGINFO := -DDEBUG -g3

# Use newlib.
USE_NOHOST   :=--specs=nosys.specs
USE_NANO     :=--specs=nano.specs
USE_SEMIHOST :=--specs=rdimon.specs

CFLAGS := \
	-c \
	-mcpu=$(MACH) \
	-mthumb \
	-mfloat-abi=soft \
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
	#-fpic

LDFLAGS := \
	-mcpu=$(MACH) \
	-mthumb \
	-mfloat-abi=soft \
	-T"STM32F407ZGTX_FLASH.ld" \
	$(MAP) \
	$(GC) \
	-static \
	$(USE_NANO) \
	-Wl,--start-group -lc -lm -Wl,--end-group \
	-L./$(OUT_DIR) \
	-l:libstm32f4xx.a
	
CONST := -DUSE_FULL_LL_DRIVER -DHSE_VALUE=8000000 -DHSI_VALUE=16000000 -DLSE_VALUE=32768 -DLSI_VALUE=32000 \
	-DHSE_STARTUP_TIMEOUT=100 -DLSE_STARTUP_TIMEOUT=5000 -DEXTERNAL_CLOCK_VALUE=12288000 -DVDD_VALUE=3300 \
	-DPREFETCH_ENABLE=1 -DINSTRUCTION_CACHE_ENABLE=1 -DDATA_CACHE_ENABLE=1 -DRCC_CFGR_MCO1EN -DUSE_FULL_ASSERT \
	-DHAL_SRAM_MODULE_ENABLED=1 $(CC_COMMON_MACRO)

INC := \
	-ICore/Inc/ \
	-IDrivers/STM32F4xx_HAL_Driver/Inc/ \
	-IDrivers/CMSIS/Device/ST/STM32F4xx/Include/ \
	-IDrivers/CMSIS/Include/ \
	-IGeneral/Inc/ \
	-Icm_backtrace/Inc/ \
	-Iembedded_log/Inc/ \
	-ICamera/Inc/ \
	-ILcd/Inc/ \
	-IHal/Inc

all: make$(OUT_DIR) $(OUT_DIR)/libstm32f4xx.a $(OUT_DIR)/target.elf $(OUT_DIR)/target.hex
test: test
	
make$(OUT_DIR):	
	@if [ ! -e $(OUT_DIR) ]; then mkdir $(OUT_DIR); fi
	@if [ ! -e $(CM_BACKTRACE_DIR) ]; then mkdir $(CM_BACKTRACE_DIR); fi
	@if [ ! -e $(CAMERA_DIR) ]; then mkdir $(CAMERA_DIR); fi
	@if [ ! -e $(DRIVER_DIR) ]; then mkdir $(DRIVER_DIR); fi
	@if [ ! -e $(GENERAL_DIR) ]; then mkdir $(GENERAL_DIR); fi
	@if [ ! -e $(HAL_DIR) ]; then mkdir $(HAL_DIR); fi
	@if [ ! -e $(LCD_DIR) ]; then mkdir $(LCD_DIR); fi
	@if [ ! -e $(LOG_DIR) ]; then mkdir $(LOG_DIR); fi
	@if [ ! -e $(GTEST_DIR) ]; then mkdir $(GTEST_DIR); fi

$(OUT_DIR)/main.o: Core/Src/main.c Core/Inc/main.h
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) Core/Src/main.c -o $(OUT_DIR)/main.o
	#                           		 			  $^              -o $@
	
$(OUT_DIR)/gpio.o: Core/Src/gpio.c Core/Inc/gpio.h
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) Core/Src/gpio.c -o $(OUT_DIR)/gpio.o
	
$(OUT_DIR)/spi.o: Core/Src/spi.c Core/Inc/spi.h
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) Core/Src/spi.c -o $(OUT_DIR)/spi.o
	
$(OUT_DIR)/usart.o: Core/Src/usart.c Core/Inc/usart.h
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) Core/Src/usart.c -o $(OUT_DIR)/usart.o	
		
$(OUT_DIR)/syscalls.o: Core/Src/syscalls.c
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) Core/Src/syscalls.c -o $(OUT_DIR)/syscalls.o	
	
$(OUT_DIR)/sysmem.o: Core/Src/sysmem.c
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) Core/Src/sysmem.c -o $(OUT_DIR)/sysmem.o	
	
$(OUT_DIR)/stm32f4xx_it.o: Core/Src/stm32f4xx_it.c Core/Inc/stm32f4xx_it.h
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) Core/Src/stm32f4xx_it.c -o $(OUT_DIR)/stm32f4xx_it.o	
	
$(OUT_DIR)/system_stm32f4xx.o: Core/Src/system_stm32f4xx.c
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) Core/Src/system_stm32f4xx.c -o $(OUT_DIR)/system_stm32f4xx.o
	
$(OUT_DIR)/startup_stm32f103c8tx.o:	Core/Startup/startup_stm32f407zgtx.s
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) -o $@ $^
	
$(DRIVER_DIR)/stm32f4xx_ll_dma.o: Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_dma.c
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) -o $@ $^
	
$(DRIVER_DIR)/stm32f4xx_ll_exti.o: Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_exti.c
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) -o $@ $^
	
$(DRIVER_DIR)/stm32f4xx_ll_gpio.o: Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_gpio.c
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) -o $@ $^
	
$(DRIVER_DIR)/stm32f4xx_ll_i2c.o: Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_i2c.c
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) -o $@ $^
	
$(DRIVER_DIR)/stm32f4xx_ll_pwr.o: Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_pwr.c
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) -o $@ $^
	
$(DRIVER_DIR)/stm32f4xx_ll_rcc.o: Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_rcc.c
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) -o $@ $^
	
$(DRIVER_DIR)/stm32f4xx_ll_spi.o: Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_spi.c
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) -o $@ $^
	
$(DRIVER_DIR)/stm32f4xx_ll_tim.o: Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_tim.c
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) -o $@ $^
	
$(DRIVER_DIR)/stm32f4xx_ll_usart.o: Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_usart.c
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) -o $@ $^
	
$(DRIVER_DIR)/stm32f4xx_ll_utils.o: Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_utils.c
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) ${INC} -o $@ $^
	
$(DRIVER_DIR)/stm32f4xx_dcmi.o: Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_dcmi.c
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) ${INC} -o $@ $^
	
$(DRIVER_DIR)/stm32f4xx_fsmc.o: Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_fsmc.c
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) -o $@ $^
	
$(GENERAL_DIR)/delay.o: General/Src/delay.c General/Inc/delay.h
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) General/Src/delay.c -o $(GENERAL_DIR)/delay.o
	
$(GENERAL_DIR)/platform.o:
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) General/Src/platform.c -o $(GENERAL_DIR)/platform.o
	
$(GENERAL_DIR)/printf.o: General/Src/printf.c General/Inc/printf.h
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) General/Src/printf.c -o $(GENERAL_DIR)/printf.o
	
$(GENERAL_DIR)/prj_version.o: General/Src/prj_version.c General/Inc/prj_version.h
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) General/Src/prj_version.c -o $(GENERAL_DIR)/prj_version.o
	
$(GENERAL_DIR)/Self_Test.o: General/Src/Self_Test.c
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) General/Src/Self_Test.c -o $(GENERAL_DIR)/Self_Test.o

$(HAL_DIR)/DCMI_hal.o:
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) Hal/Src/DCMI_hal.c -o $(HAL_DIR)/DCMI_hal.o
	
$(HAL_DIR)/DMA_hal.o:
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) Hal/Src/DMA_hal.c -o $(HAL_DIR)/DMA_hal.o
	
$(HAL_DIR)/IIC_hal.o:
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) Hal/Src/IIC_hal.c -o $(HAL_DIR)/IIC_hal.o

$(HAL_DIR)/FSMC_hal.o:
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) Hal/Src/FSMC_hal.c -o $(HAL_DIR)/FSMC_hal.o
	
$(HAL_DIR)/MCO_hal.o:
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) Hal/Src/MCO_hal.c -o $(HAL_DIR)/MCO_hal.o

$(CM_BACKTRACE_DIR)/cm_backtrace.o: cm_backtrace/Src/cm_backtrace.c
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) cm_backtrace/Src/cm_backtrace.c -o $(CM_BACKTRACE_DIR)/cm_backtrace.o
	
$(CM_BACKTRACE_DIR)/fault_test.o: cm_backtrace/Src/fault_test.c
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) cm_backtrace/Src/fault_test.c -o $(CM_BACKTRACE_DIR)/fault_test.o

$(LOG_DIR)/log.o: embedded_log/Src/log.c 
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) embedded_log/Src/log.c -o $(LOG_DIR)/log.o
	
$(CAMERA_DIR)/Camera.o: Camera/Src/Camera.c Camera/Inc/Camera.h
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) Camera/Src/Camera.c -o $(CAMERA_DIR)/Camera.o
	
$(LCD_DIR)/Lcd.o: Lcd/Src/Lcd.c Lcd/Inc/Lcd.h
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) Lcd/Src/Lcd.c -o $(LCD_DIR)/Lcd.o

$(LCD_DIR)/ST7789.o: Lcd/Src/ST7789.c Lcd/Inc/ST7789.h
	$(CC) $(CFLAGS) $(CONST) $(DEBUGINFO) $(INC) Lcd/Src/ST7789.c -o $(LCD_DIR)/ST7789.o

SLIB_FILES := \
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

$(OUT_DIR)/libstm32f4xx.a: $(SLIB_FILES)
	@echo "$(ccblue)\nStatic$(ccend)"
	arm-none-eabi-ar rcsv $(OUT_DIR)/libstm32f4xx.a $(SLIB_FILES)

$(OUT_DIR)/target.elf: \
	$(OUT_DIR)/system_stm32f4xx.o \
	$(OUT_DIR)/gpio.o \
	$(OUT_DIR)/spi.o \
	$(OUT_DIR)/usart.o \
	$(OUT_DIR)/stm32f4xx_it.o \
	$(OUT_DIR)/syscalls.o \
	$(OUT_DIR)/sysmem.o \
	$(OUT_DIR)/startup_stm32f103c8tx.o\
	$(OUT_DIR)/main.o \
	$(CM_BACKTRACE_DIR)/cm_backtrace.o \
	$(CM_BACKTRACE_DIR)/fault_test.o \
	$(GENERAL_DIR)/delay.o \
	$(GENERAL_DIR)/printf.o \
	$(GENERAL_DIR)/platform.o \
	$(GENERAL_DIR)/prj_version.o \
	$(GENERAL_DIR)/Self_Test.o \
	$(HAL_DIR)/DCMI_hal.o \
	$(HAL_DIR)/DMA_hal.o \
	$(HAL_DIR)/IIC_hal.o \
	$(HAL_DIR)/FSMC_hal.o \
	$(HAL_DIR)/MCO_hal.o \
	$(LOG_DIR)/log.o \
	$(CAMERA_DIR)/Camera.o \
	$(LCD_DIR)/Lcd.o \
	$(LCD_DIR)/ST7789.o \
	$(OUT_DIR)/libstm32f4xx.a
		@echo "$(ccblue)\nLinking$(ccend)"
		$(CC) $(LDFLAGS) $^ -o $@

$(OUT_DIR)/target.hex:
	$(CC2HEX) -O ihex $(OUT_DIR)/target.elf $(OUT_DIR)/target.hex
		
	@echo "$(ccblue)\nGenerating list file$(ccend)"
	arm-none-eabi-objdump -h -S  $(OUT_DIR)/target.elf > $(OUT_DIR)/target.list
	
	@echo "$(ccblue)\nCreating binary file$(ccend)"
	arm-none-eabi-objcopy -O binary  $(OUT_DIR)/target.elf  $(OUT_DIR)/target.bin
	
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
		
.PHONY: all make$(OUT_DIR) clean load $(OUT_DIR)/target.hex restart reset test $(OUT_DIR)/libstm32f4xx.a
