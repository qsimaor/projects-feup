import subprocess
import requests
import os
import glob
import json
import asyncio
import aiohttp
import re
import datetime
from bs4 import BeautifulSoup
import time

university_content = []
html = []
images = []

def matchpattern(text,year):
    month_map = {
        "JAN": "01", "JANEIRO": "01", "JANUARY" : "01",
        "FEV": "02", "FEVEREIRO": "02", "FEBRUARY": "02",
        "MAR": "03", "MARÇO": "03", "MARCO": "03", "MARCH": "03",
        "ABR": "04", "ABRIL": "04", "APRIL": "04",
        "MAI": "05", "MAIO": "05", "MAY": "05",
        "JUN": "06", "JUNHO": "06", "JUNE": "06",
        "JUL": "07", "JULHO": "07", "JULY": "07",
        "AGO": "08", "AGOSTO": "08", "AUGUST": "08",
        "SET": "09", "SETEMBRO": "09", "SEPTEMBER": "09",
        "OUT": "10", "OUTUBRO": "10", "OCTOBER": "10",
        "NOV": "11", "NOVEMBRO": "11", "NOVEMBER": "11",
        "DEZ": "12", "DEZEMBRO": "12", "DECEMBER": "12"
    }

    # Define the pattern for matching the date format "1-10-2021" or "1/10/2021" or "1_10_2021" or "1 10 2021"
    pattern = re.compile(r'(\d{1,2})[-/_ ](\d{1,2})[-/_ ](\d{4})')
    match = pattern.search(text)
    if match:
        day, month, year = match.groups()
        return f"{day.zfill(2)}-{month.zfill(2)}-{year}"
    
    # Define the pattern for matching the date format "2021-10-1" or "2021/10/1" or "2021_10_1" or "2021 10 1"
    pattern = re.compile(r'(\d{4})[-/_ ](\d{1,2})[-/_ ](\d{1,2})')
    match = pattern.search(text)
    if match:
        year, month, day = match.groups()
        return f"{day.zfill(2)}-{month.zfill(2)}-{year}"
    
    # Define the pattern for matching the date format "10-2021" or "10/2021" or "10_2021" or "10 2021"
    pattern = re.compile(r'[ ](\d{1,2})[-/_ ](\d{4})')
    match = pattern.search(text)
    if match:
        month, year = match.groups()
        return f"01-{month.zfill(2)}-{year}"


    # Define the pattern for matching the date format "1 DE OUTUBRO 2021"
    pattern = re.compile(r'(\d{1,2})\s*DE\s*([A-ZÇ]+)\s*(\d{4})', re.IGNORECASE)
    match = pattern.search(text)
    if match:
        day, month_str, year = match.groups()
        month = month_map.get(month_str.upper(), None)
        if month:
            date = f"{day.zfill(2)}-{month}-{year}"
            return date
        
    # Define the pattern for matching the date format "1 DE OUTUBRO DE 2021"
    pattern = re.compile(r'(\d{1,2})\s*DE\s*([A-ZÇ]+)\s*DE\s*(\d{4})', re.IGNORECASE)
    match = pattern.search(text)
    if match:
        day, month_str, year = match.groups()
        month = month_map.get(month_str.upper(), None)
        if month:
            date = f"{day.zfill(2)}-{month}-{year}"
            return date

    # Define the pattern for matching the date format "1 OUTUBRO 2021" or "1_OUTUBRO_2021" or "1OUTUBRO2021"
    pattern = re.compile(r'(\d{1,2})[ _]?([A-ZÇ]+)[ _]?(\d{4})', re.IGNORECASE)
    match = pattern.search(text)
    if match:
        day, month_str, year = match.groups()
        month = month_map.get(month_str.upper(), None)
        if month:
            date = f"{day.zfill(2)}-{month}-{year}"
            return date

    # Define the pattern for matching the date format "1 OUTUBRO 21" or "1_OUTUBRO_21" or "1OUTUBRO21"
    pattern = re.compile(r'(\d{1,2})[ _]?([A-ZÇ]+)[ _]?(\d{2})', re.IGNORECASE)
    match = pattern.search(text)
    if match:
        day, month_str, year_suffix = match.groups()
        month = month_map.get(month_str.upper(), None)
        if month:
            year = f"20{year_suffix}"
            date = f"{day.zfill(2)}-{month}-{year}"
            return date

    # Define the pattern for matching the date format "21JUNHO22"
    pattern = re.compile(r'(\d{1,2})([A-ZÇ]+)(\d{2})', re.IGNORECASE)
    match = pattern.search(text)
    if match:
        day, month_str, year_suffix = match.groups()
        month = month_map.get(month_str.upper(), None)
        if month:
            year = f"20{year_suffix}"
            date = f"{day.zfill(2)}-{month}-{year}"
            return date
    # Define the pattern for matching the date format "JUNHO2024" or "JUNHO_2024" or "JUNHO-2024"
    pattern = re.compile(r'([A-ZÇ]+)[ _-]?(\d{4})', re.IGNORECASE)
    match = pattern.search(text)
    if match:
        month_str, year = match.groups()
        month = month_map.get(month_str.upper(), None)
        if month:
            return f"01-{month}-{year}"

    # Define the pattern for matching the date format "JUNHO24" or "JUNHO_24" or "JUNHO24"
    pattern = re.compile(r'([A-ZÇ]+)[ _-]?(\d{2})', re.IGNORECASE)
    match = pattern.search(text)
    if match:
        month_str, year_suffix = match.groups()
        month = month_map.get(month_str.upper(), None)
        if month:
            year = f"20{year_suffix}"
            return f"01-{month}-{year}"

    # Define the pattern for matching the date format "19 A 26 DE ABRIL"
    pattern = re.compile(r'(\d{1,2})[ _/-]?A[ _/-]?(\d{1,2})[ _/-]?DE[ _/-]?([A-Zç]+)', re.IGNORECASE)
    match = pattern.search(text)
    if match:
        start_day, end_day, month_str = match.groups()
        month = month_map.get(month_str.upper(), None)
        if month:
            return f"{start_day.zfill(2)}-{month}-{year}"      
          
    # Define the pattern for matching the date format "19 A 26 ABRIL"
    pattern = re.compile(r'(\d{1,2})[ _/-]?A[ _/-]?(\d{1,2})[ _/-]?([A-Zç]+)', re.IGNORECASE)
    match = pattern.search(text)
    if match:
        start_day, end_day, month_str = match.groups()
        month = month_map.get(month_str.upper(), None)
        if month:
            return f"{start_day.zfill(2)}-{month}-{year}"  

    # Define the pattern for matching the date format "19 OUTUBRO" ou "19 OUT"    
    pattern = re.compile(r'(\d{1,2})[ _-]?([A-ZÇ]+)', re.IGNORECASE)
    match = pattern.search(text)
    if match:
        day, month_str = match.groups()
        month = month_map.get(month_str.upper(), None)
        if month:
            return f"{day.zfill(2)}-{month}-{year}"
        
    # Define the pattern for matching the date format "19 DE OUTUBRO" ou "19 DE OUT"    
    pattern = re.compile(r'(\d{1,2})[ _-]?DE[ _-]?([A-ZÇ]+)', re.IGNORECASE)
    match = pattern.search(text)
    if match:
        day, month_str = match.groups()
        month = month_map.get(month_str.upper(), None)
        if month:
            return f"{day.zfill(2)}-{month}-{year}"
        
    # Define the pattern for matching the date format "MARÇO-ABRIL" or "MARÇO_ABRIL" or "MARÇO / ABRIL" or "MARÇO ABRIL"
    pattern = re.compile(r'([A-ZÇ]+)[-_/ ]?([A-ZÇ]+)', re.IGNORECASE)
    match = pattern.search(text)
    if match:
        start_month, end_month = match.groups()
        start_month = month_map.get(start_month.upper(), None)
        if start_month and end_month:
            return f"01-{start_month}-{year}" 
        
    # Define the pattern for matching the date format "MARÇO-ABRIL-22" or "MARÇO_ABRIL_22" or "MARÇO / ABRIL / 22" or "MARÇO ABRIL 22"
    pattern = re.compile(r'([A-ZÇ]+)[-_/ ]?([A-ZÇ]+)[-_/ ]?(\d{2})', re.IGNORECASE)
    match = pattern.search(text)
    if match:
        start_month, end_month, year = match.groups()
        start_month = month_map.get(start_month.upper(), None)
        end_month = month_map.get(end_month.upper(), None)
        if start_month and end_month:
            return f"01-{start_month}-{year}" 
        
    # Define the pattern for matching the date format "27 de março a 01 de abril, 2023"
    pattern = re.compile(r'(\d{1,2})[ /_-]?de[ /_-]?([A-ZÇ]+)[ /_-]?a[ /_-]?(\d{1,2})[ /_-]?de[ /_-]?([A-ZÇ]+),[ /_-]?(\d{4})', re.IGNORECASE)
    match = pattern.search(text)
    if match:
        start_day, start_month_str, end_day, end_month_str, year = match.groups()
        start_month = month_map.get(start_month_str.upper(), None)
        end_month = month_map.get(end_month_str.upper(), None)
        if start_month and end_month:
            return f"{start_day.zfill(2)}-{start_month}-{year}"
        
    # Define the pattern for matching the date format "JUNHO"
    pattern = re.compile(r'([A-ZÇ]+)', re.IGNORECASE)
    match = pattern.search(text)
    if match:
        month_str = match.group(1)
        month = month_map.get(month_str.upper(), None)
        if month:
            return f"01-{month}-{year}"


    return None

