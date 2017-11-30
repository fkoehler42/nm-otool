# NM-OTOOL

Nm and Otool are two UNIX executables which display informations about the content of a binary file.

This implementation handles the most commons architectures (x86_64, i386, PowerPC...).

## Usage

```
./ft_nm [-pruUj] [file ...]

-p : don't sort symbols (table order)
-r : sort in reverse order
-u : display only undefined symbols (name only)
-U : don't display undefined symbols
-j : display the symbol name only (no value or type)
```

```
./ft_otool [-d] [file ...]

Default behaviour corresponds to the -t option of otool (display text section)
-d : display the data section
```
