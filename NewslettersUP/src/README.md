# Arquivo da Universidade do Porto
### L.EIC@FEUP - UC Projeto Integrador

## Pré-requisitos

- Sistema Ubuntu versão 24.04 com privilégios sudo
- Conexão à internet
- Visual Studio Code (VSCode) com a extensão Live Server

## Guia Passo-a-Passo

### Passo 1: Atualizar

Primeiro, atualize as listas de pacotes e atualize os pacotes existentes para garantir que tem as versões mais recentes.

```bash
sudo apt update
sudo apt upgrade -y
```

### Passo 2: Instalar Python e Pip

Certifique-se de que tem o Python 3 e o pip instalados.

```bash
sudo apt install python3 python3-pip parallel wget -y
```

### Passo 3: Instalar Flask e Flask-CORS

Flask é um framework de aplicação web WSGI leve em Python. Flask-CORS é uma extensão do Flask para lidar com o Cross-Origin Resource Sharing (CORS).

```bash
pip3 install Flask Flask-Cors
```

### Passo 4: Instalar BeautifulSoup

BeautifulSoup é uma biblioteca para analisar documentos HTML e XML.

```bash
pip3 install beautifulsoup4
```

### Passo 5: Instalar aiohttp

aiohttp é um framework de cliente/servidor HTTP assíncrono para Python.

```bash
pip3 install aiohttp
```

### Passo 6: Instalar Requests

Requests é uma biblioteca HTTP simples e elegante para Python.

```bash
pip3 install requests
```

### Passo 7: Dependências Adicionais

Irá necessitar de algumas dependências adicionais para o projeto.

```bash
pip3 install subprocess glob json re datetime time
```

## Executar o Projeto

Dentro da pasta `data_pipeline` existe o ficheiro `data.py`. Esse descarrega toda a coleção de newsletters existentes, limpa e prepara a informação para ser exibida e serem feitas pesquisas sobre a mesma.

Depois, basta correr a API em `/api/app.py`e aceder à [interface](http://127.0.0.1:5500/src/index.html) depois de inicializar o Live Server do VSCode na root do projeto.

```bash
python3 data_pipeline/data.py
python3 api/app.py
```
