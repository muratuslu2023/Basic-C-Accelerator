SOURCE_FILE="main.c"
OUTPUT_BIN="main"

UTILS="utils"

UTILS_FILES=$(find "$UTILS" -type f -name "*.c")


clang "$SOURCE_FILE" "$UTILS_FILES" -o "bin/$OUTPUT_BIN"

if [ $? -eq 0 ]; then
    echo "Compilation successful. Output binary: $OUTPUT_BIN"
else
    echo "Compilation failed."
fi

