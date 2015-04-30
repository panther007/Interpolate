#Project Name
PRJ_NAME = Interpolate

#Target Name of the prj
TARGET = Interpolate

#Objects of project
OBJS = \
  test_Interpolate.o

#Source files
SRC = \
  Interpolate.hpp\
  test_Interpolate.cpp

.PHONY: clean debug pack clang

CC = g++
CPPFLAGS = -g -Wall -std=c++11 -Wextra -pedantic
LDFLAGS= -DCS540_TEST_MANIPS

#%.o: %.cpp %.hpp
#	$(CC) $(CPPFLAGS) $(LDFLAGS) -c $< -o $@

#build the prj
$(TARGET):  test_Interpolate.cpp
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $< -o $@

#build the debug enabled object
debug: CPPFLAGS = -g -Wall -std=c++11 -DDEBUG
debug: test_Interpolate.cpp
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $< -o $(TARGET)

#build the using clang++
clang: CC = clang++
clang: test_Interpolate.cpp
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $< -o $(TARGET)

#clean the objects
clean:
	rm -rf $(OBJS) $(TARGET) $(PRJ_NAME).tar.gz *~