def scrape():
    url = 'https://mkt.up.pt/timeline'

    comando = [
        'wget',
        '-k',
        '--mirror',
        '--base=solr.apache.org',
        '--adjust-extension',
        '--level=1',
        '--convert-links',
        url
    ]

    subprocess.run(comando, capture_output=True, text=True)


def organizeData(uni, tag, number, date, html_content, url,year):
    soup = BeautifulSoup(html_content, "html.parser")
    title_tag = soup.find("title")

    img_tags = soup.find_all('img', src=True)
    images_temp = []
    for img_tag in img_tags:
        if img_tag:
            img_url = img_tag.get('src')
            if img_url:
                images_temp.append(img_url)
                img_tag['src'] = f"images/{img_url.split('/')[-1]}"

    images.append(images_temp)
    html.append(soup.prettify())

    all_text = soup.get_text()

    if date == None:
        date = matchpattern(all_text.upper(),year)


    if title_tag:
        title_content = title_tag.string

        if tag == "newsletter":
            tag = "newsletter-"+uni

        if number not in university_content:
            university_content.append({
                "id": number,
                "university": uni,
                "tag": tag,
                "date": date,
                "title": title_content,
                "preview link" : url,
                "text" : all_text
            })
    return university_content

def getDate(header,year):
    
    text = header.upper()
    return matchpattern(text,year)

