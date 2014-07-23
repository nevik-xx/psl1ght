.SUFFIXES:

TARGET		:=	$(notdir $(CURDIR))
BUILD		:=	build
SOURCE		:=	../common .
INCLUDE		:=	.
DATA		:=	data
LIBS		:=	

ifneq ($(BUILD),$(notdir $(CURDIR)))
PSL1GHT_INTERNAL := $(CURDIR)/../..
else
PSL1GHT_INTERNAL := $(CURDIR)/../../..
endif
include $(PSL1GHT_INTERNAL)/rules/internal.mk

LD			:=	$(PREFIX)ld

CFLAGS		+=	-O2 -Wall -std=gnu99

ODEPS		:=	stub.o lib.o

ifneq ($(BUILD),$(notdir $(CURDIR)))

export OUTPUT	:=	$(CURDIR)/$(TARGET)
export VPATH	:=	$(foreach dir,$(SOURCE),$(CURDIR)/$(dir)) \
					$(foreach dir,$(DATA),$(CURDIR)/$(dir))
export BUILDDIR	:=	$(CURDIR)/$(BUILD)
export DEPSDIR	:=	$(BUILDDIR)

CFILES		:= $(foreach dir,$(SOURCE),$(notdir $(wildcard $(dir)/*.c)))
CXXFILES	:= $(foreach dir,$(SOURCE),$(notdir $(wildcard $(dir)/*.cpp)))
SFILES		:= $(foreach dir,$(SOURCE),$(notdir $(wildcard $(dir)/*.S)))
BINFILES	:= $(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/*.bin)))

export OFILES	:=	$(CFILES:.c=.o) \
					$(CXXFILES:.cpp=.o) \
					$(SFILES:.S=.o)

export BINFILES	:=	$(BINFILES:.bin=.bin.h)

export INCLUDES	:=	$(foreach dir,$(INCLUDE),-I$(CURDIR)/$(dir)) \
					-I$(CURDIR)/$(BUILD)

.PHONY: $(BUILD) clean

$(BUILD):
	@[ -d $@ ] || mkdir -p $@
	@make --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile

clean:
	@echo Clean...
	@rm -rf $(BUILD) $(OUTPUT).elf $(OUTPUT).self $(OUTPUT).a

else

DEPENDS	:= $(OFILES:.o=.d)

OFILES	:=	$(filter-out $(ODEPS),$(OFILES))

$(OUTPUT).a: sprx.o $(OFILES)

lib.o: lib.c
	@echo "[CC]  $(notdir $<)"
	@$(CC) $(DEPSOPTIONS) -S -m32 $(INCLUDES) $< -o lib.S
	@$(CC) $(DEPSOPTIONS) -c lib.S -o $@

sprx.o: $(ODEPS)
	@$(LD) -r $(ODEPS) -o $@

-include $(DEPENDS)

endif
