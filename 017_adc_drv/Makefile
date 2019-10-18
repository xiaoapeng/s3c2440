TOOLS := arm-linux-
CC := $(TOOLS)gcc
LD := $(TOOLS)ld
OBJCOPY := $(TOOLS)objcopy
OBJDUMP := $(TOOLS)objdump
#宏开关选项
CONFIG_DEBUG =y




#编译选项
CFLAGS := -march=armv4 -nostdlib  -O0 -I ./drv -I ./lib -I ./debug -I ./drv/lcd/




#目标文件名
TARGET	:= text


#CONFIG_DEBUG
LDFLAGS =
NCOMPREQ :=\?
ifeq ($(CONFIG_DEBUG),y)
LDFLAGS += -L $(shell dirname `$(CC) -print-libgcc-file-name`) -lgcc
CFLAGS	+=-DCONFIG_DEBUG
else
#不需要编译的文件夹
NCOMPREQ +=|debug/
endif


SOURCE_C 	:=$(shell find *|grep "\.[c]$$"|grep -v -P "($(NCOMPREQ))")
SOURCE_ASM 	:=$(shell find *|grep "\.[Ss]$$")
OBJS_C		:=$(shell echo $(SOURCE_C)|sed "s/\.[c]\b/.o/g")
OBJS_ASM	:=$(shell echo $(SOURCE_ASM)|sed "s/\.[sS]\b/.o/g")
OBJS += $(OBJS_ASM) $(OBJS_C)

$(TARGET).bin:$(OBJS) 
	$(LD)  -T link.lds $^ -o $(TARGET).elf $(LDFLAGS)
	$(OBJCOPY) -O binary -S $(TARGET).elf $(TARGET).bin
	$(OBJDUMP) -D $(TARGET).elf > $(TARGET).dis
	@chmod 777 *

nor_flash:
	sudo oflash 0 1 1 0 0 $(TARGET).bin

nand_flash:
	sudo oflash 0 1 0 0 0 $(TARGET).bin

$(OBJS_C):%.o : %.c 

$(OBJS_ASM):%.o : %.S 


.PHONY :clean

clean:
	rm -rf $(OBJS) *.elf *.dis *.bin
	




