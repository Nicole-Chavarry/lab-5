#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

int countWordOccurrencesInFile(const std::string& filename, const std::string& targetWord) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return -1;
    }

    std::string word;
    int count = 0;
    while (file >> word) {
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);

        if (word == targetWord) {
            count++;
        }
    }

    file.close();
    return count;
}

int main() {
    std::string filename = "texto.txt";
    std::string targetWord;
    std::cout << "Enter the word to search for: ";
    std::cin >> targetWord;

    int occurrences = countWordOccurrencesInFile(filename, targetWord);
    if (occurrences >= 0) {
        std::cout << "Number of occurrences of '" << targetWord << "': " << occurrences << std::endl;
    }

    return 0;
}
