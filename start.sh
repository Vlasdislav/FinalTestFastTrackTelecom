if [ "$#" -ne 1 ]; then
    echo "Для компиляции и запуска программы нужно передать название одного файла"
    exit 1
fi

program_name="$1"

g++ "$program_name.cpp" -o "$program_name.out"; "./$program_name.out"
