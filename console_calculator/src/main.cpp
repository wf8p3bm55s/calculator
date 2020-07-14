#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <limits>
#include <filesystem>

extern "C" {
#include "calclib.h"
}

#define isWin() defined(WIN32) || defined(_WIN32) || defined(__WIN32)

#if isWin()
#include <windows.h>
#endif

static const std::string OUTPUT_FILE_PATH = "./output.json";

CalcArg parseCalcArg(const std::string &str)
{
    char *end;
    CalcArg result = strtold(str.c_str(), &end);

    if (errno == ERANGE) {
        errno = 0;
        throw std::invalid_argument(
            "Аргумент " + str + " превышает допустимое значение.");
    }

    if (str == end || std::isnan(result) || std::isinf(result)) {
        throw std::invalid_argument("Аргумент " + str + " не число.");
    }

    return result;
}

SimpleOperation parseOperation(const std::string &str)
{
    if (str.compare("+") == 0) {
        return calcSum;
    }

    if (str.compare("-") == 0) {
        return calcSub;
    }

    if (str.compare("*") == 0) {
        return calcMul;
    }

    if (str.compare("/") == 0) {
        return calcDiv;
    }

    throw std::invalid_argument(
        "Аргумент " + str + " не является поддерживаемой операцией.");
}

// Размер файла ограничен unsigned long байт
void writeOperationResultToAsciiJsonFile(CalcArg result, const std::string &filePath)
{
    std::fstream fioFile;

    if (std::filesystem::exists(filePath)) {
        fioFile.open(filePath, std::ios::in | std::ios::out | std::ios::binary);
    } else {
        fioFile.open(filePath, std::ios::in | std::ios::out | std::ios::trunc | std::ios::binary);
    }

    if (!fioFile.is_open()) {
        throw std::ios_base::failure("Ошибка открытия файла.");
    }

    const short BUFF_SIZE = 128;
    fioFile.seekg(0, fioFile.end);

    if (fioFile.bad() || fioFile.fail()) {
        throw std::ios_base::failure("Ошибка задания позиции в файле.");
    }

    long unreadBytesCount = fioFile.tellg();

    if (unreadBytesCount == -1) {
        throw std::ios_base::failure("Ошибка получения размера файла.");
    }

    unsigned long positionToWrite = 0;

    while (unreadBytesCount != 0) {
        char buffer[BUFF_SIZE] = {0};
        short readSize = unreadBytesCount < BUFF_SIZE ? unreadBytesCount : BUFF_SIZE;

        fioFile.seekg(unreadBytesCount - readSize, fioFile.beg);

        if (fioFile.bad() || fioFile.fail()) {
            throw std::ios_base::failure("Ошибка задания позиции в файле.");
        }

        fioFile.read(buffer, readSize);
        std::cout << unreadBytesCount << std::endl;

        if (fioFile.bad() || fioFile.fail()) {
            throw std::ios_base::failure("Ошибка чтения файла.");
        }

        unreadBytesCount -= readSize;

        for (short i = readSize - 1; i >= 0; i--) {
            if (buffer[i] == '}') {
                positionToWrite = unreadBytesCount + i;
                goto loopExit;
            }
        }
    }

loopExit:

    fioFile.seekg(positionToWrite == 0 ? 0 : positionToWrite - 1, fioFile.beg);

    if (fioFile.bad() || fioFile.fail()) {
        throw std::ios_base::failure("Ошибка задания позиции в файле.");
    }

    if (positionToWrite == 0) {
        fioFile << "{ result: ";
    } else {
        fioFile << ", result: ";
    }

    fioFile.precision(std::numeric_limits<CalcArg>::digits10);
    fioFile << result << " }";

    if (fioFile.bad()) {
        throw std::ios_base::failure("Ошибка записи в файл.");
    }

    fioFile.close();

    if (fioFile.bad()) {
        throw std::ios_base::failure("Ошибка закрытия файла.");
    }

    std::streamsize ss = std::cout.precision();
    std::cout.precision(std::numeric_limits<CalcArg>::digits10);
    std::cout << "Результат: "
              << result << " успешно записан в файл " << filePath << std::endl;
    std::cout.precision(ss);
}

void takeConsoleInput(std::string (&args)[3])
{
    short i = 0;
    size_t last = 0;
    size_t next = 0;
    std::string input;

    std::cout << "Пожалуйста введите простейшее выражение." << std::endl;
    std::getline(std::cin, input);

    while (((next = input.find(" ", last)) != std::string::npos) && i < 3) {
        args[i++] = input.substr(last, next - last);
        last = next + 1;
    }

    if (i == 2) {
        args[i++] = input.substr(last);
        return;
    }

    throw std::invalid_argument("Передано некорректное выражение.");
}

int main(int argc, char *argv[])
{
#if isWin()
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
#endif

    try {
        std::string args[3];

        if (argc == 1) {
            takeConsoleInput(args);
        } else if (argc == 4) {
            args[0] = argv[1];
            args[1] = argv[2];
            args[2] = argv[3];
        } else {
            throw std::invalid_argument(
                "Количество переданных аргументов не равно 0 или 3.");
        }

        CalcArg a = parseCalcArg(args[0]);
        CalcArg b = parseCalcArg(args[2]);
        CalcArg result = parseOperation(args[1])(a, b);
        writeOperationResultToAsciiJsonFile(result, OUTPUT_FILE_PATH);
    } catch (const std::exception &e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        exit(1);
    }

    return 0;
}
