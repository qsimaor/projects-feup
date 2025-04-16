from flask import Flask, jsonify, request, send_file, send_from_directory
import os
import json
from flask_cors import CORS
from datetime import datetime

app = Flask(__name__)
CORS(app)

# Load data from the JSON files in the newsletters directory
def load_data():
    data_path = '../data_pipeline/newsletters'
    data = {}
    for university in os.listdir(data_path):
        university_path = os.path.join(data_path, university)
        if os.path.isdir(university_path):
            data[university] = []
            for tag in os.listdir(university_path):
                tag_path = os.path.join(university_path, tag)
                if os.path.isdir(tag_path):
                    for news_id in os.listdir(tag_path):
                        news_id_path = os.path.join(tag_path, news_id)
                        if os.path.isdir(news_id_path):
                            for filename in os.listdir(news_id_path):
                                if filename.endswith('.json'):
                                    file_path = os.path.join(news_id_path, filename)
                                    with open(file_path, 'r', encoding='utf-8') as file:
                                        news = json.load(file)
                                        news['html'] = file_path.replace('.json', '.html')
                                        news['path'] = news_id_path
                                        data[university].append(news)
    return data

data = load_data()

# Endpoint to get all news with filtering and search
@app.route('/universities', methods=['GET'])
def get_all_news():
    query = request.args.get('q')
    selected_units = request.args.get('units')
    start_date = request.args.get('startDate')
    end_date = request.args.get('endDate')
    type_filter = request.args.get('type')

    filtered_data = []

    for university, news_list in data.items():
        for news in news_list:
            match = True

            # Exclude newsletters with null or missing dates
            if 'date' not in news or not news['date']:
                continue

            if query and query.lower() not in news['text'].lower():
                match = False
            
            if selected_units:
                selected_units_list = selected_units.split(',')
                if news['university'] not in selected_units_list:
                    match = False
            
            if type_filter and type_filter != 'Nenhum' and news['tag'] != type_filter:
                match = False

            if start_date or end_date:
                try:
                    news_date = datetime.strptime(news['date'], '%d-%m-%Y') if news['date'] else None
                    if start_date and news_date and news_date < datetime.strptime(start_date, '%Y-%m-%d'):
                        match = False
                    if end_date and news_date and news_date > datetime.strptime(end_date, '%Y-%m-%d'):
                        match = False
                except (ValueError, TypeError) as e:
                    match = False

            if match:
                filtered_data.append(news)
    
    return jsonify(filtered_data)

# Endpoint to get the HTML content of a specific news
@app.route('/universities/<university>/news/<news_id>', methods=['GET'])
def get_news_html(university, news_id):
    for news in data.get(university, []):
        if str(news['id']) == news_id:
            html_path = os.path.join(news['path'], f"{news_id}.html")
            app.logger.info(f"Attempting to serve HTML file from: {html_path}")  # Add logging
            if os.path.exists(html_path):
                return send_file(html_path)
    return "Not Found", 404

# Endpoint to serve images
@app.route('/universities/<university>/news/<news_id>/images/<filename>', methods=['GET'])
def get_news_image(university, news_id, filename):
    for news in data.get(university, []):
        if str(news['id']) == news_id:
            images_path = os.path.join(news['path'], 'images')
            if os.path.exists(images_path):
                return send_from_directory(images_path, filename)
    return "Not Found", 404

if __name__ == '__main__':
    app.run(debug=True)
