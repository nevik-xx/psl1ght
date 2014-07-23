.SUFFIXES:

TARGET		:=	$(notdir $(CURDIR))
BUILD		:=	build
SOURCE		:=	source
INCLUDE		:=	
DATA		:=	data
LIBS		:=	

ifneq ($(BUILD),$(notdir $(CURDIR)))
PSL1GHT_INTERNAL := $(CURDIR)/..
else
PSL1GHT_INTERNAL := $(CURDIR)/../..
endif
include $(PSL1GHT_INTERNAL)/rules/internal.mk

CFLAGS		+=	-O2 -Wall

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

install: $(BUILD)
	@mkdir -p $(PSL1GHT)/target/lib
	@cp -f $(TARGET).a $(PSL1GHT)/target/lib/

else

DEPENDS	:= $(OFILES:.o=.d)

$(OUTPUT).a: $(OFILES)


-include $(DEPENDS)

endif
