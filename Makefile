CC = gcc
CFLAGS = -fopenmp -Wall -O2
TARGET = matrix_multiplication

all: $(TARGET)

$(TARGET): matrix_multiplication.c
	$(CC) $(CFLAGS) -o $(TARGET) matrix_multiplication.c

run: $(TARGET)
	./$(TARGET) matrix_a.txt matrix_b.txt sonuclar.txt

clean:
	rm -f $(TARGET)










