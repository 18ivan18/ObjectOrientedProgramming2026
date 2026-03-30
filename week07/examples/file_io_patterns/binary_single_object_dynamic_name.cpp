#include "RecordDynamic.h"
#include "binary_io_dynamic_name.h"
#include <fstream>
#include <iostream>

int main() {
    RecordDynamic r(100, 9.99, "BinaryDynamic");

    std::ofstream out("one_record_dynname.dat", std::ios::binary);
    if (!out.is_open()) {
        return 1;
    }
    if (!writeRecordBinary(out, r)) {
        return 1;
    }
    out.close();

    RecordDynamic inRec;
    std::ifstream inf("one_record_dynname.dat", std::ios::binary);
    if (!inf.is_open()) {
        return 1;
    }
    if (!readRecordBinary(inf, inRec)) {
        return 1;
    }

    std::cout << inRec.getId() << ' ' << inRec.getScore() << ' ' << inRec.getName() << '\n';
    return 0;
}
