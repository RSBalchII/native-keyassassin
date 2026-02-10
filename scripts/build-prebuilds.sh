#!/bin/bash
# Script to build prebuilds for all platforms

echo "Building prebuilds for native-keyassassin..."

# Install dependencies
npm install

# Build for all N-API versions and platforms
npm run prebuild-all

echo "Prebuilds created successfully for native-keyassassin!"
echo "Files are located in the lib/binding directory"