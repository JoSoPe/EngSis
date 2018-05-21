import sqlite3 as lite
import sys
import datetime
#from dades import *


def readline ():
    f = open("exported_data.csv","r")
    info = f.readlines()
 #    print (info)
    m=[]
    p=0
    dada = info.split(';')
    for element in dada:
        print (element)
        print (p)
        p=p+1
    #for sample in read:
        #for element in sample:
            #print (sample[0])

       # print (sample)
#    for element in info:
#        print (element)
    
#    print (info)


readline()

"""
filtre per tal d'eliminar quasibé totes les dades, només es "colen"algunes dades de seure i aixecar -> 
select * from lectures where abs(eixX)>300 and (abs(eixY)>145 or abs(eixZ)>145);

"""


