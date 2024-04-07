#include <iostream>
#include <fstream>
#include <map>
#include <string>

struct Book {
    std::string id;
    std::string author;
    std::string title;
    int pages;
};

std::ostream& operator<<(std::ostream& os, const Book& book) {
    os << book.id << std::endl;
    os << book.author << std::endl;
    os << book.title << std::endl;
    os << book.pages << std::endl;
    return os;
}

std::istream& operator>>(std::istream& is, Book& book) {
    std::getline(is, book.id);
    std::getline(is, book.author);
    std::getline(is, book.title);
    is >> book.pages;
    return is;
}

void writeBooksToFile(const std::string& filename, const std::map<std::string, Book>& books) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    for (const auto& entry : books) {
        file << entry.second << std::endl;
    }

    file.close();
}

std::map<std::string, Book> readBooksFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }

    std::map<std::string, Book> books;
    Book book;
    while (file >> book) {
        books[book.id] = book;
    }

    file.close();
    return books;
}

void addBook(std::map<std::string, Book>& books, const Book& book) {
    books[book.id] = book;
}

void viewBooks(const std::map<std::string, Book>& books) {
    for (const auto& entry : books) {
        std::cout << entry.second << std::endl;
    }
}

void deleteBook(std::map<std::string, Book>& books, const std::string& id) {
    books.erase(id);
}

Book findBook(const std::map<std::string, Book>& books, const std::string& id) {
    auto it = books.find(id);
    if (it != books.end()) {
        return it->second;
    }
    return {};
}

void editBook(std::map<std::string, Book>& books, const std::string& id, const Book& newBook) {
    books[id] = newBook;
}

int main() {
    std::map<std::string, Book> books = {
        {
            "0001", {
                "0001",
                "A.S.Pushkin",
                "Dubrovsky",
                142
            }
        },
        {
            "0002", {
                "0002",
                "Y.Gibson",
                "Neuromancer",
                347
            }
        }
    };

    std::string filename = "books.txt";
    writeBooksToFile(filename, books);

    std::map<std::string, Book> readBooks = readBooksFromFile(filename);
    if (!readBooks.empty()) {
        std::cout << "Read books from file:" << std::endl;
        viewBooks(readBooks);
    }

    // Example usage
    addBook(books, {
        "0003",
        "J.K.Rowling",
        "Harry Potter and the Philosopher's Stone",
223
        });

    viewBooks(books);

    Book book = findBook(books, "0002");
    if (!book.id.empty()) {
        std::cout << "Found book: " << book.title << std::endl;
    }

    deleteBook(books, "0001");
    std::cout << "Deleted book with ID 0001" << std::endl;

    editBook(books, "0003", {
        "0003",
        "J.K.Rowling",
        "Harry Potter and the Chamber of Secrets",
        251
        });
    std::cout << "Edited book with ID 0003" << std::endl;

    viewBooks(books);

    return 0;
}