TOOLS := arm-none-linux-gnueabi-

CC := $(TOOLS)gcc
LD := $(TOOLS)ld
OBJCOPY := $(TOOLS)objcopy
OBJDUMP := $(TOOLS)objdump
CFLAGS := -nostdlib -O0 -I ./drv -I ./lib

TARGET	:= text

SOURCE :=$(shell find *|grep "\.[Ssc]$$")
OBJS := $(shell echo $(SOURCE)|sed "s/.[sSc]\b/.o/g")

$(TARGET).dis:$(OBJS)
	$(LD) -T link.lds $^ -o $(TARGET).elf
	$(OBJCOPY) -O binary -S $(TARGET).elf $(TARGET).bin
	$(OBJDUMP) -D $(TARGET).elf > $(TARGET).dis
	chmod 777 *
	
%.o : %.S
	$(CC) -o $@ $< -c

%.o : %.c
	$(CC) $(CFLAGS) -o $@ $< -c

flash:../tools/mk4412 $(TARGET).bin
	../tools/mk4412 $(TARGET).bin
	@if [ -b /dev/sdb ]; then \
	sudo mkfs.vfat -F 32 -I /dev/sdb; \
	sudo dd if=/dev/zero of=/dev/sdb bs=512 seek=1 iflag=dsync oflag=dsync count=2048; \
	sudo dd if=./$(TARGET).bin of=/dev/sdb bs=512 seek=1 iflag=dsync oflag=dsync; \
	fi
	
../tools/mk4412 : ../tools/mk4412.c
	gcc  $^ -static -o ../tools/mk4412

.PHONY :clean

clean:
	rm -rf $(OBJS) *.elf *.dis
	
	




