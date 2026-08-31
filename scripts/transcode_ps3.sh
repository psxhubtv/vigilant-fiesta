#!/usr/bin/env bash
# scripts/transcode_ps3.sh
# Minimal ffmpeg script to transcode input video to a PS3-friendly MP4/H.264 baseline file.
# Use this to prepare your copyright-free files for playback on PS3 homebrew players.

set -euo pipefail

if [ "$#" -lt 2 ]; then
  echo "Usage: $0 input_file output_file.mp4"
  exit 1
fi

INPUT="$1"
OUTPUT="$2"

# PS3 is generally tolerant of H.264 High/Main profiles, but for maximum
# compatibility with simple homebrew decoders use baseline/profile:baseline.
# Adjust -profile:v and -level as needed for your decoder.

ffmpeg -i "$INPUT" \
  -c:v libx264 -profile:v baseline -level 3.1 -preset medium -crf 20 \
  -pix_fmt yuv420p -movflags +faststart \
  -c:a aac -b:a 128k \
  -y "$OUTPUT"

echo "Transcoded $INPUT -> $OUTPUT"
