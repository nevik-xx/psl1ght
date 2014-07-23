TARGETS	:=	libaudio libcamera libgcm_sys libio libjpgdec liblv2 libnet libpngdec libsysmodule libsysutil libgem libsysfs

all:
	@for dir in $(TARGETS); do \
		$(MAKE) --no-print-directory -C $$dir; \
	done

clean:
	@for dir in $(TARGETS); do \
		$(MAKE) --no-print-directory -C $$dir clean; \
	done

install: all
	@mkdir -p $(PSL1GHT)/target/lib
	@cp */*.a $(PSL1GHT)/target/lib/

.PHONY: all install clean
