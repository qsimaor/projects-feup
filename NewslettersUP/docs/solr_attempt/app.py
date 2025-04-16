from flask import Flask, request, jsonify, render_template
from flask_cors import CORS
import requests
import os

app = Flask(__name__)
CORS(app)

SOLR_URL = 'http://localhost:8983/solr/newsletter/select'
NEWSLETTER_DIR = 'newsletters'

@app.route('/')
def index():
    return app.send_static_file('index.html')

@app.route('/search', methods=['GET'])
def search():
    query = request.args.get('q', '*:*')  # Default to *:* if no query is provided
    if query != '*:*':
        query = f'text:"{query}"'
    solr_query = {'q': query, 'wt': 'json', 'rows': 1000}  # Fetch a large number of documents
    response = requests.get(SOLR_URL, params=solr_query)
    if response.status_code == 200:
        return jsonify(response.json()['response']['docs'])
    else:
        return jsonify({'error': 'Failed to fetch data from Solr'}), response.status_code

@app.route('/universities', methods=['GET'])
def get_universities():
    solr_query = {'q': '*:*', 'wt': 'json'}
    response = requests.get(SOLR_URL, params=solr_query)
    if response.status_code == 200:
        return jsonify(response.json()['response']['docs'])
    else:
        return jsonify({'error': 'Failed to fetch data from Solr'}), 500

@app.route('/universities/<university>/news/<news_id>', methods=['GET'])
def get_news(university, news_id):
    solr_query = {'q': f'id:{news_id} AND university:{university}', 'wt': 'json'}
    response = requests.get(SOLR_URL, params=solr_query)
    docs = response.json().get('response', {}).get('docs', [])
    if docs:
        news = docs[0]
        preview_link = news.get('preview_link')
        if preview_link:
            preview_response = requests.get(preview_link)
            if preview_response.status_code == 200:
                return preview_response.text
        html_path = os.path.join(NEWSLETTER_DIR, news_id, f"{news_id}.html")
        if os.path.exists(html_path):
            with open(html_path, 'r') as file:
                content = file.read()
            return render_template('detail.html', content=content, archived=True)
    return "Notícia não encontrada", 404

if __name__ == "__main__":
    app.run(host='0.0.0.0', port=5000, debug=True)
