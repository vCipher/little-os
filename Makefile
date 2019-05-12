OBJECTS = loader.o kmain.o
CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
			-nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c
LDFLAGS = -T link.ld -melf_i386

AS = nasm
ASFLAGS = -f elf

ISO = genisoimage
ISOFLAGS = -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 \
			-A os -input-charset utf8 -quiet -boot-info-table 

BOCHS = bochs

all: kernel.elf

kernel.elf: $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) -o $@

os.iso: kernel.elf
	cp -R iso iso_stage
	cp $< iso_stage/boot/$<
	$(ISO) $(ISOFLAGS) -o $@ iso_stage

bochsrc.txt: os.iso
	echo "megs:            32" >> $@
	echo "display_library: sdl" >> $@
	echo "romimage:        file=/usr/share/bochs/BIOS-bochs-latest" >> $@
	echo "vgaromimage:     file=/usr/share/bochs/VGABIOS-lgpl-latest" >> $@
	echo "ata0-master:     type=cdrom, path=$<, status=inserted" >> $@
	echo "boot:            cdrom" >> $@
	echo "log:             bochslog.txt" >> $@
	echo "clock:           sync=realtime, time0=local" >> $@
	echo "cpu:             count=1, ips=1000000" >> $@

run: bochsrc.txt
	$(BOCHS) -f $< -q

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf *.o kernel.elf os.iso bochsrc.txt iso_stage