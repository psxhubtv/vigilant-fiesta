## PS3 PSL1GHT integration and host demo

This update adds a PS3-targeted Makefile scaffold and a host-friendly interactive
terminal demo so you can see the menu and selection flow on your development
machine before porting the UI to the PS3.

What was added
- psl1ght/Makefile: placeholder Makefile for building with a PSL1GHT toolchain. You MUST set PSL1GHT_PATH to your installed PSL1GHT path before building.
- src/ps3/ps3_main.c: PS3 scaffold with TODOs showing where to add PSL1GHT/SCE calls (video, input, filesystem, playback).
- src/host/terminal_player.c: an ncurses-based interactive demo that lists files in a media directory and lets you select one. This demonstrates the menu flow you should port to PS3 on-screen rendering.

Build & run the host demo (Linux/mac)
1. Install ncurses dev package (Ubuntu example):
   sudo apt-get install libncurses5-dev libncursesw5-dev
2. Build:
   gcc -o host_player src/host/terminal_player.c -lncurses
3. Run (point to a media directory or it will try /dev_usb000):
   ./host_player ./media

Porting notes for PS3
1. Ensure you have PSL1GHT installed and set PSL1GHT_PATH in psl1ght/Makefile.
2. Replace TODOs in src/ps3/ps3_main.c with proper includes and calls. Typical tasks:
   - Initialize PSL1GHT video and create a framebuffer you can draw into.
   - Initialize controller input and poll pad state for navigation.
   - Use PS3 filesystem APIs to enumerate files on /dev_usb000.
   - Implement a playback hand-off to your chosen decoder or playback API.
3. Build using the PSL1GHT toolchain (example):
   cd psl1ght
   make

Safety & legal reminder
- Only use this with content you own or that is licensed/public-domain for redistribution.
- This project does NOT assist with DRM circumvention.

If you want, I can now:
- Try to implement a PSL1GHT on-screen menu example using concrete PSL1GHT API calls (I will need to know which PSL1GHT headers and toolchain you have), OR
- Add audio/video playback stub that demonstrates how to call an existing decoder on PS3 (requires details about available decoder libraries/toolchain).

Which should I do next?