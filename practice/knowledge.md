## Usefull notes

- At the eof fread return less readed element then required

- For output streams, `fflush()` forces a write of all user-space buffered data for the given output or update stream via the stream's underlying write function. For input streams associated with seekable files (e.g., disk files, but not pipes or terminals), `fflush()` discards any buffered data that has been fetched from the underlying file, but has not been consumed by the application. The open status of the stream is unaffected. If the stream argument is `NULL`, `fflush()` flushes all open output streams

- `fseek()` doesn't return offset but 0 for success

- Include `sys/stat.h` to use `stat()`

- `strtok()` has internal state

- pw_passwd in struct passwd is x if password is encrypted and located in /etc/shadows

- import \_GNU_SOURCE before including mman header

- do ftruncate BEFORE mapped output file

- use MAP_SHARED flag for mapped output file

- remember to close pipe channels
