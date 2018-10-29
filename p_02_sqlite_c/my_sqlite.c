#include "sqlite3.h"
#include <stdio.h>

int callback(void *, int, char **, char **);

int main(int argc, char ** argv) {
    // Example URL : http://zetcode.com/db/sqlitec/

    // Example 01
    // The sqlite3_libversion() function returns a string indicating the SQLite library.    
    printf("sqlite3 version : %s\n", sqlite3_libversion()); 
    // -- Example 01

    sqlite3 *db;
    char *err_msg = 0;
    sqlite3_stmt *res;
    
    //const char * db_name = ":memory:" ;
    const char * db_name = "test.db" ;

    int rc = sqlite3_open( db_name, &db);
    
    if (rc != SQLITE_OK) {        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return 1;
    }

    // Example 02
    // In the second example, we again get the version of the SQLite database. 
    // This time we will use an SQL query.
    rc = sqlite3_prepare_v2(db, "SELECT SQLITE_VERSION()", -1, &res, 0);    
    
    if (rc != SQLITE_OK) {        
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return 1;
    }    
    
    rc = sqlite3_step(res);
    
    if (rc == SQLITE_ROW) {
        printf("sqlite3 version : %s\n", sqlite3_column_text(res, 0));
    }
    // -- Example 02

    // Example 03

    if ( 1 ) {
        const char *sql = "DROP TABLE IF EXISTS Cars;" 
                    "CREATE TABLE Cars(Id INT, Name TEXT, Price INT);" 
                    "INSERT INTO Cars VALUES(1, 'Audi', 52642);" 
                    "INSERT INTO Cars VALUES(2, 'Mercedes', 57127);" 
                    "INSERT INTO Cars VALUES(3, 'Skoda', 9000);" 
                    "INSERT INTO Cars VALUES(4, 'Volvo', 29000);" 
                    "INSERT INTO Cars VALUES(5, 'Bentley', 350000);" 
                    "INSERT INTO Cars VALUES(6, 'Citroen', 21000);" 
                    "INSERT INTO Cars VALUES(7, 'Hummer', 41400);" 
                    "INSERT INTO Cars VALUES(8, 'Volkswagen', 21600);";

        rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
        
        if (rc != SQLITE_OK ) {            
            fprintf(stderr, "SQL error: %s\n", err_msg);
            
            sqlite3_free(err_msg);        
            sqlite3_close(db);
            
            return 1;
        }else {
            fprintf(stdout, "Table Cars created successfully\n");
        } 
    }

    // -- Example 03

    // Example 04
    // Sometimes, we need to determine the id of the last inserted row.
    // For this, we have the sqlite3_last_insert_rowid() function.

    if( 1 ) {
        const char *sql = "CREATE TABLE Friends(Id INTEGER PRIMARY KEY, Name TEXT);"
        "INSERT INTO Friends(Name) VALUES ('Tom');"
        "INSERT INTO Friends(Name) VALUES ('Rebecca');"
        "INSERT INTO Friends(Name) VALUES ('Jim');"
        "INSERT INTO Friends(Name) VALUES ('Roger');"
        "INSERT INTO Friends(Name) VALUES ('Robert');";            
        
        rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
        
        if (rc != SQLITE_OK ) {
            fprintf(stderr, "Failed to create table\n");
            fprintf(stderr, "SQL error: %s\n", err_msg);
            sqlite3_free(err_msg);            
        } else {
            fprintf(stdout, "Table Friends created successfully\n");
        }        
        
        int last_id = sqlite3_last_insert_rowid(db);
        printf("The last Id of the inserted row is %d\n", last_id);
    }

    // -- Example 04

    // Example 05
    // In the following example, we retrieve the data from the database.

    if( 1 ) {
        char *sql = "SELECT * FROM Cars";
        
        rc = sqlite3_exec(db, sql, callback, 0, &err_msg);
        
        if (rc != SQLITE_OK ) {            
            fprintf(stderr, "Failed to select data\n");
            fprintf(stderr, "SQL error: %s\n", err_msg);

            sqlite3_free(err_msg);
            sqlite3_close(db);
            
            return 1;
        } 
    }

    // -- Example 05

    // Example 06
    // Parameterized queries, also called prepared statements, increase security and performance.
    // When we use parameterized queries, 
    // we use placeholders instead of directly writing the values into the statements.

    if( 1 ) {
        fprintf( stdout, "SELECT Id, Name FROM Cars WHERE Id = ?\n" );

        const char *sql = "SELECT Id, Name FROM Cars WHERE Id = ?";
        
        rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
        
        if (rc == SQLITE_OK) {            
            sqlite3_bind_int(res, 1, 3);
        } else {            
            fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
        }
        
        int step = sqlite3_step(res);
        
        if (step == SQLITE_ROW) {            
            printf("%s: ", sqlite3_column_text(res, 0));
            printf("%s\n", sqlite3_column_text(res, 1));
        } 
    }
    // -- Example 06

    // Example 07
    // This example uses parameterized statements with named placeholders.

    if( 1 ) {
        fprintf( stdout, "\nSELECT Id, Name FROM Cars WHERE Id = @id\n" );
        const char *sql = "SELECT Id, Name FROM Cars WHERE Id = @id";
        
        rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
        
        if (rc == SQLITE_OK) {
            int idx = sqlite3_bind_parameter_index(res, "@id");
            int value = 4;
            sqlite3_bind_int(res, idx, value);
        } else {
            fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
        }
        
        int step = sqlite3_step(res);
        
        if (step == SQLITE_ROW) {
            printf("%s: ", sqlite3_column_text(res, 0));
            printf("%s\n", sqlite3_column_text(res, 1));            
        } 
    }

    // -- Example 07

    // Example 08
    // For this example, we create a new table called Images. 
    // For the images, we use the BLOB data type, which stands for Binary Large Objects.

    if( 1 ) {
        // create images table
        if( 1 ) {
            const char *sql = "CREATE TABLE Images(Id INTEGER PRIMARY KEY, Data BLOB);" ;

            rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
            
            if (rc != SQLITE_OK ) {            
                fprintf(stderr, "SQL error: %s\n", err_msg);
                
                sqlite3_free(err_msg);    
            }else {
                fprintf(stdout, "Table Images created successfully\n");
            } 
        }

        FILE *fp = fopen("woman.jpg", "rb");
    
        if (fp == NULL) {            
            fprintf(stderr, "Cannot open image file\n");    
            
            return 1;
        }
            
        fseek(fp, 0, SEEK_END);
        
        if (ferror(fp)) {            
            fprintf(stderr, "fseek() failed\n");
            int r = fclose(fp);

            if (r == EOF) {
                fprintf(stderr, "Cannot close file handler\n");          
            }    
            
            return 1;
        }  
        
        int flen = ftell(fp);
        
        if (flen == -1) {            
            perror("error occurred");
            int r = fclose(fp);

            if (r == EOF) {
                fprintf(stderr, "Cannot close file handler\n");
            }
            
            return 1;     
        }
        
        fseek(fp, 0, SEEK_SET);
        
        if (ferror(fp)) {
            
            fprintf(stderr, "fseek() failed\n");
            int r = fclose(fp);

            if (r == EOF) {
                fprintf(stderr, "Cannot close file handler\n");
            }    
            
            return 1;
        }

        char data[flen+1];
        int size = fread(data, 1, flen, fp);
        
        if (ferror(fp)) {            
            fprintf(stderr, "fread() failed\n");
            int r = fclose(fp);

            if (r == EOF) {
                fprintf(stderr, "Cannot close file handler\n");
            }
            
            return 1;     
        }
        
        int r = fclose(fp);

        if (r == EOF) {
            fprintf(stderr, "Cannot close file handler\n");
        }

        sqlite3_stmt *pStmt;

        const char *sql = "INSERT INTO Images(Data) VALUES(?)";
        
        rc = sqlite3_prepare(db, sql, -1, &pStmt, 0);
        
        if (rc != SQLITE_OK) {            
            fprintf(stderr, "Cannot prepare statement: %s\n", sqlite3_errmsg(db));
            
            return 1;
        }
        
        sqlite3_bind_blob(pStmt, 1, data, size, SQLITE_STATIC);    
        
        rc = sqlite3_step(pStmt);
        
        if (rc != SQLITE_DONE) {            
            printf("execution failed: %s", sqlite3_errmsg(db));
        } else {
            fprintf( stdout, "\nAn image is inserted.\n" );
        }
            
        sqlite3_finalize(pStmt);

    }

    // -- Example 08
    
    // Example 09
    // We will read an image from the database table.

    if( 1 ) {
        FILE *fp = fopen("woman2.jpg", "wb");
    
        if (fp == NULL) {            
            fprintf(stderr, "Cannot open image file\n");    
            
            return 1;
        }

        const char *sql = "SELECT Data FROM Images WHERE Id = 1";
        
        sqlite3_stmt *pStmt;
        rc = sqlite3_prepare_v2(db, sql, -1, &pStmt, 0);
        
        if (rc != SQLITE_OK ) {            
            fprintf(stderr, "Failed to prepare statement\n");
            fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
            
            sqlite3_close(db);
            
            return 1;
        } 
        
        rc = sqlite3_step(pStmt);
        
        int bytes = 0;
        
        if (rc == SQLITE_ROW) {
            bytes = sqlite3_column_bytes(pStmt, 0);
        }
            
        fwrite(sqlite3_column_blob(pStmt, 0), bytes, 1, fp);

        if (ferror(fp)) {
            fprintf(stderr, "fwrite() failed\n");

            return 1;      
        } else {
            fprintf( stdout, "An image has been retrieved.\n" );
        } 
        
        int r = fclose(fp);

        if (r == EOF) {
            fprintf(stderr, "Cannot close file handler\n");
        }       
        
        rc = sqlite3_finalize(pStmt);  
    }

    // -- Example 09
    
    sqlite3_finalize(res);
    sqlite3_close(db);
    
    return 0;
}

int callback(void *NotUsed, int argc, char **argv, char **azColName) {    
    NotUsed = 0;
    
    for (int i = 0; i < argc; i++) {

        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    
    printf("\n");
    
    return 0;
}

// -- 