#include <iostream>
#include "Document.h"
#include "KeyValueDatabase.h"

int main() {
    // --- Document: readLine cursor behaviour (from task description) ---
    Document temp("temp", "/tmp", "doc");
    temp.writeLine("This is an example doc");
    temp.writeLine("This is another example line");
    temp.writeLine("This is a third example line");
    temp.writeLine("This is a forth example line");

    std::cout << temp.readLine()  << "\n"; // line 1
    std::cout << temp.readLine()  << "\n"; // line 2
    std::cout << temp.readLine(3) << "\n"; // line 3, cursor -> 4
    std::cout << temp.readLine()  << "\n"; // line 4
    std::cout << temp.readLine(1) << "\n"; // line 1, cursor -> 2
    std::cout << temp.readLine()  << "\n"; // line 2

    // debug_print
    std::cout << "\ndebug_print:\n" << temp.debug_print();

    // getPath
    std::cout << "path: " << temp.getPath() << "\n"; // /tmp/temp.doc

    // Serialization round-trip
    std::string serialized = temp.toString();
    Document restored("", "", "");
    restored.fromString(serialized);
    std::cout << "restored == original: " << (temp == &restored ? "yes" : "no") << "\n";

    // clone (Prototype pattern)
    Object* cloned = temp.clone();
    std::cout << "clone   == original: " << (temp == cloned ? "yes" : "no") << "\n";
    delete cloned;

    // out_of_range on read past end
    try {
        temp.readLine(99);
    } catch (const std::out_of_range& e) {
        std::cout << "caught: " << e.what() << "\n";
    }

    // Equality: same lines, different metadata
    Document sameLines("other", "/var", "txt");
    sameLines.writeLine("This is an example doc");
    sameLines.writeLine("This is another example line");
    sameLines.writeLine("This is a third example line");
    sameLines.writeLine("This is a forth example line");
    std::cout << "same lines, diff name: " << (temp == &sameLines ? "yes" : "no") << "\n"; // yes

    // --- KeyValueDatabase ---
    std::cout << "\n--- KeyValueDatabase ---\n";
    KeyValueDatabase db("config", "/etc", "kv");
    db.put("host", 8080);
    db.put("timeout", 30);
    db.put("retries", 3);

    std::cout << "host:    " << db.get("host")    << "\n";
    std::cout << "timeout: " << db.get("timeout") << "\n";

    std::cout << "\ndebug_print:\n" << db.debug_print();

    // duplicate key throws
    try {
        db.put("host", 9090);
    } catch (const std::invalid_argument& e) {
        std::cout << "caught: " << e.what() << "\n";
    }

    // missing key throws
    try {
        db.get("missing");
    } catch (const std::invalid_argument& e) {
        std::cout << "caught: " << e.what() << "\n";
    }

    // Serialization round-trip
    KeyValueDatabase restoredDb("", "", "");
    restoredDb.fromString(db.toString());
    std::cout << "restored == original: " << (db == &restoredDb ? "yes" : "no") << "\n";

    // Equality ignores insertion order
    KeyValueDatabase db2("other", "/tmp", "kv");
    db2.put("retries", 3);
    db2.put("host", 8080);
    db2.put("timeout", 30);
    std::cout << "diff order == same:   " << (db == &db2 ? "yes" : "no") << "\n"; // yes

    // clone
    Object* dbClone = db.clone();
    std::cout << "db clone == original: " << (db == dbClone ? "yes" : "no") << "\n";
    delete dbClone;
}
