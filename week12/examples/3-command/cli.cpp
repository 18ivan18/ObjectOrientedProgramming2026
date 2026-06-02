#include <cstring>
#include <iostream>

// -----------------------------------------------------------------------
// Receiver — the text buffer
// -----------------------------------------------------------------------

class TextEditor
{
    static const int MAX = 256;
    char buf[MAX];
    int len;

public:
    TextEditor() : len(0)
    {
        buf[0] = '\0';
    }

    void insert(int pos, char ch)
    {
        if (pos < 0 || pos > len || len >= MAX - 1)
        {
            std::cout << "Error: invalid position for insert\n";
            return;
        }
        for (int i = len; i > pos; i--)
        {
            buf[i] = buf[i - 1];
        }
        buf[pos] = ch;
        buf[++len] = '\0';
    }

    void remove(int pos)
    {
        if (pos < 0 || pos >= len)
        {
            std::cout << "Error: invalid position for delete\n";
            return;
        }
        for (int i = pos; i < len - 1; i++)
        {
            buf[i] = buf[i + 1];
        }
        buf[--len] = '\0';
    }

    void replace(int pos, char ch)
    {
        if (pos < 0 || pos >= len)
        {
            std::cout << "Error: invalid position for replace\n";
            return;
        }
        buf[pos] = ch;
    }

    char charAt(int pos) const
    {
        return buf[pos];
    }
    const char *content() const
    {
        return buf;
    }
    int length() const
    {
        return len;
    }
};

// -----------------------------------------------------------------------
// Command interface
// -----------------------------------------------------------------------

class Command
{
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual ~Command()
    {
    }
};

// -----------------------------------------------------------------------
// Concrete commands
// -----------------------------------------------------------------------

class InsertCommand : public Command
{
    TextEditor &editor;
    int pos;
    char ch;

public:
    InsertCommand(TextEditor &e, int pos, char ch) : editor(e), pos(pos), ch(ch)
    {
    }
    void execute()
    {
        editor.insert(pos, ch);
    }
    void undo()
    {
        editor.remove(pos);
    }
};

class DeleteCommand : public Command
{
    TextEditor &editor;
    int pos;
    char saved;

public:
    DeleteCommand(TextEditor &e, int pos) : editor(e), pos(pos), saved('\0')
    {
    }
    void execute()
    {
        saved = editor.charAt(pos);
        editor.remove(pos);
    }
    void undo()
    {
        editor.insert(pos, saved);
    }
};

class ReplaceCommand : public Command
{
    TextEditor &editor;
    int pos;
    char newCh;
    char oldCh;

public:
    ReplaceCommand(TextEditor &e, int pos, char newCh) : editor(e), pos(pos), newCh(newCh), oldCh('\0')
    {
    }
    void execute()
    {
        oldCh = editor.charAt(pos);
        editor.replace(pos, newCh);
    }
    void undo()
    {
        editor.replace(pos, oldCh);
    }
};

// -----------------------------------------------------------------------
// Invoker — undo/redo stack
// -----------------------------------------------------------------------

class CommandHistory
{
    static const int MAX = 256;
    Command *history[MAX];
    int size;
    int current;

public:
    CommandHistory() : size(0), current(-1)
    {
    }

    void execute(Command *cmd)
    {
        for (int i = current + 1; i < size; i++)
        {
            delete history[i];
        }
        size = current + 1;
        cmd->execute();
        history[size++] = cmd;
        current = size - 1;
    }

    void undo()
    {
        if (current < 0)
        {
            std::cout << "(nothing to undo)\n";
            return;
        }
        history[current--]->undo();
    }

    void redo()
    {
        if (current == size - 1)
        {
            std::cout << "(nothing to redo)\n";
            return;
        }
        history[++current]->execute();
    }

    ~CommandHistory()
    {
        for (int i = 0; i < size; i++)
        {
            delete history[i];
        }
    }
};

// -----------------------------------------------------------------------
// CLI loop
// -----------------------------------------------------------------------

int main()
{
    TextEditor editor;
    CommandHistory history;
    char cmd[32];

    std::cout << "Text editor — commands: insert <pos> <char>  |  delete <pos>  |  replace <pos> <char>  |  print  |  "
                 "undo  |  redo  |  quit\n\n";

    while (true)
    {
        std::cout << "> ";
        std::cin >> cmd;

        if (std::strcmp(cmd, "quit") == 0)
        {
            break;
        }
        else if (std::strcmp(cmd, "print") == 0)
        {
            std::cout << "\"" << editor.content() << "\"\n";
        }
        else if (std::strcmp(cmd, "undo") == 0)
        {
            history.undo();
        }
        else if (std::strcmp(cmd, "redo") == 0)
        {
            history.redo();
        }
        else if (std::strcmp(cmd, "insert") == 0)
        {
            int pos;
            char ch;
            std::cin >> pos >> ch;
            history.execute(new InsertCommand(editor, pos, ch));
        }
        else if (std::strcmp(cmd, "delete") == 0)
        {
            int pos;
            std::cin >> pos;
            history.execute(new DeleteCommand(editor, pos));
        }
        else if (std::strcmp(cmd, "replace") == 0)
        {
            int pos;
            char ch;
            std::cin >> pos >> ch;
            history.execute(new ReplaceCommand(editor, pos, ch));
        }
        else
        {
            std::cout << "Unknown command: " << cmd << "\n";
        }
    }
}
