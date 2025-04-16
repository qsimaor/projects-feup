#!/usr/bin/env python3

#https://realpython.com/python-command-line-arguments/
# seq_click.py

# passar dois argumentos: (só passar um)
# 1) nome da instancia
# 2) last_id das publicações que já foram sacadas (não passar este para já)

#para os argumentos
import sys
#para as configurações
import json

#mysql (start)
import mysql.connector
from mysql.connector import Error
#mysql (end)
#selenium (start)
from selenium import webdriver
from selenium.webdriver.firefox.service import Service
from selenium.webdriver.common.by import By
from selenium.webdriver.firefox.options import Options as FirefoxOptions

from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC

from pyvirtualdisplay import Display

# Start Xvfb
display = Display(visible=0, size=(800, 600))
display.start()

from PIL import Image

from time import sleep
#selenium (end)

from os.path import exists
from pathlib import Path

docroot = '/var/www/html/timeline/images'

#instancias = ['alumni','cdup','cefup','cultura','divulgacao','eugloh','fadeup','faup','fbaup','fcnaup','fcup','fdup','fep','feup','ffup','flup','fmdup','fmup','fpce','icbas','inovped','ispup','reitoria','sipreitoria','updigital','upin']

# instancias com configuração feita
instancias = ['alumni','cultura','faup','fcup','feup','flup','fmup','fmdup','fpce','icbas','ispup','reitoria','sipreitoria','updigital']

print(f"Name of the script      : {sys.argv[0]=}")
#print(f"Arguments of the script : {sys.argv[1:]=}")

instancia = sys.argv[1:][0]
#last_id=sys.argv[1:][1]

#print(instancia)

def validate_input(instancia):
    ret=0
    for i in instancias:
        if i == instancia:
            ret=1
            break
    return ret

def validate_input(last_id):
    if last_id is None:
        last_id = 0
    print("last_id="+last_id)

if validate_input(instancia):
    print("YEY")
#    with open("teste/"+instancia+".json") as json_file:
#        data = json.load(json_file)
        
#print(data)


with open("/opt/mkt_home/conf/config.json") as json_file:
    data = json.load(json_file)

#print(last_id)
    
#print(data['connection'][0]['host'])
#print(data['connection'][0]['user'])
#print(data['connection'][0]['password'])

# devia-se testar se a instancia tem configuração definida, senão atribuir default

for publication in data[instancia]:
    print(publication['publication'])
    print(publication['category_id'])
    print(publication['start_from_id'])
    print(publication['end_on_id'])
    print(publication['width'])
    print(publication['height'])
    print(publication['scrollto_x'])
    print(publication['scrollto_y'])
    print(publication['thumbnail_x'])
    print(publication['thumbnail_y'])

    from pathlib import Path
    Path(docroot + '/' + instancia).mkdir(parents=True, exist_ok=True)
    try:
        connection = mysql.connector.connect(host=data['connection'][0]['host'],database=instancia,user=data['connection'][0]['user'],password=data['connection'][0]['password'])
        if connection.is_connected():
            db_Info = connection.get_server_info()
            #print("Connected to MySQL Server version ", db_Info)
            cursor = connection.cursor()
            cursor.execute("select database();")
            record = cursor.fetchone()
            #print("You're connected to database: ", record)
            
        sql_select_Query = "select id,category_id,date_added,name,subject from emails where is_published=true and public_preview=true and category_id="+publication['category_id']
        
        cursor = connection.cursor()
        cursor.execute(sql_select_Query)
        # get all records
        records = cursor.fetchall()
        categorias = []
        print("Total number of rows in table: ", cursor.rowcount)
        
        #print("\nPrinting each row")
        for row in records:
            print("Id = ", row[0], )
            print("Category_id = ", row[1])
            print("date_modified  = ", row[2])
            print("name  = ", row[3])
            print("subject  = ", row[4], "\n")
            
            card = {
                "Id": row[0],
                "Category_id": row[1],
                "date_modified": row[2],
                "name": row[3],
                "subject": row[4]
            }
            Path("/opt/mkt_home/data/jsons/" + instancia + "/" + publication['publication']).mkdir(parents=True, exist_ok=True)
            filename="/opt/mkt_home/data/jsons/" + instancia + "/" + publication['publication'] + "/" +str(instancia)+"-"+str(row[0])+".json"
            if exists(filename):
                print ("File exist: Skiping!")
            else:
                #json_object = json.dumps(card, indent=4)
                with open(filename, "w") as outfile:
                    #outfile.write(json_object)
                    json.dump(card, outfile, default=str)
                #-- categorias (start)
                categorias.append(row[1])
                #-- categorias (end)
                s = Service('/usr/local/bin/geckodriver')
                firefox_options = FirefoxOptions()
                firefox_options.add_argument("--headless")
                #firefox_options.add_argument("--width="+publication['width'])
                # 800 -246
                #firefox_options.add_argument("--height="+publication['height'])
                firefox_options.add_argument("--window-size "+publication['width']+","+publication['height'])
                driver = webdriver.Firefox(service=s, options = firefox_options)
                #try:
                driver.implicitly_wait(5)
                driver.get('https://mkt.up.pt/' + instancia + '/email/preview/' + str(row[0]))
                #driver.maximize_window()
                #Dimension newDimension = new Dimension(publication['width'], publication['height'])
                print(driver.get_window_size())
                driver.set_window_size(publication['width'], publication['height'])
                size = driver.get_window_size()
                print("Window size: width = {}px, height = {}px".format(size["width"], size["height"]))

            
                #screen_height = driver.execute_script("return window.screen.height;")
                driver.execute_script("window.scrollTo("+publication['scrollto_x']+", "+publication['scrollto_y']+")")
            
                sleep(1)
            
                driver.get_screenshot_as_file(docroot + '/' + instancia + "/screenshot-" + str(row[0]) + ".png")
                #finally:
                driver.quit()
                display.stop()
                print("end...")
            
                try:
                    imgPath = docroot + '/' + instancia + '/screenshot-' + str(row[0]) + '.png'
                    img = Image.open(imgPath)
                    #img.show()
                    print('The size of img is: ', img.size)
                    print('After applying thumbnail() function')
                    img.thumbnail((int(publication['thumbnail_x']), int(publication['thumbnail_y'])))
                    img.save(docroot + '/' + instancia + '/thumbnail-' + str(row[0]) + '.png')
                    print('The size of thumbnail image is: ', img.size)
                except FileNotFoundError:
                    print('Provided image path is not found')
    #---
    except mysql.connector.Error as e:
        print("Error reading data from MySQL table", e)
    finally:
        #-- categories (start)
        # remover duplicados
        categorias = list(dict.fromkeys(categorias))
        for categoria in categorias:
            sql_select_Query = "select title from categories where id="+str(categoria)
            cursor = connection.cursor()
            cursor.execute(sql_select_Query)
            # get all records
            title = cursor.fetchall()
            card = {
                "Category_id": categoria,
                "title": title
            }
        #-- categories (end)
        if connection.is_connected():
            connection.close()
            cursor.close()
            print("MySQL connection is closed")

