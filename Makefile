PRJ=$(lastword $(subst /, ,$(PWD)))
FQBN=arduino:avr:uno
PORT=/dev/ttyUSB0
space := $(subst ,, )
ACORE := $(subst $(space),:,$(wordlist 1,2,$(subst :, ,$(FQBN))))

BINDIR=build
BINFILE=$(BINDIR)/$(PRJ).ino.with_bootloader.bin
ACLI=arduino-cli
ACLI_FLAGS= \
	--fqbn $(FQBN)
BUILD_FLAGS= \
	--build-property "build.extra_flags=-DPRJ=$(PRJ)"


$(BINFILE):
	$(ACLI) $(ACLI_FLAGS) --output-dir $(BINDIR) compile $(BUILD_FLAGS) .


all: $(BINFILE)

DEPS = \
	LiquidCrystal \
	RotaryEncoder


.PHONY: en
en:


.PHONY: env
env:
	$(ACLI) core update-index
	$(ACLI) core install $(ACORE)
	for dep in $(DEPS); do \
		$(ACLI) lib install $$dep; \
	done


.PHONY: clean
clean::
	-rm build/*


.PHONY: flash
flash: $(BINFILE)
	$(ACLI) $(ACLI_FLAGS) --input-dir $(BINDIR) -p $(PORT) upload .
