#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>

struct MNISTImage {
    std::vector<int> pixels;
    int label;
};

struct MNISTHeader {
    uint32_t magic_number;
    uint32_t num_items;
    uint32_t num_rows;
    uint32_t num_cols;
};

std::vector<MNISTImage> load_mnist(const std::string& image_file, const std::string& label_file) {
    std::ifstream image_stream(image_file, std::ios::binary);
    std::ifstream label_stream(label_file, std::ios::binary);

    if (!image_stream.is_open() || !label_stream.is_open()) {
        std::cerr << "Error opening files." << std::endl;
        exit(1);
    }

    MNISTHeader image_header, label_header;
    image_stream.read(reinterpret_cast<char*>(&image_header), sizeof(image_header));
    label_stream.read(reinterpret_cast<char*>(&label_header), sizeof(label_header));

    if (image_header.num_items != label_header.num_items) {
        std::cerr << "Image and label counts mismatch." << std::endl;
        exit(1);
    }

    std::vector<MNISTImage> dataset;
    dataset.reserve(image_header.num_items);

    for (int i = 0; i < image_header.num_items; ++i) {
        MNISTImage image;
        image.pixels.resize(image_header.num_rows * image_header.num_cols);
        image_stream.read(reinterpret_cast<char*>(image.pixels.data()), image.pixels.size());
        label_stream.read(reinterpret_cast<char*>(&image.label), sizeof(image.label));
        dataset.push_back(image);
    }

    return dataset;
}