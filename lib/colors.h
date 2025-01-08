#ifndef COLORS_H
#define COLORS_H

// RESET
#define RESET "\033[0m"

// WARNA TEKS
#define BLACK "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

// WARNA TEKS TEBAL
#define BOLD_BLACK "\033[1;30m"
#define BOLD_RED "\033[1;31m"
#define BOLD_GREEN "\033[1;32m"
#define BOLD_YELLOW "\033[1;33m"
#define BOLD_BLUE "\033[1;34m"
#define BOLD_MAGENTA "\033[1;35m"
#define BOLD_CYAN "\033[1;36m"
#define BOLD_WHITE "\033[1;37m"

// LATAR BELAKANG
#define BG_BLACK "\033[40m"
#define BG_RED "\033[41m"
#define BG_GREEN "\033[42m"
#define BG_YELLOW "\033[43m"
#define BG_BLUE "\033[44m"
#define BG_MAGENTA "\033[45m"
#define BG_CYAN "\033[46m"
#define BG_WHITE "\033[47m"

// LATAR BELAKANG TEBAL (HIGH INTENSITY)
#define BG_BRIGHT_BLACK "\033[100m"
#define BG_BRIGHT_RED "\033[101m"
#define BG_BRIGHT_GREEN "\033[102m"
#define BG_BRIGHT_YELLOW "\033[103m"
#define BG_BRIGHT_BLUE "\033[104m"
#define BG_BRIGHT_MAGENTA "\033[105m"
#define BG_BRIGHT_CYAN "\033[106m"
#define BG_BRIGHT_WHITE "\033[107m"

// GAYA TEKS
#define BOLD "\033[1m"       // Teks tebal
#define DIM "\033[2m"        // Teks redup
#define ITALIC "\033[3m"     // Teks miring
#define UNDERLINE "\033[4m"  // Garis bawah
#define BLINK "\033[5m"      // Berkedip
#define REVERSE "\033[7m"    // Warna terbalik (teks jadi latar, latar jadi teks)

// COMBINATIONS
#define RED_ON_WHITE BG_WHITE RED
#define GREEN_ON_BLACK BG_BLACK GREEN
#define BOLD_RED_ON_YELLOW BG_YELLOW BOLD_RED

// Fungsi reset otomatis
#define COLOR_RESET(color) color RESET

#endif // COLORS_H