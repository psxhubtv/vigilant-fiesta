/*
 * src/main.c
 * Minimal scaffold for a PS3 homebrew media player.
 *
 * This file purposefully avoids platform-specific PSL1GHT/PS3 APIs to remain
 * a safe scaffold. Replace the TODO blocks with PSL1GHT system/video/input
 * initialization and the appropriate build system for your toolchain.
 *
 * What this scaffold provides:
 * - A simple menu loop (host-friendly using stdio) that lists files from a
 *   configured media directory (e.g., /dev_usb000) and prints a selection.
 * - Clear TODO markers where PS3 platform code should be integrated.
 *
 * Note: To run on an actual PS3 homebrew environment you will need to:
 * - Replace the stdio UI with on-screen rendering (PSL1GHT video APIs).
 * - Use PS3 filesystem APIs and ensure correct permissions for USB paths.
 * - Integrate a decoder or use prepared PS3-friendly MP4/H264 files.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define MEDIA_DIR "/dev_usb000"

static void list_media(const char *path) {
    DIR *d = opendir(path);
    if (!d) {
        printf("Could not open media directory: %s\n", path);
        return;
    }

    struct dirent *entry;
    int idx = 0;
    while ((entry = readdir(d)) != NULL) {
        if (entry->d_type == DT_REG) {
            printf("%2d: %s\n", idx++, entry->d_name);
        }
    }
    closedir(d);
}

int main(int argc, char **argv) {
    /*
     * TODO (PS3):
     * - Initialize PSL1GHT or your chosen PS3 homebrew framework (video/input/etc.)
     * - Replace the stdio-based menu with on-screen rendering and controller input
     * - Implement file browser that uses PS3 filesystem mounts (e.g., /dev_usb000)
     * - Integrate a video decoder or call a platform-provided playback API
     */

    printf("Vigilant Fiesta - PS3 Homebrew Player (minimal scaffold)\n");
    printf("Using media directory: %s\n\n", MEDIA_DIR);

    /* Host-friendly listing: useful during development on Linux/host */
    list_media(MEDIA_DIR);

    printf("\nEnter the filename to play (or 'q' to quit): ");
    char buf[512];
    if (fgets(buf, sizeof(buf), stdin) == NULL) return 0;
    buf[strcspn(buf, "\n")] = '\0';
    if (strcmp(buf, "q") == 0) {
        printf("Exiting.\n");
        return 0;
    }

    printf("Selected: %s\n", buf);
    printf("TODO: launch playback of the selected file using PS3 playback APIs or integrated decoder.\n");

    /*
     * Example development workflow:
     * - On your dev PC, place compatible MP4 files in a USB drive and mount as /dev_usb000
     * - Iterate on the UI using the host-friendly stdio version
     * - When ready, replace TODOs and compile with PSL1GHT toolchain
     */

    return 0;
}
