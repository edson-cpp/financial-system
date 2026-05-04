# financial-system
A system to control personal finance and investments.

# Configuration
File config.json.model
    Rename to config.json
    Set the database user and password at line 15 and 16 respectively.
File CMakeLists.txt.model
    Rename to CMakeLists.txt
    Set the pepper password at line 21.
File data/data.sql.model
    Rename to data.sql
    Use argon2_hash.cpp file to generate argon2 hash.
File install.sql.model
    Rename to install.sql
    Set root password
File priv.sql.model
    Rename to priv.sql
    Set username and password