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
    read = f.readlines()
    read2 = [x.strip() for x in read]
    t = []
    for element in read2:
        t.append(tuple(element.split(" , ")))
    t2 = list(t)
    data = "INSERT INTO lectures(eixX,eixY,eixZ) VALUES (?,?,?)"
    con = lite.connect('lecturasensor.db')
    with con:
        cur = con.cursor()
        cur.executemany(data,t2)
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
        eixX float(5),
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
