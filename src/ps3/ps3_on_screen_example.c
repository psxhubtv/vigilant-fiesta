/*
  PS3 on-screen menu example (PSL1GHT-style)

  Notes:
  - This is a practical example showing how the on-screen menu/selection flow works.
  - You must replace the include paths and link flags to match your PSL1GHT installation.
  - The drawing calls use typical PSL1GHT helper functions (debug font / simple text draw).
  - This example focuses on menu/navigation and file listing from a PS3 USB mount (e.g., /dev_usb000).
  - Playback is a placeholder: hand off to your decoder/playback path after selection.

  Build:
  - Configure psl1ght/Makefile PSL1GHT_PATH to your environment, then build with that Makefile.
  - This file may need small edits depending on the exact PSL1GHT headers you have.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

// TODO: Replace these with your PSL1GHT/SCE headers
// #include <psl1ght.h>
// #include <video.h>
// #include <pad.h>
// #include <debugFont.h>

#define MEDIA_DIR "/dev_usb000"
#define MAX_FILES 256
#define MAX_NAME 256

// Minimal text-draw helper (replace with real debugFont or draw routines)
static void draw_text(int x, int y, const char *text) {
    // TODO: call the PSL1GHT debug font or text draw function here.
    // Example (psl1ght debug font):
    // debugFontPrintf(x, y, "%s", text);
    // For now we print to stdout so early testing on host shows some output.
    printf("%s\n", text);
}

// Poll controller and return simple navigation codes: -1 up, +1 down, 0 none, 2 select, -2 quit
static int poll_pad_stub(void) {
    // TODO: replace with pad polling (cellPad or libpad) and map buttons:
    // - Up -> return -1
    // - Down -> return +1
    // - Cross/Start -> return 2 (select)
    // - Circle/Select -> return -2 (quit)
    // For now return 0; implement real pad logic when compiling for PS3.
    return 0;
}

int main(int argc, char **argv) {
    char *files[MAX_FILES];
    int count = 0;

    // 1) Initialize PSL1GHT subsystems (video, pad, fs)
    // TODO: call psl1ght init functions:
    // videoInitDefault();
    // debugFontInitDefault();
    // padInitDefault();
    draw_text(0, 0, "Vigilant Fiesta - PS3 On-Screen Menu (example)");

    // 2) Enumerate files in MEDIA_DIR
    DIR *d = opendir(MEDIA_DIR);
    if (!d) {
        draw_text(0, 2, "Could not open media directory (is the USB mounted?)");
        // On device you might sleep a bit and retry or show an error screen.
        return 0;
    }
    struct dirent *entry;
    while ((entry = readdir(d)) != NULL && count < MAX_FILES) {
        // skip directories and hidden entries
        if (entry->d_type == DT_REG) {
            files[count] = strdup(entry->d_name);
            count++;
        }
    }
    closedir(d);

    if (count == 0) {
        draw_text(0, 2, "No media files found in " MEDIA_DIR);
        return 0;
    }

    int highlight = 0;
    int running = 1;
    while (running) {
        // Clear / draw menu
        // TODO: clear framebuffer or draw background
        draw_text(0, 1, "Use controller to navigate. Cross to select. Circle to quit.");
        for (int i = 0; i < count; ++i) {
            char line[MAX_NAME + 32];
            if (i == highlight) {
                snprintf(line, sizeof(line), "> %s", files[i]);
            } else {
                snprintf(line, sizeof(line), "  %s", files[i]);
            }
            draw_text(0, 4 + i, line);
        }

        // Poll controller (replace poll_pad_stub with real pad polling)
        int action = poll_pad_stub();
        if (action == -1) {
            if (highlight > 0) highlight--;
        } else if (action == +1) {
            if (highlight < count - 1) highlight++;
        } else if (action == 2) {
            // User selected file
            char msg[512];
            snprintf(msg, sizeof(msg), "Selected: %s", files[highlight]);
            draw_text(0, 4 + count + 2, msg);
            draw_text(0, 4 + count + 4, "Launching playback (placeholder)...");
            // TODO: hand off to playback/decoder:
            // play_file_on_ps3(MEDIA_DIR, files[highlight]);
            // For now pause briefly
            // sleep(2) or wait for input to return to menu.
        } else if (action == -2) {
            running = 0;
        }

        // On PSL1GHT you'd swap buffers or flip the framebuffer here.
        // videoSwapBuffers();
    }

    // Clean up
    for (int i = 0; i < count; ++i) free(files[i]);
    // debugFontExit();
    // padExit();
    // videoExit();
    return 0;
}
