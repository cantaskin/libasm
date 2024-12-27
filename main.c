#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "libasm.h"

// Assembly fonksiyonlarının prototipleri
size_t ft_strlen(const char *str);
int ft_strcmp(const char *s1, const char *s2);
ssize_t ft_read(int fd, void *buf, size_t count);
char *ft_strcpy(char *dest, const char *src);
char *ft_strdup(const char *s);
ssize_t ft_write(int fd, const void *buf, size_t count);

void test_strcpy(const char *test_str) {
    printf("[ft_strcpy vs strcpy Test]\n");
    char buffer1[256] = {0};
    char buffer2[256] = {0};

    printf("Source string: '%s'\n", test_str);
    
    char *my_strcpy = ft_strcpy(buffer1, test_str);
    char *libc_strcpy = strcpy(buffer2, test_str);

    printf("ft_strcpy result: '%s'\n", my_strcpy);
    printf("strcpy result: '%s'\n", libc_strcpy);
    printf("Result: %s\n\n", (strcmp(buffer1, buffer2) == 0) ? "PASS" : "FAIL");
}

void test_strdup(const char *test_str) {
    printf("[ft_strdup vs strdup Test]\n");
    printf("Original string: '%s'\n", test_str);

    char *my_strdup = ft_strdup(test_str);
    char *libc_strdup = strdup(test_str);

    printf("ft_strdup result: '%s'\n", my_strdup);
    printf("strdup result: '%s'\n", libc_strdup);
    printf("Result: %s\n\n", (strcmp(my_strdup, libc_strdup) == 0) ? "PASS" : "FAIL");

    free(my_strdup);
    free(libc_strdup);
}

void test_write(const char *test_str) {
    printf("[ft_write vs write Test]\n");
    
    int fd1 = open("ft_write_test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    int fd2 = open("write_test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    
    size_t len = strlen(test_str);
    ssize_t my_write = ft_write(fd1, test_str, len);
    ssize_t libc_write = write(fd2, test_str, len);

    printf("ft_write return: %zd\n", my_write);
    printf("write return: %zd\n", libc_write);
    printf("Result: %s\n\n", (my_write == libc_write) ? "PASS" : "FAIL");

    close(fd1);
    close(fd2);
}

// ft_strlen karşılaştırma fonksiyonu
void test_strlen(const char *test_str) {
    printf("[ft_strlen vs strlen Test]\n");
    printf("Input String: '%s'\n", test_str);

    size_t my_strlen = ft_strlen(test_str);
    size_t libc_strlen = strlen(test_str);

    printf("ft_strlen: %zu\n", my_strlen);
    printf("strlen: %zu\n", libc_strlen);
    printf("Result: %s\n\n", (my_strlen == libc_strlen) ? "PASS" : "FAIL");
}

// ft_strcmp karşılaştırma fonksiyonu
void test_strcmp(const char *str1, const char *str2) {
    printf("[ft_strcmp vs strcmp Test]\n");
    printf("String 1: '%s'\nString 2: '%s'\n", str1, str2);

    int my_strcmp = ft_strcmp(str1, str2);
    int libc_strcmp = strcmp(str1, str2);

    printf("ft_strcmp: %d\n", my_strcmp);
    printf("strcmp: %d\n", libc_strcmp);
    printf("Result: %s\n\n", (my_strcmp == libc_strcmp) ? "PASS" : "FAIL");
}

// ft_read karşılaştırma fonksiyonu
void test_read(const char *filename, size_t count) {
    printf("[ft_read vs read Test]\n");
    printf("File: '%s', Bytes to Read: %zu\n", filename, count);

    char my_buf[256] = {0};
    char libc_buf[256] = {0};

    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Failed to open file");
        return;
    }

    ssize_t my_read = ft_read(fd, my_buf, count);
    lseek(fd, 0, SEEK_SET); // Dosya başına dön
    ssize_t libc_read = read(fd, libc_buf, count);

    close(fd);

    printf("ft_read: %zd bytes, content: '%s'\n", my_read, my_buf);
    printf("read: %zd bytes, content: '%s'\n", libc_read, libc_buf);
    printf("Result: %s\n\n", 
        (my_read == libc_read && strcmp(my_buf, libc_buf) == 0) ? "PASS" : "FAIL");
}

int main() {
    // --- Test Cases ---

    // 1. ft_strlen ve strlen testleri
    printf("=== ft_strlen ve strlen Testleri ===\n");
    test_strlen("Hello, Assembly!");
    test_strlen("");
    test_strlen("A very long string to test the function.");

    // 2. ft_strcmp ve strcmp testleri
    printf("=== ft_strcmp ve strcmp Testleri ===\n");
    test_strcmp("Assembly", "Assembly");
    test_strcmp("Assembly", "Assembly!");
    test_strcmp("", "");
    test_strcmp("abc", "xyz");

    // 3. ft_read ve read testleri
    printf("=== ft_read ve read Testleri ===\n");
    const char *filename = "test.txt"; // Test dosyasını oluşturun
    FILE *file = fopen(filename, "w");
    if (file) {
        fprintf(file, "This is a test file for ft_read and read.");
        fclose(file);
    }

    test_read(filename, 10);
    test_read(filename, 50);
    test_read(filename, 0); // Hiçbir şey okumak için
    remove(filename); // Test sonrası dosyayı temizle

    // Existing tests
    test_strlen("Hello, World!");
    test_strlen("");
    
    test_strcmp("Hello", "Hello");
    test_strcmp("Hello", "World");
    test_strcmp("", "");
    
    // New tests
    test_strcpy("Hello, World!");
    test_strcpy("");
    
    test_strdup("Hello, World!");
    test_strdup("");
    
    test_write("Hello, World!\n");
    test_write("");

    return 0;
}
