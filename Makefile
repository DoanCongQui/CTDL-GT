CC=gcc
BUILD_DIR=build

TARGET=$(BUILD_DIR)/main

$(TARGET): main.c
	$(CC) main.c -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f *.o $(TARGET)
