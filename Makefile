PRJ=$(lastword $(subst /, ,$(PWD)))
PACKAGER = arduino
ARCH = avr
BOARD = uno
FQBN = $(PACKAGER):$(ARCH):$(BOARD)
PORT = /dev/ttyUSB0
BAUDRATE = 115200
space := $(subst ,, )
ACORE := $(subst $(space),:,$(wordlist 1,2,$(subst :, ,$(FQBN))))

BINDIR=build
BINFILE=$(BINDIR)/$(PRJ).ino.with_bootloader.bin
ACLI=arduino-cli
ACLI_FLAGS= \
	--fqbn $(FQBN)
BUILD_FLAGS= \
	--build-property "build.extra_flags=-DPRJ=$(PRJ)"
SRCS = \
	$(PRJ).ino \
	common.h \
	menu.ino \
	menu.h


$(BINFILE): $(SRCS)
	$(ACLI) $(ACLI_FLAGS) --output-dir $(BINDIR) compile $(BUILD_FLAGS) .


all: $(BINFILE)

DEPS = \
	LiquidCrystal \
	RotaryEncoder


.PHONY: env
env:
	$(ACLI) core update-index
	$(ACLI) core install $(ACORE)
	for dep in $(DEPS); do \
		$(ACLI) lib install $$dep; \
	done


.PHONY: clean
clean::
	arduino-cli cache clean
	-rm build/*


.PHONY: flash
flash: $(BINFILE)
	$(ACLI) $(ACLI_FLAGS) --input-dir $(BINDIR) -p $(PORT) upload .


.PHONY: screen
screen:
	screen $(PORT) $(BAUDRATE)
