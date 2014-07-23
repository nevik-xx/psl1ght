CC = gcc

ifdef WIN32
CFLAGS	+=	-I"C:\Program Files (x86)\GnuWin32\include" -L"C:\OpenSSL-Win32\lib\MinGW"
LDFLAGS	+=	-lgmp -leay32 \
	-L"C:\OpenSSL-Win32\lib\MinGW" "C:\Program Files (x86)\GnuWin32\bin\zlib1.dll"
POSTFIX	:=	exe
else
CFLAGS	+=	-I$(PS3SDK)/MinGW/include -I$(PS3SDK)/MinGW/include
LDFLAGS	+=	-L$(PS3SDK)/MinGW/lib -L$(PS3SDK)/MinGW/lib/openssl/engines-1.0.0 -lgmp -lcrypto -lz
POSTFIX	:=	
endif

TARGETS	:=	make_self$(POSTFIX) make_self_npdrm$(POSTFIX) package_finalize$(POSTFIX)

all: $(TARGETS)

make_self$(POSTFIX): make_self.c
	$(CC) $< $(CFLAGS) $(LDFLAGS) -o $@

make_self_npdrm$(POSTFIX): make_self.c
	$(CC) $< $(CFLAGS) $(LDFLAGS) -DNPDRM -o $@

package_finalize: package_finalize.c
	$(CC) $< $(CFLAGS) $(LDFLAGS) -o $@

install: $(TARGETS)
	@install -m 755 $(TARGETS) $(PSL1GHT)/host/bin/

clean:
	@rm -f $(TARGETS)

.PHONY: install clean
