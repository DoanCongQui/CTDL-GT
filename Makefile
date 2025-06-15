CC=gcc
BUILD_DIR=build
CFLAGS = -Wall -Ilib

TARGET=$(BUILD_DIR)/main
SRCS = main.c lib/sinhvien.c lib/file.c lib/sort.c

$(TARGET): $(SRCS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)  

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f *.o $(TARGET)
