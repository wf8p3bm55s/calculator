cmake_minimum_required(VERSION 3.16)

project(Calculator)

add_subdirectory(calclib)
add_subdirectory(console_calculator)
add_subdirectory(qml_calculator)

install(TARGETS Calclib CalclibStatic
    LIBRARY DESTINATION "Calclib/lib"
    ARCHIVE DESTINATION "Calclib/lib"
    RUNTIME DESTINATION "Calclib/bin"
    INCLUDES DESTINATION "Calclib/include"
)

install(TARGETS ConsoleCalculator
    LIBRARY DESTINATION "ConsoleCalculator/lib"
    ARCHIVE DESTINATION "ConsoleCalculator/lib"
    RUNTIME DESTINATION "ConsoleCalculator/bin"
    INCLUDES DESTINATION "ConsoleCalculator/include"
)

install(TARGETS QmlCalculator
    LIBRARY DESTINATION "QmlCalculator/lib"
    ARCHIVE DESTINATION "QmlCalculator/lib"
    RUNTIME DESTINATION "QmlCalculator/bin"
    INCLUDES DESTINATION "QmlCalculator/include"
)

enable_testing()

add_test(NAME 1 COMMAND ConsoleCalculator 4 + 4)
set_tests_properties(1 PROPERTIES
    PASS_REGULAR_EXPRESSION "Результат: 8 успешно записан в файл ./output.json")

add_test(NAME 2 COMMAND ConsoleCalculator "  1")
set_tests_properties(2 PROPERTIES
    PASS_REGULAR_EXPRESSION "Ошибка: Количество переданных аргументов не равно 0 или 3.")

add_test(NAME 3 COMMAND ConsoleCalculator 44444444444444.1111111111111 + 4)
set_tests_properties(3 PROPERTIES
    PASS_REGULAR_EXPRESSION "Результат: 44444444444448.1111 успешно записан в файл ./output.json")

add_test(NAME 4 COMMAND ConsoleCalculator 1e1 + 4)
set_tests_properties(4 PROPERTIES
    PASS_REGULAR_EXPRESSION "Результат: 14 успешно записан в файл ./output.json")

add_test(NAME 5 COMMAND ConsoleCalculator 1e1 + nan)
set_tests_properties(5 PROPERTIES
    PASS_REGULAR_EXPRESSION "Аргумент nan не число.")

set_tests_properties(1 2 3 4 5 PROPERTIES
    TIMEOUT 10)
    