def getPreviews():
    paths = set()
    previews = []

    folder_path = 'mkt.up.pt/timeline'

    for entry in os.listdir(folder_path):
        full_path = os.path.join(folder_path, entry)
        if os.path.isdir(full_path):
            paths.add(entry)

    for path in paths:
        folder_path = os.path.join('mkt.up.pt/timeline', path)
        for file_path in glob.glob(os.path.join(folder_path, '**', '*.html'), recursive=True):
            with open(file_path, 'r', encoding='utf-8') as file:
                tag = file_path.split('/')[-1]
                soup = BeautifulSoup(file.read(), 'html.parser')
                articles = soup.find_all('div', class_='portfolio-item')
                year = None
                for article in articles:
                    year = None
                    for class_name in article['class']:
                        if class_name.startswith('filter-'):
                            year = class_name.split('-')[-1]
                            break
                    title_tag = article.find('h4')
                    preview_link_tag = article.find('a', class_='portfolio-details-lightbox')

                    title = title_tag.get_text(strip=True) if title_tag else None
                    preview_link = preview_link_tag['href'] if preview_link_tag else None

                    date = getDate(title,year)
                    tag = file_path.split('.')[-2].split('/')[-1]
                    num = preview_link_tag['href'].split('/')[-1]
                    if num not in previews:
                        previews.append({
                            'tag' : tag,
                            'date': date,
                            'url': preview_link,
                            'year': year
                        })
    return previews

async def fetch_page(session, url, tag, date, year, retries=3):
    try:
        async with session.get(url) as response:
            parts = url.split('/')
            category = parts[-4]
            number = parts[-1]
            if response.status == 200:
                html_content = await response.text()
                organizeData(category, tag, number,date, html_content, url,year)
            else:
                print(f"Failed to fetch {url}: {response.status}")
    except (aiohttp.ClientError, asyncio.TimeoutError) as e:
        if retries > 0:
            print(f"An error occurred while processing {url}: {e}. Retrying...")
            await asyncio.sleep(1)
            await fetch_page(session, url, tag, date,year,retries - 1)
        else:
            print(f"Failed to process {url} after multiple attempts: {e}")

async def fetchPreviews():
    previews = getPreviews()
    async with aiohttp.ClientSession() as session:
        tasks = [fetch_page(session, data["url"], data['tag'], data['date'], data['year']) for data in previews]
        await asyncio.gather(*tasks)

def main():

    start_time = time.time()

    if os.path.exists("mkt.up.pt"):
        os.system("rm -r mkt.up.pt")
    if os.path.exists("newsletters"):
        os.system("rm -r newsletters")
    if os.path.exists("images_urls.txt"):
        os.remove("images_urls.txt")

    print("Scraping newsletters...")
    scrape()

    print("Organizing data...")
    asyncio.run(fetchPreviews())

    print("Saving files...")
    for i in range(0, len(university_content)):
        content = university_content[i]
        output_file_json = f"newsletters/{content['university']}/{content['tag']}/{content['id']}/{content['id']}.json"
        output_file_html = f"newsletters/{content['university']}/{content['tag']}/{content['id']}/{content['id']}.html"
        output_images_folder = f"newsletters/{content['university']}/{content['tag']}/{content['id']}/images"

        os.makedirs(os.path.dirname(output_file_json), exist_ok=True)
        os.makedirs(os.path.dirname(output_file_html), exist_ok=True)
        os.makedirs(output_images_folder, exist_ok=True)

        with open(output_file_json, "w", encoding="utf-8") as json_file:
            json.dump(content, json_file, ensure_ascii=False, indent=4)
        
        with open(output_file_html, "w", encoding="utf-8") as html_file:
            html_file.write(html[i])

        with open("images_urls.txt", "a") as url_file:
            for img_url in images[i]:
                image_filename = os.path.join(output_images_folder, img_url.split('/')[-1])
                wget_command = f"wget -nc -P {output_images_folder} -O {image_filename} {img_url}"
                url_file.write(f"{wget_command}\n")

    print("Downloading images...")
    os.system(f"cat images_urls.txt | parallel")
    os.remove("images_urls.txt")

    print(f"Runtime: {time.time() - start_time} seconds")

if __name__ == "__main__":
    main()
