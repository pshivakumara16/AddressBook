# AddressBook in C

A command-line Address Book application built in C as part of the Advanced C module at Emertxe Information Technologies, Bengaluru.

## Project Structure

AddressBook/
├── main.c       # Entry point, menu-driven interface
├── contact.c    # Core logic — create, search, edit, delete, validate
├── contact.h    # Structs, macros, function declarations
├── file.c       # File I/O — save and load contacts
├── file.h       # File function declarations
└── README.md

## Features

- ✅ Create contact with input validation
- ✅ Search contact by name, phone, or email
- ✅ Edit existing contact
- ✅ Delete contact
- ✅ List all contacts
- ✅ Save contacts to file and load on startup
- ✅ Handles up to 100 contacts

## Input Validations

**Name:**
- Only alphabets and spaces allowed
- Minimum 4 characters required

**Phone:**
- Must be exactly 10 digits
- First digit must be between 6 and 9
- No alphabets or symbols allowed
- Specific error message for each invalid case

**Email:**
- Must contain exactly one @ symbol
- Dot must appear after @
- At least one character between @ and dot
- No extra characters after domain
- Only @ and . allowed as symbols
- Specific error message for each invalid case

## How to Build

```bash
gcc -Wall -o addressbook main.c contact.c file.c
```

## How to Run

```bash
./addressbook
```

## Menu Options

1.Create contact
2.Search contact
3.Edit contact
4.Delete contact
5.List all contacts
6.Save and Exit
## Bugs Fixed During Development

| Bug | Effect | Fix |
|---|---|---|
| Delete loop out of bounds | Segfault on last contact | Changed `i < count` to `i < count - 1` |
| `fscanf %s` on names with spaces | Corrupted all contacts on load | Replaced with `fgets` + `strcspn` |
| Space not allowed in names | Names like "Ravi Kumar" rejected | Added `name[i] == ' '` condition |
| Error on first run | Confusing error when no file exists | Changed to silent return |
| No bounds check on loaded count | Array overflow on corrupted file | Added guard after `fscanf` |
| Wrong error messages in edit | Confusing user messages | Fixed all 3 case messages |
| Missing return in `validate_Email` | Undefined behavior | Added `return 0` at end |

## Key Learnings

- `fscanf %s` vs `fgets` — critical difference for strings with spaces
- Always compile with `-Wall` to catch warnings early
- `strcspn` for stripping newlines after `fgets`
- Modular code structure — same pattern used in embedded systems
- Importance of input validation and error messages

## Author

P Shivakumara  
Electronics and Communication Engineering  
Emertxe Information Technologies, Bengaluru  
GitHub: [pshivakumara16](https://github.com/pshivakumara16)
