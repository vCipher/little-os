CURRENT_DIR=$(shell pwd)
INTERMEDIATE_DIR=${CURRENT_DIR}/stage
OUTPUT_DIR=${CURRENT_DIR}/bin
SOURCE_DIR=${CURRENT_DIR}/src

ISO=genisoimage
ISOFLAGS= \
	-R -b boot/grub/stage2_eltorito \
	-no-emul-boot -boot-load-size 4 \
	-A os -input-charset utf8 -boot-info-table 

QEMU=qemu-system-i386

build_image: ${OUTPUT_DIR} ${INTERMEDIATE_DIR}
	make -C ${SOURCE_DIR} ${OUTPUT_DIR}/kernel.elf \
	INTERMEDIATE_DIR=${INTERMEDIATE_DIR} \
	OUTPUT_DIR=${OUTPUT_DIR}

build_iso: build_image
	cp -R iso ${INTERMEDIATE_DIR}/iso
	cp ${OUTPUT_DIR}/kernel.elf ${INTERMEDIATE_DIR}/iso/boot/kernel.elf
	${ISO} ${ISOFLAGS} -o ${OUTPUT_DIR}/os.iso ${INTERMEDIATE_DIR}/iso

${OUTPUT_DIR}:
	mkdir $@

${INTERMEDIATE_DIR}:
	mkdir $@

all: build_image build_iso

run: build_image
	${QEMU} -kernel ${OUTPUT_DIR}/kernel.elf

debug: build_image
	${QEMU} -s -S -kernel ${OUTPUT_DIR}/kernel.elf

clean:
	rm -rf ${INTERMEDIATE_DIR}
	rm -rf ${OUTPUT_DIR}

.PHONY: all clean run build_image build_iso