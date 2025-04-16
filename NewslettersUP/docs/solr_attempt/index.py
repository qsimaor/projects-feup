import os
import json
import requests

SOLR_URL = 'http://localhost:8983/solr/newsletter/update?commit=true'
SOLR_DELETE_URL = 'http://localhost:8983/solr/newsletter/update?commit=true'

def delete_all_documents():
    # Enviar uma solicitação para deletar todos os documentos
    delete_query = {'delete': {'query': '*:*'}}
    response = requests.post(SOLR_DELETE_URL, json=delete_query)
    if response.status_code == 200:
        print("Todos os documentos foram deletados com sucesso.")
    else:
        print(f"Falha ao deletar documentos: {response.content}")

def index_json(directory):
    for root, dirs, files in os.walk(directory):
        for file in files:
            if file.endswith(".json"):
                with open(os.path.join(root, file), 'r') as f:
                    json_data = json.load(f)
                    json_data['html'] = open(os.path.join(root, f"{json_data['id']}.html"), 'r').read()
                    response = requests.post(SOLR_URL, json=[json_data])
                    if response.status_code != 200:
                        print(f"Falha ao indexar {file}: {response.content}")
                    else:
                        print(f"{file} indexado com sucesso.")

if __name__ == "__main__":
    delete_all_documents()
    index_json('newsletters')
