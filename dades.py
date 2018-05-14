#!/usr/bin/python
# -*- coding: utf-8 -*-
import sqlite3 as lite
import sys

#-------------------------------------------------------

def create_db():
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
        data_type varchar(10),
        prova_id integer(50) default 0
        );
        """)
        con.commit()
        #data_type -> indica el tipus de dades de les caigudes

#-------------------------------------------------------
        
def prova():
    con=lite.connect('lecturasensor.db')
    cursor = con.cursor()
    try:
        last = cursor.execute('SELECT * FROM lectures ORDER BY rowid DESC')
        last_id = last.fetchone()[-1]
        con.close()
        print (last_id)
        return last_id
    except:
        print('error')
        con.close()
        return 0

#-------------------------------------------------------

def read_txt(m):
    prova_id = ()
    prova_id = prova()+1
    print (prova_id)
    con = lite.connect('lecturasensor.db')    
    f = open("sensor.txt","r")
    info = f.readlines()
    read = [x.strip() for x in info]
    t = []
    for sample in read:
        t.append(tuple(sample.split(" , ")))
    data = list(t)
    action = "INSERT INTO lectures(eixX,eixY,eixZ,data_type,prova_id) VALUES (?,?,?,?,?)"
    con = lite.connect('lecturasensor.db')
    add = ()
    add = m
    dades = []
    for tupla in data:
        tupla2 = tupla + (add,prova_id,)
        dades.append(tupla2)
    with con:
        cur = con.cursor()
        cur.executemany("INSERT INTO lectures(eixX,eixY,eixZ,data_type,prova_id) VALUES (?,?,?,?,?)",dades)
        con.commit()
    con.close()
    f.close()
    
#-------------------------------------------------------

def export_data(export):
    con = lite.connect('lecturasensor.db')
    f = open("exported_data.txt", "w+")
    with con:
        cur = con.cursor()
        if (export == 1) :#exporta tot 
            cur.execute("SELECT * FROM lectures")
            exportar = cur.fetchall()
            for data in exportar:
                p = 0
                for information in data:
                    print (data)
                    #print (p)
                    if p == 5:
                        f.write(str(information))
                        f.write('\n')
                    if (p ==1) or (p == 2) or (p ==3):
                        p = p+1
                        f.write(str(information))
                        f.write(' ')
                    else:
                        p = p+1
        else:
            print("else")
                    
    f.close
    return
#-------------------------------------------------------

def main():
    print ("Inici")
    print("")
    t = True
    while t:
        print ("")
        print (" 1 - Afegir dades de caigudes")
        print (" 2 - Afegir dades de caminar")
        print (" 3 - Afegir dades d'escales")
        print (" 4 - Afegir dades de seure i aixecar")
        print (" 5 - Crear base de dades")
        print (" Altres - Sortir")
        option = eval(input("Opció escollida"))
        if option == 0:
            #prova()
            export_data(1)
        elif option ==1:
            m = str("caiguda")
            read_txt(m)
        elif option == 2:
            m = str("caminar")
            read_txt(m)
        elif option == 3:
            m = str("escales")
            read_txt(m)
        elif option == 4:
            m = str("seure")
            read_txt(m)
        elif option == 5:
            create_db()            
        else:
            print("fi")
            t = False
            
main()
