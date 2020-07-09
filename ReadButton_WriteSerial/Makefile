
F_CPU = 8000000
TARGET_VDD_MV = 4000
TARGET_VDD = 4.0

# ---------------------------------------------------------------------

DEVICE ?= PFS154
OUTPUT_NAME ?= ReadButton_WriteSerial_$(DEVICE)

ifeq ($(DEVICE), PMS152)
	ARCH = pdk14
else ifeq ($(DEVICE), PFS154)
	ARCH = pdk14
else ifeq ($(DEVICE), PFS173)
	ARCH = pdk15
endif

ROOT_DIR = ..
BUILD_DIR = .build
OUTPUT_DIR = .output

OUTPUT = $(OUTPUT_DIR)/$(OUTPUT_NAME)

LIB_SOURCES = $(wildcard $(ROOT_DIR)/lib/*.c) $(wildcard $(ROOT_DIR)/lib/**/*.c)
LIB_OBJECTS = $(patsubst $(ROOT_DIR)/lib/%.c,$(BUILD_DIR)/lib/%.rel,$(LIB_SOURCES))

SOURCES = main.c
OBJECTS = $(patsubst %.c,$(BUILD_DIR)/%.rel,$(SOURCES))

# http://sdcc.sourceforge.net/doc/sdccman.pdf
COMPILE = sdcc -m$(ARCH) -c --std-sdcc11 --opt-code-size -D$(DEVICE) -DF_CPU=$(F_CPU) -DTARGET_VDD_MV=$(TARGET_VDD_MV) -I. -I$(ROOT_DIR)/include
BUILD_LIB = sdar -rc
LINK = sdcc -m$(ARCH)
EASYPDKPROG = easypdkprog

# symbolic targets:
all: size

print-%: ; @echo $* = $($*)

$(BUILD_DIR)/%.rel: %.c
	@mkdir -p $(dir $@)
	$(COMPILE) -o $@ $<

$(BUILD_DIR)/lib/%.rel: $(ROOT_DIR)/lib/%.c
	@mkdir -p $(dir $@)
	$(COMPILE) -o $@ $<

$(BUILD_DIR)/lib.lib: $(LIB_OBJECTS)
	$(BUILD_LIB) $@ $(LIB_OBJECTS)

$(OUTPUT).ihx: $(OBJECTS) $(BUILD_DIR)/lib.lib
	@mkdir -p $(dir $(OUTPUT))
	$(LINK) --out-fmt-ihx -o $(OUTPUT).ihx $(OBJECTS) $(BUILD_DIR)/lib.lib

$(OUTPUT).bin: $(OUTPUT).ihx
	makebin -p $(OUTPUT).ihx $(OUTPUT).bin

build: $(OUTPUT).bin

size: build
	@echo '---------- Segments ----------'
	@egrep '(ABS,CON)|(REL,CON)' $(OUTPUT).map | gawk --non-decimal-data '{dec = sprintf("%d","0x" $$2); print dec " " $$0}' | /usr/bin/sort -n -k1 | cut -f2- -d' '
	@echo '------------------------------'
	@stat -L --printf "Size of $(OUTPUT_NAME).bin: %s bytes\n" $(OUTPUT).bin

program: size
	$(EASYPDKPROG) -n $(DEVICE) write $(OUTPUT).ihx

run:
	$(EASYPDKPROG) -r $(TARGET_VDD) start

clean:
	rm -r -f $(BUILD_DIR) $(OUTPUT_DIR)
