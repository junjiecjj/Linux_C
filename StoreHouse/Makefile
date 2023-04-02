


##makefile
#OBJ_FILE=CodedModulationSystemSimulator.o  AWGN.o  BinaryLDPCCodec.o  BPSKModem.o EbitsinLDPC_simulator.o   RandNum.o  RanXORLDPCCodec.o  SourceSink.o Utility.o

#CC=g++
#CXXFLAGS=-Wall -O -g

#main :$(OBJ_FILE)
#	cc  $(CXXFLAGS)  $^ -o $@




#clean:
#	@echo "clean project"
#	-rm *.o
#	@echo "clean complete"


#.PHONY:clean




#  ①变量定义
CC=gcc			# 定义变量，表示使用g++编译器
# SRCS=main.cpp a.cpp	  # 表示项目中所需要的源文件，有更多直接在后面添加，换行用反斜杠
SRCS= main.c  Diceroll.c  C_StaticGlo.c loc_stat.c PartAB.c S_and_r.c Where.c  VLAmal.c ExpMath.c  Utility.c  ArrayPoint.c String.c StructMallocFree.c

OBJS=$(SRCS:.c=.o)	#  表示目标依赖文件.o，其又依赖于SRCS中的cpp文件
EXEC=outexe		# 表示生成的可执行文件
CFLAGS=-Wall -O2 -g	# 配置编译器，-Wall表示输出警告信息，-O表示编译优化，-g表示编译debug版本
LDLIBS += -L./usrLib -lm


#  ②目标文件的编译规则
$(EXEC):$(OBJS)		# 规则入口->目标文件：引入依赖文件,等价于mytest:main.o a.o
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS)  $(LDLIBS)
# 等价于g++ -o mytest main.o a.o;注意：命令前要缩进tab

# ③目标依赖文件的编译规则
%o:%cpp			#缺省规则：等价于%o:%cpp，表示OBJS中所有的.o文件与SRCS中同名.cpp文件的依赖关系（OBJS中有多个.o，下面命令就需要执行多次）
	$(CC) $(CFLAGS) -o $@ -c $<  	#等价于g++ -o main.o -c main.cpp和g++ -o a.o -c a.cpp


#  ④清除命令
# 注意：此处clean不是文件，而是一个动作
clean:
	rm -rf $(OBJS)  #删除依赖文件
