# CC = g++

# CFLAGS = -g -Wall 
# LDFLAGS = -L./lib/ -lsfml-graphics -lsfml-window -lsfml-system

# SOURCES = src/*.cpp

# all:
# 	@$(CC) $(CFLAGS) $(SOURCES) $(LDFLAGS) -o Quoridor -I include/

# run: 
# 	@./Quoridor

# clean:
# 	rm -rf *.o Quoridor

all: build_cmake
	@cd build; \
	make


build_cmake: prepare_submodule
	@mkdir -p build; \
	cd build; \
	cmake ..

prepare_submodule:
	@git submodule init; \
	git submodule update

run: 
	@./Quoridor

clean:
	rm -rf *.o Quoridor