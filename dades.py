#!/usr/bin/python
# -*- coding: utf-8 -*-
import sqlite3 as lite
import sys


def read_txt(m):
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
        eixZ real(5),
        data_type varchar(10)
        );
        """)
        con.commit()
        
        #prova_id integer(50)
    f = open("sensor.txt","r")
    info = f.readlines()
    read = [x.strip() for x in info]
    t = []
    for sample in read:
        t.append(tuple(sample.split(" , ")))
    data = list(t)
    action = "INSERT INTO lectures(eixX,eixY,eixZ,data_type) VALUES (?,?,?,?)"
    con = lite.connect('lecturasensor.db')
    print (data)
    #print (m)
    add = ()
    add = m
    #print (add)
    t2 = []
    for tupla in data:
        tupla2 = tupla + (add,)
        print (tupla2)
        t2.append(tupla2)
        
    print (t2)
    with con:
        cur = con.cursor()
        cur.executemany("INSERT INTO lectures(eixX,eixY,eixZ,data_type) VALUES (?,?,?,?)",t2)
        con.commit()
    con.close()
    f.close()


def main():
    print ("main")
    m = str(input("entra tipus de dada:  "))
    read_txt(m)
main()
