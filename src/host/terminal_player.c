/*
 * src/host/terminal_player.c
 * Host-friendly interactive terminal demo using ncurses. This demonstrates the
 * UI and selection flow you can later port to the PS3 on-screen UI.
 *
 * Build (Linux/mac):
 *   gcc -o host_player src/host/terminal_player.c -lncurses
 * Run:
 *   ./host_player /path/to/media_dir
 *
 * Controls:
 *   Up/Down arrows to navigate
 *   Enter to "play" (placeholder)
 *   q to quit
 */

#include <ncurses.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define MAX_FILES 1024

int is_regular_file(const char *path) {
    struct stat st;
    if (stat(path, &st) != 0) return 0;
    return S_ISREG(st.st_mode);
}

int main(int argc, char **argv) {
    const char *media_dir = "/dev_usb000";
    if (argc >= 2) media_dir = argv[1];

    DIR *d = opendir(media_dir);
    if (!d) {
        fprintf(stderr, "Could not open media directory: %s\n", media_dir);
        return 1;
    }

    char *files[MAX_FILES];
    int count = 0;
    struct dirent *entry;
    while ((entry = readdir(d)) != NULL && count < MAX_FILES) {
        if (entry->d_type == DT_REG) {
            files[count++] = strdup(entry->d_name);
        }
    }
    closedir(d);

    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    int highlight = 0;
    int ch;
    while (1) {
        clear();
        mvprintw(0, 0, "Vigilant Fiesta - Host Demo (media dir: %s)", media_dir);
        mvprintw(1, 0, "Use Up/Down, Enter to select, q to quit");
        for (int i = 0; i < count; ++i) {
            if (i == highlight) attron(A_REVERSE);
            mvprintw(3 + i, 2, "%s", files[i]);
            if (i == highlight) attroff(A_REVERSE);
        }
        ch = getch();
        if (ch == 'q') break;
        switch (ch) {
            case KEY_UP: if (highlight > 0) highlight--; break;
            case KEY_DOWN: if (highlight < count - 1) highlight++; break;
            case 10: { // Enter
                clear();
                mvprintw(0, 0, "Selected: %s", files[highlight]);
                mvprintw(2, 0, "Playing (placeholder)... Press any key to return");
                // Here you'd hand off to a playback routine or invoke the player
                getch();
                break;
            }
        }
    }

    endwin();
    for (int i = 0; i < count; ++i) free(files[i]);
    return 0;
}
