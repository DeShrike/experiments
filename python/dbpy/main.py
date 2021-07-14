import sqlite3
from sqlite3 import Error
import time
import os

database_file = os.path.join(os.path.dirname(__file__), "primes.db")
primes_file = os.path.join(os.path.dirname(__file__), "primes-1000000.txt")

create_table_primes = """
    CREATE TABLE IF NOT EXISTS primes (
        primeid INTEGER PRIMARY KEY AUTOINCREMENT,
        prime INTEGER NOT NULL UNIQUE
    );
"""

create_table_gaps = """
    CREATE TABLE IF NOT EXISTS gaps (
        gapid INTEGER PRIMARY KEY AUTOINCREMENT,
        prime1 INTEGER NOT NULL,
        prime2 INTEGER NOT NULL,
        gap INTEGER NOT NULL
    );
"""

"""
    FOREIGN KEY (primeid1)
        REFRENCES primes (primeid)
        ON DELETE NO ACTION
        ON UPDATE NO ACTION,
    FOREIGN KEY (primeid2)
        REFRENCES primes (primeid)
        ON DELETE NO ACTION
        ON UPDATE NO ACTION
"""

def execute(conn, sql):
    try:
        cur = conn.cursor()
        cur.execute(sql)
        cur.close()
    except Error as e:
        print(e)

def show_version(conn):
    cur = conn.cursor()
    cur.execute("select sqlite_version();")
    record = cur.fetchone()
    print("SQLite Database Version is: ", record[0])
    cur.close()

def insert_primes(conn):
    cur = conn.cursor()

    cur.execute("SELECT COUNT(*) FROM primes;")
    cur_result = cur.fetchone()
    count = cur_result[0]

    if count > 0:
        return

    lastprime = None
    with open(primes_file, "r") as fo:
        for line in fo:
            primeline = line.strip().split("\t")
            prime = int(primeline[1])
            cur.execute("INSERT INTO primes (prime) VALUES (?);", (prime, ))
            if lastprime is not None:
                cur.execute("INSERT INTO gaps (prime1, prime2, gap) VALUES (?, ?, ?);", (lastprime, prime, prime - lastprime))
            lastprime = prime
    cur.close()

def main():
    # ":memory:"
    with sqlite3.connect(database_file) as conn:
        show_version(conn)
        execute(conn, create_table_primes)
        execute(conn, create_table_gaps)
        insert_primes(conn)

        cur = conn.cursor()
        # cur.execute("SELECT * FROM gaps ORDER BY gap DESC, prime1;")
        cur.execute("SELECT gap, count(*) FROM gaps GROUP BY gap ORDER BY gap DESC;")
        record = cur.fetchone()
        while record is not None:
            print(f"{record[0]}\t{record[1]}")
            record = cur.fetchone()
        cur.close()

if __name__ == "__main__":
    main()

