#file searching path

CROSS_COMPILE=arm-unknown-linux-gnu-
#CROSS_COMPILE=arm-linux-
CC=$(CROSS_COMPILE)gcc
LD=$(CROSS_COMPILE)ld
AR=$(CROSS_COMPILE)ar
RM=rm
CP=cp

CFLAGS += -Wall $(INCPATH) -DPOS8510 -DCONFIG_NLGP730_L1

# 程序链接参数
LDFLAGS=

#程序中用到的函数库
#LIBS= -L../env -lndk -lwidget -L../lib -lcard -lprint -ltool -lui -L../../../../../lib -lcrypto
LIBS= -L../env -lndk -lwidget -lcrypto -L../lib -lcard -ltool -lui 
# -lcrypto -lssl

# 生成文件的路径
BINDIR = .

# 生成的程序名
NAME = main

#文件搜索路径
VPATH =../src


#头文件搜索路径
INCLPATH =  -I../env -I../inc -I../libapi -I../../../../../../third_party/openssl-1.0.0g/include/

LIBPATH =

# 程序中用到的模块
SRCS=$(wildcard $(VPATH)/*.c)
OBJS=$(patsubst $(VPATH)/%.c,%.o,$(SRCS))

#包含依赖文件
all: $(NAME)

#-include $(subst .o,.deps,$(OBJS))

$(NAME):config $(OBJS)
	-$(RM) $(BINDIR)/$(NAME)
#	$(CC) -fPIC -shared -o $(BINDIR)/$(NAME) $(OBJS) $(LIBS)
	$(CC) -o $(BINDIR)/$(NAME) $(OBJS) $(LIBS)

%.o: %.c
	$(CC) -c  $(CFLAGS) $(INCLPATH) $< -o $@

#自动生成依赖文件
config: $(subst .o,.deps,$(OBJS))

%.deps: %.c
	$(CC) -MM $(INCLPATH) $< > $@

INSTALL_PATH = /mnt/hgfs/E/upload/ 
install:
	cp -f $(NAME) $(INSTALL_PATH)
	sha256sum $(NAME)

.PHONY:clean
clean:
	-$(RM) $(OBJS)
	-$(RM) $(subst .o,.deps,$(OBJS))
