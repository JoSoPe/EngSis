#!/usr/bin/python
# -*- coding: utf-8 -*-
import sqlite3 as lite
import sys


def read_txt():
 #
    con=lite.connect('lecturasensor.db')
    with con:    
        cur = con.cursor()
        cur.executescript("""
        DROP TABLE IF EXISTS lectures;
        CREATE TABLE lectures(
        rowid integer primary key,
        eixX real(5),
        eixY real(5),
        eixZ real(5)
        );
        """)
        con.commit()
        #
    f = open("sensor.txt","r")
    info = f.readlines()
    read = [x.strip() for x in info]
    t = []
    for sample in read:
        t.append(tuple(sample.split(" , ")))
    data = list(t)
    action = "INSERT INTO lectures(eixX,eixY,eixZ) VALUES (?,?,?)"
    con = lite.connect('lecturasensor.db')
    with con:
        cur = con.cursor()
        cur.executemany("INSERT INTO lectures(eixX,eixY,eixZ) VALUES (?,?,?)",data)
        con.commit()
    con.close()
    f.close()

def txt2database():
    con=lite.connect('lecturasensor.db')
    with con:
        cur = con.cursor()
        cur.executescript("""
        DROP TABLE IF EXISTS lectures;
        CREATE TABLE lectures(
        rowid integer primary key,
        eixX real(5),
        eixY real(5),
        eixZ real(5)
        );
        """)
        con.commit()
        read_txt()

    con.close()

def main():
    print ("main")
    #txt2database()
    read_txt()

main()
