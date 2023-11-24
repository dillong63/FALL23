CP = g++
CFLAGS = -ansi -pedantic -std=c++20
SRCS = huffman.cpp TreeNode.cpp
OBJS = $(SRCS:.cpp=.o)

huffman: $(OBJS)
	$(CP) -o  huffman $(OBJS)

huffman.o: huffman.cpp TreeNode.h
	$(CP) -c -g $(CFLAGS) huffman.cpp

TreeNode.o: TreeNode.cpp TreeNode.h
	$(CP) -c -g  $(CFLAGS) TreeNode.cpp

clean:
	rm -f $(OBJS) huffman