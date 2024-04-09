PRJ=$(lastword $(subst /, ,$(PWD)))
FQBN=arduino:avr:uno
PORT=/dev/ttyUSB0

BINDIR=build
BINFILE=$(BINDIR)/$(PRJ).ino.with_bootloader.bin
ACLI=arduino-cli
ACLI_FLAGS= \
	--fqbn $(FQBN)

$(BINFILE):
	$(ACLI) $(ACLI_FLAGS) --output-dir $(BINDIR) compile .


all: $(BINFILE)


.PHONY: clean
clean::
	-rm build/*


.PHONY: upload
upload: $(BINFILE)
	$(ACLI) $(ACLI_FLAGS) --input-dir $(BINDIR) -p $(PORT) upload .
