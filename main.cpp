#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

// Function to compress data using RLE
std::vector<unsigned char> compress(const std::vector<unsigned char>& data) {
    std::vector<unsigned char> compressed;
    for (size_t i = 0; i < data.size(); ++i) {
        unsigned char count = 1;
        while (i + 1 < data.size() && data[i] == data[i + 1] && count < 255) {
            ++count;
            ++i;
        }
        compressed.push_back(count);
        compressed.push_back(data[i]);
    }
    return compressed;
}

// Function to decompress RLE data
std::vector<unsigned char> decompress(const std::vector<unsigned char>& data) {
    std::vector<unsigned char> decompressed;
    for (size_t i = 0; i < data.size(); i += 2) {
        unsigned char count = data[i];
        unsigned char value = data[i + 1];
        for (unsigned char j = 0; j < count; ++j) {
            decompressed.push_back(value);
        }
    }
    return decompressed;
}

bool filesAreEqual(const std::string& file1, const std::string& file2) {
    std::ifstream f1(file1, std::ifstream::binary|std::ifstream::ate);
    std::ifstream f2(file2, std::ifstream::binary|std::ifstream::ate);

    if (f1.fail() || f2.fail()) {
        return false; // file problem
    }

    if (f1.tellg() != f2.tellg()) {
        return false; // size mismatch
    }

    // seek back to beginning and use std::equal to compare contents
    f1.seekg(0, std::ifstream::beg);
    f2.seekg(0, std::ifstream::beg);
    return std::equal(std::istreambuf_iterator<char>(f1.rdbuf()),
                      std::istreambuf_iterator<char>(),
                      std::istreambuf_iterator<char>(f2.rdbuf()));
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <compressed_file> <decompressed_file>" << std::endl;
        return 1;
    }

    std::string inputFilename = argv[1];
    std::string compressedFilename = argv[2];
    std::string decompressedFilename = argv[3];

    try {
        // Read input file
        std::ifstream inputFile(inputFilename, std::ios::binary);
        if (!inputFile) {
            throw std::runtime_error("Error opening input file: " + inputFilename);
        }

        std::vector<unsigned char> inputData(
            (std::istreambuf_iterator<char>(inputFile)),
            std::istreambuf_iterator<char>()
        );
        inputFile.close();

        // Compress data
        std::vector<unsigned char> compressedData = compress(inputData);

        // Write compressed data to file
        std::ofstream compressedFile(compressedFilename, std::ios::binary);
        if (!compressedFile) {
            throw std::runtime_error("Error opening compressed file: " + compressedFilename);
        }
        compressedFile.write(reinterpret_cast<const char*>(compressedData.data()), compressedData.size());
        compressedFile.close();

        // Decompress data
        std::vector<unsigned char> decompressedData = decompress(compressedData);

        // Write decompressed data to file
        std::ofstream decompressedFile(decompressedFilename, std::ios::binary);
        if (!decompressedFile) {
            throw std::runtime_error("Error opening decompressed file: " + decompressedFilename);
        }
        decompressedFile.write(reinterpret_cast<const char*>(decompressedData.data()), decompressedData.size());
        decompressedFile.close();

        // Calculate compression ratio
        double compressionRatio = 1.0 - (static_cast<double>(compressedData.size()) / inputData.size());
        std::cout << "Compression complete." << std::endl;
        std::cout << "Original size: " << inputData.size() << " bytes" << std::endl;
        std::cout << "Compressed size: " << compressedData.size() << " bytes" << std::endl;
        std::cout << "Compression ratio: " << compressionRatio * 100 << "%" << std::endl;

        // Check file integrity
        if (filesAreEqual(inputFilename, decompressedFilename)) {
            std::cout << "File integrity check passed." << std::endl;
        } else {
            std::cerr << "Warning: Decompressed file does not match the original file." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}