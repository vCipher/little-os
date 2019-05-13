OBJECTS = loader.o kmain.o frame-buffer.o string.o
CC = i686-elf-gcc
CFLAGS = -std=gnu99 -ffreestanding -O0 -Wall -Wextra -g

LD = i686-elf-gcc
LDFLAGS = -T link.ld -ffreestanding -nostdlib -lgcc

AS = i686-elf-as
ASFLAGS =

ISO = genisoimage
ISOFLAGS = -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 \
	-A os -input-charset utf8 -quiet -boot-info-table 

QEMU = qemu-system-i386

all: kernel.elf

kernel.elf: $(OBJECTS)
	$(LD) $(LDFLAGS) $(OBJECTS) -o $@

os.iso: kernel.elf
	cp -R iso iso_stage
	cp $< iso_stage/boot/$<
	$(ISO) $(ISOFLAGS) -o $@ iso_stage

run: os.iso
	$(QEMU) -cdrom $<

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf *.o kernel.elf os.iso bochsrc.txt iso_stage