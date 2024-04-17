PRJ=$(lastword $(subst /, ,$(PWD)))
PACKAGER = arduino
ARCH = avr
BOARD = uno
FQBN = $(PACKAGER):$(ARCH):$(BOARD)
PORT = /dev/ttyUSB0
BAUDRATE = 115200
space := $(subst ,, )
ACORE := $(subst $(space),:,$(wordlist 1,2,$(subst :, ,$(FQBN))))

BINDIR = build
BINFILE = $(BINDIR)/$(PRJ).ino.with_bootloader.bin
ACLI = arduino-cli
ACLI_FLAGS = \
	--fqbn $(FQBN)
LIBPATH = lib
BUILD_FLAGS = \
	--build-property "build.extra_flags=-DPRJ=$(PRJ)" \
	--library $(LIBPATH)

SRCS = \
	common.h \
	rotary.ino \
	rotary.h \
	display.ino \
	display.h \
	dialog.ino \
	dialog.h \
	menu.ino \
	menu.h \
	$(PRJ).ino \


$(BINFILE): $(SRCS)
	$(ACLI) $(ACLI_FLAGS) --output-dir $(BINDIR) compile $(BUILD_FLAGS) .


all: $(BINFILE)

DEPS = \
	LiquidCrystal \
	RotaryEncoder \
	ThermistorLibrary


.PHONY: deps
deps:
	for dep in $(DEPS); do \
		$(ACLI) lib install $$dep; \
	done


.PHONY: env
env:
	$(ACLI) core update-index
	$(ACLI) core install $(ACORE)
	make deps


.PHONY: clean
clean::
	-arduino-cli cache clean
	-rm build/*


.PHONY: flash
flash: $(BINFILE)
	$(ACLI) $(ACLI_FLAGS) --input-dir $(BINDIR) -p $(PORT) upload .


.PHONY: screen
screen:
	screen $(PORT) $(BAUDRATE)
