## Описание параметров командной строки

| Опция            | Описание                                                                                    | Значение по умолчанию |
|------------------|---------------------------------------------------------------------------------------------|-----------------------|
| -h, --help       | Показать справку                                                                            | -                     |
| -d, --dir        | Директории для сканирования                                                                 | -                     |
| -e, --exclude    | Директории для исключения из сканирования                                                   | -                     |
| -l, --level      | Уровень сканирования (один на все директории, 0 - только указанная директория без вложенных | 0                     |
| -m, --min-size   | Минимальный размер файла                                                                    | 1                     |
| --mask           | Маски имен файлов разрешенных для сравнения (значение маски передается в кавычках)          | -                     |
| -s, --block-size | Размер блока, которым производится чтения файлов                                            | 4096                  |
| -H, --hash       | Один из имеющихся алгоритмов хэширования (crc32, md5)                                       | crc32                 |

## Примеры использования

./bayan -d /home/vitaly/repos/otus-cpp/cmake-build-debug-wsl/testDir/subdir1 -l 0

./bayan -d /home/vitaly/repos/otus-cpp/cmake-build-debug-wsl/testDir -e /home/vitaly/repos/otus-cpp/cmake-build-debug-wsl/testDir/subdir1 -l 1

./bayan -d /home/vitaly/repos/otus-cpp/cmake-build-debug-wsl/testDir -l 1 --mask "test*.txt"

./bayan -d /home/vitaly/repos/otus-cpp/cmake-build-debug-wsl/testDir -l 1 --mask "*.log" --mask "test*.txt"
