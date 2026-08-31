# Vigilant Fiesta PS3 homebrew scaffold

This repository sketch provides a minimal PlayStation 3 homebrew scaffold for playing locally-owned / copyright-free media.

IMPORTANT: This project is a learning scaffold. It does NOT include working PS3 platform bindings — you'll need to integrate PSL1GHT or your PS3 SDK, add on-screen rendering, controller handling, and playback code.

Files added
- Makefile — placeholder build targets; replace with your PSL1GHT build commands
- src/main.c — minimal, commented C scaffold (host-friendly stdio UI). Replace TODOs with PS3-specific code
- scripts/transcode_ps3.sh — ffmpeg helper to prepare MP4/H.264 files for PS3
- .gitignore — build artifacts

Quick start (development on PC)
1. Prepare a USB stick with your copyright-free files (e.g., sample.mp4) and mount it at /dev_usb000 (Linux host examples may vary).
2. Transcode a file if needed:
   ./scripts/transcode_ps3.sh sample_source.mp4 sample.mp4
3. Build and test the host-friendly UI:
   gcc -o vigilant_fiesta src/main.c
   ./vigilant_fiesta

Porting to PS3 (high level)
1. Install PSL1GHT or your PS3 homebrew toolchain and set up cross-compiler environment.
2. Replace the stdio UI with PSL1GHT video initialization and draw text to screen.
3. Use PS3 filesystem mounts (e.g., /dev_usb000) and controller input APIs to browse and select files.
4. For playback, either:
   - Integrate a decoder library that can run under PSL1GHT (complex), or
   - Prepare pre-encoded MP4/H.264 files and use a minimal player that interfaces with PS3 video output.

Legal and safety notes
- Only use this scaffold with content you own or that is public-domain / CC-licensed for redistribution.
- This project does NOT provide or assist in circumventing DRM or streaming copyrighted content without authorization.

Next steps I can help with
- Convert this scaffold into a PSL1GHT project with a working build (I can add a PSL1GHT Makefile and example build commands if you have PSL1GHT installed)
- Add a simple on-screen menu example using PSL1GHT's video/text APIs
- Add an example of preparing PS3-optimized files and a small test suite

If you want me to proceed and commit a PSL1GHT-specific Makefile and a more complete integration, confirm that you have the PSL1GHT toolchain installed on your side and I'll add the platform files.
