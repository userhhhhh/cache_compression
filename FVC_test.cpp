#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

// 统计频率
unordered_map<int, int> countFrequency(const vector<int>& data) {
    unordered_map<int, int> frequency_map;
    for (int item : data) {
        frequency_map[item]++;
    }
    return frequency_map;
}

// 压缩数据
vector<string> compressData(const vector<int>& data, const unordered_map<int, string>& compression_map) {
    vector<string> compressed_data;
    for (int item : data) {
        // 查找频繁值的替代标识符
        if (compression_map.find(item) != compression_map.end()) {
            compressed_data.push_back(compression_map.at(item)); // 如果是频繁值，替换为标识符
        } else {
            compressed_data.push_back(to_string(item)); // 否则保持原样
        }
    }
    return compressed_data;
}

// 解压数据
vector<int> decompressData(const vector<string>& compressed_data, const unordered_map<string, int>& reverse_compression_map) {
    vector<int> decompressed_data;
    for (const string& item : compressed_data) {
        // 查找标识符对应的原始值
        if (reverse_compression_map.find(item) != reverse_compression_map.end()) {
            decompressed_data.push_back(reverse_compression_map.at(item));
        } else {
            decompressed_data.push_back(stoi(item)); // 对于不频繁的值，转回原始数字
        }
    }
    return decompressed_data;
}

int main() {
    // 输入数据
    vector<int> data = {5, 2, 3, 5, 5, 2, 8, 3, 5, 7, 5, 2};

    // 第一步：统计频率
    unordered_map<int, int> frequency_map = countFrequency(data);

    // 设置阈值为 3，识别频繁值
    unordered_map<int, string> compression_map;
    unordered_map<string, int> reverse_compression_map; // 用于解压

    int threshold = 3; // 频繁值阈值
    char label = 'A';   // 用字母表示压缩标识符

    for (const auto& entry : frequency_map) {
        if (entry.second >= threshold) {
            // 如果频率大于等于阈值，压缩为标识符
            compression_map[entry.first] = string(1, label); // 将数字映射为字符
            reverse_compression_map[string(1, label)] = entry.first;
            label++; // 增加标识符（A -> B -> C -> ...）
        }
    }

    // 第二步：压缩数据
    vector<string> compressed_data = compressData(data, compression_map);

    cout << "Compressed Data: ";
    for (const string& item : compressed_data) {
        cout << item << " ";
    }
    cout << endl;

    cout << "Dictionary: ";
    for (const auto& entry : compression_map) {
        cout << entry.first << "->" << entry.second << " ";
    }
    cout << endl;

    // 第三步：解压数据
    vector<int> decompressed_data = decompressData(compressed_data, reverse_compression_map);

    cout << "Decompressed Data: ";
    for (int item : decompressed_data) {
        cout << item << " ";
    }
    cout << endl;

    return 0;
}