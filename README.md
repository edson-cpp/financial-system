# financial-system
A system to control personal finance and investments.

## Configuration
1. File config.json.model
   ```bash
     Rename to config.json
    Set the database user and password at line 15 and 16 respectively.
    ```
2. File CMakeLists.txt.model
   ```bash
     Rename to CMakeLists.txt
    Set the pepper password at line 21.
    ```
3. File data/data.sql.model
   ```bash
    Rename to data.sql
    Use argon2_hash.cpp file to generate argon2 hash.
    Or use hash_command.cpp to generate argon2 hash using environment variables.
    ```
4. File install.sql.model
   ```bash
    Rename to install.sql
    Set root password
    ```
5. File priv.sql.model
   ```bash
    Rename to priv.sql
    Set username and password
    ```