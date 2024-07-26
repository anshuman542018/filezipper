# filezipper
# FileZipper

FileZipper is a simple command-line file compression tool implemented in C++. It uses Run-Length Encoding (RLE) for compression and includes features like error handling and file integrity checks.

## Features

- File compression using Run-Length Encoding (RLE)
- File decompression
- Command-line interface
- Error handling
- File integrity checks
- Compression ratio calculation

## Requirements

- C++ compiler (e.g., g++, MinGW-w64, or MSVC)
- C++11 or later

## Compilation

To compile the program, use the following command:
![image](https://github.com/user-attachments/assets/faf4e67c-2583-4c2b-99a9-f9a122f785c9)


## Usage

Run the program with the following command:
![image](https://github.com/user-attachments/assets/2cf15700-14b0-42b7-84f9-2b80ad6f6d8e)

- `<input_file>`: The file you want to compress
- `<compressed_file>`: The name of the output compressed file
- `<decompressed_file>`: The name of the output decompressed file

Example: ![image](https://github.com/user-attachments/assets/a0341b63-952d-4c0b-b2c4-e3cc97474ed8)

## Output

The program will display:
- Compression completion status
- Original file size
- Compressed file size
- Compression ratio
- File integrity check result

## Limitations

- The current implementation uses a simple RLE algorithm, which may not be efficient for all types of files.
- Large files may take a considerable amount of time to process.
- The program does not support compressing multiple files or directories.

## Future Improvements

- Implement more advanced compression algorithms (e.g., Huffman coding, LZ77)
- Add support for compressing multiple files or directories
- Implement a progress bar for large files
- Enhance error handling and recovery mechanisms

## Contributing

Contributions to improve FileZipper are welcome. Please feel free to submit a Pull Request.

## License

This project is open source and available under the [MIT License](LICENSE).

