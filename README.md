# financial-system
A system to control personal finance and investments.

## Configuration
1. Create env file
   ```bash
   vim /etc/financial-system.env

   Protect The File:
   sudo chmod 600 /etc/financial-system.env
   sudo chown root:root /etc/financial-system.env

   Put this:
   PASSWORD_PEPPER=your_password
   DB_PASSWORD=your_password

   Restart Service:
   sudo systemctl daemon-reload
   sudo systemctl restart financial-system
   ```
2. File data/data.example.sql
   ```bash
   Rename to data.sql
   Use argon2_hash.cpp file to generate argon2 hash.
   Or use hash_cmd.cpp to generate argon2 hash using environment variables.
   ```
3. File install.example.sql
   ```bash
   Rename to install.sql
   Set root password
   ```
4. File priv.example.sql
   ```bash
   Rename to priv.sql
   Set username and password
   ```